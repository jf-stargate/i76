# Original versus controlled services

The run-owned Java source is the complete executable ledger. This table explains ownership; it does not turn supplied services into original engine behavior.

| Boundary | Ownership and limits |
| --- | --- |
| `0045EBD0`, `004AD6F0`, native VLOC/class binder, native GEO/TMT loaders, `004572B0` | Original instructions execute; node/class staging inputs, heap and byte-verified resource provider are controlled. Creator CALL is a boundary: original spawn-status basic blocks then direct VCF invocation, not uninterrupted startup. |
| `00493C50`, `00495000` | Original math initialization and approximate reciprocal-square-root math. No table injection or independent normalization. |
| `00405970→00472220`; `00472400` | Original projection creation/update, 118-dword copy; controlled color mode 2, 640×480 viewport, parameter 0, zoom 1 in callback. |
| `00406AB0→00437F90`, `00494E20`, `00458CB0`, `00472990→00494F70` | Original direct callback and matrix/hierarchy/view production, through full RET to sentinel; no callback-body replacement. |
| `00472D30` | Original downstream point transform, independently checked at supplied point (0,0,0). Not visibility, raster or presentation. |
| `0049D400` | Java Math sine/cosine, cast float32, return EAX/EDX. FCOS/FSINCOS emulator limitation. Logged camera calls; not hardware x87 parity. |
| `004BA090` | Read Ghidra ST0 80-bit representation, truncate with Java int conversion, shift ST0..ST6 from next register. Applied in projection init and camera callbacks. Supplied CRT/math boundary, not original `_ftol`. |
| Windows imports via IAT `004BC108/104/0E8` | Deterministic HeapAlloc/HeapFree and handle service; backing memory is emulated. No Windows heap behavior claim. |
| CRT imports `004BC238/28C/260/1F0/1E0/26C/254/210` | splitpath, strncpy, strnicmp, memcpy, toupper, strchr, strlwr, stricmp reproduced in Java at resource/construction boundaries. Case/path behavior only for bounded fixtures. |
| `0046FFC0/0046FEE0/0046FD40` | Hash-verified private fixtures supply open/size/release; no native archive I/O during emulation. Extraction separately verifies original ZFS and GEO/TMT content hashes. |
| `00477C20`, `004796A0/00470340/0044A0B0`, `00438A90` | Light registration, palette/render, nonownership target service return controlled success/zero. Their side effects are absent. |
| `0049C320` | Controlled linked-list node allocation, args retained in emulated memory. Native active-world registration still executes separately and owns actual entry `00542830`; it is not a synthetic active-world entry. |
| `004AEB90`, `004B0190/004B0150/004B0290`, `00467280` | Weapon callback/optional material side effects/equipment logger supplied success. No scientific claims about these omitted behaviors. |
| Dormant inherited cleanup boundaries `00461A20` null, `00449E60/00477E10`, `0049E0F0` | Scaffold retains explicit null unlink/render-release/cosine responses if reached. Used services can be audited in private full construction traces; no native body claim for intercepted services. |
| Controlled pose, velocity, timers, active entry | Exact values in report and events. No original physics producer or scheduler claim. Original `004FE428` mapped 0.06 remains; only `004FE420` is supplied as 0.016. |
| `reset`, `zero`, `guard` scenarios | Explicit negative/counterfactual writes, separately labeled; never mixed into positive persistent sequence. |

Persistent callback interception is limited to the two math boundaries. Their implementations write registers/return stack, not `004C2730` or smoothing memory. Every changed camera/smoothing dword is captured immediately after an original instruction step. Probe verifies no callback step changes the controlled root pose. The reset control intentionally writes camera/smoothing outside callbacks and emits `CONTROLLED_RESET`.
