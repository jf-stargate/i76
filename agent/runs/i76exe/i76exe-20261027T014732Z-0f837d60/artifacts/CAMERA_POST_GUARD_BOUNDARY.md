# Original retail camera callback: completion and first non-finite matrix boundary

**Track:** `i76exe`. **Run:** `i76exe-20261027T014732Z-0f837d60`. **Base:** `5da264c093a9d694a7d5e36f4be62c3a26b5b0fb`. **Protocol:** 1.0.3. **Schema:** 1.1.0.

## Direct original-code result

The original VCF/VCFC/VDF/VLOC/TMT/GEO loader `004AD6F0` was run in Ghidra against byte-verified original GTSi (`noal01.vcf` / `valeprec.vdf`) and bus (`nobus1.vcf` / `vxbus.vdf`) resources, preserving original `0045EBD0` node initialization, `00461970` class/runtime binder and VLOC type `0x28` handler. The creator's original selection block `00451452..0045148B` was stepped first; the full VCF loader was then explicitly invoked in the **same emulated state**, not continuously through the creator's CALL. The camera active-world entry `004C2908` was a **controlled synthetic entry** pointing at the native-constructed world object; original active registration was not repeated in this experiment.

Original default-camera callback `00406AB0` then executed beyond the `00406B13` attachment guard through original world/attachment transform composition and normal return at `00406DF4`. The selected bus used **4457 original/intercepted-boundary steps**, the selected GTSi **4473**. Both reached original `00493E60` quaternion/trig matrix, `00437F90` world transform, `00494E20` matrix multiplies, `00458CB0` attachment transform, `00472400` camera update, and `00472990` persistent view composition. The two repeated selected-bus full original-instruction trace files are byte-identical (private SHA-256 `e8587a9ede32236bdd7dd9ae5c350147510db612e3a1cd874236a4d5f8b2f2db`). The unselected bus returns after **40** callback steps, before transforms, without altering the tracked camera bytes.

**These are not full unsubstituted game instructions:** Win32 resource, CRT/heap, palette and ancillary subsystems retain the prior harness substitutes. Ghidra cannot run `0049D409` FCOS; the original `0049D400` trigonometric service was intercepted with Java `Math.sin`/`Math.cos` and returned through original register ABI. The `004BA090` x87 floating-to-integer helper was intercepted with a modeled 80-bit decoding/cast. Controlled frame-timer integer fields were set to one. Thus no retail Windows, faithful x87 or physically correct camera is claimed.

## Independent projection initialization experiment

Executing original camera projection constructor `00405970` with a **controlled 640×480 viewport** in the same vehicle state completed in **2708** emulator steps, before the original default camera callback executed for **4433** more steps. The callback changed 80 of the checked 432 camera bytes, compared with 140 without prior camera initialization. The selected control sets `005367A4` to `0x00010000`; in the unselected callback, this flag remains zero and no camera bytes change.

The resulting view remains **numerically invalid**: camera fields at `004C2894` and `004C289C` carry high words `7FF80000` (quiet NaN doubles). The original `00472990` call was reached but did not yield a valid world/view projection.

## First failing matrix boundary (original x86)

The native matrix at the original `00493E60` return / caller address `00406D27` had **zero non-finite float words** in its 16-word snapshot. Original `00437F90` consumes the tracked world object from `*(active_entry)` as its second argument, and its result at `00406D45` had **nine non-finite float words**. The following `00494E20` matrix multiply result at `00406D6F` had **12**, and the matrix after the later combine at `00406DB6` had **13**. These are controlled-emulator observations, not statements about the retail game under a real initialized world transform.

This localizes numerical corruption to the world-root transform boundary **before** the camera consumes the final matrix. An incomplete root-world basis, missing parent transforms and/or Ghidra x87 behavior are candidate causes; **none is yet uniquely established**. An experimental identity-basis full replay timed out before it reached camera execution and is excluded from the passing evidence.

## Independent verification

The included `scripts/verify_camera_postguard.py` re-checks original PE, private v97 GZF and ZFS digests, exactly 31 sparse original retail opcode anchors, successful selected/unselected branch events, native projection initialization, transform-stage nonfinite values, and byte-exact repeatability of two private full traces: **157/157 assertions passed**. The public repository contains **no retail original executable/resource bytes, private GZF, or full original-code traces**. The private traces and verified resource fixtures are necessary to reproduce results; research reproducibility status is **partial**.

## Next test

Run the world-transform helper `00437F90` with an originally initialized, nondegenerate root pose and exact parent chain (preferably via uninterrupted original spawn) and compare matrix fields before/after `00437F90`. Integrate real `004572B0` active-world registration and original camera-mode scheduling after numeric verification. Do not treat `004C2894` NaN as a valid camera pose or begin raster validation until this boundary closes.
