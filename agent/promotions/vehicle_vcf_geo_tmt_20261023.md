# Vehicle native VCF, GEO and TMT construction — promotion decision

**Decision state:** Candidate until the human maintainer merges the containing promotion PR. Once merged, the merge commit is the acceptance record; consult Git history rather than treating this text alone as an approval.  
**Research scope:** Retail `i76.exe`; two original-instruction Ghidra EmulatorHelper sessions (GTSi and bus).  
**Proposed target:** [vehicle construction reference](../../manual/reference/engine/vehicle_construction.md) and [reference index](../../manual/reference/README.md).  
**Original accepted base:** `f29379db9c7eccef91f6f93bc5984ce9dc6b9e4a`.  
**Source research:** [PR #16](https://github.com/jf-stargate/i76/pull/16), **merge commit** `a767860237b5a845db4299cb6f90984c48157c0a`, [immutable run](../runs/i76exe/i76exe-20261022T232710Z-96c58505/manifest.json).  
**Protocol:** 1.0.1; source run schema: 1.1.0.

## Proposed decision and evidence boundaries

Promote **four narrowly scoped, high-confidence original-code-emulation observations** from the merged v2.4.0 evidence record. These describe original retail x86 executed under Ghidra with external services substituted. They do **not** establish fully native Windows gameplay, device rendering, texture pixel materialization, physical/damage behavior or teardown correctness. The fifth source finding (render-surface ownership) remains unresolved and is not promoted as a positive claim.

## Binary and baseline provenance

- Source executable: retail `i76.exe`, MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`.
- Source retail archive: `I76.ZFS`, MD5 `6dd57b1627d73e814247c0d9521f9778`, SHA-256 `0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d`.
- Private Ghidra baseline: 12.1.4, program `i76_mission_v97_verified_names`, annotated v97 GZF SHA-256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`.
- These hashes are recorded in the source run manifest. This promotion reviews *published evidence*; it does not claim a new independent hashing or execution of private inputs.

## Finding-by-finding crosswalk

| Finding ID in merged run | Original retail function(s) | Principal artifact and its source-manifest SHA-256 | Proposed disposition |
|---|---|---|---|
| `i76exe-v24-native-vcf-construction-two-vehicles` | `004AD6F0`, `004B75A0`; native VDF/WDF/CDF dispatch | [native_vehicle_resources.tsv](../runs/i76exe/i76exe-20261022T232710Z-96c58505/evidence/native_vehicle_resources.tsv): `9ea1c890ec8523464eccc572a018fb8a00a27447de053b4eeb49673a466826ce` | Accept tested native-instruction construction of 46/44 world objects, 31/29 measured parts and four class-30 weapon nodes per vehicle, **not** full gameplay. |
| `i76exe-v24-native-tmt-owner-bindings` | `00449680`, `0044AB90`, `0044AC80` | [native_vehicle_resources.tsv](../runs/i76exe/i76exe-20261022T232710Z-96c58505/evidence/native_vehicle_resources.tsv): `9ea1c890ec8523464eccc572a018fb8a00a27447de053b4eeb49673a466826ce`; [resource digests](../runs/i76exe/i76exe-20261022T232710Z-96c58505/evidence/retail_resource_digests.json): `82d045d62a56870368717ee4c9ba50ced35e3719458a0c69b6f3f076ab70d319` | Accept 24/22 sampled material registrations and differentiated owner-slot/TMT cache identities; do not infer actual rendered surface assignment. |
| `i76exe-v24-native-geo-constructors` | `004469A0`, `00446C90` | [native_vehicle_resources.tsv](../runs/i76exe/i76exe-20261022T232710Z-96c58505/evidence/native_vehicle_resources.tsv): `9ea1c890ec8523464eccc572a018fb8a00a27447de053b4eeb49673a466826ce`; [resource digests](../runs/i76exe/i76exe-20261022T232710Z-96c58505/evidence/retail_resource_digests.json): `82d045d62a56870368717ee4c9ba50ced35e3719458a0c69b6f3f076ab70d319` | Accept eight non-null original GEO constructor results from seven stock resource identities under substituted resource supply. |
| `i76exe-v24-native-body-mesh-cache-reuse` | `004466C0` | [native_vehicle_resources.tsv](../runs/i76exe/i76exe-20261022T232710Z-96c58505/evidence/native_vehicle_resources.tsv): `9ea1c890ec8523464eccc572a018fb8a00a27447de053b4eeb49673a466826ce` | Accept tested group `0 → 4 → 0` pointer reuse for **one body node per vehicle** without structural transform changes. Do not generalize to all states/teardown. |
| `i76exe-v24-tmt-to-render-surface-ownership-open` | `0044A0B0`; downstream renderer unverified | [open issues](../runs/i76exe/i76exe-20261022T232710Z-96c58505/artifacts/OPEN_ISSUES.md): `f42c74b1c67e1853340275026c27fd23912460c8ed52333f1765a2dbba15aa5a` | **Defer:** no claim of TMT-to-pixel/surface/material/render-pass completion. |

Other backing records: [architecture delta](../runs/i76exe/i76exe-20261022T232710Z-96c58505/artifacts/ARCHITECTURE_DELTA.md) SHA-256 `94dc87e9d8aee05430350df05b16d2f568211af020534fa5b4a559f33fe731c2`; [source-layout hypothesis](../runs/i76exe/i76exe-20261022T232710Z-96c58505/artifacts/SOURCE_LAYOUT_DELTA.md) SHA-256 `935d65a63a8687ae1d1f6c27232895157e32936fdcb476083826724799c70fc1`. The research run reports 341/341 local checks and partial reproducibility with private inputs. The original probe is [here](../runs/i76exe/i76exe-20261022T232710Z-96c58505/scripts/I76_IntegratedVcfResourceProbe.java) (SHA-256 `e648cd1de131ad2524e6cd79579251868c119d7e0907f0dce0b3decb4d22eb06`).

## Reconciliation against existing documentation

- [Archived vehicle/FSM object-model reference](../../ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md) documents `world_object + 0x70` as class-specific runtime and class-1 vehicle identity from older v64–v76 evidence. This promotion **confirms/narrows** that relationship for the two sampled top-level VCF executions, and distinguishes temporary parser context `+4` from final runtime ownership. It does not supersede the reference's mission-FSM, damage or teardown observations.
- [Mission execution reference](../../ref/mission_execution/README.md) documents v97 mission/runtime behavior; the new VCF reference concerns vehicle/resource construction only, **not** new FSM host-command or actor-binding conclusions.
- The source [architecture delta](../runs/i76exe/i76exe-20261022T232710Z-96c58505/artifacts/ARCHITECTURE_DELTA.md) distinguishes `004B75A0` (100-byte VGEO path) from `004B7800` (different 120-byte path). Preserve this distinction.
- Translation-unit groupings of GEO and TMT routines remain **hypotheses**, not promoted original source-code names. No original `.c` or `.h` boundaries are claimed.
- [PR #21](https://github.com/jf-stargate/i76/pull/21) was an **open draft** at preparation and is not part of the evidence accepted by this promotion. A later merged run may require a separate reconciliation.

## Explicit exclusions and remaining tests

- `0044A0B0` texture refresh, MAP/M16/VQM decoding, palette, lighting, material animation, `0045CBE0`/`0045D100`/`0045D530` render dispatch, persistent cache release and physical/damage/gameplay effects are unverified in this promotion.
- Each vehicle was constructed in a *fresh, separate* emulation session, so no proof of two sequential vehicles sharing persistent cache state or cleanup after teardown.
- Resource, CRT, heap, palette, geometry-refresh, lighting, ancillary and drawing services were substituted as recorded in the run.
- No Ghidra program/symbol changes, legacy `ref/` edits, original binary/asset uploads, or retroactive run modifications are part of this PR.

## Review/acceptance

The human maintainer should verify the four selected claims against their linked source records, confirm the bounded wording in `manual/reference/engine/vehicle_construction.md`, review the index change and observe a green base-owned `integrity` check on this exact PR head. A merge accepts **this narrow interpretation**, not every claim from the evidence run.
