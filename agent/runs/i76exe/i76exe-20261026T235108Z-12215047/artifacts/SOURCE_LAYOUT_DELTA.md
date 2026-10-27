# Provisional source layout: spawning versus VCF/VLOC callbacks

Retail instruction provenance: `00451180`, `004513C0` are adjacent gameplay/world-vehicle creation procedures, calling `004AD6F0` VCF load, `004572B0` registration and `0045EBD0` object allocation. A separate session/network state cluster owns local identifier `00541028` (`00452D40`, `00454E30`). VLOC attachment callbacks reside at `004AE000` and the camera reader at `00406AB0`.

The adjacency and cross-calls support a **hypothesized spawning-and-registration functional unit**, a **vehicle-resource callback unit**, and a **camera function cluster**. They do not prove original `.c`/`.h` filenames, precise compilation units, or any compiler-emitted source file boundary. Do not alter v97 Ghidra symbols automatically.
