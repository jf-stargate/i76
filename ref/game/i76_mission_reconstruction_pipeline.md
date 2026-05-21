# Interstate '76 Mission Reconstruction Pipeline

This page describes the practical reconstruction pipeline as of the current baseline. It is a
workflow document, not a complete file-format specification.

## Baseline reconstruction layers

| Layer                    | Current output                              | Status                             | Default?          |
|--------------------------|---------------------------------------------|------------------------------------|-------------------|
| Mission chunk parse      | BWD2 tree and section inventory             | stable                             | yes               |
| Terrain                  | dense welded terrain OBJ                    | stable visual baseline             | yes               |
| Terrain adaptive overlay | diagnostic adaptive polygon overlay         | incomplete edge-sharing            | no                |
| RSEG roads/corridors     | left/right/centerline/crossbar OBJ overlays | useful diagnostic                  | yes               |
| ODEF placement           | basis/position axes OBJ                     | stable scaffold                    | yes               |
| ODEF objects             | .vcf or .sdf by class                       | resource policy now corrected      | next              |
| LDEF objects             | .sdf static scene objects                   | resource policy high confidence    | next              |
| SDF children             | SOBJ/SGEO/SCHK/LOBJ decode                  | partially traced                   | next              |
| GEO meshes               | OEG. runtime geometry reconstruction        | vehicle path partially implemented | next              |
| Materials/textures       | TMT/MAP/M16/VQM/CBK                         | known from vehicle work            | later integration |

## High-level flow

| Step | Input                 | Output                                    | Notes                                                                    |
|------|-----------------------|-------------------------------------------|--------------------------------------------------------------------------|
| 1    | .MSN/.SPC/.LVL        | BWD2 chunk tree                           | Top-level sections include WDEF, TDEF, RDEF, ODEF, LDEF, ADEF            |
| 2    | TDEF/ZMAP/ZONE + .TER | runtime page-grid terrain model           | ZMAP active pages map to a 128x128 page-pointer grid with +24/+24 offset |
| 3    | .TER pages            | dense welded terrain OBJ                  | One visual baseline quad per terrain sample interval                     |
| 4    | RDEF/RSEG             | road/corridor overlays                    | Serialized kind/count plus 0x18-byte point records                       |
| 5    | ODEF/OBJ              | placement records and resource references | Class-specific .vcf/.sdf resolution                                      |
| 6    | LDEF/OBJ              | static scene object references            | label.sdf                                                                |
| 7    | SDF                   | child resource descriptors                | SDFC, SOBJ, SGEO, SCHK, LOBJ                                             |
| 8    | SOBJ child labels     | GEO resource references                   | partName.geo                                                             |
| 9    | GEO/TMT/MAP/etc.      | placed meshes/materials                   | Final object reconstruction target                                       |

## Mission sections

| Section        | Primary role                                                                     | Current confidence                                 |
|----------------|----------------------------------------------------------------------------------|----------------------------------------------------|
| WDEF/WRLD      | World resource/config references: palettes, sky/clouds, hazard, surface textures | high                                               |
| TDEF/ZMAP/ZONE | Terrain page map and .TER sidecar name                                           | high                                               |
| RDEF/RSEG      | Road/corridor/route-like geometry                                                | medium-high                                        |
| ODEF/OBJ       | Object/entity placement records                                                  | high for transform/class policy                    |
| LDEF/OBJ       | Static scene object placement via SDF                                            | high for resource policy                           |
| ADEF/FSM       | Mission scripting / behavior tables                                              | high-level understood; execution not reconstructed |

## Terrain baseline

Dense terrain is the visual source of truth for now. The adaptive overlay is useful for understanding
the retail renderer but should not replace the dense mesh until shared edge records and exact projection
error behavior are implemented.

| Property             | Value                           |
|----------------------|---------------------------------|
| TER page size        | 128 x 128 uint16 samples        |
| Height bits          | word & 0x0fff                   |
| Surface class        | word >> 13                      |
| Page-grid dimensions | 128 x 128 runtime slots         |
| ZMAP offset          | +24, +24 into runtime page-grid |
| Dense M06 faces      | 16 * 128 * 128 = 262144 quads   |

## Object placement baseline

`ODEF/OBJ` axes are scaffolds showing placement and orientation, not final geometry. They are still
valuable because the retail binary copies the same basis/position fields into runtime transform blocks.

| Field      | Used for                             |
|------------|--------------------------------------|
| label[8]   | Resource stem or special marker name |
| basis_3x3  | Object orientation                   |
| pos_x/y/z  | Object origin                        |
| class byte | Resource policy and case dispatch    |

## Reconstruction policy

The default reconstruction path should remain binary-backed. Optional Open76-compatible outputs can be
useful for comparison, but they should be named as compatibility or comparison layers when they differ
from retail control flow.
