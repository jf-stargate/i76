# Retail i76.exe mission actor identity registry — original-instruction execution

**Scope:** original retail `i76.exe` (MD5 `a640ea0097dbb62e0c77b7f2847c7161`; SHA256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`). Annotated Ghidra 12.1.4 program `i76_mission_v97_verified_names` from private GZF SHA256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`.

**Predecessors:** `ref/mission_execution/research_checkpoints/v96/`, `v97/`, `ref/mission_execution/ORIGINAL_CODE_MISSION_LOADER_EMULATION_V06.md`, and the separately merged `agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/` (different vehicle-resource focus). The previous local *unpublished* `i76_mission_actor_registry_checkpoint_v0.1.0` contributed the independent ODEF stock-file census.

## Newly executed original instructions

Using Ghidra's `EmulatorHelper` with **the original PE instructions** and preserved registry memory within the first scenario, executed these unmodified functions:

- `004AD410` initializes registry context `0054A178`; 32-KiB buffer, 2048 slots, zero count.
- `00457610 → 004AD450` appends paired-key records; first and duplicate registration each increment count and store the supplied world pointer.
- `00457630 → 004AD5B0` searches backward; duplicate key returns the **latest inserted** world pointer. Cold and nonmatching lookup return zero.
- Duplicate registration with synthetic side-effect suppression off reaches **original** `0042D5D0`, which is a one-byte RET, then still appends; with synthetic suppression on, duplicate is appended without entering the reporter.
- `00412400` actor-binding with a missing key stores zero at actor `+0x58` and enters the original no-op reporter, **without calling** reference acquisition. Two actor rows sharing a key and a matching label both store the same pointer and each independently reach `0045ED00` (modeled ownership boundary). With different labels, the original comparison and reporter execute twice, but binding still succeeds. `taurus` stores its resolved pointer in the original global `0051F5C4` through `0040AEB0`.
- `004AD600` calls modeled HeapFree/HeapDestroy, then original instructions clear buffer, count and capacity.
- At synthetic count=capacity=2048, non-null modeled `HeapReAlloc` makes **original** `004AD450` return `0`, with no append and unchanged count/buffer. A null modeled `HeapReAlloc` makes original code set `entries=NULL`, grow capacity to 2304, and compute the next backing write to address `0x00008000`. The harness deliberately **stops before that original write**, so no invalid-memory access or retail crash is claimed.

**Executed checks:** 38 trace-logged original-code scenario assertions passed; further independent trace checks are in `scripts/verify_registry_trace.py`. Native emulation proceeded from local GZF with `-readOnly -noanalysis` and validated original executable identity. These are not full-game Windows mission loads.

## Stock-data cross-check

The provided stock archive contains 80 missions (40 each in `miss8` and `miss16`). Each ODEF has the fixed-length identity `ODEF.length = 28 + 108 * number_of_OBJ_records`. Across all 80 missions this yields 5,564 serialized OBJ records (2,782 per variant), with minimum 13 and maximum 169 per mission (T15). Paired variant counts match for all 40 names. `evidence/odef_counts.tsv` and `evidence/odef_summary.json` are counts/digests only, and `scripts/audit_odef_capacity.py` can reconstruct them from an authorized, locally held original game archive.

**Do not equate these counts with registered world-object keys.** Per-OBJ insertion multiplicity, preloaded/dynamically registered world objects, mission replacement and live registry occupancy have not been executed. The 2048-record synthetic threshold is a control-flow test, *not* observed stock mission reachability.

## Modeled boundaries, not validated retail services

- `HeapCreate`, `HeapAlloc`, `_msize`, `HeapReAlloc`, `HeapFree`, `HeapDestroy`: simulated x86 stdcall returning deterministic allocated buffers or controlled success/failure.
- `_strncpy`, `_stricmp`: narrow deterministic cdecl substitutes; the original engine's paired-key comparison and actor-label comparison **are** executed.
- `00452D20` global side-effect suppression predicate: explicitly substituted with 0 or 1; native caller conditional branches execute.
- `0045ED00` tree-ownership reference acquisition: **intercepted and counted, not executed**; actual refcount increments, world teardown and lifetime not validated. The object's synthetic pointers are identities only, not constructed vehicle/world objects.
- `0042D5D0` reporter and `0040AEB0` taurus setter: original instructions executed.

No Windows gameplay, real ODEF objects, full original loading or heap management are claimed. No modified original binary, GZF, mission resources or private game bytes are committed.

## Call/data chronology

`00457100 → 004AD410`: registry preparation (higher-level initializer not executed in this run).

`004B7AC0 → 004572B0 → 00457610 → 004AD450`: expected ODEF/world producer path (only final native append wrapper executed).

`00409740 → 004125C0 → 00412400 → 00457630 → 004AD5B0`: FSM script importer/finalizer actor consumer (only `00412400` onward executed); successful lookup reaches 0045ED00 and missing lookup leaves `+0x58` zero.

`004571A0 → 004AD600`: expected mission teardown (only final native registry destroy routine executed).

The contiguous `004AD410–004AD638` function group remains a **plausible original translation-unit neighborhood**, not a recovered filename or source implementation.

## Next experiment

Extend from isolated registry/actor paths into original `004B7AC0` ODEF object construction and `004572B0` world registration, measuring actual append count per ODEF record; thereafter replace the `0045ED00` substitute with original reference-tree code, inspecting unregister callback side effects and a same-session reset/reload. Keep OS/CRT substitutes auditable and the retail GZF read-only. Test invalid/stale identities only within disposable synthetic memory.
