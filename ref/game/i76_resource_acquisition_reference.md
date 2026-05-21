# Interstate '76 Resource Acquisition Reference

This page summarizes the resource acquisition system relevant to mission reconstruction. It explains
how requested resource names flow from mission records into loose files, ZFS records, registered
resources, and PIX/PAK embedded resources.

## Key functions

| Address  | Working name                               | Role                                                   |
|----------|--------------------------------------------|--------------------------------------------------------|
| 004ad640 | format_8char_resource_basename_with_suffix | Normalize mission labels and append optional suffix    |
| 004b41e0 | parse_bwd2_resource_with_descriptor_table  | Open/load resource and parse BWD2 descriptor table     |
| 0046ffc0 | open_resource_file_into_memory             | Primary loaded-resource acquisition chokepoint         |
| 00470070 | load_resource_stream_into_loaded_cache     | Load resource payload into cache record                |
| 00470340 | resource_exists_in_cache_or_search_paths   | Existence/search helper used by optional paths         |
| 00470660 | load_pix_pak_resource_index                | Scan *.pix and index records inside sibling .pak files |
| 00470b20 | load_indexed_resource_record_payload       | Load payload from indexed PIX/PAK resource row         |
| 004b2b30 | register_resource_key_for_zix_path         | Register resource key/path mapping                     |
| 004b2e00 | find_registered_resource_record_by_key     | Find registered resource by normalized key             |
| 004b3030 | load_registered_resource_payload           | Load payload for registered resource                   |
| 004b3310 | get_registered_resource_payload_size       | Get registered resource payload size                   |
| 004b9800 | open_zfsf_archive                          | Open ZFSF archive                                      |
| 004b9db0 | read_zfsf_record_allocated_payload         | Read allocated ZFSF record payload                     |
| 004b9fc0 | zfsf_decompress_record_payload_by_lzo_mode | Decompress ZFSF LZO record payload                     |

## Acquisition flow

| Caller intent            | Main path                                 | Notes                                          |
|--------------------------|-------------------------------------------|------------------------------------------------|
| Parse VCF/SDF/etc.       | 004b41e0 -> 0046ffc0 -> 004b3db0          | Load resource then parse BWD2 descriptor table |
| Check indexed resource   | 0046ffc0 -> 00470b20                      | PIX/PAK indexed resource path                  |
| Load registered resource | 00470070 -> 004b3310 -> 004b3000/004b3030 | Registered resource/cache path                 |
| Load PIX/PAK index       | 00470660                                  | Find *.pix, derive .pak, parse rows            |
| Load ZFSF record         | 004b9db0 / 004b9fc0                       | Archive path for top-level extracted resources |

## PIX/PAK index findings

The PIX/PAK index path is real, but current parsed inventories show it primarily covers mesh/material
payloads rather than mission-level object descriptors.

| Extension seen in PIX | Observed role                    |
|-----------------------|----------------------------------|
| .geo                  | Geometry payload                 |
| .tmt                  | Texture/material table           |
| .m16                  | Texture/image resource           |
| .vqm                  | Block-compressed indexed texture |
| .map                  | Texture map/reference            |

No `.vcf` or `.sdf` entries were observed in the parsed PIX inventories. VCF/SDF are expected as
loose/ZFS resource records rather than PIX/PAK-embedded records in the current install layout.

## Resource name policy

Resource names are case-normalized and usually derived from fixed-width 8-byte mission labels plus a
suffix. The suffix decision is made by the caller, not by `004ad640`.

| Caller                    | Suffix              | Meaning                                |
|---------------------------|---------------------|----------------------------------------|
| ODEF class 0x01/0x08/0x09 | .vcf                | Vehicle/config-backed object           |
| ODEF static classes       | .sdf                | Scene descriptor-backed object         |
| LDEF/OBJ                  | .sdf                | Static scene descriptor                |
| SOBJ child                | .geo                | Geometry payload                       |
| VCFC references           | .vdf/.vtf/.wdf etc. | Vehicle model/texture descriptor chain |

## Practical indexing rules

A complete reconstruction asset index should include:

1. Loose files under the extracted ZFS resource tree.
2. ZFS record metadata.
3. PIX/PAK indexed records.
4. Prior vehicle resolver outputs for embedded GEO/TMT/MAP/M16/VQM/CBK resources.
5. Case-insensitive normalized lookup keys.

Do not treat string hits in prior generated reports or `.tar` files as evidence for embedded game
resources.
