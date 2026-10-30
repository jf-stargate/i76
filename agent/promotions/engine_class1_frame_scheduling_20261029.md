# Promotion proposal — bounded original class-1 frame scheduling

**Status:** Candidate — effective only if the human maintainer accepts and merges this separate promotion/reference PR.  
**Date:** 2026-10-29  
**Original accepted base commit:** `980037f49b348e14ccdde8ba2961174a8647f090`  
**Research track:** `i76exe`; advisory ENG / OBJ / VEH / TER  
**Target:** [frame scheduling reference](../../manual/reference/engine/frame_scheduling.md), [reference index](../../manual/reference/README.md), [ENG discovery index](../../manual/roadmap/subsystems/ENG.md)  
**Publication:** this documentation/promotion PR; no automatic promotion from a merged research run.

## Decision and selected scope

Propose promoting the **bounded** class-1 dispatch interface: original registration and linked collection traversal, original class-descriptor slot identity and indirect original class-1 pre/post invocation/return for three controlled **unselected** M06 bus/GTSi frames. Support it with the earlier **static** original WinMain phase-order analysis and original clock prerequisites, preserving distinct evidence classes. Promote only the sampled state chronology and repeat/control comparability, not all bytes or all class behavior.

**Not selected for positive promotion:** full WinMain execution, complete pending/class-1 initialization, selected-player post effects, input/AI/FSM, class31/34 post bodies, unmodified Windows runtime, pixel rendering, general polygon contact, and hardware-wide x87 parity. The selected-post `FSINCOS` failure is a recorded diagnostic boundary, **not** successful selected scheduling.

## Source evidence and immutable provenance

| Run / accepted PR | Finding and original anchors | Artifact + SHA-256 | Evidence class and limitation |
| --- | --- | --- | --- |
| [Frame startup run](../runs/i76exe/i76exe-20261028T172133Z-66a1688b/manifest.json); [PR #50](https://github.com/jf-stargate/i76/pull/50), merge `64667f3f168de1d377af8b1adf194dc51c256ffc` | `F3-scheduler-contact-boundary`; `004039B8`, `00403D86`, `00403DD5`, `00403DDF`, `00461C80/00461D50` | [instruction anchors](../runs/i76exe/i76exe-20261028T172133Z-66a1688b/evidence/instruction_anchors.tsv) `3129bc50e9b4ba5ae716d457d41c881ff5e0513fc00b6acc056317d246f8d31f`; [frame report](../runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/FRAME_INITIALIZATION.md) `08d1e3ef1841c575367f8fde36038a34a56195d0497ea9d324fe0aaafb33aacc` | Binary-static scheduler ordering, not a replayed WinMain frame; original gated contact run did not complete valid terrain sampling |
| [M-ENG-01 run](../runs/i76exe/i76exe-20261029T170926Z-3a9402a5/manifest.json); [PR #58](https://github.com/jf-stargate/i76/pull/58), merge `e06ca00650c1bf1763fac68542f09e13e3b8e883` | `F1-original-list-and-dispatch`; `00461970`, `0049C320`, `0054B204`, `00461C80/00461D50`, `0045F0F0`, `00461D38/00461E08`, class1 descriptor `004F777C` | [dispatch events](../runs/i76exe/i76exe-20261029T170926Z-3a9402a5/evidence/dispatch_events.tsv) `aef6490e6a4832da0f8e5ec5964fd82a22af52dc7aa6de8386b8a73ffde9c16e`; [instruction anchors](../runs/i76exe/i76exe-20261029T170926Z-3a9402a5/evidence/instruction_anchors.tsv) `1fe3af3ece04f7e29c509d00fdf36c3a430641d212c3a5ccdab6a3bf6ba3dce6`; [original probe](../runs/i76exe/i76exe-20261029T170926Z-3a9402a5/scripts/I76_DescriptorScheduleProbe.java) `1ddd87d5d2cdc0f8c4e521acc187f1f11e933924bda15a70abe3692ed769d8ac` | Original x86 under Ghidra with supplied heap and peripheral services; 15 class nodes for each constructed **unselected** vehicle; no whole WinMain or selected post |
| Same merged M-ENG-01 run | `F2-phase-state-controls`; three pre/post frames; before/after root/velocity/timer/flag snapshots and direct/empty/repeat controls | [results JSON](../runs/i76exe/i76exe-20261029T170926Z-3a9402a5/evidence/results.json) `12c0bbd4d03efab9e084fb65c1fa6e1ffb969a601c08862993d165ca0bccb8af`; [verifier](../runs/i76exe/i76exe-20261029T170926Z-3a9402a5/scripts/verify_schedule.py) `d31f23b48f38805175b058a0fcc8c339316fd474c6ab018571b6c5fced0fd2c3` | Sampled fields only, three controlled M06 frames, no selected post effects, full runtime-byte coverage, or general mission fidelity |
| Same merged M-ENG-01 run | `F3-selected-post-blocker`; selected diagnostic at `0049D409` | [provenance](../runs/i76exe/i76exe-20261029T170926Z-3a9402a5/evidence/provenance.json) `a5c04ecc5362b40dd6aa9e7939f88627f8abdb10ca141075476b2f43e6ff7de3` | **Defer positive selected-player claim;** original FSINCOS unsupported P-code + incomplete peripheral state; negative evidence retained as an explicit limitation |

**Source executable:** reported retail `i76.exe` MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`.  
**Private annotated Ghidra:** Ghidra 12.1.4; `i76_mission_v97_verified_names`; annotated v97 GZF SHA-256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`.  
**M06 source identities:** `I76.ZFS`, `M06.MSN`, `M06.TER` source hashes recorded in [M-ENG-01 manifest](../runs/i76exe/i76exe-20261029T170926Z-3a9402a5/manifest.json). These identities were reported by the run; the documentation steward did **not** receive private binaries or independently execute Ghidra.

The M-ENG-01 run recorded scientific validation 3,807/3,807, five fresh-project case replays with separately reproduced bus trace, and a private input prerequisite. Its immutable `validation.json` says **partial 3,844/3,845** because the then-trusted base archive test rejected already-supported schema 1.2.0. [Accepted PR #59](https://github.com/jf-stargate/i76/pull/59) subsequently repaired that infrastructure test. This promotion does not convert the old validation field into a passing claim or imply it has rerun the original experiment.

## Reconciliation and evidence hierarchy

| Proposed current statement | Prior/historical context | Proposed disposition |
| --- | --- | --- |
| Original `00461C80/00461D50` traverse class collection registered through original `00461970/0049C320` and invoke class-1 through original indirect descriptor calls | [Older frame report](../runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/FRAME_INITIALIZATION.md) established static descriptor/WinMain order; [M06 original callback replay](../runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/AUTHENTIC_TERRAIN_PHYSICS.md) manually invoked callbacks | **Extend** static evidence with bounded original-instruction dispatch; do not mistake earlier direct invokes for evidence of original scheduler |
| Original class head `0054B204` differs from world active-entry registry `00542830` | [Historical object model](../../ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md) describes world/AI/FSM object registration and `004572B0` | **Distinguish separate registries**; no contradiction about underlying world-object membership, and no blanket lifecycle equivalence |
| Static mapped gameplay state 5 places clock before pre/post and FSM | [Historical mission execution](../../ref/mission_execution/MISSION_EXECUTION_CONTRACT.md) describes broad mission/FSM sequence | **Narrow** to exact original callsite mapping; do not promote every historical FSM or input claim |
| Unselected class-1 pre mutates sampled pose/basis/timer; post returns through false predicate | Earlier direct-callback VEH work observes state mutations under controlled drives | **Confirm only these sampled unselected fields**; defer complete selected post/cockpit/audio claims |
| Selected-post diagnostic fails at original `FSINCOS` and incomplete state | Not contradicted by unselected success; direct control uses different entry conditions | **Defer selected-player behavioral contract**; preserve negative trace as blocker, not a repaired original behavior |

No competing merged run identified here demonstrates the complete selected-player post with original pending initialization. Any subsequently accepted selected-player experiment requires **new** reconciliation and promotion; do not rewrite this record.

## Proposed reference changes

- Add [`manual/reference/engine/frame_scheduling.md`](../../manual/reference/engine/frame_scheduling.md), with explicit class collection, descriptor, phase, clock and selective-state contract and negative boundaries.
- Add a discoverable link to the [curated reference index](../../manual/reference/README.md).
- Add a careful link from [ENG subsystem discovery](../../manual/roadmap/subsystems/ENG.md) distinguishing bounded promoted evidence from the older static index.
- **No Ghidra annotation, other canonical source, `ref/`, protocol, protected CI, or immutable run changes.**

## Reproduction and risks

Follow [M-ENG-01 REPRODUCE](../runs/i76exe/i76exe-20261029T170926Z-3a9402a5/artifacts/REPRODUCE.md), [service ledger](../runs/i76exe/i76exe-20261029T170926Z-3a9402a5/artifacts/SERVICE_LEDGER.md) and [F1/F2/F3 source findings](../runs/i76exe/i76exe-20261029T170926Z-3a9402a5/findings.json). Validate authentic private inputs and source toolchain before reproducing; OS/CRT/resources, tick, input, numerical, camera, render and peripheral services are supplied. **Selected vehicle post and full WinMain are unresolved**. The next independent CAP-CONTROL-01 investigator should not adopt this reference as proof of an end-to-end gameplay frame.

## Acceptance checklist

- [x] Both named research runs are merged, with verified PR and merge-commit references.
- [x] Evidence crosswalk includes exact findings, original addresses and immutable artifact hashes.
- [x] Historical references and older manual-callback studies reconciled within stated scope.
- [x] No positive selected-player, complete WinMain, native Windows or general collision claim.
- [x] Proposed reference/index changes are isolated from new research, baselines and governance.
- [ ] Human maintainer reviews technical selection and confirms no private content.
- [ ] Ruleset `25664125` is re-enabled, required `integrity` passes on a fresh current-base check, and protection is verified.
- [ ] Human maintainer explicitly accepts and merges this PR.

**Decision:** Pending human review; this file alone is not promotion authority.
