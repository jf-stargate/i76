# Authenticated base-game corpus

Evidence tier: complete safe decoding/hash survey of one base-game archive. Retail code was not executed. Original archive, extracted resources, ZIX, inventory and bulk audit remain private. Machine-readable compact results: `../evidence/corpus.json`, `zix.json`, `provenance.json`, `historical_differences.json`.

## Identity and scope

`orig/I76.ZFS`: 55,535,506 bytes; SHA-256 `0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d`. Executable and supplied GZF match all assignment hashes. Private extracted root is `/media/neon-remote/prj/i76/zfs/resources`, containing 6,116 files. Its prior manifest is identified by SHA-256 `3112f2579f1ef811ff23c1747b602aa203e4c791711a4e26b896c2d7fb658c35`; all extracted identities were freshly recomputed in the full comparison. No extracted bytes were trusted as a format oracle.

Historical comparator is the pinned `scripts/game/i76_zfs_extract.py`, SHA-256 `7445851883a519606f77bc864ff585e217032788b75773b79fa76f77bada893f`, identical to the local_history copy. It is imported directly without editing its methods or substituting this run's decoder. Both comparisons use system LZO 2.10, so they independently establish the ZFS wrapper/index interpretation, **not two independent codec implementations**. Algorithm identity is separately grounded in original decoder arithmetic. Exact backend ELF hash/ABI and comparator Git blob are recorded in provenance.

## Complete coverage

- 62 linked tables, 6,116 nonempty records, 6,116 active, 0 inactive;84 zero empty slots. Every name is terminated ASCII with zero post-NUL bytes. Every identifier equals directory ordinal and is unique.
- 493 raw, 1,526 LZO1X, 4,097 LZO1Y. Every compressed declared length is positive and every decoded actual length matches it. Raw records all have zero upper packed-size bits; their logical lengths are stored lengths.
- 6,116 successful independent normalized-key lookups/decodes;6,116 exact extracted-file hash matches;6,116 historical metadata and decoded-byte matches. No missing file, unsupported mode, decoder failure or mismatch.
- 132,540,591 logical bytes from 55,312,030 stored payload bytes. Largest logical record 400,748 bytes; largest stored record 312,480 bytes.
- Zero duplicate normalized keys, exact physical aliases, partial payload overlaps or payload/directory overlaps. Shared content at distinct locations is not equated with storage aliasing.
- The authenticated installed ZIX's 6,116 names/source 1 rows exactly match the archive live-key multiset. Membership agreement does not execute original selection or prove loading from any other mount.

| Family | Records | Raw | X | Y | Decoded and matched |
|---|---:|---:|---:|---:|---:|
| .act | 67 | 65 | 2 | 0 | 67 |
| .cbk | 53 | 0 | 53 | 0 | 53 |
| .cdf | 1 | 0 | 1 | 0 | 1 |
| .dat | 1 | 0 | 0 | 1 | 1 |
| .elt | 1 | 0 | 0 | 1 | 1 |
| .fsi | 13 | 0 | 12 | 1 | 13 |
| .gdf | 43 | 0 | 0 | 43 | 43 |
| .geo | 7 | 0 | 0 | 7 | 7 |
| .gpw | 123 | 22 | 80 | 21 | 123 |
| .hzd | 74 | 0 | 0 | 74 | 74 |
| .lum | 35 | 0 | 0 | 35 | 35 |
| .m16 | 225 | 0 | 102 | 123 | 225 |
| .map | 154 | 0 | 44 | 110 | 154 |
| .msk | 5 | 0 | 2 | 3 | 5 |
| .npt | 62 | 0 | 18 | 44 | 62 |
| .pak | 1758 | 4 | 492 | 1262 | 1758 |
| .pcx | 20 | 0 | 20 | 0 | 20 |
| .pix | 1758 | 401 | 82 | 1275 | 1758 |
| .rtm | 18 | 0 | 0 | 18 | 18 |
| .sdf | 371 | 0 | 7 | 364 | 371 |
| .tab | 29 | 0 | 13 | 16 | 29 |
| .tbl | 35 | 0 | 32 | 3 | 35 |
| .tmt | 104 | 0 | 57 | 47 | 104 |
| .vcf | 293 | 0 | 0 | 293 | 293 |
| .vdf | 48 | 0 | 0 | 48 | 48 |
| .vqm | 101 | 0 | 60 | 41 | 101 |
| .vtf | 117 | 0 | 0 | 117 | 117 |
| .wav | 507 | 1 | 449 | 57 | 507 |
| .wdf | 70 | 0 | 0 | 70 | 70 |
| .xdf | 23 | 0 | 0 | 23 | 23 |

This includes every PIX/PAK, all 74 HZD, 67 ACT, 35 LUM, 35 TBL, 53 CBK, 371 SDF and 293 VCF, plus all other encountered top-level families. PIX+PAK mode subtotals reproduce the preceding run's 405 raw, 574 X, 2,537 Y across 3,516 resources. No PIX syntax was re-investigated.

## Aggregate digest and repeatability

Private per-record inventory canonical-JSON SHA-256: `0b167b6639cdf107b685715afcdef571710fb224c1697023f74c7a633daae421`. `survey.py` fixes the encoding: original directory order; JSON list with sorted object keys and compact comma/colon separators; raw16-byte names represented as hex; no trailing newline in digest. Rows include original/normalized names, directory location, identifier/time/packed flags, stored extent and SHA-256, expected/mode/status, decoded result length/SHA-256. It is sufficient to regenerate and compare the digest without publishing the proprietary inventory.

The full saved inventory stays at a caller-selected private path, never under the checkout. Reproduction recomputes all bytes and this digest, verifies every audited PE byte/range, runs all synthetic cases and checks source hashes before/after. Public aggregates can be compared structurally with `--compare`; host-specific log paths/timings are excluded from deterministic equality.

Opposite-mode diagnostic:1,525 X records reject as Y;1 X stream decodes identically under both; all 4,097 Y reject as X. This crosscheck is corroboration only. The original dispatch decides mode before any specimen is tested.

## Historical disagreements and narrowing

There are **zero corpus disagreements**. That does not make the historical tool the full contract. Six independently run synthetic comparisons show version2 acceptance by the old parser versus rejection; an extra cyclic pointer ignored after its declared-count stop; flags 6 returned raw as an unknown mode rather than retail X; flag8 returned raw instead of the bounded reader's explicit rejection; nonzero XOR left unapplied; and an unsigned packed length where retail uses signed SAR. Detailed outcomes are in historical_differences.json.

Additional reviewed differences: historical clean_name strips paths/sanitizes spelling, and its parser follows declared count rather than the original per-table empty sentinel/live filtering/required-table logic. It does not diagnose duplicate normalized names or storage overlap. This run preserves raw fields, validates extents and uses explicit ambiguity policy. Empty-slot zero padding, exact count agreement, ASCII limits, overlap rejection and unsupported-flag rejection are safe-profile choices, not newly claimed retail rejection behavior.

Nonzero XOR, tombstones, aliases, corrupt tables/streams and duplicate archive names are tested synthetically; none occurs in this base-game specimen. The time word's producer meaning, all writer/update variants and non-ASCII naming remain unresolved. Nitro Pack was located as a separate private archive but not surveyed or generalized to. This run closes the inherited ZFS-wrapper dependency for the base-game PIX/PAK/HZD corpus while preserving the external LZO implementation boundary.
