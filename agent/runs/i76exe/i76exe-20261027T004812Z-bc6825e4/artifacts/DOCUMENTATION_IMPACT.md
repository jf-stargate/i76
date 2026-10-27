# Documentation impact — original selected-vehicle VLOC camera attachment

## Research identity
- Run: `i76exe-20261027T004812Z-bc6825e4`; track `i76exe`; original base: `34a15f060ff585a085619defeffca2fe20969609`.
- PR / merge: pending independent draft research proposal and human review.
- Binary/Ghidra identity: `manifest.json` inputs and baseline, retained as private bytes.

## Documentation disposition
- Classification: **candidate update**, not automatic canonical promotion.
- Suggested subsystem: `manual/reference/engine/vehicle_construction.md` (spawn eligibility and VLOC attachment); a separate camera runtime reference may be warranted after numerically validated camera work.
- Prior accepted evidence: merged runs `i76exe-20261022T232710Z-96c58505` (original vehicle constructor), `i76exe-20261024T232546Z-11d4e2ec` (isolated VLOC), `i76exe-20261024T021540Z-84ef6779` (camera guard) and `i76exe-20261026T235108Z-12215047` (original status selectors). Historical `ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md` distinguishes object status and runtime state.
- Publication recommendation: **defer canonical camera pose claims**; the selected/unselected VLOC eligibility is a candidate for eventual evidence-reviewed promotion.

## Evidence-linked candidate findings
- Spawn status selector: `i76exe-20261027T004812Z-bc6825e4-native_spawn_bit_10_status_to_vcf`; native `0045146E`, original call boundary `0045148B`; `evidence/scenario_results.tsv` SHA256 `eadacc2f37d39ac04ca9aaee55c4c4b16ae82f5b894278090e169f483ef9a0e7`.
- Full VCF/VLOC class-40 attachment: `i76exe-20261027T004812Z-bc6825e4-native_vcf_vloc_class28_attachment`; `004AD6F0`, `004AE000`, `00461970`, runtime `+0x398`; replay `scripts/I76_NativeSpawnVlocCameraFastProbe.java` SHA256 `186f33be3f25057618cbaea9116d71000fed2fc0195d18e7f66bbb3527902a8b`.
- Unselected negative control: `i76exe-20261027T004812Z-bc6825e4-native_vcf_unselected_control`; zero attachment, unmodified VCF/TMT counts; same structured scenario evidence.
- Original camera guard: `i76exe-20261027T004812Z-bc6825e4-native_default_camera_guard_with_vloc`; `00406AB0`, `00406B02`, `00406B13`, `00406DF4`; no numeric view validation.
- Deferred original camera math and object lifecycle: `i76exe-20261027T004812Z-bc6825e4-default_camera_post_guard_and_teardown_open`; unresolved.

## Reconciliation notes
This extends—not contradicts—the earlier merged isolated VLOC experiment. Importantly, the spawn setter is executed to its VCF call boundary, then the loader is **explicitly invoked by the harness in the same state**, rather than CPU stepping through that one CALL instruction. Windows heap, CRT, resource and some renderer services remain substituted. A sibling-like link at object `+0x68` changes during child construction; no immutable parent field claim should be promoted from that observation.

## Publication boundary
This research PR proposes **no edits to** `ref/`, `agent/promotions/`, or `manual/reference/`. A documentation steward should reconcile merged evidence and create a separate fresh-base promotion/reference PR only at a maintainer-authorized milestone.
