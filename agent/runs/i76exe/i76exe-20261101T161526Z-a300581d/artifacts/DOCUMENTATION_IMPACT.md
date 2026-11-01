# Documentation impact — FSM mission VM architecture

## Research identity

Run `i76exe-20261101T161526Z-a300581d`, track `i76exe`, subsystem FSM; original base `8b16e9f81159c9f0f4dea63e16d69d79355b6d49`. PR/merge: pending at artifact creation. PE/GZF measured identities are in `manifest.json`; method and private prerequisites in `REPRODUCE.md`.

## Disposition

**Candidate update; no canonical change in this PR.** Proposed future target: `manual/reference/engine/mission_vm.md` (new page), with a bounded contextual link from `manual/reference/engine/frame_scheduling.md`. Do not broaden the latter's original-instruction class-1 evidence into a whole VM/gameplay test.

## Evidence-linked candidates

| Finding | Narrow proposed claim | Original anchors | Evidence and confidence | Impact |
|---|---|---|---|---|
| FSM-B-layout | 0x10BC node with mixed frame/operand workspace and separate host slots; index-to-IP phase transition | 00410490, 00412500 | SEMANTIC_RECONSTRUCTION.md; vm_architecture.c; BINARY_VERIFICATION.json; binary-static high | add architectural types with phase qualification |
| FSM-B-control | all 14 token semantics; exact return cursor comparison and budget/failure edges | 00414670 | same report and CLAIM_INSTRUCTION_MAP.tsv; binary-static high, source sketch derived | add readable control model |
| FSM-B-scheduler | ordered cooperative traversal, same-pass successors, completion free, deadline and runtime gates | 004149F0, 0040A320 | CONTROL_FLOW.md and instruction map; binary-static high | add ordered state transitions |
| FSM-B-abi-envelope | caller supplies 16 scheduler and 12 VM/host words, despite shorter old formals | 0040A644, 00414A58/00414AE4, 00414949 | report call-envelope table and BINARY_VERIFICATION.json; binary-static high, trailing purpose unresolved | qualify old Ghidra signatures |
| FSM-B-readability | live-node typing improves interpreter/scheduler; loader propagation misrepresents scalar index | same cluster | READABILITY_AUDIT.md; READABILITY_METRICS.tsv; guarded script | separate annotation proposal; defer canonical baseline change |

Artifact SHA-256 and byte counts are bound in manifest.artifacts; immutable source digests are in SOURCE_PROVENANCE.tsv. findings.json carries evidence references and confidence/limitations for each candidate.

## Reconciliation

Confirms historical `ref/mission_execution/MISSION_EXECUTION_CONTRACT.md` §§5–6 and host ABI §1. Narrows approximate budget wording to exact loop placement. Narrows the v94 report's old unknown-reporter qualification using the verified RET body. Complements v93/v94 prose with original-authored source and explicit cursor equality. The old 10/15 formal counts are presentation omissions, not new runtime parameters introduced by this run. The private v97 baseline predates v100/v101 tools; newer labeling is not treated as automatically stronger instruction evidence.

Parser/loader v0.5/v0.6 original-code experiments did not execute the VM; do not cite them as nested-call runtime verification. Corpus absence of kinds 2,3,11 remains inherited static evidence. Still unresolved: opaque forwarded word, indirect callback recursion or link mutation, dynamic nested-call depth, malformed-bytecode upstream reachability, full Windows behavior. No new gameplay, AI or host-slot-wide findings are proposed.

## Publication boundary

No edits to `ref/`, accepted runs, `manual/reference/`, `agent/promotions/`, governance, shared tools, or v102 class-dispatch work. A designated documentation steward can reconcile this run **after merge** at an FSM milestone and submit a separate fresh-base promotion/reference PR for explicit human acceptance. This research PR will not be merged by the agent.
