# Interstate '76 — v75 FSM pending-node lifecycle, deeply traced

## Provenance and qualification

Inputs: user-provided `i76_v75_fsm_{epoch_xrefs,functions,global_xrefs,node_fields,windows}.tsv` (2026-10-19); prior v72–v74 evidence exports; and original retail `i76.exe` extracted locally from the user-supplied game archive. The PE MD5 was independently verified as `a640ea0097dbb62e0c77b7f2847c7161`. All listed instruction addresses are virtual addresses with image base `00400000`. The original PE was examined through `objdump -d -Mintel`, not executed. Decompilation-level conclusions are explicitly bounded by the supplied v74 exports; **the v75 decompiled/call-edge exports themselves were not among the five new files**.

The five v75 exports have 27 function rows, 52 global-reference rows, 122 node-field rows, 1,617 disassembly-window rows, and six direct epoch xrefs (excluding headers). These are source-generated candidate collections, not exhaustive lists of aliased memory accesses.

## 1. Complete observed creation-to-destruction chain

`00409740` (`load_fsm_chunk_from_bwd2_descriptor`): the mission asset descriptor provides the serialized FSM source. At `00409776–004097CD` it prepares a large list of destinations, **passing the address** of the live node-head global `0051F628` and count global `0051F62C`, and calls `00410720`. At `004097D2–00409832`, it passes the resulting **values** into `004125C0` for finalization. Both routines execute before importer return `00409844`.

`00410720` (`load_serialized_fsm_runtime_tables`): deserializes several independent arrays and invokes `004102D0` at `0041091B` (vector-associated records), `00410490` at `0041092E` (pending execution nodes), and `004105A0` at `00410826` (bitfield records). Additional tables use `0x54`-byte records (e.g. starting at `00410761`), with loader cursor at `005244D4` and serialized words at `005244D0`. Thus **VM token records, script actor reference records, and live VM nodes are distinct arrays**. Do not conflate them.

`00410490` (`load_serialized_fsm_linked_state_blocks`): requests `0x10BC` bytes from allocator import `[004BC108]` for each node. The first `push 0x10BC` occurs at `004104CC`, subsequent nodes at `004104ED`. It links each predecessor through `+0x10B8` at `004104F7`, writes a final NULL at `00410512`, loads the initial **serialized** PC token index into `+0x10A8` at `00410535`, copies precisely 40 DWORDs to the node's beginning at `00410559–00410577`, and records the count of those words selected for relocation at `+0x10B0` (`0041057D–00410580`). It advances to `+0x10B8` to load the next node (`00410586`). This routine initializes the linked list from serialized content, not from a real-time triggered event.

`004125C0` (`finalize_loaded_fsm_runtime_tables`) completes three distinct phases: resolves host-command metadata through `00410A10` at `004125CF`, registers/binds mission world references using `00412400` at `004125EB`, processes mission labels using `004122D0` at `004125FD`, and then initializes live VM node state with `00412500` at `00412619`.

`00412500` (`initialize_fsm_execution_node_relocations`): with args `(node_head, node_count, token_stream_base, global_words_base)` inferred from registers/stack on entry, iterates the existing `+0x10B8` chain. For each node, `+0x10B0` initially delimits the serialized word-index area. It relocates *each populated working DWORD* in `[node, node + 4*word_count)` from an index `i` to `global_words_base + 4*i` (`00412521–0041253E`). It clears `node+0x10A0` (`00412546`), converts saved `+0x10A8` token index `j` to `token_stream_base + 8*j` (`00412540–00412559`), and constructs an initial VM frame/return-stack sentinel (`0041255F–00412592`). `+0x10AC` becomes the initial frame pointer, `+0x10B0` the live stack pointer, `+0x10B4` the host command argument cursor at `node+0x1000` (`00412598–0041259E`). It follows `node+0x10B8`, without allocating or duplicating nodes.

`0040A320` (`update_fsm_vehicle_runtime_frame`): when the outer guard `0051F640` permits update, it prepares AI data, then invokes either pending FSM processing (`0040A644 -> 004149F0`) in single-player-enabled mode, **or** AI player-targeting update (`0040A64E -> 0040A130`) in the alternate mode. At the shared convergence point it updates progress (`0040A653`), then increments shared epoch (`0040A658 -> 004155F0`). This is not evidence that the alternate AI branch invokes FSM VM nodes.

`004149F0` (`process_pending_fsm_instruction_list`): it first drains completed head nodes (`00414A58` VM execution, then `00414A79` successor load, `00414A84` head change and imported heap free `00414A86`). When the first retained/yielded head is found, it traverses remaining nodes once (`00414AE4` VM call), and unlinks/free completed nodes (`00414B05–00414B12`) while retaining yielded nodes (`00414B2C–00414B30`). Every completed node decrements the count (`00414A6F–00414A72` and `00414AFA–00414AFB`). Nonzero VM return means complete; token-VM's observed top-level return emits `1`, and yield returns `0`. In the ordinary, unmutated list case, each active node executes once per pass and surviving nodes retain their original relative order.

### Static exhaustiveness test (bounded)

An independent full `.text` disassembly scan of the exact retail PE finds **two** literal instructions referencing allocation size `0x10BC`, both in `00410490`. It finds **ten** textual instruction operands using `+0x10B8`: three in the serialized-node loader, one in relocation, and six in the pending scheduler. Direct references to `0051F628` are limited to initialized NULL (`00409C5A`), importer address/value passing (`00409799`, `004097F4`) and scheduler pointer passing (`0040A60F`). This is **strong static evidence** that the normal runtime does not allocate/append new FSM execution nodes. It does not rule out code reached via computed offsets, alternative allocators/sizes, or indirect calls, so *absence* remains a high-confidence inference, not a mathematically exhaustive proof.

## 2. VM node structure and initialization

Each heap node is `0x10BC` bytes (4,284 bytes). The early bytes house serialized index words and runtime stack storage, while the end contains the VM execution context. The loader copies up to 40 serialized DWORD words into the beginning of the node; `+0x10B0` at load time indicates how many of these working words will be relocated. That number must be bounded in a safe reimplementation; it should not be treated as a new stack pointer before relocation.

| Offset | Initialization | Role at runtime |
| --- | --- | --- |
| `+0000` | 40 serialized DWORDs, some converted to global-word pointers | Working stack / references |
| `+1000` | Cursor initialized at node+1000 | Host-command operand workspace |
| `+10A0` | zero | VM branch condition / last predicate result |
| `+10A4` | token-stream base | Immutable code base for indexed branches |
| `+10A8` | `code_base + 8*serialized_token_index` | Live instruction pointer |
| `+10AC` | `node + 4*serialized_word_count + 4` | Initial call/frame pointer |
| `+10B0` | `node + 4*serialized_word_count + 8` | Initial VM stack cursor |
| `+10B4` | node+0x1000 | Host-argument cursor |
| `+10B8` | next allocated node / null | Pending linked-list linkage |

The sentinel initialization at `0041255F–00412592` writes a zero word at the first free stack position and the live initial PC in the next word, then positions the pointers around this initial frame. A Python reimplementation should test these address relationships explicitly; do **not** treat `+10A8` as a token number once relocated.

The VM at `00414670` executes 8-byte `{kind,payload}` tokens and dispatches `0x0D` to host commands; branch instructions use token-base plus `index*8`. Opcode 10 (`0x0A`) yields, retaining PC/state. The top-level completion path at opcode 12 returns 1 and schedules the node for freeing. Consequently a mission's FSM program is a persistent coroutine, not a newly allocated task per callback event.

## 3. Distinguish VOM/registry callbacks from serialized FSM tasks

At `00409BD0`, world-entry callbacks are registered; `00409850` is a registration handler and `00409980` is a world-tree callback entry **embedded as an address argument** (`00409BD0` passes `&LAB_00409980`, not a direct CALL). The registration handler buckets active vehicle world-entry pointers by `(world_object->flags+0x10 >> 16) & 7`, manages the AI-state block, and marks the AI cache as dirty/rebuild-required (`AI+A714`). The unregistration callback at `00409980–00409BBC` scans the same vehicle buckets, drops detached references including mission actor slot `+0x58`, clears `AI+A9B4` references when required, and resets `AI+A714`. Its dataflow and use of `0045EF70` demonstrate registry/reference cleanup; the disassembled callback does **not** allocate `0x10BC` execution nodes or splice the FSM pending list.

`00412400` binds mission actor records of stride `0x60` to registered world objects. The actor record's two key words at `+0x50`/`+0x54` are used in lookup `00457630`, with a resolved world pointer/reference written at `+0x58` (`0041242D`), with corresponding refcount management via `0045ED00`. This is the critical identity bridge between mission script object slots and live VOM objects. The full behavior of the missing-target / duplicate-key path warrants deeper inspection in v76.

`0040C020`, presently named `fsm_stop_callback_handler`, invokes service routine `00423620` with constant arguments `(004C2DCC, 0, 3)`; it does **not** manipulate the FSM execution linked list. The service and literal string should be inspected before interpreting 'stop callback' as FSM scheduling semantics.


### Additional collision-event descriptor identification

A full original-PE `.data` byte search identifies **seven** distinct pointer records containing the literal function address `0041C2C0`, each followed immediately by the eight-byte ASCII label **`clsnDmg\0`**. The corresponding fields before the pointer include small integer descriptor values (`2`, `3`, or `4`). The seven pointer addresses are `004C5234`, `004C78DC`, `004C8C30`, `004C9F84`, `004CB2D8`, `004CD980`, and `004CECD4`; an accompanying TSV preserves the raw static records. By contrast, the complete original PE `.text` direct-call scan finds *no* `CALL 0041C2C0`; its intended invocation is via a function-pointer descriptor. The callback itself reads AI-private marker `+A6D8` and checks equality with the shared epoch (`0041C2C0–0041C2EA`). This is **strong evidence that `0041C2C0` implements the runtime predicate for named collision-damage event `clsnDmg`**, not a current-player target match. This changes its most plausible interpretation and supports a future guarded rename, after cross-checking descriptor loading/caller invocation. The v76 export now includes a direct `.data` callback-descriptor scan, independent of Ghidra's sometimes-missing pointer references.

## 4. Scheduler, event epoch and observability

`004149F0` does not terminate a pass at the first yielded node. It calls `00414670` on subsequent list elements. This affects mission behavior because an event predicate can consume an epoch marker before another node processes it. With fixed traversal order, which node executes first can change script outcome even when vehicle world state is identical.

The shared counter at `00524550` increments once per enabled frame orchestrator call at `0040A658` (not once per FSM task). The event-field predicates accept `marker == epoch` or `marker == epoch-1`, then write sentinel `0xFFFFFFF6`. Because the AI-only branch increments the epoch too, the two-observation-tick window is conditional on how frames execute and whether new damage writes occur. The stored source-object references are separate from event marker consumption. A faithful model should expose all three: queue ordering, epoch, and event ledger.

## 5. Remaining uncertainty and v76 focus

1. **Prove the full serialized format** at the array-boundary level, including count/data-pointer contracts for each argument passed by `00409740` to `00410720`, and exact node-count relationship (`0051F62C`) to the linked-list head (`0051F628`). Check malformed record bounds before allocating a node.
2. **Extract the entire implementation and callers** of `00410A10` (host-command name resolver), `004122D0` (mission label processing), `00412400` (actor lookup/refcount ownership), and `00412630` (AI task init). v75 only exported instruction windows for some of these.
3. **Determine reference ownership and callback timing** during object unregister and mission unload. In particular, trace indirect registration of `00409850` / `00409980`, world teardown events, and whether source-object references can be invalidated while a pending script node is alive.
4. **Reconstruct whole-world interpreter** by combining loader-produced node state with a persistent queue, source-record table and shared epoch. The v60–v63 synthetic node-replay tests cannot establish correct cross-node race/marker-consumption behavior by themselves.
5. **Revisit symbol naming**: `0041C2C0` compares AI `+A6D8` to shared epoch, not player identity; `0040C020` is a service-call shim and may have an over-specific name. Do not rename until callers/strings support a better label.

The v76 script is read-only, checks the established PE and Ghidra baseline, exports decompilation and full instructions for this closure, captures cross-references, and scans for *literal* accesses to key VM offsets. It cannot substitute for dynamic instrumentation of the running game.

## Commit guidance

The confirmed v75 node layout, serialized-node allocation/relocation evidence and this report are an appropriate commit checkpoint before modifying the interpreter. Preserve the source exports and Ghidra script. The next iteration can focus on closure over missing helper functions and direct mission data corpus without redoing v75.
