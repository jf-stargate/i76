# Interstate '76 — Vehicle Object Model (VOM) and FSM identity bridge

**Checkpoint:** retail `i76.exe`, MD5 `a640ea0097dbb62e0c77b7f2847c7161`; Ghidra export `20261019_205431` (2026-10-19 20:54:59 PDT); focused evidence from v64–v76. Addresses below are original executable VAs, image base `0x00400000`. The focus is on **FSM-visible object and vehicle state**, not a claim that every physics, drivetrain, mesh or AI-private field is fully decoded. See [FSM runtime reference](../fsm/i76_fsm_runtime_reference.md).

## Object identity and storage layers

| Layer | Access / record | Role and confidence |
|---|---|---|
| World object | `object + 0x10` | 32-bit status flags (`0x200` destruction, with other unrelated bits); high for tested accesses |
| World class | `object + 0x6C` | Class discriminator for callback dispatch; class 1 vehicle confirmed |
| Class-specific runtime | `object + 0x70` | Pointer to runtime object; depends on class |
| World-object tree | `object + 0x60`, `+0x64` | Sibling and child traversal links as used by recursive status helpers; review relationships per function rather than assuming uniform ownership |
| Vehicle runtime flags | `runtime + 0x454` | `0x20` dead-car bit, distinct from world-object `0x200`; other bit meanings independent |
| AI-private behavior state | `*(runtime + 0x108)` in relevant vehicle/actor paths | Large state block (allocator `00415640` requests `0xA9D8` bytes); includes damage ledger, tactics, navigation and event state |
| Active world-object entry | Entry has pointer to object at `+0x00` | `004572B0` registers; `00457420` unregisters; per-entry size `0x78` bytes |
| Mission actor slot | `0x60`-byte record, object ref `+0x58` | FSM script identity binding via instance ID at `+0x50/+0x54` |

Do not conflate the **world object pointer**, an **active world-object entry pointer**, the **vehicle runtime pointer**, and the **AI-private pointer**. Different callbacks and conditions expect different levels of indirection. The exact struct layouts should be extended with address-specific evidence, not inferred from names.

## Registration: world object to FSM-accessible vehicle

```text
00409BD0 initialize_fsm_vehicle_runtime_system
   -> register active-entry callback 00409850
   -> register removal callback 00409980

004572B0 register_active_world_object_entry
   -> store object; take object-tree reference; compute bounds
   -> invoke registered entry callbacks (including 00409850)
      -> class/vehicle eligibility check
      -> choose one of 8 team buckets from (world status >>16) & 7
      -> add active-entry pointer to bucket 00507DA0
      -> increment bucket count in 0051F5D0
      -> initialize/reset AI-private context and affected AI refresh bits

00412400 register_fsm_instance_ids_from_mission
   -> lookup (record+0x50, record+0x54) at 00457630
   -> store live object pointer at record+0x58
   -> increment world-object reference where found
```

`00409850` is currently named `initialize_fsm_runtime_heap_and_tables` in Ghidra, but its **observed behavior is the active world-object registration callback**. The heap/table loader is instead `00409740`/`00410720`. Rename `00409850` in a later guarded semantics pass after comparing registration and teardown; this documentation keeps the unchanged Ghidra symbol for traceability.

Team registry uses eight buckets (`0051F5D0..0051F5EF` counts; entries at `00507DA0`, 64 pointer slots per bucket, stride `0x100`). The registration callback is executed by the active-world-object registry; it is not part of parsing the serialized FSM execution nodes.

## Object removal: newly defined `00409980`

**Ghidra checkpoint fact:** The October 19, 20:54 snapshot contains an actual function at `00409980`, with indexed body `00409980–00409BC0` inclusive (`577` bytes), currently named `FUN_00409980` with a default source type. Prior v76 exports showed this code but lacked function ownership. The new definition changes the function count from 2096 to 2097. This checkpoint **does not** claim a semantic rename has been applied.

**Assembly-supported behavior** (verified against retail PE `00409980–00409BC0`):

1. Takes an active-world-object entry, obtaining the referenced world object from `*entry`; null/unsupported branches short-circuit some work.
2. Scans registered team entries for AI-private `+0xA9B4` references that point to the object being removed; invokes the reference-release helper `0045EF70` and clears matching fields.
3. For qualifying vehicle/actor classes, computes team from `(object+0x10 >> 16) & 7`, finds the entry in the corresponding bucket, and prepares its removal.
4. Iterates mission actor records (`0051F620` base, `0051F624` count, stride `0x60`); when actor `+0x58` equals the removed object, calls `0045EF70` and replaces the binding with NULL.
5. Releases the removed object's own AI-held `+0xA9B4` reference where applicable.
6. Compacts the team bucket, decrements the count, nulls its trailing slot, and sets AI-private `+0xA714 = 1` across remaining registered objects.

**Important branch qualification:** The callback's class and entry-membership tests matter. Not every step runs on every input, and the Ghidra-exported 577-byte boundary is evidence of definition, not a proof that refcount ordering, null-argument behavior and all indirect callers are settled.

The owner of the callback invocation is `00457420` (`unregister_active_world_object_entry_and_release`), which walks registered world-object-tree callbacks **before** its final world-object cleanup/release operations. The callback itself is registered by `00409BD0`. We now have a concrete invalidation path from world-object teardown to mission actor slots. We do **not** yet know what every FSM host command does when a saved label is NULL, whether all pending-node operand references are rewritten immediately, or every possible teardown/re-register order.

### Recommended semantic name (not applied)

`unregister_fsm_vehicle_world_object_and_invalidate_references_00409980`

The name is deliberately descriptive; retain `FUN_00409980` in file/trace references until an explicit guarded rename script is run and a subsequent snapshot verifies the change.

## Death and damage state must remain separate

| Domain | Retail location | Observed producers / consumers | Semantic warning |
|---|---|---|---|
| Vehicle runtime dead | `runtime+0x454 & 0x20` | Set by component-damage path `00465AF0`; read by `00463A80`, `0040AF00`, `0040B9E0`, `004157A0`; network updater has distinct route | Not identical to world-object death or player attribution |
| World-object dead | `object+0x10 & 0x200` | Set/propagated by `00458810` from catastrophic/destruction paths, including `00466180`, and by a network route; read by `0040B840` `isDead` | Also applies to other world-object classes; propagates to child tree |
| Primary-actor death credit | `AI+0xA6E0` | Set conditionally by `004157A0` when runtime dead and source identity matches active primary world entry; read by `isGroovesFault` | Sticky/conditional, not a generic hit flag |
| Damage-event identity | `AI+A6D4..A6F0` | Stamped by `004157A0`, read/consumed by separate FSM host predicates | Epoch markers and source-object references are separate |

`00458790`/`00458810` OR status bits across world-object descendants; `004587D0`/`00458860` clear them. Their two clear-helper semantic names were applied during v72 and are present in the latest snapshot. **Do not derive the AI damage ledger by watching only object-death bits**: an accepted source event may update source and epoch while the vehicle is still alive.

## Direct, radial, and network damage

The class damage dispatcher `00462040` looks up a function through the 13-slot-per-class callback descriptor table. For class 1, `00463A80` handles vehicle-class damage, calls part damage `00465AF0`, then takes catastrophic or alternate destruction paths when its runtime state indicates death. `00466180` performs catastrophic effects and propagates world-object death. The direct/radial dispatchers (`004A8240`, `004A7C80`) call class damage before ledger recording `004157A0`; that ordering is supported for these paths, **not universally all damage**. `00464890` applies network vehicle state and may independently set runtime/world death state without the ordinary local attribution path.

In addition, seven static descriptors labeled `clsnDmg` in the original PE reference `0041C2C0`; that function reads AI `+0xA6D8` and compares it to the **current** update epoch. Static descriptor ownership and indirect callback timing remain unresolved. Its old label `is_ai_vehicle_target_matching_current_player_or_actor` is inconsistent with its actual comparison; do not use that name as a behavior specification.

## VOM contract required for FSM simulation

An offline replay should preserve, for each world object, at least: stable identity; class; world status flags; an optional vehicle runtime with independent dead/effect status; an optional AI-private damage-event record; and whether active registry, mission actor, and VM label references remain valid. Event timestamps and epoch markers are separate from object lifetime. World object destruction is not automatically equivalent to removing its registry entry, and null actor bindings should not be silently replaced with permanently valid references.

**Open dependencies (priority order):** exact cleanup/refcount behavior of `00409980` and related helpers including `0045EF70`; null-actor behavior in FSM commands; collision callback/descriptor evaluator and event ingress; physics-to-FSM frame chronology; command dependencies on AI/steering/pathfinding/weapon state. The updated snapshot resolves the *function-boundary* blocker only. Preserve these distinctions in subsequent Ghidra research and integrated tests.
