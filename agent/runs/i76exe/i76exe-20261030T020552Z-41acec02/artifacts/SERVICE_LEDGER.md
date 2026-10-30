# Original instructions and supplied services

| Boundary | Treatment and limits |
| --- | --- |
| `0045EBD0`, `004AD6F0`, original child/GEO/TMT constructors/binders | Original instructions with measured retail resource bytes; class-1 staging context/root binding supplied after original root construction. Full pending initialization is not run. |
| `0049C320`, `00461970`, `004572B0` | Original list insertion, class registration and world registration; heap supplied. No manually authored world entry or class-list node. |
| HeapAlloc/HeapFree imports | Deterministic zero-backed emulated memory/return values. Original object constructor still initializes the root/children. No real OS heap semantics claimed. |
| `00498940`, `00499CE0` | Deterministic allocation service (events named ARENA_ALLOC, including five pre-arena construction allocations). Original `0048F9B0` writes arena globals and clears tables. |
| `0046FFC0`, `0046FEE0`, `0046FD40` | Private byte-verified retail resource supply, size and release-reference service; missing optional resource returns zero. No original archive I/O execution claim. |
| CRT imports | memcpy, strncpy, strnicmp, stricmp, strlwr, splitpath, strchr, toupper supplied in Java; unused or ancillary Win32 paths remain visible in source. |
| `00477C20`, `004796A0`, `0044A0B0` | Construction light registration and palette/render refresh supplied; light registry remains empty. Renderer/device/decoded texture correctness excluded. |
| `004B0190/004B0150/004B0290`, `004AEB90`, `0049E0F0` | Optional material effects, WEPN boundary, and inherited cosine-dependent ancillary helper supplied during construction. WEPN returns success; no complete weapon behavior. Cosine helper returns zero without establishing hardware x87 semantics. |
| Spawn formatting `004AD640` | Return boundary while original status instructions execute; no original name formatter claim. |
| Original projection `00405970 → 00472220` | Controlled viewport/color/mode argument; `0049D400` Java sine/cosine, `004BA090` truncating conversion with Ghidra normalized stack pop. No hardware x87 parity. |
| Original math seed `00493C50` | Executed before construction/projection. Emulator initial ST registers zero/control 037F explicitly supplied. |
| Root translation +0x50 double | Harness-controlled +50/-50 before original bounds registration. Actual position/basis provenance is explicit, not a physically evolved pose. |
| `00457FF0`, `00477ED0`, `00494BE0`, `00472D30`, `00472C10`, `00457F40`, `00490590`, `0048FE10` | Original bodies execute during producer, including headlight branch. Any intercepted return, helper scalar write or memory allocation while producer is active throws. No queue service, synthetic record or bucket write. |
| Render consumer/clip/draw/WinMain | Not invoked in this milestone. No output/pixel/scheduler claim. |

The owned Java source is the exact service implementation and event logger. Some inherited service branches are dormant in the four final scenarios; complete raw service chronology remains in private TSV. One optional geometry-name null read at `004461E0` remains during construction. Returning through serviced construction does not certify every vehicle byte or resource dependency.
