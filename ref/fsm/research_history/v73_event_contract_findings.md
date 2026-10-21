# Interstate '76 — v73 event contract findings and v74 handoff

Date: 2026-10-19 (America/Los_Angeles). Target: original retail `i76.exe`, MD5 `a640ea0097dbb62e0c77b7f2847c7161`. Evidence is **static Ghidra/PE analysis**, not runtime observation.

## Input validation

Reviewed the supplied five v73 exports:

- `i76_v73_fsm_event_functions.tsv`: 30/30 requested function entries resolved.
- `i76_v73_fsm_event_edges.tsv`: 727 call-reference records, 491 outgoing and 236 incoming. These are references, not unique calls or an execution trace.
- `i76_v73_fsm_event_instructions.tsv`: 5,751 instruction records spanning the 30 focus functions.
- `i76_v73_fsm_event_fields.tsv`: 280 displacement candidates: 240 `[base+0x454]` matches and **40** event-private (`+0xA6D4` through `+0xA6F0`) matches. The scan is heuristic: bases need dataflow review.
- `i76_v73_fsm_event_decompiled.txt`: current-program decompilation confirming initializer/producer/consumer contracts.

The 18:34 Ghidra state ZIP and the original game executable were also independently inspected to resolve the previously unexported counter accessors and main-loop callsite. Original executable MD5 checked.

## Event state model (high confidence for explicit instructions)

The global `g_vehicle_damage_source_event_state` is at **0x00524550**. Ghidra's references index identifies these direct accessors:

| Address | Operation | Direct source |
|---|---|---|
| `004155E0` | Reset global epoch to 0 | `mov dword ptr [00524550], 0` |
| `004155F0` | Increment global epoch | `inc dword ptr [00524550]` |
| `00415600` | Read global epoch into EAX | `mov eax, [00524550]` |
| `004157A0` | Stamp event metadata from global epoch | Several global reads in this producer |

The event-bearing AI-private memory fields are **not equivalent to a single damage Boolean**:

| AI offset | Producer `004157A0` / consumers | Contract |
|---|---|---|
| `A6D8` | `0041583C`; `0040B800`, `0041C2C0` | Event epoch for ramming/general non-special category |
| `A6E4` | `00415836`; `0040AFF0` | Ram/source object pointer |
| `A6D4` | `0041584F`; `0040B410` | Event epoch for special/shot category |
| `A6E8` | `00415849`; `0040B0F0` | Shot/source object pointer |
| `A6DC` | `00415861`; `0040B990` | General attack epoch |
| `A6EC` | `0041585B`; `0040B1F0` | General attack source object pointer |
| `A6E0` | `00415884` and `00415893`; `0040B860` | Conditional/sticky primary-actor fatality attribution |
| `A6F0` | `0041586C`; `00420C42` | Gameplay timestamp used elsewhere by AI |

`00415640` initializes event epochs to `0xFFFFFFF6` (-10), source pointers to null, attribution to zero, and timestamp to zero.

For accepted events, `004157A0` checks category flags and the source object. A qualifying source is always written to the general attack slot. Its category-specific slot update is conditional. The dead-car state (`vehicle runtime+0x454` bit `0x20`) gates attribution (`A6E0`), but **does not gate the source-event ledger**. The normal direct/radial damage call path applies class damage before recording the source event, as already established in v72.

## Consume semantics

`0040B410` (FSM opcode `0x20`) compares `A6D4` against `global_epoch` or `global_epoch - 1`, returning 1 and setting **only A6D4** to `-10` on a match. `0040B800` (opcode `0x23`) does the same to **A6D8**. `0040B990` (opcode `0x2D`) checks **A6DC** and, on success, clears **all three event epochs**: `A6D4`, `A6D8`, and `A6DC`. Nonmatches return zero without clearing the fields.

These are **consuming** FSM predicates. For a stamped epoch `N` their numeric match is true while the global epoch is `N` or `N+1` *unless they have been consumed or overwritten*. The real interval in frames depends on callback order and gate/branch timing: do not call it exactly two rendered frames without validation. In particular, the global epoch is not proven to advance during paused/guarded calls.

`whoRammed` (`0x0B`), `whoShot` (`0x0C`) and `whoAttacked` (`0x2E`) instead retrieve `A6E4/A6E8/A6EC`. They search the script-visible object table in `0x60`-byte records, create a label/slot on a miss, store the pointer, and increment its reference count. They **do not consume** the marker epochs. The source identity may therefore remain available after its marker becomes stale. Object resolution by the host dispatcher should not be presumed to be a pure lookup; the existing v61–v63 reconstruction documented possible refcount/lifetime side effects.

## Crucial scheduler branch and epoch ordering (verified against original executable)

The v73 exported functions did not include `0040A320` or `004155F0`; these were recovered from the earlier uploaded 18:34 Ghidra snapshot (`references_from_instructions.tsv`) and the original retail executable's x86 instructions.

`update_fsm_vehicle_runtime_frame` (`0040A320`) begins with a guard on global `0051F640`: nonzero jumps to the function epilogue at `0040A6DF`, **skipping the epoch increment**. The meaning and writers of that guard must be investigated rather than assuming it is always a pause flag.

Near the end of the active path:

- `0040A5D0`: calls `is_network_or_trip_runtime_mode`; nonzero branches to `0040A64E`.
- `0040A5D9`: compares `0051F5C0` to zero; nonzero also branches to `0040A64E`.
- Otherwise `0040A644` calls `process_pending_fsm_instruction_list` (`004149F0`).
- `0040A64C`: `jmp 0040A653`, skipping the alternative AI path.
- `0040A64E`: alternative call to `update_all_ai_vehicles_against_active_player` (`0040A130`).
- **Both** active branches converge: `0040A653` calls `update_fsm_runtime_progress_compare_state` (`00414B60`); `0040A658` calls `increment_vehicle_damage_source_event_state` (`004155F0`).

Thus **VM processing and AI update are alternative branches**, not both guaranteed in a single frame. A prior provisional interpretation listing these calls sequentially has been corrected by direct x86 assembly. The call order establishes a synchronization point *on active execution paths*, not necessarily per rendered frame or with an independently known clock cadence.

`process_pending_fsm_instruction_list` directly invokes `execute_fsm_vm_token_stream` (`00414670`) at `00414A58` and `00414AE4`, presenting two VM execution paths. Their iteration and ordering are v74 priorities.

## Semantic rename to review (not applied)

`0041C2C0` is currently named `is_ai_vehicle_target_matching_current_player_or_actor`. Its decompilation actually compares **AI+A6D8 with `get_vehicle_damage_source_event_state()`**. It does not compare an object pointer with the player identity. This symbol is likely misleading and should be revisited after analyzing callers. v74 deliberately preserves the existing name until the surrounding AI behavior is understood.

## Next investigation: v74 scheduler and event delivery

Ghidra script: `i76_v74_fsm_scheduler_event_timing.java`. **Read-only**. It checks executable identity, prior repairs/renames, the branch's byte signatures, and six exact callsite references before exporting:

1. `i76_v74_fsm_functions.tsv` — scheduler, token VM, damage epoch accessors, consumers and AI call ownership.
2. `i76_v74_fsm_calls.tsv` — incoming/outgoing direct call edges for 19 target functions.
3. `i76_v74_fsm_epoch_xrefs.tsv` — all Ghidra references to global `00524550`, with per-instruction context.
4. `i76_v74_fsm_windows.tsv` — focused assembly for the early exit, network-vs-FSM branch, epoch update, VM paths, and marker consumption.
5. `i76_v74_fsm_decompiled.txt` — complete focused functions including `0040A320`, `004149F0`, `00414670` and accessors.

Output folder: `/media/neon-remote/prj/i76/scratch_data/`.

**Priority questions:** When is the FSM pending list built, in which order are nodes executed, when are callback requests enqueued and drained, does VM execution occur before new damage events during the same game tick, how does `0051F640` suppress the epoch, and which paths omit `0040A658`? Follow the existing v60–v63 interpreter contracts rather than inventing a new VM layout.

## Proposed deterministic tests for the existing interpreter (not yet integrated)

- Event stamped at epoch N: each matching predicate recognizes N and N+1, fails by N+2; a successful test consumes its designated marker(s).
- Querying `whoShot`/`whoAttacked` resolves a persistent source ID independently of epoch consumption.
- A successful general-event predicate clears the ram and shot markers even if their own predicate has not yet been tested.
- A nonmatching predicate leaves its marker intact; subsequent newer event overwrites relevant category source and epoch slots only.
- If the frame driver takes the `0051F640` early exit, event epoch does not increment.
- Test the actual FSM/AI branch choice after v74 decompilation before implementing a whole-world scheduler.

These test scenarios are inferred from static instructions and should be integrated with the already-existing v60–v63 regression suite after scheduler details are established; they are not reported as executed mission tests.
