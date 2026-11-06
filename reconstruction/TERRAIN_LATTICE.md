# Checked global terrain lattice

This reconstruction-only module adds a bounded, renderer-independent source
coordinate resolver over an existing owned `i76_terrain_scene`. It consumes
the accepted original-instruction research in merged PRs
[#140](https://github.com/jf-stargate/i76/pull/140) and
[#141](https://github.com/jf-stargate/i76/pull/141). It does not amend or
promote those research records.

## Coordinate contract

The original M06/M02 loader embeds an 80×80 ZMAP at (+24,+24) in a 128×128
runtime page-pointer grid. Every page is 128×128 little-endian 16-bit samples.
Global lattice X grows with ZMAP columns; Z grows with rows. For the 80×80
serialized area:

```text
global_x = 128 * source_column + local_x
global_z = 128 * source_row + local_z
runtime_page_x = floor((global_x + 3072)/128)
runtime_page_z = floor((global_z + 3072)/128)
world_x = global_x * 5
world_z = global_z * 5
world_y = double(raw_word & 0x0fff) * double(float32(0.1))
```

These are conceptual world positions, not an assertion that the original
renderer stores an intermediate world-space vertex array. Its source XYZ
retains lattice X/Z and low12 Y before a combined scale/view transform.

`i76_terrain_lattice_at` supports the complete checked runtime lattice
rectangle [-3072,13311] in each axis. Negative translated indices and
coordinates outside that rectangle fail without any original executable's
unsafe pointer access or flattened-row spill. The returned sample preserves
the raw word, decoded height, bit12 flag, class bits, source row/column,
runtime page row/column, local coordinates and TER page ordinal.

Source cells containing 0xff and all runtime-grid cells outside the
embedded ZMAP resolve to a **valid zero-filled default page**, represented
by `default_page`, `page_ordinal=0xff`, and a zero packed word. This
corresponds to the observed initialized original executable image, not a
general assertion about all later game writes to default backing.

The existing `i76_terrain_sample_at` intentionally retains its older,
serialized-ordinal contract in which 0xff returns false. The two functions
answer different questions; this PR does not weaken that interface.

Malformed active page IDs or incomplete owned TER allocations return
`invalid_scene`; invalid coordinates return `invalid_coordinate`.
Failures preserve the caller's output. A default is not a failed query.
A valid default with a genuine ZMAP coordinate retains that coordinate;
an address outside the 80×80 embedded area reports source row/column -1.

## Page boundaries

`i76_terrain_lattice_quad_at` resolves four lattice corners independently
in the original height sampler's source order: (x,z), (x+1,z), (x,z+1),
(x+1,z+1). No duplicated 129th border row is invented. Local 127 connects
to the neighboring page's local zero over one more five-unit lattice step.
Repeated page ordinals share data but not spatial positions.

A starting cell whose +1 corner is outside the checked 128×128 grid is
invalid. Within the grid, an active-to-default cell remains sampleable.
The separate original adaptive *surface-class boundary scan* can use
linear pointer arithmetic instead of four independently resolved pointers;
that algorithm is **not** implemented by this API.

## Deliberate numerical scope

`i76_terrain_lattice_position_at` returns a widened double view of
integer-lattice positions. It uses the exactly representable float32
height-scale coefficient cast to double, rather than decimal-real 0.1.

There is no interpolated world-height function yet. The accepted native
i386/x87 research revealed staged downward-rounded float32 stores and
extended-to-double admission rounding that ordinary `std::round`, simple
bilinear math, or earlier Ghidra FISTP-only correction do not reproduce
bit-for-bit. This coordinate-only stage does not claim that parity.

There are also no newly inferred mesh triangles, camera hulls, terrain UVs,
surface-class texture IDs, normals, roads, raster commands or world objects.

## Validation

`unit_terrain_lattice` uses authored three-page samples arranged across
horizontal/vertical/diagonal page seams. It covers packed attributes,
source and world orientation, page aliasing, valid defaults inside/outside
ZMAP, signed coordinate limits, both axes of invalid input, ownership,
malformed page indices, truncated storage, independent corner selection
and transactional failure behavior.

The existing `unit_terrain_scene` additionally calls the new API after
parsing a synthetic BWD2/TER scene through the real loader, verifying that
serialized and global accessor contracts coexist without persistent
resource leases.

No proprietary game assets, GZF project or private numerical traces are
committed. Subsequent adaptive terrain source-graph implementation can
consume this accessor while keeping rendering and simulation independent.
