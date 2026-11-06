# Documentation impact — terrain coordinates and page continuity

Research identity: `i76exe-20261106T011534Z-5a34de5f`; i76exe, advisory TER/MLD/RES/GEO; base `7c315c103e6eda864f5bd9f3c3736a03b4c1fa7c`. Research-only PR pending at authorship. Binary, annotated v97 GZF and M06/CD M02 hashes are in `manifest.json` and `evidence/input_identities.json`.

**Disposition: candidate update and narrowing of numerical claims.** Target `manual/reference/engine/terrain_sampling.md`; coordinate/source-view clarification also belongs in `manual/reference/engine/m06_visual_terrain.md`. Historical reference `ref/level_format/i76_runtime_terrain_lod_reference.md` remains unchanged. Dependencies: accepted semantic terrain promotion, accepted #51 M06 terrain/physics, #69 source terrain and #76 coherent camera evidence. No canonical change is made in this PR.

| Candidate finding | Evidence / original address | Tier / disposition |
|---|---|---|
| F1, serialized rows/columns, +24 grid placement, local byte stride, +3072 lattice translation, world 5/0.1f, no extra source centering | `TERRAIN_COORDINATE_CONTRACT.md`, `coordinate_cases.jsonl`, `instruction_anchors.tsv`; 00493080/00493160/004931A4 | S/E/H/D; confirm existing facts, add explicit implementation formulas |
| F2, four independent cross-page reads, last-cell ownership, repeated-pointer control | `PAGE_CONTINUITY.md`, `boundary_cases.jsonl`; 00493652/004936A5/004936F8/0049373D | S/E/H/D; add seam contract, distinguish controlled alias from retail references |
| F3, zero-filled default page in initialized image, default vs admission rejection and unsafe direct-coordinate quirks | `PAGE_CONTINUITY.md`, `input_identities.json`, verifier; 0059C588/00493080/004927B0 | S/E/H/D; add bounded default content, retain full-game lifetime uncertainty |
| F4, staged x87 admission and bilinear rounding; exact native results in two missions | `NUMERICAL_BEHAVIOR.md`, `coordinate_cases.jsonl`, rational model/native scripts; 00493550/0049375D/00493769 | H/D plus E address traces; strengthen later static description; do not imply arbitrary x87-state parity |
| F5, corrected FISTP alone does not yield bit-exact Ghidra heights | `results.json`, native ST0 and emulator deltas in cases | H/E/D; narrow prior #51/#69 numerical readings, preserve immutable earlier evidence |
| F6, toggled bit12 does not affect tested height/class/query normals; global semantics remain unknown | controlled `bit12` cases, sparse predicate/static source; 004931A8/004927B0/004931C0 | H/E/S; add bounded negative result, defer global meaning and untested consumers |

Artifact SHA-256/lengths are individually bound by this run's manifest; finding records also bind their principal evidence. This handoff itself is a normal hashed manifest artifact.

Reconciliation: existing +24/+24, low12, 5-unit step and 0.1f claims are confirmed. Later static RC-down qualification is confirmed. Any inference that hardware FISTP correction validates all other emulated x87 arithmetic is contradicted by measured CPU differences. A simplistic single `round(world*0.2f)` admission substitute is insufficient because the extended addition and binary64 store can double-round. Existing `0xff` rejection in serialized reconstruction access is not the original runtime default-page policy. Rendering source-lattice and camera-transform claims are prior accepted evidence, not a new camera replay.

Deferred: global bit12 semantics, native normal numerics/CRT, all-mission generalization, negative-slot undefined memory behavior, teardown/indirect default writes and renderer raster/material/UV. The designated documentation steward should reconcile **merged** evidence in a separate fresh-base promotion/reference PR with explicit human acceptance. This research proposes no edits to manual/, ref/ or agent/promotions/ and does not self-promote.
