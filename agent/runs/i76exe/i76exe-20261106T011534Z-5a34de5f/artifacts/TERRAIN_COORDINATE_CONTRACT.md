# Retail terrain coordinate contract

Run `i76exe-20261106T011534Z-5a34de5f`, base `7c315c103e6eda864f5bd9f3c3736a03b4c1fa7c`. Candidate research, not a canonical promotion. Binary identity, media identities and checksums: [input ledger](../evidence/input_identities.json). Claims below apply to initialized ordinary finite queries on this retail executable; measurements cover M06 and CD M02 plus explicitly controlled M06 variants.

## Evidence classes

**S**: binary-static instructions, all audited bytes checked against the retail PE and Ghidra executable section. **E**: original instructions emulated in Ghidra 12.1.4 with listed services. **H**: unchanged original sampler instructions executed on an i386 CPU under a Linux shim with supplied image/grid/page backing. **D**: independent integer/rational model; it invokes no original implementation. **P**: prior accepted visual-terrain evidence, not newly replayed here. E/H are not full retail Windows or gameplay execution.

## Exact source-to-world mapping — F1 (S/E/H/D)

Let `r,c` be zero-based serialized ZMAP row/column and `lz,lx` local sample row/column, each local in 0..127. ZMAP has a one-byte page count before its 6,400 page-reference bytes. `id = ZMAP_payload[1 + r*80 + c]` is an **unsigned byte**; 255 retains the shared default-page pointer. Other IDs select the loader's page ordinal, not a surface class.

```text
runtime page coordinates = (c+24, r+24)
runtime slot             = (r+24)*128 + (c+24)
TER byte offset          = id*0x8000 + lz*0x100 + lx*2
raw word                 = little_endian_u16(TER + offset)
global lattice X         = c*128 + lx
global lattice Z         = r*128 + lz
world X                  = 5 * global_X
world Z                  = 5 * global_Z
world height Y           = (raw & 0x0fff) * float32(0.1)
surface class            = raw >> 13
unknown bit12            = (raw & 0x1000) != 0
```

Positive X increases serialized columns and local column; positive Z increases serialized rows and local row. Column byte stride is 2; row byte stride 256; page byte stride 32,768. No axis reversal, row/column transpose, 40-page centering or extra world-origin subtraction occurs in these coordinate/sampling paths. The internal +3072 lattice translation maps source `(0,0)` to runtime page `(24,24)`; it does **not** put serialized `(24,24)` at world zero.

`5.0f` is supplied by original TDEF exit `00493BD0`. Initializer `00493080` stores step `006442C0` and float reciprocal `006442C4 = 0x3e4ccccd`. The height constant is `0x3dcccccd`, exactly 0.100000001490116119384765625, not decimal-real 0.1 or historical 409.5/4096. These formulas describe conceptual world positions; original source geometry can retain lattice X/Z and low12 Y until its combined camera transform. Do not add world scaling twice.

## Literal integer helper — F1/F3 (S/E/H/D)

`00493160` accepts two signed int32 lattice coordinates on the stack, X then Z; `004931A4` is an interior load, not an entry point. Define `wrap32` and signed arithmetic right shift explicitly:

```text
X = signed32(wrap32(global_X + 3072))
Z = signed32(wrap32(global_Z + 3072))
slot   = signed32(wrap32((uint32(Z) & 0xffffff80) + arithmetic_shift_right(X,7)))
sample = (uint32(Z) & 127)*128 + (uint32(X) & 127)
if signed(slot) >= 16384 or signed(sample) >= 16384 or signed(sample) < 0:
    return 0
return u16(page_pointers[slot] + sample*2) & 4095
```

The `AND AL,80` instructions preserve the upper 24 bits of EAX, implementing `& 0xffffff80`, not `& 0x80` on the full value. `SAR`, not logical shift, matters for negatives. Original helper omits `slot < 0`. It also does not separately bounds-check page X: e.g. lattice X=13312,Z=0 spills into the following flattened row. Negative-slot dereferences were **not executed**; safe checked reconstruction semantics must be explicit ([handoff](RECONSTRUCTION_HANDOFF.md)).

## Evidence and scope

`coordinate_cases.jsonl` records each input, original address, slot, page/default identity, sample offset, word, decoded attributes, conceptual world position, native ST0 and expected rational height. World records contain all four height-corner addresses in read order and a distinct rounded material sample. [Sparse anchors](../evidence/instruction_anchors.tsv) identify the actual instructions; [continuity](PAGE_CONTINUITY.md) and [numerics](NUMERICAL_BEHAVIOR.md) define boundaries.

The source geometry/camera separation is additionally supported by accepted runs `i76exe-20261030T025441Z-8f2b292d` and `i76exe-20261031T011728Z-b887fccd` (P): original pre-transform vertices store integral lattice X/Z and low12 Y; `004937C0` applies scale as part of the camera/view affine operation. Those renderers were consulted, not newly run. Terrain collision-query normals and rendering-light slopes are distinct consumers. No texture/UV, bit12 meaning, arbitrary-mission behavior or native camera scheduling is inferred.
