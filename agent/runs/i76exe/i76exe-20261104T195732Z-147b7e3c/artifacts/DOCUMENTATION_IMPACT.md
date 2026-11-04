# Documentation impact — HZD horizon manifest format and loader boundary

## Research identity

- Run: `i76exe-20261104T195732Z-147b7e3c`; track i76exe.
- Base: `5f408a117da6d55e495714b648f41b43d708bf6e`.
- PR: pending publication; maintainer merge required.
- Binary/GZF: measured identities in manifest and source_integrity.json.

## Documentation disposition

Candidate update after maintainer acceptance and separate promotion. Suggested target: a new `manual/reference/engine/horizon_resources.md` linked from resource_acquisition and the engine index. No canonical change in this PR. Reconcile with accepted WRLD run `i76exe-20261104T183156Z-085a5e76` and historical `ref/material_format/i76_material_extraction_reference.md`, `ref/zfs/i76_zfs_structure_and_extraction_reference.md`. Terrain sampling and accepted M06 visual-terrain references remain separate; this work establishes no rendered pixels.

## Evidence-linked candidate findings

- HZD-001: observed CRLF wire profile and bounded independent reader. Evidence: artifacts/HZD_FORMAT.md, evidence/parser_constants.json and reviewed_instructions.tsv (00401540..004016de); retail corpus in evidence/corpus.json. Proven static/corpus scope, high confidence. Add observed profile and unsafe-scan qualification.
- HZD-002: 74 logical specimens /33 distinct payloads;80 missions /36 selected names /19 selected payloads; duplicate and mode relationships. Evidence: artifacts/HZD_CORPUS.md, corpus.json. Proven within identified corpus, high confidence. Add counts without generalizing historical releases.
- HZD-003: all272 primary names resolve as104 MAP or168 VQM+CBK, optional M16 companions; actual pairs and release boundary. Evidence: artifacts/HZD_RESOURCE_GRAPH.md, evidence/dependency_inventory.json; reviewed instructions at004474b0,00471c10/00471e50/00471f00. Proven bounded static/corpus scope, high confidence. Add ownership/availability distinction.
- HZD-004: no init rollback, partial pairs retained, separate teardown00401510; inherited “load” alias is misleading. Evidence: artifacts/HZD_CONTROL_FLOW.md, reviewed_instructions.tsv and byte validation. Proven static scope, high confidence. Correct future annotations only through a separate baseline review; do not mutate existing GZF here.

Manifest lists exact SHA-256 and lengths for every evidence/report above; findings.json also hash-links evidence. Unknowns: all-history layout coverage, active runtime source preference/locale, complete decode failure cleanup, geometry/angular mapping, UVs, blending and palette treatment. No native execution or rendering equivalence claim is eligible for promotion from this run.

## Reconciliation and publication boundary

Confirms WRLD payload+0x086/13 and its optional HZD consumer; narrows the earlier “16 tokens” statement to exact delimiter/cursor behavior and demonstrates the corpus record profile. Does not supersede generic RES source ordering/lifetime asymmetry or material/terrain renderer evidence. Proposed HZD format/dependency reporting can proceed independently of renderer guesses; runtime implementation needs transactional ownership improvements explicitly distinguished from retail.

This handoff changes no ref/, agent/promotions/, manual/reference/, shared tools or maintained reconstruction. The designated documentation steward reviews merged evidence and prepares any separate fresh-base promotion/reference PR. Human maintainer acceptance remains required.
