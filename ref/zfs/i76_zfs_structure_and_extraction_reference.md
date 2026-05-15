# Interstate ’76 ZFSF Archive Structure and Extraction Reference

This page documents the current reverse-engineered understanding of the Interstate ’76 `I76.ZFS` archive format and the extraction/decompression process. It is intended to be both human-readable and machine-actionable enough to support independent extractor implementations, regression tests, and future project handoff.

Status: reverse-engineered from the retail binary and validated against the retail `I76.ZFS` corpus.

## Scope

This document covers:

- The `ZFSF` archive container format used by Interstate ’76.
- Header, directory-table, and record layouts.
- Compression flag semantics.
- The extraction/decompression pipeline.
- The embedded LZO modes used by the game.
- Implementation notes for a standalone extractor.

This document does not cover:

- `ZIX` path/index semantics in full.
- `PIX`/`PAK` embedded resource indexing in full.
- Higher-level resource formats such as `GEO`, `VDF`, `VTF`, `TMT`, `M16`, `VQM`, or `CBK`, except where needed to describe archive extraction.

## Terminology

`ZFS` refers to the archive file, usually `I76.ZFS`.

`ZFSF` is the four-byte magic value at the start of the archive. This is an internal Activision/game archive format and is unrelated to Solaris/OpenZFS.

`DTable` means directory table. A ZFSF archive stores records in one or more linked directory tables.

`stored_size` means the compressed or raw byte count physically stored in the archive.

`logical_size` means the expected output size after decompression, or the raw output size for uncompressed records.

`record name` means the archive key stored in the 16-byte `name` field of each record.

## Retail Corpus Snapshot

The retail `I76.ZFS` observed in this project has the following high-level properties:

```text
+-----------------------------+-----------------+
| Field                       | Value           |
+-----------------------------+-----------------+
| Archive magic               | ZFSF            |
| Version                     | 1               |
| Record name size            | 0x10 / 16 bytes |
| Records per directory table | 100             |
| Raw record count            | 6116            |
| Live record count           | 6116            |
| XOR key                     | 0               |
| Directory table count       | 62              |
| Uncompressed records        | 493             |
| LZO1X records / flag 0x02   | 1526            |
| LZO1Y records / flag 0x04   | 4097            |
+-----------------------------+-----------------+
```

These values are not necessarily universal for every archive created by the engine, but they are confirmed for the retail archive used in the current analysis.

## Binary Function Map

The following function names are the current project names for the relevant archive and decompression path in `i76.exe`:

```text
+----------+--------------------------------------------+
| Address  | Current name                               |
+----------+--------------------------------------------+
| 004b95f0 | create_empty_zfsf_archive_file             |
| 004b9740 | open_zfsf_archive_file                     |
| 004b9800 | open_zfsf_archive                          |
| 004b9af0 | close_zfsf_archive                         |
| 004b9ad0 | compare_zfsf_record_name_cstring           |
| 004b9b40 | lookup_zfsf_record_logical_size            |
| 004b9ba0 | read_zfsf_record_to_buffer_bool            |
| 004b9bd0 | read_zfsf_record_payload                   |
| 004b9db0 | read_zfsf_record_allocated_payload         |
| 004b9fc0 | zfsf_decompress_record_payload_by_lzo_mode |
| 004ba980 | lzo_init_embedded_library                  |
| 004ba6d0 | lzo_runtime_config_selftest                |
| 004ba9e0 | lzo_compute_alignment_gap                  |
| 004baa00 | lzo1y_decompress_unsafe                    |
| 004babd8 | lzo1x_decompress_unsafe                    |
| 004badb0 | lzo_adler32                                |
+----------+--------------------------------------------+
```

Do not treat the following interior/probe addresses as separate decompression routines:

```text
004ba220
004ba4d0
004ba6f0
004bac80
```

## Archive Layout

A ZFSF archive begins with a fixed 0x1c-byte header. The header points to the first directory table. Directory tables form a linked list using absolute file offsets.

```text
+-----------------------------+
| zfsf_header                 |
+-----------------------------+
| payload bytes / padding     |
+-----------------------------+
| zfsf_dtable 0               |
+-----------------------------+
| payload bytes / padding     |
+-----------------------------+
| zfsf_dtable 1               |
+-----------------------------+
| ...                         |
+-----------------------------+
```

Directory tables and payloads are not required to be contiguous in semantic order. Record payload locations are specified by absolute file offsets in each record.

## Header Layout

```c
struct zfsf_header {
    char     magic[4];              // +0x00 "ZFSF"
    uint32_t version;               // +0x04 must be 1
    uint32_t record_name_size;      // +0x08 must be 0x10
    uint32_t records_per_dtable;    // +0x0c must be 100
    uint32_t record_count;          // +0x10 raw directory record count
    uint32_t xor_key;               // +0x14 observed 0 in retail I76.ZFS
    uint32_t first_dtable_offset;   // +0x18 absolute file offset
}; // size 0x1c
```

Validation rules observed in the game path:

- `magic` must be `ZFSF`.
- `version` must be `1`.
- `record_name_size` must be `0x10`.
- `records_per_dtable` must be `100`.
- `first_dtable_offset` is an absolute file offset to the first directory table.

## Runtime Archive Object

The game constructs an in-memory archive object approximately like this:

```c
struct zfsf_archive {
    FILE    *fp;                    // +0x00
    char     path_or_name[0x10];    // +0x04
    uint32_t dtable_count;          // +0x14 = record_count / 100 + 1
    uint32_t live_record_count;     // +0x18
    uint32_t xor_key;               // +0x1c
    uint32_t raw_record_count;      // +0x20
    uint32_t *dtable_offsets;       // +0x24
    zfsf_record *records;           // +0x28
}; // allocated size 0x2c
```

This is a runtime structure, not an on-disk structure. It is useful for writing source-compatible extractors because it reflects how the binary reads and normalizes the archive state.

## Directory Table Layout

```c
struct zfsf_dtable {
    uint32_t next_dtable_offset;    // +0x00 absolute file offset, 0 at end
    zfsf_record records[100];       // +0x04
}; // size 0xe14
```

Each directory table contains 100 record slots. The header’s `record_count` is the raw number of record entries to consider across the linked tables. The game computes a dtable count as:

```c
dtable_count = record_count / 100 + 1;
```

For the retail archive, `record_count = 6116`, so the game expects 62 tables.

## Record Layout

```c
struct zfsf_record {
    char     name[0x10];            // +0x00 16-byte archive key / C-string-ish name
    uint32_t file_offset;           // +0x10 absolute payload offset
    uint32_t record_id;             // +0x14 sequential ID/index
    uint32_t stored_size;           // +0x18 raw bytes read from archive
    uint32_t unix_timestamp;        // +0x1c plausible file timestamp
    uint32_t flags_size;            // +0x20 low byte flags/compression, upper 24 bits logical size
}; // size 0x24
```

The `name` field is 16 bytes. Names are generally treated as C strings for comparison, but robust tools should preserve all 16 bytes in machine-readable output and also provide a trimmed display name.

The `file_offset` field is absolute, not relative to the table or header.

The `stored_size` field is the exact number of bytes to read from `file_offset`.

The `flags_size` field packs both compression flags and the logical output size:

```c
compression_or_flags = flags_size & 0xff;
logical_size         = flags_size >> 8;
```

## Record Flags

```text
+--------------+----------------------------------------+
| Flag / value | Meaning                                |
+--------------+----------------------------------------+
| 0x01         | inactive/deleted/tombstone marker      |
| 0x02         | payload compressed with embedded LZO1X |
| 0x04         | payload compressed with embedded LZO1Y |
+--------------+----------------------------------------+
```

Current interpretation:

- If bit `0x01` is set, the record is filtered out as inactive/deleted.
- If flag `0x02` is set, decompress using the game’s LZO1X routine.
- If flag `0x04` is set, decompress using the game’s LZO1Y routine.
- If neither `0x02` nor `0x04` is set, treat the payload as uncompressed.
- The retail archive did not require XOR decoding because `xor_key == 0`.

A defensive extractor should detect and report unexpected flag combinations rather than silently guessing.

## Extraction Algorithm

The archive extraction process is:

1. Open the archive as binary.
2. Read and validate the 0x1c-byte header.
3. Follow the linked directory tables beginning at `first_dtable_offset`.
4. Read up to `record_count` raw record entries.
5. Filter out tombstone records where `flags_size & 0x01` is nonzero.
6. For each live record:
   1. Seek to `record.file_offset`.
   2. Read exactly `record.stored_size` bytes.
   3. Determine `logical_size = record.flags_size >> 8`.
   4. Determine `mode = record.flags_size & 0xff`.
   5. If mode has LZO1X flag `0x02`, decompress as LZO1X.
   6. Else if mode has LZO1Y flag `0x04`, decompress as LZO1Y.
   7. Else treat bytes as raw/uncompressed.
   8. Verify decompressed length equals `logical_size`.
   9. Write the decoded payload to the selected output location.
7. Emit a manifest with raw and decoded metadata for every record.

## Pseudocode

```python
def parse_zfsf_header(f):
    data = f.read(0x1c)
    magic, version, name_size, per_table, record_count, xor_key, first_table = unpack_header(data)

    assert magic == b"ZFSF"
    assert version == 1
    assert name_size == 0x10
    assert per_table == 100

    return {
        "record_count": record_count,
        "xor_key": xor_key,
        "first_dtable_offset": first_table,
    }


def iter_raw_records(f, header):
    remaining = header["record_count"]
    table_offset = header["first_dtable_offset"]

    while table_offset != 0 and remaining > 0:
        f.seek(table_offset)
        next_table = read_u32le(f)

        for slot in range(100):
            if remaining <= 0:
                break

            rec = read_zfsf_record(f)
            remaining -= 1
            yield rec

        table_offset = next_table


def decode_record(f, rec):
    mode = rec.flags_size & 0xff
    logical_size = rec.flags_size >> 8

    if mode & 0x01:
        return None

    f.seek(rec.file_offset)
    stored = f.read(rec.stored_size)

    if mode & 0x02:
        out = lzo1x_decompress(stored, logical_size)
    elif mode & 0x04:
        out = lzo1y_decompress(stored, logical_size)
    else:
        out = stored

    if len(out) != logical_size:
        raise ValueError("decoded size mismatch")

    return out
```

## LZO Details

The game embeds an old LZO implementation identified as LZO 1.00. The startup path includes a runtime/self-test with Adler check value:

```text
0x918c45aa
```

The wrapper treats return code `0` as success.

Observed/decompiled return-code meanings:

```text
+-------------+----------------------------+
| Return code | Meaning                    |
+-------------+----------------------------+
| 0           | success and input consumed |
| -4          | input overrun              |
| -8          | input not fully consumed   |
+-------------+----------------------------+
```

The binary includes two relevant unsafe decompression routines:

```text
+-------+----------+-------------------------+
| Mode  | Address  | Current name            |
+-------+----------+-------------------------+
| LZO1Y | 004baa00 | lzo1y_decompress_unsafe |
| LZO1X | 004babd8 | lzo1x_decompress_unsafe |
+-------+----------+-------------------------+
```

The disassembly signatures differ in ways that helped distinguish the modes:

```text
+-------+---------------------------------------------------------------------+
| Mode  | Distinguishing behavior                                             |
+-------+---------------------------------------------------------------------+
| LZO1Y | M2 offset uses op - 0x401 scale 4 and token length split token >> 4 |
| LZO1X | M2 offset uses op - 0x801 scale 8 and token length split token >> 5 |
+-------+---------------------------------------------------------------------+
```

For a practical extractor, using a system `liblzo2` binding for validation is acceptable, but a source-faithful implementation should preserve the binary’s exact mode dispatch and error handling.

## Machine-Readable Manifest Fields

A durable extractor should emit at least the following fields per record:

```json
{
  "record_index": 0,
  "record_id": 0,
  "name_raw_hex": "00000000000000000000000000000000",
  "name": "example.ext",
  "file_offset": 0,
  "stored_size": 0,
  "logical_size": 0,
  "flags_size": 0,
  "flags": 0,
  "inactive": false,
  "compression": "none|lzo1x|lzo1y|unknown",
  "unix_timestamp": 0,
  "decoded_size": 0,
  "decoded_sha256": "",
  "stored_sha256": "",
  "output_path": "",
  "status": "ok|inactive|decode_error|size_mismatch|unsupported_flags"
}
```

Recommended archive-level manifest fields:

```json
{
  "format": "I76_ZFSF",
  "source_archive": "I76.ZFS",
  "magic": "ZFSF",
  "version": 1,
  "record_name_size": 16,
  "records_per_dtable": 100,
  "record_count": 6116,
  "xor_key": 0,
  "first_dtable_offset": 0,
  "dtable_count_observed": 62,
  "live_record_count": 6116,
  "compression_counts": {
    "none": 493,
    "lzo1x": 1526,
    "lzo1y": 4097
  }
}
```

## Output Path Policy

The ZFSF record name is only 16 bytes, so it is not a full filesystem path. In the game, logical path resolution also involves `ZIX`, resource search paths, and embedded `PIX`/`PAK` containers. A standalone ZFS extractor should not invent paths that are not present in the archive record itself.

Recommended extraction layout:

```text
decoded/
  <record_index>_<record_name>
raw/
  <record_index>_<record_name>.stored
manifest.json
records.tsv
errors.tsv
```

For example:

```text
decoded/000123_PP11BDY1.VQM
raw/000123_PP11BDY1.VQM.stored
```

This avoids collisions and preserves stable indexing even if names repeat.

## Implementation Notes

A robust extractor should:

- Treat all integer fields as little-endian.
- Treat `file_offset` and `first_dtable_offset` as absolute archive offsets.
- Preserve raw names and decoded display names separately.
- Filter tombstones using bit `0x01`.
- Verify decoded size against `logical_size`.
- Hash both stored and decoded payloads for reproducible testing.
- Preserve unsupported or unexpected flag combinations in the manifest.
- Avoid assuming records are stored in directory order.
- Avoid assuming every 16-byte name is unique.
- Avoid assuming timestamps are required for extraction correctness.
- Avoid writing directly to record names without collision handling.
- Keep raw stored payloads optionally available for decompressor regression testing.

## Known Good Extraction Summary for Retail I76.ZFS

A correct extractor for the retail archive should reproduce:

```text
record_count:        6116
live records:        6116
directory tables:    62
xor_key:             0
uncompressed:        493
LZO1X records:       1526
LZO1Y records:       4097
```

A full validation pass should report no decompression failures and no decoded-size mismatches.

## Relationship to Higher-Level Resource Extraction

ZFSF extraction only produces decoded record payloads. Many game assets require subsequent container or format parsing:

```text
I76.ZFS
  -> ZFSF record payloads
    -> PIX/PAK embedded resources
      -> GEO, VDF, VTF, TMT, MAP, M16, VQM, CBK, ACT, etc.
```

For the vehicle pipeline, the current extraction chain is:

```text
VCF
  -> VDF + VTF + optional WDF references
VDF
  -> VGEO/SOBJ part hierarchy and GEO basenames
VTF
  -> TMT/MAP material slots
TMT
  -> MAP/M16/VQM frame basenames
VQM + CBK
  -> decoded indexed texture pixels
ACT/palette
  -> indexed texture RGB preview/export
```

ZFSF extraction is therefore a necessary but not sufficient step for complete asset reconstruction.

## Current Confidence

High confidence:

- Header layout.
- Directory-table layout.
- Record layout.
- Absolute payload offsets.
- `flags_size` packing.
- Tombstone flag `0x01`.
- LZO1X flag `0x02`.
- LZO1Y flag `0x04`.
- Retail compression counts.
- LZO mode function identities.

Medium confidence:

- `unix_timestamp` interpretation as a Unix-like timestamp.
- Exact intended behavior for nonzero `xor_key` archives, since retail `I76.ZFS` has `xor_key == 0`.
- Exact semantics of unsupported flag combinations not observed in retail.

Low confidence / future work:

- Full `ZIX` logical path reconstruction.
- Any write/update semantics for archives created through the `rb+` code path.
- Non-retail or development archive variants.
