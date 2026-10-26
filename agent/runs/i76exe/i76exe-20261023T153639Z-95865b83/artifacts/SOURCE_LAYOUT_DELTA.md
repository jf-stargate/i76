# Provisional source-layout refinement — NOT recovered source files

The camera projection `00405970`, camera follow/mode callbacks `00405B90`, `004061B0`, `00406920`, `00406E00`, `00406F30`, `00407500` share the global camera record at `004C2730` and controls near `004C2918`–`004C296C`, suggesting a camera-mode subsystem neighborhood. The span crosses nonadjacent utility functions; no original `.c`/`.h` boundaries are recovered.

`0048F2B0`, `0048F4C0`, `0048FAC0`, `0048F9B0`, `0048FE10`, `00490590`, and `00490640` use the same render-work record/bucket memory and dispatch table at `004FACA8`. The type-10 consumer at `00490640` is original executable code lacking a defined function in the private v97 listing; recommend guarded function-creation in a future Ghidra annotation proposal after checking code boundaries and cross-references.

Separate GEO-generation, material-resolution and backend clipping routines at `0045CBE0`, `0044A290` and `00471FD0` are connected by callers but function adjacency alone does not establish a single translation unit.
