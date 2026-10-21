# Intersection geometry, road sockets, and physical surface continuity

**Evidence baseline: editor road investigations v17–v20**; static geometry and packed-terrain reconstruction from 40 distinct retail mission layouts. The alternative `miss8` and `miss16` archives should not be double-counted as independent maps.

## Real intersection mesh resources

Common road-end-nearby class-4 resources such as `sstop_1`, `sdxin_1`, and `sedet_1` are *sign* objects, not evidence of junction pavement. True intersection SDF prefabs include `itd27_1`, `ijd27t1`, `iga21_1`, `ica21_1`, `iyd27_1`. SDF metadata supplies component geometry and local transforms; actual indexed polygon faces, vertices, UVs and textures come from GEO geometry in associated `.PAK` resources.

The completed static resource mapping resolves **54 intersection SDF definitions**, including **40 packaged geometry resources and 14 shared-geometry aliases**. Correct road attachment is against an exterior polygon edge transformed through the mission object placement, SDF component transform, and terrain-projected root position—not merely an object center or convex bounding rectangle.

## Horizontal sockets

The 40 actual layouts contain **1,300 populated road-strip endpoints**. After full polygon-face reconstruction and resolution of shared aliases, **762 endpoints** fit both corners of an actual transformed intersection exterior boundary within **0.05 world units**. Earlier v18 counts (617 exact for a smaller resource subset) are not separate additional matches.

Centerline endpoint coincidence does not prove edge fit: of 27 exact coincident separate road-to-road endpoints, 19 differ at one or both pavement edges by more than 0.05 units. Real official anomalies include folded/abrupt strips in M03 (`RSEG 0x6C2A`), S04 (`0x91C2`), T07 (`0xCD5A`) and three intersection placements with noncardinal rotation. Oblique intersection families `iga21_1`, `igd27_1`, `ila21_1`, `ild27_1` exhibit a recurrent **0.348–0.350-unit** corner mismatch even against full polygons; do not silently eliminate it. Static edge disparity is not itself proof of a visible crack.

Road terminal terrain-material differences are concentrated near junctions: **251/1,300 road ends (19.31%)** versus **488/88,295 interior samples (0.55%)**, after accounting for known material-parameter aliases. Intentional surfacing versus error remains unproven.

## Vertical placement and terrain footprint

The retail game terrain-samples RSEG road edge height and special intersection roots. Consequently using the *stored* ODEF Y can produce false vertical gaps: some original intersection stored heights differ from reconstructed runtime height by several units, with an observed maximum difference of **32.8 units**.

Among the **762 horizontally exact polygon sockets**, the median of each join's maximum Y discrepancy is about **0.001 world units**, the 90th percentile approximately **0.099**, and maximum approximately **0.50**. These are static estimates from verified reader instructions and packed mission data, not gameplay measurements.

A separate v20 survey examined **386 first-LOD intersection placements in 32 of the 40 missions**. It sampled **13,661** X/Z positions inside actual polygon footprints on a 2.5-unit diagnostic grid. The median per-placement maximum terrain-to-pavement mismatch is ~0.001; **68** placements exceed 0.1, **19** exceed 0.25, **6** exceed 0.5, and **3** exceed 1.0. The greatest value is ~**1.40 units** (A01 `ijd27t1`, OBJ `0x938E`); other fixtures include S03 `ita21_1` (`0x10CAE`, ~1.25) and S04 `ija2171` (`0x14C26`, ~1.20).

Of those 13,661 footprint points, **12,301 (90.04%)** have road-type terrain classes 2/3/4/6/7; **1,360 (9.96%)** have other terrain classes. **192** placements are fully sampled as road materials, while **194** include at least one nonroad sample. These are raster/material facts; not texture assignments or measured wheel forces.

## Contact/collision distinction

Wheel probe code in `i76.exe` at `00440740` demonstrably samples the terrain-height helper `00493550` and packed terrain materials (including `004927B0`), whereas the RSEG renderer consumes a separate polygon strip. Intersection scene classes `0x50/0x52/0x53` can be inserted into a **different scene-geometry list** through `004925F0`, global list head `00644200`. Membership alone does not establish whether those faces take part in independent collision, nor does the wheel probe prove that other environment collisions cannot affect a vehicle. This remains the highest-priority v21 question.

## Future editor compatibility guidance (not implementation)

Keep diagnostics separate for source road graph continuity, genuine polygon socket X/Z fit, runtime-projected road/intersection Y fit, mesh-versus-heightfield variation *inside* pavement footprints, and packed terrain wheel-material boundaries. Preserve signed differences and original regression fixtures. Do not automatically correct official anomalies or infer that visually continuous pavement guarantees correct grip.
