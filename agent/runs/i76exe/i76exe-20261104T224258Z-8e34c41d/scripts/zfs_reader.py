"""Independent bounded ZFSF v1 research reader; no retail code or payloads.

Strict validation is a provider policy, not a claim retail rejects these inputs.
The decoder backend is system liblzo2's safe API on Linux LP64.
"""
from __future__ import annotations
import ctypes as C
import ctypes.util
from dataclasses import dataclass
from pathlib import Path
import struct
import sys

HEADER = struct.Struct('<4s6I')
RECORD = struct.Struct('<16s5I')
TABLE_BYTES = 4 + 100 * RECORD.size
MAX_ARCHIVE = 256 * 1024 * 1024
MAX_RECORD = 0x7fffff  # retail SAR flags_size,8 must remain nonnegative
MAX_RECORDS = 100000

class InvalidArchive(ValueError): pass
class DecodeError(ValueError): pass
class AmbiguousKey(LookupError): pass


def normalize(name: str) -> str:
    if not isinstance(name, str) or not 1 <= len(name) <= 15:
        raise InvalidArchive('name must contain 1..15 ASCII characters')
    if any(not 0x21 <= ord(c) <= 0x7e or c in '/\\:' for c in name) or name in ('.', '..'):
        raise InvalidArchive('invalid logical name')
    return name.lower()


def extent(offset: int, size: int, limit: int) -> tuple[int, int]:
    # Subtraction avoids wraparound in a fixed-width implementation.
    if offset < 0 or size < 0 or offset > 0x7fffffff or size > 0x7fffffff:
        raise InvalidArchive('signed CRT range exceeded')
    if offset > limit or size > limit - offset or size > 0x7fffffff - offset:
        raise InvalidArchive('extent out of range or arithmetic overflow')
    return offset, offset + size


@dataclass(frozen=True)
class Entry:
    ordinal: int
    directory_offset: int
    raw_name: bytes
    name: str
    key: str
    offset: int
    identifier: int
    stored_size: int
    time_word: int
    flags_size: int

    @property
    def flags(self): return self.flags_size & 255
    @property
    def active(self): return not bool(self.flags & 1)
    @property
    def mode(self): return 2 if self.flags & 2 else 4 if self.flags & 4 else 0
    @property
    def expected_size(self):
        if not self.mode: return self.stored_size
        return C.c_int32(self.flags_size).value >> 8


class SafeLzo:
    """int fn(src, unsigned long, dst, unsigned long*, void*) on Linux LP64.

    No compression fallback/probing. Mode is selected from original dispatch.
    Decoder implementation correctness remains an external dependency.
    """
    def __init__(self, library=None):
        if not sys.platform.startswith('linux') or C.sizeof(C.c_ulong) != 8 or C.sizeof(C.c_void_p) != 8:
            raise RuntimeError('this binding is validated only for Linux LP64')
        self.lib = C.CDLL(library or ctypes.util.find_library('lzo2') or 'liblzo2.so.2')
        self.lib.lzo_version_string.restype = C.c_char_p
        self.version = self.lib.lzo_version_string().decode('ascii')
        self.functions = {}
        for mode, name in ((2, 'lzo1x_decompress_safe'), (4, 'lzo1y_decompress_safe')):
            fn = getattr(self.lib, name)
            fn.argtypes = [C.c_void_p, C.c_ulong, C.c_void_p, C.POINTER(C.c_ulong), C.c_void_p]
            fn.restype = C.c_int
            self.functions[mode] = fn

    def decode(self, mode, payload, expected):
        if mode not in self.functions or not 0 < expected <= MAX_RECORD:
            raise DecodeError('unsupported mode or output length')
        if not 0 < len(payload) <= MAX_ARCHIVE:
            raise DecodeError('invalid input length')
        src = C.create_string_buffer(payload, len(payload))
        dst = C.create_string_buffer(expected)
        length = C.c_ulong(expected)
        rc = self.functions[mode](src, len(payload), dst, C.byref(length), None)
        if rc != 0 or length.value != expected:
            raise DecodeError(f'LZO rc={rc}, actual={length.value}, expected={expected}')
        return dst.raw


class Archive:
    """Immutable snapshot, immutable index and independently owned result bytes.

    No output file extraction, input mutation, shared seek state, or failure cache.
    Duplicate keys remain inspectable but implicit lookup rejects ambiguity.
    Exact aliases require matching decoding metadata; partial overlaps are rejected.
    """
    def __init__(self, data: bytes):
        if len(data) > MAX_ARCHIVE: raise InvalidArchive('archive exceeds policy limit')
        self._data = bytes(data)
        data = self._data
        if len(data) < HEADER.size: raise InvalidArchive('truncated header')
        magic, version, width, capacity, count, self.xor_key, first = HEADER.unpack_from(data)
        if (magic, version, width, capacity) != (b'ZFSF', 1, 16, 100):
            raise InvalidArchive('unsupported header')
        if count > MAX_RECORDS: raise InvalidArchive('record count exceeds policy limit')
        entries, tables, metadata = [], [], [(0, HEADER.size)]
        seen = set()
        pointer = first
        while pointer:
            if pointer in seen: raise InvalidArchive('repeated or cyclic table pointer')
            if len(tables) >= count // 100 + 1: raise InvalidArchive('too many tables')
            seen.add(pointer)
            lo, hi = extent(pointer, TABLE_BYTES, len(data))
            if any(lo < b and a < hi for a, b in metadata):
                raise InvalidArchive('overlapping directory tables/header')
            metadata.append((lo, hi))
            next_pointer = struct.unpack_from('<I', data, pointer)[0]
            tables.append((pointer, next_pointer))
            ended = False
            for slot in range(100):
                position = pointer + 4 + slot * RECORD.size
                raw, off, ident, size, time_word, flags = RECORD.unpack_from(data, position)
                if raw[0] == 0:
                    ended = True
                    # Retail ignores these bytes. Strict profile requires zero padding.
                    if any(data[position:position + RECORD.size]):
                        raise InvalidArchive('nonzero empty slot')
                    continue
                if ended: raise InvalidArchive('nonempty slot after table terminator')
                if b'\0' not in raw: raise InvalidArchive('unterminated name')
                try: name = raw.split(b'\0', 1)[0].decode('ascii')
                except UnicodeDecodeError as exc: raise InvalidArchive('non-ASCII name') from exc
                key = normalize(name)
                extent(off, size, len(data))
                entries.append(Entry(len(entries), position, raw, name, key, off, ident, size, time_word, flags))
                if len(entries) > count: raise InvalidArchive('record count exceeded')
            pointer = next_pointer
        if len(tables) != count // 100 + 1 or len(entries) != count:
            raise InvalidArchive('declared/discovered count mismatch')
        self.entries, self.tables = tuple(entries), tuple(tables)
        index = {}
        for entry in entries:
            if entry.active: index.setdefault(entry.key, []).append(entry)
        from types import MappingProxyType
        self.index = MappingProxyType({k: tuple(v) for k, v in index.items()})
        self.duplicate_keys = tuple(sorted(k for k, v in self.index.items() if len(v) > 1))
        aliases, previous = [], None
        for entry in sorted(entries, key=lambda e: (e.offset, e.stored_size, e.ordinal)):
            lo, hi = extent(entry.offset, entry.stored_size, len(data))
            if entry.stored_size and any(lo < b and a < hi for a, b in metadata):
                raise InvalidArchive('payload overlaps directory/header')
            if not entry.stored_size: continue
            if previous and lo < previous.offset + previous.stored_size:
                if (lo, entry.stored_size, entry.flags_size) != (previous.offset, previous.stored_size, previous.flags_size):
                    raise InvalidArchive('partial overlap or incompatible alias')
                aliases.append((previous.ordinal, entry.ordinal))
            previous = entry
        self.aliases = tuple(aliases)
        self._backend = None

    @classmethod
    def open(cls, path):
        with Path(path).open('rb') as stream:
            if stream.seek(0, 2) > MAX_ARCHIVE: raise InvalidArchive('archive exceeds policy limit')
            stream.seek(0)
            return cls(stream.read(MAX_ARCHIVE + 1))

    def candidates(self, name): return self.index.get(normalize(name), ())

    def lookup(self, name):
        matches = self.candidates(name)
        if not matches: raise KeyError(name)
        if len(matches) != 1: raise AmbiguousKey(name)
        return matches[0]

    def read(self, name): return self.read_entry(self.lookup(name))

    def read_entry(self, entry):
        if not isinstance(entry, Entry) or not 0 <= entry.ordinal < len(self.entries) or self.entries[entry.ordinal] is not entry:
            raise InvalidArchive('entry belongs to another archive')
        if not entry.active: raise DecodeError('inactive entry')
        if self._data is None: raise ValueError('archive closed')
        if entry.flags & ~7: raise DecodeError('unsupported flag bits')
        expected = entry.expected_size
        if not 0 <= expected <= MAX_RECORD: raise DecodeError('invalid expected output size')
        payload = self._data[entry.offset:entry.offset + entry.stored_size]
        if entry.mode:
            if self._backend is None: self._backend = SafeLzo()
            payload = self._backend.decode(entry.mode, payload, expected)
        if self.xor_key:
            # Original applies XOR after decompression, to complete little-endian words only.
            out = bytearray(payload)
            for pos in range(0, len(out) - 3, 4):
                struct.pack_into('<I', out, pos, struct.unpack_from('<I', out, pos)[0] ^ self.xor_key)
            payload = bytes(out)
        return payload

    def close(self): self._data = None; self._backend = None
