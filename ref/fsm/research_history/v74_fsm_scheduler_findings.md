# Interstate '76 — v74 FSM scheduler / epoch review

**Evidence:** user-supplied Ghidra exports (`i76_v74_fsm_calls.tsv`, `i76_v74_fsm_decompiled.txt`, `i76_v74_fsm_epoch_xrefs.tsv`, `i76_v74_fsm_functions.tsv`, `i76_v74_fsm_windows.tsv`), obtained from the original `i76.exe`. This is static reverse-engineering, not a runtime test.

## Export validation

- 19 function records; 92 incoming/outgoing call-edge records; 6 direct xrefs to `0x00524550`; 353 targeted assembly rows (excluding file headers).
- Direct references to the event epoch: reset `004155E0`, increment `004155F0`, read `00415600`, and three reads in the event producer `004157A0`. The direct-reference inventory is explicitly not exhaustive for indirect accesses.
- Required scheduler calls appear at `0040A644` (pending FSM), `0040A64E` (AI-only branch), `0040A653` (progress comparison), and `0040A658` (epoch increment).

## Frame dispatch

`update_fsm_vehicle_runtime_frame` (`0040A320`) skips its normal body, including the epoch increment, when `DAT_0051F640 != 0` (`0040A32C–0040A338`). Otherwise it resets/commits progress/control state, iterates vehicle precompute, and takes ONE of the following branches:

- **FSM branch** if `is_network_or_trip_runtime_mode()` returns zero AND `DAT_0051F5C0` is zero; direct call `0040A644 → 004149F0`.
- **AI-only branch** otherwise; direct call `0040A64E → 0040A130`.

They converge at `0040A653 → 00414B60` (progress comparison), then `0040A658 → 004155F0` (epoch increment). This is an ordering in the normal body; the observed top-level caller `00403DDF` is a separate question from whether other entry points or effects can influence the condition.

## Scheduler node lifetime

At `process_pending_fsm_instruction_list` (`004149F0`):

- The first VM callsite is `00414A58`; the following-nodes callsite is `00414AE4`.
- VM `00414670` returns `0` on opcode 10 (yield) and returns `1` on the terminal top-level return path of opcode 12; it may have additional fatal/error behavior.
- Return **1**: the scheduler decrements the active node count, unlinks the node from the `+0x10B8` singly-linked chain, and calls `HeapFree` (`00414A86`, `00414B12`).
- Return **0**: the scheduler retains the node, but advances to the next linked node instead of stopping the entire pass. It first drains completed head nodes; then traverses the remaining list once, removing completed later nodes and preserving yielded ones.
- These observations do **not** yet prove what happens if VM callbacks insert or reorder nodes during traversal, or how the initial head/count are seeded.

## Damage-event epoch semantics

`0x00524550` is a **shared per-update epoch**; `0041D240` also indexes a four-slot AI rolling drive-safety window by `(epoch mod 4)`. Hence 'unique event id' and 'current actor id' are potentially misleading names.

At `0040B410`, `0040B800`, `0040B990`, event markers are accepted if `marker == epoch` OR `marker == epoch - 1`; successful checks write `0xFFFFFFF6` (-10) as consumed. General attack-event consumption clears all three marker fields. The source-pointer slots remain independent. Thus an event recorded at epoch E is potentially visible in both E and E+1, but it may be consumed sooner, and a disabled frame cannot advance the epoch.

At `0041C2C0`, the current Ghidra name `is_ai_vehicle_target_matching_current_player_or_actor` does not fit the instructions: the function compares AI-private `+0xA6D8` against the shared epoch, not an actor identity. This should be reviewed for a later guarded rename after the caller's purpose is established.

## Next investigation: v75 pending-node creation and wake-up

**Primary question:** Which loader/callback creates an execution node and adds it to the pending list, and can host instructions enqueue another node during a pass?

Investigate the serialized FSM loader at `004102D0`, `00410490`, `004105A0`, `00410720`; mission registration at `00412400`; relocation at `00412500`; initialization/finalization at `00409850`, `004125C0`; and the dispatcher/scheduler at `00412CE0`, `00414670`, `004149F0`. Recover fields `+0x10A0…+0x10B8`, writers to global head `0051F628`, node count `0051F62C`, the FSM-enable gate `0051F5C0`, and outer-frame gate `0051F640`.

**Deliverable:** an explicit creation/append/remove/yield/wake model and a safe basis to implement a linked-list scheduler in the established mission interpreter, with no invented callback semantics.

## Checkpoint

Commit v74 exports, this report, and the exact Ghidra script. v75 investigation should remain read-only until field ownership and callback insertion order are verified. The generated v75 script filename and public Java class follow `i76_v[number]_[purpose].java`.
