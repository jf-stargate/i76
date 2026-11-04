"""Independent read-only reader for the observed retail CRLF HZD profile.
No resource I/O, loading, rendering, or approximation of unsafe CRT scans.
"""
from dataclasses import dataclass
import re

class FormatError(ValueError):
    pass

@dataclass(frozen=True)
class Manifest:
    raw: bytes
    names: tuple[str, ...]
    offsets: tuple[int, ...]

    def serialize(self) -> bytes:
        return self.raw

    def references(self) -> tuple[tuple[int, str], ...]:
        # Keep repeated slots. Resolution and reference ownership are separate.
        return tuple(enumerate(self.names))

# Conservative corpus profile, not every input the original scanner can consume.
NAME = re.compile(rb"[A-Za-z][A-Za-z0-9_.-]{0,14}\Z")

def parse(data: bytes) -> Manifest:
    raw = bytes(data)
    # 16 slots with <=15 bytes plus CRLF. Reject before any unbounded operation.
    if len(raw) > 16 * 17:
        raise FormatError('manifest exceeds profile size bound')
    names, offsets = [], []
    pos = 0
    for slot in range(16):
        end = raw.find(b'\r\n', pos, min(len(raw), pos + 17))
        if end < 0:
            raise FormatError(f'slot {slot}: missing bounded CRLF')
        token = raw[pos:end]
        if not NAME.fullmatch(token):
            raise FormatError(f'slot {slot}: empty, oversized, or unsupported name bytes')
        offsets.append(pos)
        names.append(token.decode('ascii'))
        pos = end + 2
    if pos != len(raw):
        raise FormatError('trailing content or excess records')
    return Manifest(raw, tuple(names), tuple(offsets))
