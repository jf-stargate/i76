# Interstate '76 — v76 engine uncertainty assessment

**Scope:** Prioritize gaps that affect accurate vehicle-object-model (VOM) and multi-node mission FSM reconstruction. Based on the user-supplied v76 outputs (`calls`, `collision_descriptor_refs`, `decompiled`, `global_xrefs`, `readme`, `targets`, `whole_text_field_scan`), v72–v75 exported evidence and technical findings, and selected original retail PE assembly (`i76.exe`, MD5 `a640ea0097dbb62e0c77b7f2847c7161`). **Static evidence, not gameplay instrumentation.** Functions/variables not exported in v76 cannot be claimed exhaustively analyzed.

## Known contracts (not current primary blockers)

- Mission FSM BWD2 payload import `00409740 -> 00410720 -> 004125C0`: serializes independent command, object/bitfield, vector, word, token, and initial execution-node tables.
- Initial pending nodes: `00410490`, allocated as `0x10BC` bytes, linked through `+0x10B8`, count/head globals `0051F62C`/`0051F628`. `00412500` relocates references and seeds PC, frame, stack and command workspace.
- Mission actor binding: `00412400`, 0x60-byte records, key `+0x50/+0x54`, object at `+0x58`, refcounted.
- VM `00414670`, `{u32 kind,u32 payload}` 8-byte tokens; 0x0A yields (return 0), top-level return 0x0C completes (return 1); host dispatcher `00412CE0` recognizes 96 ID slots but not all host effects are independently verified.
- Scheduler `004149F0` executes all eligible persistent nodes in linked-list order, unlinks/frees completed nodes and retains yielded nodes. A full retail PE scan found only two literal `0x10BC` heap-allocation sites, both in initial loader; this is strong but bounded evidence of no dynamic normal node spawn.
- Frame branch `0040A320`: when `0051F640==0`, takes either single-player FSM scheduler or alternative AI update according to runtime mode and `0051F5C0`, then updates progress and increments shared epoch `00524550` at `0040A658`.
- Event ledger: `004157A0` writes `AI+A6D4/D8/DC` epoch markers, `AI+A6E4/E8/EC` source objects, `AI+A6E0` attribution, `AI+A6F0` timestamp; `0040B410`, `0040B800`, `0040B990` consume matching marker `epoch` or `epoch-1`, writing `-10` sentinel. Source pointers are separate from markers.

## Priority 1 — World object creation, reference invalidation and teardown (high impact; not closed)

**Chain:** active object registration `004572B0 -> 00409850` (indirect callback registered by `00409BD0` using `00457270`); mission actors bind through `00412400 -> 00457630` and reference increment `0045ED00`; destruction/unregistration `00457420` invokes world-tree callbacks, including `00409980`, and cleanup via `0045EF70`. Original PE bytes at `00409980–00409BBC` reveal a genuine unregistration routine that removes a vehicle from team bucket arrays `00507DA0/0051F5D0`, clears references at mission-actor record `+0x58` and AI `+A9B4`, and sets AI invalidation marker `+A714`. The **v76 Ghidra function inventory has no function at `00409980`** (`is_exact_entry=false`), preventing proper decompilation/call-graph ownership. Investigate callback registration/invocation order, whether scripts can still hold stale entity pointers, effects of remove/re-register, and mission unload/destruction sequencing. Resolve `00409980` ownership first; then inspect refcount helpers' return/error contracts and host-command resolution of null actor bindings.

## Priority 2 — Collision/physical damage event ingress (high impact; partial)

**Chain:** collision/weapon/physics dispatch -> class-specific damage (`00462040`, class table) -> vehicle part/death (`00463A80`, `00465AF0`, `00466180`, `00465370`) -> event write `004157A0` (direct and radial dispatch at `004A821C`, `004A8298`) -> FSM queries. Network state ingress `00464890` is a distinct producer of death-related changes. There are **seven** original-PE static descriptors whose callback pointer is `0041C2C0`, tagged ASCII `clsnDmg`, with prior descriptor DWORDs 2/3/4 (`004C5234`, `004C78DC`, `004C8C30`, `004C9F84`, `004CB2D8`, `004CD980`, `004CECD4`). Function `0041C2C0` compares AI-private `+A6D8` with the shared epoch; its current name `is_ai_vehicle_target_matching_current_player_or_actor` is inaccurate. The descriptor evaluator and its caller cadence are **not** established in v76. Trace the consumer of these descriptors and who writes event state during collisions and vehicle-vs-world contacts; verify duplicate hits, suppression flags, time of update and source reference lifetime. Do not equate a descriptor label with a confirmed runtime invocation path.

## Priority 3 — Overall frame chronology and game mode gates (high impact; partial)

The **order within** `0040A320` is established. The order **around** it is not: engine main loop (`00403DDF` seen previously), physics/collision callbacks, world-object registration/unregistration, damage source writes, game time advance, and rendering/input events must be placed on a full frame timeline. `0051F640` skips the entire FSM/epoch update; `0051F5C0` replaces the VM pass with AI-only targeting (one observed mutation path `0040A050`, itself invoked from `0044BEAC`). Identify all writers to both gates, how often outer update runs, and whether damage can occur before, during or after a scheduler pass. Epoch E/E-1 predicate logic is verified, but *when an event is seen or missed* cannot be proven by static local functions alone.

## Priority 4 — Host-command dependencies and AI/navigation/combat (high to medium impact)

Host command-ID resolution `00410A10` and dispatch `00412CE0` are mapped structurally; this does not prove all 96 command effects. High-impact commands read or mutate: AI tactic/aggression/avoidance state, target and follow behavior, steering/braking, pathfinding and obstacle/terrain tests, ammo/visibility, weapon firing, and vehicle health/damage. Resolve commands by actual **mission-corpus frequency** rather than by name alone, and follow each into its producing/consuming engine service. Important source of uncertainty: FSM-visible conditions (e.g., arrival, within nav, enemy nearby, ammo thresholds, callback-ready) may depend on physics, pathing and asynchronous state that a standalone interpreter cannot synthesize from script bytes.

## Priority 5 — Mission control, timers, resource-side callbacks and media (medium impact)

`004149F0` checks mission-flow timeout; dispatcher `00412CE0` handles objective success/failure, timers, camera, speech, and callbacks. The `0040C020` function named `fsm_stop_callback_handler` calls `00423620` with the literal `STOPCBXX`; it does *not* touch the pending node list. `004122D0` checks WAV/SMK availability. Trace timer clock source, callback queue and `cb`/`cbFrom`/`cbPrior` semantics, mission state transitions, and effect/audio completion if real missions depend on them. Distinguish independent event systems rather than assuming callbacks create new `0x10BC` VM nodes.

## Priority 6 — Network/alternate modes (lower priority for single-player replay)

`0040A320` switches off normal script traversal in certain network/trip modes and under an execution gate. `00464890` consumes network vehicle state and has its own destruction route. Reconstructing multiplayer authoritative updates and replication is separate from faithful single-player mission replay. Document now; implement later unless single-player tests show a dependency.

## Separate broader-engine reconstruction areas (not blockers for FSM core)

Road mesh and material/UV assembly from the RSEG renderer, LUM/TBL/PCF lighting and palette fidelity, terrain/streamed scenery, texture and effect rendering, UI/HUD, audio, cutscenes, and network simulation still have varying degrees of unverified implementation based on previous project work. The **current v76 artifacts do not quantify coverage of these subsystems**, so do not infer that they are finished or unfinished solely from this export.

## Recommended next pass and acceptance criteria

**v77 — VOM identity, collision-event ingress and frame ordering closure:**
1. Create or verify a correctly bounded Ghidra function at `00409980` (guard against overlap); decompile it, gather its indirect callers, and establish world-tree removal/mission actor reference ownership through `004572B0`, `00457420`, `00412400`, `0045ED00`, `0045EF70`, `00457630`.
2. Locate the registration/iteration/evaluation of `clsnDmg` descriptors and prove the indirect call into `0041C2C0`; inspect physical collision + damage ingestion into `004157A0` and its event classification.
3. Trace top-level frame order around `0040A320`, all writers to `0051F640`/`0051F5C0`, and the game-time source to show when collisions and other callbacks change FSM-observable state relative to epoch increment.
4. Use the existing 25-mission corpus to construct integration tests for at least two simultaneous nodes, event consumption order, object disappearance, fatal-damage credit, and a timer-triggered objective transition. Reconcile failures against retail traces rather than guessing behaviors.

**Overall assessment:** Loader, VM and node-scheduler *mechanics* are high-confidence and ready for implementation. VOM ownership and object invalidation, collision ingress and top-level update chronology are the biggest remaining *causal* uncertainties. A working interpreter is not yet the same as a validated full mission simulation. Explicitly distinguish static verification from runtime execution in all commits.
