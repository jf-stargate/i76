# I76 retail engine v89 — mission host command ABI and CB voice queue correction

**Research date:** October 20, 2026. **Executable:** retail `i76.exe` MD5 `a640ea0097dbb62e0c77b7f2847c7161`. **Tool:** native Ghidra 12.1.4 headless, using the annotated v81 project as immutable input; plus machine-readable validation and script-derived analysis. **Scope:** reverse engineering only; no game simulation or source reconstruction. New function labels were applied solely to a separately imported, writable program and independently reimport-verified.

## Executive result

**Most important correction:** The FSM `cb` host-command family drives a separate asynchronous CB voice-message queue, **not** the FSM virtual-machine node scheduler. Inherited names such as `update_timer_or_frame_delta` at `00423620`, `fsm_update_timer_with_script_type`, and `fsm_stop_callback_handler` were inaccurate. The previous interpretation mistook use of Windows `GetTickCount` for a mission timer. Ghidra machine code demonstrates that the routine manipulates 0x24-byte linked audio requests, sound objects and cockpit presentation. The opcode family includes `0x13 cb`, `0x14 cbPrior`, `0x15 cbFromPrior`, `0x4C isCBEmpty`, `0x4F cbFrom`, `0x50 killCB`, and `0x5F stopCB`.

A **previously unbounded executable callback** at `004238E0–00423A04` was defined in an isolated Ghidra project as `cb_voice_message_completion_callback`. Its execution releases a finished audio request and advances the queue. A real asynchronous callback exists, but it is an **audio callback**, not a queued FSM VM node.

## 1. Host command ABI: all IDs accounted for

`00412CE0 dispatch_fsm_host_command_record` uses the source command index to read its `0x54`-byte serialized command record (command opcode at `+0x50`), then switches through a 96-entry **absolute-address jump table at `004144E4`**. We independently read each u32 entry from the retail image through Ghidra memory (`v89_host_jump_table_raw.tsv`), rather than relying only on decompiler switch presentation.

* Exactly 96 slots indexed `0x00–0x5F`.
* 95 distinct machine-code destinations: `0x07 set` and `0x2F setId` share handler `00413F16`.
* `0x16 playScene` is recognized by the command-name resolver but has **no implemented case**: its table entry points to `004144AE`, the fatal/default path that calls `0042D5D0` and an imported abort/exit callback.
* Every other named opcode has a table destination; this **does not prove** the called helper is fully implemented. For instance `behave`, `do`, `test`, and `isLit` call functions identified as unimplemented placeholders in the imported database.
* Host commands use operand stack/pointer slots beginning at VM-node `+0x1000`; the source command *record index* is converted to a record at `source_command_base + index*0x54`, while the VM token-stream command uses a separate 8-byte `{kind,payload}` stream. Source names, VM tokens and numeric host commands are three different layers.
* Ordinary host command epilogue at `004144C2` resets the VM node's argument cursor to `node+0x1000` and advances the program counter by 8 bytes. Fatal/error paths and functions with other control effects require separate treatment.

`v89_host_abi_matrix.tsv` contains **all 96 opcode names**, jump targets, source-level direct callee hints, decompiled operand slot offsets, Boolean result writes, behavioral categories and selected verified side effects. Those categories are audit indexes, not a proof of every transitive side effect. Blocks joined by a shared `goto` may have more operands than are locally visible in the C case text.

## 2. Corrected CB voice subsystem

`00423620 queue_cb_voice_message` takes `(message_name, optional_source_object, type)`. A queued record is `0x24` bytes and has fields:

| Relative offset | Meaning | Evidence |
|---|---|---|
| `+0x00..0x0F` | Message identifier/text, truncated at 16 bytes | `strncpy` with count `0x10` |
| `+0x10` | Source object pointer, possibly null | Assigned from argument 2 and checked for world-object flag `0x200` |
| `+0x14` | Associated audio object handle | Returned by `00421B40`, released via `00421E70` |
| `+0x18` | Speech handling type/priority variant | Branches on values 1,2,4,5,6; assigned argument 3 |
| `+0x1C` | Request timestamp in Windows `GetTickCount` units | `GetTickCount` and 10,000 ms comparison for type 4 |
| `+0x20` | Next queued record | Linked-list insertion, removal and traversal |

The global list head is `0052457C` (new `g_cb_voice_message_queue_head`). At `00524580`, the enqueue-block flag (`g_cb_voice_enqueue_blocked`) is set by the `STOPCBXX` special marker and also by the existing setter `00423600` when its argument is zero. `00423620` returns immediately if this block flag is already set. This flag **is not an FSM instruction budget, mission timer, or VM scheduler gate**.

Priority/type observations from the native decompilation:

* Existing list and a new request of type **1**: clear the list before making a new request. Another queue-clearing condition occurs when a type less than 5 encounters a queued head type greater than 4.
* Type **2** can replace the head while preserving its successor.
* When a message is already queued, type **5** returns without queuing a new message; type **6** is rejected when the current head's type is below 5.
* Type **4** requests older than **10,000 milliseconds** are discarded when reaching playback.
* Each playable message attaches an audio completion callback. The callback frees the completed record, advances to the next message, skips invalidated source objects, and starts the next valid audio clip. This is the `004238E0` routine.

`0040BF50` (`isCBEmpty`) is a simple `queue_head==NULL` predicate. `00423A10` (`killCB` target) removes queued records and their audio handles; the host invokes it with argument zero. `0040C020` (`stopCB` target) calls `00423620("STOPCBXX",0,3)` and thereby raises the enqueue-block flag. **`stopCB` does not itself traverse, free, or unlink the existing queue**, and it does not mark a mission VM node complete. Do not confuse it with opcode 0x0C of `00414670`, which genuinely returns VM-completion status.

**Important relationship to ownership:** The queue records store source-object pointers at `+0x10`. No independent reference acquisition appears in `00423620` or the completion routine, and those routines can examine object flags or identity. This is another borrowed-object identity in the wider engine. Its practical lifetime safety is not established by this pass. The audio queue's cleanup ordering during world teardown should be audited separately, particularly before treating it as a fully resolved owner.

## 3. State-changing mission commands: verified first-layer boundaries

| Opcode family | Runtime action | Immediate vs deferred |
|---|---|---|
| `0x02 attack`, `0x03 sit`, `0x04 goto`, `0x05 guard`, `0x30 follow`, `0x40 evade`, `0x59 hide`, `0x5C race` | Call `00412830 update_vehicle_ai_target_and_attack_state`, potentially release/acquire counted target references, evaluate AI predicates and perform selected callbacks | **Synchronous** call during the host instruction; downstream physical movement is frame-driven |
| `0x31 teleport`, `0x57 teleportOffset` | Enter common teleport helper `00414BC0` after resolving actor and scripted location; write world-object transform and vehicle runtime velocity/inertia state; mark changed control context | **Immediate** world/vehicle state mutation |
| `0x32 destroy` | Resolve target, then invoke `0040B9E0 fsm_destroy_target_object`; vehicle/actor path uses forced damage rather than a direct generic unregister call | **Immediate** command dispatch, potentially delayed lifecycle consequences |
| `0x45 setSkill`, `0x4D setAgg`, `0x41 toggleAvoid`, `0x53 setAvoid`, `0x54 setMaxAttackers` | Mutate AI tactics parameters or behavior-state fields (`AI+A818`, `AI+A81C…A828`, `AI+9D14`, `AI+A948`) | **Immediate** AI state writes; actual AI movement/firing can be deferred |
| `0x0B whoRammed`, `0x0C whoShot`, `0x2E whoAttacked` | May append counted mission actor binding if pointer not already registered | **Immediate** actor-table mutation |
| `0x0F successAll`, `0x11 failAll`, `0x12 failAllObj` | Write `005244E0` timeout and `005244E4` next flow state; separate mission scheduler checks deadline | **Deferred** mission game-flow transition |
| `0x0E success`, `0x10 fail`, `0x4B reveal` | Modify mission-objective registry/visibility and may trigger notification audio | **Immediate** registry effect, with possible downstream presentation |
| `cb` family, `killCB`, `stopCB` | Modify separate CB voice queue | **Immediate** enqueue/cancel/latch; **asynchronous** playback and callback advancement |

These are function-level findings grounded in `v89_host_native_decompilation.txt`. They do **not** constitute a full dataflow proof for all host operands or all transitive effects for the 96 commands. The raw jump table and machine-code callee inventory are supplied so the remaining command groups can be analyzed incrementally.

## 4. Mission time and frame sequencing

Mission-flow timeout at `005244E0` is based on gameplay runtime seconds (`0049C7E0`), checked by the node scheduler `004149F0`. CB message timestamps instead use the Windows `GetTickCount` tick counter; a type-4 speech request has an observed 10-second discard condition. The two clock domains are distinct and should not be conflated in any later validation tests.

The FSM node scheduler at `004149F0` walks nodes in list order; `00414670` executes the token VM; opcode `0x0A` of that **token VM** yields, while opcode `0x0C` returns completion. The host dispatcher can synchronously enter AI predicates and callbacks; it may therefore mutate AI state before returning to the current VM node. This establishes a scheduling relationship but does not prove a particular shipped mission exercises every ordering combination.

For later functional tests, instrumented assertions should distinguish `vm_node_count`, `cb_voice_queue_head`, pending audio completion callbacks, `GetTickCount` timeouts, gameplay-time mission timeout, and epoch-marked damage events. In particular, `stopCB` followed by `isCBEmpty` does not automatically imply the queue becomes empty, while `killCB` targets the queue directly.

## 5. Proposed symbol consolidation and verified working artifact

Ten changes (one previously absent function definition, seven renamed functions, two renamed globals) were applied to **an isolated project imported from v81 GZF**, not the canonical baseline. All original names and their addresses appear in `v89_cb_name_change_audit.tsv`. The packed export `i76_mission_v89_cb_voice_symbols.gzf` was opened by a new headless Ghidra project, and **all 17 reimport checks passed**, covering the new names, earlier v81 symbols and retail MD5.

This correction intentionally changes none of the VM execution functions, machine code, loaded resources, data types or existing user comments. Full source variable names, original header boundaries, and real gameplay traces remain unknown.

## 6. Pending work and confidence

* **High confidence:** 96-entry jump table and destinations; command ABI layers; `CB` voice subsystem separation; queue field offsets; end-of-message callback; tagged speech command paths; corrected function and global identities.
* **High confidence for shown paths:** immediate AI/actor/world/mission state mutations and deferred game-flow timeout. Additional transitive callee analysis remains necessary for full ABI documentation.
* **Medium:** precise intended priority semantics for all CB type values and whether actor/source pointers are always protected by external ownership.
* **Unresolved:** dynamic reachability, game session/audio teardown ordering, replay-specific command ordering, imported DLL callbacks, and whether unimplemented stubs have alternative code paths in other game builds.

This changes the recommended next research step: audit **CB voice queue teardown and source-object lifetime** as a short ownership follow-up, then return to the host command ABI with the speech subsystem cleanly separated from the true FSM node scheduler. Continue recording speculative translation-unit evidence separately.
