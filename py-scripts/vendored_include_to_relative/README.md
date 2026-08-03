# vendored_include_to_relative

A small utility that walks a C/C++ project, finds every quoted `#include "..."` directive, and rewrites it
to a path **relative to the file doing the including**. Angle-bracket includes (`#include <...>`) are left
untouched. Each target is resolved against an index of the whole source tree, so the tool can repair includes
even when the original path is wrong, partial, or missing a prefix.

It runs as a **dry run by default**: it prints what it *would* change and writes nothing until you pass `--apply`.

## Limitations

> Only double-quoted includes are considered `#include <...>` are ignored. Resolution relies on names being
> unique across the tree: when two headers share a name (or a sub-path suffix matches more than one file) the
> include is reported as **ambiguous** and left unchanged, with all data printed. Matching is purely
> path/name based; the script does not parse compiler include directories, so a header reachable only through a
> `-I` search path may not resolve.

## Overview

Given a project root, the script will:

- Index every file under the root (skipping excluded directories such as `.git`, `build`, `out`, `node_modules`, ...),
  recording both full normalized paths and a `filename -> paths` map.
- Scan each source file for lines matching `#include "..."`, preserving everything else.
- Resolve each include target using, in order:
  - **adjacent**  does it already resolve relative to the including file? If so it is counted as *already correct* and left as-is.
  - **suffix match**  does exactly one indexed path end with the given sub-path?
  - **basename fallback**  is there exactly one file in the whole tree with that name?
- Rewrite the include to the relative path from the source file's directory to the resolved header, preserving the
  original line ending and any trailing text after the directive.
- Warn and leave the line unchanged when the target cannot be found, or is ambiguous.
- Print a summary of rewritten / already-correct / not-found / ambiguous counts.

## Example

Given `src/engine/render.cpp` contains:

```cpp
#include "vector.hpp"
```

but the actual file lives at `src/math/types/vector.hpp`. The script finds the unique match and rewrites it:

```cpp
#include "../../math/types/vector.hpp"
```

Console output (dry run):

```
  src/engine/render.cpp:1: "vector.hpp" -> "../../math/types/vector.hpp"
```

## Usage

### Requirements

Python 3 only  the script uses just the standard library, so there is nothing to install.

### Run

By default the tool indexes the current directory, scans that same tree, and performs a **dry run**:

```bash
python include_to_relative.py .
```

Review the proposed changes, then apply them for real:

```bash
python include_to_relative.py . --apply
```

### Options

* `root` - Project root to index for headers (positional, default `.`). 
* `--src DIR\|FILE` - Directory or file to scan and rewrite. Repeatable; defaults to `root`.
* `--apply` - Actually modify files. Omit for a dry run.
* `--backup` - Write a `.bak` copy of each file before modifying it.
* `--ext .cpp,.h` - Comma-separated list of extensions to scan (default: common C/C++ extensions).
* `--exclude NAME\|GLOB` - Directory name or glob to skip. Repeatable (default: `.git`, `build`, `out`, `node_modules`, `cmake-build*`, ...).
* `--verbose` - Also report includes that are already correct.

### More examples

Index the whole repo but only rewrite files under `src/`, keeping backups:

```bash
python include_to_relative.py . --src src --apply --backup
```

Only touch `.cpp` and `.hpp` files:

```bash
python include_to_relative.py . --ext .cpp,.hpp --apply
```
