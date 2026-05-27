# Interstate '76 ZFSF Archive and Resource Extraction Reference

This page documents the current reverse-engineered understanding of the
Interstate '76 `I76.ZFS` / `I76.ZIX` resource system and how extracted resources
feed the mission, model, material, and terrain reconstruction tools.

## ZFSF Overview

`I76.ZFS` is an Activision/game archive format with magic `ZFSF`.  It is not
Solaris/OpenZFS.

Known header fields:

```text
+----------------------+------------------------------------------------------------+
| Field                | Meaning                                                    |
+----------------------+------------------------------------------------------------+
| magic                | "ZFSF"                                                     |
| version              | observed 1                                                 |
| record_name_size     | observed 0x10                                              |
| records_per_dtable   | observed 100                                               |
| record_count         | number of directory records                                |
| xor_key              | observed 0 in retail I76.ZFS                               |
| first_dtable_offset  | offset to first directory table                            |
+----------------------+------------------------------------------------------------+
```

Directory tables are linked records of fixed-size entries.  Each entry contains
a 16-byte name, payload offset, stored size, flags/expanded size, timestamp-like
field, and record id.

## Compression Modes

```text
+--------+------------------------+---------------------------------------------+
| Flag   | Meaning                | Notes                                       |
+--------+------------------------+---------------------------------------------+
| 0x01   | tombstone/inactive     | filtered from live resource set             |
| 0x02   | LZO1X                  | decompressed by game wrapper                |
| 0x04   | LZO1Y                  | decompressed by game wrapper                |
+--------+------------------------+---------------------------------------------+
```

The retail executable contains LZO 1.00 style decode paths.  The wrapper treats
return code zero as success.

Important binary functions:

```text
+----------+---------------------------------------------------+
| Address  | Current name                                      |
+----------+---------------------------------------------------+
| 004b9800 | open_zfsf_archive                                 |
| 004b9bd0 | read_zfsf_record_payload                          |
| 004b9db0 | read_zfsf_record_allocated_payload                |
| 004b9fc0 | zfsf_decompress_record_payload_by_lzo_mode        |
+----------+---------------------------------------------------+
```

## Resource Indexing Role

Archive extraction alone is not sufficient for reconstruction.  Many visual
assets are embedded inside PIX/PAK-like resource containers and must be indexed
by logical name.

Current reconstruction depends on a combined index:

```text
+-----------------------+---------------------------------------------------------+
| Source                | Role                                                    |
+-----------------------+---------------------------------------------------------+
| extracted ZFS files   | top-level VCF/SDF/ACT/MAP/M16/VQM/TMT resources         |
| PIX/PAK payloads      | embedded GEO/TMT/MAP/M16/VQM/CBK and related assets     |
| installed miss8 tree  | mission containers and 8-bit terrain/texture resources  |
| installed miss16 tree | mission containers and high-color/alternate resources   |
+-----------------------+---------------------------------------------------------+
```

The reusable resolver currently provides the embedded-name inventory used by
the level exporter.  Recent full runs indexed approximately tens of thousands
of logical resource names, including thousands of embedded `.geo` assets.

## Resource Types Relevant to Current Reconstruction

```text
+-----------+--------------------------------------------------------------+
| Extension | Current role                                                 |
+-----------+--------------------------------------------------------------+
| .MSN      | Retail mission BWD2 container                                |
| .TER      | Terrain page/sample data                                     |
| .SDF      | Static scene-object root                                     |
| .VCF      | Vehicle/actor root                                           |
| .GEO      | Mesh part payload, usually embedded                          |
| .MAP      | Texture name, direct indexed image, or wrapper/reference      |
| .M16      | Indexed image payload                                        |
| .VQM      | 4x4 block-compressed indexed image                           |
| .CBK      | VQM codebook                                                 |
| .TMT      | Texture frame/material set                                   |
| .ACT      | 256-color RGB palette                                        |
| .LUM      | 65536-byte luma/remap candidate                              |
| .TBL      | 65536-byte table/remap/translucency candidate                |
+-----------+--------------------------------------------------------------+
```

## MAP Resource Split

Recent terrain/material work established that `.MAP` is contextual.

```text
+-------------------------+------------------------------------------------------------+
| Case                    | Behavior                                                   |
+-------------------------+------------------------------------------------------------+
| Static ordinary MAP     | Often a material name that resolves to same-stem VQM/M16   |
| Static I2D* MAP         | Road/junction family; direct-MAP override can be needed    |
| miss8 terrain MAP       | Direct indexed 128x128 image payload                       |
| miss16 terrain MAP      | Often resolves by same-stem M16/VQM sibling                |
| sky/environment MAP     | Direct indexed image or image sibling depending mission    |
+-------------------------+------------------------------------------------------------+
```

Direct indexed MAP shape:

```c
struct direct_indexed_map {
    uint32_t width;
    uint32_t height;
    uint8_t  indexed_pixels[width * height];
};
```

Validated direct MAP examples:

```text
+------------+------------+-------------------------------+
| Resource   | Shape      | Role                          |
+------------+------------+-------------------------------+
| TT181SD_   | 128x128    | miss8 M06 terrain candidate   |
| NK_1CLD2   | 128x128    | miss8 M06 sky/environment     |
+------------+------------+-------------------------------+
```

## Static Object GEO Resolution Through Embedded Index

The mission reconstruction pipeline now depends on embedded GEO lookup:

```text
MSN BWD2
  -> ODEF/LDEF OBJ records
  -> SDF root
  -> SGEO declared part
  -> partName.geo
  -> embedded resource index hit
  -> parse GEO payload
```

Important policy: a missing filesystem `.geo` file does not imply the asset is
missing.  Most static and vehicle GEO payloads are embedded in PIX/PAK/ZFS
indexed resources.

## Recommended Extraction/Index Debug Artifacts

```text
+-----------------------------------+---------------------------------------------------------+
| Artifact                          | Purpose                                                 |
+-----------------------------------+---------------------------------------------------------+
| resource_inventory.tsv            | All logical resources and source locations              |
| embedded_asset_inventory.tsv      | PIX/PAK embedded logical asset names                    |
| unresolved_resources.tsv          | Missing policy-required roots                           |
| static_texture_asset_probe.tsv    | MAP/M16/VQM/TMT/CBK availability per static texture     |
| terrain_map_probe.tsv             | MAP payload shape and sibling availability              |
| level_color_table_probe.tsv       | ACT/LUM/TBL/PCF color context resources                 |
+-----------------------------------+---------------------------------------------------------+
```

## Current Open Questions

```text
+-----------------------------+--------------------------------------------------------+
| Topic                       | Needed evidence                                        |
+-----------------------------+--------------------------------------------------------+
| LUM/TBL behavior            | Trace renderer/material table lookup                   |
| PCF role                    | Determine palette/table content and binding context    |
| Road materials              | Trace game/editor road type -> texture selection       |
| MAP variants                | Catalog all direct MAP vs wrapper/sibling cases        |
+-----------------------------+--------------------------------------------------------+
```
