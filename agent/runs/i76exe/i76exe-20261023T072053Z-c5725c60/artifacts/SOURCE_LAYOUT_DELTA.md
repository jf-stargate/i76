# Provisional source-layout note — active world vs render work record

Binary-proven, independent call-site neighborhoods:
- `00457100`–`00457630` owns 0x78-stride active-world registry/entry callbacks (`004572B0`, `00457420`). Entry pointer is a registry slot, not the world object itself.
- `00457FF0`–`00458784` classifies entries into per-frame render work through camera/context transforms and visibility; its type-6 branch calls `00490590` at one address and `0048FE10` from `004586BF`.
- A separate `0048F4A3` callsite inserts type-10 records, and `0048FAC0` processes buckets, dispatching type 6 by `0048F4C0` to the GEO hierarchy renderer.
- Renderer scratch and GEO traversal are around `0045CBE0`, `0045D100`, `0045D530`.

These are *functional neighborhoods*, not recovered original translation units. Function adjacency and shared state support hypotheses, not .c/.h file recovery. No symbol renames applied to the private program.
