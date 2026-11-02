# Promotion proposal: retail terrain samplers, mission VM and resource ownership

**Status:** Candidate — not accepted until human review and merge.
**Date:** 2026-11-02.
**Original accepted base commit:** `9576fc573964bed624a08d878886ccad40a63d7a`.
**Track:** `i76exe`.
**Target documentation:** `manual/reference/engine/terrain_sampling.md`, `mission_vm.md`, `resource_acquisition.md`.
**Publication:** this documentation PR; no Ghidra database modification.

## Scope and decision proposed

Promote bounded **binary-static semantic contracts** from already merged research PRs #102–#104, reconciled against the subsequently accepted tooling PR #105, into separate original-address-linked technical reference pages. Neither interpreted original developer source names nor live retail runtime execution is claimed. Do not promote incomplete source-media policy, unknown serialized-field meanings, absent malformed-input guarantees, Ghidra cast rendering as literal x87 instructions, or the existence of a unified resource handle.

Private `i76_mission_v99_verified_names.gzf` (whole SHA-256 `ca211238170806eda27a2b4ecf6aee2192abb69df27fe56f106b455ac75bc710`) is a separately **identity-verified but internally unaudited candidate**. The three source-level semantic references below are based on accepted original PE evidence rather than on unverified v99 annotations.

## Accepted source crosswalk

All source paths are under `agent/runs/i76exe/<run-id>/`, with file SHA-256 from each immutable accepted run manifest:

| Run / merge | Finding IDs and retail anchors | Principal artifact SHA-256 | Evidence/limits |
|---|---|---|---|
| `i76exe-20261101T161505Z-44beefbb`, PR #103, merge `5f0a310109d87efd3a2f565605e166e9d1d65ef5` | `TER-A-layout` 00493080/00493160; `TER-A-height-abi` 00493550; `TER-A-normal-material` 004931C0/004927B0; `TER-A-readability` | `artifacts/SEMANTIC_RECONSTRUCTION.md`: `3f01b9c51c99ef5b1bb3847441dc052762255feadb2bb07b4827823465b041e2`; `evidence/ORIGINAL_CODE.tsv`: `465183cc2ff42b6a889ff2258e1731b9e6e2c9aff8cf86180a32ddfcc993f136` | Binary-static plus prior separately accepted M06 corroboration. No full sampler runtime equivalence |
| `i76exe-20261101T161526Z-a300581d`, PR #102, merge `0ead406484c2e1107bfbb22fd83065e45dc4cb2f` | `FSM-B-layout` 00410490/00412500; `FSM-B-control` 00414670; `FSM-B-scheduler` 004149F0; `FSM-B-abi-envelope` 00412CE0; `FSM-B-readability` | `artifacts/SEMANTIC_RECONSTRUCTION.md`: `acb0cdc688b6f75daf31da1216f1c6bd858b2a42ebecbcf261d8bbf65af8e5db`; `evidence/BINARY_VERIFICATION.json`: `9f3cdb37a58e0367eafb96a89580e20be4fdd41cc43d1580bc3e48823c69be23` | All 2,489 audited instructions PE-matched; no original VM run |
| `i76exe-20261101T161535Z-22d9956f`, PR #104, merge `3efea4bc25b2614ac93b593ebfa49e57c2170bde` | `RES.C1`–`RES.C10` 0046FFC0/00470070/00470340/00470B20/004B2E00/004B3030 and others; `RES.U1` deferred | `artifacts/SEMANTIC_RECONSTRUCTION.md`: `7f003fd487c71d3a2dccf79b15df2101947e6aee14fe4f00ebfc65e76daa3dcd`; `artifacts/RESOURCE_CONTROL_FLOW.md`: `89f1591cd5c2233beee88a0b857eb1997488a5a7654bd2d63cb0a8a98fa7bbf5` | Binary-static; no native end-to-end acquisition |

**Reconciliation tooling:** merged PR #105, commit `9576fc573964bed624a08d878886ccad40a63d7a`, `agent/tools/ghidra/semantic-consolidation/{CONFLICTS.md,READABILITY_AUDIT.md,DOCUMENTATION_HANDOFF.md}`. It validated specific Ghidra 12.1.4 v98-derived staged input; do not extrapolate its 29 operations or 14 reviewed improvements to private v99.

**Authenticated retail binary used in the research:** `i76.exe` MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`.

## Reconciliation decisions and historical contrasts

| Claim | Prior/conflicting presentation | Proposed disposition |
|---|---|---|
| 00493160 is low-12-bit lattice height, not entire packed word; 004931A4 is interior code | Historical `TER_ReadPackedTerrainGridWord` alias | Correct semantics, retain historical alias as provenance |
| 00493550 returns numeric x87 ST0, has two double inputs, bilinear interpolation | v99 float presentation vs Pilot A double; old bound/transform label | Promote ST0 only; source declaration and final rounding unresolved |
| 004931C0 writes normal and returns its explicit output pointer in EAX | Pilot A void signature | **Correct** using 00493210/00493516 and caller 00440B8E/00440B93 as reconciled by #105 |
| 006442C0 spacing global | v99 `int` vs sampled float storage | **Defer** exact shared Ghidra type change; annotate conflict |
| VM node +10A8 | scalar import index vs live pointer | Phase-qualified semantics; no blanket pointer propagation into loader |
| Resource existence/selection | Historical “cache or search paths” name; registered-record lookup | Narrow to index/key membership and selected mounted-source row |
| Name acquisition vs size/release | Priority assumed uniform | Preserve conditional acquire priority and independent PIX-first size/release; collision behavior unresolved |
| 0042D5D0 reporter | Pilot C uncertainty about return | This authenticated retail body is a single RET; does **not** prove safe error handling |

Historical sources examined: `ref/mission_execution/MISSION_EXECUTION_CONTRACT.md`, `ref/mission_execution/HOST_COMMAND_ABI_CONTRACT.md`, `ref/game/i76_resource_acquisition_reference.md`, `ref/level_format/i76_runtime_level_and_terrain_format_notes.md`. Preserve `ref/` unmodified. Prior promoted class-1 scheduling, vehicle and renderer references describe different controlled scopes and are not superseded.

## Proposed reference changes

Create TER, FSM and RES reference pages with explicit scope and address crosswalk; add links to `manual/reference/README.md`. No other reference is rewritten. Add separate candidate v99 file-identity registry entry, **without** baseline promotion or a verified annotation-coverage claim.

## Reproduction and unresolved risks

This documentation reconciliation re-read accepted static evidence and GitHub's provenance; it did **not** rerun original instructions, replay private Ghidra 12.1.4 projects, run unmodified retail gameplay, or fully audit the uploaded v99 GZF. The v99 GZF's Java serialization envelope, embedded deflate member, descriptor CRC and exact sizes were verified independently; its annotation meaning remains pending a private Ghidra import. The shared migration reports two cosmetic caller-label regressions, five deferred RES layouts and five return propagations, an int/float spacing conflict and unknown VM trailing words. CI integrity evaluates repository policy, not scientific truth.

## Acceptance checklist

- [x] Cited runs and consolidated tooling were merged before this proposal.
- [x] Stable finding IDs, original addresses, paths, run-manifest digests and merge commits supplied.
- [x] Legacy references and principal contradictions assessed without rewriting historical sources.
- [x] Private GZF, executable and bulk decompilation excluded.
- [ ] Exact v99 Ghidra internal symbols/types/signatures audited. **Not a prerequisite for promoting independent retail-binary findings, but required for baseline promotion.**
- [ ] Trusted integrity success at exact proposed head.
- [ ] Human maintainer reviews and explicitly chooses to merge.

**Decision:** Pending human review. This record and its source-oriented reference pages are only proposals until merged.
