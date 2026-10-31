# Executed original code and supplied boundaries

All code sections are authenticated against retail PE after private GZF import. No retail instruction body is patched. The two owned Java files are the exact executable service definitions. Camera base derives from immutable #67; terrain loader/step observer derives from immutable #74. The C x87 helper is byte-identical to #69/#74. These are experimental research tools, not maintained reconstruction.

| Boundary | Treatment / limit |
|---|---|
| `0045EBD0`, spawn-status blocks `00451452..48B`, `004AD6F0`, `004572B0` | Original construction, original selected-status prefix, stock resource parsing and world registration. Class staging, direct entry and optional services inherited from #67. Not full spawning, selected initialization/post or physics. |
| OS HeapAlloc/HeapFree imports | Deterministic private zero-backed memory/ref acknowledgement. Original root/node/class/GEO constructors retained. No Windows heap/SEH lifecycle claim. |
| `0046FFC0/0046FEE0/0046FD40` during vehicle load | Exact authenticated 64-resource stock fixture set from accepted ZFS extractor; bounded resource pointer/size/release services. Absent optional dependencies remain absent. All fixture hashes independently checked. |
| Vehicle CRT/resource/light/weapon/material auxiliaries | Exact inherited #67 boundary services: path/string/copy, optional light registration, palette/device refresh, optional material side effects, weapon chunk handling and unsupported ancillary cosine helper. No complete vehicle behavior/texture/lighting claim. |
| `00493C50`, `00405970(0)`, `00472220/00472400/00472530`, `00406AB0/00437F90/00472990/00494F70` | Original math startup/projection/camera/inverse writers. Controlled viewport, root pose, active-entry assignment, dt/velocity/angle inputs. Standard x87 CW=037F supplied at emulator creation; no mid-scene FP-state reset. |
| `0049D400` | Java sin/cos service returning float32 in EAX/EDX at original boundary; original callsite and surrounding FOV/camera arithmetic execute. Not hardware FSINCOS parity. |
| CRT `004BA090` | Explicit signed truncation/pop from emulated ST0; original callsites retained. |
| M06 WRLD/TDEF/terrain mapper/init | Original bodies on authenticated MSN/TER, exact supplied file handles/mapping. WRLD graphics/audio/texture peripherals omitted as #74; palette resource acquisition returns null and original error paths execute. |
| `004935EE/00493608`, `00492EAF` | Same narrow FISTP/FPATAN host x87 instruction services as accepted #69/#74. Exact emulated ST0/ST1/CW forwarded. Original terrain selection/height/subdivision bodies retained. |
| Source scratch bases | Supplied XYZ/aux/edge-leaf backing at `42000000/43000000/44000000`; original builder resets cursors and creates all geometry. Host writes to geometry/renderer output/camera are guarded after production begins. |
| `0048F9B0` | Original allocator initialization. Services only at `00498940/00499CE0` return zero backing at `48000000..48400000` for five original requests. Original pointer installation and bucket stores retained. No OS reserve/commit/capacity lifecycle claim. |
| `00490A00/004937C0/00494E20/00491A30/004922F0/00490590` | Original selection, adaptive geometry, transform composition, transform, leaf reader, emitter and allocator. Same persistent original camera pointer. No supplied projection, corners, view translation, work records or source indices. |
| `0047BF00/0047B8C0` | Original near/far classification and clipping, original projection, original screen clipping. Rejections and accepted outputs independently verified. |
| Imported memcpy from original caller return `0047BEDF` | Exact bounded copy of original clip-stack bytes to `currentRecord+1C`. Guard requires original caller, original stack, current record and <=32 vertex records. This external service writes final output bytes; it performs no geometric arithmetic and authors no polygon. |
| `0048FE10` | Original insertion/cursor/link/bucket arithmetic and stores. Complete final chains independently traversed. |
| `00474EA0` below-height rejection | Original rejection reaches fill boundary; log/return service, no framebuffer. |
| `00403E64/00401C90/00401CC0/00401FA0`, `0048FAC0` and allocator service bodies | Source audited only. No full frame, queue consumption/reset, draw-command production or raster execution. |

The inherited optional null geometry-key read at `004461E0` and uninitialized ST startup warnings at `00438340` remain explicit construction limitations. CW is initialized before construction, fixing the exploratory external-service failure; x87 register warnings are not silently recast as hardware fidelity. No original physics-produced root pose, mission spawn or selected-player scheduler event is inferred from callback execution.
