# Documentation impact — native vehicle root initialization resolves synthetic camera NaNs

## Research identity
- Run ID: `i76exe-20261027T031313Z-32de4d1e`; track: `i76exe`; base: `5da264c093a9d694a7d5e36f4be62c3a26b5b0fb`.
- PR / merge: pending human review; binary/Ghidra/retail archive identities: `manifest.json`, `evidence/replay_provenance.json`.

## Disposition
- **Candidate update** after human documentation-steward reconciliation, not automatic canonical promotion.
- Candidate living reference: `manual/reference/engine/vehicle_camera_math.md` (proposed) and link from existing `manual/reference/engine/vehicle_construction.md` after review.
- Historical source: `ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md` (world-object/vehicle-runtime/active-entry pointer distinction).
- Relevant proposed research: PR #46 (full camera NaN boundary), PR #47 (`00437F90` contract and constructor precondition). Both retain independent run status and cannot be silently overwritten.

## Evidence-linked candidate findings
- `i76exe-b-native-root-stable-basis-through-vcf-registration`: original `0045EBD0` initializes root identity basis; original `004AD6F0` and `004572B0` preserve direction `(0,0,1)`; status proven within emulated original instruction tests, confidence high. Evidence: `evidence/scenario_results.tsv`, `scripts/I76_MilestoneBPoseDiagnosticsProbe.java`; original addresses `0045ECAD`, `004AD6F0`, `004572B0`.
- `i76exe-b-selected-native-camera-finite-six-doubles`: native-registered GTSi and bus complete original `00406AB0` and produce zero nonfinite at `00437F90` output and six-double `00472990` view record; original-x86 emulator with stated math/service substitutes, confidence high **for controlled emulation only**. Evidence: `evidence/scenario_results.tsv`, `evidence/replay_provenance.json`, `00437F90/00406D45/00472990`.
- `i76exe-b-zero-root-causal-nan-control`: selected bus with same original registration/VCF/camera path but missing original constructor root basis reproduces 9 nonfinite transform words and 6 camera NaNs. Strong controlled causal differential; confidence high for this fixture. Evidence: `evidence/scenario_results.tsv`, `00493D1B`.
- `i76exe-b-retail-numeric-parity-open`: no authentic simulation pose, original frame timer/controller, hardware x87 parity, numerical tolerance comparison or complete renderer frame. **Defer** promotion of any live camera pose or pixel claims.

## Reconciliation
The previous synthetic-camera NaN observation is not evidence of a retail-game numerical defect. This controlled test explains it through root initialization. The earlier findings and trace history remain intact. Confirm original gameplay pose writers and compare x87 hardware before claiming full camera parity.

## Publication boundary
This note is a handoff only. No `manual/reference/`, `agent/promotions/`, `ref/`, or governance edits are made in this research PR. A separate maintainer-designated documentation steward proposes any canonical changes, with explicit human acceptance.
