# Original HZD initialization, failure and teardown

Evidence tier: binary-static, exact retail EXE and v100 imported without analysis into a disposable project. `../evidence/reviewed_instructions.tsv` has627 reviewed instructions with original bytes; `instruction_byte_validation.tsv` compares14 defined function bodies /12,135 bytes with the EXE, zero differences. Full exports stay private. Ghidra aliases are annotations, not original source symbols. In particular 00401510's “load_predefined_localized_m16_texture_set” name/comment is contradicted by its call to **release**00471e50.

## Bounded consumer path

| Original VA | Inputs / operation | Destination, handling and bounds |
|---|---|---|
| 004b8bcb..d2 | WRLD header+0x8e = payload+0x86, 13-byte serialized slot; PUSH and CALL00401540 | No HZD result checked by WRLD |
| 00401546/4b/52/63 | Load dword+word delimiter bytes from004c20d0 to stack | `20 2c 09 0d 0a 00`; not file header |
| 00401561..8e | Null pointer/name-byte test, clear32-bit00504838; acquire0046ffc0 at00401582 | Null/empty/missing returns at004016b1, no dependent load. No error-report call here; old records untouched |
| 00401594..c6 | Resource payload start ESI; imported strpbrk result EBX; clear255 local bytes; compute EBX-ESI; strncpy | No source end/length, null delimiter test, destination bound or explicit terminator |
| 004015c9..fa | EBP=00504840; advance24, scan local C string and copy including NUL | Sixteen slots until advanced pointer==005049c0; unbounded name copy |
| 004015fc..00401637 | Start prior delimiter+1; scan signed source bytes through CRT table or _isctype, mask0x103 | No NUL/EOF/end test; predicate depends on CRT state, not a file field |
| 00401639..6e | Next strpbrk, clear255 bytes, difference-length strncpy; loop | Same unchecked behavior as first copy |
| 00401673..80 | Release HZD by original logical name through0046fd40 | After all16 names copied, before first texture load; resource bytes are not retained in records |
| 00401683..a5 | Pair pointer starts00504850; name=pair-16; call00471c10 at0040168f; increment24 | Stop at005049d0; exactly16 calls only if all earlier calls nonzero |
| 00401697/99; bc..de | If texture result0, format diagnostic and call0042d5d0 | Reporter is RET, but **explicit epilogue returns** after it. Horizon remains disabled; prior pairs retained; later pairs not loaded |
| 004016a7 | Store32-bit1 to00504838 | Only after16 nonzero results; no return-value aggregation beyond gate |

Runtime record i is at `00504840+24*i`: `+0..15` name storage inferred from pair boundary, `+16` four-byte primary pointer, `+20` four-byte optional M16 pointer. Final name base005049a8, pair005049b8. End of table005049c0 is a separate render counter, not a seventeenth record. All name copies precede all acquisitions. There is no count/signature/version/parameter parse.

## Texture ownership boundary

00471c10 takes `(pair*, logical_name*)`. At00471c29 it clears pair+4, calls004474b0 at00471c30 and stores primary at00471c38. If the primary resolver returns null, this helper returns0; otherwise high-color predicate00495060 (005dd2a8==1) controls companion loading. Non-high-color returns1. It copies the name, removes the **last** dot suffix (00471c89/96), adds `.m16`, size-queries0046fee0 at00471cc8, then acquires0046ffc0 at00471cdd if size nonzero. Missing size/acquire leaves optional null and returns1. Optional success returns2. HZD accepts **both1 and2**; it requires primary success for every attempted slot, not all M16 companions.

004474b0 derives `.vqm` by truncating at the **first** dot. It first reuses an existing decoded-texture cache record and increments its16-bit reference (004475da). Otherwise global00609564 controls trying the literal primary name before VQM. VQM-size query/acquire and embedded codebook-name acquire occur at00447609/2b/3d. Its VQM decode result is a separate allocated image; source VQM/CBK references are released after decode (0044784a/57). If no decoded VQM candidate is used, fallback literal-name acquire is00447889. Resource preference and decoding state live outside HZD.

Generic acquire0046ffc0 may return retained loaded-file payload or a slice of retained whole PAK;0046fee0 and0046fd40 choose their own PIX-first paths. See accepted `manual/reference/engine/resource_acquisition.md` for collision/lifetime asymmetry. Do not infer a uniform pointer-free API or success from an inventory hit. FULLRES.LST can be acquired at00471d11 and released00471daf to construct global hash flags; it is not serialized in HZD. The pipeline mutates primary image flags as well as optional M16 header flags; “read-only reader” describes this run's independent parser, not the retail loader.

A further failure boundary is visible in004474b0: after literal fallback, the high-color branch calls00471840 at0044789e with EBP even if acquisition returned null; there is no null test before that call.00471840 reads and writes `[primary+4]` at00471950/69 without a null guard. Thus a missing primary in this branch can fault before00471c10 or HZD gets a zero result. The diagnostic-and-return path above describes a returned failure, not every missing-asset outcome.00471840 also acquires FULLRES.LST at0047185a and releases it at004718f8 when building the same global bitset; built-in list use is not restricted to optional M16 loading. No native fault was induced.

## Teardown and repeat limitations

00401510 iterates pair00504850..005049d0 step24, passing name=pair-16 to00471e50 at0040151b. It then clears vertex count00503034 and enabled00504838 at00401531/36. Top-level teardown calls this routine at004045c3. This is release, despite its inherited load alias.

00471e50 tests primary at00471e59. If nonzero,00471e67 calls00447b20 by name, then clears primary at00471e6c. If optional is nonzero, it derives `.m16`, releases by name at00471ee5 and clears optional at00471eed. If primary is zero, it returns without inspecting/clearing optional.00447b20 decrements cached VQM reference / queues unused records; without a decoded cache hit it releases the literal resource by0046fd40. Duplicate slots therefore represent repeated acquisitions/releases, even when payload pointers alias.

Normal intact pairs become zero; a second teardown skips them. This establishes a local conditional repeat behavior, **not** proof of whole-engine safe repeated lifecycle. No cleanup occurs at entry to00401540. Reinitializing successfully overwrites live pairs without releasing old references; null/empty/missing HZD only disables, retaining old table state. Partial failure does not unwind prior acquired pairs. Reinitializing with changed names overwrites all names before loading; untouched old pairs can then be associated with new names during teardown. A safe caller must not rely on this as a transactional replacement contract.

Normal parsing releases HZD once before loads, including later texture failure. Failed acquisition creates no local HZD lease. Malformed scanning may never reach the release and has no observed recovery path. No explicit exception guard or rollback exists in the audited function. Do not say “released on all paths” without this qualification. WRLD ignores the void initializer's state/failures.

## Small rendering boundary audit

004016e0 tests configuration byte00654b8f and enabled00504838 before horizon submission.00401970 writes incrementing global005049cc into an output index at00401ae9..afb, resetting its sequencing state at00401981..8b when exhausted;004018f3..00401902 computes `00504850+24*index`.00471f00 selects pair+4 only when nonzero, context nonnull and `[context+0x3c]+8==1`; otherwise pair+0.00401905/23 passes that selected pointer into the two polygon submission paths. There is no per-record HZD geometry/UV field.

The helper's geometry generation, index safety for all runtime states, exact angular order, UV constants, blending flags, palette conversion and visual correctness are not completed here. Slot order is retained; do not assign compass labels or interpret the duplicate half as guaranteed wrap behavior from filenames alone. The static selector proves a downstream interface, not a faithful rendered horizon.
