# Indexed textures and color assets — read-only reconstruction slice

This independently authored module extends the existing `i76_assets` resource
store. It introduces owned VQM/CBK indexed textures and ACT/LUM/TBL color data
without installing a renderer, replacing the synthetic level loader, or changing
world/session state.

The original-executable research sources are candidate PRs
[#135](https://github.com/jf-stargate/i76/pull/135) and
[#136](https://github.com/jf-stargate/i76/pull/136), together with previously
accepted ACT/LUM/TBL analysis
[#133](https://github.com/jf-stargate/i76/pull/133). Their evidence must be
reviewed separately. This implementation is not a promotion record or proof of
full retail compatibility.

## Asset decoding

`i76_texture_decode(vqm, cbk, output, error)` expects VQM width and height
as little-endian words at offsets 0 and 4, a NUL-terminated dependency name at
offset 8, and block tokens beginning at 24. CBK declares its 16-byte tile
count in the first DWORD and stores tile bytes beginning at 4.

Each 4x4 block token either references a tile by its ordinal or, when bit 15
is set, repeats the low eight bits as a solid index. Blocks traverse
left-to-right in four-row groups; right and bottom edges are clipped.
The output is a tightly packed `width * height` vector of palette indices.
It does not contain RGB conversion, alpha inference, row padding or mipmaps.

Our bounded reader rejects source height flags, missing NUL, mismatched token
or CBK extent, invalid tile ordinals, zero dimensions and outputs larger than
4 MiB. The original retail decoder does **not** implement all these safety
checks; the bounded policy is intentional.

`i76_texture_read(resources, name, output, error)` accepts an explicit
`.vqm` name, acquires it from the already mounted memory or directory
providers, resolves its declared CBK name relative to the VQM directory and
decodes both. Both transient leases are released on success or failure.
A failed operation leaves the previous owned output unchanged.

This is not yet the original TMT owner-slot, VQM/MAP preference, PIX/PAK
mount or decoded-resource cache. The existing resource provider's safe leases
remain authoritative. Retail scene/vehicle activation is still unavailable.

## Indexed colors

`i76_color_read` can acquire a required ACT plus optional LUM/TBL names,
validating an exact 768-byte ACT and 65,536-byte remap tables. ACT triples
remain raw RGB8. A supplied LUM is copied without generation or correction.
For TBL, the active copy replaces source row 255 with the identity map
`TBL[(255 << 8) | destination] = destination`; the original resource bytes
are not modified.

`i76_color_shade` selects row offset `accumulator & 0x1f00` and source
index as column. `i76_color_compose` selects TBL source in the high byte,
destination in the low byte. No universal transparency rule is applied.
Missing tables return false and preserve the output parameter.

The complete conditional null-LUM arithmetic in #136 can inform a later
generated-table implementation. Exact historical gamma correction still
depends on unverified MSVCRT/x87 semantics; it is deliberately excluded.

`i76_texture_sample` provides the verified arithmetic-shift and bitmask
sampling policy for power-of-two texture dimensions. It rejects other
dimensions rather than silently treating the retail bitmask as modulo.

## Developer inspection

With a directory containing VQM and CBK files:

```text
resource mount /path/to/extracted/assets
texture inspect textures/a.vqm
color inspect palette.act shade.lum blend.tbl
color inspect palette.act
color inspect palette.act - blend.tbl
```

These commands decode, report metadata and release resources immediately.
They neither prepare a level nor change the active world. Directory mounting
remains case-sensitive for actual Linux filenames; logical keys are normalized
to lowercase. Embedded PIX/PAK resources require a separate future provider.

## Testing

```sh
cmake -S reconstruction -B build/i76-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/i76-debug --parallel
ctest --test-dir build/i76-debug --output-on-failure
```

`unit_indexed_assets` uses authored fixtures for mixed tile/solid decoding,
edge clipping, short/extra records, invalid dimensions and token references,
CBK size checks, signed fixed-point sampling, ACT/LUM/TBL lookup semantics,
missing dependencies, rollback and resource lease cleanup.

`functional_texture_inspect` mounts a generated synthetic directory and
executes the real headless console command. No proprietary resources or
retail decoded images are included in the repository.
