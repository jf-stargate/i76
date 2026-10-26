# Provisional translation-unit map delta — scene pipeline

The sequence `00457FF0` (world-object visibility and work-record production) → spatial bin service → `0048FAC0` (cross-subsystem work-bucket draining) → `0048F4C0` (geometry subtype callback) → `0045D100`/`0045D530` (GEO tree sorting and traversal) → `0044A290` and `00471FD0` (material and raster pipeline) spans several different *functional* neighborhoods. It is not a single original source unit.

- `00457xxx`: active world registry and visibility/work-record preparation: moderate functional grouping, no recovered source file names.
- `0048FAxx`: terrain/dynamic spatial work bucket consumption and callback dispatch: strong functional neighborhood; original translation-unit boundary unproven.
- `0045CBxx–0045DAxx`: GEO scratch record/depth ordering, primary/secondary passes: strong functional neighborhood; physical code placement is not sufficient to assert a source module.
- `00447xxx–0044Axxx`: texture names, owner slots and VQM/M16 cache: cross-module calls, previous v2.4 and PR #24/#26 evidence retained.
- `00471xxx–00487xxx`: clipping/raster dispatch and optional hardware/DirectDraw callbacks: not yet deeply executed.

Do not infer developer-authored `.c`/`.h` names, independent lifetimes, or object ownership from these proposed subsystem separations.
