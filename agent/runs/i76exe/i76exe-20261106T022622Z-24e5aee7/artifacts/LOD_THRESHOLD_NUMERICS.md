# LOD thresholds and arithmetic boundaries

Finding ROOT-LOD; original `00490A8B..00490B18`, quality setter `004907E0`
and initializer `00493080`. S/E/H/D scope is defined in CAMERA_TERRAIN_ROOT.md.

Thresholds are not a function of pose alone. Runtime terrain quality chooses two
float32 factors, qx/qz. Replaying the raw PE's initialized data without calling
the quality setter selects a different state from M06 terrain initialization.
The native probe calls the **original** `004907E0` with the explicit fixture
quality, matching `00493080`; the independent model uses the recovered factors.

| quality | qx bits/value | qz bits/value |
|---|---|---|
| 0 | `40CCCCCD`, float32(6.4) | `3B800000`, 1/256 |
| 2 | `42200000`, 40 | `3AE353F8`, 0.0017343750223517418 |
| other tested: 1 | `41800000`, 16 | `3B2AAAAB`, float32(1/384) |

Do not round quality-2 qz to 1/576; those values differ. The setter first assigns
the default pair, then special-cases 0 and 2. No new renderer setting is invented.

For view horizontal projection scale sx=+08, tangent t=+2C, signed int32 viewport
width W=`*(view+3C)`, terrain step=5.0f:

```
distanceThreshold = float32((abs(sx) * qx) / arithmetic_shift_right(W,1))
heightThreshold   = float32(abs(t*t*4.0f) * qz * step * 10.0f)
cameraLatticeX    = float32(doubleCameraX * reciprocal)
cameraLatticeZ    = float32(doubleCameraZ * reciprocal)
```

Evaluate each threshold chain in original x87 order and retain extended
intermediates until its final FSTP float at `00490AF4` or `00490AB3`.
There is no float32 store after every multiply and no absolute value around the
division. Width is halved as an integer, so odd viewport widths must not use
floating division by two. The same expression can be constant across coherent
changes to width if original projection construction changes sx accordingly;
`lodwide` intentionally changes only the retained viewport width to 800.
`lodfov` intentionally changes only the retained tangent to `.8f`.
Neither is claimed to be an original coherent camera resize operation.

Primary bits: distance `40CCCCCE`, height `3F47FFFE`, camera lattice X
`44139AC8`, Z `46167CC7`. Viewport-only 800 gives distance `40A3D70B`;
tangent-only .8 gives height `3F000000`. Quality 1 gives `41800001/3F055555`;
quality 2 gives `42200001/3EB19998`. Native prefix observations and independent
prediction agree exactly for all 24 cases, including rejected cameras.

## FPATAN, bias conversion and _ftol

The hull FPATAN at `00492EAF` is original x87 atan2(ST1,ST0), popping one value.
The accepted narrow hardware service remains necessary in Ghidra; native CPU
execution needs no FPATAN/FISTP service. Inputs/outputs are captured as ext80.
Stored candidate scores match the independent extended model exactly in the
observed corpus. Signed-zero normal behavior is also explicitly checked.

Root bounds use the add-large-bias / double-store / low-dword mechanism, **not**
CRT `_ftol`. The executable entry at `004BA090` is an import thunk through `004BC27C`;
the external CRT body is not available in this PE audit. Truncation toward zero
is the declared bounded service contract, not a newly executed original CRT
body. The inherited projection harness services
that boundary with an int32 cast for bounded finite values. No out-of-range,
NaN, exception or full int64 `_ftol` emulation is claimed. No `_ftol` call lies in
the root/threshold path measured natively. `00490A00`'s later camera integer
conversion and subdivision CW changes belong to the retained downstream stage.

## Precision evidence and discrepancy

Native x87 CW037F and NumPy longdouble with 64 significant bits reproduce all
observed plane fields exactly. Double normal-component spill points and extended
dot products matter: all-float64 evaluation already changes some plane offset
low bits, even though normals/topology can remain equal. D's float64 diagnostic
mode is not advertised as native parity. Require an x86 extended NumPy build;
other longdouble formats have not been qualified.

At `clear_exact`, source camera Y is double `29.882023029459088`. H/D clearance
is above double .01 by approximately 1e-15; Ghidra's inherited sampler evaluates
a height larger by `2.459108728170359e-6` and rejects. This independently confirms #141's limit:
hardware FISTP service alone does not make the full Ghidra sampler exact. E/H
and prediction fields stay separate in fixtures; the E admission mismatch is
counted and not converted into an alleged successful source-graph comparison.
`numeric_diagnostics.json` records 31 plane-field low-bit differences with
all-float64 evaluation; premature float32 operations give primary height-threshold
`3F47FFFF` instead of original `3F47FFFE`. Default CW only, finite measured states; no universal x87/transcendental parity.
