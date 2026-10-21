# I76 retail engine v90 — CB speech ownership, teardown ordering, and host-command semantics

**Research date:** October 20, 2026 (session). **Program:** retail `i76.exe`, PE MD5 `a640ea0097dbb62e0c77b7f2847c7161`. **Tool:** Ghidra 12.1.4 headless using the verified annotated v89 `.gzf` baseline; separate writable Ghidra copy for v90 symbol corrections. **Scope:** source-backed reverse engineering only, no replacement engine or live game tests.

## Summary

1. **CB source-object pointers are borrowed:** `00423620 queue_cb_voice_message` allocates a **0x24-byte** request node, stores the source at `node+0x10`, and does not call the world-object tree `incref` routines; `004238E0` completion callback and `00423A10` clear do not release such references. They do release the associated **audio object** at `node+0x14`, then free the request node. This separates the speech queue's two ownership domains.
2. **Orderly mission teardown protects the borrowed CB references:** in `00402B30`, `00421730 release_all_audio_objects_and_buffers` (including `00423A10(0)`) runs before `004571A0` dismantles the active-world registry and fires its world-object callbacks, and before FSM shutdown. Five **direct** caller sites of `00423A10` all explicitly pass zero, selecting the full queue release branch. This is strong evidence for orderly mission exit—not a proof against every mid-frame exceptional removal.
3. **CB playback's validity tests are not refcount or liveness tests:** `00458BF0 world_object_has_optional_runtime_flag` returns whether non-null `object+0x10` has bit `0x10`. The completion callback also checks queued source bit `0x200` when moving to the next request; it does **not** call `0045F0F0` to validate object logical removal or acquire a counted reference. The latter check dereferences `source+0x10` if the pointer is non-null. Retained identity safety therefore depends on game object lifetime and mode-specific cleanup.
4. **Vehicle destruction reconciles related CB records:** `00463A80`, `00464890`, and `00466180` invoke `00423A90 play_cmike_voice_clip` as part of damage transitions. That routine scans by source-pointer equality and replaces an active head request with a `cmike.wav` request, or unlinks queued matching non-head records, according to the visible branches. This often reduces stale queued references before setting destruction flags. It is not generic world-object unregistration cleanup.
5. **A second misleading inherited host helper name is resolved:** `0040B320`, used by mission host opcode `0x28 isArrived`, consumes **AI+0x9C**, a path arrival flag—not a damage-event epoch. `00415020` sets this word when a route reaches its final segment/waypoint; `00420A20` and `00420AA0` reset it to zero when beginning path following. It returns true exactly when it sees `1` and clears it to `0`.
6. **Opcode `0x3F triggerGate` operates on a class-7 descendant:** `0040BF20` calls `00458F40(object,7)` to recursively find a class-7 object in the supplied world-object subtree, then calls `0046D740`, which sets `class7->runtime(+0x70)->field+0x90 = 0`. Its existing helper name said only “start action slot 7”; the verified operation is more precise. The generic class subtree search at `00458F40` was safely renamed.

## 1. CB queue ownership and lifetime matrix

| Entity or reference | Address/field | Owner and lifetime | Confidence |
|---|---|---|---|
| CB message record | `00423620` allocates `0x24`, `node+0x20` next | CB queue owns node; `004238E0`/`00423A10` release with global heap `xfree` | High |
| Optional voice source object | `node+0x10` | Borrowed; no source-specific counted acquire/release in queue functions | High within the audited paths |
| Attached audio object handle | `node+0x14` | CB record tracks a separately allocated/managed audio record, released through `00421E70` | High |
| Voice queue head | `0052457C` | Linked-list root; nil means `isCBEmpty` true | High |
| Voice enqueue stop latch | `00524580` | `STOPCBXX` sets to 1; `00423600(1)` resets at game-loop setup | High |
| Audio completion callback | `004238E0` | Deletes completed CB head; starts next eligible audio request | High |
| Active-world registry object | `004571A0`, `00457420` | Distinct counted owner; world-object removal callbacks before release | High |

`00421B40 create_or_queue_positional_audio_object` is called with source-object positional argument **zero** by the CB queue path. Its first argument is the message record's string at offset zero, not the source object at `node+0x10`; it therefore does not establish a world-object reference on behalf of the message source in this call.

### Queue clearing and other callers

The five direct call sites targeting `00423A10` and their meanings:

| Address | Calling function | Visible condition/command |
|---|---|---|
| `00413587` | FSM dispatcher `0x50 killCB` | Explicit `push 0`; clear all CB entries |
| `00421319` | `004211B0` audio reconfiguration | Clear queue when audio priority/voice object constraints change |
| `00421742` | `00421730` audio shutdown | Clear queue before releasing audio object lists |
| `00421AB3` | `00421A60` priority trimming | Clear queue on audio availability reduction |
| `00495252` | `00495170` player/audio options reload | Clear queue if voice audio category is disabled |

The current `00423A10(int)` implementation has a nonzero-argument branch that starts releasing from the second node then sets head to null. Since no **direct** callers pass a nonzero value, do not infer its intended semantics or memory safety outside the observed zero-argument uses. Indirect calls have not been excluded.

### Normal teardown timeline

In the documented end-of-game branch of `00402B30`:

1. `stop_and_demote_all_active_audio_objects`
2. `00421730 release_all_audio_objects_and_buffers` (calls `00423A10(0)`)
3. `release_pending_audio_objects_and_buffers`
4. Various player/map/effect subsystem releases
5. `004571A0` active-world registry teardown, including callbacks and object reference release
6. `shutdown_fsm_runtime_heap_and_tables`

This order is executable-backed. It does **not** prove that every abort/error path follows the same route, nor that audio callbacks and object lifetimes are synchronized under all exceptional events.

### Vehicle-destruction reconciliation

The class-1 paths `00463A80`, `00464890`, and `00466180` all call `00423A90` around damage transitions. `00423A90` compares queued `source+0x10` with the affected vehicle, then either inserts an urgent `cmike.wav` replacement if it matches the head or removes matching waiting nodes. This is source-specific queue repair, not an object-refcount operation. It helps protect normal vehicle destruction, although new `cmike.wav` messages may still retain the same source identity and ordinary destruction need not free the vehicle.

## 2. Host-command results added in v90

### `isArrived` (`0x28`) is a consuming AI path completion event

- Source opcode `0x28` dispatches to `0040B320` via `00412CE0` at call site `00413C95`.
- `0040B320`: reads `AI+0x9C`, returns 1 only when the stored value is 1, and clears it to zero as a side effect.
- `00415020 update_ai_path_waypoint_progress_state`: sets the same field on final path segment/waypoint progress, via `param_1[0x27] = 1` (`0x27*4=0x9C`).
- `00420A20` and `00420AA0`: initialize a new forward path-follow operation, resetting this field to 0.
- The prior symbol `fsm_query_and_clear_vehicle_damage_event_flag` was therefore misleading. **Verified new symbol:** `fsm_consume_ai_path_arrival_flag`.

An important later functional-test implication: two `isArrived` queries for the same actor without another arrival write should return true then false; the test is **not** idempotent, even though it appears to be a Boolean query.

### `triggerGate` (`0x3F`) is class-specific tree dispatch

- `0040BF20` searches for world-object class **7** in the supplied object's child tree.
- `00458F40` is a generic recursive class lookup: compare `node+0x6C` with requested class, otherwise traverse first child `+0x64` and next sibling `+0x60` until a match.
- `0046D740` resets `runtime+0x90` to zero if the class-7 object has a runtime pointer at `object+0x70`.
- This provides a more specific initial side-effect contract than “start action slot,” although the subsequent interpretation of the class-7 runtime field is not yet closed. **Verified new symbol:** `find_world_object_class_in_subtree` at `00458F40`.

### `setUserRadar` (`0x4E`): more than scalar assignment

`0040BF90` compares the script-provided value with `DAT_004C2AB0`. When different and the active player/camera object exists, it invokes `00460EA0` against the player and then stores the new value. `00460EA0` manipulates a nested radar/classifier state object including flags and resource-state reset. The full intended display behavior remains a separate follow-up; v90 does not rename this helper.

## 3. Evidence and confidence

**High confidence from the imported retail binary and Ghidra machine code:** queue record sizes and fields; all five direct `00423A10` callers pushing zero; regular top-level audio-before-world teardown; class-1 damage paths invoking `play_cmike_voice_clip`; source bit tests; arrival field producer, clearer and consumer; class-7 recursive lookup and direct reset of class-specific runtime field.

**Bounded inference:** ordinary vehicle destruction and orderly mission shutdown together appear designed to avoid stale CB sources. The source is still borrowed, and no evidence establishes an independent lifetime pin held by a CB request. **No real-time crash, use-after-free, or lack thereof was demonstrated.** Other object classes, exceptionally unregistered active sources and foreign audio callbacks could behave differently.

**Explicit limits:** Ghidra native static decompilation only; the per-offset instruction census has potential unrelated matches and must not be treated as base-pointer proof without call-path evidence. Raw call-site inventories do not include arbitrary indirect calls. No gameplay/DirectSound execution, Ghidra type-system mutation, or reconstructed engine code.

## 4. Future behavioral-test specifications (not yet implemented)

1. Enqueue one CB message with a source actor; verify source world-object refcount unchanged, queue node allocated, and audio object independently released by `killCB`.
2. Enqueue messages for multiple actors; destroy a source vehicle while one request is playing and another queued. Verify the `cmike.wav` replacement/removal behavior and when bit `0x200` is checked.
3. Run ordinary game shutdown with nonempty CB queue. Assert callback queue drains and audio objects are released before active-world registry teardown.
4. Run `stopCB` with nonempty CB queue. Verify enqueue latch changes without forcibly completing the VM node or necessarily clearing existing audio records.
5. Start a path, reach a final waypoint, and issue `isArrived` twice in one VM or across consecutive turns. Verify true/false consumption and reset-on-new-path behavior.
6. Invoke `triggerGate` on a world-object subtree with zero, one and multiple class-7 descendants; confirm class lookup order and the field `runtime+0x90` reset.
7. Exceptional removal: explicitly unregister an object that remains the CB source without normal vehicle damage; instrument the callback and world-object removal to establish actual reachable lifetime constraints before asserting safety.

## 5. Symbol baseline and delivery

The v89 `.gzf` was imported into a distinct writable project. Two narrowly guarded semantic renames (plus explanatory comments) were applied, exported, then verified by importing the v90 GZF into a **third** fresh Ghidra project. **All 15 independent reimport checks passed**, including ten established function names, four globals and retail MD5. The canonical user Ghidra project and v89 input archive were not edited.

Ghidra export: `i76_mission_v90_verified_names.gzf`. Rename audit: `v90_verified_semantic_rename_audit.tsv`. Independent assertions: `v90_static_validation.json` and `v90_validate_evidence.py` (**23/23 passed**). Source-layout hypotheses are kept in `V90_SOURCE_LAYOUT_ADDITIONS.md`, separate from actual original object-file claims.

## Suggested next investigation

With the CB speech queue bounded, continue **control, movement, world manipulation, and objective** host ABI effects—especially fields shared by `triggerGate`, `isArrived`, navigation, and asynchronous camera/mission progression. Expand reachability tests only where the static evidence is ambiguous. Maintain source-layout evidence as a secondary concern.
