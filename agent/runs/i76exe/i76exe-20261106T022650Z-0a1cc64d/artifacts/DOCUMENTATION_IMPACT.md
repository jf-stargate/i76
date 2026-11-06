# Documentation impact — adaptive terrain boundary scans

Run `i76exe-20261106T022650Z-0a1cc64d`; i76exe, TER/GEO. Original base `19c755a77db404ba9cb0ab51f307b4261e983aff`. Research-only PR pending at packaging. Binary SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`; authenticated v100 GZF identity in manifest/provenance. No maintained C++, canonical documentation, promotions or earlier runs are edited.

Disposition: **candidate update**, narrowing a prior unresolved issue; **no canonical change in this PR**. Suggested target: `manual/reference/engine/terrain_sampling.md` for lookup/scan separation and a future adaptive geometry reference alongside `manual/reference/engine/m06_visual_terrain.md`. Historical `ref/` is retained unchanged; this run does not claim to reconcile every historical terrain report.

| Finding | Candidate documentation statement | Primary evidence / anchors | Tier and qualification |
|---|---|---|---|
| F-SCAN | One-pointer scan has four exact starts/strides and side samples; normal phase prevents crossing127 | ADAPTIVE_BOUNDARY_SCAN.md; instruction_anchors.tsv; public_verification.json; 00491556–00491674, 00492CB9–00492CC2, 004912F0/00491550 | Proven bounded native scan + binary-static/derived caller invariant; not arbitrary corrupted roots |
| F-CROSS | Unaligned X can row-spill; Z can enter next ordinal or leave backing; defaults can spill into unrelated globals | PAGE_CROSSING_CASES.md; scan_cases.jsonl; 004915F7/0049160F/00491627/0049163F | Native original instructions with supplied environment; unsafe reads stopped before dereference |
| F-CLASS | Classes2/3/4/6/7 refine; default0 and class5 do not; repeats have no special scan handling | MATERIAL_REFINEMENT_BOUNDARIES.md; scan_cases.jsonl; geometry_comparisons.json | Native class predicate and original-instruction emulated full geometry; initialized default lifetime bounded to setup |
| F-GEOMETRY | Default/repeat/class controls reproduce complete source graphs and shared unequal-LOD loops without partial T junctions | geometry_comparisons.json; geometry_details.json; geometry_repeat.json; 004911E0/004918F0/00491A30 | Derived independent model versus Ghidra original instruction execution, six selected M06 cases; no full renderer/native geometry claim |

All report/table/script hashes are enumerated in manifest.json; findings.json links the corresponding artifacts. The documentation steward should reconcile merged #140's ADAPTIVE_TERRAIN_ALGORITHM/GEOMETRY_RECONSTRUCTION_HANDOFF with merged #141's TERRAIN_COORDINATE_CONTRACT/PAGE_CONTINUITY. This run narrows #140's default/repeated scan limitation and confirms #141's ordinary coordinate resolution. It contradicts neither ordinary bilinear lookup nor its numerical caveats.

Suggested dependency: promote alongside both starting runs, retaining evidence tiers. Further work: full camera-root independent recovery, remaining walker/emitter branches and full-game default lifetime. A normal-operation memory-safety claim requires the caller invariant and valid backing, not only the scan's origin checks. An unaligned coordinate-resolved extension must be labeled a safe extension rather than original pointer parity.

The designated steward may prepare a separate fresh-base promotion/reference PR after this research is merged and reviewed. Human maintainer acceptance remains required; this handoff grants no self-merge or promotion authority.
