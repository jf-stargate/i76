# Native active-world vehicle registration → visibility and render-queue bridge

**Evidence checkpoint:** `i76.exe`, MD5 `a640ea0097dbb62e0c77b7f2847c7161`, original x86 instructions in private Ghidra 12.1.4 v97 (`b2f76177...`). This **new run is proposed evidence**, not a promotion of merged reference documentation. Based on protected `main` `f29379db9c7eccef91f6f93bc5984ce9dc6b9e4a`; builds on merged vehicle v2.4 and overlapping *draft* renderer proposals #24, #26, #29 and #30.

## New original-code observations

1. **Original live registry creation**: Executed `004572B0(root, 0, NULL)` against each privately constructed VCF-native class-1 root (`0x26000000`) after original geometry variants were selected. Original `0045ED00` recursive reference acquisition, `00459160` world-object bounds, and `00458FC0` bounding radius were **not replaced**. Native return points to active entry `00542830`, owner at entry `+0` is actual class-1 root, count global `0054A25C` becomes 1; in both controlled states root refcount `+0x0C` increments 3 → 4. The entry's center/radius floats read as zero under this private setup: do **not** interpret these as valid retail-world bounds or accurate FPU numerics.
2. **Original producer with genuine entry**: Called retail `00457FF0` without manufacturing the entry. Under synthetic identity camera, normalized near bound 0, far bound 4096, and acceptable frustum, original `00472C10`, `00490590`, and `0048FE10` emitted **two distinct records**, type 6 (owner `26000000`, bucket 100, `0x44` bytes) and type 10 (other child node `27000C00`, bucket 90). This is *not* one duplicate entry; bin call sites are `004586BF` (return `004586C4`) and `0048F4A3` (return `0048F4A8`). The original instructions at `0048F433` write the literal `0x0A` discriminator. Cursor advanced from `2E180000` to `2E1800B8`; do **not** generalize sizes across the record types.
3. **Frustum rejection**: A controlled opposing frustum causes one classifier call and zero work records for each genuine registered vehicle. The accepted case reaches two classifier calls. We did not alter the registry on either path.
4. **Original consumption**: `0048FAC0` consumed both original-produced records. Type 6 dispatched through `0048F4C0` into `0045D530` secondary traversal with actual hierarchy. `0045CBE0` processed a real GEO child in each case; zero calls to `00471FD0` under this test view. Type 10 has a different creation/handling path and does **not** establish a second root geometry submission.
5. **Original unregister and slot reuse**: Executed `00457420(entry)` unmodified. For each vehicle, active entry `+0` became null, count became 0, and root refcount dropped 4 → 3. A second original `004572B0` returned **the same entry address**, restored count 1 and root refcount 4. Reference release was original retail code, although OS/heap/media services around the vehicle harness remain substituted.

The precise production call chain tested is:

`004AD6F0 (VCF) → 004572B0 (active entry/recursive reference) → 00457FF0 (original transforms/frustum) → 00490590 (record allocation) → 0048FE10 (depth buckets) → 0048FAC0 (bucket consumer) → [type-6] 0048F4C0 → 0045D530 → 0045CBE0`, then `00457420 → 004572B0` for lifecycle re-use. This **is not a complete retail frame**.

## Evidence / reproduction

- Private trace SHA256 `7b4a567be1ca1f64f73ccb8cc7e6b69aaf8f30101343271557174a054692a4bf`; two separate read-only Ghidra headless original-code runs were byte-identical.
- Ghidra script `scripts/I76_RegisteredVehicleLifecycleProbe.java` (extends v2.4 native VCF constructor + PR #29/#30 producer/consumer experiments); run script from a read-only imported private v97 Ghidra project with original resource fixture directory and an output trace path. Original media, GZF and traces stay private.
- Independent verification against the original retail PE's instruction-byte anchors and parsed native events: see `scripts/verify_native_registration.py` and derived `evidence/*.tsv`. The verifier neither reproduces original hardware x87 arithmetic nor verifies the Windows game-loop camera.

## Remaining limits

- `004572B0`'s registered callbacks were **not separately initialized through the full mission/world startup**, and no game session was executed. Initial fixture context uses synthetic world root pointer/transform and substitutions for CRT, heap, palette, optional lighting, resource acquisition and clip/draw. Do not claim original game actor/team registration was validated here.
- Entry center/radius zero under emulation is not evidence that real vehicles have zero spatial extent. Synthetic camera planes and queue normalization determine bucket 90/100 and visible/culled choices. Validity of original camera matrices, far/near selection and x87 parity remains open.
- Mode-0 secondary pass builds GEO scratch but produces no submitted polygons under this view. Distinguish this from a real retail camera verdict and from primary rendering, which the earlier native direct-entry experiment exercised only under supplied pass mode.
- Type-10 origin at native `0048F433`/`0048F4A3` is proven; exact purpose (e.g., a separate overlay/effect) requires investigation rather than inferring from Ghidra's names.
- Real pixel decode and clipping/draw callback execution remain unvalidated; no displayed frame or GPU output.

## Next focused experiment

Trace original per-frame camera/frustum construction and actual active-entry initialization for multiple root vehicle instances. Carry authentic camera depth bounds into `0048FAC0`, then determine why the secondary pass's created scratch records are rejected under the synthetic view. In parallel trace type-10 consumer callback and its ownership/release to avoid conflating it with the type-6 body pass.
