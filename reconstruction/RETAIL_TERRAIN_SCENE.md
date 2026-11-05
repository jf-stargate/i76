# Retail terrain scene preparation

This implementation is the next terrain-only step after the accepted read-only
BWD2 mission and ZMAP/ZONE/TER inspection code. It does **not** activate a
retail level, generate meshes, construct world objects, or execute scripts.

## Contract and ownership

`i76_terrain_prepare` uses the existing typed retail mission reader to
obtain the serialized 80-by-80 ZMAP page ordinals and the ZONE sidecar name.
The resource store acquires the referenced TER, requires exactly
`active_pages * 128 * 128 * 2` bytes, decodes little-endian packed 16-bit
samples into an owned vector, and releases the TER lease.

Each sample preserves the original packed word. The accessor exposes
`height = word & 0x0fff`, `surface_flag = (word & 0x1000) != 0`,
and `surface_class = (word >> 13) & 7`. The ZONE prefix remains an
opaque byte in the mission definition; it is not used to determine page count.

The new scene holds the normalized mission and TER source names, the complete
ZMAP, counts of mapped cells and referenced pages, and all declared packed
pages. An unmapped page ordinal (0xFF) is not a sampleable cell. No image,
vertex buffer or world-space orientation is inferred from the serialized
sample order. The scene's page and cell indices are source ordinals.

Preparation is transactional: missing resources, malformed BWD2, invalid
ZMAP/ZONE and TER length mismatches do not alter the pending scene. The
`i76_terrain_activate` operation moves an already validated prepared scene
into a distinct active slot; it does not publish render commands or affect
the synthetic `i76_active_level` world registry. Discard and unload are
separate and explicit. The runtime clears both pending and active terrain
during shutdown, allowing subsequent initialization.

All prepared/active data is independently owned. No resource lease survives
preparation or activation. The resource manager's generation-checked handles
remain valid for other clients without being stored in terrain cells.

## Commands

For a user-supplied extracted retail mission with its TER sidecar mounted:

```text
resource mount /path/to/assets
terrain prepare miss16/m06.msn
terrain status
terrain activate
terrain status
terrain unload
```

`terrain discard` removes only a pending scene. These commands are available
in the headless console as well as through other console frontends, with no
window or renderer dependency. They intentionally remain separate from
`level prepare` / `level activate`, which still handle synthetic manifests.
The existing read-only `level terrain <mission>` inspection is unchanged.

## Evidence boundaries

The byte layout, mask and page-size contract come from the accepted retail
reader and earlier original-executable terrain investigations. The new
source-to-scene structure and lifecycle are independently authored
reconstruction design, not recovered retail object layouts.

Actual terrain orientation, page-to-neighbor stitching, world-space scale,
vertex winding, texturing, mesh submission, native clip/draw commands and
mission activation remain separate milestones.

## Validation

`unit_terrain_scene` uses independently authored BWD2/ZMAP/ZONE/TER fixtures
and tests missing missions/sidecars, malformed page references and lengths,
owned sample attributes, unmapped pages, out-of-range indices, busy pending
state, failed activation rollback, discard, replacement preparation, unload,
no outstanding resource leases and repeated runtime initialization.

`functional_terrain_scene` uses the pre-existing synthetic retail
mission/TER directory fixture, then runs the same headless executable
commands that a user would invoke. No proprietary resources are committed.

```sh
cmake -S reconstruction -B build/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/debug --parallel
ctest --test-dir build/debug --output-on-failure
```
