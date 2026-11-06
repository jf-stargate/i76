# Polygon facing and shade

## Facing and planes

Binary-static and executed evidence: walker calls `00494A90` at `00491E4A`, `00491E9F`, and `004920E8`. With input vertices P,Q,R in **post-transform view coordinates**, it forms `(Q-P) cross (R-P)`. The apparent reversed subtraction arrangement in the decompiler is algebraically this same cross product. It scales the cross product using original approximate inverse square root `00495000`, then produces four float32 values `(nx,ny,nz,d)` with `d = -dot(P,n)`, subject to the actual x87 intermediate stores. `d<0` is the facing condition; d==0 is rejected. The whole gate requires both corner triangles to face; fallback tests each eligible fan triangle separately. It does not test normal Y in world space.

`00495000` uses a double exponent/mantissa seed and a generated 256-byte lookup table, followed by one correction. The inherited observer executes original table initializer `00493C50`; `Numerics.seed()` independently reproduces its numerical formula, including the special table[128]=255 assignment. Using a zero-filled PE BSS table is incorrect. No normal table or original binary payload is published. The audited imported baseline matches every byte of the retail 765,952-byte executable section, SHA-256 `e58a54c0e39b55c2d0110cf8a6d22bedf8c53896a85b10dc7d1e8775cfe1318a`.

The independent plane model uses explicit float32 spills and binary64 intermediates. Across this corpus maximum absolute errors are `9.685754776000977e-8` for normal components and `3.0517578125e-5` for d. Validation permits 2e-6 per normal component and `max(2e-6, 2e-6*sum(abs(P_i*n_i)))` for distance cancellation. Every facing sign matches exactly. These are corpus-specific comparison bounds; neither exact plane bits nor all-input x87 behavior is claimed.

## Scalar shade

World light at `006435F0/F4/F8` is multiplied by the retained camera basis at view+40..60 and stored as float32 view-light at `0059C578/7C/80`. For each tested plane:

```
L = -(nx*light.x + ny*light.y + nz*light.z)
attenuation = clamp(first_boundary_Z * [00643600] + [006435FC], .75, 1)
shade = ambient [0059C54C]                     if L < 0
shade = min(1, L*attenuation + ambient)        otherwise
```

The Z comes from the **first flattened boundary vertex**, including when shading other fan triangles; it is not each triangle's minimum, maximum or anchor depth. The clamp lower bound is the original constant at `004BE82C`. There is no independent lower clamp applied to ambient. The first whole shade is spilled to float32; the second remains on the x87 stack until conversion. Triangle scalar shades are spilled before passing to the callback.

At `00492039..00492077`, each shade S is converted through the low dword of the stored double:

```
q = low32_bits(double((1.0-S)*[004FA48C] + 6755399441055744.0))
band = q & 0x1f00
```

The measured scale `[004FA48C]` is 8064. The original code XORs the two low dwords and tests mask 0x1f00. Any unequal masked bands forces fallback before attempting the whole polygon. This is a floating bias/rounding construction, not a truncating C integer cast; round-boundary and unusual FPU modes need separate validation. `SHADE_TEST.first` in raw observer logs is the +64 stack low dword (second shade), and `.second` is +38 (first shade); the verifier reorders them into corner-plane order.

## Controlled rare-branch observations

The accepted stock M06 harness leaves world light, attenuation and ambient zero, so all stock shade comparisons agree. This run's `shade` control supplies world light=(0,1,0), attenuation=(1,0), ambient=float32(.15) before terrain execution. It retains authentic source geometry and original camera construction; it does **not** recover mission lighting initialization. Eighteen leaves now fail the shade-band test: 51 whole attempts +134 triangle attempts=185 attempts, 42 accepted bins. Every band pair, attempt sequence and clip result matches the independent model. Maximum shade error is one float32 step, `5.960464477539063e-8`.

The `high` control additionally supplies cached resource flag `005A4618=1`. Fallback bypasses scalar lighting at `0049216E` and passes zero as the triangle callback shade; the ordinary emitter separately reads per-vertex aux+08 when high-color is enabled. Whole-polygon shade eligibility is still computed. This run validates high-control triangle callback arguments and geometric acceptance, not authentic high-color resources, aux color provenance or displayed color.

Unresolved: degenerate/nonfinite planes, numerical ties near shade boundaries, authentic nonzero M06 light/resource initialization, alternate material emitter success, real palette/color or rendering behavior.
