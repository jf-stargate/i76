# Terrain storage and ABI assessment

Evidence tier: **binary-static** instructions and Ghidra 12.1.4 annotation experiments on the exact audited v99 export. Accepted Pilot A and consolidation are corroborating sources, not proof of what v99 contains. No engine code was reimplemented or executed.

| Retail address | Verified responsibility / disposition |
|---|---|
| 00493080 | Initialize borrowed page grid and scaling; signature already correct, spacing data corrected |
| 00493160 | Integer lattice query returning low12 height; retained historical packed-word alias |
| 004931C0 | Triangle-selected approximate normal into caller output; correct existing explicit ABI preserved |
| 00493550 | Bilinear world-height sampling; two double inputs and numeric ST0 return preserved |
| 004927B0 | Rounded discrete high3 material class; existing representation preserved |
| 006442C0 | Four-byte spacing: int → float in disposable trial |
| 006442C4 | Four-byte float reciprocal; unchanged |
| 00644380 | 16,384 borrowed ushort pointers; unchanged |
| 004ED7EC | Misdefined four-byte pointer is literal `aud` plus NUL; corrected to terminated string |

## Spacing: every identified writer and relevant reader

Whole-PE searches for the little-endian address 006442C0 find exactly five occurrences, all accounted for in the instruction/reference capture:

- **004930E1** is the only identified writer: MOV stores EAX loaded from the third setup argument at 004930D9. The preceding 004930D5 **FDIV float** uses those same argument bytes; reciprocal **FSTP float** is at 004930FB. There is no float-to-integer conversion before the spacing store.
- **00490AA7 FMUL float** and **00490FB9 FDIV float** consume spacing as IEEE-754 single precision.
- **004937C9 MOV** copies its bits into EAX, then 004937E8/004937EE copy into two float matrix entries; the matrix call at 00493819 and subsequent float transforms consume that representation. This is a bit-copy, not evidence for integer spacing arithmetic.
- **004B8B40 CMP EAX,006442C0** compares an address threshold. It does not read or write the storage. It must not be counted as an integer spacing consumer.

The setup wrapper **00493BD2** pushes the float bit-pattern for 5.0, **00493BD7..00493BDD** supplies the mode/setup arguments, and **00493BDF** calls setup. This caller supplies 5.0; the setup function is not intrinsically constant-5. Reciprocal address searches account for 35 direct sites: 34 floating readers and the float store. `spacing_references.tsv` lists all identified sites. No escaping pointer to spacing was found among address-literal occurrences. This is bounded static evidence, not an assertion about arbitrary indirect memory writes at runtime.

**Correction:** retype exactly 006442C0..006442C3 from `/int` to `/float`, retaining `g_TER_GridStep` and all comments. The script requires the known alias, exact four-byte definition, no interior analyst symbols/instruction overlap and original function guards. A different type, footprint or label aborts the whole application. No neighboring reciprocal definition is cleared.

## Normal and height ABI

At 004931C0, accounting for SUB ESP,14 and register pushes gives entry arguments **output +4, X double +8, Z double +16**. Both fallback **00493210** and normal exit **00493516** reload that output argument into **EAX**. The remaining paths write exactly three float components and return without changing EAX. **00440B8E** calls; **00440B93** loads from EAX; **00440B95** cleans 0x14 argument bytes; **00440B9D/00440BA3** consume the other two components. The existing custom-storage signature already has TER_Normal3f*, EAX:4, and those stack offsets. It has no hidden return pointer or invented padding. **No signature change is proposed.** Caller-owned output and pointer alias return are supported; the original C declaration is unavailable.

Height 00493550 already has double world_x/world_z at stack +4/+12, `/float` return stored as **ST0:10**, and no hidden parameter. Original entry reads doubles at EBP+8/+10; the final path restores RC at 00493792 and leaves the final interpolation/scaling on x87 through RET 004937B2. Outside admission loads numeric zero. Existing float is a valid Ghidra numeric-return presentation; it does not prove an original float declaration or final-width rounding. Preserve it. RC-down FISTP at 004935EE/00493608, float X-row stores before RC restoration, Ghidra ROUND and printed world-to-float casts remain qualifications. No hardware/emulator experiment was rerun here.

## The misleading grid-interior label

At **004ED7EC..004ED7EF**, the original bytes spell **`aud` plus NUL**. v99 defines them as generic `/pointer`, whose apparent numeric value 00647561 happens to equal grid base +0x31E1 = entry 3192 plus one byte. Ghidra therefore generates `PTR_g_runtime_terrain_page_pointer_grid[3192]+1_004ed7ec`. That is an accidental interpretation of text, **not a meaningful interior pointer or ownership relationship**. This narrows/corrects the explanation in accepted consolidation CONFLICTS.md; immutable evidence is left intact.

Ten original PUSH sites pass **the address of the literal** across six audio callers: 00421400, 004217E0, 00422540, 00425130, 00425E60 and 00425EF0. Direct world-reference cleanup callees were examined; the extra word is forwarded without establishing a terrain relationship. The exact purpose of the `aud` tag remains inferred/unresolved; no new parameter type, refcount contract or ownership name is assigned.

**Correction:** replace only the exact generic four-byte pointer at 004ED7EC with a four-byte terminated string. Preserve any analyst data by aborting on another type, interior label or USER_DEFINED start label. Keep page-grid typing unchanged. Ghidra now emits its stable derived string name `s_aud_004ed7ec`; no manual cosmetic alias is introduced.

## Reviewed C differences

Representative excerpts, not complete decompiler exports:

```c
/* 00493080, before -> after */
g_TER_GridStep = (int)sample_spacing;
g_TER_GridStep = sample_spacing;
/* 004937C0: both float matrix entries lose the cast */
local_50[0] = (float)g_TER_GridStep;
local_50[0] = g_TER_GridStep;
/* 00425EF0: actual after expression */
pvVar4 = release_world_object_tree_reference((LPVOID)param_1[0x17],s_aud_004ed7ec);
```

The old audio expression used `&PTR_g_runtime_terrain_page_pointer_grid_3192__1_004ed7ec`. All ten caller sites now use the string symbol. Complete before/after C was manually reviewed for all ten changed functions, five primary terrain functions and relevant direct callees. Changes are limited to four spacing expressions/functions and six audio callers; no new locals, parameters, fabricated arrays, ownership aliases or pointer casts appeared. All other four terrain target C bodies are byte-identical, as are ENG/OBJ, VM and RES controls. This is a small storage/readability correction, not a claim of globally source-ready decompilation.

Unresolved: bit12, unusual x87 input/control state, original declared return precision, exact normal branch intent, page teardown/lifetime, complete collision semantics, and missing v100–v102 type passes. Prior M06 execution corroboration was reviewed but not rerun. Next suitable subsystem is a separately scoped mission VM readability/provenance reconciliation after maintainer acceptance of terrain stability.
