# Documentation impact — VQM/CBK to indexed software raster

Run i76exe-20261105T021753Z-998542c9; track i76exe; base
999fcc0798c7756bab34d0fa46e43bf2a21e8236. PR pending when packaged.
Original EXE/GZF identities and artifact hashes: manifest.json.

Classification: candidate update; **no canonical change in this PR**.
Targets: manual/reference/engine/software_renderer.md,
manual/reference/engine/resource_acquisition.md, RES/GEO/RND discovery indexes;
possible focused texture-format reference after reconciliation.
Historical locator: ref/material_format/i76_material_extraction_reference.md,
sections Direct Indexed MAP and VQM/CBK Decoding. Do not promote its exporter
palette, alpha, family-specific overrides or format preferences as retail rules.

| Finding | Evidence / method / confidence | Candidate impact |
|---|---|---|
| texture.decode | VQM_CBK_SPEC; decoder_comparisons;0044B430; O+B+D, high | Add tight indexed runtime representation and edge/token contract |
| texture.selection | TEXTURE_SELECTION; selection.json;004474B0/0044A290; O+S+X, high within controls | Narrow exporter VQM-first into actual preference/cache/dependency rules |
| texture.owner | RUNTIME_TEXTURE; execution.json owner_layout;0044AB90/0044AC80; O+B+X, high | Extend prior supplied-pixel material bridge through authentic decode |
| texture.samples | SOFTWARE_SAMPLING; original_memory_reads/stores;00485120/004828E0; O+B+X+D, high | Add bounded authentic textured framebuffer-index outputs, retaining supplied scene/planes/table-install limits |
| texture.m16 | TEXTURE_SELECTION; m16_observation;00471980; O+B+X, high at selection boundary | Add raw M16 alternative and distinguish unproven high-color decode |

Reconciles rather than invalidates prior runs: lazy-texture/cache invalidation
and integrated material ownership were original with substituted pixels; promoted
bus raster was untextured; PR133 table interpretation was static. This run adds
one-state diagnostic texture decode-to-indexed-store fixtures, not an original
scene/GEO-to-display frame. Safe malformed-input checks remain independent policy.

Defer general perspective precision, actual textured GEO dispatch/UV clipping,
renderer-global cache invalidation on reused addresses, M16 payload decoding,
scene palette selection, display RGB and full texture lifecycle. Evidence hashes
are listed in manifest.json; finding records link their reports and JSON.
A designated steward must reconcile merged evidence in a separate fresh-base PR;
only the human maintainer can accept promotion. Existing runs are immutable.
