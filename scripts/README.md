# Scripts

Helper scripts that generate data used by the main framework. 
These are build-time utilities, not part of the runtime.

## Contents

* [`built_in_builder/`](built_in_builder/) - Generates a C++ table mapping x86 instructions (Capstone `x86_insn` IDs) to their semantic *built-ins*, derived from Intel's Intrinsics Guide data.

See each subdirectory's `README.md` for details.

## Requirements

- Python 3
- Per-script dependencies (see each subdirectory), install them with pip `pip install -r requirements.txt` 
