# Provisional source-layout delta — rendering boundary

This is a linkage/data-flow hypothesis, not a recovered translation unit list.

- `004466C0`, `004469A0`, `00446C90` share GEO variant selector/cache/constructor functions. Cross-check merged v2.4.
- `00449680`, `0044AB90`, `0044AC80`, `0044A0B0` and `0044A290` operate on related but distinct TMT-descriptor, per-object hash-slot, VQM-cache and M16 cache records. The per-object texture-binding machinery demonstrably persists across geometry refresh.
- `0045CB80`, `0045CBE0`, `0045D100`, `0045D530` form a tightly connected native temporary render-record and depth-sort subsystem using globals `0054ACB8/BC` and `0054AD28`. The record slot format is separate from the persistent world object and GEO cache.
- `00471FD0` accesses callback tables `004F9538` / `004F8D38`, selecting `0047C2F0` / `00487EA0` for observed mode `0x15` in this emulated context. No claim that all table entries form one original source file.

Original source filenames/headers, linker units and ownership transfer to final drawing are unresolved. Avoid inference from address adjacency alone.
