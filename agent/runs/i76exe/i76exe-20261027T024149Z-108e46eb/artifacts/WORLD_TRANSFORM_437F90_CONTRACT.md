# Original retail `00437F90`: vehicle-camera stabilization / orientation basis contract

**Evidence tier:** retail PE disassembly + v97 Ghidra decompilation + original-x86 read-only Ghidra emulation with controlled inputs; **not** Windows retail runtime. **Track:** `i76exe`, milestone A. **Original program:** `i76.exe` MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`; private annotated Ghidra 12.1.4 v97 GZF SHA256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`. Actual addresses are original PE virtual addresses.

## Correction to working interpretation

The v97 Ghidra label `effect_target_bounds_query_helper_00437f90` is **not an observed general world-object transform or a bounding-box accessor**. This function has two direct original PE callers **`00406D40`** (default camera callback `00406AB0`, currently not defined as a Ghidra function) and **`00407236`** (another camera-relative / hierarchy-composing callback around `004071A0`). The second caller traverses attachment parent links at `node+0x68` *outside* `00437F90` and calls this function for the vehicle root. `00437F90` itself does not walk parent links.

ABI from retail instructions: `00437F90(float out[16], world_object *owner)` is `cdecl`, receives out pointer at caller stack `[ESP+4]`, owner at `[ESP+8]`, writes exactly 16 dwords / 64 bytes and returns with `EAX == out` in tested paths. Data are **float32**; do not assume the 16-word constant is a conventional homogeneous 4x4 identity (its final word is zero). The routine first loads original update delta from `0049C7A0`, then branches on `owner+0x6C == 1`. Other classes copy the fixed 16-dword template from `004FAED8` using `REP MOVSD` at `00437FF1`.

## Class-1 inputs and side effects

| Location | Width | Source and proven access | Cautious interpretation |
|---|---|---|---|
| `owner+0x6C` | u32 | `00437FD8` | class discriminator; class 1 takes dynamic path |
| `owner+0x70` | pointer | getter `00467440` | vehicle runtime context pointer; must be valid |
| `owner+0x18/+0x1C/+0x20` | 3 × float32 | loads `004380B2..004380C9` | first object basis vector, used for residual dot product |
| `owner+0x30/+0x34/+0x38` | 3 × float32 | loads `0043802E..00438045` | another object basis vector: **nonzero squared magnitude mandatory** for projection helper |
| `runtime+0xD4/+0xD8/+0xDC` | 3 × float32 | copied into argument to `00493CA0` | vector to project; physical meaning unverified |
| `runtime+0x114` | float32 | loads `00438003`, `0043803D` | adjustment influencing constructed reference points |
| `runtime+0x118` | float32 | loads `00438026`, `00438054`, `00438075` | second adjustment influencing constructed reference points |
| `004FE420` | float32 | `0049C7A0` | frame/update delta; native test explicitly sets `0.016` seconds |
| `0052B93C/40/44` | 3 × float32 | stores around `004381AF`, `0043821A`, `00438269` | persistent smoothing/derived offsets: **function is stateful** |

PE numeric constants include `004BD03C=0.0f`, `004BD040=-0.008f`, `004BD05C=0.95f`, `004BD060=0.005` (float64), `004BD074=-2.0f`, `004BD078=-16.0f`. These are exact *static* data, not promises of production physical units. The matrix data at `004FAED8` is 16 floats with +1 at indices 0,4,8 and zero elsewhere (including index 15).

## Call chain and mathematical operations

1. `0049C7A0`: load update delta from global `004FE420`, including on nonvehicle path.
2. Check `owner+0x6C`; return fixed template for a non-class-1 object. For class 1, call `00467440` for `owner+0x70`.
3. `00493CA0`: decompose runtime vector **v** from `+0xD4` into a component along **d** from `owner+0x30` and perpendicular component: `projected = d * dot(v,d)/dot(d,d)` and `residual=v-projected`. Original x87 instruction `FDIVP` at `00493D1B` has **no zero-length direction guard** in this helper.
4. Dot projected vector with **d** and residual with **owner+0x18**; scale by `-0.008`; derive three offset quantities, including a term scaled by `-16.0`. Frame-delta-dependent x87 comparisons to 0.0, 0.95 and 0.005 select smoothing, updating globals `0052B93C/40/44`. No assumption that each conditional always smooths.
5. `00494C80`: compute a cross product of differences between reference points, then normalize with `00495000` (an approximate reciprocal-square-root helper using lookup data around `00655180`). Collinear/zero-length geometry is a second potential degeneracy. `00494710`: build an orthogonal basis using that vector and the fixed reference vector `(0,0,1)`; this also normalizes through `00495000`. The result is a 16-word float32 orientation/basis record.
6. Copy exactly 16 dwords into `out` at `004382C8` using `REP MOVSD`, return to caller. No object parent traversal, camera projection, resource decoding, or rasterization inside this routine.

### Original-node initialization linkage

`0045EBD0` (world-object allocation/initialization) requests **0xB0 bytes** through imported `HeapAlloc` then copies 16 dwords from `004FAED8` into `object+0x18` at `0045ECAD`. For a root node created by that function, this establishes `object+0x30..0x38 == (0,0,1)` **before** later pose updates. Original spawn code calls `0045EBD0` at `00451219` and `004513E8` (static PE references). The prior camera harness created its top-level root in manually zeroed emulator memory instead of invoking that constructor for the root. This is a plausible, directly testable explanation for the observed class-1 zero-direction NaNs, but the root-cause attribution in the *full selected-bus camera session* is not yet independently replayed.

## Original-instruction replay and counterfactual

The standalone probe executes original `0045EBD0` (only Win32 HeapAlloc response substituted) and original `00437F90` plus `00493CA0`, `00494C80`, `00494710`, `00495000` using controlled finite runtime fields. The native root constructor completes in **86** counted steps, and the class-1 helper in **612**. A native constructor output with direction `(0,0,1)` yields **0 non-finite float32 output words**. Zeroing only the direction vector afterward gives **9 NaN words** in **600** helper steps. A wholly manually zeroed root reproduces the same 9 NaN words. A distinct source direction `(1,0,0)` also yields 0 non-finite words; class non-1 copies the constant without invoking projection helpers. Two independent native replay passes are byte-identical.

These controlled vectors and runtime fields are test fixtures; `00495000` uses original lookup data as represented by imported v97 program memory and has **not been checked against real x87 hardware numeric results**. A fully finite output is not sufficient to certify an orthonormal matrix or genuine retail camera pose: a zero runtime test yielded a finite but degenerate zero-heavy record. We make **no** complete-retail-game or pixel/raster claim.

## Remaining questions (do not merge with milestones B/C)

- Trace exactly how the authentic root object's 16-float basis evolves after `0045EBD0` through VCF, spawn placement and simulation; record first write changing `object+0x30..0x38`.
- Preserve and compare original finite state of `runtime+0xD4..0xDC`, `+0x114/+0x118`, the three smoothing globals and `004FE420` during a real camera tick.
- Test second degeneracy where normalized cross products vanish and investigate `00495000` parity with x87 hardware if needed.
- Re-execute the complete camera path with a **native-initialized root** and native active-world registration. Treat proper pose, frame scheduling, projection and rendered pixels as later milestones.

This is an evidence run and proposed semantic correction, **not** an applied Ghidra rename or canonical documentation promotion.
