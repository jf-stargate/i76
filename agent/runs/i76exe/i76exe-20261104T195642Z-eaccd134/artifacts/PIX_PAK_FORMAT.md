# PIX/PAK serialized format — bounded verified contract

Evidence: binary-static authenticated retail instructions in `instructions.json`,
20 functions / 1,559 instructions, plus authenticated base-game corpus in
`corpus.json`. This is a research proposal, not promoted canonical documentation.
No retail resource route was dynamically executed. All VAs are retail PE32 VAs.

## PIX is text, not a 0x1C-byte disk directory

The inspected variant has **no signature or version field**. Byte zero starts a
signed decimal count line. Each of the next count lines has three whitespace
separated tokens:

```text
<count>\r\n
<name> <decimal byte offset> <decimal byte length>\r\n
...
```

The displayed escapes mean actual CR/LF bytes. Corpus: 1,758 of 1,758 indexes
have CRLF. The original explicitly searches LF (`strchr(...,10)`), overwrites
that LF with NUL, and scans each resulting line with `%d` or `%s %d %d`.
CR is whitespace for scanning. LF-only fixtures also satisfy this path. A final
LF is necessary for the last declared row to reach `sscanf`. There is no
fixed serialized row size, fixed name slot, binary count field or on-disk
alignment. Decimal text has no binary endianness. All measured tokens are ASCII;
non-ASCII locale behavior is unresolved.

| Serialized location | Width / syntax | Runtime destination | Evidence |
|---|---|---|---|
| First line, variable byte span starting at 0 | `%d`, signed decimal | Local 32-bit count; summed into allocation count | `00470823..00470849`, `0047093B..00470965` |
| Row token 1; variable position and length | Unbounded `%s` in original | Member `+00`, zeroed 16-byte key region then `_strlwr` | `004709A0`, `004709BF..004709EA` |
| Row token 2; variable byte position | `%d`, signed decimal | Member `+14:u32` containing the scanned signed value's bits | `004709BA..004709C6` |
| Row token 3; variable byte position | `%d`, signed decimal | Member `+18:u32` containing the scanned signed value's bits | `004709B7..004709C6` |
| Absent from serialized row | No bytes | Member `+10:u32` = owning PIX enumeration ordinal | `00470A05..00470A09` |

Exact token byte offsets for ten reviewed records are published in `corpus.json`
(`line_offset`, `name_offset`, `offset_token_offset`, `size_token_offset`). They
are specimen offsets, not constant structure offsets. The independent parser
also returns these positions. No opaque serialized fields were found in this
variant; unsupported extensions/variants must be rejected, not filled in by guess.

## Association and ordering

`00470660` enumerates registered resource **keys** matching `*.pix`, through
`004B2AC0`. This is not a raw OS directory scan. It copies each 16-byte key into
a 0x18-byte PAK row and replaces the **first** dot and following bytes with
`.pak\0` (`004706EF..00470700`). It reconstructs the `.pix` key the same way on
each parsing pass. No backing path, PAK ordinal or group marker is serialized
in the PIX text. All rows in one PIX are assigned that index's one PAK row.
The backing logical name is subsequently resolved through the loaded-file and
registered-source routes; it need not be a physical neighboring file at runtime.
The reference reader's extracted-file adapter resolves a same-directory,
case-insensitive sibling and rejects ambiguous names or escaping symlinks.

Rows are ingested in per-PIX source order, then all indexes' runtime member rows
are globally `qsort`ed with stride 0x1C and callback `00470CA0`. This can intermix
PAKs. Within all observed PIX files offsets are nondecreasing; this is corpus
behavior, not an original validation rule or a required parser constraint.

## PAK byte addressing

PAK has no additional package header interpreted by these functions. It is the
whole logical PAK resource byte stream returned by `00470070`. Indexed acquire
returns **base + member.offset** (`00470BAA..00470BB2`). Offsets are absolute
from the first byte of that logical stream, including offset zero. They are
not relative to the ZFS's physical file offset, a directory, or a payload region.

A byte length at `member+18` is returned by `00470C40` but is **not used to bound
acquisition**. No separate expanded length, compression flag, member header
skip or decompressor exists on the indexed acquisition path. Every measured
PAK is completely tiled by the declared byte ranges with no holes or overlaps.
Thus stored member length equals the exposed byte-span length here. Encoded
GEO/image contents retain their own formats; this does not assert that VQM
pixels are uncompressed.

The *outer ZFS record* containing a PIX/PAK may be compressed: this corpus has
405 raw, 574 flag-2 and 2,537 flag-4 records across the 3,516 PIX/PAK files.
Authentication decoded those records with the pinned historical ZFS extractor
and system `liblzo2`; this is explicitly a separate layer. Nothing here proposes
a new PIX-level compression scheme or independently validates all ZFS decoding.

## Limits, variants and safe-reader policy

Original code has no visible name-width conversion limit, negative-count/range
checks, sum/product overflow checks, PAK byte-range checks or duplicate rejection.
`%d` is decimal, including leading zeros, not Python base-zero syntax. Scanning
can accept trailing junk after required conversions; only the declared number
of rows is processed. Signed counts are subsequently tested using unsigned
branches. Malformed files can exceed allocations, overrun names, leak buffers
or continue after diagnostics; these are not supported interchange variants.

The lower loaded-file route rejects registered sizes <=0 and uses 16-bit cache
references. Its header+payload size check against `0x7FFF8` calls the returning
reporter, so it is a diagnostic, not an unconditional enforced maximum. Indexed
PAK references and pointer arithmetic are 32-bit with no visible saturation or
wrap guard. Allocation failures do terminate through the separate out-of-memory
helper. See the control-flow report for empty-index and two-pass failure limits.

The safe reader deliberately requires ASCII flat names of 1..15 bytes, exact
count, three full tokens per row, LF termination, no NUL, nonnegative signed-32
decimal integers, bounded allocations and ranges inside a stable byte snapshot.
Limits: 16 MiB index, 250,000 entries, 128 MiB PAK. These are independent limits,
not claimed retail limits. It rejects unsupported trailing data and ambiguous
keys, accepts zero lengths and overlapping valid spans, and never publishes
payload bytes. An empty index is `0\n`; an empty byte file is malformed. Integer
arithmetic uses Python integers and subtraction-based bounds checks. The original
DWORD comparator uses little-endian 32-bit loads at offsets 0,4,8,12; the runtime
fields are 4-byte aligned within their arrays, while member payload offsets need
no alignment. No other PIX/PAK variant was observed in the audited base-game
root. Nitro Pack and unrelated files merely sharing these extensions are outside
this specification.
