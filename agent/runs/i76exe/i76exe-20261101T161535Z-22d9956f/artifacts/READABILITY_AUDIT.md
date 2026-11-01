# Ghidra readability audit

A private disposable Ghidra 12.1.4 PUBLIC project was imported from `i76_mission_v97_verified_names.gzf` (SHA-256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`). The imported program reports retail executable SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`, and audited body bytes match the separately hashed PE. The user's source database/export was not edited.

## Applied changes: nine default parameter names

| Original function / address | Before | After |
|---|---|---|
| `open_resource_file_into_memory` / `0046FFC0` | `char *param_1` | `char *logical_name` |
| `load_resource_stream_into_loaded_cache` / `00470070` | `char *param_1` | `char *logical_name` |
| `resource_exists_in_cache_or_search_paths` / `00470340` | `char *param_1` | `char *logical_name` |
| `load_indexed_resource_record_payload` / `00470B20` | `void *param_1` | `void *logical_name` |
| `resolve_virtual_filename_to_mounted_source` / `004B2E00` | `undefined4 *param_1` | `undefined4 *key16` |
| `load_registered_resource_payload` / `004B3030` | `param_1, param_2, param_3, param_4` | `logical_name, out_size, destination, destination_capacity` |

The actual post-change decompiler now reads, for example:

```c
pcVar3 = resolve_virtual_filename_to_mounted_source((undefined4 *)logical_name);
*out_size = dwBytes;
if (destination_capacity < (int)dwBytes) { /* close and fail */ }
```

This replaces anonymous inputs with the three distinct responsibilities of the read API: identity, output length, and optional destination/capacity. It does not resolve every `pcVar` local or remove old type artifacts. Applied return and argument **types are unchanged**. Proposed byte-pointer prototypes and structures remain in `resource_design.h` for review.

`PilotCParameterNames.java` defaults to dry run. It verifies executable identity, PE32 pointer size, all provided audited code-range hashes, exact existing function names/counts, and `SourceType.DEFAULT` with `param_N` names before any mutation. Already-applied names are accepted for idempotence. A conflicting analyst name causes rejection rather than overwrite. Changes run in a transaction and roll back on failure. No original function name, global, comment, data type or local variable was changed.

Results captured in `evidence/ANNOTATION_VALIDATION.txt`:

- Dry run: 9 eligible, 0 already, 0 errors.
- Apply: 9 changed, 0 already, 0 errors.
- Repeat: 0 changed, 9 already, 0 errors.
- Function count remained 2,335 in each pass.
- All 23 original audited ranges were unchanged in the before/after exports; the final export additionally audits `0046FEE0` (24 total PE-matching ranges).

## Preserved disagreements and limits

The v97 database already names `004B2E00` `resolve_virtual_filename_to_mounted_source`, whereas the public May snapshot and older comments describe a registered-record lookup. This run confirms the v97 semantic direction from return-address arithmetic; it preserves both the existing function name and its historical comments. Similarly, `004702D0` is named as a canonicalizer but its code evicts a loaded-cache entry. The “used bytes” global behaves as a record count. These findings are documented, not silently imposed as broad migrations.

No common Ghidra migration was changed or applied. No decompiler prettiness score is claimed: the bounded improvement is nine named inputs, with before/after prototype evidence in `STATIC_AUDIT.tsv` and `STATIC_AFTER.tsv`. Full listings remain private. Structural recovery is expressed as small C layouts with compile-time offset/size checks; applying them to the database would need separate alias and use-site reconciliation.
