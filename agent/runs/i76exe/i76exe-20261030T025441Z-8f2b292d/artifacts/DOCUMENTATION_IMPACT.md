# Documentation impact — M06 visual terrain adaptive primitives

## Research identity
- Run: `i76exe-20261030T025441Z-8f2b292d`, track `i76exe`.
- Original base: `b219f0f2edea9da7f6ea9f44b80de90d4ddecb49`; PR pending at artifact creation; no merge authority.
- Original PE/GZF/ZFS/M06 identities: manifest inputs/baseline; executable section independently equals retail.

## Documentation disposition
**Candidate update; no canonical edits in this PR.** Future TER/RND reference may add this bounded original visible-LOD primitive evidence after review. No accepted standalone terrain reference currently exists under manual/reference/engine; steward may create a suitably scoped terrain/RND section. Do not promote texture, UV, final triangles or pixels.

## Evidence-linked candidates
- **F1-original-visual-leaves:** original `00490A00/004929B0/004911E0/00491810` produce source-owned adaptive leaf/edge records; positive original-instruction result with declared services and controlled view. Evidence: `VISIBLE_TERRAIN.md`, `results.json`, `selected_events.tsv`, original writer anchors and standalone verifier. Add a bounded visual producer entry, not a full renderer contract.
- **F2-source-provenance:** all generated vertex heights and selected leaf source page/row/column/material bits independently match authenticated M06; high confidence, exact pre-transform lattice units. Material class reads occur in original LOD predicate. Add provenance distinct from terrain physics; bit12 remains unresolved.
- **F3-render-material-boundary:** static `004922F0` writes fixed B4, alternate `004923F0/004924B0` uses separate descriptor/global state. High confidence for instruction ownership, unresolved for dynamic texture assignment. Narrow any interpretation of TER classes as rendered textures; no contradiction with accepted engine terrain physics.
- **F4-downstream-prerequisites:** raw Ghidra stops at `00492EAF` FPATAN; localized hardware service enables original production. Positive runs stop intentionally at `004937C0` before affine transform/walker. A valid view+40, polygon scratch/clip context and alternate texture resource initialization remain required. Defer renderer/image acceptance.

Digests for all evidence are recorded in manifest.json; original addresses and instruction tiers are in the report and opcode table. Findings.json links exact artifacts with their SHA-256.

## Reconciliation and milestone handoff
Historical `ref/level_format/i76_runtime_terrain_lod_reference.md` described this path as binary-static/analytical. This run confirms its shared edge/leaf layout and reader ordering with new retail instruction checks and original producer execution, without declaring the historical adaptive exporter faithful. `manual/roadmap/subsystems/TER.md` and `RND.md` may distinguish this new producer evidence from previously accepted physics-only results. Existing physics evidence is neither used as visual proof nor contradicted.

Map to **G-RND-05 preliminary source/primitive provenance: bounded positive**; rendered material/texture and terrain→image **partial/unexecuted**. RND-R2/I1 and SC-RND-04/05 stay open. M-RND-03 is independent and untouched. Any fuller source camera/renderer fixture must be separately reviewed; no new gate or maintained renderer authorization is proposed.

## Publication boundary
This handoff proposes no changes to ref/, agent/promotions/ or manual/reference/. A designated steward can reconcile merged evidence in a separate fresh-base documentation PR; only the human maintainer accepts it. No automatic promotion or merge.
