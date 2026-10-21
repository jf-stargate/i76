# Mission-runtime reverse engineering checkpoint — 2026-10-21

This checkpoint supersedes the October 19 *mission runtime status summary*, not the historical October 19 measurement snapshot. The **v97** annotation baseline and **v0.4** static specification have been augmented with **v0.5/v0.6 original-code Ghidra x86 emulation**.

## Now resolved

- All 96 FSM host opcode IDs inventoried, with argument/result/effect signatures at the dispatcher boundary; 95 normal cases, one unsupported `playScene` error route.
- BWD2/ADEF/FSM seven-table serializer and loader, 95 stock command prototypes, instance-key object lookup, media validation, named-position records and 4,284-byte VM node ABI.
- Linked-list cooperative VM scheduling, yielding, synchronous AI calls, consuming event predicates and deferred success/failure transitions.
- World-object reference ownership versus borrowed pointers; CB radio voice queue distinguished from VM callbacks; normal mission teardown ordering.
- Native-emulated evidence for shared descriptor `seen` bits persisting across selected-mission wrapper calls, including rejected prior parses; wrapper return `1` can coexist with parser failure or omitted FSM import.

## Important qualifications

The original parser and FSM loader are executed under an emulator, **not a live Windows game**. World-building callbacks, media lookup, file-cache and some CRT/heap services were deliberately replaced. No playable malformed mission or full-game repeat-load behavior is established. The latest program database is *v97*, not the read-only v98–v100 research extractors or emulation harness version numbers.

## Navigation

- [Current mission architecture and ABI contracts](../mission_execution/README.md)
- [Fresh annotated symbol/disassembly listings](../../snapshot/i76.exe/i76.exe_ghidra_state_snapshot_20261021_v97/README.md)
- [Previous October 19 research checkpoint](i76_research_checkpoint_20261019.md)

## Pending high-value work

Extend the emulator into actual ODEF object registration, duplicate/missing actor resolution and teardown using retail x86 instructions; then validate runtime loading in a true Windows environment. Preserve all already-recorded original-code vs emulated-service boundaries.
