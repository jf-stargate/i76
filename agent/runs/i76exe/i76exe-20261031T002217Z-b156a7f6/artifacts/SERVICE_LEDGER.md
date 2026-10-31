# Original instructions and supplied boundaries

The owned Java source is the exact service implementation. Inherited scaffolding derives from #66, camera methods from #67, and renderer observations from the earlier synthetic consumer; all are experimental research tooling, not maintained reconstruction.

| Boundary | Treatment |
| --- | --- |
| `00493C50`, `0045EBD0`, spawn-status prefix, `004AD6F0`, `004572B0`, original list/class/GEO/TMT routines | Original instructions, actual retail resource bytes. Class-1 staging bindings and controlled poses are explicit. Two separate roots and registries; no original pending-init/post/scheduler claim. |
| OS heap imports and `00498940/00499CE0` | Deterministic zero-backed allocation; original constructors/arena initializer perform their own writes. HeapFree is acknowledged without real OS semantics. |
| `0046FFC0/0046FEE0/0046FD40` | Supplied private hash-verified resources, size and ref release. 64 inherited subset plus camera `hdlv_msk.geo`; absent dependencies return null and remain in private chronology. No claim of full archive loader or complete vehicle assets. |
| CRT imports | Supplied memcpy/strncpy/string comparisons/case/path helpers. All bulk writes pass queue/view overlap guards. Producer's actual additional service is case-insensitive comparison of already prebound headlight variant; it neither creates nor inserts work records. |
| `00477C20`, `004796A0`, `00470340`, construction `0044A0B0` | Supplied ancillary light registration, palette/device/material refresh. Original `0044A0B0` executes during visibility/consumption; light registry remains empty. |
| `004B0190/004B0150/004B0290`, WEPN boundary, `0049E0F0` | Inherited optional material effects/weapon behavior/cosine-dependent ancillary helper services. No complete weapon behavior or hardware numerical fidelity. |
| `00405970`, `00406AB0`, `00437F90`, `00472990` | Original instructions. Java sine/cosine and truncating float-to-int with Ghidra ST-register shift replace unsupported numeric services. Initial ST registers zero/control 037F supplied; not x87 parity. |
| Camera inputs | 640×480/color mode 2, active selected entry, delta=.016, velocity=(2,0,1), integer angles=(1,1,1), retail mapped camera mode 0. Root poses controlled. Full persistent view and smoothing are native callback outputs; no host camera writes after callbacks. |
| Renderer support | Supplied transformed-position/render-record scratch `2E000000/2D000000`, separate from original queues. Depth range near=0/far=4095 supplied before sealing; no original terrain range scheduling claim. |
| `00457FF0`, `00490590`, `0048FE10`, `0048FAC0`, `0048F4C0`, `0045D530`, `0045CBE0`, `00490640`, `00471FD0` | Original bodies, original queue mutation and original polygon wrapper. Retired original queue dword changes observed. Never a supplied kind/owner/link/count/head/index or primary-pass override. |
| `004474B0`, `00471980`, texture release helpers | VQM/M16 acquisition returns null; release acknowledged. Original material lookup and null-texture fallback execute. No decoded textures or source-to-texture image claim. |
| Selected clip/draw callbacks | Kind 6: `0047C8D0/0047CE40`; kind 10: `0047BF00/0047D110`. Clip service copies 24-byte vertex records unchanged and returns count; draw service returns success. These are **substitutes**, not native clipping, raster output or pixels. |
| FS/SEH | Supplied FS_OFFSET=`3C000000`, zero-backed local segment with -1 chain sentinel. Original wrapper SEH reads/writes execute; no actual Windows SEH. |

One inherited optional null geometry-name read at `004461E0` remains in every nonempty process. No other uninitialized-memory/register warnings occur in the final replay. Construction completion does not certify every vehicle field. The report distinguishes the rejected camera-owner kind-10 scratch lifetime from accepted records and accounts for original kind-10 +0x3C clearing.


## M-RND-04 measured delta

This inherited ledger describes baseline setup and services. The versioned `I76_PolygonBoundaryProbe.java` is authoritative for this run. Exactly one existing replacement is removed: `0047C8D0` executes original instructions for original kind6 polygons. All deterministic heap/resource/CRT, optional construction, math, texture and draw services above remain. Actual original camera projection parameters and persistent view are retained.

The accepted interception tests only `pc==selectedClip`. Therefore kind6's later `0047BF00` at index1 was already original, not substituted. This run captures its natural entry/return and draw input; the inherited broad ledger row must be read with this qualification. Kind10 initial BF00 still equals selectedClip and is substituted. CE40 and D110 draw callbacks still return supplied success. C2F0/87EA0 are audited but not executed.

Original C8D0 leaves destination +12/+16 unchanged. These stale words are not validated UV. The viewport descriptor's first dimensions are zero, so wrapper fallback is not evidence of a properly configured raster surface. We preserve that setup and report it. No new dependency service is introduced in final evidence. Supplied zero-backed renderer scratch, depth-scan bound and Windows FS/SEH segment remain experimental setup. There are no native pixels or decoded textures.
