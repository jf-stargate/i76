# Interstate '76 — VOM/FSM research checkpoint (2026-10-19)

> **Historical research reference (2026-10-19):** Later findings and corrections are at [mission execution](../mission_execution/README.md). This document is preserved verbatim below as a historical snapshot.


## Source and Git state

This is a **documentation/checkpoint update** based on the uploaded repository (`remote1.tar`) and its already-included retail `i76.exe` Ghidra snapshot. No network publication, Ghidra mutation, runtime execution, or Git commit is implied by the documentation update.

- Program: original retail `i76.exe`; MD5: `a640ea0097dbb62e0c77b7f2847c7161`; image base `0x00400000`.
- Snapshot: [`snapshot/i76.exe/i76.exe_ghidra_state_snapshot_20261019_205431/`](../../snapshot/i76.exe/i76.exe_ghidra_state_snapshot_20261019_205431/README.md), exported **Mon Oct 19 20:54:59 PDT 2026**.
- Snapshot manifest schema: `i76-ghidra-project-state-snapshot-v69` (schema version, **not** research iteration number).
- Snapshot counts: **2097 functions, 2093 semantically named functions, 9988 callgraph edges, 27099 symbols, 3356 comments, 89 structures, 4020 defined strings**; all 29 known candidates defined, class-table verification true.
- `00409980`: now a Ghidra-defined function, body `00409980–00409BC0` (`577` bytes), currently named `FUN_00409980`. Its definition accounts for the increase from 2096 to 2097 functions relative to the previous 18:34 export. Full decompilation for this function is **not** present in the focused scope of the 20:54 snapshot; behavior below is also supported by independent original-PE disassembly.
- The zip archive of the snapshot and its files already in the supplied repository were compared byte-for-byte (568 ZIP file entries); all matched. No duplicate snapshot copy added.

## Work established by v71–v76

| Pass | Durable result | Distinction / remaining caveat |
|---|---|---|
| v71 | Re-created 13 incorrectly bounded function bodies following deletion of 23 false fragments | Function body ownership repaired; no reason to reapply the old fragment-merging script |
| v72 | Two status-clearing recursive/helper names committed in Ghidra; separated vehicle runtime dead, world-object dead, and attribution states | Other destructive/network paths still exist |
| v73 | Mapped AI-private damage source records, timestamp, epoch markers and destructive event tests | Collision producer timing unresolved |
| v74 | Established VM yield/completion and full pending-list traversal, plus conditional FSM-vs-AI frame branch and epoch increment | Ordering outside `0040A320` unresolved |
| v75 | Recovered serialized FSM loader, `0x10BC` persistent node layout, linking, relocation and reference binding | Indirect runtime node creation not exhaustively excluded |
| v76 | Closed principal loader-to-VM static call chain, identified `clsnDmg` descriptors and unregistration callback as highest-priority missing definition | `00409980` definition **now fixed in subsequent 20:54 checkpoint**, but object-lifetime semantics not complete |

## New callback boundary fact

The retail executable's `00409980` contains a world-object removal callback. It checks/clears matching AI references at `+0xA9B4`, clears mission actor `+0x58` pointers with reference-release calls, removes qualifying vehicles from team buckets and sets AI `+0xA714` to request refresh of remaining registered state. The new snapshot records a bounded function, **not** a rename or full pointer-ownership proof. Suggested future semantic label: `unregister_fsm_vehicle_world_object_and_invalidate_references_00409980`; **not applied**.

A separate misleading existing symbol, `00409850 initialize_fsm_runtime_heap_and_tables`, is actually the active-world-object registration callback (see companion VOM reference). Likewise `0041C2C0 is_ai_vehicle_target_matching_current_player_or_actor` compares the `+A6D8` event marker against the current update epoch, not player identity. These names should be re-evaluated with guarded renames after caller closure; do not silently change the exported snapshot.

## Published reference pages in this checkpoint

- [FSM runtime, loader, pending scheduler and damage-event semantics](../fsm/i76_fsm_runtime_reference.md)
- [Vehicle Object Model, object identity, death state and removal/invalidation](../vehicle_object_model/i76_vehicle_object_runtime_reference.md)
- Existing [game mission pipeline](i76_mission_reconstruction_pipeline.md) and [mission reconstruction pipeline](../mission_reconstruction/i76_mission_reconstruction_pipeline.md) now refer to the FSM/VOM documentation and distinguish asset export from runtime simulation.

## Unresolved engine interfaces, ranked for single-player FSM fidelity

1. **World-object lifetime**: validate execution of `00409980` during unregister, reference release/count semantics, actor/VM label invalidation, and re-registration behavior. The function is defined; its runtime contract is not completely closed.
2. **Collision/weapon event ingress**: find the evaluator/callers of the seven `clsnDmg` descriptors pointing at `0041C2C0`; trace contact/damage to `004157A0`; verify event category, suppression and epoch stamping.
3. **Whole-frame order**: locate the outer call of `0040A320` relative to physics, collisions, world-object callbacks, mission timers and clock advancement. Respect `0051F640` and `0051F5C0` gates.
4. **Host-command dependencies**: prioritize the commands actually present in the 25-mission corpus (AI navigation, target acquisition, ammo, combat, arrival/visibility and steering); not all 96 IDs have independently verified world effects.
5. **Mission timers and callback services**: trace asynchronous objective/time/voice/camera changes. `0040C020` with `STOPCBXX` is a timer/event wrapper, **not** a VM-node allocator.
6. **Alternative network/trip modes**: the `00464890` network state application is not automatically equivalent to local damage attribution. Lower priority for single-player unless demonstrated otherwise.

Rendering road UV/material fidelity, palette/lighting, terrain visual reconstruction, audio/cutscenes, UI and multiplayer require additional work for full-engine reconstruction, but are **not currently assumed prerequisites** for a single-player, state-injected FSM interpreter.

## Recommended next iteration and validation

**v77 — VOM ownership and event producer frame closure:** decompile the newly defined `00409980` and verify its indirect callers; follow `004572B0`, `00457420`, `00412400`, `0045EF70`, `00457630`; locate indirect `clsnDmg` descriptor evaluator; establish the complete frame phase sequence and the source of the epoch clock. Export corresponding callsite/disassembly/field evidence, then add a two-node shared-state scheduler regression, event-consumption-order regression, object-unregister regression and a timer-driven objective regression. Do not claim retail behavior from an offline parser passing its own tests.

**For publication:** include the existing snapshot folder and relevant Ghidra scripts already present in the supplied archive, plus the new reference files. Keep the snapshot manifest unaltered; changes to Ghidra symbol names require a fresh export. Commit and push through the normal repository workflow only after inspecting `git status` and reviewing additions.
