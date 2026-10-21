# I76 retail mission-runtime research — v91: navigation, control queues, objectives and flow

**Program:** `i76.exe`, MD5 `a640ea0097dbb62e0c77b7f2847c7161`. **Baseline:** v90 annotated `.gzf`. **Methods:** Ghidra 12.1.4 native decompilation and instruction/displacement-reference scans. **Scope:** static original-engine analysis, not implementation or live game execution. **Date:** October 20, 2026 research session.

## Executive findings

The mission host VM coordinates at least **three independent completion mechanisms**; they must not be collapsed into a single generic `done` event:

| Script command | Host opcode | State read | Producer | Consumption rule |
|---|---:|---|---|---|
| `isArrived` | `0x28` | AI+`0x9C` | `00415020` sets it after final recorded path/route progress; `00420A20`/`00420AA0` reset when starting path following | **Consuming:** `0040B320` returns true only for 1 and clears it to zero |
| `isAtFollow` | `0x46` | AI+`0xA988` | `0041EF40` recomputes it from a three-dimensional proximity test between the actor and a target-space transformed local offset | **Consuming:** `0040BDF0` returns true if nonzero and clears it to zero |
| `controlDone` | `0x4A` | AI+`0xA6D0` | `0041F9C0` clears on any control-sample enqueue; `0041F8E0` sets when a dequeue drains the ring | **Non-consuming:** `0041FCE0` returns field value unchanged |

This table is anchored in opcode cases of `00412CE0`, Ghidra's actual functions, and direct instruction-address offset hits in `v91_displacement_candidates.tsv` (note that the broad displacement scanner is a candidate scan; the named producer/consumer routines independently prove register-base provenance by their decompilations).

### Follow proximity: `isAtFollow` is not a stationary Boolean

- `0041EF40 update_ai_vehicle_intercept_or_avoidance_drive` computes a local follow offset from AI+`A980/A984`, transforms that offset by the target object's world matrix, subtracts the follower's world position, and computes the 3D distance.
- It writes `(distance < threshold)` to AI+`A988` (`0041F0C0` instruction). It also handles steering and throttle behavior; the write is part of an AI update, not the VM command itself.
- `0040BDF0`, invoked by `isAtFollow`, checks and **clears** AI+`A988`. A later AI tick can recompute and reassert it. The nearest known writing sites are exactly this producer and the consuming clearing operation in the whole-program direct displacement scan.
- Hence two immediate `isAtFollow` queries may return true then false without another AI update, whereas two evaluations separated by a driving AI update may both return true. **Execution frequency and relative ordering in any concrete mission remain conditional.**

### Buffered controls: `controlDone` is the producer/consumer queue's drained marker

- The AI state constructor `00415640` initializes AI+`A6D0` to `1`.
- `0041F9C0 enqueue_vehicle_steer_brake_input_sample` stores six sample fields per entry, 0x18 bytes per entry, starting AI+`9D68`; validates steering and other bounded inputs; advances producer index AI+`A6CC` and wraps at **100**. It clears AI+`A6D0` to `0`. It reports an error if producer catches up with consumer.
- `0041F8E0 dequeue_player_control_input` reads and removes the next sample, advances consumer index AI+`A6C8` modulo **100**, and sets AI+`A6D0` to `1` when consumer and producer indices become equal. If already empty, it reports an error and returns zero.
- `0041FCE0`, used by opcode `0x4A`, returns AI+`A6D0` **without clearing**. The old symbol `get_ai_vehicle_damage_state_field_a6d0` falsely associated this queue with vehicle damage.
- This is a bounded, fixed-capacity FIFO with no separate count, not a damage flag or generic steering completion callback. Real-time enforcement/consumption is elsewhere in the vehicle control subsystem and was not exhaustively audited this pass.

### `isArrived` path progress is independent

- `004151F0 bind_ai_path_state_to_path_record` binds the route record at AI+`88` and reads route header+`50` to AI+`A4`; it also resets path progress offsets.
- `00420A20` and `00420AA0` both begin forward path following, set AI+`84=2`, and clear AI+`9C`; the latter can also scan for threats when the previous flag was clear.
- `00415020 update_ai_path_waypoint_progress_state` advances path nodes using horizontal world-space coordinates and the current segment; on completing the final route progress record, sets AI+`9C=1`. Other path-status fields include AI+`94`, `98`, `A0`, `A4`, `A8`.
- `00420B30` and related path-following drive routines invoke waypoint progress and then choose steering/throttle/braking; `00420D30` can run A* path search and coordinate with a global AI/FSM lock.
- `0040B320` consumes arrival once. Thus **route arrival and follow-target proximity are different event sources**.

## Mission objective transition flags

**Confirmed objective functions:** `0045E960 reveal_mission_objective`, `0045E9E0 mark_mission_objective_succeeded`, `0045EA90 mark_mission_objective_failed`. In these routines, input objective IDs are **1-based**, converted to zero-based array indices (`arg-1`) and bounds-checked against `DAT_006093C0`; entries at `DAT_006093C8` must exist.

At `DAT_00609420 + 4 * index`, the observable flag bits are:

- `0x01`: hidden / not yet revealed (reveal clears this bit).
- `0x02`: succeeded (success sets this bit, refusing an already failed flag).
- `0x04`: failed (failure sets this bit, refusing an already succeeded flag).

`reveal` triggers `cnote.wav`; first `success` also triggers the same sound; `fail` does not call the sound enqueue routine in its audited body. `reveal` reports an error if its hidden bit is already clear; success/fail report errors for missing indices and conflicting existing state. Do not assume `report_error()` is nonfatal, or that all error paths continue into mutation; this is native decompiler control flow, not a live behavior test. The objective notepad's UI and localized text loader are separate from these state transitions.

**Global mission outcome timing is separate from objective flags.** `successAll` (`0x0F`), `failAll` (`0x11`), and `failAllObj` (`0x12`) write `g_fsm_game_flow_timeout_seconds` at `005244E0` as gameplay time plus the script delay and set `g_fsm_game_flow_timeout_next_state` at `005244E4` (success `1`, failure `0`). The `failAllObj` case additionally invokes `0045EB30` to store a zero-based objective-context index at `00609438`. The pending-FSM-node scheduler `004149F0` checks the gameplay deadline and invokes `set_game_flow_state` when due. That is a deferred game-flow transition; it is **not** simply marking each objective complete immediately.

### Teleport is a simulation-state operation

`00414BC0 fsm_teleport_object` reads a script navigation position, optional offsets, speed and heading. It validates the angle, constructs a transform and copies sixteen words into `object+0x18`; updates world-object position/terrain-derived height; sets vehicle runtime velocities from the actor's current basis vectors and speed; resets selected runtime motion fields; calls `mark_active_player_object_control_changed`. `teleport` and `teleportOffset` both reach the same behavior with different operand preparation. This does not directly advance the `isArrived` flag; the decompiled teleport routine has no write to AI+`0x9C`.

### Camera completion is another independent consuming state

`0049D730 mission_flow_map_context_helper_0049d730` returns `DAT_005A7ED8`, then clears it to zero. It is reached by `camIsArrived` (`0x3D`) rather than by the AI route predicates. The inspected camera setup functions reset this camera-state flag. The producer of the **nonzero** camera-arrival state is outside the narrowed follow/AI closure, so do not conflate it with vehicle arrival, or assign it the same update cadence without further analysis.

## Symbol correctness and Ghidra checkpoint

Four guarded, high-confidence corrections were applied **only** to a disposable Ghidra project and packed as `i76_mission_v91_verified_names.gzf`:

| Address | Former v90 name | Verified v91 name |
|---|---|---|
| `0040BDF0` | `fsm_query_is_at_follow_target` | `fsm_consume_ai_at_follow_proximity_flag` |
| `0041FCE0` | `get_ai_vehicle_damage_state_field_a6d0` | `fsm_query_vehicle_control_queue_drained` |
| `0045EB70` | `mission_objective_notepad_context_helper_0045eb70` | `initialize_world_object_and_aux_heaps` |
| `0045EBA0` | `mission_objective_notepad_context_helper_0045eba0` | `destroy_world_object_and_aux_heaps` |

The last two had been mislabeled as objective-notepad operations: their bodies instead call `HeapCreate`/`HeapDestroy` for `g_world_object_node_heap` and `DAT_0054AD38`. They clarify low-level memory ownership without changing runtime behavior.

**Validation:** 51/51 initial native decompilations; 35 follow-up native decompilations; 15 producer-path decompilations; separate fresh GZF reimport checked nine function names plus the retail MD5 (10/10 passed). Distinct functions overlap between passes. Ghidra did not run gameplay; no engine-reimplementation code was created. The original v90 imported program and the retail executable were not modified.

## Important limits and potential future behavioral tests

1. `isAtFollow` true/false back-to-back without an intervening `0041EF40` update, and subsequent reassertion on later behavior updates.
2. `isArrived` true/false consumption, with a new route begin resetting the flag and a completed waypoint causing the producer write.
3. Queue fill/dequeue through the 100-entry ring; `controlDone` transitions `1 -> 0 -> 1`, including wrap and collision behavior. Verify who triggers the runtime dequeue, not merely the queue helper.
4. Objective `reveal`/`success`/`fail` transitions from both visible and hidden states, including invalid IDs, replays, and the notification sound.
5. `successAll`/`failAll` schedule a terminal flow change; run a simulated deadline crossing with pending VM nodes to establish whether the scheduler continues other VM nodes after the change.
6. `teleport` while following a route: confirm motion-state reset and whether completion flags persist until a new path-start routine runs.
7. Camera `camIsArrived` event producer and its own update scheduling; do not guess that it is AI/vehicle completion.

All test descriptions are deferred specifications for an eventual engine validation pipeline; no replacement behavior has been programmed here.

## Next prioritized research

Trace the **global AI/FSM path-lock and control-buffer dequeue scheduler** (especially `00420D30`, `0041F8E0` callers), and the **objective deadline to game-state transition** (`004149F0` → `set_game_flow_state` → shell/game loop). This is now a more productive integration question than treating navigation commands as independent opcodes.
