# I76 Ghidra export comparison — 2026-10-31

Comparison uses Ghidra 12.1.4 imported GZF files, no reanalysis, original retail executable metadata matches in both. The export archive timestamps are embedded ZIP DOS timestamps (timezone unspecified), not upload timestamps.

| Metric | `i76.exe(2).gzf` | `i76_mission_v97_verified_names(2).gzf` |
|---|---:|---:|
| Defined functions | 2332 | 2335 |
| User-defined function symbols | 2029 | 2034 |
| User-defined labels | 357 | 380 |

**v97 is later and richer:** its GZF embedded export entry is dated 2026-10-21 04:03:22 vs 2026-10-20 11:06:42 (ZIP local metadata). It exactly matches the v97 SHA-256 cited in accepted I76 research.

Across symbol address/type keys, **67 differences**: 36 function-related and 31 label-related. Of these 60 are revised, 4 added and 3 removed (a label may be replaced by a function at the same address).

The changes especially affect FSM command semantics, AI queue and predicate callbacks, world-object instance IDs, and globals. The full address-by-address reconciliation is in the companion TSV.

**Migration baseline:** use v97. Older GZF is retained as evidence only; do not merge its older symbol names indiscriminately.
