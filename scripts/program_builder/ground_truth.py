#!/usr/bin/env python3
import argparse
import json
import re
import sys
from dataclasses import dataclass, field, asdict
from pathlib import Path
from typing import Dict, List, Optional, Set, Tuple

from capstone import (
    Cs, CS_ARCH_X86, CS_MODE_64, CS_OP_IMM, CS_OP_MEM, CS_OP_REG,
);
from capstone.x86 import (
    X86_GRP_CALL, X86_GRP_JUMP, X86_GRP_RET, X86_OP_IMM, X86_OP_MEM,
    X86_OP_REG, X86_REG_RIP,
);
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection
from elftools.elf.relocation import RelocationSection

# ---------------------------------------------------------------------------
# constants
# ---------------------------------------------------------------------------

SHF_WRITE = 0x1;
SHF_ALLOC = 0x2;
SHF_EXECINSTR = 0x4;

PF_X = 0x1;
PF_W = 0x2;

# Relocation types whose value is an absolute address (what a jump table or a
# function-pointer array is built out of on x86-64).
ABS_RELOCS = {
    1: 8,    # R_X86_64_64
    10: 4,   # R_X86_64_32
    11: 4,   # R_X86_64_32S
};

# Imports that let a process create or rewrite executable memory at run time.
# Their mere presence does not prove self-modifying code, but a corpus entry
# that pulls them in cannot be certified free of it by static means.
SMC_IMPORTS = {
    'mprotect', 'pkey_mprotect', 'mmap', 'mmap64', 'memfd_create',
    'shmat', 'dlopen', 'dlsym', '__clear_cache', '__builtin___clear_cache',
    'VirtualProtect', 'VirtualAlloc', 'WriteProcessMemory', 'FlushInstructionCache',
};

# How far back a slice will walk to find the base of an indirect branch.
SLICE_WINDOW = 40;

# Assembler labels that exist only for the debug info, not for code.
# `.LBB2` is a GCC lexical block, `.LBB0_2` is a clang basic block: keep the
# second one, it is a real branch target.
DEBUG_LABEL_RE = re.compile(r'^\.L(VL\d|VU\d|FB\d|FE\d|B[BE]\d+$|text|etext|debug|line|data\d)');


SUB_REGS = {
    'eax': 'rax', 'ax': 'rax', 'al': 'rax', 'ah': 'rax',
    'ebx': 'rbx', 'bx': 'rbx', 'bl': 'rbx', 'bh': 'rbx',
    'ecx': 'rcx', 'cx': 'rcx', 'cl': 'rcx', 'ch': 'rcx',
    'edx': 'rdx', 'dx': 'rdx', 'dl': 'rdx', 'dh': 'rdx',
    'esi': 'rsi', 'si': 'rsi', 'sil': 'rsi',
    'edi': 'rdi', 'di': 'rdi', 'dil': 'rdi',
    'ebp': 'rbp', 'bp': 'rbp', 'bpl': 'rbp',
    'esp': 'rsp', 'sp': 'rsp', 'spl': 'rsp',
};


# System V AMD64 integer argument registers, in order.
ARG_REGS = ('rdi', 'rsi', 'rdx', 'rcx', 'r8', 'r9');
CALLEE_SAVED = ('rbx', 'rbp', 'r12', 'r13', 'r14', 'r15');


def canon_reg(name: str) -> str:
    """`r8d`/`eax` and `r8`/`rax` are the same storage as far as a value
    trace is concerned."""
    if not name:
        return '';
    if name in SUB_REGS:
        return SUB_REGS[name];
    if re.fullmatch(r'r\d+[dwb]', name):
        return name[:-1];
    return name;


def clean_symbol(name: str) -> str:
    """`__printf_chk@GLIBC_2.3.4` -> `__printf_chk`."""
    return name.split('@', 1)[0] if name else name;


# ---------------------------------------------------------------------------
# schema
# ---------------------------------------------------------------------------

@dataclass
class SectionInfo:
    name: str;
    va: int;
    size: int;
    file_offset: int;
    exec: bool;
    write: bool;
    alloc: bool;


@dataclass
class TableEntry:
    index: int;
    va: int;
    label: Optional[str] = None;
    in_function: Optional[str] = None;
    valid_instruction_boundary: bool = False;


@dataclass
class JumpTable:
    va: int;
    entry_size: int;
    entry_kind: str;              # 'absolute' | 'relative_to_table'
    count: int;
    bound_from_compare: Optional[int] = None;
    count_from_relocs: Optional[int] = None;


@dataclass
class BranchSite:
    va: int;
    mnemonic: str;
    text: str;
    in_function: Optional[str];
    kind: str;                    # 'call' | 'jump'
    mode: str;                    # 'direct' | 'indirect'
    resolution: str;              # reloc | table_scan | disasm | address_taken | unresolved
    complete: bool;
    targets: List[int] = field(default_factory=list);
    target_names: List[str] = field(default_factory=list);
    imported_symbol: Optional[str] = None;
    next_va: int = 0;
    conditional: bool = False;
    table: Optional[JumpTable] = None;
    entries: List[TableEntry] = field(default_factory=list);
    note: Optional[str] = None;


@dataclass
class Edge:
    """One control transfer. Every instruction that can move rip appears here,
    including the intra-procedural branches that make up a function's CFG."""
    va: int;
    va_hex: str;
    in_function: Optional[str];
    text: str;
    kind: str;                    # jump | conditional_jump | call | indirect_jump
                                  # | indirect_call | return
    conditional: bool;
    resolution: str;
    complete: bool;
    targets: List[int] = field(default_factory=list);
    targets_hex: List[str] = field(default_factory=list);
    target_names: List[str] = field(default_factory=list);
    fallthrough: Optional[int] = None;
    fallthrough_hex: Optional[str] = None;


@dataclass
class FunctionInfo:
    name: str;
    va: int;
    size: int;
    section: Optional[str] = None;
    source_file: Optional[str] = None;
    source_line: Optional[int] = None;
    is_user_code: bool = False;
    address_taken: bool = False;
    address_taken_from: List[str] = field(default_factory=list);
    calls: List[str] = field(default_factory=list);
    called_by: List[str] = field(default_factory=list);
    tail_calls: List[str] = field(default_factory=list);
    indirect_call_sites: int = 0;
    indirect_jump_sites: int = 0;
    instruction_count: int = 0;
    edge_count: int = 0;


@dataclass
class SmcReport:
    verdict: str;                 # 'clean' | 'suspect'
    writable_executable_sections: List[str] = field(default_factory=list);
    writable_executable_segments: List[int] = field(default_factory=list);
    executable_stack: bool = False;
    text_relocations: bool = False;
    lazy_binding: bool = False;
    runtime_codegen_imports: List[str] = field(default_factory=list);
    writes_into_executable_sections: List[int] = field(default_factory=list);
    reasons: List[str] = field(default_factory=list);


# ---------------------------------------------------------------------------
# image
# ---------------------------------------------------------------------------

class Image:
    """A parsed, linked ELF64 x86-64 image."""

    def __init__(self, path: Path, user_sources: Optional[Set[str]] = None):
        self.path = path;
        self.user_sources = user_sources or set();
        self.fh = path.open('rb');
        self.elf = ELFFile(self.fh);

        if self.elf.get_machine_arch() != 'x64':
            raise ValueError(f"{path}: not x86-64 ({self.elf.get_machine_arch()})");

        self.sections: List[SectionInfo] = [];
        self._raw: Dict[str, bytes] = {};
        self.symbols: Dict[int, str] = {};        # va -> best name
        self.func_syms: Dict[int, Tuple[str, int]] = {};   # va -> (name, size)
        self.labels: Dict[int, str] = {};         # va -> local .L label
        self.relocs: Dict[int, dict] = {};        # va -> reloc record
        self.plt_map: Dict[int, str] = {};        # plt stub va -> import name
        self.imports: Set[str] = set();
        self.dwarf_funcs: Dict[int, Tuple[str, str, int]] = {};
        self.addr_lines: Dict[int, Tuple[str, int]] = {};
        self.cu_ranges: List[Tuple[int, int]] = [];

        self.md = Cs(CS_ARCH_X86, CS_MODE_64);
        self.md.detail = True;

        self._load_sections();
        self._load_symbols();
        self._load_relocs();
        self._load_plt();
        self._load_dwarf();

    def close(self) -> None:
        self.fh.close();

    # -- loading ------------------------------------------------------------

    def _load_sections(self) -> None:
        for sec in self.elf.iter_sections():
            flags = sec['sh_flags'];
            info = SectionInfo(
                name=sec.name,
                va=sec['sh_addr'],
                size=sec['sh_size'],
                file_offset=sec['sh_offset'],
                exec=bool(flags & SHF_EXECINSTR),
                write=bool(flags & SHF_WRITE),
                alloc=bool(flags & SHF_ALLOC),
            );
            self.sections.append(info);
            if sec['sh_type'] != 'SHT_NOBITS':
                self._raw[sec.name] = sec.data();

    def _load_symbols(self) -> None:
        for sec in self.elf.iter_sections():
            if not isinstance(sec, SymbolTableSection):
                continue;
            for sym in sec.iter_symbols():
                name = sym.name;
                if not name:
                    continue;
                va = sym['st_value'];
                info = sym['st_info'];
                if info['type'] == 'STT_FUNC' and va:
                    prev = self.func_syms.get(va);
                    if prev is None or (not prev[1] and sym['st_size']):
                        self.func_syms[va] = (name, sym['st_size']);
                    self.symbols[va] = name;
                elif name.startswith('.L'):
                    # .LVL/.Ltext/.LFB/.LFE are debug bookkeeping, not code labels.
                    if not DEBUG_LABEL_RE.match(name):
                        self.labels.setdefault(va, name);
                elif va:
                    self.symbols.setdefault(va, name);
                if sym['st_shndx'] == 'SHN_UNDEF':
                    self.imports.add(name);

    def _load_relocs(self) -> None:
        for sec in self.elf.iter_sections():
            if not isinstance(sec, RelocationSection):
                continue;
            symtab = None;
            if sec['sh_link']:
                try:
                    symtab = self.elf.get_section(sec['sh_link']);
                except Exception:
                    symtab = None;
            for reloc in sec.iter_relocations():
                r_type = reloc['r_info_type'];
                sym_name = '';
                sym_value = 0;
                if symtab is not None and isinstance(symtab, SymbolTableSection):
                    idx = reloc['r_info_sym'];
                    if idx < symtab.num_symbols():
                        sym = symtab.get_symbol(idx);
                        sym_name = sym.name;
                        sym_value = sym['st_value'];
                addend = reloc['r_addend'] if reloc.is_RELA() else 0;
                rec = {
                    'type': r_type,
                    'symbol': sym_name,
                    'symbol_value': sym_value,
                    'addend': addend,
                    'section': sec.name,
                    'target': None,
                    'width': ABS_RELOCS.get(r_type),
                };
                if r_type in ABS_RELOCS:
                    rec['target'] = sym_value + addend;
                self.relocs[reloc['r_offset']] = rec;

    def _load_plt(self) -> None:
        """Map PLT stub addresses to the import they forward to."""
        plt_secs = [s for s in self.sections if s.name.startswith('.plt') and s.size];
        if not plt_secs:
            return;
        # .rela.plt slot N -> stub N. Resolve by disassembling each stub and
        # following its GOT slot back to the jump-slot relocation.
        got_to_name: Dict[int, str] = {};
        for va, rec in self.relocs.items():
            if rec['section'] in ('.rela.plt', '.rel.plt') and rec['symbol']:
                got_to_name[va] = rec['symbol'];
        for sec in plt_secs:
            data = self._raw.get(sec.name, b'');
            for insn in self.md.disasm(data, sec.va):
                if insn.mnemonic not in ('jmp', 'bnd jmp'):
                    continue;
                for op in insn.operands:
                    if op.type == X86_OP_MEM and op.mem.base == X86_REG_RIP:
                        slot = insn.address + insn.size + op.mem.disp;
                        name = got_to_name.get(slot);
                        if name:
                            stub = insn.address & ~0xF;
                            self.plt_map[stub] = name;
                            self.plt_map[insn.address] = name;

    def _load_dwarf(self) -> None:
        if not self.elf.has_dwarf_info():
            return;
        try:
            # `--emit-relocs` leaves .rela.debug_* behind in a *linked* image.
            # pyelftools would try to apply them a second time and walk off the
            # end of the section, so the relocation pass is turned off here.
            dw = self.elf.get_dwarf_info(relocate_dwarf_sections=False);
        except Exception:
            return;
        for cu in dw.iter_CUs():
            try:
                top = cu.get_top_DIE();
                cu_name = top.attributes.get('DW_AT_name');
                cu_name = cu_name.value.decode('utf-8', 'replace') if cu_name else '';
                line_prog = dw.line_program_for_CU(cu);
                files = line_prog.header.file_entry if line_prog else [];

                # The line program is the reliable "is this my code" oracle:
                # it still covers functions the compiler split into hot/cold
                # fragments, which carry DW_AT_ranges instead of DW_AT_low_pc.
                if line_prog is not None:
                    seq_start = None;
                    for entry in line_prog.get_entries():
                        st = entry.state;
                        if st is None:
                            continue;
                        if st.end_sequence:
                            if seq_start is not None:
                                # Half-open: the end address belongs to whatever
                                # comes next (usually a CRT stub), not to this CU.
                                self.cu_ranges.append((seq_start, st.address));
                            seq_start = None;
                            continue;
                        if seq_start is None:
                            seq_start = st.address;
                        src = cu_name;
                        if files and 0 <= st.file < len(files):
                            src = files[st.file].name.decode('utf-8', 'replace');
                        self.addr_lines.setdefault(st.address, (src, st.line));

                for die in cu.iter_DIEs():
                    if die.tag != 'DW_TAG_subprogram':
                        continue;
                    attrs = die.attributes;
                    if 'DW_AT_low_pc' not in attrs:
                        continue;
                    low = attrs['DW_AT_low_pc'].value;
                    name_a = attrs.get('DW_AT_name');
                    name = name_a.value.decode('utf-8', 'replace') if name_a else f'sub_{low:x}';
                    line = attrs['DW_AT_decl_line'].value if 'DW_AT_decl_line' in attrs else 0;
                    src = cu_name;
                    if 'DW_AT_decl_file' in attrs and files:
                        fi = attrs['DW_AT_decl_file'].value;
                        if 0 <= fi < len(files):
                            src = files[fi].name.decode('utf-8', 'replace');
                    self.dwarf_funcs[low] = (name, src, line);
            except Exception:
                continue;

    # -- primitives ---------------------------------------------------------

    def in_cu_range(self, va: int) -> bool:
        """True when `va` falls inside code emitted from a corpus source file."""
        return any(lo <= va < hi for lo, hi in self.cu_ranges);

    def section_of(self, va: int) -> Optional[SectionInfo]:
        for sec in self.sections:
            if sec.alloc and sec.va <= va < sec.va + sec.size:
                return sec;
        return None;

    def read_va(self, va: int, size: int) -> Optional[bytes]:
        sec = self.section_of(va);
        if sec is None:
            return None;
        data = self._raw.get(sec.name);
        if data is None:
            return None;
        off = va - sec.va;
        if off + size > len(data):
            return None;
        return data[off:off + size];

    def read_int(self, va: int, size: int, signed: bool = False) -> Optional[int]:
        raw = self.read_va(va, size);
        if raw is None:
            return None;
        return int.from_bytes(raw, 'little', signed=signed);

    def is_executable(self, va: int) -> bool:
        sec = self.section_of(va);
        return bool(sec and sec.exec);

    def name_for(self, va: int) -> str:
        if va in self.func_syms:
            return clean_symbol(self.func_syms[va][0]);
        if va in self.plt_map:
            return f'{clean_symbol(self.plt_map[va])}@plt';
        if va in self.labels:
            return self.labels[va];
        if va in self.symbols:
            return clean_symbol(self.symbols[va]);
        return f'loc_{va:x}';


# ---------------------------------------------------------------------------
# analysis
# ---------------------------------------------------------------------------

class Analyzer:

    def __init__(self, img: Image, scope: str = 'user'):
        self.img = img;
        self.scope = scope;
        self.functions: Dict[int, FunctionInfo] = {};
        self.branches: List[BranchSite] = [];
        self.local_edges: List[Edge] = [];
        self.address_taken: Dict[int, List[str]] = {};
        self.field_stores: Dict[int, Set[int]] = {};
        self.func_starts: List[int] = [];
        self._insns: Dict[int, list] = {};        # func va -> [insn]
        self._boundaries: Set[int] = set();

    # -- functions ----------------------------------------------------------

    def build_functions(self) -> None:
        img = self.img;
        for va, (name, size) in sorted(img.func_syms.items()):
            sec = img.section_of(va);
            if sec is None or not sec.exec:
                continue;
            fn = FunctionInfo(name=name, va=va, size=size, section=sec.name);
            if va in img.dwarf_funcs:
                _dname, src, line = img.dwarf_funcs[va];
                fn.source_file = src;
                fn.source_line = line or None;
                fn.is_user_code = True;
            if img.in_cu_range(va):
                fn.is_user_code = True;
                if va in img.addr_lines:
                    src, line = img.addr_lines[va];
                    fn.source_file = fn.source_file or src;
                    fn.source_line = fn.source_line or line;
            self.functions[va] = fn;

        # Symbol sizes are sometimes 0 (hand-written asm in the CRT). Fill the
        # gap up to the next function start so disassembly stays bounded.
        starts = sorted(self.functions);
        for i, va in enumerate(starts):
            fn = self.functions[va];
            if fn.size:
                continue;
            sec = self.img.section_of(va);
            end = starts[i + 1] if i + 1 < len(starts) else (sec.va + sec.size if sec else va);
            fn.size = max(0, end - va);
        self.func_starts = starts;

    def in_scope(self, fn: FunctionInfo) -> bool:
        if self.scope == 'all':
            return True;
        return fn.is_user_code;

    def function_at(self, va: int) -> Optional[FunctionInfo]:
        lo, hi = 0, len(self.func_starts) - 1;
        best = None;
        while lo <= hi:
            mid = (lo + hi) // 2;
            start = self.func_starts[mid];
            if start <= va:
                best = start;
                lo = mid + 1;
            else:
                hi = mid - 1;
        if best is None:
            return None;
        fn = self.functions[best];
        if va < fn.va + max(fn.size, 1):
            return fn;
        return None;

    # -- disassembly --------------------------------------------------------

    def disassemble(self) -> None:
        img = self.img;
        for va, fn in self.functions.items():
            if not self.in_scope(fn) or fn.size <= 0:
                continue;
            data = img.read_va(va, fn.size);
            if not data:
                continue;
            insns = list(img.md.disasm(data, va));
            self._insns[va] = insns;
            fn.instruction_count = len(insns);
            for insn in insns:
                self._boundaries.add(insn.address);

    # -- address-taken set --------------------------------------------------

    def collect_address_taken(self) -> None:
        """A function is address-taken if a data relocation or a non-branch
        instruction materialises its entry address.

        The same pass records where function pointers are *stored*, which is
        what makes `call [obj+0x20]` resolvable later:

          phase A  per function, trace registers holding either a known
                   function address or an incoming argument, and note every
                   store of one into a struct field
          phase B  a field fed by an incoming argument is resolved by looking
                   at what each direct caller actually passed in that slot
        """
        img = self.img;
        for off, rec in img.relocs.items():
            tgt = rec['target'];
            if tgt is None or tgt not in self.functions:
                continue;
            sec = rec['section'];
            if sec.startswith('.rela.debug') or sec.startswith('.rela.eh'):
                continue;
            holder = img.section_of(off);
            where = f"{holder.name if holder else sec}+0x{off:x}";
            self.address_taken.setdefault(tgt, []).append(where);

        param_stores: Dict[Tuple[int, int], Set[int]] = {};   # (callee, arg) -> disps
        call_args: Dict[Tuple[int, int], Set[int]] = {};      # (callee, arg) -> funcs

        for fva, insns in self._insns.items():
            # System V argument registers, seeded so a callback that arrives as
            # a parameter can still be followed to the field it lands in.
            regvals: Dict[str, object] = {
                reg: ('arg', i) for i, reg in enumerate(ARG_REGS)
            };
            for insn in insns:
                ops = insn.operands;

                if insn.group(X86_GRP_CALL) and ops and ops[0].type == X86_OP_IMM:
                    callee = ops[0].imm;
                    for i, reg in enumerate(ARG_REGS):
                        val = regvals.get(reg);
                        if isinstance(val, int) and val in self.functions:
                            call_args.setdefault((callee, i), set()).add(val);
                    regvals = {k: v for k, v in regvals.items()
                               if k in CALLEE_SAVED};
                    continue;

                if insn.mnemonic in ('mov', 'movabs', 'lea') and len(ops) == 2 \
                        and ops[0].type == X86_OP_REG:
                    dst = canon_reg(insn.reg_name(ops[0].reg));
                    src = ops[1];
                    value = None;
                    if src.type == X86_OP_IMM:
                        value = src.imm;
                    elif src.type == X86_OP_REG:
                        value = regvals.get(canon_reg(insn.reg_name(src.reg)));
                    elif src.type == X86_OP_MEM and src.mem.base == X86_REG_RIP \
                            and not src.mem.index and insn.mnemonic == 'lea':
                        value = insn.address + insn.size + src.mem.disp;
                    if isinstance(value, tuple) or value in self.functions:
                        regvals[dst] = value;
                    else:
                        regvals.pop(dst, None);
                elif ops and ops[0].type == X86_OP_REG:
                    regvals.pop(canon_reg(insn.reg_name(ops[0].reg)), None);

                # `mov [obj+0x20], fn` - a callback installed in a struct field.
                if insn.mnemonic.startswith('mov') and len(ops) == 2 \
                        and ops[0].type == X86_OP_MEM:
                    m = ops[0].mem;
                    base_name = canon_reg(insn.reg_name(m.base)) if m.base else '';
                    if m.base and base_name not in ('rsp', 'rbp', 'rip'):
                        value = None;
                        if ops[1].type == X86_OP_REG:
                            value = regvals.get(canon_reg(insn.reg_name(ops[1].reg)));
                        elif ops[1].type == X86_OP_IMM and ops[1].imm in self.functions:
                            value = ops[1].imm;
                        if isinstance(value, tuple) and value[0] == 'arg':
                            param_stores.setdefault((fva, value[1]), set()).add(m.disp);
                        elif isinstance(value, int) and value in self.functions:
                            self.field_stores.setdefault(m.disp, set()).add(value);

                if insn.group(X86_GRP_CALL) or insn.group(X86_GRP_JUMP):
                    continue;
                if insn.mnemonic not in ('lea', 'mov', 'movabs', 'push'):
                    continue;
                for op in ops:
                    tgt = None;
                    if op.type == X86_OP_MEM and op.mem.base == X86_REG_RIP and not op.mem.index:
                        tgt = insn.address + insn.size + op.mem.disp;
                    elif op.type == X86_OP_IMM:
                        tgt = op.imm;
                    if tgt in self.functions and tgt != fva:
                        self.address_taken.setdefault(tgt, []).append(
                            f"{self.img.name_for(fva)}+0x{insn.address - fva:x}");

        for (callee, arg_idx), disps in param_stores.items():
            passed = call_args.get((callee, arg_idx));
            if not passed:
                continue;
            for disp in disps:
                self.field_stores.setdefault(disp, set()).update(passed);

        for va, sites in self.address_taken.items():
            fn = self.functions[va];
            fn.address_taken = True;
            fn.address_taken_from = sorted(set(sites))[:16];

    # -- backward slice -----------------------------------------------------

    def _slice_back(self, insns: list, idx: int, reg: int) -> dict:
        """Walk backwards looking for the value that reached `reg`.

        Recognises the two shapes a compiler emits for a switch:
          absolute:  lea  base,[rip+TABLE] ; mov  reg,[base+idx*8]      ; jmp reg
          relative:  lea  base,[rip+TABLE] ; movsxd r,[base+idx*4] ; add r,base ; jmp reg
        """
        want = {reg};
        table_va = None;
        entry_size = 8;
        kind = 'absolute';
        rel_base = None;

        for insn in reversed(insns[max(0, idx - SLICE_WINDOW):idx]):
            ops = insn.operands;
            if not ops:
                continue;
            dst = ops[0];
            if dst.type != X86_OP_REG or dst.reg not in want:
                continue;
            mn = insn.mnemonic;

            if mn == 'add' and len(ops) == 2 and ops[1].type == X86_OP_REG:
                # target = table_base + delta: follow both halves, but only if
                # the table access itself has not been identified yet.
                if table_va is None:
                    want.add(ops[1].reg);
                    kind = 'relative_to_table';
                continue;

            if mn in ('mov', 'movsxd', 'movsx', 'movslq') and len(ops) == 2:
                src = ops[1];
                if src.type == X86_OP_MEM:
                    m = src.mem;
                    if m.base == X86_REG_RIP:
                        table_va = insn.address + insn.size + m.disp;
                        break;
                    if m.index:
                        # This is the table load itself; everything earlier is
                        # index computation, not the base.
                        entry_size = m.scale or entry_size;
                        if mn in ('movsxd', 'movsx', 'movslq'):
                            entry_size = 4;
                            kind = 'relative_to_table';
                        if m.disp:
                            table_va = m.disp;
                            break;
                        if m.base:
                            want.add(m.base);
                            rel_base = m.base;
                    continue;
                if src.type == X86_OP_REG:
                    want.add(src.reg);
                    continue;
                if src.type == X86_OP_IMM:
                    table_va = table_va or src.imm;
                    continue;

            if mn == 'lea' and len(ops) == 2 and ops[1].type == X86_OP_MEM:
                m = ops[1].mem;
                if m.base == X86_REG_RIP:
                    table_va = insn.address + insn.size + m.disp;
                    break;

        return {
            'table_va': table_va,
            'entry_size': entry_size,
            'kind': kind,
            'has_base_reg': rel_base is not None,
        };

    def _bound_from_compare(self, insns: list, idx: int) -> Optional[int]:
        """`cmp reg, N ; ja default` gives the exact entry count (N+1)."""
        last_cmp = None;
        for insn in insns[max(0, idx - SLICE_WINDOW):idx]:
            if insn.mnemonic in ('cmp', 'sub') and len(insn.operands) == 2 \
                    and insn.operands[1].type == X86_OP_IMM:
                last_cmp = insn.operands[1].imm;
            elif insn.mnemonic in ('ja', 'jae', 'jnbe', 'jg', 'jge') and last_cmp is not None:
                return last_cmp + 1;
        return None;

    # -- table walking ------------------------------------------------------

    def _walk_table(self, table_va: int, entry_size: int, kind: str,
                    bound: Optional[int], enclosing: Optional[FunctionInfo]) -> Tuple[List[TableEntry], JumpTable, str, bool]:
        img = self.img;
        entries: List[TableEntry] = [];
        reloc_run = 0;

        if kind == 'absolute':
            probe = table_va;
            while probe in img.relocs and img.relocs[probe]['target'] is not None:
                reloc_run += 1;
                probe += entry_size;

        limit = bound if bound else 0;
        if reloc_run:
            limit = min(limit, reloc_run) if limit else reloc_run;
        if not limit:
            limit = 512;              # hard stop for the heuristic scan

        resolution = 'reloc' if reloc_run else 'table_scan';
        complete = bool(reloc_run) or bound is not None;

        for i in range(limit):
            slot = table_va + i * entry_size;
            target = None;
            if kind == 'absolute':
                rec = img.relocs.get(slot);
                if rec is not None and rec['target'] is not None:
                    target = rec['target'];
                else:
                    target = img.read_int(slot, entry_size);
            else:
                delta = img.read_int(slot, entry_size, signed=True);
                if delta is not None:
                    target = table_va + delta;

            if target is None:
                complete = False;
                break;
            if not img.is_executable(target):
                if i == 0:
                    return [], JumpTable(table_va, entry_size, kind, 0), 'unresolved', False;
                break;
            if enclosing is not None and not (enclosing.va <= target < enclosing.va + enclosing.size):
                # A table never leaves its own function in compiler output;
                # leaving it means the scan overran the end.
                if reloc_run == 0:
                    break;

            entries.append(TableEntry(
                index=i,
                va=target,
                label=img.name_for(target),
                in_function=(self.function_at(target).name if self.function_at(target) else None),
                valid_instruction_boundary=target in self._boundaries,
            ));

        table = JumpTable(
            va=table_va,
            entry_size=entry_size,
            entry_kind=kind,
            count=len(entries),
            bound_from_compare=bound,
            count_from_relocs=reloc_run or None,
        );
        return entries, table, resolution, complete;

    # -- control flow -------------------------------------------------------

    def analyse_control_flow(self) -> None:
        img = self.img;
        for fva, insns in self._insns.items():
            fn = self.functions[fva];
            for idx, insn in enumerate(insns):
                is_call = insn.group(X86_GRP_CALL);
                is_jump = insn.group(X86_GRP_JUMP);
                if insn.group(X86_GRP_RET):
                    self.local_edges.append(Edge(
                        va=insn.address, va_hex=f'0x{insn.address:x}',
                        in_function=fn.name,
                        text=f'{insn.mnemonic} {insn.op_str}'.strip(),
                        kind='return', conditional=False,
                        resolution='disasm', complete=True));
                    continue;
                if not (is_call or is_jump):
                    continue;
                kind = 'call' if is_call else 'jump';
                ops = insn.operands;
                if not ops:
                    continue;
                op = ops[0];
                conditional = bool(is_jump and insn.mnemonic not in ('jmp', 'bnd jmp'));
                next_va = insn.address + insn.size;

                # --- direct ------------------------------------------------
                if op.type == X86_OP_IMM:
                    target = op.imm;
                    if is_jump and fn.va <= target < fn.va + fn.size:
                        # Intra-procedural: not a call-graph edge, but it is
                        # still a control transfer the framework has to model.
                        self.local_edges.append(Edge(
                            va=insn.address, va_hex=f'0x{insn.address:x}',
                            in_function=fn.name,
                            text=f'{insn.mnemonic} {insn.op_str}',
                            kind='conditional_jump' if conditional else 'jump',
                            conditional=conditional,
                            resolution='disasm', complete=True,
                            targets=[target], targets_hex=[f'0x{target:x}'],
                            target_names=[img.name_for(target)],
                            fallthrough=next_va if conditional else None,
                            fallthrough_hex=f'0x{next_va:x}' if conditional else None));
                        continue;
                    site = BranchSite(
                        va=insn.address, mnemonic=insn.mnemonic,
                        text=f'{insn.mnemonic} {insn.op_str}',
                        in_function=fn.name, kind=kind, mode='direct',
                        next_va=next_va, conditional=conditional,
                        resolution='disasm', complete=True,
                        targets=[target], target_names=[img.name_for(target)],
                    );
                    rec = img.relocs.get(insn.address + (insn.size - 4));
                    if rec is not None and rec['symbol']:
                        site.resolution = 'reloc';
                        site.target_names = [clean_symbol(rec['symbol'])];
                    if target in img.plt_map:
                        site.imported_symbol = clean_symbol(img.plt_map[target]);
                        site.target_names = [site.imported_symbol];
                    self._record_edge(fn, site);
                    self.branches.append(site);
                    continue;

                # --- indirect ----------------------------------------------
                site = BranchSite(
                    va=insn.address, mnemonic=insn.mnemonic,
                    text=f'{insn.mnemonic} {insn.op_str}',
                    in_function=fn.name, kind=kind, mode='indirect',
                    next_va=next_va, conditional=conditional,
                    resolution='unresolved', complete=False,
                );
                if kind == 'call':
                    fn.indirect_call_sites += 1;
                else:
                    fn.indirect_jump_sites += 1;

                table_va = None;
                entry_size = 8;
                tkind = 'absolute';

                if op.type == X86_OP_MEM:
                    m = op.mem;
                    if m.base == X86_REG_RIP and not m.index:
                        slot = insn.address + insn.size + m.disp;
                        rec = img.relocs.get(slot);
                        if rec is not None and rec['symbol']:
                            site.resolution = 'reloc';
                            site.complete = True;
                            site.imported_symbol = clean_symbol(rec['symbol']);
                            site.target_names = [site.imported_symbol];
                            if rec['target']:
                                site.targets = [rec['target']];
                        else:
                            ptr = img.read_int(slot, 8);
                            if ptr and img.is_executable(ptr):
                                site.resolution = 'table_scan';
                                site.complete = True;
                                site.targets = [ptr];
                                site.target_names = [img.name_for(ptr)];
                            else:
                                site.note = f'pointer at 0x{slot:x} not statically known';
                        self._record_edge(fn, site);
                        self.branches.append(site);
                        continue;
                    if m.index:
                        entry_size = m.scale or 8;
                        table_va = m.disp;
                        if m.base:
                            hint = self._slice_back(insns, idx, m.base);
                            if hint['table_va'] is not None:
                                table_va = hint['table_va'] + (m.disp or 0);
                elif op.type == X86_OP_REG:
                    hint = self._slice_back(insns, idx, op.reg);
                    table_va = hint['table_va'];
                    entry_size = hint['entry_size'];
                    tkind = hint['kind'];
                    if table_va is not None and img.is_executable(table_va) \
                            and table_va not in img.relocs:
                        # lea of a code address straight into a register:
                        # a computed branch with exactly one target.
                        site.resolution = 'disasm';
                        site.complete = True;
                        site.targets = [table_va];
                        site.target_names = [img.name_for(table_va)];
                        self._record_edge(fn, site);
                        self.branches.append(site);
                        continue;

                if table_va is not None:
                    bound = self._bound_from_compare(insns, idx);
                    entries, table, resolution, complete = self._walk_table(
                        table_va, entry_size, tkind, bound, fn if kind == 'jump' else None);
                    if entries:
                        site.table = table;
                        site.entries = entries;
                        site.resolution = resolution;
                        site.complete = complete;
                        site.targets = [e.va for e in entries];
                        site.target_names = [e.label or img.name_for(e.va) for e in entries];
                        self._record_edge(fn, site);
                        self.branches.append(site);
                        continue;

                # `call [obj+0x20]`: a callback in a struct field. Not exact,
                # but far tighter than the whole address-taken set.
                if kind == 'call' and op.type == X86_OP_MEM and op.mem.base \
                        and not op.mem.index \
                        and self.field_stores.get(op.mem.disp):
                    cands = sorted(self.field_stores[op.mem.disp]);
                    site.resolution = 'field_store';
                    site.complete = False;
                    site.targets = cands;
                    site.target_names = [img.name_for(v) for v in cands];
                    site.note = (f'over-approximation: functions stored at '
                                 f'field +0x{op.mem.disp:x}');
                    self._record_edge(fn, site);
                    self.branches.append(site);
                    continue;

                # Nothing exact: fall back to the address-taken over-approximation
                # for calls, and be honest that jumps are unknown.
                if kind == 'call' and self.address_taken:
                    site.resolution = 'address_taken';
                    site.complete = False;
                    site.targets = sorted(self.address_taken);
                    site.target_names = [img.name_for(v) for v in site.targets];
                    site.note = 'over-approximation: every address-taken function';
                else:
                    site.note = 'no static base for the branch';
                self._record_edge(fn, site);
                self.branches.append(site);

    def _record_edge(self, fn: FunctionInfo, site: BranchSite) -> None:
        for target, name in zip(site.targets, site.target_names or site.targets):
            label = name if isinstance(name, str) else self.img.name_for(target);
            if site.kind == 'call':
                if label not in fn.calls:
                    fn.calls.append(label);
                callee = self.functions.get(target);
                if callee is not None and fn.name not in callee.called_by:
                    callee.called_by.append(fn.name);
            else:
                callee = self.functions.get(target);
                if callee is not None and callee.va != fn.va:
                    if label not in fn.tail_calls:
                        fn.tail_calls.append(label);
                    if fn.name not in callee.called_by:
                        callee.called_by.append(fn.name);
        if site.kind == 'call' and site.imported_symbol:
            if site.imported_symbol not in fn.calls:
                fn.calls.append(site.imported_symbol);

    # -- SMC ----------------------------------------------------------------

    def audit_smc(self) -> SmcReport:
        img = self.img;
        rep = SmcReport(verdict='clean');

        for sec in img.sections:
            if sec.exec and sec.write and sec.alloc:
                rep.writable_executable_sections.append(sec.name);
                rep.reasons.append(f'section {sec.name} is writable and executable');

        for i, seg in enumerate(img.elf.iter_segments()):
            flags = seg['p_flags'];
            if seg['p_type'] == 'PT_LOAD' and (flags & PF_W) and (flags & PF_X):
                rep.writable_executable_segments.append(i);
                rep.reasons.append(f'PT_LOAD segment {i} is RWX');
            if seg['p_type'] == 'PT_GNU_STACK' and (flags & PF_X):
                rep.executable_stack = True;
                rep.reasons.append('executable stack (PT_GNU_STACK is +X)');

        for seg in img.elf.iter_segments():
            if seg['p_type'] != 'PT_DYNAMIC':
                continue;
            try:
                tags = {t.entry.d_tag for t in seg.iter_tags()};
            except Exception:
                continue;
            if 'DT_TEXTREL' in tags:
                rep.text_relocations = True;
                rep.reasons.append('DT_TEXTREL: the loader patches .text at load time');
            if 'DT_BIND_NOW' not in tags and 'DT_FLAGS_1' not in tags:
                rep.lazy_binding = True;

        hits = sorted(img.imports & SMC_IMPORTS);
        if hits:
            rep.runtime_codegen_imports = hits;
            rep.reasons.append('imports that can create or rewrite code: ' + ', '.join(hits));

        for insns in self._insns.values():
            for insn in insns:
                if insn.mnemonic not in ('mov', 'movb', 'movw', 'movl', 'movq'):
                    continue;
                ops = insn.operands;
                if len(ops) != 2 or ops[0].type != X86_OP_MEM:
                    continue;
                m = ops[0].mem;
                if m.base == X86_REG_RIP and not m.index:
                    dst = insn.address + insn.size + m.disp;
                    if img.is_executable(dst):
                        rep.writes_into_executable_sections.append(insn.address);
                        rep.reasons.append(f'store into executable memory at 0x{insn.address:x}');

        if rep.writable_executable_sections or rep.writable_executable_segments \
                or rep.executable_stack or rep.text_relocations \
                or rep.writes_into_executable_sections or rep.runtime_codegen_imports:
            rep.verdict = 'suspect';
        return rep;

    # -- output -------------------------------------------------------------

    def run(self) -> None:
        self.build_functions();
        self.disassemble();
        self.collect_address_taken();
        self.analyse_control_flow();

    def to_dict(self, with_edges: bool = True) -> dict:
        img = self.img;
        smc = self.audit_smc();
        edges = self.build_edges();
        funcs = [asdict(fn) for va, fn in sorted(self.functions.items())
                 if self.in_scope(fn)];
        branches = [self._branch_dict(b) for b in sorted(self.branches, key=lambda b: b.va)];
        indirect_jumps = [b for b in branches if b['kind'] == 'jump' and b['mode'] == 'indirect'];
        indirect_calls = [b for b in branches if b['kind'] == 'call' and b['mode'] == 'indirect'];
        return {
            'schema': 'luramas.groundtruth/1',
            'image': str(img.path),
            'arch': 'x86_64',
            'format': 'elf64',
            'entry': img.elf.header['e_entry'],
            'type': str(img.elf.header['e_type']),
            'scope': self.scope,
            'sections': [asdict(s) for s in img.sections if s.alloc],
            'smc': asdict(smc),
            'summary': {
                'functions': len(funcs),
                'branch_sites': len(branches),
                'indirect_jumps': len(indirect_jumps),
                'indirect_jumps_resolved': sum(1 for b in indirect_jumps if b['complete']),
                'indirect_calls': len(indirect_calls),
                'indirect_calls_resolved': sum(1 for b in indirect_calls if b['complete']),
                'address_taken_functions': len(self.address_taken),
                'edges': len(edges),
                'edges_unresolved': sum(1 for e in edges if not e.complete),
                'resolution_breakdown': self._breakdown(branches),
            },
            'functions': funcs,
            'call_sites': [b for b in branches if b['kind'] == 'call'],
            'indirect_jumps': indirect_jumps,
            'edges': [asdict(e) for e in edges] if with_edges else [],
        };

    @staticmethod
    def _breakdown(branches: List[dict]) -> Dict[str, int]:
        """How each edge was recovered. `reloc`/`disasm`/`table_scan` are
        exact; `field_store` and `address_taken` are over-approximations."""
        out: Dict[str, int] = {};
        for b in branches:
            key = f"{b['mode']}_{b['kind']}_{b['resolution']}";
            out[key] = out.get(key, 0) + 1;
        return dict(sorted(out.items()));

    def build_edges(self) -> List[Edge]:
        """Every control transfer in scope, sorted by address: the flat form of
        `where does this instruction go`."""
        edges = list(self.local_edges);
        for b in self.branches:
            if b.mode == 'indirect':
                kind = 'indirect_call' if b.kind == 'call' else 'indirect_jump';
            elif b.kind == 'call':
                kind = 'call';
            else:
                kind = 'conditional_jump' if b.conditional else 'jump';
            fall = None;
            if b.conditional or b.kind == 'call':
                fall = b.next_va or None;
            edges.append(Edge(
                va=b.va, va_hex=f'0x{b.va:x}', in_function=b.in_function,
                text=b.text, kind=kind, conditional=b.conditional,
                resolution=b.resolution, complete=b.complete,
                targets=list(b.targets),
                targets_hex=[f'0x{t:x}' for t in b.targets],
                target_names=list(b.target_names),
                fallthrough=fall,
                fallthrough_hex=f'0x{fall:x}' if fall else None));
        edges.sort(key=lambda e: e.va);
        counts: Dict[Optional[str], int] = {};
        for e in edges:
            counts[e.in_function] = counts.get(e.in_function, 0) + 1;
        for fn in self.functions.values():
            fn.edge_count = counts.get(fn.name, 0);
        return edges;

    def _branch_dict(self, b: BranchSite) -> dict:
        d = asdict(b);
        d['va_hex'] = f'0x{b.va:x}';
        d['targets_hex'] = [f'0x{t:x}' for t in b.targets];
        return d;


# ---------------------------------------------------------------------------
# driver
# ---------------------------------------------------------------------------

def analyse_image(path: Path, scope: str = 'user', with_edges: bool = True) -> dict:
    img = Image(path);
    try:
        an = Analyzer(img, scope=scope);
        an.run();
        return an.to_dict(with_edges=with_edges);
    finally:
        img.close();


def is_elf(path: Path) -> bool:
    try:
        with path.open('rb') as fh:
            return fh.read(4) == b'\x7fELF';
    except OSError:
        return False;


def main() -> int:
    ap = argparse.ArgumentParser(
        description='Extract decompiler ground truth (call graph, indirect '
                    'branch targets, SMC audit) from x86-64 ELF images.');
    ap.add_argument('target', type=Path,
                    help='ELF image, or a folder to walk');
    ap.add_argument('-o', '--out', type=Path,
                    help='output folder for <name>.meta.json (default: print to stdout)');
    ap.add_argument('--scope', choices=('user', 'all'), default='user',
                    help='user = functions with DWARF from the corpus source; '
                         'all = every function in the image, CRT included');
    ap.add_argument('--strict-no-smc', action='store_true',
                    help='exit non-zero if any image fails the SMC audit');
    ap.add_argument('--no-edges', action='store_true',
                    help='omit the per-instruction edge list (smaller output)');
    ap.add_argument('--indent', type=int, default=2);
    args = ap.parse_args();

    if args.target.is_dir():
        images = sorted(p for p in args.target.rglob('*') if p.is_file() and is_elf(p));
    else:
        images = [args.target];
    if not images:
        print('no ELF images found', file=sys.stderr);
        return 1;

    if args.out:
        args.out.mkdir(parents=True, exist_ok=True);

    failures = 0;
    for path in images:
        try:
            meta = analyse_image(path, scope=args.scope,
                                 with_edges=not args.no_edges);
        except Exception as exc:
            print(f'{path}: {exc}', file=sys.stderr);
            failures += 1;
            continue;
        if meta['smc']['verdict'] != 'clean':
            print(f"SMC: {path} -> {'; '.join(meta['smc']['reasons'])}", file=sys.stderr);
            if args.strict_no_smc:
                failures += 1;
        if args.out:
            dest = args.out / (path.stem + '.meta.json');
            dest.write_text(json.dumps(meta, indent=args.indent), encoding='utf-8');
            s = meta['summary'];
            print(f"{path.name}: {s['functions']} funcs, "
                  f"{s['indirect_jumps_resolved']}/{s['indirect_jumps']} indirect jumps resolved, "
                  f"{s['indirect_calls_resolved']}/{s['indirect_calls']} indirect calls resolved "
                  f"-> {dest}");
        else:
            print(json.dumps(meta, indent=args.indent));

    return 1 if failures else 0;


if __name__ == '__main__':
    sys.exit(main());
