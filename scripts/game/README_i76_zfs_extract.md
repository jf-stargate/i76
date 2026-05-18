# Interstate '76 ZFS Extractor

`i76_zfs_extract.py` extracts files from Interstate '76 `ZFSF` archives such as `I76.ZFS`.

The script parses the archive directory tables directly, optionally decompresses LZO-compressed records, writes extracted files to disk, and emits a JSON manifest plus a compact TSV record listing.

## Requirements

Python 3.8 or newer is required.

For normal decompression, the system LZO2 library must be installed:

```bash
sudo apt install liblzo2-2
```

No Python `lzo` package is required. The script loads `liblzo2` through `ctypes`.

## Basic usage

Extract the full archive:

```bash
python3 i76_zfs_extract.py orig/I76.ZFS   --zix orig/I76.ZIX   --out-dir scratch_data/i76_zfs_extract
```

Extract only level-adjacent resources:

```bash
python3 i76_zfs_extract.py orig/I76.ZFS   --zix orig/I76.ZIX   --out-dir scratch_data/i76_zfs_level_extract   --ext .tab .hzd .npt .rtm .lum .tbl .fsi .act
```

List the archive without extracting payloads:

```bash
python3 i76_zfs_extract.py orig/I76.ZFS   --zix orig/I76.ZIX   --out-dir scratch_data/i76_zfs_listing   --list-only
```

Write stored compressed/raw bytes instead of decompressed output:

```bash
python3 i76_zfs_extract.py orig/I76.ZFS   --out-dir scratch_data/i76_zfs_raw   --raw
```

## Output layout

A normal extraction writes:

```text
scratch_data/i76_zfs_extract/
  resources/
    extracted, decompressed files

  zfs_extract_manifest.json
    full archive metadata, record table, extraction report, errors, filters

  zfs_records.tsv
    compact tab-separated record listing
```

When `--raw` is used, payloads are written to:

```text
scratch_data/i76_zfs_extract/raw_payloads/
```

instead of `resources/`.

## Useful options

```text
--zix PATH
    Optional companion I76.ZIX path. The current extractor records ZIX metadata
    in the manifest, but extraction is driven by the ZFS directory tables.

--ext .tab .hzd ...
    Extract only records with matching extensions. Extensions are matched
    case-insensitively and may be written with or without the leading dot.

--include-inactive
    Include tombstone/inactive records. These are skipped by default.

--list-only
    Parse records and write manifest/listing without extracting file payloads.

--raw
    Write stored bytes exactly as found in the archive. This disables
    decompression for extracted payloads.

--no-lzo
    Do not load or use liblzo2. Compressed records will fail if extraction is
    attempted without `--raw`.

--collision-mode suffix|overwrite
    Controls filename collisions. The default is `suffix`, which appends the
    record number when a duplicate output filename would overwrite an existing
    file.

--json-out PATH
    Write the JSON manifest to an explicit path.

--allow-nonzero-xor
    Permit archives whose header has a nonzero XOR key. The script currently
    does not apply an XOR transform; this option is primarily for inspection.
```

## Archive format notes

The extractor targets the `ZFSF` archive format used by Interstate '76.

The recovered header layout is:

```c
struct zfsf_header {
    char     magic[4];             // "ZFSF"
    uint32_t version;              // usually 1
    uint32_t record_name_size;     // usually 0x10
    uint32_t records_per_dtable;   // usually 100
    uint32_t record_count;
    uint32_t xor_key;              // retail I76.ZFS uses 0
    uint32_t first_dtable_offset;
};
```

The archive directory is a linked list of dtables. Each dtable starts with a `uint32_t next_dtable_offset`, followed by `records_per_dtable` records.

Each record is:

```c
struct zfsf_record {
    char     name[16];
    uint32_t file_offset;     // absolute payload offset in ZFS
    uint32_t record_id;
    uint32_t stored_size;     // compressed/raw byte count
    uint32_t unix_timestamp;
    uint32_t flags_size;      // low byte mode/flags, upper 24 bits logical size
};
```

Known low-byte `flags_size` values:

```text
0x01  inactive/tombstone bit
0x02  LZO1X compressed
0x04  LZO1Y compressed
```

The decompressed size is stored in the upper 24 bits of `flags_size`.

## Typical level-resource workflow

For terrain and mission research, start with a filtered extraction:

```bash
python3 i76_zfs_extract.py orig/I76.ZFS   --zix orig/I76.ZIX   --out-dir scratch_data/i76_zfs_level_extract   --ext .tab .hzd .npt .rtm .lum .tbl .fsi .act
```

Then inspect:

```bash
less scratch_data/i76_zfs_level_extract/zfs_records.tsv
jq '.summary_selected_records.by_extension' scratch_data/i76_zfs_level_extract/zfs_extract_manifest.json
```

Current runtime-format evidence indicates that game-faithful terrain reconstruction should be based on BWD2 mission streams with `TDEF/ZMAP/ZONE` plus the terrain sidecar pages. Standalone `.TAB`, `.LUM`, and `.TBL` resources should be treated as supporting resources unless paired with the mission/sidecar loader path.

## Current limitations

The extractor is intentionally conservative.

It does not currently apply any nonzero XOR transform. Retail `I76.ZFS` uses `xor_key = 0`, so this is not needed for the known main archive.

The optional `I76.ZIX` file is recorded in the manifest but is not used for extraction. Current extraction is based on the ZFSF dtable chain.

Unknown compression modes are preserved as raw payloads and reported in the manifest rather than guessed.

## Quick sanity check

A successful full extraction of the known retail `I76.ZFS` should report thousands of records, for example:

```json
{
  "records": 6116,
  "selected": 6116,
  "extracted": 6116,
  "errors": 0
}
```

Filtered extractions will have lower `selected` and `extracted` counts.
