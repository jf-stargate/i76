# Documentation impact — RND controlled camera continuity

## Research identity

- Run: `i76exe-20261030T020546Z-e1909f11`, track `i76exe`, M-RND-02.
- Original base: `d2072e673492b8fa72b268028890e6ef51dc2537`; PR pending at artifact creation.
- Retail PE, ZFS and annotated v97 Ghidra identities are measured and listed in `manifest.json`; full fixture and replay provenance in `evidence/provenance.json`.

## Documentation disposition

**Candidate update after human research review; no canonical change in this PR.** Suggested future target: a camera/view section under `manual/reference/engine/`, reconciled with `manual/roadmap/subsystems/RND.md` and its immutable camera/root evidence. This is not a request to mark CAP-CAMERA-01 or CAP-SLICE-01 complete. Selected-player post/init remains outside this run.

## Evidence-linked candidate findings

- `rnd02-persistent-camera-pose-response`: direct original `00406AB0` across A,A,B,B,C,C,A,A updates full original `004C2730` with measured pose differences and retained history for bus/GTSi; original root pose itself is controlled. Evidence: `CAMERA_CONTINUITY.md`, exact byte samples/read/write chronology in `evidence/camera_events.tsv`, independently derived `evidence/numerics.json`, PE anchors and verifier. Artifact SHA-256 values are in manifest. Status proven within bounded original-instruction emulation, high confidence. Add narrowly scoped continuity evidence; do not imply native simulation pose or scheduling.
- `rnd02-view-field-provenance`: `+0x160` is origin and `+0x178` begins four transformed frustum corners; inverse matrix, bounding center and radius independently match original source bytes. Evidence: same records plus `00472990/00494F70/00472D30` anchors. Proven/derived, high confidence in sampled valid states. Clarify earlier six-double diagnostic wording and older 432-byte sampling, without rewriting old runs.
- `rnd02-controls-and-repeat`: stationary/reset/cold-B separate history from pose; zero basis yields six NaNs; null VLOC preserves initialized camera. Fresh-project full bus trace byte-identical. Proven bounded emulator controls; evidence and limitations in report and provenance. Preserve contrary/negative evidence.
- `rnd02-live-camera-gap`: hardware x87 parity, live selected post, physics-produced pose, visibility and raster remain unresolved. No claim promotion without separate evidence.

## Reconciliation notes

Confirms accepted original native-root camera run `i76exe-20261027T031313Z-32de4d1e`, extends it beyond one finite state, retains original math initializer from `i76exe-20261028T172133Z-66a1688b`, and extends the 118-dword projection record mapped in `i76exe-20261023T153639Z-95865b83`. No conflict with bounded scheduler or vehicle construction promotions. Existing `ref/` is historical; no historical text is rewritten or assumed to be the new canonical camera contract.

Publication recheck found accepted main `a474af7f893d240706e4bfa752e4dc0212e46ebd` (PR #65), with unchanged publication policy. The new RND-v1 acceptance contract leaves this controlled investigation valid but requires separate M06-scene and visibility evidence: this run does not close RND-R1 or SC-RND-01 as a whole.

M-RND-03 can reproduce a controlled original-updated camera using this run's exact startup and service ledger. It still needs separate M-RND-01 producer evidence; this run executes neither visibility producer nor queue consumer. Review should retain the distinction between a constructed native node with controlled pose writes and native simulation-produced pose.

## Publication boundary

No edits to `ref/`, `manual/reference/`, `agent/promotions/`, shared tooling or another run. A designated documentation steward reconciles merged evidence in a separate fresh-base proposal; only the human maintainer accepts promotion.
