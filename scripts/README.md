# Scripts

Helper scripts that generate data used by the main framework. 
These are build-time utilities, not part of the runtime.

## Contents

* [`intel_x86_built_in_builder/`](intel_x86_built_in_builder/) - Generates a C++ table mapping x86 instructions (Capstone `x86_insn` IDs) to their semantic *built-ins*, derived from Intel's Intrinsics Guide data.
* [`x86_emitter/`](x86_emitter/) - Generates C++ emitter data for testing chunks of x86 instructions.
* [`x86_intel_msr_builder`](x86_intel_msr_builder/) - Generates C++ Intel X86 MSRs offsets.

See each subdirectory's `README.md` for details.

## Requirements

- Python 3
- Per-script dependencies (see each subdirectory), install them with pip `pip install -r requirements.txt` 
