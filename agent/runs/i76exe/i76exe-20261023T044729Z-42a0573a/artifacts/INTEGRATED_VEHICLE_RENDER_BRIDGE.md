# I76 original-code vehicle → GEO → TMT → raster boundary

**Research classification:** original x86 instructions executed in Ghidra 12.1.4 read-only EmulatorHelper on the retail `i76.exe` v97 annotated program. Research-only; no new engine implementation or native Windows process.

## Baseline and provenance

- Retail PE MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`.
- Private v97 Ghidra GZF SHA256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`.
- Retail `I76.ZFS` SHA256 `0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d`.
- Source research: merged `agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/` (native VCF/TMT/GEO v2.4.0), plus the newer *draft* renderer investigation `agent/runs/i76exe/i76exe-20261023T042231Z-4e59e782/` (PR #24). This run independently executes the integration; it does not rewrite or promote either earlier run.
- The v2.4 full-run regression was reproduced byte-for-byte (`9ea1c890ec8523464eccc572a018fb8a00a27447de053b4eeb49673a466826ce`). The expanded replay produced identical private trace hashes in two headless Ghidra runs (`cbaa3cc5b59ddd3f183d530478875776be455a2d518f2e3a5c84338239e6e911`).

## What the actual original code executed, in sequence

**Separate GTSi and bus process states:** Original `004AD6F0` constructs 46 and 44 world nodes, respectively, and binds 24 and 22 per-object TMT registrations from original retail resources. Native `004469A0`/`00446C90` processes GEO, and original `004466C0` selects exterior 0 → cockpit 4 → exterior 0, then cockpit 4 again. Unlike the merged v2.4 proof, original `0044A0B0` executes during each relevant geometry change; underlying VQM/M16 release services are still intercepted, not genuinely freed.

**Actual GEO source in live object memory:** The selected body node has an original-code-produced handle at `object+0x5C`, an original-built section list at `geometry+0x14` and a 16-bit/32-bit resource identity checked against independently extracted retail bytes. These are not synthetic section arrays. In the *same emulated process state*, original `0045CBE0` accepts the actual live body pointer, its object transform and a clearly marked synthetic identity-like renderer/camera transform. It runs original compose, transform, lighting and per-section record construction instructions into separately allocated scratch memory.

| Original GEO | Original vertex count | Original sections visited | Temporary record slots | Bytes advanced | Textured records sent downstream |
|---|---:|---:|---:|---:|---:|
| GTSi `AL11BDYM.GEO` exterior | 24 | 17 | 17 | 1,320 | 1 |
| GTSi `AL51BDYM.GEO` cockpit | 81 | 69 | 69 | 8,136 | 3 |
| Bus `XB11BDYM.GEO` exterior | 16 | 5 | 5 | 456 | 1 |
| Bus `XB51BDYM.GEO` cockpit | 169 | 93 | 93 | 15,240 | 0 |

The **184 slots are not 184 submitted polygons.** Some temporary section records have `vertex_count=0` and no owner/material payload, but remain linked into the native sort structure. That outcome is camera/transform-dependent; do not infer an inherent absence of these surfaces in gameplay. There are five textured records with counts ≥3 for which the harness calls original `0044A290` and then original `00471FD0`. The original complete scene traversal `0045D100` was **not** executed in this run; the authentic records were handed to the consumer functions with the same documented call arguments.

**Native owner/texture bridge (high confidence for exterior examples):** GTSi and bus native exterior GEO section material `V1 MD UN.MAP` has a real object/name keyed slot, a valid original-decoded retail TMT record, and first-frame names `al11mdu1.map` and `xb11mdu1.map`. The actual `0044A290` native call selects those first-frame names for original `004474B0` VQM acquisition. Pixel loading is intercepted and returns a synthetic pointer. This proves actual *slot ownership, frame selection and call argument*, not VQM decode success or color correctness.

**Cockpit distinction:** GTSi cockpit GEO has visible textured `V1 BO DY.MAP` records. The first encountered name had no preexisting object/TMT slot in the audited hash, so original `0044A290` followed the name-based fallback, invoked the intercepted VQM loader with `V1 BO DY.MAP`, and a subsequent native lookup found a cached owner slot. That is not proof a matching retail MAP file exists or that the dynamic fallback depicts a valid texture. The bus cockpit produced no textured record under this artificial identity camera pose; this cannot be generalized to authentic game view or all transform choices.

**Original submission wrapper:** For five genuine, nonzero records, original `00471FD0` reads the record corner buffer at `record+0x48`, the native material-loader return pointer, and draw flags `0x15`. It selects entry 21 (`0x15`) in its original dispatch tables: clip callback `0047C2F0` and draw callback `00487EA0`. The harness intercepts each callback, copies the input corner array to the clip temporary array and returns the input count, then intercepts the drawing callback. Original `00471FD0` returns `0x0800` in this controlled case, representing an FPU-control-related return value, **not** a successful native draw or pixel equivalence. The original raster functions were not exercised.

## Ownership and temporary lifetime implications

- Object identity is carried through to render record `+0x08`, while the material identifier is copied into render record `+0x0C` (15-byte source copy). The vertex/corner data follows from `+0x48`, a 24-byte stride. The record cursor advances `0x48 + 0x18*n` per section, including empty `n=0` records.
- Render records live in externally prepared scratch buffers and form a linked depth tree using `+0x40/+0x44`. Neither a separate render-record reference count nor ownership transfer to the graphics backend is demonstrated.
- Cached TMT descriptor registration survives geometry refresh in this experiment, while the subordinate VQM reference can be invalidated; corresponding actual reference releases and animations across Windows frames remain unverified.
- Hypothesized original code neighborhoods remain provisional: `00446xxx` GEO cache/selection, `00449xxx–0044Axxx` texture-owner bindings, `0045Cxxx–0045Dxxx` record construction and traversal, `00471xxx–00487xxx` raster submission. No original translation-unit names are asserted.

## Explicit experimental substitutions and follow-up

Synthetic: identity-like camera/render context, renderer scratch arrays, resource-provider/CRT/Windows heap services inherited from v2.4, palette/light auxiliary services, VQM pixel-acquire (`004474B0`), raster clip (`0047C2F0`), raster draw (`00487EA0`) and VQM/M16 releases. Ghidra reported uninitialized x87 state in legacy vehicle construction and SEH/FPU state at native `00471FD0`; no pixel-quality inference is made. The full renderer traversal, authentic camera matrices, M16 branch and actual VQM/CBK/MAP decoding remain open.

**Next native experiment:** establish an authentic initialized render context by tracing the caller of `0045D100`/`0045D530`, execute that entry with the live VCF body hierarchy, and replace the VQM and raster stubs progressively using actual retail resource bytes. Keep the raster state/primitive flags/ownership tests separate from image correctness claims.

Reproduce: privately extract fixtures with the merged v2.4 extractor, run `scripts/I76_IntegratedVcfRenderProbe.java` in Ghidra 12.1.4 read-only with arguments `<private-fixtures> <private-trace.tsv>` (twice), and run `scripts/verify_integrated_render.py` with private PE, ZFS, original v2.4 trace and two expanded native traces. Public `evidence/` contains only a derived summary, owner/material mapping, small opcode anchors and dispatch target tables; no proprietary resource bytes or full native instruction trace are committed.
