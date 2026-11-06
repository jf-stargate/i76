# Documentation impact — terrain walker emission selection

Run `i76exe-20261106T041351Z-cdebba73`, track i76exe, advisory TER/GEO/RND. Base `19c755a77db404ba9cb0ab51f307b4261e983aff`. Original executable and private annotated v100 baseline identities are measured in manifest.json. This handoff is not canonical promotion.

Disposition: **candidate update** to `manual/reference/engine/m06_visual_terrain.md`, with crosslinks from terrain_sampling.md and software_renderer.md as a documentation steward judges useful. Historical `ref/level_format/i76_runtime_terrain_lod_reference.md` remains a preserved checkpoint. No canonical change is made by this PR.

| Finding | Claim / evidence | Proposed impact |
| --- | --- | --- |
| F-WALK | Exact projected-Y, corner-facing, shade-band gates and whole-return fallback; TERRAIN_WALKER_DECISIONS.md, POLYGON_FACING_AND_SHADE.md, instruction anchors, decisions.jsonl, verification.json | Add bounded original selection contract; replace “full walker unresolved” only within demonstrated corpus |
| F-FAN | Anchor priority, ordered adjacent fan, negative-distance filter and ignored triangle returns; TRIANGLE_FALLBACK.md, decisions.jsonl | Add tested anchor cases and exact order; preserve static-only corner-end/center qualification |
| F-EMISSION | Attempts, clipped results and final bins have distinct identities; EMISSION_RECONSTRUCTION_HANDOFF.md, verification.json, context_validation.json | Narrow any assumption that EAX success always proves bin acceptance |
| F-SHADE-CONTROL | 18 shade-band rejections under supplied lighting and original high-flag triangle scalar bypass; POLYGON_FACING_AND_SHADE.md and shade/high numerical fixtures | Add controlled branch evidence, not authentic M06 lighting/color claims |

Methods/confidence: binary-static and original-instruction emulation with substituted services; high confidence within named fixtures. Independent numerical prediction is derived evidence with explicit error bounds, not hardware-wide x87 identity. Manifest artifact entries supply SHA-256/byte lengths for each cited local artifact; findings.json links the precise digests.

Reconciliation: confirms merged #140 shared-edge flattening, source/work reversal and primary counts; eight common cases retain 76 exact sidecars. Extends the full walker gap left by #140. Does not supersede its independent graph/root boundary or open #143/#144 research. Inherits the accepted #76 controlled-camera/clip/bin scope and confirms primary/contrast/below with its unchanged independent context verifier (v100 digest already accepted by #140). No conflict with the promoted M06 material/rendering boundary: the source class, 0xB4 header, auxiliary color and displayed material remain different entities.

Deferred: additional-center cannot be authentically reached in the measured corpus; static trigger/arithmetic are documented without invented output expectations. C.end/D.end, authentic nonzero lighting/resource setup, degenerate/tie arithmetic, generalized bin failure, successful alternate descriptor and downstream rendering remain open. A separate steward PR should reconcile merged evidence and retain these caveats. Only human review can accept promotion; this run does not edit `manual/`, `ref/` or `agent/promotions/`.
