# I76 retail mission execution — v93 FSM ordering, reentrancy and shared effects

**Date:** 2026-10-20. **Retail `i76.exe` MD5:** `a640ea0097dbb62e0c77b7f2847c7161`. **Tools:** native Ghidra 12.1.4 decompiler and program reference/instruction manager, working from the annotated **v92** `.gzf` baseline; independent saved static-evidence assertions. **Scope:** analysis only, no reconstructed runtime, gameplay execution, or source modifications.

## Executive results

1. The mission scheduler (`004149F0`) is a deterministic, cooperative **forward traversal of a singly linked list**. Each VM node (`0x10BC` bytes) is run until `yield` (VM token `0x0A`, return status 0) or top-level frame completion (VM token `0x0C`, return status 1). Yielding preserves a node; completion decrements list count and frees that node.
2. After the head yields, the scheduler visits following nodes in list order **in the same scheduler invocation**. It never restarts the head after later nodes. Every pending node is eligible to run once per scheduler pass, unless earlier completion removes nodes or a fatal handler interrupts execution. A script can carry out many operations in one pass before yielding; there is no instruction-by-instruction interleaving between nodes.
3. FSM host command token `0x0D` calls dispatcher `00412CE0` **synchronously**. Eight direct call sites within that dispatcher enter the separate AI behavior evaluator `00412830`. The AI evaluator can run table-driven predicates, callbacks and transitions immediately and returns before the calling FSM node advances to the next instruction.
4. **Shared state makes list order observable**: damage-epoch predicates consume markers; `who*` source lookups do not require the corresponding epoch; AI current-epoch normal-damage observer `0041C2C0` is nonconsuming. An earlier script node can therefore mask a later node's view of the same damage event. The `isAttacked` predicate at `0040B990` clears three epoch slots in one operation.
5. **The AI weighted behavior selector and FSM `rand` command share C runtime `rand()`** (`[004BC20C]`), confirmed at `00412739` and `004133B9`. A synchronous AI transition can shift subsequent script random draws, and earlier script draws can shift AI outcomes.
6. **Node creation is load-time in the observed static paths.** `00410490` allocates and initially links `0x10BC`-byte nodes; `00412500` performs relocation and context initialization. Direct writes to the `+0x10B8` list-next field in the 232,525-instruction program scan occur in the loader and scheduler, not in AI or host dispatcher paths. This does not rule out indirect/computed addressing or unusual binary paths, but no normal host command to launch additional VM nodes was established.
7. The per-node execution loop **does not yield on its budget warning**: after 800+ previously executed instructions it sets global `g_fsm_vm_instruction_budget_exceeded`; after the 1000-instruction threshold it invokes `exit(0)` if it has not yielded or completed. This is a hard failure mechanism, not cooperative time slicing.

## 1. Scheduler sequence, verified directly

`0040A320 update_fsm_vehicle_runtime_frame` calls `004149F0 process_pending_fsm_instruction_list` only under its normal mission scheduling gate (`!is_network_or_trip_runtime_mode()` and `DAT_0051F5C0 == 0`, plus its outer `DAT_0051F640 == 0` condition). Then `0040A658` increments the shared damage epoch through `004155F0` **after** the scheduler/alternate AI path returns.

Inside `004149F0`:

- Compare elapsed mission clock against `g_fsm_game_flow_timeout_seconds` **before** checking whether any node is pending; set the game-flow state if due.
- Evaluate the head node at `00414A58`. If complete, unlink it by replacing the head pointer with `head->next` (`+0x10B8`), decrement count and `HeapFree`. Continue running the new head while previous heads have completed.
- When a head yields, retain it as head. Start traversing its successor, invoking VM at `00414AE4`. If each successor yields, follow its `next`; if it completes, relink the predecessor to successor's next, decrement count, and free the completed node.
- No immediate stop condition is tested on `g_game_flow_state` within the body after the initial timeout check. Thus a due timeout does not automatically prevent later nodes from running during that same pass. This matches v92's loop-exit analysis.

Machine-code evidence: `v93_instruction_assembly.tsv` `004149F0` rows `00414A58`, `00414A74–00414A86` and `00414AE4–00414B30`. Native decompilation: `v93_native_decompiled.txt`.

**Boundary:** If a command has unusual side effects that alter links through indirect aliases, scheduling behavior would require a follow-up trace. None was demonstrated in this pass.

## 2. VM node context and control transfers

The loader `00410490` reads serialized initial-node records, allocates a linked list with stride `0x10BC`, writes `+0x10B8` links, and leaves the last link null. `00412500` relocates context-word pointers and initializes each node's VM fields:

| Node offset | Established meaning |
|---|---|
| `+0x10A0` | Per-node Boolean condition/result, used by VM branch and negation tokens |
| `+0x10A4` | Base address of the shared token stream |
| `+0x10A8` | Current token-stream instruction pointer |
| `+0x10AC` | Call-frame/context base pointer |
| `+0x10B0` | Operand stack cursor |
| `+0x10B4` | Host-command argument cursor |
| `+0x10B8` | Next runnable VM node |

Key VM tokens:

| VM token | Role | Scheduling implication |
|---|---|---|
| `0x08` | Absolute token-index jump | Continues executing same VM node |
| `0x09` | Conditional jump if per-node result false | Consults `node+0x10A0` |
| `0x0A` | Yield to saved token index; VM returns **0** | Scheduler preserves node and advances to next |
| `0x0B` | Call subroutine / push VM frame | Remains inside current node |
| `0x0C` | Return from frame; VM returns **1** only if outermost frame closes | Completed node unlinked/freed |
| `0x0D` | Dispatch 96-ID host command table | Host side effects synchronous |
| `0x0E` | Negate result flag | Changes only current node's result |

Neither 800-instruction warning nor the 1000-instruction fatal threshold is a scheduler-level yield. `local_54` starts at zero on every call to `00414670` and tracks work within that invocation, including VM-level subroutine calls.

## 3. Synchronous AI and shared effects

The eight direct host->AI call sites are `00412DAC`, `00412DEF`, `00412E32`, `00412E9C`, `00412F11`, `00412FAD`, `00413049`, `00414046`. All are inside `00412CE0`, called directly by VM at `00414949`.

`00412830` runs AI predicates via pointers from its behavior table (`0x1354` stride), can invoke entry/update actions and first-satisfied state transitions, and can evaluate weapon-fire requests. This occurs **within the active FSM command's C call stack**, before control returns to VM execution. This establishes nested ordinary function calls, **not recursive entry into the mission VM**. `00414670` has only two direct call sites, both in scheduler `004149F0`; the scheduler has one direct call site at `0040A644`.

Damage-event ordering:
- `record_vehicle_damage_source_event` (`004157A0`) caches source object at `AI+A6E4/A6E8/A6EC` and stamps corresponding epoch fields `A6D8/A6D4/A6DC`.
- FSM damage predicates `0040B800`, `0040B410`, `0040B990` accept current or prior epoch and clear selected marker(s) to `-10` on success. `0040B990` clears all three.
- AI behavior predicate `0041C2C0` compares `A6D8` to the **current** epoch without consuming it.
- `who*` actor lookup commands can read the cached attacker identity after consumption because the identity pointer and event marker are separate.

These mechanics support conditional ordering examples; they **do not prove** a given retail mission exercises every possible sequence or that AI behavior produces physical damage immediately upon evaluation.

Randomness: both `00412680` and host command `rand` case `0x0A` invoke the imported CRT `rand()` at `004BC20C`. If the AI selector is entered, its draws change the shared PRNG sequence available to other script nodes. Exact draws depend on AI state and selector branch conditions.

## 4. Game-flow changes and scheduling

The pending-result timeout is checked at the top of `004149F0`, not after every VM token. A `successAll`/`failAll` command that sets a deadline while running normally will not cause this scheduler to recheck that deadline until a later invocation. In contrast, a deadline already expired at entry sets the game-flow state before the node traversal, but remaining nodes can still execute in the same call. The top-level frame loop observes changed game-flow state at its next active-loop condition, as established in v92.

Thus completion events and mission-game-flow termination should be treated as **ordered state transitions**, not exceptions or immediate VM aborts.

## 5. Confidence and exclusions

**High confidence, source backed:** loader allocation/links, node offsets, scheduler list order and remove/retain semantics, host->AI direct call sites, shared `rand` import, event predicate differences, epoch advancement placement, VM budget behavior. These were re-decompiled in Ghidra 12.1.4 against v92's named database and independently verified from instruction rows.

**Conditional:** actual frequency of AI state changes in retail missions; indirect or computed modification of VM list; runtime callback recursion outside the direct callgraph; exact wall-clock/frame interleavings from real gameplay; whether damage events are produced by particular host commands in the same VM turn.

**No live tests** and **no source reconstruction** performed. No Ghidra symbol changes were necessary. All v92 names remain the baseline.

## 6. Next research question

A productive next pass is the **mission VM bytecode, call-frame and per-node storage invariants**: valid stack bounds, all 14 token semantics, function call/return stack layout, and parser/loader validation. It would clarify exactly which serialized script sequences are legal and provide stronger unit-test oracles for later validation, without building an interpreter now.
