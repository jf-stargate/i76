#!/usr/bin/env python3
"""Check the maintained reconstruction's 80-column and function-banner style."""

from __future__ import annotations

import argparse
from pathlib import Path
import re
import sys


CONTROL_FLOW = {"if", "for", "while", "switch", "catch", "return"}
NAME_PATTERN = re.compile(r"(~?[A-Za-z_]\w*)\s*$")
TRAILER_PATTERN = re.compile(
    r"\)\s*(?:(?:noexcept|const|override|final)\s*)*$"
)


def function_starts(lines: list[str]) -> list[tuple[int, str]]:
    """Locate ordinary free functions and inline destructors with Allman braces."""
    result: list[tuple[int, str]] = []
    for brace_index, line in enumerate(lines):
        if line.strip() != "{":
            continue
        for index in range(brace_index - 1, max(-1, brace_index - 16), -1):
            candidate = lines[index]
            if (
                not candidate.strip()
                or candidate.lstrip().startswith("//")
                or any(character in candidate for character in ";{}")
            ):
                break
            if "(" not in candidate:
                continue
            if candidate[:1].isspace() and not re.match(
                r"^\s+~[A-Za-z_]\w*\s*\(", candidate
            ):
                continue
            signature = " ".join(lines[index:brace_index]).strip()
            prefix = signature.split("(", 1)[0]
            match = NAME_PATTERN.search(prefix)
            if (
                match
                and match.group(1) not in CONTROL_FLOW
                and TRAILER_PATTERN.search(signature)
            ):
                result.append((index, match.group(1)))
            break
    return result



def logical_operators(line: str, in_block_comment: bool) -> tuple[list[int], bool]:
    """Find Boolean operators outside comments, quotes, and preprocessor text."""
    if line.lstrip().startswith("#"):
        return [], in_block_comment

    positions: list[int] = []
    quote: str | None = None
    escaped = False
    index = 0
    while index < len(line) - 1:
        character = line[index]
        following = line[index + 1]

        if in_block_comment:
            if character == "*" and following == "/":
                in_block_comment = False
                index += 2
            else:
                index += 1
            continue

        if quote is not None:
            if escaped:
                escaped = False
            elif character == "\\":
                escaped = True
            elif character == quote:
                quote = None
            index += 1
            continue

        if character == "/" and following == "/":
            break
        if character == "/" and following == "*":
            in_block_comment = True
            index += 2
            continue
        if character in ("'", '"'):
            quote = character
            index += 1
            continue
        if character + following in ("||", "&&"):
            positions.append(index)
            index += 2
            continue
        index += 1

    return positions, in_block_comment

def check_file(path: Path) -> tuple[int, int, list[str]]:
    """Report long source lines and missing descriptive function headers."""
    content = path.read_text(encoding="utf-8")
    lines = content.splitlines()
    errors: list[str] = []
    in_block_comment = False
    for index, line in enumerate(lines, 1):
        if len(line) > 80:
            errors.append(f"{path}:{index}: {len(line)} columns (maximum 80)")

        if path.suffix not in {".c", ".cpp", ".h", ".hpp"}:
            continue
        operators, in_block_comment = logical_operators(line, in_block_comment)
        for position in operators:
            if line[:position].strip():
                errors.append(
                    f"{path}:{index}: place each && or || at the start "
                    "of its own condition line"
                )
            elif not line[position + 2 :].strip():
                errors.append(
                    f"{path}:{index}: logical operator needs a condition "
                    "on the same line"
                )

    function_count = 0
    if path.suffix in {".cpp", ".c"}:
        for index, name in function_starts(lines):
            function_count += 1
            indentation = re.match(r"^\s*", lines[index]).group(0)
            rule = indentation + "// " + "-" * (77 - len(indentation))
            if index < 3:
                errors.append(
                    f"{path}:{index + 1}: {name} is missing a function banner"
                )
                continue
            if (
                lines[index - 3] != rule
                or not lines[index - 2].startswith(indentation + "// ")
                or not lines[index - 2][len(indentation) + 3 :].strip()
                or lines[index - 1] != rule
            ):
                errors.append(
                    f"{path}:{index + 1}: {name} needs a descriptive "
                    "80-column function banner"
                )
    return len(lines), function_count, errors


def main() -> int:
    """Check all maintained implementation, test, and public-header files."""
    parser = argparse.ArgumentParser()
    parser.add_argument("source_root", type=Path)
    options = parser.parse_args()
    source_root: Path = options.source_root
    paths: list[Path] = []
    for directory in ("src", "tests", "include"):
        root = source_root / directory
        for suffix in ("*.c", "*.cpp", "*.h", "*.hpp"):
            paths.extend(root.rglob(suffix))
    paths.sort()

    total_lines = 0
    total_functions = 0
    errors: list[str] = []
    for path in paths:
        lines, functions, problems = check_file(path)
        total_lines += lines
        total_functions += functions
        errors.extend(problems)
    for problem in errors:
        print(problem, file=sys.stderr)
    print(
        f"Checked {len(paths)} files, {total_lines} lines, "
        f"{total_functions} function definitions; {len(errors)} issues"
    )
    return 0 if not errors else 1


if __name__ == "__main__":
    raise SystemExit(main())
