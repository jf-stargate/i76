# Documentation impact — retail vehicle spawn status and VLOC camera eligibility

## Research identity
- Run ID: `i76exe-20261026T235108Z-12215047`
- Track: `i76exe`
- Original base: `6b4176dfb289997fae432bb50885adda8d4f6dca`
- Research draft PR: [#40](https://github.com/jf-stargate/i76/pull/40); merge pending
- Input provenance: `manifest.json` — retail `i76.exe` MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`, private Ghidra v97 GZF SHA256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`.
- This handoff follows the newly accepted documentation-stewardship protocol 1.0.3; original research base/protocol version remain unaltered for provenance.

## Documentation disposition
- Classification: **candidate update, pending human evidence reconciliation**. No immediate canonical modification.
- Suggested target: existing `manual/reference/engine/vehicle_construction.md` for vehicle spawn flag assignment and conditional VLOC type-`0x28` attachment prerequisites; optionally create a focused vehicle-camera lifecycle reference in a separate reviewed documentation PR when camera execution evidence matures.
- Legacy context: `ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md` (world object status `+0x10`, class 1 at `+0x6C`, runtime `+0x70`, active entries at `004572B0`). Preserve the existing legacy file unchanged.
- Prior accepted related evidence: merged VLOC run `i76exe-20261024T232546Z-11d4e2ec`, whose `004AE000` conditionally creates the attachment at `runtime+0x398` when original `00458BF0` sees status bit `0x10`.

## Evidence-linked candidate findings

1. **`i76exe-20261026T235108Z-12215047-local-identifier-flag-policy` — proven/high within original-x86 emulation.** At `00451180` / `004512A1`, the session-local ID stored at `00541028` (low 16 bits) selects `0x10` for a matching vehicle, `0x20` otherwise. Status is set before VCF call `004512E5`. Method: 4 original-x86 Ghidra scenarios; evidence `evidence/status_flag10_original_x86.tsv` SHA256 `0bbae7ee9bbeeb775e0be0c50f4b52a4016d2d22390d8c88c2897f5cb37b471b`, `evidence/retail_opcode_anchors.tsv` SHA256 `d155ff1245b9c50d3dec4b1419ce6bf2613b9006928ce1de019db5fa41a2c43c` and Ghidra audit script. **Impact: add narrow note on local network-spawn policy**. Limit: resource lookup/formats intercepted and complete VCF not executed.
2. **`i76exe-20261026T235108Z-12215047-ordinary-selector-flag-policy` — proven/high within original-x86 emulation.** At `004513C0` / `0045146E`, fifth argument zero selects `0x00020000`; nonzero selects `0x00010010` before VCF call `0045148B`. 3 original-x86 scenarios independently reach the original VLOC bit predicate `00458BF0` with expected outcome. Same trace SHA256 as above. **Impact: add separate spawn-policy rule**; do not collapse with the network ID rule.
3. **`i76exe-20261026T235108Z-12215047-local-id-session-global-owner` — derived/high.** Global `00541028` is written at `00452D79`, read by `00454E30`; network/game-loop/mission callers reach `00451180`. Evidence `evidence/call_edges.tsv` SHA256 `7a20b642972a6315e19c894a0bfbf2dedca0bf3b718acadf6a90d545818f006d` checked from original PE call displacements, and `scripts/I76_Flag10CallgraphAudit.java` SHA256 `faa22c0f8283ae1be565d24f9540af27d513137e03be6507a77e4343a53d3c4d`. **Impact: support caller chronology and identity qualification**.
4. **`i76exe-20261026T235108Z-12215047-continuous-eligible-vcf-vloc-camera-unresolved` — unresolved/unknown.** Full original eligible-root constructor `004AD6F0` → VLOC `004AE000` → native class-`0x28` binder `00461970` → default camera `00406AB0` has not been executed continuously. **Impact: defer numerical camera-pose assertions and class-lifecycle promotion** until native execution with correctly initialized class registry and x87 service validation.

## Reconciliation notes
- The new findings explain **how two creation paths supply the status required by the previously verified VLOC guard**. They do not contradict the earlier finding that status bit `0x10` is required for type-`0x28` attachment creation.
- **Do not generalize the bit as a global “player” discriminator**: its documented policy differs between creation paths, and other object classes and status writers remain to be audited.
- Original retail x86 emulator checks (95/95 independent assertions, two byte-identical traces), not a full Windows retail gameplay frame.
- Recommended promotion dependency: after PR #40 is reviewed and merged, reconcile these findings with accepted VCF/VLOC runs and the current vehicle-construction reference. A single integrated VCF/class-attachment/camera run would strengthen the final camera document.

## Publication boundary
No canonical file changes are proposed by this research PR. A maintainer-designated documentation steward may generate a separate evidence crosswalk, promotion and `manual/reference/` PR after explicit review. No direct modifications to `ref/`, `agent/promotions/` or `manual/reference/` are authorized here.
