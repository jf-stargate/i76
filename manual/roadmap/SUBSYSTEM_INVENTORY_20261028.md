# I76 subsystem and research/tooling inventory — 2026-10-28

**Status: architecture inventory proposal; not a promotion or a new reverse-engineering finding.** This page maps already-published files and results onto candidate subsystem owners. It does not amend the publication protocol, validate the full original game, or authorize reconstruction. Historical references and accepted run directories remain immutable.

- **Pinned inventory commit:** \`026fd0daacb21b4da122163186a8ec2f4b49d894\` ([view](https://github.com/jf-stargate/i76/tree/026fd0daacb21b4da122163186a8ec2f4b49d894)).
- **Tree SHA:** \`161f50added692968de7f1df42fa27fef0d5733d\`; inventory taken from the complete, non-truncated Git tree at the pinned commit.
- **Inventory method:** enumerate tracked paths and read selected current/legacy reference documents and run assessments. Counts are Git *files*, not unique algorithms, independently confirmed findings, or runnable tests. No original binary, Ghidra project or proprietary asset was executed for this inventory.
- **Boundary:** \`i76.exe\` is the primary active runtime research target. \`i76edit.exe\` and \`i76shell.dll\` are separate Ghidra/binary targets with defined data and invocation interfaces; \`shared\` is cross-program/protocol work.

## Repository census (as committed)

| Area | Tracked files | Notes |
| --- | ---: | --- |
| \`snapshot/\` | 15,500 | 13,166 \`i76.exe\`; 1,746 \`i76edit.exe\`; 588 \`i76shell.dll\` |
| \`ref/\` | 108 | Historical references, tables and measured evidence; not automatically promoted |
| \`scripts/\` | 217 | 166 \`local_history/\`, 40 \`ghidra_history/\`, 6 \`ghidra_emulation/\`, 3 \`game/\`, 2 \`auto_templates/\` |
| \`agent/runs/\` | 326 | 33 run directories: 18 \`i76exe\`, 14 \`i76edit\`, 1 \`shared\` |
| \`manual/\` | 15 | Curated reference, roadmap and decisions |
| \`agent/\` all | 351 | Includes run files and governance, baseline and promotion records |
| Git blobs overall | 16,200 | Includes all top-level tracked files; not a count of nonduplicate logical artifacts |

**Publication classification:** the \`agent/runs/\` records are accepted repository evidence where merged, **not automatically promoted behavioral truths**. \`manual/reference/engine/vehicle_construction.md\` is an existing specifically promoted reference; most other knowledge remains in \`ref/\` and append-only research runs.

## Candidate subsystem map for original \`i76.exe\`

**Functional IDs are ownership labels, not recovered original source modules.** Multiple subsystems legitimately cite the same original function or research run. No new correctness grade is inferred from file counts.

| ID | Boundary / present evidence | Anchor(s) | Major unclosed interface |
| --- | --- | --- | --- |
| **ENG** | Startup, clocks, frame update order, class callbacks, teardown; original timing and two-frame probes | [mission execution](../../ref/mission_execution/MISSION_EXECUTION_CONTRACT.md), [clock run](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/FRAME_INITIALIZATION.md) | Whole WinMain-to-world-to-render scheduling and cross-mode ordering |
| **RES** | ZFS/ZIX, PIX/PAK, resource search/caches, format and extraction work | [ZFS](../../ref/zfs/i76_zfs_structure_and_extraction_reference.md), [resource acquisition](../../ref/game/i76_resource_acquisition_reference.md) | End-to-end original cache/allocation failure/lifetime policy |
| **MLD** | BWD2 and mission descriptors, ODEF/LDEF, nested ADEF/FSM, parser/loader original-code emulators | [loader spec](../../ref/mission_execution/README.md), [parser emulator](../../scripts/ghidra_emulation/I76_BWD2_OriginalParserEmulator.java) | Full mission load / repeated-load and malformed input behavior under retail execution |
| **OBJ** | World class objects, registries, identity keys, reference ownership, spawn and teardown | [object model](../../ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md), [registry run](../../agent/runs/i76exe/i76exe-20261023T032812Z-044e59e2/artifacts/REGISTRY_NATIVE_RESEARCH.md) | Complete real-object destroy/unregister/actor invalidation lifecycle |
| **FSM** | Seven serialized tables, VM execution nodes, cooperative scheduler, 96 command host ABI, mission events | [FSM/VM contract](../../ref/mission_execution/MISSION_EXECUTION_CONTRACT.md), [host ABI](../../ref/mission_execution/HOST_COMMAND_ABI_CONTRACT.md) | Live end-to-end VM integration with full world/AI/physics callbacks |
| **VEH** | VCF/VDF/VTF/CDF construction; controls, pose, drivetrain and suspension original-instruction experiments | [promoted construction](../reference/engine/vehicle_construction.md), [authentic-terrain run](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/AUTHENTIC_TERRAIN_PHYSICS.md) | General contact/collision, normal frame input, full vehicle dynamics and x87 parity |
| **AI** | Behavior-state tables, steering/follow/control queue and FSM host-call interfaces | [mission execution, AI section](../../ref/mission_execution/MISSION_EXECUTION_CONTRACT.md), [historical navigation research](../../ref/mission_execution/research_checkpoints/v91/V91_MOVEMENT_NAVIGATION_OBJECTIVES.md) | Multi-actor AI movement/targeting/combat correctness with live world state |
| **COM** | Weapons, damage sources, death flags, collision event and mission-event bridge | [object model](../../ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md), [historical FSM events](../../ref/fsm/i76_fsm_runtime_reference.md) | End-to-end projectile/hit/damage/collision callbacks and attribution |
| **TER** | WDEF/TDEF/ZMAP/ZONE, height/material sampling, RSEG, adaptive terrain and scene collision surfaces | [level format](../../ref/level_format/i76_runtime_level_and_terrain_format_notes.md), [terrain LOD](../../ref/level_format/i76_runtime_terrain_lod_reference.md), [authentic-terrain run](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/AUTHENTIC_TERRAIN_PHYSICS.md) | Complete world collision surfaces, road texture/UV rules and runtime LOD parity |
| **GEO** | VCF/VGEO/GEO, static SDF mesh, materials/TMT, texture formats and palette data | [model formats](../../ref/model_format/i76_vehicle_model_format_and_extraction_reference.md), [materials](../../ref/material_format/i76_material_extraction_reference.md), [construction](../reference/engine/vehicle_construction.md) | Full texture decode/render-state semantics, general object-family parity |
| **RND** | Cameras, world transforms, visibility producer, work buckets, geometry traversal, software/D3D dispatch | [render traversal run](../../agent/runs/i76exe/i76exe-20261023T062154Z-62e3a718/artifacts/RENDER_TRAVERSAL_AND_BUCKET_CONTRACT.md), [camera run](../../agent/runs/i76exe/i76exe-20261023T153639Z-95865b83/artifacts/CAMERA_TYPE10_ARCHITECTURE.md) | Authentic complete frame producer → native clip/draw → pixels |
| **AUD** | Mission-visible CB/audio queue, audio assets, engine-sound initialization and media hooks | [mission contract](../../ref/mission_execution/MISSION_EXECUTION_CONTRACT.md), [authentic-terrain run](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/AUTHENTIC_TERRAIN_PHYSICS.md) | Actual mixer, spatial audio, media playback and synchronization |
| **NET** | Game-side multiplayer flags, object-state/damage replication and frame mode gates | [mission contract](../../ref/mission_execution/MISSION_EXECUTION_CONTRACT.md), [shell interface reference](../../ref/game/i76shell.dll_reference.md) | Runtime packet protocol, state consistency and multiplayer timing |

Ownership rules: VEH computes dynamic contact response while TER supplies terrain/surface queries; OBJ owns object identity/lifetime, while GEO owns graph/geometry/material loading; FSM owns bytecode/host-call semantics, AI owns autonomous decision-making; ENG owns frame phase order; RND consumes scene/camera state and owns presentation. Cross-cutting experimental harnesses remain permissible in any reversing workstream.

## Accepted \`i76exe\` run crosswalk

Each link is an existing immutable run manifest; mappings are an inventory annotation, **not a claim that all listed subsystems were completely validated**.

| Run suffix | Candidate owners | Subject / observed research focus |
| --- | --- | --- |
| [96c58505](../../agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/manifest.json) | RES,OBJ,VEH,GEO,RND | Native VCF/VDF/VTF/CDF resource construction, geometry and TMT binding |
| [044e59e2](../../agent/runs/i76exe/i76exe-20261023T032812Z-044e59e2/manifest.json) | MLD,OBJ,FSM | Instance-key registry and actor lookup original-instruction probe |
| [4e59e782](../../agent/runs/i76exe/i76exe-20261023T042231Z-4e59e782/manifest.json) | RND,GEO,RES | Render boundaries, depth records and lazy texture acquisition |
| [42a0573a](../../agent/runs/i76exe/i76exe-20261023T044729Z-42a0573a/manifest.json) | RND,GEO,VEH | Vehicle resource-to-render/material dispatch bridge |
| [62e3a718](../../agent/runs/i76exe/i76exe-20261023T062154Z-62e3a718/manifest.json) | RND,GEO,OBJ | Scene traversal, buckets and polygon submission |
| [dea36f3e](../../agent/runs/i76exe/i76exe-20261023T065502Z-dea36f3e/manifest.json) | RND,OBJ | Visibility and queue producer contract |
| [c5725c60](../../agent/runs/i76exe/i76exe-20261023T072053Z-c5725c60/manifest.json) | OBJ,VEH,RND | Registered vehicle rendering and reference-lifecycle bridge |
| [95865b83](../../agent/runs/i76exe/i76exe-20261023T153639Z-95865b83/manifest.json) | RND,ENG | Camera initialization, render arena and type-10 GEO path |
| [84ef6779](../../agent/runs/i76exe/i76exe-20261024T021540Z-84ef6779/manifest.json) | RND,VEH | Follow-camera native behavior |
| [11d4e2ec](../../agent/runs/i76exe/i76exe-20261024T232546Z-11d4e2ec/manifest.json) | RND,VEH,OBJ | VLOC attachment/camera contract |
| [12215047](../../agent/runs/i76exe/i76exe-20261026T235108Z-12215047/manifest.json) | OBJ,VEH | Flag-10 creation/status to VLOC call chain |
| [bc6825e4](../../agent/runs/i76exe/i76exe-20261027T004812Z-bc6825e4/manifest.json) | OBJ,VEH,RND | Selected VCF/VLOC spawn and camera |
| [0f837d60](../../agent/runs/i76exe/i76exe-20261027T014732Z-0f837d60/manifest.json) | RND,OBJ | Camera post-guard and world-matrix boundary |
| [108e46eb](../../agent/runs/i76exe/i76exe-20261027T024149Z-108e46eb/manifest.json) | RND,OBJ,VEH | World-transform initialization and camera basis |
| [32de4d1e](../../agent/runs/i76exe/i76exe-20261027T031313Z-32de4d1e/manifest.json) | RND,OBJ,VEH | Valid constructed root and camera numerics |
| [2f8c31f5](../../agent/runs/i76exe/i76exe-20261027T033452Z-2f8c31f5/manifest.json) | VEH,ENG,RND | Original vehicle pose over two consecutive controlled frames |
| [66a1688b](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/manifest.json) | ENG,VEH | Clock subdivision and startup reciprocal-square-root prerequisites |
| [3f1f83f8](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/manifest.json) | TER,VEH,ENG,AUD | Authentic M06 terrain, bilinear sampling and suspension contacts; engine-sound resource init |

## Independent program tracks

### \`i76edit.exe\` — editor / builder (\`i76edit\`)

Original editable road graph, cubic segments, terrain grading and classification, zone state, object/FSM export and original CRT startup behavior. This is a distinct program and **not** a subgroup of main-engine TER. Engine TER/OBJ/MLD references may use editor evidence as cross-checks of shared formats only. Start at [editor reference](../../ref/editor/README.md), [road authoring](../../ref/editor/road_terrain_serialization.md), [object identity/export](../../ref/editor/object_fsm_serialization.md).

| Run suffix | Focus |
| --- | --- |
| [21de63e4](../../agent/runs/i76edit/i76edit-20261023T013651Z-21de63e4/manifest.json) | Object terrain grading |
| [70ae8183](../../agent/runs/i76edit/i76edit-20261023T020247Z-70ae8183/manifest.json) | Smoothing and object processing order |
| [5ce8ac14](../../agent/runs/i76edit/i76edit-20261023T023107Z-5ce8ac14/manifest.json) | Original editor overlap and smoothing |
| [5492075e](../../agent/runs/i76edit/i76edit-20261023T025734Z-5492075e/manifest.json) | Road mode precedence |
| [fec7cae2](../../agent/runs/i76edit/i76edit-20261023T031245Z-fec7cae2/manifest.json) | Road/terrain classifier differential |
| [a8d70545](../../agent/runs/i76edit/i76edit-20261023T043010Z-a8d70545/manifest.json) | Road grid scaling |
| [05173d2e](../../agent/runs/i76edit/i76edit-20261023T045502Z-05173d2e/manifest.json) | Road raster neighbor behavior |
| [7504f18b](../../agent/runs/i76edit/i76edit-20261023T062209Z-7504f18b/manifest.json) | Terrain service/zone seam |
| [0e28a278](../../agent/runs/i76edit/i76edit-20261023T065437Z-0e28a278/manifest.json) | Zone first touch |
| [ea5043d8](../../agent/runs/i76edit/i76edit-20261023T072227Z-ea5043d8/manifest.json) | Zone compaction and reuse |
| [64b4e9ad](../../agent/runs/i76edit/i76edit-20261023T153200Z-64b4e9ad/manifest.json) | Editor object teardown |
| [3e91ae7d](../../agent/runs/i76edit/i76edit-20261027T000144Z-3e91ae7d/manifest.json) | Editor CRT allocator investigation |
| [25e3484f](../../agent/runs/i76edit/i76edit-20261027T003326Z-25e3484f/manifest.json) | Original CRT small-block heap |
| [3eb837e1](../../agent/runs/i76edit/i76edit-20261027T010513Z-3eb837e1/manifest.json) | Editor startup/decommit lifecycle |

### \`i76shell.dll\` — frontend DLL (\`i76shell\`, proposed publication track)

**Independent Ghidra target already exists:** \`snapshot/i76shell.dll/\` (588 Git blobs). Historical work: [shell DLL research](../../ref/game/i76shell.dll_reference.md), [MW2 database](../../ref/mw2/database_mw2_reference.md), and shell-focused tools under \`scripts/local_history/\`. Covers ShellMain, menu/selection/UI assets, mission/vehicle configuration, DirectPlay setup and shell-to-engine callback/config-block ABI.

**Current gap is administrative, not architectural:** there is no published \`agent/runs/i76shell/\` run, and protocol v1.0.3 does not permit that track. Do not relabel prior shell snapshots or scripts as synthetic research runs. A separate versioned governance proposal should add \`i76shell\` with the same original-binary and Ghidra provenance requirement as \`i76exe\`/\`i76edit\`.

The engine side owns the recipient of the launch/session ABI. The shell owns the frontend producer. NET owns engine-side multiplayer behavior after session handoff.

### \`shared\` — cross-program research/protocol

The one [shared run](../../agent/runs/shared/shared-20261022T043403Z-da3692e8/manifest.json) is a protocol structure-only publication smoke test with no substantive original-binary finding. Shared tools, differential validation and cross-program format interface contracts should remain distinct from binary-specific research.

## Existing tool inventory and classification

| Location/example | Experimental role | Proposed handling |
| --- | --- | --- |
| \`agent/runs/i76exe/*/scripts/\` | Original Ghidra execution, source/anchor audits, controlled replay and experiment validators | Preserve inside immutable runs; identify reusable primitives later |
| \`agent/runs/i76edit/*/scripts/\` | Editor original-instruction validators and localized analytical models | Preserve as editor-track evidence |
| [\`scripts/ghidra_emulation/\`](../../scripts/ghidra_emulation/) | Legacy original parser/mission-wrapper probes and verification | Historical reversing tools, not automatically a maintained engine |
| [\`scripts/game/\`](../../scripts/game/) | ZFS extraction and independent terrain/Blender export | Candidate resource/terrain reconstruction utilities, with explicit fidelity limits |
| \`scripts/local_history/\`, \`scripts/ghidra_history/\` | Earlier iterative decode, export, Ghidra reporting and experiments | Index by subject; do not mass-rewrite or treat all revisions as active |
| \`ref/mission_execution/evidence/\` | Prior parser/VM/loader corpus tests and observation traces | Historical test evidence for MLD/FSM |
| \`manual/reference/\` and \`agent/promotions/\` | Curated accepted claims and crosswalk | Interface specification source after deliberate promotion |
| \`agent/protocol/\`, \`.github/\` | Identity/provenance schemas, validation and governance | Shared publication infrastructure, not reverse-engineered runtime behavior |

**Harness classification rule:** a reversing run may author original-code emulators, stubs, analytic models, extracted fixtures, comparison scripts and even provisional implementations. Their purpose and evidentiary limitations must be stated; this work is never prohibited for looking like reconstruction. A maintained replacement implementation requires a separate review and conformance claim, not merely code relocation.

## Inventory gaps / caveats

1. This is a **repository-path and selected-document inventory**, not a completed callgraph-level map of every one of the 15,500 snapshot blobs or all 217 historical scripts; further subsystem-oriented mining is appropriate.
2. The legacy file inventory [\`manual/history/legacy_inventory.json\`](../history/legacy_inventory.json) already pins 108 reference and 217 script blobs and should be reused, not regenerated with invented historical identities.
3. Some recent original-code reports are emulated with explicit platform or numerical substitutes. They do not imply live Windows execution, perfect x87 matching, a complete game loop, or finished raster pixels.
4. Research coverage, reconstruction implementation coverage and differential validation coverage are **separate**; these rows do not assign numerical completion percentages.
5. New source/contract organization, \`i76shell\` publication identity and possible \`reconstruction/\` or \`validation/\` directories require separate reviewed proposals. No accepted files are moved by this inventory.

## Planning handoff

Use this inventory to establish subsystem workstreams for the main binary, then define separate reversing coverage, validated contracts, independent reconstruction and integration needs. Do not impose a policy that blocks creation of validation tools during reversing, and do not promote historical conclusions based only on script names or file counts.