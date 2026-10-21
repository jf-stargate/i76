# Interstate '76 — v72 results and v73 VOM/FSM handoff

Source: uploaded `i76_v72_rename_decisions.tsv`, `i76_v72_vom_fsm_sites.tsv`, `i76_v72_vom_fsm_edges.tsv`, `i76_v72_vom_fsm_flag_candidates.tsv`, `i76_v72_vom_fsm_decompiled.txt`; v71 18:34 Ghidra snapshot and earlier v59–v63 FSM research. All instructions refer to original i76.exe, image base `00400000`. Decompiled C is reconstruction evidence, not live runtime verification.

## Outcome of v72

- Two guarded v72 renames are reported `VERIFIED_AFTER_COMMIT`:
  - `004587D0` -> `clear_world_object_subtree_status_flags_recursive`.
  - `00458860` -> `clear_world_object_and_descendant_status_flags`.
- The site export includes 33 instruction locations, resolved into containing Ghidra functions.
- Edges export: 761 records (422 OUT, 339 IN). Includes computed-call references; an edge count is not a count of unique semantic call relationships.
- Candidate flag scan: 333 records (240 matches for `0x454`, 45 matches for `0x200`). These are text matches, not all verified object-field accesses. In particular, ordinary `push 0x200` can be a screen or allocation size.

## Verified state domains

| State | Addressing | Producer/consumer evidence | Caution |
|---|---|---|---|
| Vehicle runtime death | `object + 0x70 -> runtime + 0x454`, bit `0x20` | Producer in `00465AF0` at `00465D6D`/`00465D7F`; reads `00463A80`, `0040AF00`, `0040B9E0`, `004157A0`; network reconciler `00464890` can also set/reset runtime flags | Not synonymous with the world dead flag |
| World-object dead | `world object + 0x10`, bit `0x200` | `0040B840` reads it as `isDead`. `00463A80` and `00466180` set it using `00458810`; `00464890` also contains a network death path using `00458810` | Destruction paths and object classes differ; flags propagate through descendants |
| Primary death credit | `AI private + 0xA6E0` | `004157A0` checks runtime dead flag and source identity against primary world entry, writes 0/1 conditionally; `0040B860` returns raw word to FSM opcode 88 | Not rewritten for every event, not a general damage indicator |
| Event source identities | `AI private +0xA6E4/+0xA6E8/+0xA6EC` | Initialized in `00415640`, written conditionally/unconditionally within accepted ledger updates by `004157A0`; read by `whoRammed`, special/`whoShot`, and `whoAttacked` | Identify which source category is eligible before applying a write |
| Event markers | `AI private +0xA6D8/+0xA6D4/+0xA6DC` | `004157A0` writes event-state markers alongside source identities; `0040B800`, `0040B410`, `0040B990` consume and clear them | Marker read is not a passive query; successful query can modify event state |
| Event timestamp | `AI private +0xA6F0` | `004157A0` stores gameplay time; `00420C42` is a separate read in driving/target avoidance | Temporal units and downstream semantics require validation |

## Normal direct-damage path (control-flow relationship)

`004A8240`: `dispatch_damage_context_to_world_object_class_handler` -> conditional `record_vehicle_damage_source_event`. `004A7C80` likewise dispatches class damage before attribution, with a temporary world-object reference and release intervening. `00462040` selects the class-specific damage callback indirectly via the class descriptor table. For class-1 vehicle damage, `00463A80` invokes part-damage handling, observes runtime `+0x454 & 0x20`, and enters catastrophic-breakup or alternate destruction. Those paths can set world `+0x10 & 0x200`; the attribution function then reads runtime death and conditionally credits the active primary source.

This establishes an ordering for those call paths but **does not** establish that all deaths use these exact routes, that the attribution write always fires, or that every FSM poll occurs after both flags change. Preserve these as separate fields in the emulator.

## Critical network exception to investigate

`00464890` (`apply_network_vehicle_state_and_damage_update`) updates `runtime+0x454`, has branches for network death/status packet flags, and calls the world-object status setter with `0x200`. It can introduce additional state transitions that do not pass through local damage-source attribution. v73 therefore includes this full function.

## Event identity and destructive query semantics

Observed FSM host calls (opcode values are decimal or hex representations of the same command):

| Opcode | Command | Field read |
|---|---|---|
| `0x0B` | `whoRammed` | AI `+0xA6E4` |
| `0x0C` | `whoShot` / recent special damage source | AI `+0xA6E8` |
| `0x2E` | `whoAttacked` | AI `+0xA6EC` |
| `0x24` (36) | `isDead` | world-object `+0x10 & 0x200` |
| `0x58` (88) | `isGroovesFault` | AI `+0xA6E0` (raw word) |

The source-ID query functions can add source objects into the FSM command's object-label array and adjust references. Thus query results can modify the VM-visible object table. The event-marker predicates (`0040B410`, `0040B800`, `0040B990`) can write `0xFFFFFFF6` (-10) on successful matches. The `A6DC` variant clears all three event markers. These should not be modeled as pure predicates.

## v73 investigation

Script: `i76_v73_fsm_event_lifecycle.java` (exact requested naming convention). Its operation is **read-only**, with these outputs:

- `i76_v73_fsm_event_functions.tsv` — target ownership and sizes.
- `i76_v73_fsm_event_fields.tsv` — exact bracketed displacement hits across the listing, with estimated READ/WRITE/RMW classification (requires manual verification of base-object identity and dataflow).
- `i76_v73_fsm_event_instructions.tsv` — source assembly for selected FSM/VOM/attribution/network functions.
- `i76_v73_fsm_event_edges.tsv` — incoming and outgoing control-flow references for selected functions.
- `i76_v73_fsm_event_decompiled.txt` — selected current-program decompilation, including commands, event producers/consumers, and network path.

Script checks MD5, image base, signatures, v71 repaired body sizes, and confirmed v72 renames before exporting. No changes to the original Ghidra database are made. This script has not been executed or compiled against a live Ghidra installation here; results must be validated in CodeBrowser.

**Acceptance criteria for the next pass:** verify each source slot's write gate; identify successful poll/clear rules and global event epoch behavior; determine if network replication changes only dead-state flags or also event-credit state; add regression cases to the existing v60-v63 interpreter without inventing missing world fixtures.

## Checkpoint

Once the v73 outputs are reviewed and integrated with tests, commit this report, the versioned Java script, regression code, and a new Ghidra export to the existing GitHub I76 repository. Preserve historical snapshot files. After that, proceed to FSM shared scheduler and callback ordering.
