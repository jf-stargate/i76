# Documentation impact — native vehicle camera basis and constructor-state prerequisite

## Research identity
- Track/run: `i76exe` / `i76exe-20261027T024149Z-108e46eb`.
- Original base: `5da264c093a9d694a7d5e36f4be62c3a26b5b0fb`.
- PR / merge commit: pending; this is an evidence handoff, not accepted promotion.
- Original executable and annotated Ghidra identity: `manifest.json` `inputs[]` / `baselines[]`.

## Documentation disposition
- **Candidate update**, not an applied canonical change.
- Suggested future reference: a dedicated `manual/reference/engine/vehicle_camera_math.md` or a scoped vehicle-camera section in the relevant accepted engine reference, after documentation steward reconciliation. No existing canonical page modified.
- Historical checkpoint: `ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md` (world-object and runtime pointer levels), earlier merged VLOC/camera runs #38/#40/#44; previous proposal #46, whose native selected camera revealed non-finite output from `00437F90`. Treat #46 as candidate evidence until human merged; no override of its provenance.

## Evidence-linked candidate findings

1. **`i76exe-transform-437f90-class1-camera-contract`**: original retail `00437F90` is a class-1 vehicle camera-basis/stabilization function, not a general bounds query. Supporting original addresses: `00437F90`, direct callers `00406D40` and `00407236`, vector projection `00493CA0`, cross-normalization `00494C80`, matrix constructor `00494710`, three smoothing globals. Evidence: `artifacts/WORLD_TRANSFORM_437F90_CONTRACT.md`, `evidence/field_access_contract.tsv`, `evidence/caller_helper_edges.tsv`, `evidence/retail_opcode_anchors.tsv`, read-only audit scripts, repeat native traces. **Candidate semantic correction**, confidence high within original disassembly/emulated behavior. Do not silently rename annotated Ghidra labels.
2. **`i76exe-native-world-node-direction-initialization`**: original `0045EBD0` copies a 16-word transform template into `object+0x18`, furnishing direction `(0,0,1)` at `object+0x30` for a root; original `00437F90` yields 0 non-finite outputs under finite controlled runtime state. Evidence: `scripts/I76_NativeNodeRootContractProbe.java`, original `0045EC9C–0045ECAD`, `evidence/native_contract_scenarios.tsv`. **Candidate add**, confidence high within isolated execution.
3. **`i76exe-437f90-zero-axis-nonfinite`**: clearing exactly the constructor-provided direction causes 9 nonfinite output words, with projection helper x87 division lacking a zero-length guard at `00493D1B`. Evidence: same probe, `00493CA0`, `evidence/native_contract_scenarios.tsv`. **Candidate add**, constrained to isolated synthetic input and Ghidra execution. This is not evidence that real retail gameplay produces NaNs.
4. **`i76exe-full-camera-pose-not-yet-validated`**: a full vehicle camera replay initialized from native world constructor and authentic world/physics pose has not occurred; neither full-game numeric parity nor pixel rendering should be described as validated. **Defer** a canonical claim of finite live camera pose until future evidence.

## Reconciliation notes
- This narrows, rather than contradicts, prior camera-boundary research: the older complete camera harness manually zero-initialized the root instead of exercising the root node constructor. A direct native node-constructor vs zero-root differential supports a root initialization prerequisite, but **the complete previous selected-vehicle camera replay has not been rerun with this correction**.
- The inherited annotation `effect_target_bounds_query_helper_00437f90` is behaviorally misleading. Consider a reviewed semantic rename *after* the documentary crosswalk, without altering original merged run records.
- Shared normalization helper `00495000` uses a lookup approximation, and synthetic runtime inputs are not hardware x87 parity tests. Input magnitude and cross-product degeneracy require further coverage.

## Publication boundary
No edits to `ref/`, `agent/promotions/`, `manual/reference/`, governance or accepted baselines are proposed here. A separately requested documentation steward review may consider a later canonical PR. Human maintainer alone accepts the change.
