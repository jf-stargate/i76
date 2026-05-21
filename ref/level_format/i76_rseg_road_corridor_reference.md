# Interstate '76 RSEG Road / Corridor Reference

This page documents the current interpretation of `RDEF/RSEG` records. The format is stable enough
for visualization, but some field names remain provisional.

## Descriptor context

| Section | Tag  | Handler  | Role                                          |
|---------|------|----------|-----------------------------------------------|
| RDEF    | RREV | 004b4610 | Revision validation                           |
| RDEF    | RSEG | 004b8780 | Serialized route/road/corridor segment loader |
| RDEF    | ISEG | 004b8960 | Related segment-like record path              |
| RDEF    | TSEG | 004b8960 | Related segment-like record path              |

## Serialized RSEG shape

| Offset | Type               | Current interpretation                 |
|--------|--------------------|----------------------------------------|
| +0x00  | uint32             | kind                                   |
| +0x04  | uint32             | count                                  |
| +0x08  | point[count][0x18] | Serialized point/cross-section records |

The size invariant is:

```text
payload_size == 8 + count * 0x18
```

## Point record interpretation

The six floats read naturally as paired road/corridor edge coordinates, not a single 3D point.

| Offset | Float | Working name | Notes                                                |
|--------|-------|--------------|------------------------------------------------------|
| +0x00  | f0    | left_x       | Left/candidate edge X                                |
| +0x04  | f1    | left_z       | Left/candidate edge Z                                |
| +0x08  | f2    | aux_z_or_mid | Often tracks Z or center/control value               |
| +0x0c  | f3    | right_x      | Right/candidate edge X                               |
| +0x10  | f4    | unknown_10   | Not reliable vertical height; can spike at endpoints |
| +0x14  | f5    | right_z      | Right/candidate edge Z                               |

`+0x10` was initially treated as height but produced large endpoint jumps. Current visualization samples
terrain height instead.

## Runtime chunking

The runtime loader does not necessarily allocate one runtime node per serialized RSEG. It chunks large
segments into nodes of at most 0x18 point records.

| Runtime behavior          | Evidence                             |
|---------------------------|--------------------------------------|
| Node allocation size      | 0x2c + point_count * 0x18            |
| Maximum chunk point count | 0x18                                 |
| Global list head          | 005db988                             |
| Global count              | 005db98c                             |
| Point copy source         | payload + 0x10 + source_index * 0x18 |

## Visualization policy

| Overlay    | Coordinates                   | Height                  |
|------------|-------------------------------|-------------------------|
| left_edge  | left_x / left_z               | terrain sample + offset |
| right_edge | right_x / right_z             | terrain sample + offset |
| centerline | average of left/right edge    | terrain sample + offset |
| crossbars  | left-to-right lines per point | terrain sample + offset |

The RSEG overlay is a diagnostic road/corridor layer. It should not yet be treated as collision,
AI navigation, or rendered road mesh until the runtime consumers of the chunked nodes are traced.
