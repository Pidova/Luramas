# X86-Intel-MSR-Builder

A small utility that takes an Intel [SDM](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html) PDF, extracts every MSR from its
"Table 2-2. IA-32 Architectural MSRs" tables with [PyMuPDF](https://pymupdf.readthedocs.io/), and writes out C++
`static constexpr` declarations for the `msrs::intel` namespace.
Register names and addresses are pulled straight from the table, and each declaration is commented with the MSR's
one-line description as a trailing comment so nothing is lost against the source manual.

## Limitations

> This is designed to only parse the linear text of the "Register Address:" MSR tables. Registers described purely
> in prose, or in tables using a different layout, are not extracted. A handful of descriptions may come through
> truncated where a row's column layout differs from the common cases.

## Overview

Given a PDF, the script will:

- Read the PDF page by page as **plain text**, using PyMuPDF and falling back to pdfplumber.
- Walk the text and locate every `Register Address: <hex>H, <dec>` block.
- Pull the `IA32_*` / `MSR_*` identifier and its hex address from each block, removing duplicates repeats across page breaks.
- Generate one-line description, handling both column shapes (description before or after the `(R/W)` access marker) and emitting no comment when the row has none.
- Emit one `static constexpr auto` line per MSR, wrapped in the `LURAMAS_TARGET_X86` guard and `msrs::intel` namespace.

## Example

Given SDM table row:
```
Register Address: C1H, 193   IA32_PMC0
General Performance Counter 0 (R/W)   If CPUID.0AH:EAX[15:8] > 0
```

Output:
```cpp
static constexpr auto IA32_PMC0 = 0xC1; /* General Performance Counter 0 */
```

## Usage

### Install Dependencies

```
pip install -r requirements.txt
```

### Changing Input

The script takes the SDM PDF path as a single argument. 

### Run

```bash
cd /d x86_intel_msr_builder
python x86_intel_msr_builder.py sdm.pdf
```

Generates declarations to `output.hpp`.
