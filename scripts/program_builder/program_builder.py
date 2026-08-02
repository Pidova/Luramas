#!/usr/bin/env python3
import argparse
import json
import os
import re
import shlex
import shutil
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass, field, asdict
from pathlib import Path
from typing import Dict, List, Optional

sys.path.insert(0, str(Path(__file__).resolve().parent));
try:
    from ground_truth import analyse_image
except ModuleNotFoundError as exc:                      # missing capstone/pyelftools
    raise SystemExit(
        f'cannot import the extractor: {exc}\n'
        f'the metadata pass needs its dependencies:\n'
        f'    pip install -r requirements.txt') from exc

MAIN_RE = re.compile(r'^\s*(?:int|void)\s+main\s*\(', re.MULTILINE);

CC_CANDIDATES = ('clang', 'gcc', 'cc');


def default_cc() -> str:
    """$CC if set, else the first compiler actually present. Defaulting to a
    hard-coded 'clang' made the whole run abort on a gcc-only box, which looked
    like an empty output folder."""
    env = os.environ.get('CC');
    if env:
        return env;
    for cand in CC_CANDIDATES:
        if shutil.which(cand):
            return cand;
    return CC_CANDIDATES[0];


@dataclass
class BuildResult:
    name: str;
    source: str;
    opt: str;
    kind: str;                       # 'executable' | 'image'
    status: str;                     # 'ok' | 'compile-failed' | 'link-failed' | 'meta-failed'
    binary: Optional[str] = None;
    metadata: Optional[str] = None;
    asm: Optional[str] = None;
    units: List[str] = field(default_factory=list);
    notes: List[str] = field(default_factory=list);
    diagnostics: str = '';
    summary: Dict[str, int] = field(default_factory=dict);
    smc: str = '';


# ---------------------------------------------------------------------------
# toolchain
# ---------------------------------------------------------------------------

class Toolchain:
    """Probes the compiler once so unsupported flags are dropped instead of
    breaking every build (clang's integrated assembler has no -Wa,-L)."""

    def __init__(self, cc: str, cf_protection: str, extra_cflags: List[str],
                 extra_ldflags: List[str], static: bool, strict: bool,
                 target: Optional[str] = None):
        # A driver can be more than one word ('zig cc', 'ccache gcc'), so keep
        # the argv form alongside the display string.
        self.cc = cc;
        self.cc_cmd = shlex.split(cc, posix=(os.name != 'nt'));
        if not self.cc_cmd:
            raise SystemExit('--cc is empty');
        self.target = target;
        self.static = static;
        self.strict = strict;
        self.dropped: List[str] = [];
        self.image_ok = True;
        self.image_error = '';
        self.version = self._version();
        self.is_clang = 'clang' in self.version.lower();

        self.cflags = ['-g', '-gdwarf-4', '-fno-pie', '-w',
                       '-fno-omit-frame-pointer'];
        self.ldflags = ['-no-pie', '-Wl,--emit-relocs', '-Wl,-z,noexecstack',
                        '-Wl,-z,relro', '-Wl,-z,now'];
        # Extra flags for a translation unit with no main: lay the code out at
        # real virtual addresses without requiring an entry point or a
        # complete symbol set. Hoisted out of build_one so they get probed too.
        self.image_ldflags = ['-nostartfiles',
                              '-Wl,--unresolved-symbols=ignore-all',
                              '-Wl,-e,0'];
        self.libs = ['-lm'];
        if target:
            # single token: '--target=X' survives per-flag probing, where
            # '-target X' would be split and each half rejected on its own.
            for bucket in ('cflags', 'ldflags'):
                getattr(self, bucket)[:0] = [f'--target={target}'];

        optional = [
            ('-Wa,-L', 'cflags'),               # keep .L labels in the symtab
            ('-Wtrampolines', 'cflags'),        # nested-function trampolines
            ('-fno-ident', 'cflags'),
            # zig cc enables UBSan by default, which links ~800 runtime
            # functions into every image and imports mmap64, making the SMC
            # audit flag all of them. A no-op on gcc, which has it off already.
            ('-fno-sanitize=undefined', 'cflags'),
        ];
        if cf_protection == 'none':
            optional.append(('-fcf-protection=none', 'cflags'));
        for flag, bucket in optional:
            if self._accepts(flag):
                getattr(self, bucket).append(flag);
            else:
                print(f'note: {cc} rejects {flag}, continuing without it',
                      file=sys.stderr);

        if self.is_clang and '-Wa,-L' not in self.cflags:
            if self._accepts('-fno-integrated-as'):
                self.cflags += ['-fno-integrated-as', '-Wa,-L'];

        if strict:
            self.cflags.append('-Werror=trampolines') if self._accepts('-Werror=trampolines') else None;
        if static:
            self.ldflags.append('-static');
        self.cflags += extra_cflags;
        self.ldflags += extra_ldflags;

    def _run(self, cmd: List[str], timeout: int = 120):
        try:
            return subprocess.run(cmd, capture_output=True, text=True,
                                  timeout=timeout);
        except (OSError, subprocess.SubprocessError):
            return None;

    def _version(self) -> str:
        out = self._run([*self.cc_cmd, '--version'], timeout=60);
        if out is None:
            raise SystemExit(f'cannot run compiler {self.cc!r}');
        return out.stdout.splitlines()[0] if out.stdout else self.cc;

    def _filter_links(self) -> None:
        """Probe the link flags the way cflags were already probed.

        Only cflags used to be probed, so any driver that rejected a single
        link flag failed every link in the corpus: MinGW's ld has no '-z',
        zig cc's driver has no '--emit-relocs'. Drop what the linker will not
        take and record it, instead of losing the whole run to one flag.
        """
        with tempfile.TemporaryDirectory() as tmp:
            tmpdir = Path(tmp);
            main_c = tmpdir / 'm.c';
            main_c.write_text('int main(void){return 0;}\n');
            main_o = tmpdir / 'm.o';
            if (r := self._run([*self.cc_cmd, *self.cflags, '-c', str(main_c),
                                '-o', str(main_o)])) is None or r.returncode:
                return;                      # probe_baseline reports this

            # a unit with no main and an unresolved reference: the exact shape
            # the image path has to tolerate
            img_c = tmpdir / 'i.c';
            img_c.write_text('extern int elsewhere(void);\n'
                             'int here(void){return elsewhere();}\n');
            img_o = tmpdir / 'i.o';
            have_img = ((r := self._run([*self.cc_cmd, *self.cflags, '-c',
                                         str(img_c), '-o', str(img_o)]))
                        is not None and r.returncode == 0);

            def keep(flags: List[str], base: List[str], bucket: str) -> List[str]:
                # Test each flag for recognition against an object that
                # links cleanly, so a flag is only dropped when the
                # driver itself rejects it -- never because some
                # other flag is missing.
                kept: List[str] = [];
                for flag in flags:
                    r = self._run([*self.cc_cmd, *base, *kept, flag,
                                   str(main_o), '-o',
                                   str(tmpdir / 'probe.bin'), *self.libs]);
                    if r is not None and r.returncode == 0:
                        kept.append(flag);
                    else:
                        self.dropped.append(f'{bucket}:{flag}');
                        print(f'note: {self.cc} rejects {flag}, continuing '
                              f'without it', file=sys.stderr);
                return kept;

            self.ldflags = keep(self.ldflags, [], 'link');
            self.image_ldflags = keep(self.image_ldflags, self.ldflags, 'image');

            # A no-main unit only lays out if the linker tolerates unresolved
            # symbols. Check the assembled recipe once; if it cannot, say so
            # up front rather than failing 41% of the corpus one file at a time.
            if have_img:
                r = self._run([*self.cc_cmd, *self.ldflags, *self.image_ldflags,
                               str(img_o), '-o', str(tmpdir / 'img.bin')]);
                self.image_ok = r is not None and r.returncode == 0;
                if not self.image_ok:
                    self.image_error = ((r.stderr or r.stdout).strip()[-600:]
                                        if r is not None else 'linker not runnable');

    def _accepts(self, flag: str) -> bool:
        with tempfile.TemporaryDirectory() as tmp:
            src = Path(tmp) / 'probe.c';
            src.write_text('int main(void){return 0;}\n');
            res = self._run([*self.cc_cmd, flag, '-c', str(src), '-o',
                             str(Path(tmp) / 'probe.o')], timeout=60);
            return res is not None and res.returncode == 0;

    def probe_baseline(self) -> Optional[str]:
        """Compile *and link* a trivial program with the exact final flag set.

        Without this the driver happily launches the whole job matrix against a
        toolchain that cannot build anything -- a bad --force-include header, a
        --static with no static libc, a linker that rejects --emit-relocs -- and
        every entry fails identically. The user sees an output tree of empty
        directories and no error. Fail once, up front, with the real diagnostic.
        Returns None when the toolchain is usable, else the diagnostic text.
        """
        with tempfile.TemporaryDirectory() as tmp:
            tmpdir = Path(tmp);
            src = tmpdir / 'baseline.c';
            src.write_text('int main(void){return 0;}\n');
            obj = tmpdir / 'baseline.o';
            steps = [
                ('compile', [*self.cc_cmd, '-O0', *self.cflags, '-c', str(src),
                             '-o', str(obj)]),
                ('link', [*self.cc_cmd, *self.ldflags, str(obj), '-o',
                          str(tmpdir / 'baseline.bin'), *self.libs]),
            ];
            for phase, cmd in steps:
                try:
                    res = subprocess.run(cmd, capture_output=True, text=True,
                                         timeout=120);
                except (OSError, subprocess.SubprocessError) as exc:
                    return f'{phase} probe could not run: {exc}';
                if res.returncode != 0:
                    detail = (res.stderr or res.stdout).strip();
                    return (f'{phase} probe failed with the configured flags:\n'
                            f'  {" ".join(cmd)}\n'
                            f'{detail[-1500:]}');
            # The extractor is ELF-only, so a driver that links a valid PE or
            # Mach-O image is still useless here: every entry would come back
            # meta-failed with 'Magic number does not match' after a full build.
            probe_bin = tmpdir / 'baseline.bin';
            try:
                magic = probe_bin.open('rb').read(4);
            except OSError:
                return 'link probe produced no output file';
            if magic != b'\x7fELF':
                fmt = ('PE/COFF (Windows)' if magic[:2] == b'MZ'
                       else 'Mach-O (macOS)' if magic[:4] in
                       (b'\xcf\xfa\xed\xfe', b'\xce\xfa\xed\xfe')
                       else f'unrecognised ({magic!r})');
                return (f'this toolchain produces {fmt}, but the extractor '
                        f'reads ELF only.\n'
                        f'cross-compile to Linux instead, e.g.\n'
                        f'  --cc "zig cc" --target x86_64-linux-gnu');
        return None;

    def describe(self) -> dict:
        return {
            'cc': self.cc,
            'version': self.version,
            'target': self.target,
            'cflags': self.cflags,
            'ldflags': self.ldflags,
            'image_ldflags': self.image_ldflags,
            'libs': self.libs,
            'static': self.static,
            'dropped_flags': self.dropped,
            'image_link_supported': self.image_ok,
        };


# ---------------------------------------------------------------------------
# building
# ---------------------------------------------------------------------------

def has_main(path: Path) -> bool:
    try:
        return bool(MAIN_RE.search(path.read_text(encoding='utf-8', errors='ignore')));
    except OSError:
        return False;


def rel_key(root: Path, src: Path) -> str:
    """Stable identifier for a program: its path relative to the source root."""
    return src.relative_to(root).as_posix();


def output_paths(root: Path, src: Path, opt: str, out_root: Path) -> Dict[str, Path]:
    """Mirror the source layout, tagging each artifact with its opt level so
    several corpora can live side by side."""
    stem = (out_root / src.relative_to(root)).with_suffix('');
    return {
        'binary': stem.with_name(f'{stem.name}.{opt}'),
        'metadata': stem.with_name(f'{stem.name}.{opt}.meta.json'),
        'asm': stem.with_name(f'{stem.name}.{opt}.s'),
    };


MISSING_HEADER_RE = re.compile(r"fatal error: ([^:]+): No such file or directory");
UNDEFINED_REF_RE = re.compile(r"undefined reference to");


def case_shim(src: Path, stderr: str, scratch: Path) -> Optional[Path]:
    """Some corpus files were written on a case-insensitive filesystem and ask
    for `Graph.h` when the file on disk is `graph.h`. Build a directory of
    correctly-cased links rather than dropping the entry."""
    wanted = MISSING_HEADER_RE.findall(stderr);
    if not wanted:
        return None;
    made = False;
    scratch.mkdir(parents=True, exist_ok=True);
    for header in wanted:
        target = Path(header).name;
        for candidate in src.parent.iterdir():
            if candidate.is_file() and candidate.name.lower() == target.lower():
                link = scratch / target;
                if not link.exists():
                    try:
                        link.symlink_to(candidate.resolve());
                    except OSError:
                        shutil.copyfile(candidate, link);
                made = True;
                break;
    return scratch if made else None;


def sibling_units(src: Path) -> List[Path]:
    """`main.c` next to `dynamic_array.c` is one program, not two. Anything in
    the same folder that does not declare its own main is fair game."""
    out = [];
    for candidate in sorted(src.parent.glob('*.c')):
        if candidate == src or has_main(candidate):
            continue;
        out.append(candidate);
    return out;


def build_one(tc: Toolchain, root: Path, src: Path, opt: str, out_root: Path,
              scope: str, save_asm: bool, timeout: int,
              with_edges: bool = True) -> BuildResult:
    name = rel_key(root, src);
    kind = 'executable' if has_main(src) else 'image';
    paths = output_paths(root, src, opt, out_root);
    binary = paths['binary'];
    tmp_prefix = binary.name;

    res = BuildResult(name=name, source=str(src), opt=opt, kind=kind, status='ok');
    res.units = [str(src)];

    if kind == 'image' and not tc.image_ok:
        # This linker cannot lay out a unit with no main (it will not tolerate
        # unresolved symbols). Say that once, per entry, instead of emitting an
        # identical link error for every such source in the corpus.
        res.status = 'image-unsupported';
        res.diagnostics = ('linker cannot lay out a translation unit with no '
                           'main; needs --unresolved-symbols=ignore-all or an '
                           'equivalent');
        return res;

    with tempfile.TemporaryDirectory(prefix=f'{tmp_prefix}.') as tmp:
        tmpdir = Path(tmp);
        includes = [f'-I{src.parent}'];

        def compile_unit(unit: Path, obj: Path) -> subprocess.CompletedProcess:
            cmd = [*tc.cc_cmd, f'-{opt}', *tc.cflags, '-c', str(unit),
                   '-o', str(obj), *includes];
            return subprocess.run(cmd, capture_output=True, text=True, timeout=timeout);

        obj = tmpdir / 'unit.o';
        try:
            cp = compile_unit(src, obj);
            if cp.returncode != 0:
                shim = case_shim(src, cp.stderr, tmpdir / 'shim');
                if shim is not None:
                    includes.append(f'-I{shim}');
                    res.notes.append('case-insensitive include shim applied');
                    cp = compile_unit(src, obj);
        except subprocess.TimeoutExpired:
            res.status = 'compile-failed';
            res.diagnostics = f'timeout after {timeout}s';
            return res;
        if cp.returncode != 0:
            res.status = 'compile-failed';
            res.diagnostics = cp.stderr.strip()[-1200:];
            return res;

        tmp_asm = tmpdir / 'unit.s';
        if save_asm:
            subprocess.run([*tc.cc_cmd, f'-{opt}', *tc.cflags, '-S', str(src),
                            '-o', str(tmp_asm), *includes],
                           capture_output=True, text=True, timeout=timeout);

        tmp_bin = tmpdir / 'unit.bin';

        def link(objs: List[Path]) -> subprocess.CompletedProcess:
            if kind == 'executable':
                cmd = [*tc.cc_cmd, *tc.ldflags, *[str(o) for o in objs],
                       '-o', str(tmp_bin), *tc.libs];
            else:
                # No main: still lay the code out at real addresses so the
                # metadata carries virtual addresses, not section offsets.
                cmd = [*tc.cc_cmd, *tc.ldflags, *tc.image_ldflags,
                       *[str(o) for o in objs], '-o', str(tmp_bin)];
            return subprocess.run(cmd, capture_output=True, text=True, timeout=timeout);

        try:
            lp = link([obj]);
            if lp.returncode != 0 and UNDEFINED_REF_RE.search(lp.stderr):
                objs = [obj];
                for i, unit in enumerate(sibling_units(src)):
                    sib = tmpdir / f'sib{i}.o';
                    sp = compile_unit(unit, sib);
                    if sp.returncode == 0:
                        objs.append(sib);
                        res.units.append(str(unit));
                if len(objs) > 1:
                    res.notes.append(f'linked with {len(objs) - 1} sibling unit(s)');
                    lp = link(objs);
        except subprocess.TimeoutExpired:
            res.status = 'link-failed';
            res.diagnostics = f'timeout after {timeout}s';
            return res;
        if lp.returncode != 0:
            res.status = 'link-failed';
            res.diagnostics = lp.stderr.strip()[-1200:];
            return res;

        if not tmp_bin.is_file():
            res.status = 'link-failed';
            res.diagnostics = ('linker reported success but produced no output '
                               f'at {tmp_bin.name}');
            return res;

        # Only now that there is a real artifact do we touch the output tree,
        # so a failed corpus leaves no skeleton of empty directories behind.
        try:
            binary.parent.mkdir(parents=True, exist_ok=True);
            shutil.move(str(tmp_bin), str(binary));
            if save_asm and tmp_asm.is_file():
                shutil.move(str(tmp_asm), str(paths['asm']));
                res.asm = str(paths['asm']);
        except OSError as exc:
            res.status = 'link-failed';
            res.diagnostics = f'cannot write artifact: {exc}';
            return res;

    res.binary = str(binary);

    try:
        meta = analyse_image(binary, scope=scope, with_edges=with_edges);
        meta['source'] = str(src);
        meta['units'] = res.units;
        meta['opt'] = opt;
        meta['kind'] = kind;
        meta['toolchain'] = tc.describe();
        paths['metadata'].write_text(json.dumps(meta, indent=2), encoding='utf-8');
    except Exception as exc:
        res.status = 'meta-failed';
        res.diagnostics = f'{type(exc).__name__}: {exc}';
        return res;

    res.metadata = str(paths['metadata']);
    res.summary = meta.get('summary') or {};
    res.smc = (meta.get('smc') or {}).get('verdict', 'unknown');
    return res;

# driver

def discover(root: Path, exclude: List[str]) -> List[Path]:
    out = [];
    for path in sorted(root.rglob('*.c')):
        rel = str(path.relative_to(root));
        if any(pat in rel for pat in exclude):
            continue;
        out.append(path);
    return out;


def first_error(diagnostics: str) -> str:
    """Pull the line a human wants out of a compiler dump. gcc ends its output
    with a caret/source-echo line, so the naive `splitlines()[-1]` reported
    something like `|      ;` instead of the actual error."""
    lines = [ln.strip() for ln in (diagnostics or '').splitlines() if ln.strip()];
    if not lines:
        return '(no diagnostic)';
    for ln in lines:
        if 'error:' in ln:
            return ln;
    for ln in lines:
        if 'warning:' not in ln and not ln.startswith(('|', '^', '~')):
            return ln;
    return lines[-1];


def clean(out_root: Path, opts: List[str]) -> int:
    """Remove artifacts from a previous run. Only files this script generates
    are matched, so it is safe to point at a tree holding the sources."""
    removed = 0;
    patterns = [f'*.{opt}' for opt in opts];
    patterns += [f'*.{opt}.meta.json' for opt in opts];
    patterns += [f'*.{opt}.s' for opt in opts];
    for pattern in patterns:
        for path in out_root.rglob(pattern):
            if path.is_file():
                path.unlink();
                removed += 1;
    index = out_root / 'program_index.json';
    if index.is_file():
        index.unlink();
        removed += 1;
    # Older runs created a directory per source folder up front, whether or not
    # anything was ever written into it. Prune what is now empty, deepest first.
    for path in sorted(out_root.rglob('*'), key=lambda q: len(q.parts), reverse=True):
        if path.is_dir():
            try:
                path.rmdir();
            except OSError:
                pass;
    return removed;


def main() -> int:
     
    # Options
    ap = argparse.ArgumentParser(
        description='Compile every C program in a folder into decompiler-ready '
                    'images with ground-truth metadata.');
    ap.add_argument('sources', type=Path, help='folder to walk for .c files');
    ap.add_argument('-o', '--out', type=Path, default=None,
                    help='write artifacts under this root instead of next to '
                         'the sources, keeping the same relative layout');
    ap.add_argument('--clean', action='store_true',
                    help='delete previously generated artifacts and exit');
    ap.add_argument('--cc', default=None,
                    help='compiler to drive; may be multi-word, e.g. '
                         '--cc "zig cc" (default: $CC, else the first of '
                         'clang/gcc/cc found on PATH)');
    ap.add_argument('--target', default=None,
                    help='cross-compile triple passed as -target to a '
                         'clang-style driver, e.g. x86_64-linux-gnu. The '
                         'extractor only reads ELF, so a Windows or macOS '
                         'host must cross-compile to Linux');
    ap.add_argument('--opt', nargs='+', default=['O0', 'O2'],
                    help='optimisation levels to build, one corpus per level');
    ap.add_argument('--jobs', type=int, default=os.cpu_count() or 4);
    ap.add_argument('--scope', choices=('user', 'all'), default='user',
                    help='metadata scope: user code only, or the whole image');
    ap.add_argument('--static', action='store_true',
                    help='link statically (no PLT, everything in one image)');
    ap.add_argument('--cf-protection', choices=('none', 'default'), default='none',
                    help='none drops endbr64/notrack padding for a cleaner lift');
    ap.add_argument('--no-edges', action='store_true',
                    help='omit the per-instruction edge list from the metadata');
    ap.add_argument('--save-asm', action='store_true',
                    help='also keep the .s next to each image');
    ap.add_argument('--strict-no-smc', action='store_true',
                    help='fail the run if any image trips the SMC audit');
    ap.add_argument('--exclude', nargs='*', default=[],
                    help='substrings of paths to skip');
    ap.add_argument('--timeout', type=int, default=120);
    ap.add_argument('--force-include', nargs='*', default=[],
                    help='headers to -include into every unit. TheAlgorithms '
                         'corpus has files that use INT_MIN or strlen without '
                         'including limits.h/string.h; this rescues them '
                         'without editing the sources');
    # action='append' + shlex, because nargs='*' cannot accept a value that
    # starts with '-': argparse read --extra-cflags -fno-sanitize=undefined as
    # an unknown option. Use --extra-cflags="-a -b", repeatable.
    ap.add_argument('--extra-cflags', action='append', default=[],
                    help='extra compile flags; use the = form for values '
                         'starting with a dash, e.g. --extra-cflags="-O3 -mavx2"');
    ap.add_argument('--extra-ldflags', action='append', default=[],
                    help='extra link flags; same = form as --extra-cflags');
    args = ap.parse_args();
    if args.cc is None:
        args.cc = default_cc();

    # Source is directory?
    if not args.sources.is_dir():
        print(f'{args.sources}: not a folder', file=sys.stderr);
        return 2;

    out_root = args.out if args.out is not None else args.sources;
    if args.clean:
        removed = clean(out_root, args.opt);
        print(f'removed {removed} generated file(s) under {out_root}');
        return 0;

    cc_argv0 = (shlex.split(args.cc, posix=(os.name != 'nt')) or [''])[0];
    if shutil.which(cc_argv0) is None:
        found = [c for c in CC_CANDIDATES if shutil.which(c)];
        hint = (f'available: {", ".join(found)} -- try --cc {found[0]}'
                if found else 'no C compiler found on PATH at all');
        print(f'{cc_argv0}: not on PATH ({hint})', file=sys.stderr);
        return 2;

    args.extra_cflags = [f for chunk in args.extra_cflags
                         for f in shlex.split(chunk)];
    args.extra_ldflags = [f for chunk in args.extra_ldflags
                          for f in shlex.split(chunk)];
    forced = [f for h in args.force_include for f in ('-include', h)];
    tc = Toolchain(args.cc, args.cf_protection, forced + args.extra_cflags,
                   args.extra_ldflags, args.static, args.strict_no_smc,
                   args.target);
    tc._filter_links();
    sources = discover(args.sources, args.exclude);
    if not sources:
        print(f'no .c files found under {args.sources}', file=sys.stderr);
        if args.exclude:
            print(f'(--exclude {" ".join(args.exclude)} may have removed them)',
                  file=sys.stderr);
        return 2;

    # Fail fast on a toolchain that cannot build anything, instead of running
    # the whole matrix and leaving an output folder with nothing in it. This
    # runs before the no-main warning: when the run is about to abort anyway,
    # a warning about a subset of sources is just noise.
    baseline = tc.probe_baseline();
    if baseline is not None:
        print(f'toolchain check failed -- not building {len(sources)} sources '
              f'that would all fail the same way:', file=sys.stderr);
        print(baseline, file=sys.stderr);
        # Only blame the forced headers when it was the *compile* that broke.
        # On a link or output-format failure they are irrelevant, and pointing
        # at them sends you looking in the wrong place.
        if args.force_include and baseline.startswith('compile'):
            print(f'hint: --force-include {" ".join(args.force_include)} is part '
                  f'of every compile; check those headers resolve',
                  file=sys.stderr);
        if args.static and baseline.startswith('link'):
            print('hint: --static needs a static libc (glibc-static / '
                  'libc6-dev static libs)', file=sys.stderr);
        return 2;

    n_img = sum(1 for s in sources if not has_main(s)) if not tc.image_ok else 0;
    if n_img:
        print(f'warning: this linker cannot lay out translation units with no '
              f'main ({n_img} of {len(sources)} sources); they will be '
              f'reported as image-unsupported', file=sys.stderr);

    where = 'in place' if args.out is None else str(out_root);
    print(f'{tc.version}');
    if tc.dropped:
        print(f'dropped {len(tc.dropped)} unsupported flag(s): '
              f'{", ".join(tc.dropped)}');
    print(f'{len(sources)} sources x {len(args.opt)} opt levels '
          f'-> {where} ({args.jobs} jobs)');
    out_root.mkdir(parents=True, exist_ok=True);

    results: List[BuildResult] = [];
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures = [];
        labels = [];
        for opt in args.opt:
            for src in sources:
                futures.append(pool.submit(build_one, tc, args.sources, src, opt,
                                           out_root, args.scope, args.save_asm,
                                           args.timeout, not args.no_edges));
                labels.append((opt, src));
        done = 0;
        for fut, (opt, src) in zip(futures, labels):
            try:
                res = fut.result();
            except Exception as exc:                    # never lose the run
                res = BuildResult(name=rel_key(args.sources, src),
                                  source=str(src), opt=opt, kind='unknown',
                                  status='crashed',
                                  diagnostics=f'{type(exc).__name__}: {exc}');
            results.append(res);
            done += 1;
            if done % 50 == 0 or done == len(futures):
                print(f'  {done}/{len(futures)}', file=sys.stderr);

    ok = [r for r in results if r.status == 'ok'];
    smc_hits = [r for r in ok if r.smc != 'clean'];
    totals = {
        'sources': len(sources),
        'built': len(ok),
        'failed': len(results) - len(ok),
        'functions': sum(r.summary.get('functions', 0) for r in ok),
        'indirect_jumps': sum(r.summary.get('indirect_jumps', 0) for r in ok),
        'indirect_jumps_resolved': sum(r.summary.get('indirect_jumps_resolved', 0) for r in ok),
        'indirect_calls': sum(r.summary.get('indirect_calls', 0) for r in ok),
        'indirect_calls_resolved': sum(r.summary.get('indirect_calls_resolved', 0) for r in ok),
        'smc_suspect': len(smc_hits),
    };
    breakdown: Dict[str, int] = {};
    for r in ok:
        for key, n in (r.summary.get('resolution_breakdown') or {}).items():
            breakdown[key] = breakdown.get(key, 0) + n;
    totals['resolution_breakdown'] = dict(sorted(breakdown.items()));
    index = {
        'schema': 'luramas.corpus/1',
        'root': str(args.sources.resolve()),
        'out_root': str(out_root.resolve()),
        'toolchain': tc.describe(),
        'scope': args.scope,
        'opt_levels': args.opt,
        'totals': totals,
        'entries': [asdict(r) for r in results],
    };
    index_path = out_root / 'program_index.json';
    index_path.write_text(json.dumps(index, indent=2), encoding='utf-8');

    print(f"\nbuilt {totals['built']}/{len(results)}  "
          f"functions {totals['functions']}  "
          f"indirect jumps {totals['indirect_jumps_resolved']}/{totals['indirect_jumps']} resolved  "
          f"indirect calls {totals['indirect_calls_resolved']}/{totals['indirect_calls']} resolved");
    if smc_hits:
        print(f"SMC audit flagged {len(smc_hits)} image(s):");
        for r in smc_hits[:20]:
            print(f'  {r.opt}/{r.name}');
    print(f'index: {index_path}');

    failed = [r for r in results if r.status != 'ok'];
    if failed:
        by_status: Dict[str, int] = {};
        for r in failed:
            by_status[r.status] = by_status.get(r.status, 0) + 1;
        print('failures: ' + '  '.join(f'{k} {v}' for k, v in
                                      sorted(by_status.items())));
    if not ok:
        # The symptom this used to produce was an output folder with nothing in
        # it and a zero exit status. Say why, and fail.
        print(f'\nnothing was built -- {out_root} has no images.',
              file=sys.stderr);
        seen = set();
        for r in failed:
            line = first_error(r.diagnostics);
            if line in seen:
                continue;
            seen.add(line);
            print(f'  {r.status}: {r.name}\n    {line[:200]}', file=sys.stderr);
            if len(seen) >= 5:
                break;
        print(f'\nall {len(failed)} diagnostics are in {index_path}',
              file=sys.stderr);
        return 1;

    if args.strict_no_smc and smc_hits:
        return 1;
    return 0;


if __name__ == '__main__':
    sys.exit(main());
