# Documentation impact — vehicle motion and two-frame camera handoff

## Identity
- Run: `i76exe-20261027T033452Z-2f8c31f5`; track `i76exe`; recorded accepted base `5da264c093a9d694a7d5e36f4be62c3a26b5b0fb`.
- PR/merge: pending manual acceptance. Retail executable and private annotated Ghidra identities: `manifest.json`.

## Disposition
- **Candidate update**, with unresolved hardware numerical parity.
- Potential future target: vehicle physics / camera chapters under `manual/reference/engine/`. Historical context: `ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md`. Avoid silently turning these observations into authoritative gameplay dynamics.

## Evidence-linked claims
- `i76exe-v08-native-active-vehicle-simulation`: real original `00463800`, `0043A3C0`, `0043BDF0` call chain changes a registered root. Evidence: `evidence/direct_call_edges.tsv`, `evidence/two_frame_scenarios.tsv`, `scripts/I76_MovingVehicleTwoFrameProbe.java`. Confidence high for controlled original-code emulation; not live game scheduling.
- `i76exe-v08-consecutive-moving-camera-finite`: two frames show changing world Z and finite six-double original camera state for both GTSi/bus. Evidence: same traces and `evidence/replay_provenance.json`; original addresses `00406AB0`, `00437F90`, `00472990`. Candidate scoped original-instruction finding.
- `i76exe-v08-axis-nonunit-parity-open`: norm squared 0.473 and 0.755; **defer** orthonormal/physically accurate pose, physics/terrain and hardware x87 conclusions.

## Reconciliation / boundary
Builds upon prior VCF and camera research including PR #44 and currently proposed #46/#47/#48. No earlier immutable evidence is rewritten. A designated documentation steward may reconcile **merged** evidence at a later maintainer-requested milestone; no canonical change is proposed here.
