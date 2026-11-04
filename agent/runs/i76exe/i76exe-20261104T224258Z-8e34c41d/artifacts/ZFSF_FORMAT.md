# ZFSF v1 on-disk contract

Evidence tier: retail binary static analysis plus authenticated base-game corpus. No retail program paths were executed. All addresses refer to executable SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`, imported from the supplied v100 GZF in read-only Ghidra 12.1.4 with reanalysis disabled. `../evidence/instructions.json` authenticates function extents and reviewed assembly against the original PE; exact bytes and full decompilation remain private. Machine-readable layouts are in `fields.json`.

## Header: 0x1C bytes, little endian

| Offset | Width | Disk representation | Meaning and executable use |
|---|---:|---|---|
| 00 | 4 | bytes | Exactly `ZFSF`, checked bytewise |
| 04 | 4 | u32 | Version, must equal 1 |
| 08 | 4 | u32 | Name width, must equal 16 |
| 0C | 4 | u32 | Table capacity, must equal 100 |
| 10 | 4 | u32 bits; signed runtime arithmetic | Declared record/allocation count; allocates count*0x24 bytes and trunc_signed(count/100)+1 table pointers |
| 14 | 4 | u32 | XOR key copied into archive handle +1C; applied to logical bytes after decoding |
| 18 | 4 | u32 bits; signed CRT long offset | Absolute first table offset; passed directly to fseek |

`004B9800..004B9AC5` is the verified open function (710 bytes). It reads exactly 28 bytes and rejects signature/version/name-width/capacity mismatches. Name width and capacity are fixed validations, not supported variable-layout selectors. Creator `004B95F0` writes those constants and one zero-filled table at offset 28, even for count zero. There are no unexplained header bytes to call reserved. The header contains no demonstrated checksum.

## Directory table: 0xE14 bytes

At an absolute table offset, +00 is a little-endian u32 next-table offset; +04 contains 100 records of 0x24 bytes. Zero next pointer terminates. Tables need not be contiguous. The original always reads the complete 3,604-byte table, including unused slots.

For each table, retail scans until the first name byte is zero or 100 slots have been visited. It excludes records with `record[0x20] & 1`, copies each other entire 36-byte record into its live array, and follows the next pointer. An empty slot terminates only that table's record scan; it does not terminate the chain. Inactive entries do not terminate scanning. Retail then replaces the handle's count with the live count and requires the number of traversed tables to equal trunc_signed(header.count/100)+1. It does **not** check that discovered nonempty records equal the declared allocation count. It does not guard live-array overflow, cycles, repeated pointers or overlapping tables.

Thus an exact multiple of 100 expects an extra table; this differs from a generic ceil(count/100) layout. The authenticated archive has count 6,116, 62 tables, 84 zero slots at the end, no inactive records and no nonempty entry following a table terminator. Its first table is at 28, last at 55,517,810. The 62 complete table extents fit the file.

## Record: 0x24 bytes

| Offset | Width | Representation | Meaning |
|---|---:|---|---|
| 00 | 16 | char bytes | NUL-terminated name in observed corpus; comparison ignores case and bytes after first NUL |
| 10 | 4 | u32 disk bits / signed fseek offset | Absolute stored payload offset |
| 14 | 4 | u32 | Identifier; all corpus values equal original directory ordinal 0..6115; open/read preserve but do not use it for addressing |
| 18 | 4 | u32 bits / signed comparisons and CRT size_t | Stored byte length, before decompression |
| 1C | 4 | u32 | Time-like word, copied but not interpreted by reviewed reader; historical extractor calls it Unix timestamp; epoch/producer semantics remain unresolved |
| 20 | 4 | u32 bits | Packed flags/decoded length; low byte contains flags; upper bits are used through **signed arithmetic right shift by 8** when bits 1 or 2 are set |

Time-like values range 867,972,550..887,417,580 in this specimen. That correlation does not establish a timestamp type. No field is silently labeled reserved. Identifier purpose beyond observed ordinal equality is unresolved.

If `(flags & 6)==0`, logical size is stored length; upper bits of +20 are ignored by retail. Otherwise logical size is `(int32_t)flags_size >> 8`, not an unconditional unsigned 24-bit extraction. Values with bit 31 set are negative under retail's size query. The bounded profile rejects them; all observed compressed sizes are positive, at most 400,748 bytes.

`004B9AD0` forwards to CRT `_stricmp`. Retail qsorts copied live records with that callback and bsearches by requested name. It does not lowercase stored names or implement first/last-record duplicate precedence. Equal-key qsort stability and bsearch winner were not established. Disk order and identifier are not lookup priorities. Nonterminated names can escape record bounds in retail comparison; the independent reader rejects them. High-bit/locale behavior is outside the validated ASCII profile.

## Disk versus runtime

Archive handle is a **0x2C-byte allocation**, not the disk header: +00 FILE*, +04 a nominal 16-byte filename region, +14 expected table count, +18 live count (initially declared count), +1C XOR key, +20 retained declared allocation count, +24 table-offset array pointer, +28 copied/sorted live-record array pointer. Open's filename copy has no bounds check; the nominal region is not an established safe path limit. Directory records retain the disk layout when copied, but now reside in a sorted heap array.

Registered keys (0x30), mounted sources (0x10C) and loaded-file headers (0x24) are different runtime objects. See `RESOURCE_SOURCE_SELECTION.md` and `RESOURCE_LIFETIME.md`. Do not serialize those structures as ZFS directory entries.

## Bounded reader profile and variants

The independent reader requires the fixed header, positive valid first table, full in-range nonoverlapping tables, bounded counts, exact discovered count agreement, chain termination, zero empty slots and no later occupied slots after a terminator. It checks every nonempty record's payload extent, including inactive metadata. This is deliberately stricter than retail; old stale tombstones or nonzero ignored slots can be rejected even where retail would skip them. Limit policies and diagnostics are in the handoff.

Exact same-span aliases with equal packed decoding metadata are retained and reported; partial overlaps, incompatible same-span decoding and metadata/payload overlaps are rejected. This distinguishes representable shared bytes from unsafe overlap without claiming to know producer intent. Duplicate names remain enumerable; implicit ambiguous reads fail. There are no such cases in this archive. Only this v1 base-game specimen is authenticated; no Nitro Pack, other release or update-writer variant is established.
