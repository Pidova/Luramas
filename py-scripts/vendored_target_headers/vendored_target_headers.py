#!/usr/bin/env python3

import argparse
import sys
from pathlib import Path

EXTENSIONS = {".c", ".cpp", ".h", ".hpp"}


def build_header(macro: str) -> str:
    return f"#if {macro}\n\n"


FOOTER = "\n#endif\n"


def is_already_wrapped(content: str, header: str) -> bool:
    """
    We compare the first non-empty line against the header's #if line so
    that trailing-whitespace or blank-line differences don't cause a
    double wrap.
    """
    header_first_line = header.strip().splitlines()[0].strip()

    for line in content.splitlines():
        stripped = line.strip()
        if not stripped:
            continue
        return stripped == header_first_line
    return False
    # empty file


def wrap_folder(folder: Path, macro: str, dry_run: bool = False) -> None:
    header = build_header(macro)
    wrapped = skipped = 0

    for file_path in folder.rglob("*"):
        if not (file_path.is_file() and file_path.suffix.lower() in EXTENSIONS):
            continue

        content = file_path.read_text(encoding="utf-8", errors="ignore")

        if is_already_wrapped(content, header):
            skipped += 1
            print(f"skip (already wrapped): {file_path}")
            continue

        if dry_run:
            print(f"would wrap: {file_path}")
        else:
            file_path.write_text(header + content + FOOTER, encoding="utf-8")
            print(f"wrapped: {file_path}")
        wrapped += 1

    action = "would wrap" if dry_run else "wrapped"
    print(f"\nDone. {action} {wrapped}, skipped {skipped}.")


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Wrap C/C++ files in a preprocessor guard."
    )
    parser.add_argument(
        "folder", type=Path, help="Input folder to process recursively."
    )
    parser.add_argument(
        "-m",
        "--macro",
        required=True,
        help="The condition placed after #if (without the '#if').",
    )
    parser.add_argument(
        "-n",
        "--dry-run",
        action="store_true",
        help="Show what would change without writing any files.",
    )
    args = parser.parse_args()

    if not args.folder.is_dir():
        print(f"error: not a directory: {args.folder}", file=sys.stderr)
        return 1

    wrap_folder(args.folder, args.macro, args.dry_run)
    return 0


if __name__ == "__main__":
    sys.exit(main())
