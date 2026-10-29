# Documentation impact — M-TER-01 controlled vertical pose

## Research identity

- Run: i76exe-20261029T023733Z-bd8eb024; track i76exe; TER primary, VEH/ENG interfaces.
- Base: 81bc3b0c16dd93191e59a2d85de5d7b9ea77629e; PR pending; no merge authorized.
- Binary/GZF identities: manifest.json inputs/baselines, measured anew; private payloads excluded.

## Documentation disposition

Candidate update after separate reconciliation; **no canonical change in this PR**. Suggested future TER/contact reference path is not yet an accepted contract. Discovery-index milestone coverage could cite this run after merge. Historical context: ref/level_format/i76_runtime_level_and_terrain_format_notes.md terrain queries; ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md identity/lifecycle. Those historical files remain untouched.

## Evidence-linked candidate findings

- `mter01-pose-contact`: original 00463800/0043A5D0/0046DC10 complete a new -0.25 initial-Y case and repeat. Mode-0 compression and separate zero 00440740 returns are measured. Evidence: evidence/results.json, frames.tsv, selected_events.tsv (manifest hashes); original-instruction execution with services, high confidence in this bounded observation. Potential addition only after review.
- `mter01-source-oracle`: all logged TER reads and heights agree with authenticated source; triangle normals agree within declared approximate-numerical tolerances. Evidence: normal_checks.tsv, source_read_examples.json, scripts/verify_pose.py and validation.json. Derived, high confidence in these cases; no all-mission contract.
- `mter01-contact-chronology-open`: earlier surface query in lowered case does not imply earlier mode-0 tire result. Cause unresolved; retain per-frame evidence, do not publish a monotonic suspension law.

## Reconciliation and limits

Confirms accepted unpromoted M06 run i76exe-20261028T174609Z-3f1f83f8 under identical baseline conditions; extends only controlled vertical pose near one M06 spawn. Does not contradict its scoped upright observations. The promoted construction contract remains unaffected. No new seam/material corpus, positive special contact, polygon collision, real input, dispatcher/WinMain or full hardware parity is established. The source-normal tolerance accounts for the original approximate inverse square root. Lowered contact timing warrants later original-branch/state investigation.

## Publication boundary

This run proposes no edits to ref/, manual/reference/, agent/promotions/ or original baselines. Hashes and byte lengths for evidence and this handoff are in manifest.json. A designated documentation steward may reconcile merged evidence in a separate fresh-base PR; human acceptance is required.
