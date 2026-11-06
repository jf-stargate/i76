# Retail terrain and indexed-asset scene staging

This implementation-only milestone brings together the independently
developed retail terrain scene (#138) and VQM/CBK + ACT/LUM/TBL loaders
(#137). Its output is an **owned, renderer-neutral diagnostic scene**, not a
faithful terrain material mapping, frame buffer, polygon renderer or complete
retail level activation.

## Source provenance and exact supported boundary

The retail WREV-9 WRLD structural proposal from the merged research run
`agent/runs/i76exe/i76exe-20261104T183156Z-085a5e76/` places ACT,
LUM and TBL resource names in 13-byte fields at WRLD payload offsets
`0x1e`, `0x2b`, and `0x38`. This milestone requires one top-level
WDEF, one direct child WRLD and WREV=9, and a **331-byte WRLD payload**.
The renderer-independent reader requires each named slot to terminate in
its own 13-byte extent and normalizes names through the existing resource
store. An ACT name is required; LUM and TBL names may be empty.

These are bounded reconstruction rules for the observed revision, not claims
that the retail executable enforces record length, ASCII, path safety or
consistent error handling. Unsupported versions/layouts are explicit
failures, not heuristically reinterpreted.

The source WRLD **terrain_default** field at offset `0x6c` is not a direct
VQM filename: retail derives multiple MAP variants from that template and
may fall back to built-ins. Material/texture ownership and UV coordinates
remain unresolved. Therefore this first combined stage requires a caller
to name a specific VQM and describes it as a **diagnostic sample texture**,
never the automatically selected visual material for the terrain page.

## Transaction and ownership

`i76_retail_scene_prepare(resources, mission, sample_vqm, pending, error)`:

1. Reads the selected BWD2 mission through the resource provider and
   resolves WREV-9 WRLD ACT/LUM/TBL names without retaining the file lease.
2. Calls `i76_terrain_prepare` to load and own the ZMAP/ZONE/TER page map
   and its packed 16-bit terrain samples.
3. Loads ACT and any **supplied** LUM/TBL into independent owned tables.
   It initializes the active source-255 TBL identity row as in #137.
4. Decodes the explicit VQM/CBK into owned indexed texture pixels using #137.
5. Publishes the scene to the pending slot only after every operation succeeds.

Failures in parsing, resource acquisition, size validation or decoding do
not change an already prepared/active scene. All transient resource leases
are released. The C++ state and data are independent of original retail
runtime pointer layouts. `activate` moves a complete pending scene into
the active slot; `discard` and `unload` are separate. Runtime shutdown
unloads both pending and active combined scenes.

An empty LUM name does **not** generate the retail null-LUM table, and this
stage does not attempt historical MSVCRT/x87 gamma correction. Consumers
must request shade/composition explicitly, and requests fail when a needed
table is absent.

## Indexed sampling

`i76_retail_scene_sample` accepts a serialized terrain cell ordinal,
an ordinal within the referenced 128×128 TER page, explicit signed 16.16
UV coordinates, a shade accumulator, an existing destination index and
two operation-enable flags. It returns:

- The selected packed terrain height (12 bits), flag (bit 12) and surface
  class (bits 13–15).
- The decoded indexed VQM texel from a power-of-two texture, wrapping
  coordinates with the original `width-1`/`height-1` masks.
- Optionally `LUM[(accumulator & 0x1f00) + texel]`.
- Optionally `TBL[(shaded << 8) | destination]`.

Every operand is selected independently by the caller. **No link between
surface-class bits and a particular texture is asserted; no terrain UV
projection or world-coordinate conversion is invented.** Sampling failure
preserves the caller's prior result.

## Console usage

With an extracted and appropriately named user-owned resource directory:

```text
resource mount /absolute/path/to/extracted/resources
scene prepare miss16/m06.msn textures/example.vqm
scene status
scene activate
scene status
scene unload
scene status
```

`scene discard` drops the pending scene only. The original `terrain`,
`texture`, `color`, `level` and `resource` commands remain available,
and scene activation does not change the game world, synthetic level or
independent terrain inspector. The resource store still has no integrated
PIX/PAK/ZFS provider; files must already be supplied through memory or
directory mounts.

## Verification

`unit_retail_scene` constructs synthetic BWD2 WREV-9, WRLD, ZMAP/ZONE,
TER, ACT/LUM/TBL, VQM and CBK bytes. Tests cover revision/layout and name
bounds, missing resources, ownership/rollback, indexed sampling and missing
table distinctions, independent activation/discard/unload, console grammar,
world isolation and repeated runtime initialization.

`functional_scene_lifecycle` mounts generated directory fixtures and
executes the actual headless `i76` command path. Its setup is registered
under both CTest and Valgrind Memcheck labels so diagnostics have the same
source files available. No game files or reconstructed original images are
included.

```sh
cmake -S reconstruction -B build/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/debug --parallel
ctest --test-dir build/debug --output-on-failure
```

The next implementation milestone is to replace the explicit diagnostic VQM
with **verified material slot selection** from WRLD terrain variants,
TMT/VTF references and GEO/TER mapping, then construct renderer-neutral
geometry packets. That mapping requires additional original-instruction
proof and should not be inferred from filenames alone.
