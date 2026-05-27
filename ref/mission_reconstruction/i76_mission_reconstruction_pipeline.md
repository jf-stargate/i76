# Interstate '76 Mission Reconstruction Pipeline

This page documents the current end-to-end mission reconstruction/exporter
baseline.

## Current Baseline Command Pattern

```bash
python3 scripts/i76_level_reconstruction_export_v47.py \
  "/media/neon-remote/prj/i76/game/interstate 76/miss8" \
  --resource-root "/media/neon-remote/prj/i76/zfs" \
  --resource-root "/media/neon-remote/prj/i76/game/interstate 76" \
  --resolver "/media/neon-remote/prj/i76/remote/scripts/local_history/i76_vehicle_texture_slot_resolver_v5.py" \
  --geo-exporter "/media/neon-remote/prj/i76/remote/scripts/local_history/i76_vehicle_geo_obj_export_v20.py" \
  --zfs "/media/neon-remote/prj/i76/game/interstate 76/I76.ZFS" \
  --mission-filter m06 \
  --out-dir /media/neon-remote/prj/i76/scratch_data \
  --write-terrain \
  --write-terrain-materials \
  --write-odef-axes \
  --write-rseg \
  --write-resource-markers \
  --write-static-objects \
  --write-static-uvs \
  --write-sky-object \
  --sky-shape hemisphere \
  --write-combined-scene \
  --export-static-textures \
  --static-texture-map-mode prefer-vqm \
  --static-texture-override "I2D*=prefer-direct-map" \
  --static-texture-override "AT_*=prefer-vqm" \
  --static-alpha-mode auto \
  --export-terrain-texture-candidates \
  --bind-terrain-candidate-textures \
  --terrain-texture-binding-mode evidence-single \
  --terrain-palette-mode mission-act \
  --static-palette-mode mission-act \
  --palette-file "scratch_data/palettes/i76_vehicle_palette_selected.act" \
  --palette-scale auto \
  --copy-resolved \
  --make-tar \
  --fail-empty
```

Terrain UV defaults are expected to be:

```text
--terrain-uv-mode world-repeat
--terrain-uv-repeat 1.0
```

Static UV V flip is expected/default.

## Pipeline Stages

```text
+--------------------------+------------------------------------------------------------+
| Stage                    | Output / evidence                                          |
+--------------------------+------------------------------------------------------------+
| Mission parse            | BWD2 tree, ODEF/LDEF/RDEF/TDEF/ZMAP/ZONE records           |
| Terrain                  | dense welded OBJ, diagnostic surface-class materials        |
| Terrain texture          | direct MAP or MAP->M16/VQM candidate PNG                   |
| RSEG                     | road/corridor overlay lines and experimental road mesh      |
| Static roots             | ODEF/LDEF class-specific SDF/VCF policy                    |
| SDF parts                | SGEO declared parts and hierarchy transforms                |
| GEO meshes               | embedded GEO payload parsed and transformed                 |
| Static materials         | VQM-first + family overrides + alpha                       |
| Sky                      | hemisphere validation object from mission sky MAP           |
| Combined scene           | OBJ concatenation for Blender validation                    |
+--------------------------+------------------------------------------------------------+
```

## Current M06 Conclusions

```text
+---------------------------+-----------------------------------------------------------+
| Area                      | Conclusion                                                |
+---------------------------+-----------------------------------------------------------+
| Terrain classes           | 3 road, 7 roadbed/shoulder, 1 base, 5 secondary/pad        |
| Terrain texture           | miss8 direct MAP TT181SD_ works with world-repeat UV       |
| Sky texture               | NK_1CLD2 environment MAP gives approximate sky             |
| Static objects            | SDF/SGEO/GEO assembly working                              |
| Static material selection | VQM-first with I2D/AT overrides working                    |
| Static transparency       | AW_1BR_1 black-key cutout works                            |
| Road overlay              | geometry placement useful; material/UV unresolved          |
+---------------------------+-----------------------------------------------------------+
```

## Important Output Files

```text
+--------------------------------------+------------------------------------------------------------+
| Output                               | Purpose                                                    |
+--------------------------------------+------------------------------------------------------------+
| scene_obj/*.combined_scene.obj       | Terrain + static + overlays validation scene               |
| scene_obj/*.combined_scene_with_sky.obj | Combined scene plus sky validation object               |
| terrain_obj/*.terrain_dense.obj      | Dense terrain mesh                                         |
| terrain_obj/textures/*.png           | Terrain/environment candidate textures                     |
| static_obj/*.static_objects.obj      | Hierarchy-composed static SDF/GEO objects                  |
| static_obj/textures/*.png            | Static material textures                                   |
| sky_obj/*.skyhemisphere.obj          | Sky validation geometry                                    |
| tables/static_part_instances.tsv     | Static SGEO part evidence                                  |
| tables/static_texture_exports.tsv    | Static material resource selection                         |
| tables/static_texture_alpha.tsv      | Transparency/color-key decisions                           |
| tables/terrain_surface_inference.tsv | Surface-class role evidence                                |
| tables/terrain_map_probe.tsv         | Direct MAP / sibling image evidence                        |
| tables/rseg_road_texture_bindings.tsv | Experimental road material selection                      |
+--------------------------------------+------------------------------------------------------------+
```

## Unresolved Road Work

RSEG geometry is useful for placement, but the road renderer/material pipeline is
not solved.  Each level likely supports multiple road types.  The next work
should trace both game and editor binaries.

```text
+----------------------+------------------------------------------------------------+
| Question             | Needed trace                                               |
+----------------------+------------------------------------------------------------+
| road type storage    | RSEG/RDEF fields or side tables selecting material family  |
| road material source | I2D* vs other road/junction/terrain material names         |
| road UV generation   | runtime/editor road mesh texture coordinate generation     |
| intersections        | junction-specific material placement and orientation       |
+----------------------+------------------------------------------------------------+
```
