# Interstate '76 — v100 semantic type propagation for human-readable C

**Status:** candidate Ghidra shared tool. **Binary track:** `i76exe`. **Goal:** aid future *manual* C-source reconstruction by improving Ghidra pseudocode without fabricating source-level semantics. These aliases, field names and layout sketches are research-derived, **not recovered original developer names**.

## Exact baseline and sources

- Retail `i76.exe` PE SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`, MD5 `a640ea0097dbb62e0c77b7f2847c7161`; 32-bit x86 image at `00400000`.
- Ghidra **12.1.4**, starting from the user's private corrected v98 GZF `i76_mission_v98_verified_names(1).gzf` (SHA-256 `d48df73dc331b87c2bae23f4f481be102aa0a77c6baceb01687de8a6e0e57fbd`) after *applying* `I76_SemanticPass_v99.java` from [PR #98](https://github.com/jf-stargate/i76/pull/98). The v99 GZF remains private; these tests use an equivalent disposable Ghidra project migrated in the previous session. If the user's local v99 has additional edits, the guarded dry run may have different results.
- Pinned accepted `main` for publication: `71da0efa1ec4c92fa939f499683611a1ae647406` (2026-10-31). The original type research was checked against `87b24ee244b9b38249d2de0c30e84bb4d2291344`; intervening merged #92–#98 are discovery/roadmap and tooling promotions, not new original-instruction proofs of the v100 field offsets. Main technical references: `manual/reference/engine/{frame_scheduling,vehicle_construction,m06_visual_terrain,software_renderer}.md` and accepted/promoted original-instruction findings: #58, #62, #66–#70, #73–#81, #83–#84. Newly merged discovery indexes are navigation aids, not independently promoted original-instruction proof.
- **No original game executable/resource payload or Ghidra database is published here.** No C implementation of original routines is produced.

## Why this pass is different

The earlier v99 pass registered eight partial structures but used them in only two mapped data regions. v100 propagates the **existing verified types** into a small, independently checked set of function arguments and a return type so the *decompiler itself* displays field names rather than pointer arithmetic. It also defines an opaque callback prototype and precisely retypes three class-1 function-pointer slots, without overwriting other pointer data in the descriptor.

### Fourteen proven migration operations

| Kind | Count | Addresses / boundaries |
| --- | ---: | --- |
| Typed function arguments | 8 | Camera: `00490A00`, `004929B0`, `00457FF0`, `0048FAC0`, `00472C10`; software draw: two arguments at `0047CB00`, surface creation `00474C60` |
| Typed return | 1 | `00491810` returns the existing `I76_TerrainAdaptiveLeaf_0x1C *` instead of untyped `short *` |
| New non-invasive types | 2 | `I76_Class1Callback` (opaque receiver) and `I76_Class1Descriptor_0x34` (partial descriptor; **not** a C++ vtable) |
| Exact class-1 pointer slot retyping | 3 | `004F7784 → 00463120`, `004F7788 → 00463800`, `004F778C → 00463950` (the `004639A0` pointer at descriptor +0x30 remains unchanged) |
| **Total** | **14** | Changes guarded by original retail PE identity and current Ghidra state |

The class descriptor has *pre-existing pointer data*, including +0x04, +0x1c...+0x30. Retyping the whole 52-byte region would destroy or replace useful analysis; therefore v100 only applies types to the three exact existing analysis pointers. The separately declared descriptor structure serves as a reference for possible future reconciliation.

## Measured effect on decompilation

In a fixed **12-function sample** with the same decompiler settings, six function C outputs changed and named structure-field accesses increased from **0 to 42**. These are observed textual counts **within this sample**, not project-wide readability metrics:

| Function | Before | After | Named field accesses after |
| --- | --- | --- | ---: |
| `00490A00` terrain root builder | `*(float *)(camera_view + 0x2c)` | `camera_view->fov_tangent` | 7 |
| `004929B0` visible bounds | `*(double *)(camera_view + 0x170)` | `camera_view->source_camera_z` | 8 |
| `00457FF0` visibility producer | untyped camera | typed `I76_CameraView_0x1D8 *` | 11 |
| `0048FAC0` queue consumption | `float *camera_view` | typed camera, e.g. `viewport_context_ptr` | 3 |
| `0047CB00` indexed span writer | `*(float *)(draw_command + 0x58)` | `draw_command->shade_gradient_x` | 11 |
| `00474C60` bitmap surface | `int *surface_descriptor` | `I76_SoftwareSurface_0x34 *` | 2 |

Some other functions in the 12-function sample correctly remain unchanged; the source text is *not* a complete decompiler export. All original executable bytes are untouched.

### Deliberately excluded: unsafe world-root types

A trial that typed `00463120` / `00463800` / `00463950` as pointers to the **partial 0x58-byte world-object prefix** made Ghidra misinterpret a genuine `world_object+0x70` reference as a bogus array access into `world_object[1].orientation_basis`. That would *decrease* C readability and corrupt its inferred types. Those three parameter changes were **removed** entirely. The `I76_Class1Callback` receiver therefore remains an *opaque pointer*. A follow-up must first establish a complete object-header layout, verify the `+0x70` owner and preserve other observed offsets before propagating root types.

Also deferred: typed mixed kind-6/kind-10 work queues (different layouts), speculative UVs, color/palette fidelity, global image-pointer arrays with interior labels, x87 ABI rewrites, and unknown class callback slots.

## How to apply

1. Create a **backup or working copy** of your locally updated v99 program.
2. Add `I76_SemanticTypes_v100.java` to Ghidra 12.1.4 Script Manager. It defaults to **`APPLY = false`** and prints every proposed action without modifying anything.
3. Confirm the identity guard and inspect the proposal summary. On the tested v99, this is `changed=14 already=0 skipped=0 errors=0`.
4. Set `APPLY = true`, run on the **working copy** and confirm `committed=true`, `errors=0`. Repeating should yield `changed=0 already=14`.
5. Review at least `00490A00`, `004929B0`, `00457FF0`, `0047CB00`, `00474C60`, plus class-1 pointers. Save the program and export a v100 GZF if you want an independently verifiable baseline.

If a name, type, argument ordinal or known callback slot differs, the script conservatively skips that modification; **do not force it** without inspecting the underlying instructions. The migration does not undo analyst changes in unrelated functions or change local variables.

## C layout reference and checks

`I76_Readability_v100.h` is a **portable layout sketch**, not a real retail-ABI header. It uses fixed 32-bit `I76Addr32` fields for original pointer slots, intentionally enabling structural checks on a 64-bit workstation. It sketches exact known offsets and leaves unknown bytes explicit. Field meanings are limited to cited original-instruction evidence.

Run `cc -std=c11 -Wall -Wextra -Werror -pedantic -c header_check.c`. The compile-time size/offset assertions passed in the validation environment. They prove C packing arithmetic only, **not** original behavior or host-native binary interoperability.

## Validation scope

- Disposable, fully v99-migrated Ghidra 12.1.4 database: **dry run 14 / applied 14 / repeat 0**, all zero errors.
- After v100: **2,102** defined functions, **3,656** parameters, **8,299** locals, **400** user-defined labels; all unchanged from the audited v99 baseline.
- Address/name/symbol set unchanged: **0 added/deleted symbol-table entries**. Exactly eight function signatures changed (seven functions whose parameters changed, plus one leaf-return function; `0047CB00` has two typed parameters).
- Original class-1 bytes are preserved; three callback pointer data types change from `undefined *` to `I76_Class1Callback *`; other descriptor pointers remain untouched.
- `action_audit.tsv`: proposed/applied actions with source linkage. `readability_metrics.tsv`: only the measured 12-function decompiler sample. Private decompiler dumps and GZF **are not committed**.

This is a **shared tooling proposal** requiring explicit maintainer review. It should not be automatically merged and does not promote any unreviewed claims into `manual/reference/`.
