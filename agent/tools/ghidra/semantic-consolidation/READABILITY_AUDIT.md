# Fixed-baseline source readability audit

Ghidra 12.1.4, identical default decompiler settings, no auto-analysis between captures. Both phases use the same imported program; **before** is the v99–v102 staged derivative described in BASELINE_COMPATIBILITY.md. Accepted prerequisite improvements are excluded from new consolidation results. Full C, instruction rows and comprehensive symbol/type/comment captures remain private. Public evidence is limited to digests, counts, reviewed findings and original-authored layout/semantic sketches.

## Measurements and interpretation

`readability_metrics.tsv` contains all **279** selected functions: the 20 required functions, reporter, and discovered direct callers. Reporter callers deliberately broaden the regression sample. No claim of all transitive/indirect callers being decompiled is made. All 2,102 defined function bodies were independently PE-verified.

- **33 changed C digests; 246 unchanged.** A digest change alone is not an improvement.
- **14 reviewed target improvements**: five TER, three live FSM and six RES functions. RES gains are limited to meaningful input names. Import `00410490` and relocation `00412500` remain exactly unchanged.
- All four ENG/OBJ controls `00461970/00461B80/00461C80/00461D50` have identical complete C output and signatures. Existing typed indirect dispatch and opaque runtime payload relationships survive.
- Nineteen additional changed callers/adjacent functions are not counted as target improvements. Their changes include whole-double normal calls, source-name propagation, constant spelling, local coalescing, supplied scheduler words and two verbose generated pointer labels. See CONFLICTS.md.

Counts below are occurrences in comment-stripped C, using the exact regexes in `validate.py`. Named-field counts deliberately include only the new node/cursor/condition/link and x/y/z field vocabulary, and exclude pre-existing dispatch fields. Casts include C syntax patterns, not a P-code semantic measure.

| Metric | All 279 before | All 279 after | 14 improved targets before | 14 improved targets after |
|---|---:|---:|---:|---:|
| Selected named field accesses | 0 | 317 | 0 | 293 |
| Anonymous `param_N` occurrences | 4113 | 3739 | 606 | 232 |
| Anonymous DAT globals | 2738 | 2734 | 100 | 96 |
| Pointer casts | 4963 | 4846 | 573 | 467 |
| All measured casts | 7382 | 7240 | 605 | 497 |
| Direct indexed terrain-grid accesses | 0 | 14 | 0 | 13 |

Aggregate cast reduction does not mean every conversion is correct. VM return-time cursor comparison still casts a temporary to VmNode; terrain retains inaccurate ROUND/world-float artifacts. The normal pointer return is verified in EAX and not inferred from the cast count. No incorrect new node-array indexing was observed in the reviewed changed bodies. No universal class-runtime, host-service bundle or resource-record relationship was introduced.

## Function-group review

| Functions | Reviewed change | Boundary retained |
|---|---|---|
| 00493080 | setup value/mode/spacing inputs; borrowed page-grid indexing | spacing global remains conflicting int; setup allocates no page |
| 00493160 | flattened page/sample indexing with low12 mask | misleading packed-word alias retained; no invented 004931A4 function |
| 004927B0 | indexed high3 material-class read | rounded admission distinct from height interpolation |
| 004931C0 | typed x/y/z output, whole X/Z doubles, EAX output-alias return | packed +4/+8/+16 storage; no hidden result or new alignment gap |
| 00493550 | four indexed corners and named float constants | valid v99 ST0 return retained; original precision and x87 rounding qualification |
| 00414670 | live token/node fields distinguish host and operand cursors | mixed words stay scalar; completion compares restored cursor to base |
| 004149F0 | typed list traversal/unlink and explicit supplied words | cooperative ordering, heap/count scalar roles, deadline before list |
| 00412CE0 | persistent node condition/host cursor/IP accesses | synchronous dispatch owns IP advance/reset; trailing arguments unresolved |
| 0046FFC0 / 00470070 / 00470340 / 00470B20 | logical-name inputs | conditional acquisition versus membership; type proposals not forced |
| 004B2E00 / 004B3030 | key versus output-size/destination/capacity roles | selected-source pointer remains distinct from key table and retained payload |

Representative original-authored C notation (not complete decompiler quotations):

```c
/* Original addresses remain the anchors; these are explanatory responsibilities. */
/* 00493160 */ height12 = page_grid[page_index][sample_index] & 0x0fff;
/* 004931C0 */ normal = terrain_normal(out_normal, world_x, world_z); /* normal == out */
/* 00414670 */ *node->host_cursor++ = node->frame[token->payload];
/* 004149F0 */ *head = completed_node->next;
/* 004B3030 */ retained = read_selected(logical_name, out_size, destination, capacity);
```

Representative complete private bodies reviewed include normal, bilinear height, interpreter, scheduler, loaded-file acquisition, mounted-source selection and registered read. Their original return paths and caller ABI were also checked independently. Larger host-dispatch changes are persistent-field substitutions and its supplied-word envelope; they do not establish the entire host ABI. Caller diffs were screened; two label-verbosity costs remain explicitly recorded. This is a bounded integration success with unresolved issues, not globally export-ready original C.
