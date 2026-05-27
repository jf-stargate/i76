# Interstate '76 RSEG Road / Corridor Reference

This document summarizes the current understanding of `RDEF/RSEG` records and their use in level reconstruction.

## Current conclusion

`RDEF/RSEG` records are route/road/corridor records. Serialized records carry paired left/right edge samples rather than single centerline points.

Current reconstruction use:

```text
Use                         Status
------------------------    ------------------------------------------------------------
RSEG overlay lines          useful and stable
RSEG height                 sample terrain height; do not use serialized +0x10
RSEG road mesh              experimental visual overlay
RSEG road material          unresolved
RSEG road UVs               unresolved
Runtime road type mapping   requires further game/editor tracing
```

## Serialized layout

Current serialized layout:

```c
struct i76_rseg_serialized {
    uint32_t kind;
    uint32_t count;
    struct i76_rseg_point points[count];
};

struct i76_rseg_point {
    float left_x;       // +0x00
    float left_z;       // +0x04
    float aux_z_or_mid; // +0x08
    float right_x;      // +0x0c
    float unknown_10;   // +0x10
    float right_z;      // +0x14
}; // 0x18
```

Field interpretation:

```text
Offset    Field          Current interpretation
------    -----------    ------------------------------------------------------------
+0x00     left_x         left corridor/road-edge x
+0x04     left_z         left corridor/road-edge z
+0x08     aux_z_or_mid   auxiliary z/mid/corridor value; not final height
+0x0c     right_x        right corridor/road-edge x
+0x10     unknown_10     not reliable vertical height
+0x14     right_z        right corridor/road-edge z
```

Important correction:

```text
+0x10 is not reliable height.
```

Some records contain large values at `+0x10`. Visual overlays should sample terrain height at the relevant x/z location and then add a small offset to avoid z-fighting.

## Runtime loader

Runtime loader:

```text
Address     Symbol
--------    ---------------------------------------------
004b8780    load_rseg_route_corridor_records
```

Runtime globals:

```text
Address     Symbol
--------    ---------------------------------------------
005db988    g_runtime_rseg_node_list_head
005db98c    g_runtime_rseg_node_count
```

The runtime chunks large serialized RSEG records into linked runtime nodes:

```text
Runtime node allocation size = 0x2c + point_count * 0x18
point_count <= 0x18
```

Kind `3072` appears as a rare count-zero record and should be treated as a sentinel/control entry until proven otherwise.

## M06 surface-class correlation

M06 terrain/RSEG correlation strongly supports surface class `3` as the road surface candidate and surface class `7` as roadbed/shoulder/adjacent road area.

```text
Surface class    RSEG centerline overlap    RSEG left-edge overlap    RSEG right-edge overlap
-------------    -----------------------    ----------------------    -----------------------
3                about 95.66%               about 95.59%             about 95.79%
7                about 4.21%                about 4.14%              about 3.54%
```

Current interpretation:

```text
Surface class    Role hypothesis
-------------    ------------------------------------------------------------
3                primary road/corridor surface
7                roadbed, shoulder, or adjacent road transition
1                dominant base terrain
5                secondary ground/pad/local surface
0                minor default/boundary/filler surface
```

## RSEG road mesh overlay

The exporter can generate an experimental road mesh from RSEG left/right samples.

Current behavior:

```text
Step                    Current behavior
--------------------    ------------------------------------------------------------
left/right edges        from serialized RSEG point records
height                  terrain sampled at left/right positions
height offset           small positive offset for visibility
faces                   strip quads between consecutive samples
texture source          experimental static road/junction texture family
UV modes                strip, strip-swapped, world-repeat, world-repeat-swapped
```

Useful exporter options:

```text
Option                                  Purpose
------------------------------------    ----------------------------------------------
--write-rseg-road-mesh                  write experimental road/corridor surface mesh
--rseg-road-height-offset N             lift overlay above terrain to avoid z-fighting
--rseg-road-texture-source MODE         static-pattern, terrain-candidate, or none
--rseg-road-static-texture-pattern PAT   choose road texture family, e.g. I2DNG*
--rseg-road-uv-mode MODE                strip/world-repeat variants
--rseg-road-uv-repeat N                 road texture repeat scale
--rseg-road-uv-rotate DEG               0/90/180/270 diagnostic rotation
--rseg-road-uv-v-flip                   diagnostic V flip
```

## Current road-material status

The road mesh placement is broadly correct, but material/UV assignment is not solved.

Observed status:

```text
Aspect              Status
----------------    ------------------------------------------------------------
placement           correct enough for visual validation
height              correct when terrain-sampled
basic material       closer using I2D* road/junction texture families
texture mapping      still rotated/stretched/wrong in places
road type mapping    unresolved
```

The current evidence suggests that each level supports multiple road types and/or road material families. The simple single-texture RSEG overlay cannot represent this faithfully.

## Known road/junction texture families

M06 static object exports include several road/intersection-like families:

```text
Pattern     Current interpretation
-------     ------------------------------------------------------------
I2DNG*      road/intersection/junction candidate
I2DNT*      road/intersection/junction candidate
I2DNX*      road/intersection/junction candidate
```

These are useful test textures but not proof of runtime RSEG material selection.

## Recommended next tracing

The next correct step is binary/editor tracing, not further heuristic UV tuning.

```text
Target                            Reason
------------------------------    ------------------------------------------------------------
game RSEG render/material path     find runtime road texture/type selection
editor road authoring path         likely reveals road type/material fields
RDEF/RSEG sibling tags             ISEG/TSEG may carry road type/material metadata
WRLD terrain/surface handlers      may connect surface texture and road material resources
static I2D material users          understand road junction material conventions
```
