# Service and substitution ledger

| Boundary | Treatment in this experiment | Research effect |
|---|---|---|
| Retail EXE functions in probe | Emulated original instructions, including stock vehicle construction/registration, camera callback, visibility producer/consumer, GEO traversal, polygon wrapper, and kind-6 `0047C8D0` | Native control/data flow retained in a single emulator per case. |
| kind-6 callback `0047C8D0` | **Original body**; removed the accepted probe's `SERVICE_CLIP` handler only when `currentKind==6` | Writes projected vertex records and returns count; captured source/destination/return bytes. |
| kind-10 callback `0047BF00` | Existing substitute retained: copies source array to destination and returns input count | It is reported explicitly and is not part of the native-success claim. |
| kind-6 draw `0047CE40`; kind-10 draw `0047D110` | Existing draw services retained; return success | No raster command, framebuffer or pixel claim. |
| Texture acquisition `004474B0` and related texture path | Existing documented service behavior | Material/texture inputs are not native renderer resources. |
| Camera/visibility math and selected depth range | Probe's established controlled values, CRT/math services as documented in the accepted run | Valid for the controlled trace only. |
| GEO/material/archive, allocator, OS, CRT | Existing accepted probe's documented fixture/resource/allocator/import services | Original GEO object/sections and vertex bytes are loaded and traced; surrounding service boundary remains harness-controlled. |
| Renderer scratch | Supplied position/record scratch at `2E000000` / `2D000000`; queue and view host-write guards enabled | Source array `2D000528` or `2D000480`; native projection destination `3001C76C`; no host queue mutation after sealing. |
| Ghidra emulator | Ghidra 12.1.4 `EmulatorHelper`; isolated private project/config/cache | Not hardware execution; one observed inherited warning at `004461E0`. |

Every callback treatment is visible in `scripts/I76_IntegratedClipProbe.java`. No synthetic polygon is constructed: the two four-vertex wrappers arrive through the accepted original producer/consumer/GEO path.
