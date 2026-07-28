#!/usr/bin/env python3
import argparse
import fnmatch
import os
import re
import shutil
import sys
from collections import defaultdict

INCLUDE_RE = re.compile(r'^(\s*#\s*include\s*)"([^"]+)"(.*)$');

DEFAULT_SOURCE_EXTS = {
    ".c", ".cc", ".cpp", ".cxx", ".c++",
    ".h", ".hh", ".hpp", ".hxx", ".h++",
    ".inl", ".ipp", ".tpp", ".m", ".mm",
};

DEFAULT_EXCLUDES = [
    ".git", ".hg", ".svn", "build", "out", "bin",
    "node_modules", ".vs", ".vscode", ".cache", "cmake-build*",
];


def norm(p):
    return p.replace(os.sep, "/");


def is_excluded(name, patterns):
    return any(fnmatch.fnmatch(name, pat) for pat in patterns);


def split_eol(line):
    """Return (content_without_line_ending, line_ending)."""
    for eol in ("\r\n", "\n", "\r"):
        if line.endswith(eol):
            return line[:-len(eol)], eol;
    return line, "";


def build_index(root, excludes):
    """Walk root. Return (norm_index, by_basename).
    norm_index  : list of (normalized_path, os_path) for every file
    by_basename : dict filename -> list of os_paths
    """
    norm_index = []
    by_basename = defaultdict(list)
    for dirpath, dirnames, filenames in os.walk(root):
        dirnames[:] = [d for d in dirnames if not is_excluded(d, excludes)]
        for fn in filenames:
            full = os.path.join(dirpath, fn)
            norm_index.append((norm(os.path.abspath(full)), full))
            by_basename[fn].append(full)
    return norm_index, by_basename


def resolve(target, src_dir, norm_index, by_basename):
    """Return (status, result).
    status  : 'ok' | 'ambiguous' | 'not_found'
    result  : os_path (ok) | list of os_paths (ambiguous) | None (not_found)
    """
    target = norm(target);
    basename = os.path.basename(target);

    # already resolves relative to the including file
    adjacent = os.path.normpath(os.path.join(src_dir, target));
    if os.path.isfile(adjacent):
        return "ok", adjacent;

    # sub-path (suffix) match
    suffix = "/" + target
    matches = sorted({op for np, op in norm_index
                      if np.endswith(suffix) or np == target});
    if len(matches) == 1:
        return "ok", matches[0];
    if len(matches) > 1:
        return "ambiguous", matches;

    # bare file name fallback, catches missing prefixes
    name_matches = sorted(set(by_basename.get(basename, [])))
    if len(name_matches) == 1:
        return "ok", name_matches[0];
    if len(name_matches) > 1:
        return "ambiguous", name_matches;

    return "not_found", None;

# Make header to relative path
def make_relative(header_os_path, source_os_path):
    src_dir = os.path.dirname(os.path.abspath(source_os_path));
    rel = os.path.relpath(os.path.abspath(header_os_path), src_dir);
    return norm(rel);

# Warn with path line number and msg 
def warn(path, line_no, msg):
    print(f"WARNING {norm(path)}:{line_no}: {msg}", file=sys.stderr);


def process_file(path, norm_index, by_basename, apply_changes, backup, stats,
                 verbose):
    try:
        with open(path, "r", encoding="utf-8", errors="surrogateescape") as f:
            text = f.read();
    except OSError as e:
        print(f"! could not read {norm(path)}: {e}", file=sys.stderr);
        return;

    src_dir = os.path.dirname(os.path.abspath(path));
    out_lines = [];
    file_changed = False;

    for i, raw in enumerate(text.splitlines(keepends=True), start=1):
        content, eol = split_eol(raw);
        m = INCLUDE_RE.match(content);
        if not m:
            out_lines.append(raw);
            continue;

        prefix, target, rest = m.group(1), m.group(2), m.group(3);
        status, result = resolve(target, src_dir, norm_index, by_basename);

        if status == "not_found":
            warn(path, i, f'could not find "{target}" -- left unchanged');
            stats["not_found"] += 1;
            out_lines.append(raw);
            continue;

        if status == "ambiguous":
            warn(path, i,
                 f'duplicate header name "{os.path.basename(target)}" for '
                 f'include "{target}" ({len(result)} matches) -- left unchanged');
            for c in result:
                print(f"          candidate: {norm(c)}", file=sys.stderr);
            stats["ambiguous"] += 1;
            out_lines.append(raw);
            continue;

        rel = make_relative(result, path);
        if rel == norm(target):
            stats["already_ok"] += 1;
            if verbose:
                print(f'  {norm(path)}:{i}: "{target}" already correct');
            out_lines.append(raw);
            continue;

        out_lines.append(f'{prefix}"{rel}"{rest}{eol}');
        file_changed = True;
        stats["rewritten"] += 1;
        print(f'  {norm(path)}:{i}: "{target}" -> "{rel}"');

    if file_changed and apply_changes:
        if backup:
            shutil.copy2(path, path + ".bak");
        with open(path, "w", encoding="utf-8", errors="surrogateescape",
                  newline="") as f:
            f.write("".join(out_lines));
        stats["files_written"] += 1;


def gather_source_files(src_roots, exts, excludes):
    seen = set();
    files = [];
    for root in src_roots:
        if os.path.isfile(root):
            rp = os.path.realpath(root);
            if rp not in seen:
                seen.add(rp);
                files.append(root);
            continue;
        for dirpath, dirnames, filenames in os.walk(root):
            dirnames[:] = [d for d in dirnames if not is_excluded(d, excludes)];
            for fn in filenames:
                if os.path.splitext(fn)[1].lower() in exts:
                    full = os.path.join(dirpath, fn);
                    rp = os.path.realpath(full);
                    if rp not in seen:
                        seen.add(rp);
                        files.append(full);
    return files;


def main(argv=None):
    
    ap = argparse.ArgumentParser(
        description="Rewrite quoted #include \"...\" directives to relative paths.");
    ap.add_argument("root", nargs="?", default=".",
                    help="project root to index for headers (default: .)");
    ap.add_argument("--src", action="append", default=None,
                    help="dir/file to scan & rewrite (repeatable; default: root)");
    ap.add_argument("--apply", action="store_true",
                    help="actually modify files (default: dry run)");
    ap.add_argument("--backup", action="store_true",
                    help="write a .bak copy before modifying a file");
    ap.add_argument("--ext", default=None,
                    help="comma list of extensions to scan, e.g. .cpp,.h "
                         "(default: common C/C++ extensions)");
    ap.add_argument("--exclude", action="append", default=None,
                    help="directory name/glob to skip (repeatable)");
    ap.add_argument("--verbose", action="store_true",
                    help="also report includes that are already correct");
    args = ap.parse_args(argv);

    excludes = args.exclude if args.exclude is not None else DEFAULT_EXCLUDES;
    exts = ({e if e.startswith(".") else "." + e
             for e in (x.strip().lower() for x in args.ext.split(",")) if e}
            if args.ext else DEFAULT_SOURCE_EXTS);
    src_roots = args.src if args.src else [args.root];

    if not os.path.isdir(args.root):
        print(f"error: root '{args.root}' is not a directory", file=sys.stderr);
        return 2;

    print(f"Indexing headers under: {norm(os.path.abspath(args.root))}");
    norm_index, by_basename = build_index(args.root, excludes);
    print(f"Indexed {len(norm_index)} files.\n");

    source_files = gather_source_files(src_roots, exts, excludes);
    mode = "APPLY" if args.apply else "DRY RUN (no files written; use --apply)";
    print(f"Scanning {len(source_files)} source file(s)  [{mode}]\n");

    stats = defaultdict(int);
    for path in source_files:
        process_file(path, norm_index, by_basename, args.apply, args.backup,
                     stats, args.verbose);

    print("\nSummary:");
    print(f"  rewritten              : {stats['rewritten']}");
    print(f"  already correct        : {stats['already_ok']}");
    print(f"  not found (warned)     : {stats['not_found']}");
    print(f"  duplicates (warned)    : {stats['ambiguous']}");
    if args.apply:
        print(f"  files written          : {stats['files_written']}");
    else:
        print("  (dry run -- nothing was written; re-run with --apply)");
    return 0;


if __name__ == "__main__":
    sys.exit(main());
