# C readability review

Same Ghidra 12.1.4 default decompiler options, no analysis, **419 unique functions** per capture: all original v100/v101/v102 sample targets, every directly changed signature, important table consumers, controls and their direct callers. Full C, raw digests and unnormalized diffs remain private; selected original-address digests are published. Primary changed targets and important direct callers were reviewed in full. A normalized diff aided caller triage only; variable-number normalization is not evidence of semantic equivalence.

## Improvements

- `00490A00`, `004929B0`: named projection, FOV, source camera coordinates and 4×3 frustum corners replace anonymous offset arithmetic. Existing terrain page-pointer grid and normal/height ABIs remain correct.
- `0047CB00`: surface byte pitch/pixel base/row offset and draw-command shade gradients replace indexed raw pointers. Byte pixel addressing remains byte-based.
- `00491810`: arena advances one true 0x1C leaf; named edge references replace anonymous short offsets. Unknown leading leaf bytes stay unknown; no speculative names added. `004911E0` preserves page-grid array dimensions.
- `0045EBD0`, `0045EF70`, `0045F0F0`, `00461970`, class1 init/pre/post: world-node class/runtime and contextual links become visible inside **0xB0**, avoiding rejected 0x58-prefix array extrapolation. Runtime stays opaque; no `world_node[1].orientation_basis` workaround.
- `0049C320/360`: `previous`, `next`, opaque `payload`, pointer return and head pointer-to-pointer expose real list operations. Enrolled and pending heads stay separate; pending payload cast to enrolled node is local to those verified dispatchers.
- `00461B80/1C80/1D50`, `00461970`, `00462040`: typed descriptor search/dispatch and counters replace anonymous stride-13 arithmetic. Initialize/pre/post pass one world pointer; factory takes zero arguments and returns opaque pointer; damage has world + two opaque arguments and a 32-bit result. Other slots remain `slot_XX`/generic function-pointer calls.

Representative original C expressions before → after (short excerpts):

```c
/* 00490A00 */
*(float *)(camera_view + 0x2c)
camera_view->fov_tangent
/* 0049C320 */
void allocate_linked_list_node_3field(...); /* return; */
I76_ClassLinkNode_0x0C *allocate_linked_list_node_3field(...); /* return pIVar1; */
/* 0049C360 */
*(int *)(*param_2 + 4) = param_2[1];
node->previous->next = node->next;
/* 00461C80 */
(*(code *)(&DAT_004f76ec)[iVar4 * 0xd])(pvVar3);
(*g_world_object_class_callback_table[iVar2].pre_update)(world_node);
/* 00461970 */
world_node->class_runtime = (*g_world_object_class_callback_table[iVar1].runtime_factory)();
```

## Neutral effects

Many of the **127** changed outputs only gain casts or the reviewed resolver alias. They are not individually credited as readability improvements. Class1 post-update `00463950` mainly gains its argument type. Library-only runtime-prefix types do not by themselves change C field accesses. No type is cast indiscriminately into every `class_runtime` use.

Arrow-field occurrences **336→853** within the sample are a textual measurement, not a semantic score. Staged changes are terrain **10**, v100 **10**, v101 **105**, v102 **18**; these overlap. Initial broad v100 trial changed **57** sampled outputs, but was rejected.

## Rejected regressions and deferrals

- **00457FF0 camera argument:** actual input is camera, but Ghidra coalesces its variable with active-entry and stack-list lifetimes; trial prints `g_RND_SelectedCameraActiveWorldEntry` as camera and turns a world pointer into `viewport_center_x`. Defer this propagation rather than endorse false field meaning.
- **00474C60 surface constructor argument:** trial turns its 13-DWORD copy into repeated `surface_descriptor->byte_pitch` plus a cast to `&...->flags`, and repeats this artifact in many callers. Preserve original scalar copying pending local variable separation/copy-loop handling.
- **00472C10 camera argument:** existing raw frustum region is byte storage. Trial obscures numerical four-float plane stepping with byte casts. Defer until independently recovering the plane layout; do not alter v99 structure merely for typography.
- **00409980 active-entry argument:** after initial entry use, original parameter storage is reused for a numeric team-bucket index. Trial introduces `&registered_entry->world_object` arithmetic on that index. Defer; local world-node pointers still legitimately improve via typed callees.

## Residual artifacts and limits

Two bounded presentation drawbacks remain recorded separately from gains: the real camera copy in caller `00460A70` renders an explicit 0x76-DWORD copy as repeated first-field access; the real active-entry clear in `00457420` renders 0x1E-DWORD zeroing similarly. Both operate inside actual identified allocations and retain the exact original four-byte step/count; neither establishes that each copied word is semantically the first field. They are copy/clear idioms, not field ownership evidence. The constructor's original 0x40-byte transform-template copy spans more than the named nine-float basis; retain the raw-copy qualification.

The pre-update callback `00463800` still has a decompiler-coalesced temporary that casts a float duration to a pointer-typed parameter name. The original callback input remains a world node; no local float-duration field is inferred. Existing float-pointer/integer casts, unknown world fields, imported function ABI artifacts and reporter behavior remain reconstruction debt. No new hidden return, speculative parent/payload interpretation, class-runtime allocation extent or fabricated world-node array relationship was accepted. No retail runtime was executed.
