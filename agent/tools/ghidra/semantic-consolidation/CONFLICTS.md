# Conflicts and unresolved interpretations

## Retained spacing-type conflict

At `006442C0`, accepted v99 installs `int` based on a grid-step interpretation; Pilot A follows original floating stores and consumers and proposes `float`. The actual staged baseline contains that v99 `int`. The new pass reports **CONFLICT**, preserves it, and continues independent safe actions. There are two inventory records for this one issue (pilot candidate and executable operation). It is not two incompatible globals. No arbitrary analyst-defined int is silently rewritten. A follow-up can justify the exact known migration correction and review all users; this release does not claim spacing typing is solved.

## Normal output and EAX return: resolved at integration scope

Pilot A proposed `void(TER_Normal3f*,double,double)`. Original fallback `00493210` and normal exit `00493516` load the explicit output argument into EAX; neither epilogue changes EAX. Original caller `00440B8E` calls and `00440B93` reads `[EAX]` (also `00440B95` performs caller cleanup). This is an output-alias return used by callers. The guarded signature returns **TER_Normal3f*** in **EAX:4**, with explicit stack offsets **+4,+8,+16**, and no hidden pointer or eight-byte alignment gap. Source declaration is unavailable. This is a narrowly supported ABI correction to a merged proposal, not a rewrite of its immutable evidence.

The script uses explicit return storage as well as explicit argument storage. Ghidra custom-storage signatures otherwise leave a newly supplied return unassigned; the validation rejects that state. The final independent capture verifies assigned EAX and all three inputs. Old plate comments are retained with additive corrections.

## Height presentation and arithmetic limits

v99 `float` and Pilot A `double` both select numeric x87 ST0. Neither proves a final-width store or recovered declaration. Retain the recognized v99 float instead of changing a legitimate presentation for shorter output. No hidden result pointer. RC-down FISTP and float X-row stores before RC restore remain qualifications; Ghidra ROUND and world-to-float casts are not literal instruction semantics. Material rounding, bilinear height and triangle-normal selection stay distinct. Bit12, negative page-index exposure and normal branch intent remain unresolved.

## VM phase and local/persistent boundaries

Import and relocation are unchanged, including scalar entry index at +10A8 before relocation. Do not type their inputs/outputs as live VmNode pointers. Operand and host workspace elements remain uint32 words, not universal pointers. Call envelopes describe caller-supplied words; trailing purposes remain unknown. `0040A320` now exposes `in_stack_00000004` at its scheduler call; its own unresolved formal is not forced. Return-time comparison can still cast a temporary to VmNode solely to compare it with node base; no frame-slot node relationship is inferred. Host dispatch is synchronous; no recursive VM or runtime safety claim follows.

## RES types, ownership and misleading aliases

Each of LoadedFile32, PixMember32, PakRetention32, RegisteredKey32 and MountedSource32 is individually **DEFER** for database mapping, with independent C size/offset assertions retained through Pilot C's header. Five byte-pointer/source-row return prototypes are individually **DEFER** for propagation: EAX width alone does not settle distant inferred types/aliases. Only nine default parameter names are changed. The existing bool membership return remains intact.

Acquire returns retained bytes through conditional PIX-first versus loaded-file-first order. Size and name-release use separate PIX-first precedence. A key-table hit is not loadability; a selected source row is not a registered-key row; GEO/TMT owner caches are separate. Historical count/invalidation names remain analyst symbols; added comments identify record count and eviction behavior. Collision consequences, invalidation with active references, filename termination, source modes/media callbacks and allocated-ZFS ownership remain open. No universal handle or full teardown contract is introduced.

## Reporter reconciliation

The authenticated retail `0042D5D0` is one RET, confirming Pilot B and narrowing Pilot C's reporter uncertainty for this exact PE. A returning reporter does not make failure paths safe: PAK backing-load continuation may add an offset to zero. No general configuration, alternate hook behavior, malformed-input reachability or runtime safety contract is inferred.

## Remaining caller readability costs

Grid typing changes Ghidra-generated labels at `004ED7EC` in callers `00425130` and `00425EF0` to a verbose pointer-into-grid name. The original pointer bytes fall within the actual 16,384-entry grid; this is a derived label, not a newly invented owning object. Nevertheless, these are **two cosmetic readability regressions**, not improvements. The required four class-dispatch controls remain unchanged. Stabilizing useful analysis aliases needs analyst review; no new USER_DEFINED alias is manufactured merely to improve the metric.

Normal output typing can coalesce reused local three-float storage outside the call's lifetime. The x/y/z names denote layout, not proof those temporaries always represent normals. No new array-of-short-prefix reinterpretation was observed; no class_runtime propagation is permitted. These limits prevent claiming globally regression-free C or export-ready original source.
