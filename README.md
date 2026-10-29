# Interstate '76 Reverse-Engineering Reference Index

### Instructions for repository-aware agents

All automated research agents and new conversations should begin with [AGENTS.md](AGENTS.md), then read the versioned [agent access policy](agent/protocol/access.yaml) and [cold-start bootstrap](agent/protocol/BOOTSTRAP.md) at the current `main` commit before proposing any repository changes. The repository is divided into [manual documentation](manual/README.md) and [machine-facing research/protocol](agent/protocol/README.md). The existing `ref/`, `scripts/` and `snapshot/` directories remain accessible pending migration.


### Local Codex CLI workspace

On the local machine where it is available, use `/media/neon-remote/prj/i76` as the workspace root for Codex CLI intermediate work: temporary worktrees, experimental scripts, traces, logs, and generated test artifacts. Do not create separate `/home/z/i76-*` project workspaces (for example, `/home/z/i76-mter01`) for new investigations. Isolate concurrent investigations in distinct child directories under the specified root. Inspect existing contents before writing: do not overwrite a working checkout, active session, or private input assets. This is a machine-specific workspace preference, not a repository publication path or a change to the protected-`main`/immutable-run protocol.

## Mission VM, loader ABI, and original-code emulation (2026-10-21)

The current [retail mission execution contract](ref/mission_execution/README.md) includes the 96-command host ABI, BWD2/FSM loader validation, original-code x86 parser/loader emulation and the latest [v97 annotated listings](snapshot/i76.exe/i76.exe_ghidra_state_snapshot_20261021_v97/README.md). The October 19 program snapshot remains a historical baseline. These results describe **retail `i76.exe`** and are distinct from the separate `i76edit.exe` investigation.

**Editor reference update (2026-10-21):** [original `I76EDIT.EXE` reference](ref/editor/README.md), [road/terrain serialization](ref/editor/road_terrain_serialization.md), and [intersection and wheel-contact limitations](ref/editor/intersection_geometry_and_driving_surface.md). The terrain **road-kind-to-material-index** mapping is now established; rendered road textures/UVs remain incompletely resolved.


This directory is the durable human-readable reference set for the current
Interstate '76 reconstruction work.  It is intentionally organized by runtime
system rather than by individual exporter revision.

## Current reference folders

```text
+------------------------------+--------------------------------------------------------------+
| Folder                       | Contents                                                     |
+------------------------------+--------------------------------------------------------------+
| ref/level_format/            | Mission/terrain/RSEG/ODEF/SDF/static-object reconstruction   |
| ref/editor/                  | Original builder: roads/terrain/intersections, OBJ and FSM   |
| ref/material_format/         | Indexed texture, MAP/M16/VQM/CBK, palette, alpha policy      |
| ref/model_format/            | VCF/VDF/VTF/VGEO/GEO vehicle and reusable GEO model details  |
| ref/zfs/                     | ZFSF archive structure, LZO decode, PIX/PAK resource index   |
| ref/object_resource_resolution/ | ODEF/LDEF class policy and SDF/SGEO static resolution     |
| ref/mission_reconstruction/  | End-to-end current exporter pipeline and validation state    |
+------------------------------+--------------------------------------------------------------+
```

## Current visual/exporter baselines

```text
+--------------------------+--------------------------------------------------------------+
| Area                     | Current baseline                                             |
+--------------------------+--------------------------------------------------------------+
| Terrain mesh             | Dense welded terrain OBJ from TER/ZMAP/TDEF                  |
| Terrain UV               | --terrain-uv-mode world-repeat; --terrain-uv-repeat 1.0      |
| Terrain material style   | natural diagnostic surface-class colors                      |
| Terrain texture, miss8   | direct indexed MAP payloads, e.g. TT181SD_.MAP               |
| Static object roots      | ODEF/LDEF class policy -> SDF/VCF                            |
| Static SDF geometry      | SDF SGEO declared parts -> partName.geo                      |
| Static GEO lookup        | embedded PIX/PAK/ZFS resource index                          |
| Static texture selection | default VQM-first, with per-family overrides                 |
| Static UVs               | GEO UVs with V flip required                                 |
| Static alpha             | targeted black-key alpha for cutout textures                 |
| Sky                      | hemisphere validation object from mission sky/environment MAP|
| RSEG road geometry       | terrain material mapping established; texture/UV rules open           |
+--------------------------+--------------------------------------------------------------+
```

## Important unresolved items

```text
+--------------------------+--------------------------------------------------------------+
| Topic                    | Next evidence needed                                         |
+--------------------------+--------------------------------------------------------------+
| RSEG road textures       | Terrain material mapping established; investigate render texture selection               |
| Multiple road textures   | Investigate how road kind selects I2D* or other textures |
| Road UVs                 | Trace runtime/editor road mesh UV generation                 |
| LUM/TBL/PCF color tables | Determine whether static/terrain palettes are remapped       |
| Runtime render states    | Trace blend/clamp/filter/alpha flags beyond OBJ approximation|
+--------------------------+--------------------------------------------------------------+
```
