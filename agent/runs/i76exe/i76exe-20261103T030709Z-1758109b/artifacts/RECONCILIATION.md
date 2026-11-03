# Exact v99 → integrated v100–v102 reconciliation

Evidence tier: binary-static and disposable Ghidra annotation experiments. Base `430ef59c8396db9880cd95e6f6ba9d1bd81e9c20`, protocol **1.0.4**. GitHub main independently authenticated; no open PRs at bootstrap. Active ruleset 25664125 requires PR + integrity, zero formal reviews, no bypass; human merge only. Accepted #106/#107/#108 reviewed at this pinned base.

Selected input `i76_mission_v99_verified_names.gzf`: **6,500,304 bytes**, SHA-256 **ca211238170806eda27a2b4ecf6aee2192abb69df27fe56f106b455ac75bc710**. Retail PE SHA-256 **bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3**, MD5 **a640ea0097dbb62e0c77b7f2847c7161**. Private paths are recorded locally in `session.json`; no GZF/PE is distributed. User-export search found v99 newest among identified `scratch_data` exports; no newer named user export was substituted. Older generic i76.exe.gzf SHA-256 `d48e0bc5194fcb7d4c74c3c9af3b502b495ec9a4d683374a745098f6bee76c03`, 6,432,616 bytes, predates v99. Research-generated v97 copies are not newer user baselines.

Initial observations match accepted run `i76exe-20261103T011951Z-e8b8ea6e`: **2,102 defined + 235 external functions**, **387 type entries**, all original defined body hashes verified independently against PE sections. Complete private symbols, signatures/storage, comments, type components, data, external functions, references, instructions and fixed **419-function** C sample captured before mutation.

| History | Original ALREADY | APPLY | PRESERVE | CONFLICT | DEFER |
|---|---:|---:|---:|---:|---:|
| v100 | 0 | 11 | 0 | 0 | 3 |
| v101 | 0 | 25 | 0 | 0 | 1 |
| v102 | 0 | 16 | 0 | 0 | 0 |
| Total historical | 0 | 52 | 0 | 0 | 4 |
| Accepted terrain correction, separate | 0 | 2 | 0 | 0 | 0 |

[evidence/operations.tsv](../evidence/operations.tsv) retains all 56 historical identities, exact target addresses, observed signatures and dispositions. APPLY means applied in the accepted disposable candidate, never the live database. After integration, repeat reports **54 ALREADY, 4 DEFER** including terrain. Historical v100 slot edits are then subsumed by the v102 array, not silently deleted from provenance.

## Execution and reconciliation

1. Imported exact v99 into a new Ghidra 12.1.4 project without analysis; captured complete evidence and independently PE-verified all 2,102 bodies.
2. Accepted unmodified PR #107 terrain script previewed **2**, applied **2**, repeated **0**; full before/preview and after/repeat equality. Corrections are float `006442C0` and terminated aud literal `004ED7EC`. Normal EAX/packed-stack and height ST0 signatures retained.
3. Historical v100 trial applied 14 to its own project. Broad caller capture revealed regressions; retained that rejected trial privately. Fresh input replay applied only **11**, deferred three.
4. V101 preview/trial applied 26. Review found index/pointer lifetime conflation in `00409980`; fresh replay applied **25**, deferred that parameter. No annotations from a trial were selectively erased to fake final equivalence.
5. V102 preview/apply **16**; complete table byte digest authenticates all **351 DWORD values** (27 IDs + 324 pointer/reserved fields), **113 nonzero callback fields**. Preserved both original labels at `004F76E0` and `004F777C`, all three old comments and all 42 outgoing references, recovered 113 total. Repeat **0**.
6. Final standalone script independently default-previewed/applied/repeated from pristine disposable v99: **54 / 54 / 0**, four deferrals. Full staged/one-shot captures agree exactly. Ten negative cases, independent saved rollback, 55 assertions pass.

New named types: opaque v100 `I76_Class1Callback`, partial `I76_Class1Descriptor_0x34`; v101 `I76_WorldNode_0xB0`, `I76_ClassLinkNode_0x0C`, `I76_ActiveWorldEntry_0x78`; v102 factory/phase/damage callback definitions, complete `I76_ClassDescriptor_0x34`, class31/class34/class32_33 observed runtime prefixes. Existing v99 types are reused, not replaced to satisfy strict Ghidra equivalence. The runtime prefixes are **not** globally installed on `class_runtime`. No universal payload/owner/parent or original C++ vtable is claimed.

`0049C320` return proof: HeapAlloc EAX tested at `0049C331`; zero branch `0049C333→0049C356`; success stores use EAX as address and preserve it through `0049C354`; both return via POP ESI / RET at `0049C356/357`. Callers `00461970`, `0049C260`, `0049C2A0` use returned nodes. This establishes a 0x0C node pointer/NULL at the boundary, correcting v99's displayed void return; it establishes no universal payload ownership.

Production tool is proposed separately at `agent/tools/ghidra/reconcile-v100-v102/I76_Reconcile_v100_v102_20261103.java`. No live GUI database opened; no successor export substituted for the maintainer's original. GUI execution remains outstanding. Findings and code are proposals for human review; no merge/promotion performed.
