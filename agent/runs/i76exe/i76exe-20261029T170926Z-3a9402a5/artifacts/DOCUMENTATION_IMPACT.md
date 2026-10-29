# Documentation impact — ENG descriptor-driven class-1 pre/post

## Research identity
- Run: `i76exe-20261029T170926Z-3a9402a5`; binary track `i76exe`; milestone M-ENG-01, ENG/VEH/OBJ/TER interfaces.
- Original base: `9312486b92f15305d814c2bf0551f3cf1e233f48`; research PR pending at artifact creation; merge not authorized.
- Original PE/GZF and fixture identities: manifest plus `evidence/results.json` and `evidence/provenance.json` (measured, no private payloads).

## Documentation disposition
- Classification: **candidate update**, with a narrow unresolved selected-post boundary.
- Suggested separate living target: `manual/reference/engine/frame_scheduling.md` (proposed new reference), with ENG/VEH index links only after reconciliation.
- No canonical change in this research PR. No edits to `ref/`, accepted runs, promotions or current reference.
- Historical sources: `ref/mission_execution/MISSION_EXECUTION_CONTRACT.md` (gameplay phase order), `ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md` (object/class lifecycle). These are context, not fully revalidated contracts.

## Evidence-linked candidates

### F1-original-list-and-dispatch
- Claim: Original 00461970/0049C320 class registration and list insertion produce the collection traversed by original 00461C80/00461D50; in the tested bus/GTSi unselected states, class-1 slots 004F7788/004F778C invoke and return from 00463800/00463950 through original indirect calls.
- Status: proven, high confidence; original-instruction emulation with declared services plus independent checks.
- Impact: add bounded ENG dispatch interface
- Evidence: `evidence/dispatch_events.tsv`, SHA-256 `aef6490e6a4832da0f8e5ec5964fd82a22af52dc7aa6de8386b8a73ffde9c16e`.
- Evidence: `evidence/instruction_anchors.tsv`, SHA-256 `1fe3af3ece04f7e29c509d00fdf36c3a430641d212c3a5ccdab6a3bf6ba3dce6`.
- Evidence: `evidence/results.json`, SHA-256 `12c0bbd4d03efab9e084fb65c1fa6e1ffb969a601c08862993d165ca0bccb8af`.
- Evidence: `scripts/I76_DescriptorScheduleProbe.java`, SHA-256 `1ddd87d5d2cdc0f8c4e521acc187f1f11e933924bda15a70abe3692ed769d8ac`.
- Evidence: `scripts/verify_schedule.py`, SHA-256 `d31f23b48f38805175b058a0fcc8c339316fd474c6ab018571b6c5fced0fd2c3`.
- Limits/contrary evidence: Bounded Ghidra original-instruction execution. Controlled setup skips complete pending initialization and full 00463120; class31/34 post services supplied; primary post predicate false. Not complete WinMain.

### F2-phase-state-controls
- Claim: Three dispatcher-driven frames per vehicle show original pre pose/velocity mutations and original false-gate post return with unchanged sampled state; bus sampled states equal the direct-callback control, and a separate bus process reproduces the entire trace byte-for-byte.
- Status: proven, high confidence; original-instruction emulation with declared services plus independent checks.
- Impact: qualify state and reproduction scope
- Evidence: `evidence/results.json`, SHA-256 `12c0bbd4d03efab9e084fb65c1fa6e1ffb969a601c08862993d165ca0bccb8af`.
- Evidence: `evidence/dispatch_events.tsv`, SHA-256 `aef6490e6a4832da0f8e5ec5964fd82a22af52dc7aa6de8386b8a73ffde9c16e`.
- Evidence: `scripts/verify_schedule.py`, SHA-256 `d31f23b48f38805175b058a0fcc8c339316fd474c6ab018571b6c5fced0fd2c3`.
- Limits/contrary evidence: Only sampled basis, position, velocity, timer, status and runtime flags compared. Three controlled M06 frames; not all runtime bytes, selected post effects, input/AI delivery or general contact fidelity.

### F3-selected-post-blocker
- Claim: The selected raw diagnostic reaches both class-1 callbacks but does not complete post: original FSINCOS at 0049D409 encounters unsupported fcos P-code after raw peripheral post callbacks read incomplete state.
- Status: proven, high confidence; original-instruction emulation with declared services plus independent checks.
- Impact: defer selected-post/lifecycle claims; preserve exact blocker
- Evidence: `evidence/dispatch_events.tsv`, SHA-256 `aef6490e6a4832da0f8e5ec5964fd82a22af52dc7aa6de8386b8a73ffde9c16e`.
- Evidence: `evidence/provenance.json`, SHA-256 `a5c04ecc5362b40dd6aa9e7939f88627f8abdb10ca141075476b2f43e6ff7de3`.
- Evidence: `evidence/instruction_anchors.tsv`, SHA-256 `1fe3af3ece04f7e29c509d00fdf36c3a430641d212c3a5ccdab6a3bf6ba3dce6`.
- Evidence: `scripts/reproduce.py`, SHA-256 `8a1578d8f1928c37ee8022066ffff106ed8f3f0115ae07300b9bf5447b5f7f4b`.
- Limits/contrary evidence: Diagnostic failure is preserved, not positive selected-post execution. Full class31/34 ownership/initialization and selected input/cockpit/audio remain unresolved; no full WinMain claim.

## Reconciliation
Accepted frame run `i76exe-20261028T172133Z-66a1688b` provided static descriptor/order evidence; accepted M06 run `i76exe-20261028T174609Z-3f1f83f8` and M-TER-01 `i76exe-20261029T023733Z-bd8eb024` invoked callbacks directly. This run extends that evidence to actual original descriptor/collection traversal. It does not contradict their stated limits. The existing vehicle construction promotion is adjacent and does not authorize scheduling claims.

A steward should retain: class collection `0054B204` is distinct from world registry `00542830`; slot identity and callback entry/return are proven for this controlled unselected state; primary class31/34 post bodies are supplied; selected raw execution remains incomplete. Recover complete pending initialization and peripheral/selected services before broadening to a normal retail gameplay frame. Reconcile merged findings and exact artifact hashes in a separate fresh-base promotion/reference PR. Only the human maintainer can accept it.

## Publication boundary
No automatic promotion or maintained reconstruction. This handoff is an immutable research artifact, not the canonical specification.

## Publication gate
Scientific checks pass, but the research PR remains draft because untouched protected-base archive tests reject an already accepted schema-1.2.0 run. See `artifacts/PUBLICATION_BLOCKER.md` and `evidence/publication_blocker.json`; this does not change the bounded scientific claims.
