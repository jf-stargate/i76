"""Strict, read-only PIX text/PAK reader. No retail payloads are included.

Independent policy: ASCII names <=15 bytes, nonnegative signed-32 decimal
fields, exact count, LF termination, bounded immutable PAK snapshots, ambiguous
keys rejected. These checks deliberately exceed original validation.
"""
from __future__ import annotations
import argparse
from dataclasses import dataclass, asdict
import json
from pathlib import Path
import re
import struct

MAX_INDEX_BYTES = 16 * 1024 * 1024
MAX_ENTRIES = 250_000
MAX_PAK_BYTES = 128 * 1024 * 1024
INT_MAX = 0x7fffffff

class FormatError(ValueError):
    pass

class AmbiguousKey(FormatError):
    pass

def key16(name: str) -> bytes:
    try:
        raw = name.encode("ascii")
    except (UnicodeError, AttributeError) as exc:
        raise FormatError("unsupported non-ASCII name") from exc
    if not 1 <= len(raw) <= 15 or any(c <= 32 or c >= 127 for c in raw):
        raise FormatError("name must be 1..15 printable ASCII bytes without whitespace")
    if any(c in raw for c in (b"/", b"\\", b":")) or name in (".", ".."):
        raise FormatError("name must be a flat resource key")
    return raw.lower().ljust(16, b"\0")

def compare16(left: bytes, right: bytes) -> int:
    """Original callback's signed wrapped DWORD subtraction, including post-NUL bytes."""
    if len(left) != 16 or len(right) != 16:
        raise FormatError("comparison requires exactly 16 bytes")
    for a, b in zip(struct.unpack("<4I", left), struct.unpack("<4I", right)):
        d = (a - b) & 0xffffffff
        if d:
            return d if d < 0x80000000 else d - 0x100000000
    return 0

def decimal(token: bytes) -> int:
    if len(token) > 11 or not re.fullmatch(rb"[+]?[0-9]+", token):
        raise FormatError("expected bounded nonnegative decimal integer")
    value = int(token, 10)
    if value > INT_MAX:
        raise FormatError("signed-32 integer overflow")
    return value

@dataclass(frozen=True)
class Entry:
    ordinal: int
    name: str
    offset: int
    size: int
    line_offset: int
    name_offset: int
    offset_token_offset: int
    size_token_offset: int

    @property
    def key(self) -> bytes:
        return key16(self.name)

@dataclass(frozen=True)
class Index:
    entries: tuple[Entry, ...]

    def candidates(self, name: str) -> tuple[Entry, ...]:
        key = key16(name)
        return tuple(e for e in self.entries if compare16(key, e.key) == 0)

    def lookup(self, name: str, *, ordinal: int | None = None) -> Entry:
        matches = self.candidates(name)
        if ordinal is not None:
            matches = tuple(e for e in matches if e.ordinal == ordinal)
        if not matches:
            raise KeyError(name)
        if len(matches) != 1:
            raise AmbiguousKey("multiple candidates; select an explicit ordinal")
        return matches[0]

def parse_index(data: bytes) -> Index:
    if len(data) > MAX_INDEX_BYTES:
        raise FormatError("index byte limit exceeded")
    if not data or not data.endswith(b"\n") or b"\0" in data:
        raise FormatError("index requires LF termination and no NUL")
    try:
        data.decode("ascii")
    except UnicodeError as exc:
        raise FormatError("unsupported index encoding") from exc
    lines = data.split(b"\n")
    header = lines[0].strip(b" \t\r")
    count = decimal(header)
    if count > MAX_ENTRIES:
        raise FormatError("entry limit exceeded")
    if len(lines) < count + 2:
        raise FormatError("truncated records")
    entries = []
    position = len(lines[0]) + 1
    for ordinal, line in enumerate(lines[1:count + 1]):
        tokens = list(re.finditer(rb"[^ \t\r\v\f]+", line))
        if len(tokens) != 3:
            raise FormatError("expected exactly name offset size")
        name = tokens[0].group().decode("ascii")
        key16(name)
        offset, size = (decimal(t.group()) for t in tokens[1:])
        if offset > 0xffffffff - size:
            raise FormatError("range arithmetic overflow")
        entries.append(Entry(ordinal, name, offset, size, position,
                             *(position + t.start() for t in tokens)))
        position += len(line) + 1
    if any(line.strip(b" \t\r") for line in lines[count + 1:]):
        raise FormatError("extra records or unsupported trailing data")
    return Index(tuple(entries))

def read_index(path: Path) -> Index:
    with path.open("rb") as stream:
        data = stream.read(MAX_INDEX_BYTES + 1)
    return parse_index(data)

def sibling_pak(pix: Path) -> Path:
    """Match original first-dot replacement; case ambiguity is an error."""
    if pix.suffix.lower() != ".pix" or pix.name.count(".") != 1:
        raise FormatError("unsupported PIX basename")
    key16(pix.name)
    wanted = pix.name.split(".", 1)[0].lower() + ".pak"
    matches = [p for p in pix.parent.iterdir() if p.name.lower() == wanted]
    if not matches:
        raise FileNotFoundError(wanted)
    if len(matches) != 1:
        raise FormatError("ambiguous backing filename case")
    resolved = matches[0].resolve()
    if resolved.parent != pix.parent.resolve() or not resolved.is_file():
        raise FormatError("backing file escapes sibling directory or is not regular")
    return resolved

def validate_ranges(index: Index, pak_size: int) -> None:
    for e in index.entries:
        if e.offset > pak_size or e.size > pak_size - e.offset:
            raise FormatError(f"entry {e.ordinal}: range outside backing data")

class Reader:
    """One PIX source. Snapshot retained by Python views; failures never poison cache."""
    def __init__(self, pix: Path):
        self.pix = Path(pix)
        self.index = read_index(self.pix)
        self._snapshot = None

    def acquire(self, name: str, *, ordinal: int | None = None) -> memoryview:
        entry = self.index.lookup(name, ordinal=ordinal)
        if self._snapshot is None:
            pak = sibling_pak(self.pix)
            with pak.open("rb") as stream:
                data = stream.read(MAX_PAK_BYTES + 1)
            if len(data) > MAX_PAK_BYTES:
                raise FormatError("PAK byte limit exceeded")
            validate_ranges(self.index, len(data))
            self._snapshot = data
        return memoryview(self._snapshot)[entry.offset:entry.offset + entry.size]

    def close(self) -> None:
        # Outstanding immutable views keep their own owner alive.
        self._snapshot = None

def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("pix", type=Path)
    ap.add_argument("name")
    ap.add_argument("--ordinal", type=int)
    args = ap.parse_args()
    try:
        reader = Reader(args.pix)
        entry = reader.index.lookup(args.name, ordinal=args.ordinal)
        view = reader.acquire(args.name, ordinal=args.ordinal)
        import hashlib
        print(json.dumps({**asdict(entry), "pak": sibling_pak(args.pix).name,
                          "sha256": hashlib.sha256(view).hexdigest()}))
    except (OSError, FormatError, KeyError) as exc:
        ap.exit(2, f"PIX/PAK: {exc}\n")

if __name__ == "__main__":
    main()
