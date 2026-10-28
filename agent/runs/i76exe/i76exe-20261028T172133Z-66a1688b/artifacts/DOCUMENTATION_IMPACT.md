# Documentation impact — frame subdivision and startup math

## Research identity
Run `i76exe-20261028T172133Z-66a1688b`, track `i76exe`, base `ea2d96e2155a53f40cbb1a5e12e2edd563a5a34a`; protocol 1.0.3. Original binary and v97 GZF identities are in manifest.json. PR pending at artifact creation.

## Disposition
Candidate update after review/merge; no canonical edits in this run. Suggested future `manual/reference/engine/vehicle_simulation.md`; retain the narrower current vehicle-construction promotion. Historical sources: `ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md`, `ref/mission_execution/README.md`, v97 snapshot. PR #49 is unmerged candidate evidence, not an accepted specification.

## Evidence-linked candidates
- F1: 0049C7F0 initializes reciprocals required by 0049CC20. The original helpers subdivide current-frame delta, not persistent elapsed-time accumulation. Evidence: `evidence/subdivision.tsv`, original anchors, `scripts/I76_TimerSubdivisionProbe.java`. High confidence for tested nonnegative inputs; `_ftol`/clock services substituted. Correct/narrow timer terminology only through later promotion.
- F2: original 00493C50 seed initialization corrects the reproduced non-unit basis to near-unit Gram matrices without replacing original normalization. Evidence: `evidence/replay_events.tsv`, private trace identities in provenance.json, `scripts/I76_FramePhysicsProbe.java`. High confidence for tested stock bus/GTSi states; preserve approximate-math/hardware caveat. Candidate narrows PR #49's unresolved numerical cause; does not modify its files.
- F3: WinMain clock/pre/post/FSM ordering and class-1 callback descriptor; positive-time original wheel-path entry ending at unloaded 00493550. Evidence: instruction anchors and guarded contact events. Static scheduling, dynamic entry only. Defer claims of completed valid contact/physics frames. Earlier unguarded finite solver results are contaminated by null terrain reads.

## Reconciliation and next milestone
Confirms original root initialization from merged PR #48 remains necessary. Adds distinct math/clock prerequisites; no contradiction with the accepted construction specification. Need actual mission terrain initialization and safe packed-block reads before promoting positive ground-contact dynamics. Evidence digests are recorded in the manifest; full assessment and reproduction limits are in FRAME_INITIALIZATION.md and REPRODUCE.md.

## Publication boundary
No changes to ref/, manual/reference/, agent/promotions/, other runs, or baselines. A designated documentation steward reconciles merged evidence in a separate fresh-base PR; human maintainer acceptance remains required.
