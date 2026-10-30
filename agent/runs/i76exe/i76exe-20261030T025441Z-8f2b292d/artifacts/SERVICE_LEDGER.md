# Original versus supplied services

All retail executable-section bytes in the imported annotated program match the authenticated PE. Original instruction emulation is Ghidra 12.1.4; no original function or symbol is patched. The experiment stops at original `004937C0` entry. `evidence/results.json` lists observed service counts/PCs over the five scenarios (repeat separately matches primary).

| Operation | Original instructions retained | Supplied boundary / limitation |
| --- | --- | --- |
| Math startup | `00493C50` | Explicit direct invocation; not WinMain |
| WRLD / terrain load | `004B8A10`, `00493910`, original descriptor dispatcher/handlers, `00471400`, `00493080` | Private M06 bytes mapped at `41000000` / `40000000`; handler execution creates the page grid. No synthetic terrain page pointers |
| WRLD peripheral bodies | Main WRLD logic and eight property copies retained | `00423320,00477B00,00479780,004B8500,004908F0,00401540` return 0. Guard also permits unused `00478B30`. No graphics, audio, texture-load success claim |
| Palette resources | Original callers and error branches execute | `0046FFC0` returns null for t01.ACT/LUM/TBL; reporter `0042D5D0` logs and returns; three explicit reports per scene. Resource names/errors stay in private trace. No visual material/palette output |
| File mapping | Original `00471400` wrapper | CreateFileA, CreateFileMappingA, MapViewOfFile return controlled handles and authentic read-only TER mapping; sizes/identities checked independently |
| CRT | Original callsites | sprintf substitutes the observed `%s`; stat succeeds; guarded memcpy hook exists but is unobserved in final scenes |
| Numerical `004BA090` | Original callsites | C runtime ftol replaced with logged signed truncation/pop; no record writes. Finite integral lattice inputs are independently constrained by resulting source-grid checks; not full CRT/x87 equivalence |
| Sampler FISTP `004935EE/00493608` | Surrounding original height guard retained | Exact ST0/CW handed to host x87 FISTP, original stack destination written and x87 popped. Needed because Ghidra ignores requested rounding control. Python checks RC independently |
| Bounds FPATAN `00492EAF` | Entire original hull/visibility algorithm retained | Exact ST0/ST1/CW handed to host x87 FPATAN, result/pop returned to emulator. Exact host repeat and independent atan2 check. Raw negative case attempts original instruction and records failure |
| Allocation and view | Original terrain output writers/allocators | Zeroed or A5-poisoned scratch: XYZ `42000000` (1 MiB), aux `43000000` (1 MiB), arena `44000000` (4 MiB). Only base globals supplied. 118-dword controlled view and width descriptor are declared fixture inputs; not original camera outputs |
| Empty-region fill `00474EA0` | Original rejection branch retained | Log and return 0 without framebuffer write; below control proves region rejection, not fill behavior |
| Transform / walker / polygons | Retail static instructions audited | **Not executed or replaced.** Deliberate stop at `004937C0`; original leaves remain intact |

The production guard rejects harness/service writes intersecting `42000000..443FFFFF` after entry to `00490A00`. All service destinations are stack/CRT outputs; numeric services update x87/registers and sampler stack slots. Original `e.step()` performs all vertex/edge/leaf writes. The independent verifier checks every final vertex and leaf against original writer events, allocator arguments and authentic source bytes. Poisoned storage produces the same fully allocated arena and vertex bytes, preventing a prewritten mesh from serving as evidence.

No vehicle construction, world-object spatial producer/consumer, collision candidate list, backend clip/draw, texture decoder, OS surface or device service is executed as part of this run. No services write a synthetic render list. Ghidra empty x87-stack startup warnings are retained privately; no claim of full x87 hardware parity follows from the localized instruction oracles.
