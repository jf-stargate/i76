# Reconstruction handoff

Research proposal only. Independently implementable boundaries supported here:

1. `decode_vqm(resource, codebook, limits) -> IndexedTexture(width,height,pixels)`.
   Require exact token plane, bounded dimensions and CBK index checks. Use row-major
   4x4 tiles, high-bit solid fills and clipped right/bottom blocks. Return tightly
   packed owned indexes with separate metadata/provenance. Original count checks
   are unsafe; do not reproduce unchecked source reads or overflow.
2. `select_indexed_texture(frame_name, decoded_cache, preference, provider)`.
   Preserve cached-VQM-before-preference, caller-name-first when preference is
   nonzero, VQM size-selected dependency load, MAP fallback only before VQM is
   selected. Capture provider lease identity and use typed errors. A configurable
   modern recovery policy is separate from retail fallback behavior.
3. `OwnerMaterialSlot`: keep owner/material identity, TMT descriptor/frame index,
   current frame name, indexed texture reference, alternate M16 lease and dirty
   state separate. TMT resources and decoded texture caches have distinct lifetimes.
4. `SampleIndexed(texture, signed_fixed_u, signed_fixed_v)`: contiguous row stride,
   SAR16 then width/height-1 masks for these callbacks. Explicitly gate power-of-two
   wrapping or reproduce the original bitmask for other dimensions; do not silently
   replace it with generic modulo. Lifetime-aware row views avoid pointer-reuse bugs.
5. `ShadeWrite(texel, shade_row, runtime_lum)` and
   `ComposeWrite(texel, destination, runtime_tbl)`: exact byte-index contracts.
   Do not turn255 into generic alpha. Keep serialized and initialized tables apart.

The bounded experimental scripts are not a maintained renderer. They cover every
retail VQM shape with a bounded original decode sample, plus connected owner-slot
and indexed sampler operation for two real materials. General perspective planes,
clip intersection/UV propagation, native M16 decoding, selected scene palette,
full WinMain/frame scheduling and RGB display are still separate tasks.

Next investigation can reuse these interfaces without repeating the decoder:
load the already accepted authentic vehicle/GEO harness, retain real TMT owner
registration, replace its004474B0 substitute with the original path and the
recorded resource/CRT/heap adapter, then retain textured prepare/draw routines
through00471FD0. Inspect actual flags: the prior0x15 material path selects
00487EA0/00487480, whereas this run's diagnostic uses00485120 and004828E0.
Authenticate actual projected UV/q/shade planes before comparing a framebuffer.
The exact missing interface is original-produced command+0C..18/+40..5C and
span list under a valid surface/context, not VQM block reconstruction.

No canonical/reference/reconstruction files changed. A designated steward may
reconcile this with accepted PR131/133/134, lazy texture findings and renderer
promotions only after human acceptance of this research PR.
