# I76 curated reference index

**Status: incremental, evidence-reviewed migration.** `ref/` remains the legacy checkpoint; this directory is the living technical reference. The vehicle-construction reference below was accepted through its separate promotion PR. A promotion becomes accepted only when its documentation PR is merged by the maintainer.

The original project's human-readable references continue under `ref/` until reviewed content is intentionally promoted into this directory. This index gives new conversations a stable entry point without duplicating historical technical claims or silently changing evidence.

- [Original game mission architecture](../../ref/mission_execution/README.md): mission execution, FSM integration, current research checkpoints.
- [Vehicle VCF construction, GEO cache, and TMT binding](engine/vehicle_construction.md): scoped original-instruction emulation evidence for two stock vehicles; [promotion crosswalk](../../agent/promotions/vehicle_vcf_geo_tmt_20261023.md).
- [Retail object model](../../ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md): historical FSM-visible identity, damage, registration, ownership and lifecycle.
- [Original level editor](../../ref/editor/README.md): terrain, road and intersection research.
- [Original road and terrain authoring](../../ref/editor/road_terrain_serialization.md).
- [Intersection mesh and physical surface continuity](../../ref/editor/intersection_geometry_and_driving_surface.md).
- [Historical level format](../../ref/level_format/i76_runtime_level_and_terrain_format_notes.md).
- [Resource archive research](../../ref/zfs/): existing ZFS reference directory.

**Subsystem discovery (advisory navigation, not promoted findings):** [ENG / VEH / TER indexes](../roadmap/subsystems/README.md) collect original-function anchors, immutable research runs, reproducibility links and unresolved boundaries for cold-start investigations. Their inclusion here does not promote the linked research conclusions.

**Documentation generation:** a maintainer-designated repository/documentation steward synthesizes accepted research and publishes curated updates with linked `agent/promotions/` records in separate reviewed PRs. Research runs are immutable evidence, not automatic technical promotions. [Workflow](../roadmap/DOCUMENTATION_WORKFLOW.md).

**Preservation policy:** do not delete or mutate historical source references as part of this indexing change. Canonical promotion from legacy references requires a separate reviewed decision and source/evidence reconciliation.
