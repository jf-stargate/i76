# Services, inputs and ownership

The authoritative implementation is `scripts/I76_DrawBoundaryProbe.java`. It derives from the accepted main copy of PR #73's probe, which extends the accepted PR #70 integration. This is run-owned research tooling, not a maintained renderer.

## Original execution

Vehicle construction/loading/registration, original camera initializer and two camera callbacks, visibility producer, original queue/bucket insertion and consumption, GEO traversal/builder, material lookup and polygon wrapper execute original instructions. Original C8D0 projection and secondary BF00 fallback remain original. This run removes the selected kind-6 CE40 replacement. Original CE40, arena initializer 472DF0, command constructor 472EE0, scanline dispatcher/implementation 473670/473960, edge constructor 472F20 and barycentric inverse 48D140 all execute. Original workspace thunk/constructor/growth 473620/4736B0/473760 execute. The finalizer extension executes original 473640/474380 and its native incremental span helpers through natural callback dispatch to 47CB00.

The 47CB00 entry is a deliberate boundary stop: no instruction of its body executes. No return value or successful pixel output is supplied there. The finalizer has not returned when this stop occurs; the trace labels it BOUNDARY_STOP. There is no host-written framebuffer and no generated image.

## Added services and context

| Boundary | Supplied action | Original ownership retained |
| --- | --- | --- |
| `004BA2FE`, retail thunk `JMP [004BC154]`, unmapped import target `000C0DD2` | Cdecl CRT allocation returns disjoint zero-backed memory, max request 1 MiB, bounded 4 MiB pool; 16-byte CD guard on each side | Original callers choose sizes; original constructor/initialization and edge/span/command writes run |
| `004BA2F8`, retail thunk `JMP [004BC150]`, unmapped import target `000C0DC2` | Cdecl delete acknowledges only a pointer from this pool; backing retained without reuse | Original workspace growth/copy chooses released pointer and all new bindings |
| Explicit startup call `00473620()` | Driver invokes an original startup thunk before queue production | Original code chooses 128 capacity and constructs/clears ten arrays and global state |
| Allocation zero bytes | Initial storage property, always identified as service-authored | Changed-byte trace is taken only after original steps; unchanged zeros are not attributed to original writes |

No direct raster-global, edge, command, span or existing allocation bytes are host-written. Draw allocations are exactly 5,120 + 12 + 65,536 + 20,480 = **91,148 bytes**, plus **128 guard bytes**. Original delete releases the initial 5,120-byte workspace; no backing is reused. Behind control allocates only the initial workspace. Original arena owns the command/edge/span records; allocation addresses and lifetime are verified. Guards are checked after every retired original step while native initialization/draw/finalization is active. Existing draw backing is additionally forbidden as a destination for every host write.

## Inherited supplied boundaries

These remain substantial and limit the claim to original-instruction emulation:

- Deterministic OS HeapAlloc/HeapFree, queue allocation services `00498940/00499CE0`, resource open/size/release `0046FFC0/0046FEE0/0046FD40`, and CRT string/path/memory helpers. Resources are authenticated retail ZFS extraction; absent optional dependencies return null. Original queues themselves are never supplied.
- Class-1 staging pointers, two controlled root poses, supplied active selected entry, delta `.016`, velocity `(2,0,1)` and angle inputs `(1,1,1)`. The target basis and Z=+50/-50 are controls; no complete physics or scheduler execution is claimed.
- Controlled 640×480/color-mode-2 camera initialization inputs, Ghidra ST registers/control setup, Java sine/cosine and truncation services for unsupported math. The resulting 472-byte camera is original-produced and sealed after the two callbacks. Hardware x87 parity remains untested.
- Zero-backed transformed-position and GEO-record scratch at `2E000000` (2 MiB) and `2D000000` (1 MiB); original code fills them. Queue depth-scan bound 4095 is supplied before sealing, not a fabricated bucket index. Original queue initializer requests 370000,128000,49152,49152,2880 bytes through its inherited backing services.
- Ancillary vehicle-light registration `00477C20`; palette/device/material refresh `004796A0/00470340` and construction-only `0044A0B0`; optional material effects `004B0190/004B0150/004B0290`; weapon boundary and ancillary cosine helper `0049E0F0`; optional rendering cleanup and target-context helpers. Native `0044A0B0` executes during producer/consumer phases. See the versioned probe for exact branches.
- VQM/M16 texture acquisition returns null; release helpers acknowledge it. Original null-texture material fallback produces the tested untextured polygon. There are no decoded textures or complete vehicle asset claims.
- Kind-10 initial selected BF00 is still a vertex-copy service and D110 still returns supplied success. Kind-6 secondary BF00 differs from the selected initial clip target and executes original code. CE40 is no longer serviced. No other kind's rendering is established.
- Windows FS/SEH segment backing and chain sentinel are supplied; original SEH instructions run in the emulator. This is not Windows execution.

The inherited optional null geometry-name read at `004461E0` is the sole uninitialized-memory warning in every final nonempty case. No new warning is hidden. The surface descriptor at `005DCEC0` is inherited and invalid for pixels: pitch/base contributions are zero. Palette/shade-table initialization is not authenticated. No substitute raster surface or color table is installed.

## Service ledger reconciliation

Accepted PR #70 intercepted projection and drawing. Accepted PR #73 removed C8D0 interception and clarified that kind-6 secondary BF00 was already original. This run removes exactly CE40's interception and progressively supplies its measured CRT dependencies and original workspace initialization. It subsequently invokes original finalization, stopping before the pixel callback. No accepted run, canonical reference or other worker workspace is modified. The complete inherited ledger remains available in accepted run `i76exe-20261031T002217Z-b156a7f6/artifacts/SERVICE_LEDGER.md`; the owned probe and this measured delta govern this run's claims.
