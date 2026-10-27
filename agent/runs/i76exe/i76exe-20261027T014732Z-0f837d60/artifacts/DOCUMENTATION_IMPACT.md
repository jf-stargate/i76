# Documentation impact — native vehicle default camera callback

## Research identity
- Run ID: `i76exe-20261027T014732Z-0f837d60`
- Track: `i76exe`
- Original `base_commit`: `5da264c093a9d694a7d5e36f4be62c3a26b5b0fb`
- PR / merge commit: pending
- Source identities: see `manifest.json`, verified retail `i76.exe`, original `I76.ZFS`, and private annotated Ghidra 12.1.4 v97 GZF.

## Documentation disposition
- Classification: **candidate update**, **unresolved numerical boundary**.
- Potential target: `manual/reference/engine/vehicle_camera_rendering.md` (proposed; do not presume this exists) and accepted `manual/reference/engine/vehicle_construction.md` for VLOC dependency context.
- Historical references: `ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md` (world object / active entry distinct identities).
- Suggested milestone: numerical correctness of root world transform and camera output before canonical camera specification.

## Evidence-linked candidate findings
- `i76exe-camera-v07-default-postguard-exec`: original `00406AB0` completes normal return through `00472990` with native-built class-`0x28` VLOC attachment. Evidence: `artifacts/CAMERA_POST_GUARD_BOUNDARY.md`, `evidence/experiment_summary.json`, `scripts/I76_NativeCameraPastGuardProbe.java`. **Proven for emulated control flow; not real player camera**, original CRT/render service substitutions.
- `i76exe-camera-v07-world-transform-nan`: first observed nonfinite transform arises after original `00437F90` return at `00406D45`; recorded stages at `00406D27`, `00406D6F`, `00406DB6`. Evidence: `evidence/experiment_summary.json`, `scripts/I76_NativeCameraMatrixBoundaryProbe.java`. **Proven for this synthetic world context**, not general retail behavior.
- `i76exe-camera-v07-projection-init-control`: native `00405970` completes under controlled viewport, but does not eliminate resulting nonfinite camera transform. Evidence: `scripts/I76_NativeCameraWithInitProbe.java`, `evidence/experiment_summary.json`. **Proven for experimental assumptions**.

## Reconciliation notes
Confirms merged PR #44 class-`0x28` attachment is sufficient to pass the default camera's null guard; extends it through camera return. This **does not** close authentic camera pose, actual frame scheduling, or final clipping/draw. No contradiction with existing VCF construction reference; defer canonical numerical claims until valid finite matrices are reproduced. Original `ref/` reports remain historical.

## Publication boundary
This artifact proposes no edits to `ref/`, `agent/promotions/`, or `manual/reference/`. A designated documentation steward can promote supported statements through a separate reviewed PR after subsequent numerical validation.
