# Interstate '76 retail mission execution — current research index

**Last consolidated research:** 2026-10-21. **Ghidra symbol baseline:** v97. **Retail executable MD5:** `a640ea0097dbb62e0c77b7f2847c7161`.

This directory is the **current** contract for mission loading and execution in the original retail `i76.exe`; it supersedes *mission-runtime conclusions* in the older October 19 reference notes, but not their independent observations of rendering, geometry or resource extraction.

## Authoritative specifications

- [Mission execution contract](MISSION_EXECUTION_CONTRACT.md): resources, runtime layouts, VM, scheduler, AI, ownership, progression and teardown.
- [96-command host ABI](HOST_COMMAND_ABI_CONTRACT.md) and [opcode matrix](tables/ABI_DISPATCH_CONTRACT_96.tsv): dispatcher-level complete; deep `salvage`/`canSee` algorithms not exhaustively specified.
- [BWD2/FSM loader validation](LOADER_VALIDATION_AND_FAILURE_CONTRACT.md): callback policy, return propagation, resource failures.
- [Descriptor persistence and repeated loads](DESCRIPTOR_STATE_AND_REPEATED_LOAD_CONTRACT.md): static original-code contract; complemented by emulation below.
- [Original-code parser emulation v0.5](ORIGINAL_CODE_PARSER_EMULATION_V05.md) and [original-code selected-mission-loader emulation v0.6](ORIGINAL_CODE_MISSION_LOADER_EMULATION_V06.md): **native x86 instruction emulation, not full retail gameplay**.
- [Emulation contract addendum](EMULATION_CONTRACT_ADDENDUM_V06.md) and [open issues](RECONCILIATION_AND_OPEN_ISSUES.md).
- [Source-layout hypotheses](SOURCE_LAYOUT_HYPOTHESES.md) remain provisional; no original `.c`/`.h` source is claimed recovered.
- [Deferred validation](DEFERRED_VALIDATION_SPEC.md) and [descriptor test plan](DESCRIPTOR_STATE_TEST_PLAN.md).

## Data and reproduction

- [95 compiled stock command names](tables/COMPILED_COMMAND_TABLE_95.tsv), [shipped FSM inventory](tables/RETAIL_MISSION_FSM_INVENTORY.tsv), and [actor-fixup inventory](tables/RETAIL_MISSION_ACTOR_FIXUPS.tsv).
- [Latest generated Ghidra v97 symbol/listing snapshot](../../snapshot/i76.exe/i76.exe_ghidra_state_snapshot_20261021_v97/README.md): whole-program indices plus 55 selected updated decompilations and x86 listings.
- [Original-code emulator sources](../../scripts/ghidra_emulation/) require the separately supplied retail PE and mission files. Game assets and retail binary are not part of this update.
- Individual [v89–v97 research reports](research_checkpoints/) retain detailed incremental evidence and course corrections.

## Evidence classes and limits

**Native-static:** instruction and call-graph evidence in Ghidra v97. **Corpus:** 80 shipped mission files / 40 per `miss8` and `miss16`. **Native-emulated:** original retail parser/loader *subset* in Ghidra's x86 emulator, with selected OS, world-building and media services stubbed. **Not tested:** whole retail gameplay/mission resets, complete actor/media fixups in a live world, arbitrary malformed-input safety.

The entire dispatcher catalog is 96 ID slots, with 95 normal branch targets and an unsupported `playScene` path. The shipped serialized table has 95 commands. Do **not** confuse those counts, or assume the loader's unconditional `1` means a valid mission reached gameplay.
