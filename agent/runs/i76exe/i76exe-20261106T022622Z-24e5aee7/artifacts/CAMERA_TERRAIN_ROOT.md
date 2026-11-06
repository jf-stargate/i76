# Camera to terrain root

Run `i76exe-20261106T022622Z-24e5aee7`, i76exe; advisory TER/RND/GEO.
Pinned protected main: `19c755a77db404ba9cb0ab51f307b4261e983aff`.
Research proposal; no maintained reconstruction or canonical edits.

The independent model takes the original constructed 472-byte camera/view,
viewport width, terrain quality, and an independent terrain-height provider.
It reads no original root, ordered hull, vertical plane, or threshold output.
Deleting every observation from a fixture leaves its prediction unchanged.
The original view's world frustum corners ARE camera inputs, not terrain outputs.
This run does not independently replace the camera scheduler/constructor.

Evidence classes: **S** original binary instructions; **E** original instructions
in Ghidra 12.1.4 with declared services; **H** original instructions on i386 CPU
with supplied Linux image/backing; **D** independent numerical algorithm. Neither
E nor H is a retail Windows frame. The entire 765,952-byte executable section of
the imported v100 database matches the authenticated PE (SHA-256
`e58a54c0e39b55c2d0110cf8a6d22bedf8c53896a85b10dc7d1e8775cfe1318a`).
Inputs and baseline digests are measured in manifest.json; no source payloads ship.

## Camera and terrain coordinates (S/E/H/D)

Accepted #76/#140 setup remains original stock bus construction, registration,
`00405970` projection setup and two original `00406AB0` camera callbacks. Root
pose `(2952.5,60,48152.5)`, identity basis, velocity `(2,0,1)`, dt `.016`, angle
integers `(1,1,1)` and viewport 640×480 are supplied experiment inputs, not a
mission spawn. Contrast adds 200 world X. Baseline source camera is
`(2952.0923249721527,62.02251482009888,48155.97027873993)` after callbacks.

The view retains orientation at +40, inverse translation at +68, local far
corners at +130 (four float32 triples), source camera at +160 (three doubles),
and world far corners at +178 (four double triples). Accepted coherent-camera
verification reconstructs a world corner as source position plus the local
corner transformed by the transpose of the stored orientation. This is the
measured transpose-as-inverse operation; do not assume a perfectly orthonormal
callback basis. Projection +08 is horizontal scale, +2C is the FOV tangent,
+3C is the viewport pointer; +108/+138 are near `.1f` and far `150f`.
`00472400` updates projection/local frustum state; `00472990` installs the
original selected camera transform, source position and world far corners.
`00405970`/`00406AB0` call these original bodies; the accepted harness executes
them unchanged. Their transform formulas were also inspected in the retail
listing. `00472D30` is a downstream affine point transform, not the terrain
footprint projection.
Yaw `.4` and pitch `-.3` root-basis controls exercise rotated original cameras.
Synthetic corner controls are identified separately in fixtures.

`004929B0` calls `00493550` at camera world X/Z. It rejects if the x87
cameraY-minus-bilinear-height result is strictly less than double `.01`.
Equality passes; height is not first rounded to float32. The decompiler's casts
are misleading here. Use #141's sampler operation/store contract, including its
round-down row stores and subsequent restored-control interpolation.

For an accepted camera, construct five double triples with Y=0: camera and four
world far corners. X/Z become world X/Z multiplied in extended precision by
float32 reciprocal `0x3E4CCCCD`; store each coordinate as double. Terrain lattice
spacing is 5 world units. There is no extra world origin shift or axis reversal.
The sampler's internal +3072 page translation is not a geometry translation.
`00490A00` separately stores float32 camera lattice X/Z for LOD distance tests.

## Footprint, expansion and root (S/E/H/D)

Ordinarily the five points' rounded X/Z determine bounds. If **all four original
corner world Y values are <=0**, `00492B82..00492CA7` resets the bounds and replaces
each far point with its camera-ray intersection with world Y=0:

```
t = reciprocal * cornerY / (cameraY - cornerY)
pointX = storedScaledCornerX + (cornerX-cameraX)*t
pointZ = storedScaledCornerZ + (cornerZ-cameraZ)*t
```

Store both as doubles before integer conversion. This is not terrain raycasting.
At least one positive far-corner Y disables the intersection for **all** corners.
Zero corners enter the intersection branch with t=0. Terrain height affects
admission only, not the footprint. No mountain envelope, sampled max-height
expansion, or clipping against varying terrain height occurs in this routine.

Integer conversion adds double `6755399441055744` in the active x87 state,
stores a double, then reads its low signed dword. This is nearest-even under the
tested CW037F, not `_ftol` truncation or `floor`. Initial min sentinels are 13312,
max sentinels -3072; these are extrema seeds, **not clamps**. With resulting
integer min/max X/Z:

```
rootX = (minX & ~31) - 32
rootZ = (minZ & ~31) - 32
extent = max(maxX-rootX, maxZ-rootZ)
exponent = number of arithmetic right shifts until extent becomes zero
```

Positive extent uses bit_length, including an exact power of two: extent 64
produces exponent 7. Root origins expand minima by 32..63 lattice units;
the power-of-two side is anchored there and covers the maxima. This is not a
centered or minimum-area square. Root is written before hull rejection. An early
height rejection leaves previous root/plane globals untouched; fresh zero globals
do not prove reset on repeated frames. Negative extent would never terminate the
original SAR loop; the independent model rejects that unsupported state safely.

## Measured agreement and limits

24 cases: all nine valid #140 cameras; below; all-negative, zero, mixed, duplicate
and collinear corner controls; altered viewport/FOV; qualities 1/2; yaw/pitch;
and three terrain-clearance cases. Native admission, written root integers,
threshold bits and all stored plane float/double fields match D bit-for-bit.
Observed emulated footprint/hull coordinates, duplicate decisions and candidate
scores also match exactly where that path executes. There is one intentional
retained discrepancy: `clear_exact` is accepted by H/D and rejected by E because
the emulator height differs at the .01 boundary. Adjacent .00999/.01001 cases
agree. No emulated source graph exists for `clear_exact`.

`evidence/camera_fixtures.json`, `comparison.json`, `predictions.json` and
`downstream.json` separate inputs, observations, predictions and downstream results.
General NaN/infinity, unusual CW, degenerate division, large-coordinate overflow,
default-page lifetime, arbitrary missions and reused rejected-frame lifetime are
unverified. The model is bounded research code, not a safe general engine API.
