# Terrain sampling: explanatory C reconstruction

This is a compact model of original retail `i76.exe`, not recovered developer source or a modern engine implementation. Evidence tier: **binary-static**, checked against the private original PE and a disposable import of the supplied GZF. Earlier M06 original-instruction results are cited as corroboration, not rerun here. The address crosswalk is [ORIGINAL_CODE.tsv](../evidence/ORIGINAL_CODE.tsv); every algorithm below maps to its rows. Names below are explanatory aliases; retained database names and actual changes are in [SYMBOL_DECISIONS.tsv](../evidence/SYMBOL_DECISIONS.tsv).

## Essential storage and interfaces

```c
#include <stdint.h>
typedef uint16_t TerrainSample;       // low12 height; bit12 UNKNOWN; high3 class
typedef struct { TerrainSample samples[128][128]; } TerrainPage; // [z][x], 0x8000
// Runtime pointers are 32-bit. These declarations describe the original address space.
typedef struct { float x, y, z; } TerrainNormal;

float terrain_spacing;               // 006442C0; setup caller supplies 5.0f
float terrain_reciprocal;            // 006442C4; stored 1.0f / spacing (~0.2f)
TerrainSample *terrain_pages[128*128];// 00644380; each points to 16384 packed words
// Separate page-pointer source: 005A4628, acquired by 00493C00.
// Separate eight material-property records: 00644220, NOT terrain pages.

int terrain_initialize(uint32_t setup_value, int mode, float sample_spacing); // 493080
uint16_t terrain_height12(int32_t sample_x, int32_t sample_z);                // 493160
// 4931A4 is an interior instruction, not a separate callable interface.
double terrain_height(double world_x, double world_z);                     // 493550
uint16_t terrain_material(double world_x, double world_z);                  // 4927B0
void terrain_normal(TerrainNormal *out, double world_x, double world_z);    // 4931C0
```

`double` on the height declaration is a conventional C presentation of a numeric **x87 ST0** return. Original instructions do not establish the original source's declared precision: there is no final float or double store in the sampler. The database's `uint` return loses the calculation; Ghidra's `float10` can create an incorrect hidden result pointer. This run uses `double`, verifies two stack doubles and ST0:10, and does **not** assert a final 64-bit rounding. Earlier semantic v99 chose `float`; that also selects x87 in Ghidra but should not be read as evidence of a final float truncation. See [readability audit](READABILITY_AUDIT.md).

For the normal call, the actual entry stack is return address +0, output pointer +4, X double +8, Z double +16. Four-byte stack packing matters: Ghidra dynamic alignment placed X at +12 in a rejected trial. The final script uses explicit storage for this one function. The output belongs to the caller; 12 bytes are overwritten, no allocation or null-output check occurs.

## Page setup and ownership — 00493080

Original `00493BD0` calls setup with `(1, mode_byte_at_00654B87, 5.0f)`. The initializer accepts spacing as an argument; the constant 5 belongs to this caller, not an unconditional value inside setup.

```c
int terrain_initialize(uint32_t setup_value, int mode, float spacing) {
    // Literal ancillary mode settings; precise consumer meaning remains unknown.
    mode_value_at_004FAD20 = 16.0f;
    mode_value_at_004FAD24 = bits_to_float(0x3b2aaaab);
    if (mode == 0) {
        mode_value_at_004FAD20 = bits_to_float(0x40cccccd);
        mode_value_at_004FAD24 = bits_to_float(0x3b800000);
    } else if (mode == 2) {
        mode_value_at_004FAD20 = 40.0f;
        mode_value_at_004FAD24 = bits_to_float(0x3ae353f8);
    }
    terrain_spacing = spacing;
    terrain_reciprocal = store_float(1.0f / spacing);
    setup_value_at_006442D0 = setup_value; // meaning not inferred from caller's 1
    for (int n = 0; n < 16384; ++n)
        terrain_pages[n] = default_page_at_0059C588;
    const uint8_t *zmap = get_zmap_00493BF0();
    for (int z = 0; z < 80; ++z)
        for (int x = 0; x < 80; ++x) {
            unsigned id = *zmap++;
            if (id != 255)
                terrain_pages[(z+24)*128 + x+24] = active_page_00493C00(id);
        }
    return 1;
}
```

Setup overwrites the shared grid, scaling globals and ancillary settings. It allocates/frees no page buffers, validates neither ZMAP length nor active-page ID here, and always returns EAX=1. ZMAP and active-page pointers come from existing loader state. `004939D0` maps the TER sidecar through `00471400` and fills `005A4628` at **0x8000** strides (`00493BA7..00493BBC`); the grid borrows those pointers. Mapped-buffer cleanup/lifetime is outside this cluster and cannot be replaced by freeing the grid entries. Many entries may alias the same page, including the default. No claim is made about initialized default-page content or missing-file success.

The editor's distinct **0x8004 working-plane stride does not apply**. Each game page is exactly 128×128×2 bytes. Page IDs are mapping references, not material IDs.

## Addressing — 00493160 / interior 004931A4

The helper accepts integer lattice coordinates, not world doubles. It adds **3072 = 24×128** samples in each axis, so world sample (0,0) maps to grid page (24,24). There is no clamp to the last sample of a page. Low seven bits select a page-local sample; the remaining bits select another pointer.

```c
// wrap32 and sar32 make original x86 arithmetic explicit; no C signed-overflow claim.
X = wrap32(sample_x + 3072);
Z = wrap32(sample_z + 3072);
page_index = signed32((Z & 0xffffff80u) + sar32(X, 7));
word_index = (Z & 127u)*128u + (X & 127u);
if (page_index >= 16384 || word_index >= 16384 || signed32(word_index) < 0)
    return 0;
return terrain_pages[page_index][word_index] & 4095u;
```

This literal helper lacks a **negative page-index check**. It is not a general safe API for arbitrary int32 coordinates. The local-word negative check is redundant after masks in ordinary inputs but is present in the instructions. Do not silently add a safety guard and call it original behavior. The material variant does explicitly reject a negative page index; height/normal inline variants resemble the helper. Ordinary world samplers have an earlier admission test.

At a seam, sample X=127 and X+1=128 address different pointer-grid entries. With spacing 5, a page covers 640 world units between corresponding page origins. Each corner of interpolation is independently addressed, so repeated/default pointers and cross-page neighbors are naturally handled. `004931A4` loads a full uint16, then `004931A8` masks it: despite the retained alias `TER_ReadPackedTerrainGridWord`, the function returns **height12**, not the full packed word and not world-height units.

## Coordinate admission and rounding

The three world-query functions begin with `bias_index(world * terrain_reciprocal)`. Original x87 multiplies **double** world coordinates by the stored float reciprocal, adds double **6755399441055744 = 0x4338000000000000** at `004FAF18`, stores a double, and reads its low signed 32 bits. On finite normal-range values under usual round-to-nearest, this is the classic rounded-integer bias idiom. It is not a general portable cast or unconditional floor. Admission is a literal sign-bit test of `index_x | index_z | (10240-index_x) | (10240-index_z)`. For ordinary non-overflowing indices it accepts 0..10240 inclusive. Behavior for NaN, extreme values, unusual caller control words or uninitialized terrain is not certified.

The bias idiom also makes boundary admission dependent on rounding, rather than an exact world-space rectangle test. Do not replace it with a claim that all negative coordinates are rejected. The reciprocal is float 0.2, not exact real 1/5.

## Bilinear height — 00493550..004937B2

```c
x_check = bias_index(world_x * terrain_reciprocal);
z_check = bias_index(world_z * terrain_reciprocal);
if (!admitted(x_check, z_check)) return 0.0;  // FLD float 004BE8A0

saved_rc = x87_rounding_control();
x87_set_round_down();
sx = store_double(world_x * terrain_reciprocal);
sz = store_double(world_z * terrain_reciprocal);
ix = x87_fistp_i64(sx); iz = x87_fistp_i64(sz); // low32 used for addresses
h00 = height12_inline(ix,   iz);
h10 = height12_inline(ix+1, iz);
h01 = height12_inline(ix,   iz+1);
h11 = height12_inline(ix+1, iz+1);
fx = sx - ix;
xrow0 = store_float(h00 + (h10-h00)*fx);
xrow1 = store_float(h01 + (h11-h01)*fx);
x87_restore_rounding_control(saved_rc);
return_x87_ST0((xrow0 + (xrow1-xrow0)*(sz-iz)) * float_constant_0_1);
```

This is explanatory arithmetic, not an instruction-perfect floating-point implementation. The original uses x87 intermediates; the two X-row stores occur while rounding is down, and the final Z interpolation occurs after restoring RC. It returns world height from low12 units multiplied by the float constant `0x3DCCCCCD`. It is **bilinear**, not a triangle height plane. Four inlined page reads avoid a necessary call to `00493160`; the algorithms share the addressing rule, not necessarily a source-level call relationship. Queries have no intentional persistent writes; the original temporarily changes x87 RC and restores its saved bits before returning normally.

**Hardware FISTP qualification:** Ghidra 12.1.4 decompilation/P-code prints `ROUND` without honoring the selected control word. Original `FLDCW 004935CA` sets RC down; FISTP sites are `004935EE` and `00493608`. Existing accepted M06 replay delegated those instructions to hardware x87. Its corrected cross-page result and the independent scalar agreement support this interpretation; this run does not rerun that emulator or claim full hardware-sampler parity. Even after annotations Ghidra prints casts of world doubles to float that the original `FMUL double ptr` instructions do not contain. The reconstruction above follows instructions, not those casts.

## Material — 004927B0..0049288F

```c
rx = bias_index(world_x * terrain_reciprocal);
rz = bias_index(world_z * terrain_reciprocal);
if (!admitted(rx, rz)) return 5;
// Original repeats the bias conversions before addressing.
page_index, word_index = locate(rx, rz);
if (page_index < 0 || page_index >= 16384 || word_index >= 16384
    || signed32(word_index) < 0) return 0;
return terrain_pages[page_index][word_index] >> 13;
```

Class lookup rounds to a sample using the bias idiom; it does not bilinearly blend four materials or share the height function's floor-selected corner. Result is 0..7 in the integer return register (C `uint16_t` presentation retained). It is an index, not a pointer to a 20-byte material-property record or a rendered texture. Bit12 is ignored and remains unexplained. Distinguish outside admission fallback **5** from invalid flattened-index fallback **0**. There are no page writes or allocations.

## Normal — 004931C0..00493542

```c
if (!admitted(bias_index(world_x * reciprocal),
              bias_index(world_z * reciprocal))) {
    *out = (TerrainNormal){0,1,0}; return;
}
ix = crt_ftol(world_x * reciprocal);
iz = crt_ftol(world_z * reciprocal);
// Literal test uses ORIGINAL WORLD coordinates, not sx/sz fractional coordinates.
if (world_z - iz <= world_x - ix) {
    a = height12_inline(ix+1, iz);       // h10
    dx = a - height12_inline(ix, iz);   // h10-h00
    dz = height12_inline(ix+1, iz+1)-a; // h11-h10
} else {
    a = height12_inline(ix, iz+1);      // h01
    dx = a-height12_inline(ix+1, iz+1); // h01-h11
    dz = height12_inline(ix, iz)-a;     // h00-h01
}
gx = store_float(reciprocal * float_constant_0_1 * dx);
gz = store_float(reciprocal * float_constant_0_1 * dz);
r = approx_inverse_sqrt_00495000(gx*gx + gz*gz + 1);
out->x = store_float(gx*r);
out->y = store_float(r);
out->z = store_float(gz*r);
```

`004BA090` is an import thunk to `_ftol`, an x87-input CRT conversion, not a no-argument C semantic function. Its ordinary conversion truncates toward zero; its private external implementation was not supplied in this PE. This is an explicit library-contract assumption. Under admitted ordinary nonnegative coordinates it selects the same integer as floor. The three height reads, triangle branches and normalization are visible in original code. The arithmetic above elides extended intermediates; original saves two float slopes, passes a double norm-square to the table-seeded approximate inverse-square-root helper, stores that helper result as double, then writes three floats. The math seed table must be initialized (earlier accepted ENG/VEH research establishes startup necessity).

Two details are deliberately preserved: the unscaled world-minus-index comparison at `00493286/0049328C`, and the **positive X difference in the first branch**, versus negative X in the second. These are not silently replaced with a conventional cross product or derivative of the bilinear height. They are static observations, not a diagnosis of an engine defect or broad numerical validation. Unordered comparisons and unusual CRT conversion state remain outside this description. No general collision behavior follows from constructing this vector.

## Evidence boundary and next use

The coherent sampler requires installed page pointers, loader-owned live page memory, valid scaling and initialized math state. It supplies terrain height, a discrete surface class and a separate triangle-selected approximate normal. Callers such as `00440740` consume height and normal; `0043E530` may first select a polygon surface from another list. This run stops at that interface. No new missions, renderer integration, collision bridge, bit12 interpretation or complete original-source ABI claim is made.

Historical comparison: the preserved May decompilers and v49 renamer describe `00493550` as a transform/bounds helper and `004931C0` as a raw-word sampler; original loads, stores and returns contradict those old descriptions. Current v98 names partly correct them while retaining stale comments/types. Existing v99–v101 passes are accepted tooling references, not automatically applied to the supplied GZF. This run keeps changes local and reports its actual 2,337-function baseline rather than assuming their published 2,102-function counts.
