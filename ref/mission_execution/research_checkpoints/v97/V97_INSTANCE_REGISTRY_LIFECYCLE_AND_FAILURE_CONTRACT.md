# I76 retail — v97: instance-key registry lifecycle and failure semantics

**Scope:** original retail `i76.exe` (`MD5 a640ea0097dbb62e0c77b7f2847c7161`); native Ghidra 12.1.4 decompilation plus x86 instruction evidence, annotated v96 source program and existing retail mission-corpus checks. Research-only. No executable patch, gameplay execution, or engine reimplementation.

## Summary of new findings

1. **Registry lifetime is mission-scoped.** `00457100` initializes active-world entries, callback lists, auxiliary heaps, and then the instance-key registry using `004AD410`. At `004571A0`, the registry heap is destroyed by `004AD600` **before** object-removal callbacks release active entries. Direct references to context base `0054A178` originate from these two lifecycle functions and the insert/lookup wrappers at `00457610` and `00457630` (four source locations in Ghidra's reference graph). This is bounded evidence and cannot exclude alias-based access.
2. **Registry representation is a 16-byte context:** base `0054A178`: `+0x00` private Win32 heap handle; `+0x04` entries allocation; `+0x08` live appended-record count; `+0x0C` capacity. `004AD410` uses `HeapCreate(0,0,0)`, `HeapAlloc(heap,HEAP_ZERO_MEMORY,0x8000)`, capacity `0x800 = 2048` records of `0x10` bytes, count zero. Records contain key word 0 at `+0x00`, key word 1 at `+0x04`, an unowned world-object pointer at `+0x08`, and an unused/unspecified final word. Existing v96 structural and shipped-file cross-checks corroborate the paired-key interpretation.
3. **Duplicate keys do not stop insertion in this retail build.** `004AD450` scans existing keys when damage-side-effect suppression is false, and calls `0042D5D0` upon a duplicate; it breaks that scan but proceeds to append regardless. In the suppressed mode the duplicate check is skipped. `0042D5D0` (`report_error`) is a *single instruction RET* in the retail executable; it is not a fatal assertion, exception, or diagnostic logger in this binary. The wrapper at `00457610` discards the append routine's return value. Lookup at `004AD5B0` scans records **backward** (newest to oldest), so if duplicate keys are inserted, the last registered object wins. This differs from the FSM's own duplicate-key *label-consistency* check at `00412400`, which checks separately whether equal keys carry different script labels; that error call is also a no-op here.
4. **Missing actor lookup is not a loader rejection.** `004AD5B0` returns zero when a paired key is absent. `00412400` stores zero in the actor binding at `+0x58`, calls the no-op reporter and continues its actor pass; it only acquires a counted world-object reference when the lookup succeeded. `004125C0` proceeds to media checks and VM-node relocation. The `00409740` FSM chunk callback unconditionally returns success after this finalization. Thus a mission with missing actor bindings can pass *these* loader steps but carry null actor references into runtime; whether any given VM command subsequently dereferences one is opcode- and control-flow-dependent.
5. **Instance-registry entries are not individually deleted on world-object unregistration.** The active-world unregister function `00457420` dispatches removal callbacks and retires that registry entry's object reference. The instance-key registry's own exposed operations are initialize, append, reverse lookup, and whole-table destruction; no direct per-key removal or liveness invalidation was found in the audited callers/references. Therefore a record can retain a non-owning pointer after the corresponding active-world entry is removed, until full registry teardown. The normal shipped-load contract resolves FSM actor keys shortly after ODEF loading and before mission execution, mitigating that condition, but an exceptional later registry lookup could see an obsolete pointer. Do not infer ordinary mission exposure without proving such a path.
6. **Potential capacity-growth defect — verified control flow, unproven runtime reachability.** When `count >= capacity`, `004AD450` calls `_msize` then `HeapReAlloc(heap,8,oldBuffer,oldSize+0x1000)`. The original **machine code** at `004AD487–004AD494` tests `EAX` and, when the returned pointer is non-null, returns zero immediately. Conversely, if the pointer is null, the code clears `context+0x04` to zero, increments capacity by `0x100`, and continues to a write at `entries+count*0x10` (`004AD56E–004AD598`). On the non-null branch it neither updates the stored table pointer nor appends. These branches are consistent with an erroneous growth path. The initial 2048-record reserve likely makes this an exceptional case, but the current audit does **not** prove shipped workloads never reach it. Avoid claiming a reproduced crash or byte-for-byte source bug. The ODEF caller ignores insertion's return value.

## Runtime chronology and cross-system ownership

| Moment | Address | Registry/ownership change |
|---|---|---|
| Before world load | `00457100 → 004AD410` | Build context, heap and 2048-record initial allocation; register world callbacks |
| Each registered ODEF object | `004B7AC0 → 004572B0 → 00457610 → 004AD450` | Active world registry acquires counted ownership; instance registry appends a **borrowed** pointer and two key words |
| FSM script fixup | `00409740 → 004125C0 → 00412400 → 00457630 → 004AD5B0` | Newest-key match returned; each successful FSM actor binding separately adds a counted reference |
| Individual object unregister | `00457420` | Calls removal callbacks, clears active-world slot; FSM callback clears actor bindings; **no instance-key row removal demonstrated** |
| Mission teardown | `004571A0 → 004AD600` | Release entire instance-key registry, then dispatch world-object callbacks and release registered objects |

The earlier v83–v88 ownership evidence remains relevant: neither an active-world registry slot nor a mission actor record is the same ownership object as an instance-key registry row. The latter is a non-owning identity index.

## Critical source-backed observations

- `004AD410`: `HeapAlloc(...,8,0x8000)`, `ctx[3]=0x800`, `ctx[2]=0`.
- `004AD450`: `004AD487 TEST EAX,EAX; 004AD489 JZ 004AD495; 004AD48B XOR EAX,EAX; ... 004AD494 RET`. Failure branch: `004AD498 MOV [ESI+4],0`, `004AD49F ADD EAX,0x100`, then `004AD57E MOV [EDX],EBX`. These bytes are included in `v97_assembly.tsv`.
- `004AD5B0`: count-1 reverse traversal, 0x10 record stride, returns record `+8` or zero.
- `0042D5D0`: one-byte RET, included in `v97_detail_decompiled.txt` and `v97_detail_assembly.tsv`.
- `00412400`: `actor+0x58` binding written before the missing-key error stub, and reference acquisition guarded by nonzero result.
- `00409740`: FSM chunk callback returns `1` after table import/finalization.
- v96 shipped-file census: **794** actor-key occurrences across two variants; all matched a contiguous 8-byte sequence in that mission's ODEF chunk. This is a key-byte comparison, **not proof that runtime registration succeeds**. The v96 corpus also documents duplicate actor rows labeled `user` in T16/T17.

## Confidence and outstanding limits

**High:** layout, capacity, reverse-lookup precedence, nonfatal duplicate/missing-key behavior within the audited paths, one-byte error stub, allocator-growth branch directions, mission-scope init/teardown, lack of direct per-entry unregister in the known registry call graph.

**Moderate:** exceptional object removal can make rows stale until cleanup (follows from borrowed-pointer writes and absence of observed deletion, but not an exercised runtime scenario); impact of failed growth (specific failure modes depend on Windows heap behavior and actual load).

**Open:** whether any shipped/runtime mission reaches 2048 cumulative registered keys; whether late loading/replacement can invoke the instance-key lookup after object removal; whether an absent actor used by a particular VM command causes an actual fault; whether other pointers alias registry context without direct xrefs; exact meaning of paired key fields beyond equality and display as eight characters.

**Suggested future behavioral experiments (not implemented):** read-only debugger trace around 2048th registration in a safe disposable environment; duplicated instance key under unsuppressed and suppressed mode; missing actor binding while executing a guarded versus unguarded host command; teardown and replacement with a stale key; paired-key re-registration with a different object pointer.

## Symbol updates

The v97 project introduces five guarded function renames plus `0054A178` → `g_world_object_instance_key_registry`. These are documented in `v97_verified_symbol_change_audit.tsv`. `report_error` was intentionally **not** renamed, since many other functions use this historical annotation, but its one-byte no-op nature is now documented. The updated `.gzf` was exported from a saved, separate Ghidra project and then **freshly imported with 12/12 checks passed**; original v96 GZF and retail executable are unchanged.

## Source-layout hypothesis

The contiguous `004AD410–004AD638` functions (`init`, `append`, `lookup`, `destroy`) make a strong source-subsystem neighborhood and a **moderately supported single translation-unit hypothesis**. The higher-level world-object lifecycle at `00457100–004571A0`, its wrappers at `00457610/30`, and the FSM actor fixup at `00412400` should remain separate source units until evidence warrants combining them. No original filenames are asserted.
