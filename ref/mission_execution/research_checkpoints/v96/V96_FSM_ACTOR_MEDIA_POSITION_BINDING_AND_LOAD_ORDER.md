# I76 retail mission architecture — v96: FSM actor, media, and named-position binding

**Research date:** 2026-10-20. **Retail executable MD5:** `a640ea0097dbb62e0c77b7f2847c7161`.

**Scope:** source-backed research, not reconstruction or dynamic execution. This checkpoint uses native Ghidra 12.1.4 decompilation and decoded x86 of the annotated v95 program, plus a read-only structural comparison of the 80 shipped `miss8`/`miss16` missions. Changes to symbols occurred only in a separate working program. Every newly exported name was verified through a clean reimport.

## Executive results

1. **Resolved and corrected the actual world-object instance-key lookup.** `004AD5B0` was historically named `world_instance_id_remove_context_helper_004ad5b0`, but its code scans a 16-byte-stride registry *backwards*, compares two 32-bit key words, and returns the third word (a world-object pointer). It performs **no removal**. Its wrapper `00457630` calls it, leaving the return pointer in `EAX`; Ghidra's previously inherited `void` signature obscured that fact. The finalizer's actor-resolution routine at `00412400` saves that `EAX` into each actor runtime record at `+0x58`, then acquires a counted world-object reference when nonzero.
2. **Established the producer/consumer pairing for world-object identity.** During ODEF loading, `004B7AC0` creates/registers live objects and calls `00457610` to insert `{key_word0,key_word1,object_pointer}` into the instance registry at `0054A178`. The insertion routine is `004AD450`, using 16-byte entries. During ADEF/FSM finalization, `00412400` performs reverse lookup with both serialized key words at actor `+0x50/+0x54`, independently of the actor's script label. These functions are separated across the binary but share the same registry representation.
3. **Validated the identity linkage against the shipped corpus.** In all 50 nonempty FSM chunks across `miss8` and `miss16`, there are 794 serialized actor-key occurrences (397 per variant). The exact eight serialized key bytes appear contiguously in the *same mission's* `ODEF` chunk in **all 794** cases. 792 keys appear once in their ODEF chunk; `shack1` in `T15.MSN` appears twice in each of the two resource variants. This is strong corpus corroboration but is not, by itself, proof of successful *runtime* registry insertion for every key; it is a raw byte comparison, not a complete ODEF parser.
4. **ADEF ordering is important and consistent.** The 80 BWD2 envelopes put `ODEF` before `ADEF`, and the verified load sequence is sequential descriptor dispatch. The normal path therefore populates the instance registry from world loading before the FSM finalizer tries to resolve actors. There may also be preloaded or dynamically registered world objects; do not equate the set of ODEF keys with the entire runtime registry.
5. **Actor labels and identity keys are distinct.** Each actor's first 40 serialized bytes are its script label; the next two words form its registry key. `00412400` checks duplicate key pairs with *different* labels and reports an error. The shipped `T16` and `T17` missions deliberately contain two `user` actor records with the same key and same label; each duplicate is accepted by this particular check and may independently acquire an ownership reference. Missing runtime instance-key lookups call `report_error`, but this static pass has not established their externally observable fatal/recoverable outcome.
6. **`taurus` is a special binding, not a registered instance count.** On a label equal to `taurus`, `00412400` passes the already-resolved world-object pointer to `0040AEB0`. That routine stores it at `0051F5C4`, and `0040AEC0` reads it; callers include the post-mission audio routine at `0049C4A2` and an effect-target selection path at `00438EFD`. The inherited setter/getter names that described this value as an "instance count" were wrong. The corpus contains `taurus` in eight missions per resource variant. The pointer's independent ownership is *not* established by the global; its actor binding holds a reference.
7. **Media is validated by resource category, not attached to world objects.** `004122D0` walks runtime media records (stride `0x54`), tests the filename's last four characters for `.wav` or `.smk`, calls `resource_exists_in_cache_or_search_paths` for WAV and `find_cutscene_smk_file` for SMK, then writes `record+0x50 = 1` for success or 0 for failure. Unsupported or failed checks also call `report_error`. All 6,738 serialized media records in both resource variants end in WAV or SMK: 6,734 WAV, four SMK. This categorization says nothing by itself about whether the corresponding files were actually accessible at runtime.
8. **Named positions are standalone vector lists.** The loader at `004102D0` allocates `0x58`-byte runtime records, each holding a 40-byte script name, a vector count at `+0x50`, and a pointer at `+0x54` to the read-in triples of 32-bit floats. `004125C0` does *not* perform any world-object identity resolution for this table. Host commands access the position records through integer indices and their `0x58` stride. Across each shipped resource variant the scripts carry 551 named-position records. Duplicate names appear in several missions, but an error for those duplicates was **not** established in the audited position-loader/finalizer paths; duplicate text is not itself evidence of a malformed mission.

## Runtime initialization sequence — established path

| Phase | Site | Verified behavior |
|---|---|---|
| BWD2 envelope | `004B42B0`, `004B3DB0` | Parse tagged, ordered mission sections |
| ODEF population | `004B7AC0` | Construct/load object, register active world entry, register paired key via `00457610` when eligible |
| ADEF wrapper | `004B45F0`, `004B89B0` | Handle `AREV`, `FSM`, `EXIT` through child descriptor table |
| FSM import | `00409740`, `00410720` | Read command, actor, media, named-position, node, initial-word, token arrays |
| Command fixup | `004125C0` → `00410A10` | Convert command names to numerical host-command IDs; store at `command+0x50` |
| Actor binding | `004125C0` → `00412400` → `00457630` → `004AD5B0` | Use paired 32-bit key, populate `actor+0x58`, incref resolved object |
| Media check | `004125C0` → `004122D0` | Validate WAV or SMK and set availability/status at `media+0x50` |
| Node relocation | `004125C0` → `00412500` | Fix initial VM execution pointers/frames using the loaded token/word arrays |
| Script runtime | `0040A320` → `004149F0` → `00414670` | Cooperative node scheduler and token execution |

This is the normal traced code path, not an assertion of all possible runtime entrypoints or input sequences.

## Registry representation and side effects

`0054A178` points to the instance table context. `004AD450` manages records of 16 bytes; at offset 0 it stores the first key word, at 4 the second, and at 8 the world-object pointer. `004AD5B0` searches backward by paired key and returns the stored pointer or zero. Its name was corrected because its old `remove` description was contradicted by native instructions. The checked world-object registration wrapper at `00457610` returns no useful pointer; the lookup wrapper at `00457630` *does* preserve the pointer result in `EAX`, even though the inherited decompiler signature says `void`.

`00412400` uses this return value as an object pointer. Upon success, it stores it at actor `+0x58` and calls `0045ED00` to acquire ownership. Later world-object unregister callbacks clear these actor bindings and relinquish the counted references, as established in v83–v88. The two key words at actor `+0x50/+0x54` remain the source of actor identity, whereas the actor name is used for duplicate-label consistency and special handling of `taurus`.

**Caution:** `004AD450` also has nonunique-key reporting and allocation-related behavior; its entire failure-handling contract has not been established by this pass. Further refinement should start with raw assembly, because the inherited prototype and some decompiler expressions are unreliable.

## Corpus evidence and ambiguities

- **Both resource variants:** 25 nonempty scripts each; every one parsed completely with no unexpected trailing bytes. The original v95 corpus established the enclosing BWD2/ADEF chunk boundaries.
- **Per variant:** 397 actor rows, 3,369 media rows, and 551 named-position records. Max per mission: 42 actor rows, 170 media rows, 52 named-position records. These are occurrences, not distinct game objects or unique resource names.
- **Media:** 3,367 `.wav` and two `.smk` names per variant. Existence was *not* tested with the game resource cache.
- **Actor ODEF byte cross-check:** all 794 paired keys occur contiguously in their corresponding `ODEF` sections. This is stronger than comparing the names but is not a proof of runtime object loading or liveness.
- **Duplicate actor keys:** the repeated pair in `T16.MSN` and `T17.MSN` is labeled `user` on both occurrences, in both resource variants. This satisfies the *particular* duplicate-label check seen in `00412400`.
- **Named-position labels:** some source lists repeat a name. These are stored as independent indexed records; a global label uniqueness rule is not established.
- **Media-name validator:** its suffix access assumes a meaningful filename length; do not infer well-formed-input guarantees from successful stock corpus parsing.

## High-confidence symbol changes

The final, **separately exported and reimport-verified** Ghidra program `i76_mission_v96_committed_symbols.gzf` contains six changes on top of v95:

| Address | Updated annotation | Rationale |
|---|---|---|
| `004AD5B0` | `lookup_world_object_by_instance_key` | Reverse-searches registry; no removal |
| `00457630` | `lookup_registered_world_object_by_instance_key` | Wrapper preserves `EAX` return from `004AD5B0` |
| `00457610` | `register_world_object_instance_key` | Wrapper calls instance registry insert `004AD450` |
| `0040AEB0` | `set_fsm_taurus_world_object` | Stores world-object pointer for literal `taurus` |
| `0040AEC0` | `get_fsm_taurus_world_object` | Returns pointer from special actor global |
| `0051F5C4` | `g_fsm_taurus_world_object` | Global is pointer, not an actor count |

**Export integrity:** The program was saved before executing the final GZF pack operation. The packed GZF was independently imported into a fresh project, where all 11 checks (nine functions, global symbol, and retail PE MD5) passed. Superseded scratch exports made before the save are not included as deliverables.

## Future behavioral tests, not implementations

1. Load a mission with an actor key not found in the instance registry: determine whether `report_error` leaves the pointer zero and whether the mission continues.
2. Load a mission with two actor rows having an identical key and name: determine whether both hold references and how unregister clears them (stock T16/T17 are useful baseline inputs).
3. Load a mission with an existing WAV and with a missing WAV; confirm `media+0x50` and diagnostic behavior.
4. Load a mission with a valid SMK name; verify the specialized cutscene catalog lookup.
5. Test duplicated named-position labels and index-directed commands, without assuming name uniqueness.
6. Test the `taurus` special binding through post-mission audio and effect-target selection, including absent-actor behavior.
7. Trace abnormal mission loads where `ODEF` registration is partial, then determine whether FSM finalization still occurs.

## Remaining questions

- Precise instance-registry lifecycle (reset, duplicate handling, allocator error behavior) across mission restarts and mixed modes.
- Exact real-world meaning/encoding of the paired eight-byte key, beyond its bytewise equality semantics. `004AD450` treats it as an eight-character identity in one error-rendering path but also masks high bits.
- Whether `report_error` is fatal/recoverable at every fixup call site and in which runtime modes.
- Other callers reading the resolved `taurus` pointer and the effects of a missing special actor.
- Whether named-position vector buffers are fully released on every FSM shutdown path.
- Full ODEF record parsing would allow a stronger semantic cross-check than matching key bytes within the ODEF chunk.

**Source-layout note:** See `V96_SOURCE_LAYOUT_ADDITIONS.md`. Original translation-unit boundaries remain hypotheses.
