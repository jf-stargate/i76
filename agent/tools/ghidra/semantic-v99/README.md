# I76 Ghidra semantic pass v99 (candidate)

**Status:** proposed Ghidra annotation tool, **not** a recovered original source-symbol release or a promoted behavioral reference. **Track:** `i76exe`; interfaces ENG / VEH / TER / RND / GEO. **Date:** 2026-10-31.

## Inputs and scope

- Target: retail `i76.exe`, image base `0x00400000`, `x86:LE:32:default`, MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`.
- Tested Ghidra build: **12.1.4** on the user's corrected `i76_mission_v98_verified_names(1).gzf` (original GZF SHA-256 `d48df73dc331b87c2bae23f4f481be102aa0a77c6baceb01687de8a6e0e57fbd`). The GZF is private and **not** included.
- Repository evidence: latest merged ENG, vehicle, M06 and renderer work on current `main`, including research PRs **#64, #66–#70, #73–#77, #80–#81** and accepted promotions **#62, #78–#79, #83–#84**; relevant curated references `manual/reference/engine/{frame_scheduling,vehicle_construction,m06_visual_terrain,software_renderer}.md`.
- Reconciliation base: `main` `87b24ee244b9b38249d2de0c30e84bb4d2291344`, after #91 was merged. New research after that commit is not automatically incorporated.

## Changes on the verified v98 database

| Class | Verified trial changes | Principle |
| --- | ---: | --- |
| Function parameters | 36 | Rename only decompiler-default `param_N` at a verified original function and ordinal; correct two obviously wrong world-root pointer types |
| Local variables | 9 | Rename only unmodified default stack locals observed in **Ghidra's original decompiler output** for sampler, indexed raster, color cache and bitmap surface constructor |
| User-defined global corrections | 3 | Exact-match obsolete names at `00654380`, `005DD324`, `005DD2EC`; preserve other analyst names |
| New global labels | 3 | Source-verified shade table, signed RGB difference table, polygon work arena base |
| 4-byte global scalar types | 5 | Float/int at exact original-source addresses, only if the whole footprint was previously undefined |
| Terrain sampler return | 1 | Change erroneous `uint` to **float returned via x87 ST0**, rather than Ghidra's *float10* which spuriously synthesizes a return-storage parameter |
| Partial structure types | 8 | Define documented field offsets; **unknown bytes remain undefined**; do not automatically impose on arbitrary instances |
| Safe mapped data | 2 | Install actual camera `0x1D8` structure at `004C2730` and byte[65536] shade-table array at `0061B2A0` **only if each entire region contains undefined data and no interior analyst labels** |
| Additive evidence comments | 18 | Add repeatable comments to previously uncommented anchors; never overwrite an existing comment |
| **Total** | **85** | **Zero execution errors; all changes transactional** |

A pre-existing comment at `006543AC` is preserved, counted as **one skip**. The Ghidra **function count stays 2,102**; no speculative functions are created. Three new primary data labels bring the user-defined label count from 397 to 400. Original parameter/local *counts* remain unchanged (3,656 / 8,299).

### Important semantic corrections

- `00654380`: **adaptive terrain edge/leaf cursor**, not the general renderer polygon-record cursor (`006543C0`).
- `005DD324`: shared terrain/vehicle scratch allocation base in the bounded unified experiment; `005DD2EC` is an *alias* into the associated source-vertex buffer, not an independent backing allocation. A historical secondary alias may remain at `005DD2EC` to avoid deleting user-authored symbols.
- `00493550`: bilinear terrain *height*, returning a numeric value via x87. `004931C0` produces the surface normal; neither is an object-bounds transform. Do not confuse packed height low12 with packed material bits 15–13; bit 12 remains unknown.
- `0047CB00`: **first argument is the 96-byte draw command, second is the 13-DWORD software surface**. This ordering was checked against its decompiled field reads; it differs from plausible but incorrect naming based on the prior function prototype alone.
- `004C2730`: original `472`-byte camera view (`+0x108` near, `+0x138` far), distinct from the queue depth bounds `006543AC/006543A4`.
- `0061B2A0`: original shade table has **65,536 indexed entries**. Only one color column has been executed in accepted original-code evidence; the type does **not** certify full palette selection or authentic pixel color.

## Execution

Open the **corrected v98** program in Ghidra 12.1.4, add `I76_SemanticPass_v99.java` to Script Manager, run once with `APPLY=false`, and inspect the detailed console summary. Back up the program/GZF, change `private static final boolean APPLY = false;` to `true`, run on a **working copy**, then save and export a new GZF. The script independently guards executable SHA-256, MD5, architecture and image base. It does **not** hash the GZF itself: the SHA above documents the verified test baseline, not a mandatory filename/hash gate.

The script refuses conflicting preexisting function parameters, analyst stack locals, program comments and global types; it does not clear or replace existing class-descriptor pointer data at `004F777C`. The two mapped regions were separately checked for defined content, instruction overlap and interior symbols before applying; in the tested baseline they contained only undefined data. Always inspect the dry-run plan on any further GZF revision.

## Validation

- Imported and audited the user's corrected v98 GZF with Ghidra 12.1.4, retaining a separate disposable working project; original uploaded GZF was **never modified**.
- Ran a dry run on v98 (85 proposed, one preserved comment, zero errors).
- Applied to a cloned Ghidra program: **85 changes**, one intentional skip, zero errors, all committed successfully.
- Reopened the trial project and reapplied: **zero additional changes**, 85 already correct, one skip, zero errors.
- Confirmed camera occupies 472 bytes and shade table occupies 65,536 bytes in the resulting Ghidra listing; eight user-defined partial structures register.
- Audited function signatures/locals after application and reviewed decompiled output, including the return ABI and pixel-writer argument ordering.
- Independently compared before/after symbol table: no functions deleted/created; only expected new/guarded global labels and parameter/signature changes. See `v99_symbol_diff.tsv`.

## Deliberately deferred

Do not invent assignments for the unresolved `0045F0F0` release-versus-resolver interpretation without a fresh direct-call audit; the old label is preserved. Do not infer exact textures, authentic color rendering, unexecuted terrain polygon draw, full selected-player frame, or other class/destruction semantics from bounded emulator work. Camera frustum plane bytes, raster flags, output buffers, world runtime internals and unproven stack variables intentionally remain raw or nameless. There is **no** general bulk renaming of all 2,102 functions or automatic promotion of research aliases to original names.

This is a reusable shared-tool **PR candidate** under `agent/tools/ghidra/`; it must be reviewed and merged only by the maintainer under repository policy.
