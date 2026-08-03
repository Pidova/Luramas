# Vendored-Target-Headers

A small script that traverses a folder of C/C++ sources and wraps each file in a preprocessor target guard.
The guard condition is taken from the command line, and every matching file is enclosed with an `#if <macro>` header and a `#endif` footer.
Re-running is safe: a file already carrying the exact guard is left untouched instead of being wrapped a second time.

## Limitations

> This only detects and skips *its own* guard, matched against the first non-empty line of the file. A file already
> wrapped with a *different* macro will still get the new guard added on top of it, and comments that happen
> to start with a matching `#if` line could be misread. Files are matched purely by extension.

## Overview

Given a folder, the script will:

- Walk the folder **recursively**, selecting every file whose extension is `.c`, `.cpp`, `.h`, or `.hpp`.
- Read each file as text and inspect its first non-empty line.
- Compare that line against the `#if <macro>` header to decide whether the guard is already present.
- Skip files that are already wrapped, and bracket the rest with the `#if <macro>` header and `#endif` footer.
- Report how many files were wrapped versus skipped, with a `--dry-run` mode that previews changes without writing.

## Example

Given source folder `Luau-V6`:
```cpp
void run() { /* ... */ }
```

Run with:
```
python vendored_target_headers.py Luau-V6 -m "defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)"
```

Result:
```cpp
#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)

#include "Luau/Analyze.h"

void run() { /* ... */ }

#endif
```

## Usage

### Install Dependencies

None. The script uses only the Python standard library (Python 3.6+).

### Changing Input

The script takes the target folder as its argument, and the guard condition via `-m` / `--macro` (without leading `#if`). 
Add `-n` / `--dry-run` to preview which files would change without writing anything.
