# Interstate '76 — Ghidra v102 class dispatch and runtime semantics

**Purpose:** improve human-readable C pseudocode for eventual manual reconstruction. This is a guarded, evidence-scoped annotation tool for the retail `i76.exe`, **not recovered developer source names, a complete engine reconstruction, or a promoted new behavioral claim**.

**Provenance:** retail PE MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`, Ghidra 12.1.4, 32-bit x86, base `0x00400000`. Validated in a disposable Ghidra project derived from the user's **corrected private v98 GZF**, with v99, v100, and v101 migration scripts applied. No newer locally exported v101 GZF was supplied; the user's latest personal edits remain unverified.

**Research basis:** original Ghidra data and decompiled/x86 access patterns; accepted ENG #58/#62 and selected-init #64; curated `manual/reference/engine/{frame_scheduling,vehicle_construction}.md`; merged original-world-object discovery #95 (`manual/roadmap/subsystems/OBJ.md`). Later OBJ index is a discovery/reconciliation guide and not independently executable proof. Main at proposal creation: record exact commit in PR. This pass does not assert complete pending dispatch, validated destruction ordering, a full selected game frame, or an original-source C++ vtable.

## Improvements

- Typed the full **27 × 0x34 = 0x57C** original class descriptor array at `004F76E0..004F7C5B` (ending just before the `clasfn` string), with `class_id`, `runtime_factory`, `initialize`, `pre_update`, `post_update`, and `damage` members. The remaining pointer columns are explicitly opaque slots. Static values confirm **113 nonzero in-range targets**; they are *addresses in the original code region*, not a claim that all are separate defined functions.
- Restored three distinct callback prototypes: zero-argument factory returning an opaque pointer, world-node phase callback with ignored return, and damage callback returning a 32-bit result with a world-node and two intentionally opaque arguments. The exact `004F7784/88/8C` class-1 init/pre/post pointers and `004F77A4` class-1 damage pointer are checked before any table update.
- Added class-specific **observed prefixes** in the Ghidra type library, not installed on polymorphic `world_node->class_runtime`: class 31 animation context at +0, class 34 animation +8/root +0x78/self +0x7C, and class 0x20/0x21 local effect state +4/self +8/selector +0xC. Each type's length is only the minimum observed extent, **not a verified original allocation size**.
- Retyped the world-node argument to five verified class/damage routines: `00462040`, `00463A80`, `0046F2B0`, `0045F810`, `0046DFE0`; renamed class parameter at `00461970`.
- Named and typed `0054B20C` pending-node count and `0054B210` enrolled-class-node count, based on original original increment/decrement callsites. The two class lists remain distinct from the active world registry.

### Why map the entire descriptor table?

In v101, Ghidra showed `puVar4 = &g_world_object_class_callback_table; puVar4 += 0xD`, and anonymous `(&DAT_004f76ec)[i * 0xD]` calls. A disposable trial proved that a typed 27-row array produces `descriptor->class_id` and `g_world_object_class_callback_table[i].pre_update(world_node)` instead. Retyping is guarded: it verifies the PE digest, exact class-1 slot bytes, 27 × 52-byte original records, source pointer census, absence of conflicting labels or non-scalar defined data, and absence of instructions. It preserves **both user labels** (`004F76E0`, `004F777C`) and **three existing analyst comments**. After replacing data, it verifies the labels and ensures outgoing references are not reduced; failures roll back the entire Ghidra transaction.

No engine instructions, function boundaries, or function bodies are changed. Only selected signatures, labels/types and data definitions change. The source pointer references increased from 42 existing typed pointer references to 113 distinct nonzero pointer fields after array typing; this is a *reference recovery* measure, not evidence of runtime execution.

## Validation summary

| Test | Result |
|---|---|
| Dry run on exact v101-equivalent disposable Ghidra database | `changed=16 already=0 skipped=0 errors=0` |
| Apply | `changed=16 already=0 skipped=0 errors=0 committed=true` |
| Same-project repeat apply | `changed=0 already=16 skipped=0 errors=0` |
| Defined functions | 2,102 before / 2,102 after |
| Typed descriptor array | 27 × 0x34 = 1,404 bytes |
| Original nonzero callback/reference address values | 113; unchanged bytes |
| Existing labels/comments | 2 labels, 3 comments preserved |
| Decompiler sample | 9 of 10 functions changed; 32 measured named field occurrences after (sample only) |
| Portable C layout smoke test | C11 `-Wall -Wextra -Werror -pedantic` passed |

Representative pseudocode improvement:

```c
/* Before */
(*(code *)(&DAT_004f76ec)[iVar3 * 0xd])(world_node);

/* After */
(*g_world_object_class_callback_table[iVar3].pre_update)(world_node);
```

Other improvements include `->initialize`, `->post_update`, `->damage`, `->class_id`, `world_node->class_runtime`, and the named class-list counters. Detailed metrics are in `readability_metrics.tsv`. Raw decompiler dumps are deliberately not committed.

## Applying the script

1. Begin from a **backed-up copy of the v101-applied Ghidra program**. If you have new local changes, examine all `PRESERVE` messages in the preview.
2. Add `I76_ClassDispatch_v102.java` to Script Manager. Default `private static final boolean APPLY=false` is read-only and prints every proposed operation.
3. Confirm `changed=16 already=0 skipped=0 errors=0` (the precise count may differ if you've already annotated fields). Change `APPLY` to `true`, execute, and confirm `committed=true`, `errors=0`.
4. Re-run the script; expect zero new changes. Inspect `00461970`, `00461B80`, `00461C80`, `00461D50`, `00462040`, `00463A80`, and `0046DFE0` before trusting its impact on your local GZF. Export a **private v102 GZF** after review.

**Safety limitations:** The script replaces a previously scalar/partially typed `.rdata` table with one array representation only if each guard passes; existing user labels/comments are restored, but other plugins or custom Ghidra decorations may require manual confirmation. No automatic conversion of per-class runtime pointers, universal callback ABI beyond verified slots, or assumed allocation lengths. User-authored changes outside the exact baseline cause a conservative skip. v99/v100/v101 must precede v102; the v101 tool PR may still be awaiting manual acceptance on `main`.

## Included files

- `I76_ClassDispatch_v102.java` — Ghidra 12.1.4 idempotent guarded migration, dry-run by default.
- `I76_ClassDispatch_v102.h` — portable C layout sketches with fixed-width 32-bit address slots and unknown fields.
- `header_check.c` — independent C11 layout verification.
- `action_audit.tsv` — exact 16 migration operations and evidence.
- `readability_metrics.tsv` — ten-function decompiler sample, baseline and resulting field-access counts.

No original executable bytes, private game resources, GZF, bulk decompilation, credentials, or new reconstructed implementation are published.
