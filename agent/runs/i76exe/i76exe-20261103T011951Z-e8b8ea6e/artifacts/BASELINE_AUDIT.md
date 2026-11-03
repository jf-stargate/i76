# Private v99 baseline audit

Pinned accepted main: `9576fc573964bed624a08d878886ccad40a63d7a`; protocol 1.0.4. Track i76exe; narrow terrain work plus migration coverage. No prior migration was applied. PRs #101–#105 were verified merged; #106 remains an unaccepted proposal at `adf550a899579aa5592c13ab96ee26648e616793`. This run changes no canonical reference, promotion or baseline identity record.

The exact supplied **i76_mission_v99_verified_names.gzf** is 6,500,304 bytes, SHA-256 **ca211238170806eda27a2b4ecf6aee2192abb69df27fe56f106b455ac75bc710**. The original retail executable matches SHA-256 **bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3** and MD5 **a640ea0097dbb62e0c77b7f2847c7161**. The export was imported into a new disposable project with no auto-analysis. Original export and live GUI database were not modified.

Ghidra 12.1.4, OpenJDK 27-ea, program i76.exe, language x86:LE:32:default, base 00400000, 4-byte pointers. Actual counts: **2,102 defined +235 external =2,337 total functions**, **27,100 symbols**, **387 type entries**, **3,402 address/comment-kind rows**. All 2,102 defined body ranges and SHA-256 hashes independently match PE section-mapped original bytes. Function names/source markers, full signatures/parameter storage/return storage, external functions, symbol provenance, structure components, all defined data, comments and selected instructions/C were captured privately. Counts and 12 compared structures are in `baseline_inventory_summary.json`; 16 selected function/body/signature rows are published in `selected_functions.tsv`.

## Coverage of accepted operations

`migration_coverage.tsv` has **173 historical operation rows**, plus **10 individually retained resource deferrals**. These are provenance/action records, not unique addresses or applied-edit counts.

| History | ALREADY | MISSING | PRESERVE | CONFLICT |
|---|---:|---:|---:|---:|
| v99 | 85 | 0 | 1 | 0 |
| v100 | 0 | 14 | 0 | 0 |
| v101 | 0 | 26 | 0 | 0 |
| v102 | 0 | 16 | 0 | 0 |
| consolidation | 25 | 5 | 0 | 1 |
| **Historical total** | **110** | **61** | **1** | **1** |

The extra ten DEFER rows preserve the accepted five resource-type and five propagated-return deferrals. Two new data corrections were tested separately; they are not added to the historical totals. The spacing correction resolves the historical conflict on the disposable derivative only.

- **v99:** all 85 successful historical results are present. Eight structure definitions independently match component layouts, not merely names/sizes. One existing repeatable comment at 006543AC remains preserved.
- **v100–v102:** their categories and typed targets are absent. v100/v101 read-only previews report 14/26 eligible operations. v102 preview stops because its required v101 world type is missing; the sixteen historical targets were independently checked in the captured types/data/signatures. Existing semantic function aliases alone do not establish these type migrations. No prerequisites were staged during this audit.
- **Consolidation:** four type layouts and eleven function-signature results are semantically present, including normal EAX and packed stack storage, the live VM cursor fields and resource input names. Six mapped data results are present; spacing remains int. Four comment cores are semantically equivalent. Five comments have shortened summaries but omit substantive qualifications from the accepted migration, so they are **MISSING (partial)** rather than credited as complete annotations: 00493550, 004931C0, 00414670, 0046FFC0 and 004702D0. Existing summaries are preserved; additions are not part of this terrain pass.

The unmodified consolidation preview reports 16 ALREADY, 6 CONFLICT, 9 eligible comments. That is **not** the audited semantic count: TER_Page and VmNode fail Ghidra `isEquivalent`, yet recursive comparison verifies identical sizes, offsets, field names, array dimensions and pointed-to component types. Component commentary and fixed-width pointer presentation differ. Three dependent VM signatures are then skipped by that preview, even though the actual captured signature semantics are present. The nine comment strings differ verbatim; four retain equivalent core meanings and five lack specified qualifications. The crosswalk records both cases without forcing historical text onto v99.

All existing analyst symbols and comments survive the two corrections. **Provenance remains unresolved:** USER_DEFINED, matching names, matching layouts and even migration-like comments do not establish who authored an annotation or which script version executed. This file is a measured-state audit, not a reconstructed execution log.

## Evidence and governance limits

`capture_validation.json` contains digests/byte lengths of private tables and a deterministic aggregate file-index digest for each capture. Full C and complete tables remain private. `source_digests.json` pins accepted tooling/policy/report contents. `bootstrap.json` records GitHub enforcement: active ruleset 25664125, PR and integrity required, zero formal approvals, no bypass, manual acceptance still required. Effective branch rules were fetched independently; classic-protection API returned integration 403, so no absence claim is made about that separate endpoint.

This run provides no new VM/resource behavioral result, no full-game execution, no original source declaration recovery and no automatic baseline promotion. See TERRAIN_AUDIT.md, VALIDATION.md and DOCUMENTATION_IMPACT.md.
