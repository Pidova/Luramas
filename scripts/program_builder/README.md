# Program-Builder

Compiles every C program in a folder into a binary to analyze: one linked x86-64 image per
translation unit, each with a `.meta.json` stating graphical edges as if it were gathered from a [DBI](https://github.com/Pidova/Lura-DBI/tree/main).

This is used to test passes and lifters alone not pre-analysis.

## Contents

* [`program_builder.py`](program_builder.py) - compiles a source tree and runs the extractor over the result.
* [`ground_truth.py`](ground_truth.py) - the extractor. Also usable standalone against any x86-64 ELF, or a folder of them.

## Why the compile flags matter

Indirect jump recovery is usually resolved by a [DBI](https://github.com/Pidova/Lura-DBI/tree/main).
We only want to care how passes preform and if there is any bugs we can spo.

| Flag | Effect |
| --- | --- |
| `-Wl,--emit-relocs` | keeps relocations in the **linked** image, so a jump table resolves out of `.rela.rodata` instead of a scan |
| `-Wa,-L` | keeps local `.L` labels in `.symtab`, so table targets come back named (`.L18`) rather than `loc_401133` |
| `-fno-pie -no-pie` | absolute 8-byte tables; the PIC form is a 4-byte delta table, still recoverable but only by inference |
| `-z noexecstack`, `-z relro -z now` | no executable stack, no lazy PLT patching |
| `-Wtrampolines` | GCC nested functions build a trampoline on the stack, which is self-modifying code; `--strict-no-smc` promotes it to an error |
| `-fcf-protection=none` | drops `endbr64`/`notrack` padding for a cleaner lift (`--cf-protection default` to keep it) |

Unsupported flags are probed once at startup and dropped with a note rather than breaking every
build, since clang's integrated assembler rejects `-Wa,-L` (it falls back to
`-fno-integrated-as`).

## Indirect branch resolution

Every branch site carries a `resolution` and a `complete` flag.

| `resolution` | Meaning | Exact |
| --- | --- | --- |
| `reloc` | read out of relocation data | yes |
| `disasm` | direct branch, target in the instruction | yes |
| `table_scan` | table read from `.rodata`, extent bounded by the `cmp`/`ja` guard | yes when `complete` |
| `field_store` | callback in a struct field, narrowed to functions ever stored at that offset | no |
| `address_taken` | fallback: every address-taken function | no |
| `unresolved` | no static base found | no |

Table extent is cross-checked two ways: `count_from_relocs` (how many consecutive relocated
slots follow the base) and `bound_from_compare` (the `cmp $N, reg ; ja default` guard). The
walker takes the smaller. This matters — when two tables sit adjacent in `.rodata` the
relocation run spans both, and only the compare bound stops the scan at the right place.

Both shapes are handled:

```
absolute   jmp *TABLE(,%rax,8)                       entries are 8-byte addresses
relative   lea BASE,[rip+TABLE] ; movsxd ... ; add   entries are 4-byte deltas from the base
```

For the register form (`jmp *%rax`) a bounded backward slice walks up to 40 instructions to
find the table load.

## Every instruction that moves rip

`edges` is the flat control-flow list: one record per control transfer, in address order,
including the intra-procedural branches that never reach the call graph. It is the answer to
"where does this instruction go".

| `kind` | Targets | `fallthrough` |
| --- | --- | --- |
| `jump` | the target | none |
| `conditional_jump` | the taken target | the not-taken address |
| `call` | the callee | the return address |
| `indirect_jump` | every jump-table entry | none |
| `indirect_call` | resolved or over-approximated callees | the return address |
| `return` | none | none |

```json
{ "va_hex": "0x401059", "in_function": "romanToInt", "text": "ja 0x40118e",
  "kind": "conditional_jump", "conditional": true,
  "targets_hex": ["0x40118e"], "fallthrough_hex": "0x40105f",
  "resolution": "disasm", "complete": true }
```

Every record carries the same `resolution`/`complete` pair as the call graph, so an incomplete
edge is visible in the flat list too. `--no-edges` omits the section if the metadata is getting
large; it roughly doubles a `.meta.json`.

## Self-modifying code

The lifter is linear and does not support SMC, so each image gets a static audit:

* sections or `PT_LOAD` segments that are both writable and executable
* executable `PT_GNU_STACK`
* `DT_TEXTREL` (the loader patches `.text` at load time)
* RIP-relative stores landing in executable memory
* imports that can mint or rewrite code: `mprotect`, `mmap`, `memfd_create`, `dlopen`, ...

`verdict` is `clean` or `suspect` with reasons. `--strict-no-smc` fails the run on any hit.

## Output layout

Artifacts keep the source tree's shape. Each one is tagged with its optimisation level, so
several corpora coexist without colliding:

```
programs/
  program_index.json                 every entry, status, diagnostics, aggregate totals
  leetcode/src/
    13.c                             the source, untouched
    13.O0        13.O2               the linked images
    13.O0.meta.json  13.O2.meta.json the ground truth
    13.O0.s      13.O2.s             with --save-asm
```

By default this is written in place, next to the sources. `-o DIR` mirrors the same relative
layout under another root instead, and `--clean` deletes everything the script generated
(matching only its own `.<opt>` artifacts, so it is safe to point at a tree holding sources).

`meta.json`, trimmed:

```json
{
  "schema": "luramas.graphv1",
  "smc": { "verdict": "clean", "reasons": [] },
  "call_sites": [
    { "va_hex": "0x4010aa", "kind": "call", "mode": "indirect",
      "resolution": "reloc", "complete": true,
      "target_names": ["f0", "f1", "f2"] }
  ],
  "indirect_jumps": [
    { "va_hex": "0x401069", "text": "jmp rax", "in_function": "romanToInt",
      "resolution": "reloc", "complete": true,
      "table": { "va": 4202496, "entry_size": 8, "entry_kind": "absolute",
                 "count": 22, "bound_from_compare": 22, "count_from_relocs": 22 },
      "entries": [ { "index": 0, "va": 4198542, "label": ".L4",
                     "in_function": "romanToInt",
                     "valid_instruction_boundary": true } ]
    }
  ],
  entry: ""
}
```

`valid_instruction_boundary` is a self-check: a recovered target that does not land on an
instruction boundary in the extractor's own disassembly means the recovery is wrong.

## Building on Windows

The extractor reads ELF only, so a native MinGW/MSVC build is a dead end: its
`ld` has no `-z` options, and even once those are dropped the resulting PE
image fails with `Magic number does not match`. The toolchain check catches
this before building anything and says so.

Cross-compile to Linux instead. [zig](https://ziglang.org) is a single download
that bundles a glibc sysroot, so no WSL and no sysroot wrangling:

```
scoop install zig
python program_builder.py C:\repo\Luramas\tests\programs\TheAlgorithms -o build ^
  --opt O0 O2 --jobs 4 --cc "zig cc" --target x86_64-linux-gnu ^
  --force-include limits.h string.h stdlib.h stdio.h ctype.h math.h stdint.h
```

`--cc` accepts a multi-word driver, and `--target` is threaded into both the
compile and the link. Three things to know about this path:

| | |
| --- | --- |
| no-main units | zig's driver has no `--unresolved-symbols=ignore-all`, so a translation unit without `main` cannot be laid out. Those entries come back `image-unsupported` -- 166 of 407 in `TheAlgorithms`. Sources with `main` build normally. |
| jump tables | zig's driver has no `--emit-relocs`, so tables resolve by `table_scan` rather than `reloc`. Measured on this corpus that costs nothing: 24/24 still resolve, all `complete`, no `valid_instruction_boundary` failures. |
| scope | zig's CRT carries DWARF, so `_start` and `__libc_csu_init`/`_fini` pass the `--scope user` filter and show up per image. |
| jobs | keep `--jobs` low. Each `zig cc` is far heavier than a `gcc`; 16 parallel jobs will exhaust memory. |

Unsupported compile *and* link flags are probed once and dropped with a note,
so other drivers work too -- the run reports what it dropped and records it
under `toolchain.dropped_flags` in `program_index.json`.

WSL remains the full-fidelity option: `gcc` there needs no flags dropped and
builds the whole corpus, no-main units included.

## Usage

### Install dependencies

```
pip install -r requirements.txt
```

### Build a corpus

```bash
python program_builder.py ../../programs
python program_builder.py ../../programs --opt O0 O1 O2 O3 --jobs 16
python program_builder.py ../../programs -o ../../build --strict-no-smc --static
python program_builder.py ../../programs --clean
```

Useful options:

* `-o` write artifacts under another root, same relative layout (default: in place)
* `--clean` remove previously generated artifacts and exit
* `--cc` compiler to drive, may be multi-word (default: `$CC`, else the first of `clang`/`gcc`/`cc` found on PATH)
* `--target` cross-compile triple passed as `--target=`, e.g. `x86_64-linux-gnu`
* `--opt` one corpus per optimisation level, default `O0 O2`
* `--scope user|all` metadata for corpus code only, or the whole image including the CRT
* `--static` no PLT, everything in one image
* `--save-asm` keep the `.s` beside each image
* `--force-include` headers to `-include` everywhere, to rescue sources with missing includes
* `--exclude` path substrings to skip

### If the output folder comes out empty

The toolchain is probed once, up front, by compiling and linking a trivial
program with the exact flag set the run will use. If that probe fails the run
aborts immediately with the compiler's own diagnostic rather than building the
whole matrix and leaving an output tree of empty directories. Common causes:

* a `--force-include` header that does not resolve
* `--static` without a static libc installed
* a toolchain that emits PE or Mach-O rather than ELF (see Building on Windows)

If the probe passes but every source still fails, the run exits non-zero and
prints the first few real diagnostics; the full set is in `program_index.json`.
Directories are only created when there is an artifact to put in them, so an
empty output folder now means nothing was built, not that something was lost.

### Extract from existing binaries

```bash
python ground_truth.py ../../programs -o ../../metadata
python ground_truth.py some_binary --scope all
```

## Results on `programs/TheAlgorithms`

407 sources at `-O0` and `-O2`, GCC 13.3, `--force-include limits.h string.h stdlib.h stdio.h`:

```
built 676/814   functions 2547   SMC suspect 0
indirect jumps  24/24 resolved, all from relocation data
indirect calls  4 narrowed by field store, 4 over-approximated

CFG edges       26687 total, 8 incomplete
  call               10425
  conditional_jump    9727
  jump                3813
  return              2690
  indirect_jump         24
  indirect_call          8
```

The 8 incomplete edges are all one program, `segment_tree.c`, whose comparator lives in a
struct field. At `-O2` the field store is visible and all four sites narrow to `minimum`; at
`-O0` the callback is spilled to a stack slot first, which the field tracker deliberately does
not follow, so those four fall back to the address-taken set.

The 138 failures are upstream corpus bugs, each recorded with its diagnostic in
`program_index.json`: `#include <conio.h>`, undefined struct types, and similar. Two fallbacks
already run automatically — a case-insensitive include shim for sources that ask for `Graph.h`
when the file is `graph.h`, and sibling-unit linking for directories where `main.c` needs the
`.c` next to it.

## Limitations

* Linux ELF only. The SMC audit knows the PE import names but nothing else here parses PE.
* A translation unit with no `main` is linked with `-nostartfiles -e 0` and unresolved symbols
  ignored, purely so its code lands at real virtual addresses. Those images are laid out, not
  runnable.
* Function-pointer resolution is deliberately shallow: one interprocedural step from a direct
  caller's argument into a struct field. Anything that flows through the heap or several calls
  falls back to the address-taken set, flagged `complete: false`.
* Verified against GCC 13.3. The clang path is implemented but not exercised.
* `--emit-relocs` leaves `.rela.debug_*` in the linked image, which makes pyelftools apply
  those relocations a second time and walk off the end of the section. The extractor passes
  `relocate_dwarf_sections=False` for that reason — worth knowing if you extend it, because the
  failure is silent and shows up as zero functions.
