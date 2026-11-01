# I76 Ghidra v101 — world-object and class-dispatch C readability

**Scope:** `i76exe` / ENG + OBJ + VEH + FSM. **Status:** candidate shared Ghidra tool for **human-readable C reconstruction**, not recovered original source names or a promoted new behavioral finding. Default `APPLY=false` and transaction-guarded. No original binaries or private GZF published.

## Target and evidence

- Retail `i76.exe` MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`, 32-bit x86, base `00400000`.
- Baseline: a **disposable Ghidra 12.1.4 project** derived from the user's verified v98 export, with successful v99 and v100 migrations already applied. The user's **own latest locally exported v100 GZF was not supplied**; actual user-side results must be confirmed with dry-run and a new export. The test database and original inputs were not changed.
- Anchors: `manual/reference/engine/{vehicle_construction,frame_scheduling}.md`, `manual/roadmap/subsystems/OBJ.md` (merged #95; discovery/reconciliation, not new executable proof), accepted M-ENG-01 (#58/#62), original vehicle construction, and direct original x86/decompiler inspection of `0045EBD0`, `0045F0F0`, `0045EF70`, `004572B0`, `00461970`, `0049C320`, `0049C360`, `00461B80`, `00461C80`, `00461D50`, `00409850`, `00409980`.
- Class registration at `00461970` uses `0049C320` for **two separate** 12-byte lists: enrolled head `0054B204` (payload = world-node pointer) and pending head `0054B208` (payload = enrolled-list node pointer). This list is **not** the world registration array at `00542830`.

## Verified migration

| Change | Count | Example |
| --- | ---: | --- |
| New partial C-compatible types | 3 | `I76_WorldNode_0xB0`, `I76_ClassLinkNode_0x0C`, `I76_ActiveWorldEntry_0x78` |
| Typed parameters | 15 | world-node constructor, class binder/init/pre/post, ref resolver/cleanup, active-world callback, generic list insertion/removal |
| Typed returns | 4 | world-node allocation, conditional resolver, active registry entry and **12-byte list insertion** |
| Typed class-list global heads | 2 | `0054B204`, `0054B208` |
| Guarded misleading symbol correction | 1 | `0045F0F0`: `release_world_object_tree_reference` → `OBJ_ResolveLiveOrReleaseWorldReference` |
| Additive lifecycle evidence comment | 1 | `0045F0F0`; preserves earlier notes |
| **Total** | **26** | No errors, no conflicts |

The direct x86 `0049C320..0049C357` trace demonstrates `EAX` holds the returned `HeapAlloc` node or NULL at all return paths. Ghidra's prior **void** prototype was incorrect despite callers using the return. v101 explicitly types the return as `I76_ClassLinkNode_0x0C *`, resulting in cleaner caller and callee pseudocode.

### Key layout boundaries

- Original `0045EBD0` allocates **0xB0 bytes** for a world node, including world position at `+0x40/+0x48/+0x50`, child/sibling links `+0x60/+0x64/+0x68`, class at `+0x6C`, and a class-dependent opaque runtime pointer at `+0x70`.
- `+0x68` must **not** be called a stable `parent`: original child insertion and selected VLOC research show a mutable contextual/backlink role.
- The world record is kept at the true **0xB0 extent**, not v99's partial `0x58` prefix; this avoids v100's demonstrated incorrect array-index reinterpretation of `+0x70`.
- Both class lists share the same **0x0C structural node** but carry distinct payload types. `payload` remains `void *` to avoid inventing a universal payload type.
- `I76_ActiveWorldEntry_0x78` represents registry entries, **not** world nodes or class-list nodes. Only a small subset of the 30-DWORD structure is labeled; the remainder is undefined.
- The world-node `class_runtime` stays an **opaque pointer**. Different classes are not assumed to use one vehicle-runtime structure.
- FSM registered/unregistered callbacks are typed to the active-entry argument, but actor records and AI-private lifetime remain outside this pass.

## C readability test

A fixed, identical **18-function** Ghidra-decompiler sample was captured before and after. **16 functions changed**; 168 accesses now resolve to the newly named fields (vs. 0 before). This is a **sample-specific textual count**, not project-wide completeness. For example:

```c
/* v100 baseline */
*(int *)(param_1 + 0x6c) = param_2;

/* v101 */
world_node->class_id = param_2;
```

```c
/* v100 baseline */
*(int *)(param_1 + 0x70)

/* v101 */
vehicle_root->class_runtime
```

```c
/* v100 baseline */
*(int *)(*param_1 + 0x6c)

/* v101 */
registered_entry->world_object->class_id
```

`0049C360` becomes `node->previous->next = node->next` and `*head_pointer = node->previous`. Original instruction bytes and CFG remain untouched. The trial includes a **same-program second application** (0 changes, 26 already-correct, 0 errors). Original 2,102 function definitions are not created or deleted.

## Apply in Ghidra

1. Open your **locally updated v100** program in Ghidra 12.1.4. Save a backup/export first.
2. Add `I76_ObjectDispatch_v101.java` to Script Manager and run the default **`APPLY=false`** preview. The clean tested baseline reports `changed=26 already=0 skipped=0 errors=0`.
3. Review any `PRESERVE` warning on a locally edited GZF rather than forcing a rename. If matched, change `APPLY=true` and run against a **working copy**. Expect `changed=26 errors=0 committed=true`.
4. Re-run to verify idempotence; inspect `0045EBD0`, `00461970`, `00461B80`, `00461C80`, `00461D50`, `00463120`, `00463800`, `0049C320`, `0049C360`, and `00409850` in the decompiler.
5. Save and export a private v101 GZF, then attach it for reconciliation.

The script guards original executable digest/image/language, existing names/types, global data definitions, and uses a Ghidra transaction. Existing analyst comments are preserved. It does not interpret unverified removal order as safe, claim complete pending dispatch, or infer full runtime-vtable behavior. No retagging of active-world array or class descriptor as whole overlapping data blocks.

## Files and validation

- `I76_ObjectDispatch_v101.java`: executable dry-run-first script.
- `I76_ObjectDispatch_v101.h`: portable **structural sketch**, 32-bit address slots instead of host pointers.
- `header_check.c`: C11 compile and static offset validation, `cc -std=c11 -Wall -Wextra -Werror -pedantic -c header_check.c`.
- `action_audit.tsv`: all 26 operations, evidence.
- `readability_metrics.tsv`: before/after field-name sample counts.

Further work should focus on class descriptor dispatch-table *call signatures* and class-specific runtime layouts only after verified callsite/ABI analysis; the v101 pass deliberately leaves those outside its confidence boundary.