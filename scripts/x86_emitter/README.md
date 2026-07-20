# X86-Emitter

A small utility that takes raw x86-64 machine code, disassembles it with [Capstone](https://www.capstone-engine.org/), and prints out C++ `data.emit(...)` 
calls for the `luramas::profile` emitter.
Jump and call targets are resolved automatically: reachable targets are turned into labels, while targets that fall outside the supplied buffer are printed separately so nothing is silently dropped.

## Limitations

> This is designed to only test linearized behaviours to test x86 lifter and passes. Self-modifying code is not supported.


## Overview

Given a byte array, the script will:

- Disassemble the bytes as **64-bit x86** starting at a configurable base address.
- Walk every instruction and collect the targets of all jumps and calls.
- Assign an incrementing label ID to each reachable jump/call target.
- Emit one `data.emit({ ... })` line per instruction, annotated with the original mnemonic and operands as a trailing comment.
- For control-flow instructions, `inst_kind` (`jump_to` / `call_to`), the resolved label (or raw address), and for jumps whether the branch is conditional.
- Print a list of any jump/call targets that were referenced but not present in the buffer.

## Example

Given C:
```
eax += 5;
```

Compiled:
```
add eax, 5
```

As bytes (set by default):
```
0x83, 0xC0, 0x05
```

Output:
```
data.emit({0x83, 0xC0, 0x05}); /* add eax, 5 */
```

## Usage
 
### Install Dependencies

```
pip install -r requirements.txt
```

### Changing Bytes

Open `emitter.py` and clear `code = bytes([ ]);` array and paste bytes as formatted `0x??, 0x??, 0x??, ...` in array.

### Run

```bash
cd /d x86_emitter
python emitter.py
```

The script will print emissions to output.