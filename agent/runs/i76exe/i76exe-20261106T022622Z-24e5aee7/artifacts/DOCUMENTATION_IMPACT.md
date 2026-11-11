# Documentation impact — TER/RND/GEO camera to terrain geometry

## Research identity

- Run: `i76exe-20261106T022622Z-24e5aee7`, track i76exe.
- Base: `19c755a77db404ba9cb0ab51f307b4261e983aff`, protected main pinned through GitHub.
- PR/merge: proposal pending at authorship; no merge requested from the agent.
- Binary/Ghidra/input identities: manifest.json, measured private retail PE and
  v100 archive; imported executable section checked in full against PE.

## Disposition and evidence-linked findings

Candidate update after human acceptance; **no canonical change in this PR**.
Targets: `manual/reference/engine/m06_visual_terrain.md`, proposed terrain geometry
reference and advisory TER/GEO/RND milestone notes. Historical
`ref/level_format/i76_runtime_terrain_lod_reference.md` remains immutable evidence.
Dependencies: merged research #140/#141 and accepted coherent-camera #76/#78.

- **ROOT-FOOTPRINT** (S/E/H/D, high): `004929B0`, `00492A1C..00492CF2`;
  camera-height admission, scaled camera/far-corner points, all-nonpositive corner
  ground intersection, bias bounds and expanded root. CAMERA_TERRAIN_ROOT.md,
  camera_fixtures.json and selected_original_events.tsv. Add exact field/operation
  contract; narrow any generic terrain-height/frustum-clipping interpretation.
- **ROOT-HULL** (S/E/H/D, high): `00492D0F..00493065`, `00492890`, `00495000`;
  later-point duplicate rejection, score/sentinel ordering, approximate vertical
  planes and centroid orientation. VISIBILITY_HULL.md, predictions.json,
  angle_instruction_service.tsv. Add original algorithm, not a standard hull.
- **ROOT-LOD** (S/E/H/D, high): `004907E0`, `00490A8B..00490B18`;
  quality-conditioned extended chains and final float32 thresholds.
  LOD_THRESHOLD_NUMERICS.md and comparison.json. Quality is required explicit
  configuration; camera pose alone is insufficient.
- **ROOT-PARITY** (H/D plus E diagnostic, high bounded confidence): 24 native
  cases, exact written outputs; 20 E downstream source graphs, including nine
  accepted #140 cases. CAMERA_GEOMETRY_HANDOFF.md, comparison.json,
  downstream.json and accepted_graph_crosswalk.json. Add bounded source-builder
  handoff removing root/plane external-output dependency.
- **ROOT-EMU-LIMIT** (E/H/D, high): `00493550`/`00492A04` near .01 clearance.
  `clear_exact` native/model accepted versus E rejected. Fixtures and numerics
  report preserve contrary evidence. Confirm and illustrate #141's emulator
  limitation rather than claiming new universal hardware parity.

Artifact SHA-256/lengths are indexed in manifest.json; findings.json repeats
evidence digests. These reports are candidate interpretation, not promotion.

## Reconciliation and publication boundary

Confirms #140's root formula and supplies its missing independent camera-hull
stage. Confirms #141's lattice transform and numerical warning. Narrows #140's
decompiler-level description of height/rounding: actual x87 instructions, not
the displayed float casts, determine admission. Do not overwrite either accepted
run. Existing accepted visual-terrain text still correctly limits native/full
render claims; this is source geometry evidence only. General camera state,
exceptional values and render-output questions stay open as listed in handoff.

The designated documentation steward may reconcile this **after merge** in a
separate fresh-base promotion/reference PR with explicit human acceptance. No
edits to manual/, ref/, promotions/, shared tools or reconstruction/ accompany
this run; research author does not self-merge.
