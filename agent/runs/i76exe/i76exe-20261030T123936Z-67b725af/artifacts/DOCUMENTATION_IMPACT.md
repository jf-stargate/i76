# Documentation impact — RND / TER M06 transformed terrain

## Research identity
- Run ID: `i76exe-20261030T123936Z-67b725af`
- Track: `i76exe`
- Original base recorded for the existing isolated workspace: `b219f0f2edea9da7f6ea9f44b80de90d4ddecb49`
- Related accepted research: M-RND-05 PR #69; M-RND-03 PR #70 is interface context only.
- Original binary: authenticated retail `i76.exe`; annotated Ghidra baseline `i76_mission_v97_verified_names`.

## Documentation disposition
- Classification: **unresolved / no canonical change**.
- Target indexes: `manual/roadmap/subsystems/RND.md`, `manual/roadmap/subsystems/TER.md`, and RND acceptance notes.
- Historical context: `ref/level_format/i76_runtime_terrain_lod_reference.md` and linked terrain material notes.
- Suggested dependency: a complete, scene-compatible original camera/render-context initialization and polygon pool lifecycle sufficient for original `0047BF00` clipping and `0048FE10` binning.

## Evidence-linked findings

- **F1 — transformed native vertices:** Original `004937C0` applies its retail terrain scale composed with the explicitly controlled affine view. All 267 transformed XYZ tuples match an independent calculation from the exact pre-transform vertex bytes; source coordinates, TER page/row/column, height, and material class are resolved independently. Status: **proven for this controlled emulation**. Evidence: `REPORT.md`, `evidence/verification.json`, probe script. Documentation impact: **defer** until scene-authentic camera provenance is available.
- **F2 — original polygon candidates:** With test-owned polygon scratch memory installed at `006543C0`, original `004922F0` writes 139 0xB4-byte candidate work records before original clip callback `0047BF00`. Every record XYZ tuple reconciles with its source vertex IDs. All candidates are rejected and none reaches `0048FE10`. Status: **proven for the controlled harness**. Evidence: report, service ledger, independently regenerated verification. Documentation impact: **narrow** the accepted visual-terrain boundary to distinguish adaptive leaves, transformed vertices, and pre-clip polygon candidates from accepted renderer submissions.
- **F3 — material provenance boundary:** M06 TER material classes remain attached to source vertex samples. The primary polygon path writes a fixed record type; the alternate `004924B0` path reads runtime globals including `0059C558`, and `00471F00` selects a resource handle using render-context state. This run does not establish a TER-material-to-descriptor relation. Status: **proven that no relation was established here; mapping unresolved**. Documentation impact: **defer**; do not name rendered textures or UVs from TER codes.

## Reconciliation notes

This extends M-RND-05 beyond its `004937C0` entry boundary but does not replace or modify that accepted run. It does not merge with M-RND-03, infer terrain pixels, use physics/collision as rendering evidence, or complete G-RND-05. The candidate work records are pre-clip; the clip callback returns zero under the controlled context. A documentation steward should reconcile this run only after review and merge, and should leave canonical references unchanged until the renderer context dependency is resolved.
