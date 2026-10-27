# Milestone B: constructor-initialized root through native registration and original camera

**Evidence classification:** original-retail-x86 emulation against verified stock GTSi and bus resources; numerical parity and live Windows rendering remain **unproven**.

- Run: `i76exe-20261027T031313Z-32de4d1e`; base main: `5da264c093a9d694a7d5e36f4be62c3a26b5b0fb`; protocol 1.0.3; private Ghidra 12.1.4 annotated v97.
- Earlier related *separate draft proposals*: PR #46 (default camera execution and NaN origin), PR #47 (isolated `00437F90` and original constructor contract). Their existing runs were neither modified nor presumed merged.
- Retail executable MD5 `a640ea0097dbb62e0c77b7f2847c7161`; executable SHA256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`; private v97 GZF SHA256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`; original I76.ZFS SHA256 `0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d`.

## Experimental setup: original instructions versus supplied state

Original `0045EBD0` world-node constructor runs through its instruction body. The Windows HeapAlloc service is intercepted and supplies a fixed, emulated `0xB0`-byte object at `26000000`; the constructor copies the **16-dword transform** from original retail constant `004FAED8` into `object+0x18`, leaving its initial `object+0x30..0x38` direction `(0,0,1)`. The test then binds a controlled class-1 context pointer to that constructed root, as required to enter the original VCF loader. This stage is not uninterrupted game startup.

Original vehicle selection instructions `00451452..0045148B` assign the low status policy. Original `004AD6F0` is **explicitly invoked in the same emulator state**, not reached by stepping continuously through the caller's CALL. It processes byte-verified original stock VCF/VDF/VCFC/WDF/CDF/TMT/GEO resource fixtures, invokes VLOC type `0x28`, original node constructor `0045EBD0` for child objects, and original class binder `00461970`. Selected vehicles obtain an original class-0x28 attachment at `runtime+0x398` (observed `27000800`). The VCF load preserves the original root's identity direction exactly.

Original `004572B0` registers the fully built vehicle. It creates active-world entry `00542830`, stores the real constructed root and changes its observed reference count 3→4. The camera's active-entry pointer `004C2908` is set to this **native registered entry**, not a fabricated entry. Original `00405970` projection init then executes with controlled 640×480 viewport. Original default camera callback `00406AB0` runs through `00437F90`, `00472400`, `00472990` and normal return `00406DF4`.

**Substitutions:** original Win32 heap/service calls use deterministic emulated return values; original retail archive/resource-provider I/O, palette and ancillary services use recorded fixture boundaries. Original sine/cosine helper `0049D400` and x87-to-integer helper `004BA090` are substituted at explicit numerical boundaries. Frame timers are synthetic. No engine scheduler, real physics tick, original Windows API behavior, raster or hardware x87 parity is claimed.

## Original x86 differential: only constructor-root status changes

All listed camera cases follow original active-world registration. Controlled selected-bus tests **both register a real class-1 object and both retain a valid class-0x28 attachment**. Their material resource loading, camera projection initialization, and post-guard camera instructions execute; the distinguishing root variable is whether original `0045EBD0` initialized the root 16-dword transform.

| Case | Root direction before and after VCF | VLOC +0x398 | `00437F90` invalid float32 (of 16) | Camera `004C2890..004C28BF` invalid doubles (of 6) | Camera callback behavior |
|---|---|---|---:|---:|---|
| Selected bus / native root / original registration | (0,0,1) | class-0x28 | 0 | **0** | 4,428 steps; normal return; updates 143 bytes |
| Selected GTSi / native root / original registration | (0,0,1) | class-0x28 | 0 | **0** | 4,444 steps; normal return; updates 136 bytes |
| Selected bus / zeroed root / original registration | (0,0,0) | class-0x28 | **9** | **6** | 4,433 steps; normal return but view invalid |
| Unselected bus / native root / original registration | (0,0,1) | null | not entered | 0 (prior initialized state) | 40-step null-guard exit; 0 bytes modified |

The original registration step preserves the constructor-established root direction for both vehicles. The class-1 camera matrix helper `00437F90` receives that direction, invokes the projection/basis helpers, and returns a 16-float matrix with **zero non-finite values** for both native roots. With a zeroed root it returns nine NaNs, which propagate into **all six** tested camera-state doubles. The six native-root doubles are finite. The unselected vehicle's finite doubles represent retained initialized camera state, not a successful follow-camera update.

Camera-state doubles are taken from `004C2730+0x160..+0x18F` at the post-callback boundary. Retail `00472990` explicitly copies source doubles into `+0x160..+0x177` and computes transformed doubles at `+0x178..+0x18F`. The six-double diagnostic therefore checks a structured view-state region, not 32-bit float reinterpretations or an arbitrary byte sample. Selected bus values: `[-0.407675027847,2.02251482010,3.47027873993,-150.592023998,199.657567407,154.082328373]`; GTSi values: `[-0.407675027847,1.25139272213,-0.427281379700,-150.592023998,198.886737488,150.185385091]`. These are **emulated values**, not real gameplay camera coordinates.

## Reproducibility and remaining risks

- **196/196** independent verifier assertions covering verified retail PE/GZF/ZFS identities, **31** sparse original retail PE opcode anchors, original world registration, native construction, VLOC attachment, camera-path events, source-versus-derived evidence tables, six-double numerical checks, and independent byte-identical selected-bus Ghidra traces.
- Independent selected-bus original-instruction replay SHA256 `a45f7e7a989f9fd104431f965cb0a86a149cde2cc0a42e093964e5cc10f0b424`. Both executions yield the same 432-byte camera-state SHA256 `a14577d65af45eeb985bd234f1bb8fe34d0f8a1eca79a82184dc09b17a99e581`.
- Ghidra warns about uninitialized x87 registers near `00438340` and private resource-state reads elsewhere. Finiteness proves neither physically accurate pose nor orthonormal matrix, and x87 approximation/rounding remain unresolved.
- The original VCF resource loader is entered explicitly after the spawn status policy (not through a single uninterrupted creator CALL). The original camera callback is entered explicitly and frame inputs are synthetic. Player runtime lifecycle, game-world physics/pose update, full camera mode scheduler and renderer frame are **not** integrated.
- Original `00437F90` changes persistent smoothing globals. Multiple sequential frames, class-1 runtime updates, possible zero/parallel axis later in gameplay, and tolerance/hardware parity are not yet established.

**Conclusions:** The original node constructor's transform initialization is **necessary for finite output** in the tested differential, and preserves a nonzero projection axis across original VCF loading and original active-world registration. **The previously observed NaN chain is resolved for both stock vehicles in this controlled integration.** The broader Milestone B demand for hardware numerical parity and authentic world-camera pose remains open; this run is a reproducible submilestone, not claimed completion of B/C.
