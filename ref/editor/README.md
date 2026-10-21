# Original Interstate '76 level editor — research reference

**Baseline: October 21, 2026; editor investigations v01–v20.** The original public editor `BUILDER/I76EDIT.EXE` is the primary authoring-program target. Retail `i76.exe` is used as an independent consumer cross-check, not as a substitute for editor evidence.

| Program | Verified original MD5 | Role |
| --- | --- | --- |
| `I76EDIT.EXE` | `4c7ed9e8a54fcadbf1895f34aa9918fe` | Original builder and annotated Ghidra baseline |
| `i76.exe` | `a640ea0097dbb62e0c77b7f2847c7161` | Retail runtime reader and physics cross-check |
| `miss8` / `miss16` | 40 equivalent mission-layout pairs | Original mission and terrain corpus |

## Current synthesis

- [Road and terrain serialization](road_terrain_serialization.md): editable road graph, cubic curves, baked road strips, terrain grading, packed heights/materials, WRLD surface properties.
- [Intersection geometry and driving-surface limitations](intersection_geometry_and_driving_surface.md): SDF/GEO polygon sockets, horizontal/vertical seams, terrain under pavement, wheel-contact distinction.
- [Object identity and FSM bridge](object_fsm_serialization.md): generated instance keys, IXP, OBJ fields and editor/game behavior.
- [Retail vehicle/object lifetime notes](runtime_object_lifetime_notes.md): related engine behavior, explicitly not editor authoring logic.
- [Research provenance](research_history/README.md): versioned investigations and evidence status.

## Established architectural boundaries

1. Original editable roads use straight/cubic-curve controls and explicit connectivity; runtime `RSEG` strips are baked samples and do not retain the source road graph.
2. The visible pavement mesh, intersection meshes, terrain elevation, and packed terrain material are distinct structures. Road visual continuity alone does not prove correct wheel height or grip.
3. The game reconstructs RSEG edge Y by sampling terrain, and terrain-projects intersection root placement. Serialized Y is not always final runtime Y.
4. Retail missions include reproducible geometry/material exceptions. They are regression fixtures, not automatic corrections.
5. No original editable `.I76` workspace sample has been demonstrated to round-trip byte-for-byte; no edited game binary or dynamic road-driving measurement is claimed.

## Immediate next research priority

Trace the game scene-geometry list entered through `004925F0` (global head `00644200`) into collision/rigid-body routines, cross-checking the terrain wheel probe at `00440740`. Independently trace original-editor object grading around road approaches. Separate proven instruction semantics from static numeric reconstruction and live collision observation.

Use original Ghidra baselines **read-only**. No game/editor reimplementation is authorized.
