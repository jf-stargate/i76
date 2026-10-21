# Interstate '76 — FSM runtime, events, and scheduler reference

**Evidence cutoff:** original retail `i76.exe`, Ghidra state export `20261019_205431` (2026-10-19 20:54:59 PDT), research iterations v57–v76. Executable MD5 `a640ea0097dbb62e0c77b7f2847c7161`. All addresses are image-base `0x00400000` virtual addresses. **This describes static binary evidence and prior offline mission-corpus tests; it is not a validated live-game, full-world replay.**

The companion [vehicle object runtime reference](../vehicle_object_model/i76_vehicle_object_runtime_reference.md) documents the object and AI-state fields consumed by FSM commands. The [October 2026 research checkpoint](../game/i76_research_checkpoint_20261019.md) records evidence provenance, known gaps, and proposed next work.

## Runtime architecture

```text
BWD2 mission ADEF/FSM
  -> 00409740  load_fsm_chunk_from_bwd2_descriptor
     -> 00410720  load_serialized_fsm_runtime_tables
        -> 00410490  load_serialized_fsm_linked_state_blocks
     -> 004125C0  finalize_loaded_fsm_runtime_tables
        -> 00410A10  initialize_fsm_command_name_table
        -> 00412400  register_fsm_instance_ids_from_mission
        -> 004122D0  validate_project_wav_smk_resource_list
        -> 00412500  initialize_fsm_execution_node_relocations
  -> 0040A320  update_fsm_vehicle_runtime_frame (when enabled)
     -> 004149F0  process_pending_fsm_instruction_list
        -> 00414670  execute_fsm_vm_token_stream
           -> 00412CE0  dispatch_fsm_host_command_record
              -> world-object / vehicle / AI / mission / media services
     -> 004155F0  increment_vehicle_damage_source_event_state
```

`00409740` takes a BWD2 descriptor with length at `+0x04` and payload at `+0x08`, calls the loader and then the finalizer. It creates a dedicated Windows heap for FSM runtime tables. Serialization and runtime table ownership are different from normal world-object allocations. The loader is substantially understood; this does **not** imply every host command's downstream effects have been implemented.

## Serialized inputs and runtime storage

| Resource | Runtime representation | Evidence / limitation |
|---|---|---|
| Command prototypes | `0x54`-byte command records, decoded command ID at record `+0x50` | Name-to-ID resolver `00410A10`; dispatcher `00412CE0` handles IDs `0..95`, with `0x16` an error/unsupported route |
| Named mission objects | `0x60`-byte instance records | Identifier words `+0x50`, `+0x54`; resolved reference at `+0x58` via `00412400` |
| Named vector resources | `0x58`-byte rows with variable `vec3` list | Loader `004102D0` |
| Named bitfield resources | `0x60`-byte runtime rows | Loader `004105A0` |
| FSM shared words | `u32` array | Relocation source, not a separate VM task list |
| Tokens | `{u32 kind, u32 payload}`, 8 bytes | VM `00414670`, 14 recognized operational kinds `1..0x0E` |
| Initial execution nodes | Linked `0x10BC`-byte blocks, with 40 initial serialized context words | Allocator `00410490`; relocation `00412500` |

**Do not conflate** the `0x60`-byte mission actor records with the `0x54`-byte host command records. Token payload indices, resolved word pointers, and object references also occupy separate namespaces.

### Persistent execution-node layout

| Offset | Retail role |
|---|---|
| `+0x0000` | Serialized initial working words; populated entries are relocated into shared-word pointers |
| `+0x1000` | Host-command argument/operand workspace |
| `+0x10A0` | VM result/condition word; not always normalized to bool by host services |
| `+0x10A4` | Base of token stream |
| `+0x10A8` | Current token instruction pointer |
| `+0x10AC` | Current frame pointer |
| `+0x10B0` | VM stack pointer |
| `+0x10B4` | Host-command operand cursor |
| `+0x10B8` | Next pending node (singly linked) |

The loader requests `0x10BC` for each initial node, chains them, installs initial entry tokens and 40 working words. The relocation routine patches populated context words, initializes the frame/stack and sets the token-base/IP fields. Ghidra and original-PE static scans found only the two literal `0x10BC` allocation *instructions* in `00410490`; this supports loader-constructed persistent nodes, but **does not prove that no indirect or differently sized runtime allocation exists**.

### VM and scheduler semantics

The 14-operation VM at `00414670` supports stack/frame operations, absolute token jumps, conditional branches, host-command dispatch (kind `0x0D`), and condition inversion (kind `0x0E`). Token kind `0x0A` updates the saved PC and **returns 0 (yield)**. The top-level frame return at kind `0x0C` **returns 1 (finished)**. This distinction is executable-verified.

`004149F0` traverses the pending singly linked list. A completed node is unlinked and freed using the mission heap; a yielded node remains linked. Importantly, **a yield does not terminate the list walk**: later nodes can execute in that same pass. The scheduler handles head removal and interior removal separately. A faithful emulator must preserve node order, each node's independent saved PC/frame/stack, and shared-world side effects in traversal order. It must not execute every node as an isolated full mission.

Known globals in the original executable:

| Address | Interpretation |
|---|---|
| `0051F628` | Pending-node list head |
| `0051F62C` | Pending-node count |
| `0051F620` / `0051F624` | Mission actor records base / count |
| `0051F640` | Outer FSM/vehicle-runtime update gate; nonzero bypasses the update body |
| `0051F5C0` | Switches normal single-player FSM traversal to alternative AI update path when nonzero |
| `00524550` | Shared FSM/AI update epoch, historically named `g_vehicle_damage_source_event_state` |

## Frame-local execution order

Within `0040A320`, provided `0051F640 == 0`:

1. Commit active-control transition state; clear/reset per-pass progress counters.
2. Precompute registered vehicle/AI target/terrain-related fields.
3. If **not** network/trip mode **and** `0051F5C0 == 0`, run `004149F0` pending-list traversal; **otherwise** run `0040A130` AI-vehicle update. The two branches are alternatives, not two consecutive passes.
4. Run `00414B60` progress-state comparison; increment the shared epoch using `004155F0` (callsite `0040A658`).
5. Perform the remaining per-pass state cleanup.

**Scope limit:** This proves the local order inside `0040A320`, not its absolute place relative to physics contact generation, collision callbacks, outer game-loop input, rendering, or mission clock advance. The epoch is also sampled by `0041D240` to select one of four rolling safe-drive slots (`epoch % 4`), so it is not unique to damage reporting.

## Damage-event contract

`004157A0` records eligible vehicle damage-source events in a large AI-private structure reached from the world object through runtime state. Initialization in `00415640` sets event markers to `0xFFFFFFF6` (`-10`), sources to null and attribution to zero.

| AI-private offset | Meaning | Host-visible behavior |
|---|---|---|
| `+0xA6D4` | Shot/special-source event epoch | `isShot` (`0x20`, `0040B410`) checks `epoch` or `epoch-1`, then replaces marker with `-10` |
| `+0xA6D8` | Ram/general-nonspecial event epoch | `isRammed` (`0x23`, `0040B800`), same consume rule |
| `+0xA6DC` | General attack event epoch | `isAttacked` (`0x2D`, `0040B990`) matches epoch or previous and clears **all three** event markers on success |
| `+0xA6E4` | Ramming-source world-object reference | `whoRammed` (`0x0B`, `0040AFF0`) resolves a source into mission object's label/reference table |
| `+0xA6E8` | Shot/special-source reference | `whoShot` (`0x0C`, `0040B0F0`) similarly resolves a source |
| `+0xA6EC` | General attack-source reference | `whoAttacked` (`0x2E`, `0040B1F0`) similarly resolves a source |
| `+0xA6E0` | Conditional, sticky primary-actor death attribution | `isGroovesFault` (`0x58`, `0040B860`) returns **raw 32-bit word** |
| `+0xA6F0` | Gameplay-time timestamp | Written by event producer; also used by AI logic |

For the category-qualifying direct/radial damage paths, the engine dispatches class-specific damage **before** stamping the event ledger. `004157A0` conditionally updates category-specific source/epoch fields and generally stamps the attack source and timestamp. The runtime dead-car flag gates conditional primary-source fatality attribution, **not all accepted ledger writes**. Successful `isShot`, `isRammed` or `isAttacked` queries are *destructive*; `who...` source queries are not destructive to event markers, though they can alter/extend the VM object-label table. Source fields are not automatically erased when an event marker is consumed.

A marker stamped at epoch `E` may be recognized by a consuming predicate at `E` or `E+1`; this is an integer comparison contract, **not** a guarantee about when a real collision is delivered relative to the next FSM update. The `0xA6D8` read at `0041C2C0` instead compares **only** against the current epoch (non-consuming); seven `clsnDmg` static descriptors point at that function. Their invoking dispatcher has not yet been proven. Its present Ghidra name, `is_ai_vehicle_target_matching_current_player_or_actor`, is semantically misleading; retain the address as the stable key until callers are traced.

## Other FSM-visible vehicle state

- `isDead` (`0x24`, `0040B840`) reads `object+0x10 & 0x200`, not the vehicle runtime dead-car bit.
- `destroy` (`0x32`, `0040B9E0`) and `sit` (`0x03`, `0040AF00`) test `runtime+0x454 & 0x20` on vehicle-specific paths.
- `isAirborne` (`0x56`) reads a **different** runtime flag bit; do not merge it with dead-car status.
- Network state replication (`00464890`) has its own death/visual update route; do not assume it stamps the local damage-source ledger.

## Validation and outstanding work

The prior v60–v63 offline baseline exercised 797 initial FSM nodes across 25 missions (7,336 tokens reported, no v60/v61 divergences for the tested sample). These tests establish parser/VM regression behavior, **not** equivalence to the retail engine's live scheduler or physics. Preserve that corpus and add tests for: two nodes yielding on one tick, successful predicate consumption order, actor unregistration during active execution, fatal damage-source credit, mode-specific scheduler gating and a timer-driven objective transition.

Highest-priority unresolved contracts: world-object reference invalidation on unregister (`00409980` has now been defined in Ghidra); real collision-to-ledger ingress; whole-frame ordering beyond `0040A320`; AI/navigation/visibility/ammo-producing services; timer/callback/media completion behavior; and mode-specific replication. The `0040C020` `STOPCBXX` wrapper calls a timer/event service, **not** the pending-node list. Do not treat all `cb*` commands as coroutine creation.

Evidence entry points: `snapshot/i76.exe/i76.exe_ghidra_state_snapshot_20261019_205431/` (relative to repository root), prior v72–v76 research exports, and `scripts/ghidra_history/i76_v73_fsm_event_lifecycle.java` through `i76_v76_fsm_loader_callback_closure.java` as present in this checkpoint. The 20:54 snapshot is authoritative for **current function-definition state**, not proof that all prior focused exports are included in its decompilation subset.
