# Documentation impact - I76EDIT workspace object allocation

## Research identity
- Run: i76edit-20261027T000144Z-3e91ae7d
- Track: i76edit
- Original base: 61c9b3b425010615755a18302cb27068850377c6
- PR/merge: pending human review
- Private editor/GZF hashes: manifest.json inputs/baselines and artifacts/CRT_MALLOC_RESEARCH.md.

## Disposition
Classification: **candidate update and deferred failure-path qualifications**, not an automatic canonical promotion.
Candidate living-reference subsystem: manual/reference/editor/ object and zone lifecycle when a documentation steward chooses a coherent milestone.
Historical reference: ref/editor/README.md, ref/editor/road_terrain_serialization.md and accepted editor v31 run i76edit-20261023T153200Z-64b4e9ad.
No canonical documentation or legacy ref/ edit proposed in this run.

## Evidence-linked candidates
- editor.v33.crt_size_class_and_fallback: original 004232E0/00423300/00423350 align 0x78 to 0x80 and choose SBH then Win32 fallback depending on threshold/return. Native emulation; caveat synthetic CRT state. Candidate ADD.
- editor.v33.new_handler_allocation_retry: original 00426230 callback controls retry on CRT allocation failure. Native emulation with synthetic callback. Candidate ADD with mode limitation.
- editor.v33.constructor_native_crt_lifecycle: original 00409840 -> 0041C430 -> 00409DC0 -> 00409A60 -> 00422FA0 tested in one emulation state. Candidate ADD limited to isolated heap callbacks.
- editor.v33.node_heap_allocation_failure: original constructor does not free previously allocated payload when list-node HeapAlloc fails along tested path. Candidate DEFER any claim of actual retail-process memory leak.
- editor.v33.malloc_null_dereference_path: 0040989A writes to the returned malloc pointer without a preceding null test. Candidate DEFER user-visible crash conclusions.

All evidence and limitations are in artifacts/CRT_MALLOC_RESEARCH.md and evidence/CRT_MALLOC_AGGREGATE.json; original execution probe is preserved in private v33 checkpoint, with digest recorded in report.

## Reconciliation
Extends accepted v31 dual-heap release evidence, not a contradiction. In particular CRT small-block and fallback are alternative allocation routes; real startup configuration remains unknown. The Ghidra low-address model is not Windows exception behavior. All findings concern editor workspace objects, not game engine scene or vehicle objects.

## Publication boundary
This is an immutable research handoff, NOT an agent/promotions record or a manual/reference edit. Documentation steward synthesizes merged runs in a separate fresh-base PR subject to human acceptance.
