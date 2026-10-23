# Open technical questions after v2.4.0

1. Re-enable original `0044A0B0` geometry-change texture refresh with the real TMT-backed object slots and investigate the native MAP→M16/VQM lookup, palette translation and surface-to-material resolution.
2. Trace `0045CBE0`, `0045D100` and `0045D530` rendering preparation/dispatch using native vehicle body GEO and actual object-bound material records. Distinguish direct TMT frames from MAP/material fallback, and inspect ownership into the draw records.
3. Prove object-binding and TMT-reference release and reuse over geometry state changes, vehicle teardown and two sequential vehicle loads in one persistent retail state. The v2.4.0 runs use separate fresh emulators.
4. Unstub ancillary WEPN/light/geometry-change refresh and x87/palette services where needed. The optional `vpit_1.elt` is missing from the limited fixture map; distinguish optional lookup from actual installed resource availability.
5. The ZIX/ZFS/PIX/PAK path was validated independently in v1.4–v1.7; v2.4.0 supplies verified original file slices at the resource-service boundary. A future one-session integrated archive-bootstrap path is not yet proven and would need resource-service changes.
6. Runtime vehicle physics, component behavior, damage propagation, material animation and game-world rendering remain separate from validated asset and object construction.
7. The original `.c`/`.h` translation unit map is provisional. Function adjacency and common globals are evidence; alleged source filenames are not.
