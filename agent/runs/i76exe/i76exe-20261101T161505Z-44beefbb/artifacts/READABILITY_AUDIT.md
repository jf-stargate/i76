# Ghidra readability audit

Measured baseline: supplied private GZF SHA-256 `d48df73dc331b87c2bae23f4f481be102aa0a77c6baceb01687de8a6e0e57fbd`, Ghidra 12.1.4, domain file `i76_mission_v98_verified_names`, actual program name `i76.exe`, **2,337 functions**. Published v99–v101 reports describe a 2,102-function trial; that count and their migrated types were not assumed here. This GZF has partly migrated function names and meaningful scaling/grid globals, stale comments, a `uint` height return and a split Z argument for the normal function. The private GZF was imported twice into new disposable projects; the supplied export and other projects were untouched.

The final same-input run used the same decompiler default settings for all captures. `TerrainInspect.java` produces bounded **private** output. [Metrics](../evidence/readability_metrics.tsv) summarize five unique functions; `004931A4` is an interior instruction and is not double-counted. [Checks](../evidence/capture_checks.json) contain private capture digests and 23 passing assertions; [code-range digests](../evidence/code_ranges.tsv) match the original PE and gate the annotation script against patched program bytes.

| Function | Before | Final | Limit |
|---|---|---|---|
| `00493080` setup | three anonymous parameters, scalar grid symbol and pointer arithmetic | `setup_value`, `mode`, `sample_spacing`; indexed pointer array | mode consumers and setup-value meaning remain unknown |
| `00493160` lattice height | anonymous inputs, integer page address plus byte offset | `sample_x/sample_z`, `grid[page][sample] & 0xfff` | retained USER_DEFINED name suggests packed return; additive comment corrects it |
| `004931A4` | word load inside helper | same instruction and containing function | no fabricated second function |
| `00493550` height | `uint` return, only admission/rounding fragment visible | two doubles, double presentation with ST0:10 return, four grid reads and bilinear result | inaccurate decompiler ROUND and casts remain |
| `004927B0` material | anonymous doubles and integer address arithmetic | `world_x/world_z`, indexed sample shift by13 | bias rounding still requires instruction reading |
| `004931C0` normal | output float pointer, double X, two 32-bit pieces of Z | `void(TER_Normal3f *, double, double)`, whole Z, six named component writes across success/fallback | `_ftol` still printed as argumentless import thunk; approximate inverse sqrt retains split argument prototype |

Representative original baseline fragment:

```c
uint __cdecl TER_SampleBilinearHeightXZ(double param_1,double param_2)
/* ... */
return CONCAT22(/* rounding/control-word temporaries */) & 0xfffff3ff | 0x400;
```

Final decompiler fragment (elided only to focus on return shape):

```c
double __cdecl TER_SampleBilinearHeightXZ(double world_x,double world_z)
/* Four separately indexed g_runtime_terrain_page_pointer_grid reads & 0xfff. */
return (((double)(((float)uVar7 - (float)uVar9) * fVar3 + (float)uVar9)
         - (double)fVar2) *
        ((double)(g_TER_GridStepReciprocal * (float)world_z) - (double)local_10)
        + (double)fVar2) * (double)FLOAT_004be8a8;
```

The complete calculation is visible, but `(float)world_z` is still a **decompiler artifact**: original `FMUL double ptr` has no such input cast. `double` selects the correct numeric return ABI without asserting final double rounding. The original ends with FMUL followed by epilogue/RET, and caller `0044089C` immediately consumes ST0 using FSUB, after passing exactly 16 bytes of doubles. This is stronger evidence than choosing a type because the C looks cleaner. No hidden result pointer is introduced.

Second representative before/after:

```c
// Before
void TER_SampleSurfaceNormalXZ(float *param_1, double param_2,
                              undefined4 param_3, undefined4 param_4);
param_1[1] = (float)fVar11;

// Final
void TER_SampleSurfaceNormalXZ(TER_Normal3f *out_normal,
                              double world_x, double world_z);
out_normal->y = (float)fVar11;
```

## Regressions and safeguards

A **rejected first trial** used Ghidra dynamic storage for normal `(pointer,double,double)`. It aligned X to entry stack+12 and Z to+20 instead of the actual +8/+16. The output acquired `in_stack_00000008` and `CONCAT44` artifacts. That trial was discarded; the final script uses custom stack storage **only for this normal signature**, and a fresh GZF import verifies +4/+8/+16. This is unrelated to a hidden height-result pointer. All final normal arguments are accounted for and no alignment-gap input remains.

Remaining pre-existing limitations: x87 P-code's ROUND ignores RC; bias arithmetic still displays dubious float casts; ftol and inverse-sqrt helper prototypes are not fully readable; historical plate comments still mention obsolete transform/raw-word interpretations. The script **preserves those analyst comments and appends repeatable corrections**. Existing USER_DEFINED names are retained, including misleading `TER_ReadPackedTerrainGridWord`. A clearer `TER_ReadHeight12` is proposed but skipped to honor symbol preservation. No new semantic regression was observed in the final five-function comparison, with these limits.

Final operations: **19 planned, 19 applied, 0 additional on repeat; 0 skipped in the final application; no exceptions**. These are 2 type definitions, 5 signatures, 7 data applications and 5 additive comments. The audit table also records deliberately skipped *candidate ideas* outside those 19 operations. No functions are created/deleted; all five original body ranges and instruction sequences are identical. The default dry-run capture is byte-identical to the before capture. The original USER_DEFINED global labels in the inventory are preserved; undefined constant data may acquire Ghidra-generated FLOAT labels.

The full grid is mapped as `uint16_t *[16384]`, not a larger nested page structure: this preserves literal flattened addressing and avoids invented array-of-structure indexing. `TER_Page` is a standalone reference type, not imposed onto borrowed buffers. `TER_Normal3f` contains only the three observed floats. Other unknown fields remain unknown. Defined data, interior user labels, nondefault parameters, conflicting types and unexpected function names cause preservation/skips (or transactional failure for conflicting pilot types). SHA-256, MD5, architecture, image base and original instruction-range hashes guard application. No original instruction byte is modified.
