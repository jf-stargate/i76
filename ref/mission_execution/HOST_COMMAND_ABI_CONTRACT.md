# I76 retail FSM host-command ABI — v0.2.0

**Evidence class:** executable-verified at dispatch and first-level callees; stock serialized-command mapping corpus-verified.  
**Retail binary:** `i76.exe` MD5 `a640ea0097dbb62e0c77b7f2847c7161`.  
**Authority:** annotated v97 Ghidra 12.1.4 project, read-only native decompilation rechecked in v98.  
**Purpose:** finish the **host-command invocation ABI**; this is a research contract, **not** a reconstructed interpreter or a declaration that every transitive engine subsystem is understood.

## 1. Invocation and dispatch ABI

`00414670` interprets eight-byte tokens `{uint32 tokenKind, uint32 payload}`. For token kind `0x0D`, the payload is an index into **serialized 0x54-byte command records**, *not* the internal numeric host opcode. The host dispatcher `00412CE0` reads the command opcode at `commandBase + index * 0x54 + 0x50` and indexes the 96-entry jump table at `004144E4`. At most 95 numeric IDs have normal explicit handler cases; `0x16/playScene` resolves to the error/abort destination. The stock compiled command table contains 95 names and omits `playScene`.

The executing VM node contains a **40-word host argument area at `node+0x1000`**, separate from its 4 KiB operand/call-frame workspace. For opcode-specific argument position `aN`, the host reads the 32-bit word at `node+0x1000+4*N`, most often **as a pointer to a 32-bit value** in the VM word workspace. For a world object, that value is an **actor-table index**, which is used to locate `actorBase + index * 0x60 + 0x58`. Named-position indices address `positionBase + index * 0x58`; media indices address `mediaBase + index * 0x54`. Ordinary scalar arguments may be integers, coordinates, angles or selector values; these distinctions are semantic roles, **not recovered original `fsmcomp.exe` type tokens**.

After a normally returning host case, the dispatcher resets `node+0x10B4` to the host argument-area base and advances `node+0x10A8` by eight bytes. Predicate handlers write the result at **`node+0x10A0`**; non-predicate handlers generally **leave this field unchanged**, so it is inaccurate to model every command as returning `false` or resetting the predicate. Commands that write a script variable (for example `set`, `rand`, `whoRammed`) write through an argument pointer instead of using `+0x10A0`.

A handler that references an actor calls `0045F0F0` to validate its retained object pointer and writes the result back to `actor+0x58`. For a live object this preserves the pointer; for a logically removed object it can consume a counted hold, return null and leave a null actor binding. This is **not a general null guard**: several helpers subsequently dereference the returned pointer without a check. Thus opcode availability does not imply runtime safety for malformed indices or missing actors.

The `effective_slot_count` in the machine-readable matrix is the number of **argument positions actually consumed by the audited dispatcher path**, including shared blocks; it is **not proof of the original source-level compiler arity**. A slot's conceptual type may be underconstrained where it is simply forwarded into another subsystem.

## 2. Dispatch-level coverage and evidence

The 96 handler addresses from the read-only v98 Ghidra project match the v89 executable-verified table exactly. Both `0x07/set` and `0x2F/setId` share one handler. The `v98_native_selected.txt` evidence re-decompiles 32 functions successfully and the secondary audit decompiles four additional helpers, with no decompilation failures in either pass. Table rows contain the symbolic argument roles, result destination, principal side effect and confidence boundary. `closed` refers to **opcode-to-first-level semantic contract**, not every transitive physics, UI, audio or collision state transition.

The following are worth treating as ABI constraints, rather than implementation details that can be guessed from labels:

- **`hpLesser` `0x21`:** `actor, ignored_slot, integrity_threshold`. It passes a middle word to `0040B7D0`, but that helper tests only calculated integrity percentage against the third argument. The middle value is unused by that callee in this build.
- **`startTimer` `0x0D`:** despite its name, it writes the current gameplay time converted to an integer into a supplied script variable. It does not independently schedule the mission outcome deadline.
- **`camPosDir` `0x39`:** the case initializes argument pointers for slots `a2–a4`, then branches to common code that also reads `a0` and `a1`. Its **effective five-slot** signature cannot be recovered by simply counting accesses within the labeled case.
- **`pushCam` `0x34` and `popCam` `0x35`:** the former invokes `0049D420` (which calls `pop_runtime_camera_state_stack`) after optional camera handling; the latter invokes `0049D470` (which calls `push_runtime_camera_state_stack`). These are the *observed calls*, regardless of counterintuitive source command names.
- **`stopCB` `0x5F`:** consumes **no host argument**; its implementation emits the fixed `STOPCBXX` voice message marker. Earlier automatic operand extraction reported a spurious slot.
- **`nearestEnemy` `0x17` versus `nearestBlg` `0x18`:** the former actually scans team-bucket vehicles and has a no-result null-write branch; the latter scans qualifying transform-composed effect targets. Both may allocate counted dynamic actor bindings.
- **`behave/do/test/isLit` (`0x01/0x06/0x1E/0x25`):** these are genuine, defined dispatch paths to unimplemented stubs. `test/isLit` return false. The stub's diagnostic call is a single-`RET` `report_error` in this retail PE; some stubs reset one-time notification flags.
- **`playScene` `0x16`:** *not equivalent* to those stubs. Its opcode is lexically recognized but dispatches to the default `report_error()` and `abort()` path.
- **`setLights` `0x5B`:** mismatch between script input and vehicle `+0x454` bit 6 triggers `004674C0`, which toggles the bit and updates light/attachment state; not a mere read-only comparison.
- **`setArtillery` `0x5D` / `setArtilleryRate` `0x5E`:** writes through the world object's class-specific `+0x508` pointer into separate fields at `+0x4C` and `+0x50` respectively.
- **`rand` `0x0A`:** uses CRT `rand() % modulus` without an opcode-local zero-modulus check. RNG state is shared with AI weighted selection.
- **`timeGreater/timeLesser` `0x26/0x27`:** compare the sum of two script integers against a gameplay time converted by `ftol`, with an embedded float tolerance. Boundary equality is strict, not inclusive.
- **`isAirborne` `0x56`:** helper returns the *bit mask* `runtime+0x454 & 4`, not necessarily canonical integer one; the VM uses nonzero truthiness.
- **`isArrived/isAtFollow/isShot/isRammed/isAttacked`** consume internal marker/epoch flags on success; `controlDone` does not consume its queue-drained flag.
- **`CB` voice commands** initiate asynchronous CB-message queue effects; they neither enqueue new VM execution nodes nor immediately block the interpreter until a clip completes.

## 3. Exhaustive 96-opcode table

The canonical table is **`ABI_DISPATCH_CONTRACT_96.tsv`**, which preserves program addresses and includes one row for every `0x00..0x5F` opcode. It is designed for filtering, machine comparisons and future differential tests. For convenience, an abbreviated readable inventory follows; full semantics remain in the TSV.

| ID | Command | Effective argument roles | Dispatcher-observed effect |
|---|---|---|---|
| `0x00` | `null` | `none` | No-op |
| `0x01` | `behave` | `a0:actor` | Resolve actor, then invoke unimplemented behave stub; no behavior executed |
| `0x02` | `attack` | `a0:actor a1:target_actor` | Resolve both actors; enter AI evaluator with mode 0 and target retarget/refcount handling |
| `0x03` | `sit` | `a0:actor` | Enter AI evaluator with null target, mode 0x1F |
| `0x04` | `goto` | `a0:actor a1:position_index a2:speed_integer` | Store named-position address and speed scalar in AI state; enter AI evaluator mode 0x16 |
| `0x05` | `guard` | `a0:actor a1:target_actor` | Enter AI evaluator with target and mode 0x20 |
| `0x06` | `do` | `a0:actor` | Resolve actor; invoke unimplemented do stub |
| `0x07` | `set` | `a0:out_word a1:value` | Copy one 32-bit word to destination; same handler as setId |
| `0x08` | `inc` | `a0:inout_word` | Increment signed 32-bit storage word by one |
| `0x09` | `dec` | `a0:inout_word` | Decrement signed 32-bit storage word by one |
| `0x0A` | `rand` | `a0:out_word a1:modulus` | Write rand() modulo supplied modulus; no zero-divisor guard in case |
| `0x0B` | `whoRammed` | `a0:actor a1:out_actor_index` | Look up ram-source cache; reuse actor slot or append NoLabel record with counted object reference |
| `0x0C` | `whoShot` | `a0:actor a1:out_actor_index` | Look up shot-source cache; reuse actor slot or append NoLabel record with counted object reference |
| `0x0D` | `startTimer` | `a0:out_word` | Write integer-converted current gameplay elapsed time to supplied destination |
| `0x0E` | `success` | `a0:objective_index` | Set succeeded objective flag (validated by objective helper) |
| `0x0F` | `successAll` | `a0:delay_seconds` | Set result=1 and deadline=current gameplay time + delay; call objective context helper with -1 |
| `0x10` | `fail` | `a0:objective_index` | Set failed objective flag (validated by objective helper) |
| `0x11` | `failAll` | `a0:delay_seconds` | Set result=0 and deadline=current gameplay time + delay; call objective context helper with -1 |
| `0x12` | `failAllObj` | `a0:delay_seconds a1:objective_index` | Set failure result/deadline; pass objective index to objective context helper |
| `0x13` | `cb` | `a0:media_index` | If media status at +0x50 nonzero, submit CB voice message type 3 with null source |
| `0x14` | `cbPrior` | `a0:media_index a1:cb_type` | Submit CB message by media record and script-provided type |
| `0x15` | `cbFromPrior` | `a0:media_index a1:source_actor a2:cb_type` | Submit CB message by media record, actor source, and script type |
| `0x16` | `playScene` | `none` | Recognized host name, no legal dispatch case; takes report_error then abort |
| `0x17` | `nearestEnemy` | `a0:actor a1:out_actor_index` | Nearest eligible opposing team vehicle selection; may append counted NoLabel actor record |
| `0x18` | `nearestBlg` | `a0:actor a1:out_actor_index` | Nearest qualifying transform-composed effect target; may append counted NoLabel actor record |
| `0x19` | `true` | `none` | Write VM predicate result 1 |
| `0x1A` | `false` | `none` | Write VM predicate result 0 |
| `0x1B` | `isEqual` | `a0:lhs a1:rhs` | Predicate result = (lhs == rhs) for 32-bit integer words |
| `0x1C` | `isGreater` | `a0:lhs a1:rhs` | Predicate result = (lhs > rhs) for signed 32-bit integer words |
| `0x1D` | `isLesser` | `a0:lhs a1:rhs` | Predicate result = (lhs < rhs) for signed 32-bit integer words |
| `0x1E` | `test` | `a0:actor` | Resolve actor; unimplemented test helper returns zero; write VM predicate result |
| `0x1F` | `isWithin` | `a0:actor a1:target_actor a2:radius` | Strict 3D squared-distance comparison using aim positions and integer radius |
| `0x20` | `isShot` | `a0:actor` | Consume shot epoch marker AI+A6D4 if current or previous epoch |
| `0x21` | `hpLesser` | `a0:actor a1:unused_slot_word a2:integrity_percent` | Compare computed object integrity percent against third argument; middle argument ignored by callee |
| `0x22` | `ammoLesser` | `a0:actor a1:hardpoint_id a2:ammo_threshold` | Search weapon state by hardpoint; result true when ammo count below threshold |
| `0x23` | `isRammed` | `a0:actor` | Consume ram epoch marker AI+A6D8 if current or previous epoch |
| `0x24` | `isDead` | `a0:actor` | Check world-object status bit 0x200 |
| `0x25` | `isLit` | `a0:actor` | Resolve actor; unimplemented isLit helper returns zero; write VM predicate result |
| `0x26` | `timeGreater` | `a0:time_base a1:time_offset` | Result true when base + offset < truncated_gameplay_time - tolerance |
| `0x27` | `timeLesser` | `a0:time_base a1:time_offset` | Result true when truncated_gameplay_time - tolerance < base + offset |
| `0x28` | `isArrived` | `a0:actor` | Consume AI+0x9C path-arrival event |
| `0x29` | `isEqualId` | `a0:actor a1:target_actor` | Compare validated world-object pointers for equality |
| `0x2A` | `isWithinNav` | `a0:position_index a1:actor a2:radius` | Test strict X/Z squared-distance against named-position record and integer radius |
| `0x2B` | `isWithinSqNav` | `a0:position_index a1:actor a2:half_extent` | Test strict axis-aligned X/Z box inclusion against named position |
| `0x2C` | `isWithinEnemy` | `a0:actor a1:radius` | Scan opponent team objects for an active enemy within squared X/Z radius |
| `0x2D` | `isAttacked` | `a0:actor` | Consume attacked epoch AI+A6DC, clearing all three event epoch markers on success |
| `0x2E` | `whoAttacked` | `a0:actor a1:out_actor_index` | Look up last-attacker cache; reuse actor slot or append counted NoLabel record |
| `0x2F` | `setId` | `a0:out_word a1:value` | Copy one 32-bit word; shared handler with set |
| `0x30` | `follow` | `a0:actor a1:target_actor a2:aux_actor a3:follow_mode a4:scalar_a a5:scalar_b` | Store auxiliary target, mode, two scalars in AI state; enter AI evaluator mode 0x1E with target actor |
| `0x31` | `teleport` | `a0:actor a1:position_index a2:teleport_param_a a3:teleport_param_b` | Call teleport helper with named position and two scalar pointers; optional parameters null |
| `0x32` | `destroy` | `a0:actor` | Enter class-dependent force-damage/destruction helper; not direct unregistration |
| `0x33` | `playMovie` | `a0:media_index` | If media status nonzero, set pending SMK playback resource pointer |
| `0x34` | `pushCam` | `none` | Conditional active-camera reset then camera stack *pop* helper; name pushCam not a faithful stack description |
| `0x35` | `popCam` | `none` | Invoke camera stack *push* helper; name popCam not a faithful stack description |
| `0x36` | `camObjObj` | `a0:actor a1:scalar_a a2:scalar_b a3:scalar_c a4:target_actor` | Activate camera transform anchored to actor and target actor, three supplied scalars |
| `0x37` | `camObjDir` | `a0:actor a1:scalar_a a2:scalar_b a3:scalar_c a4:angle_a a5:angle_b a6:angle_c` | Activate object-based camera directional transform, six supplied scalars |
| `0x38` | `camPosObj` | `a0:position_index a1:scalar_a a2:target_actor` | Start camera movement from named-position record relative to target object |
| `0x39` | `camPosDir` | `a0:position_index a1:scalar_a a2:angle_a a3:angle_b a4:angle_c` | Use shared camera directional handler; slot 0 and 1 consumed after branch (five effective slots) |
| `0x3A` | `camTransObj` | `a0:position_index a1:scalar_a a2:scalar_b a3:target_actor` | Start camera transition from named position toward target object |
| `0x3B` | `camF12` | `a0:actor a1:target_actor a2:scalar_a a3:scalar_b` | Start camera F12-style interpolated transition toward target |
| `0x3C` | `camTransDir` | `a0:position_index a1:scalar_a a2:scalar_b a3:angle_a a4:angle_b a5:angle_c` | Use shared camera directional handler with six effective slots |
| `0x3D` | `camIsArrived` | `none` | Read and clear camera-arrival flag through camera helper |
| `0x3E` | `isKeypress` | `none` | Set input-consumed latch; read pending action; clear keyboard/joystick latch on recognized keypress; write VM predicate result |
| `0x3F` | `triggerGate` | `a0:actor` | Find class-7 object in subtree and reset its runtime action/gate field |
| `0x40` | `evade` | `a0:actor a1:position_index a2:speed_integer a3:target_actor` | Set scripted position and speed; enter AI evaluator with target, mode 0x18 |
| `0x41` | `toggleAvoid` | `a0:actor` | Toggle AI+0x9D14 state flag |
| `0x42` | `allBlgDead` | `none` | True if no qualifying living composed effect targets are found |
| `0x43` | `allEnemyDead` | `a0:actor` | Test whether all other-team registered vehicles have destruction/status bit 0x20 |
| `0x44` | `setHeliHeight` | `a0:actor a1:height` | Write helicopter height through AI vehicle helper |
| `0x45` | `setSkill` | `a0:actor a1:skill_selector_a a2:skill_selector_b` | Write four AI tactic weights from two selector tables |
| `0x46` | `isAtFollow` | `a0:actor` | Consume AI+A988 follow-proximity event |
| `0x47` | `control` | `a0:actor a1:control_history_sel_a a2:control_history_sel_b` | Enqueue history-derived buffered control sample, clear controlDone flag |
| `0x48` | `controlAll` | `a0:actor a1:control_a a2:control_b a3:control_c a4:control_d a5:control_e a6:control_f` | Enqueue six-field buffered control sample |
| `0x49` | `driveControl` | `a0:actor` | Dequeue and apply one buffered control sample in host-command execution |
| `0x4A` | `controlDone` | `a0:actor` | Read AI+A6D0 control queue-drained flag, nonconsuming |
| `0x4B` | `reveal` | `a0:objective_index` | Clear objective hidden bit 0x01 and possibly issue note sound |
| `0x4C` | `isCBEmpty` | `none` | True iff CB voice queue head is null; not FSM node list |
| `0x4D` | `setAgg` | `a0:actor a1:aggression_selector` | Write zero-based tactics index to AI+A818 and parse tactics tag |
| `0x4E` | `setUserRadar` | `a0:radar_context_id` | Update active player radar/control context when value changes |
| `0x4F` | `cbFrom` | `a0:media_index a1:source_actor` | Submit CB message of type 3 using borrowed actor source |
| `0x50` | `killCB` | `none` | Clear voice queue and associated resources |
| `0x51` | `salvage` | `a0:media_index` | Classify supplied media/resource name and conditionally append linked salvage record (gated by mode, mission family and file-type) |
| `0x52` | `setSiren` | `a0:actor a1:enabled_value` | When enabled queue positional engine event sound; otherwise find and release matching actor-bound sound |
| `0x53` | `setAvoid` | `a0:actor a1:avoid_value` | Assign AI+0x9D14 directly |
| `0x54` | `setMaxAttackers` | `a0:actor a1:max_attackers_value` | Assign AI+0xA948 directly |
| `0x55` | `canSee` | `a0:actor a1:target_actor` | Perform projectile line-of-sight/path test; write predicate result |
| `0x56` | `isAirborne` | `a0:actor` | Read vehicle runtime +0x454 bit 2 (mask 4) as predicate result |
| `0x57` | `teleportOffset` | `a0:actor a1:position_index a2:teleport_param_a a3:teleport_param_b a4:teleport_param_c a5:teleport_param_d` | Call teleport helper with named position and four scalar pointers |
| `0x58` | `isGroovesFault` | `a0:actor` | Invoke AI/vehicle grooves-fault query; write predicate result |
| `0x59` | `hide` | `a0:actor` | Enter AI evaluator with null target, mode 0x21 |
| `0x5A` | `startCar` | `a0:actor` | If vehicle runtime flags +454 mask 9 are clear, start engine sound; write +450 and set +454 bits 0x80000008 |
| `0x5B` | `setLights` | `a0:actor a1:light_value` | If supplied bit differs from runtime+0x454 bit 6, toggle that bit and recompute vehicle light/attachment flags via 004674C0 |
| `0x5C` | `race` | `a0:actor a1:position_index a2:speed_integer a3:target_actor` | Enter AI evaluator with target and race mode 0x1A |
| `0x5D` | `setArtillery` | `a0:actor a1:artillery_value` | Assign input word to object->class_runtime+0x508 pointer +0x4C |
| `0x5E` | `setArtilleryRate` | `a0:actor a1:artillery_rate` | Assign input word to object->class_runtime+0x508 pointer +0x50 |
| `0x5F` | `stopCB` | `none` | Submit STOPCBXX CB marker and set stop latch; no host operand slots |

## 4. Domain boundaries, ownership and error behavior

**Actor lookups:** prior to most actor-dependent actions, the dispatcher performs the `actor+0x58` conditional-release/liveness operation. Dynamic actor queries can append counted references and mutate the mission actor count. Most opcode bodies do **not** range-check actor/position/media indices, nor establish a per-opcode null safety guarantee. The exact behavior of a missing actor may range from returning false to dereferencing null; this contract documents the audited code path without asserting a safe fallback.

**Immediate versus deferred effects:** AI attack, follow, guard, evade and race dispatch may invoke the synchronous behavior evaluator before the VM advances; CB voice submissions are deferred through their own audio queue; objective result commands schedule a gameplay-time deadline, and the FSM scheduler evaluates it even when the VM-node list has become empty. Queue-control producers `control/controlAll` do not by themselves consume samples; `driveControl` explicitly dequeues and applies one.

**Results versus side effects:** a host Boolean at `node+0x10A0` is generally written only by predicates. Query commands such as `whoShot` instead write an actor index into script storage and may create a counted binding. Several conditions consume one-shot flags; a later predicate in the same VM pass may observe that the event has already been cleared. Ordinary script scalar writes (`set/inc/dec`) do not imply generic VM result updates.

**Errors:** in this retail executable `report_error` at `0042D5D0` consists of one `RET`; do not treat it as rejecting malformed arguments or forcing a failure. `abort`, `exit(0)`, invalid memory accesses, and a possible hardware divide error are separate paths with different consequences. The 96-entry ABI table does not grant bounds safety.

## 5. Contract closure and residual questions

**ABI boundary: complete as a static dispatcher inventory** for 96 IDs, with effective argument positions, output channel, first-level callee and direct side effects. **Transitive effect coverage is not universal.** Two commands still point into complex subsystems for which their complete downstream side effects are intentionally not closed:

1. `salvage` `0x51` classifies and conditionally appends to the salvage/resource list in `004B16E0`; the details of its mission-family gating and every possible emitted record need their own subsystem specification.
2. `canSee` `0x55` invokes a weapon/projectile swept-path and effect-target collision test in `00417BF0`; the full collision solver and every obstacle policy lie beyond the command ABI.

For both, the invoked helper, argument passing, result channel and primary effect are established. This does not prevent completing the **host ABI**; it identifies where a future camera, salvage, or physics specification must elaborate the internals. Other indirect paths and null/malformed-bytecode reachability have not been proven absent. No live-game or malicious-input tests were run.

**Evidence/reproduction:** `scripts/i76_v98_host_abi_readonly.java`, `scripts/i76_v98_host_deep_helpers_readonly.java`, `evidence/v98_native_selected.txt`, `evidence/v98_secondary_callees_native.txt`, `evidence/v98_jump_targets.tsv`, and v89's preserved host-case/callee decompilation. Address-matched validation is in `ABI_AUDIT_VALIDATION.json`. The baseline program was opened read-only and no rename or GZF export was necessary.
