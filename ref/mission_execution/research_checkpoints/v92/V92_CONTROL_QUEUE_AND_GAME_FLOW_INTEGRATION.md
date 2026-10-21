# I76 retail mission execution architecture — v92 control queues and game-flow integration

**Date:** 2026-10-20. **Executable MD5:** `a640ea0097dbb62e0c77b7f2847c7161`.
**Program:** read-only v91 symbol snapshot imported into local Ghidra 12.1.4; three guarded renames applied only in separate disposable project and packed to the v92 GZF. **Scope:** reverse engineering; no reimplementation, runtime patching, or live gameplay tests.

## Executive findings

The control-sample queue is **explicitly clocked by the FSM host command `driveControl` (0x49)**, not automatically popped by the ordinary vehicle physics update. The mission VM can enqueue controls (`control`, `controlAll`) and subsequently advance them with `driveControl` at a cadence governed by the script's own VM instructions. `controlDone` is a *nonconsuming* query for the queue's drained flag. This resolves the major scheduling uncertainty left in v91.

Mission completion follows a separate state transition: the host commands `successAll`, `failAll`, `failAllObj` write an elapsed-clock deadline and result value; `004149F0` checks the deadline before iterating pending VM nodes (including when the node list is empty), then calls `00402620` to update `g_game_flow_state`. The top-level game loop at `00402B30` runs while that state equals **5**. On completion, it leaves the active-loop body and executes outcome-specific postgame behavior. This is not a per-objective immediate termination mechanism.

## 1. Four host commands and the control queue

| Command | Opcode | Code | Verified side effect |
|---|---|---|---|
| `control` | 0x47 | dispatcher -> 0041FB90 -> 0041F9C0 | Derives six-component control record from current vehicle/queue history and appends it |
| `controlAll` | 0x48 | dispatcher -> 0041F9C0 | Appends explicit values into the per-vehicle ring |
| `driveControl` | 0x49 | 004141BC -> 0041FC40 -> 0041F8E0 | **Applies precisely one** queued control record to vehicle runtime, if vehicle is eligible |
| `controlDone` | 0x4A | dispatcher -> 0041FCE0 | Reads AI+A6D0 without clearing it |

Read-only Ghidra reference-manager audit:
- Only direct caller of `0041F8E0`: `0041FC40` at `0041FC8F`.
- Only direct caller of `0041FC40`: `00412CE0` at `004141BC`.
- Only direct callers of `0041F9C0`: `0041FB90` at `0041FC32` and `00412CE0` at `00414184`.
- `0043A3C0` vehicle control/drivetrain update is called by `00463800` class-1 pre-update. It reads the vehicle control state but does **not** invoke the queued-input dequeue routine.

`0041F9C0` creates a 0x18-byte record in the 100-element ring starting at AI+9D68, increments producer index AI+A6CC modulo 100, and clears AI+A6D0. `0041F8E0` reads the record at consumer index AI+A6C8, increments modulo 100 and sets AI+A6D0 when the two indices become equal. The two-equal-indices empty/full representation and error check when enqueue catches the consumer imply the permitted effective capacity must be treated carefully; there is no evidence for silently overwriting records safely.

`0041FC40` writes dequeued values into vehicle runtime +E4, +E0, +F0, +E8 (the other two sample fields are read into locals); it returns without dequeuing if the vehicle runtime `+454` bit `0x20` is set, although it still calls the active-control-changed function. On attempted dequeue from an empty ring, the producer reports an error, and `0041FC40` resets vehicle control values and invokes `00467370` with mode 3. The handling/severity of `report_error` is not established by this pass.

**Scheduling constraint:** there is only one known direct route to dequeuing a script sample, via the explicit host command. This is a static callgraph conclusion; unexpected indirect entries cannot be wholly ruled out. Sequential `driveControl` instructions in one VM frame could consume multiple samples before the next drivetrain update. Conversely enqueued samples do not progress across frames unless script execution invokes the consumer.

## 2. Mission result clock and gameplay state

- `0x0F successAll`: sets `g_fsm_game_flow_timeout_next_state=1` and `g_fsm_game_flow_timeout_seconds` (`005244E0`) to mission elapsed time + scripted delay.
- `0x11 failAll`: similarly sets result 0.
- `0x12 failAllObj`: sets result 0 and additional objective-context field through `0045EB30`.
- `00412CC0` initializes timeout to IEEE float max (`0x7F7FFFFF`); no spurious timeout should occur before the script arms a deadline.
- `004149F0` evaluates timeout at the **start** of pending-script processing, before checking whether the VM-node list is empty, and calls `00402620` if due. Its remaining body still traverses runnable VM nodes after setting the flow state; a due deadline therefore does not directly interrupt the scheduler mid-call.
- `00402620` is a simple setter of `g_game_flow_state`; main loop `00402B30` is `while (g_game_flow_state == 5)` and subsequently branches on completion code. A completion set during a frame need not skip all later rendering/audio steps in that same iteration; the outer loop reevaluates the state at its next test.
- The post-loop code handles state 1 as a success-style transition (with an additional remapping to `0x0B` under condition `DAT_00535F78 != 0`), and states 0/0x0B via separate post-mission shell paths. Avoid treating `0x0B` as an ordinary failure synonym.

## 3. Deadline clock is not the clamped simulation time

`0049C7E0` directly reads the float at `005A7E14`. The clock initializer `0049C7F0` initializes that field to zero; `0049C920 update_runtime_clock_from_gettickcount` accumulates its raw `GetTickCount`-based interval **before** subsequently clamping the per-frame delta used by simulation. `0049C920` is called from top-level frame handling.

The clock has a warmup condition (counter `005A7E18` versus constant `004BE990`) and a pause-like early return when a non-gameplay display/input mode is active outside the suppressed-damage runtime. Thus a mission deadline can move differently from the clamped physics/control integration timestep on frame hitches or pause-like states.

This is a strong static semantic distinction; exact timing under all display modes and runtime state combinations has not been live-tested.

## 4. Proposed behavioral validation cases (for later, NOT executed)

1. Queue one control sample; verify `controlDone` false until a successful `driveControl` call, then true.
2. Enqueue N records; execute only N-1 driveControl commands; verify one remains and completion false. After Nth, completion true.
3. Enqueue two records, run two consecutive `driveControl` commands in one VM tick; determine whether only the final values reach the subsequent vehicle update.
4. Attempt `driveControl` on empty queue and on vehicle with `runtime+454 & 0x20`: record `report_error`, return mode, queue indices, output fields.
5. Cause a frame hitch while a delayed success/failure is pending: measure deadline elapsed clock versus clamped drivetrain delta.
6. Schedule a zero-delay result with no VM nodes remaining; verify scheduler still transitions when enabled.
7. Arm a deadline that expires before additional runnable VM-node work; verify what later same-frame commands can change before top-level game-loop exit.
8. Pause into a non-gameplay input/display mode; compare elapsed clock, global FSM epoch, and queue state on return.

## 5. Confidence and open issues

**High confidence:** direct caller relationships, queue offsets/strides, one-record dequeue, state setter, `==5` active-loop gate, command result values, timer initialization and read/write sites. All are native Ghidra decompilation plus reference/instruction evidence.

**Still conditional:** indirect call entries and dynamic scheduling, `report_error` fatality, queue overflow effects, mission-authored command cadence, exact frame synchronization, player-death control bit combinations, special post-mission branch meanings. No gameplay behavior is claimed to have been exercised.

## 6. Symbol corrections and original source-layout notes

In an isolated Ghidra project, three high-confidence corrections were guarded by exact old name and retail MD5, and the resulting `.gzf` was reimported into a third project to verify old and new annotations:
- `0041F8E0`: `dequeue_player_control_input` -> `dequeue_fsm_vehicle_control_sample`.
- `0041FC40`: `apply_player_control_input_to_vehicle_runtime` -> `apply_next_fsm_vehicle_control_sample`.
- `0049C7E0`: `mission_flow_map_context_helper_0049c7e0` -> `get_mission_elapsed_clock_seconds`.

These are semantic, reverse-engineering names; no original developer names are claimed. The mission elapsed-clock data global at `005A7E14` is identified but intentionally not renamed before broader global/time subsystem review.

The tight `0041F8E0–0041FCE0` queue implementation neighborhood is a strong candidate for a shared original source module. `0049C7F0–0049CBAC` groups related clock operations, and `00402610–00402620` groups flow-state accessors; they are separate clusters. Original `.c` and `.h` boundaries remain speculative; see `V92_SOURCE_LAYOUT_ADDITIONS.md`.
