# built_in_builder

A code generator that turns Intel's official **Intrinsics Guide** data into a
C++ lookup table mapping x86 instructions to their semantic *built-ins*.

Given a Capstone `x86_insn` ID (e.g. `X86_INS_ADDPS`), the table
describes what the instruction *does* in terms of the Intel intrinsics that
implement it: their return values, parameters, argument order, affected CPU
flags, and fully-resolved operand types. The output is emitted as an
`output.cpp` fragment ready to be compiled.

**This data is used in the X86 lifter for either optional intrinsic emissions or data**

## What it produces

Generates `output.cpp` that contains one entry per supported instruction:

```cpp
{x86_insn::X86_INS_AESENC, builtin({
    func("_mm_aesenc_si128",
        { arg("dst", -1, 0, object("__m128i", luramas::types::native::t_m128i, 0u, false, false)) },
        { arg("a",       -1, 0, object("__m128i", luramas::types::native::t_m128i, 0u, false, false)),
          arg("RoundKey", -1, 1, object("__m128i", luramas::types::native::t_m128i, 0u, false, false)) })
})},
```

Structure:

* `x86_insn::X86_INS_*` - Capstone instruction ID used as the map key.
* `builtin({ ... })` - All intrinsic overloads that lower to this instruction. 
* `func("name", {results}, {params})` - One intrinsic: its name, result list, and parameter list. 
* `arg("varname", flag, index, object(...))` - A single result/parameter slot.
* `getflag(CF)` / `-1` - The CPU flag this slot reads or writes, or `-1` if none. 
* `object("type", native::t_*, ptrs, const_ptr, const_val)` - The fully-resolved operand type. 

A single instruction can map to several intrinsics (for example `ADCX` and
`ADOX` both come from `_addcarryx_u32` / `_addcarryx_u64`), and the flag column
distinguishes them (`getflag(CF)` vs `getflag(OF)`).

## How it works

1. **Load the data.** `xmls/intel.xml` (the Intel Intrinsics Guide export) is
   parsed with `xmltodict` and converted to a plain dict via `json`.
2. **Parse each intrinsic** (`parse_intrinsic`): reads the `<return>`,
   `<parameter>`, and `<instruction>` elements, assigning each operand an
   argument index and, where relevant, a flag derived from `*_in` varnames.
3. **Resolve types** (`parse_type` + `underlying_map`): normalizes the C type
   string (strips `const`/`constexpr`, counts `*`) and maps the base type to a
   `luramas::types::native::t_*` enum. Unknown pointer types fall back to
   `t_int32`; other unknowns become `t_none`. Results are cached.
4. **Build the instruction map** (`generate_instruction_map`): emits a
   `func(...)` string per intrinsic and keys it by each `<instruction name=...>`.
   When an intrinsic carries several instruction forms, a per-instruction
   *override flag* is computed from the instruction mnemonic so, e.g., the `C`
   in `ADCX` and the `O` in `ADOX` select the correct flag.
5. **Filter and emit** (`generate_output`): only instructions whose key exists
   in the built-in `x86_insn` list (Capstone's enum, mirrored at the top of the
   script) are written out. Everything else is dropped.

The `x86_insn` list embedded in the script is Capstone's x86 instruction
enumeration (from `X86_INS_INVALID` through the `X86_INS_ENDING` sentinel) and
acts as the allow-list that keeps the output in sync with the disassembler.

## Layout

```
built_in_builder/
|- intel_intrins_xml.py   # Generator
|- xmls/
|   -- intel.xml          # Intel Intrinsics Guide data (input)
|- output.cpp             # Output file
```

## Usage

### Get the data

`xmls/intel.xml` is already included. To update it, download the latest Intrinsics Guide dataset from Intel and save it there:

```
https://www.intel.com/content/dam/develop/public/us/en/include/intrinsics-guide/data-3-6-9.xml
```
 > Change version number to current
 
### Install Dependencies

```
pip install -r requirements.txt
```

### Run

```bash
cd /d built_in_builder
python intel_intrins_xml.py
```

The script expects to be run from this directory, since it opens
`xmls/intel.xml` by relative path. On success it prints:

```
Done Written to output.cpp
```

and writes `output.cpp` next to the script.
