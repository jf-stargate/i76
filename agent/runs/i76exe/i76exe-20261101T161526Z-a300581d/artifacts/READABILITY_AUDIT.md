# Ghidra readability audit

Ghidra 12.1.4, Java 27-ea, original v97 GZF freshly imported with `-noanalysis` into a disposable project. Private baseline SHA-256 is in the manifest. Existing function names/comments were retained. No shared project, v102 class-dispatch table, global data definition, original instruction, or accepted snapshot was modified.

The final script checks x86 little-endian 32-bit architecture, executable metadata MD5, the supplied original PE SHA-256, and **all 2,489 instructions** across six functions against PE section-mapped bytes before mutation. Additional allocation/budget fingerprints guard semantic anchors. It defaults to no mutation unless the second argument is exactly APPLY. Use DRY on a fresh import for inspection. It adds `/PilotB/VmToken` and `/PilotB/VmNode`, four live-node/head/count parameter annotations, and three explicit call envelopes. Mutations use one transaction, rolled back on annotation error. It rejects an existing PilotB node type instead of overwriting an analyst's work; it is intentionally not an idempotent migration. Before/after source is exported privately. The script is a tested disposable-project proposal, not a baseline release.

## Fixed-sample comparison

`evidence/READABILITY_METRICS.tsv` records full private decompilation digests, UTF-8 byte counts, formal parameter counts and a deliberately narrow textual field-access count. Six of six functions decompiled before and after. Four changed in the final scoped experiment; allocation and initialization remained byte-identical as decompiled text.

| Function | Before bytes | After bytes | Before/after formals | After selected named-field mentions |
|---|---:|---:|---|---:|
| 00410490 allocator/import | 2268 | 2268 | 3 / 3 | 0 |
| 00412500 relocation | 1419 | 1419 | 4 / 4 | 0 |
| 00414670 interpreter | 4461 | 3824 | 10 / 12 | 54 |
| 004149F0 scheduler | 2536 | 2684 | 15 / 16 | 6 |
| 0040A320 runtime gate | 5288 | 5361 | 0 / 0 | 0 |
| 00412CE0 host bridge | 33463 | 32727 | 10 / 12 | 3 |

Named-field count matches only `->ip`, `->operand_cursor`, `->next`, `->frame`, `->host_cursor`. It is not a semantic score. Scheduler text grows because the recovered call envelope reveals the ordinal and extra arguments; that growth improves ABI visibility.

Representative **short** private-decompiler excerpts (not complete output):

```c
/* interpreter before */
**(int **)(param_1 + 0x10b4) = *(int *)(param_1 + 0x10ac) + puVar4[1] * 4;
/* interpreter after */
*node->host_cursor = (uint)(node->frame + pVVar1->payload);
```

```c
/* scheduler before */
*param_11 = *(int *)((int)pvVar1 + 0x10b8);
/* scheduler after */
*head = pVVar1->next;
```

The interpreter now visibly distinguishes operand writes from host-argument writes, token payload remains an unsigned scalar, and `token_base + payload` scales by an eight-byte token rather than an inferred node. Frame points to raw 32-bit words. No array of pointer-to-word elements is imposed on either mixed workspace. `pending_count` remains pointer-to-int, not node-pointer.

## Rejected propagation and remaining artifacts

An earlier disposable trial also typed the allocator output and initializer's first argument. It displayed the **pre-relocation scalar entry index** as a `VmToken*` read in the allocator and required casting that pointer back to integer in relocation. This is an incorrect lifetime interpretation. Those two annotations were removed from the final script. Their code now remains unchanged, while the C architecture explicitly models the index-to-address phase transition. This is a concrete reason not to propagate a live-node pointer indiscriminately through the loader.

Ghidra still sometimes casts the return-time operand address to `VmNode*` because it compares that address against the node base. This temporary is a comparison artifact; it does not establish that frame slots contain nodes. The C sketch uses Addr32 arithmetic and the exact equality to avoid that misleading inference. The 80-byte local scratch is split into small locals by Ghidra. Exposing the trailing host argument makes its address visible but does not establish any semantic consumer. Function 0040A320 still has no formal despite forwarding `[EBP+8]`; its intended caller contract was not forced here.

The final source architecture therefore remains the readable semantic artifact. Typing improves inspection of the original program without rewriting the interpreter or treating every cast as recovered original source.

## Reproduce and assess

Follow `REPRODUCE.md`. Preserve full source privately and compare its digests with the metrics. `scripts/verify_evidence.py` independently compares both phases with the original PE and accepted instruction listings. A previous broader trial was re-imported and reproduced successfully, then final phase scoping was tested in another fresh import. Only final scoped metrics are reported as the final result. No compatibility claim is made for privately edited v98+ programs or for the open v102 proposal.
