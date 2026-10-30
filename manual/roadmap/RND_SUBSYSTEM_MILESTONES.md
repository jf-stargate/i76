# RND original render pipeline — bounded worker milestones

**Status: proposed technical planning for human review; not original-code evidence, a promoted contract or authorization for maintained reconstruction.** Source accepted `main`: `8b0cf1912b3b717e2e2eb7500e44b08f37a2972a` (2026-10-29 PDT). **Binary publication track:** `i76exe`; advisory owner [RND](subsystems/RND.md) with OBJ, GEO, VEH, ENG and RES interfaces. **Capability path:** [OBJ-02 → CAP-CAMERA-01 → CAP-SLICE-01](CAPABILITY_ROADMAP.md). Research publication is governed by the current [agent bootstrap](../../agent/protocol/BOOTSTRAP.md) and [access policy](../../agent/protocol/access.yaml), not this plan.

**Finite completion definition:** [RND-v1 acceptance](subsystems/RND_ACCEPTANCE.md) sets required original-behavior, integrated and optional product gates. These bounded investigations **do not, by themselves, complete RND**. M-RND-01/02 provide accepted partial research evidence for RND-R1 ([#66](https://github.com/jf-stargate/i76/pull/66), [#67](https://github.com/jf-stargate/i76/pull/67)); M-RND-03 supports RND-R2/I1, M-RND-04 is gated downstream, and preparatory M-RND-05 independently probes original M06 visible-terrain/material source provenance. Neither M-RND-04 nor M-RND-05 alone proves a completed terrain-to-image path. Full G-RND-05 output integration remains gated on M-RND-03/04; G-RND-06 (approved original image oracle/tolerances) is still unassigned. Do not mark a gate complete on milestone count. The acceptance contract governs *why* further work is necessary; this document governs *how* to run bounded experiments.

This is a **second, parallel subsystem workstream**. An independently assigned CAP-CONTROL-01 investigation has now produced [merged partial PR #64](https://github.com/jf-stargate/i76/pull/64); selected-player initialization/input/frame integration remains open. The RND assignments below neither duplicate nor assert completion of that work. The overall project end state and maintained reconstruction authorization remain decisions under [project objectives](PROJECT_OBJECTIVES.md).

## Measurable RND capability target

**CAP-RND-PRODUCER-01 (RND-local intermediate gate, subordinate to CAP-CAMERA-01):** In a repeatable bounded original-instruction emulator, initialize an original camera/view context and original spatial arena, register a stock vehicle with the original world registry, execute the original `00457FF0` visibility producer, and verify that **original instructions** (not a harness-authored queue node) produce a traceable spatial work record that original `0048FAC0` can consume. Record source object, work kind, priority/bucket and any original clip/submit handoff, and explicitly identify still-supplied renderer services.

This is not yet a native pixel image, live Windows frame, or original scheduler invocation. **A negative or all-culled authentic producer experiment is meaningful evidence but does not complete this positive integration gate.**

## Dispatch order and dependencies

```text
                 merged original RND/camera/vehicle evidence
                                │
                  ┌─────────────┴─────────────┐
                  ▼                           ▼
     M-RND-01 native queue producer    M-RND-02 camera continuity
       ACCEPTED bounded #66               ACCEPTED bounded #67
                  │                           │
                  └─────────────┬─────────────┘           M-RND-05
                                ▼                     M06 visible-terrain
                M-RND-03 producer → consumer           and material path
                   READY with #66 + #67                  READY / parallel
                                │                           │
                                ▼                           │
                M-RND-04 native clip/draw boundary          │
                      conditional after 03                 │
                                └──────────────┬────────────┘
                                               ▼
                             later joint M06 terrain + image
                               gate (not dispatched here)

 Separate CAP-CONTROL-01 selected-player work ───────────┐
                                                       └─► later CAP-SLICE-01
                   (not a prerequisite for M-RND-01/02)
```

| Milestone | State for dispatch | Required predecessor | Primary outcome |
| --- | --- | --- | --- |
| **M-RND-01** | **ACCEPTED bounded evidence** ([PR #66](https://github.com/jf-stargate/i76/pull/66)) | Accepted camera projection/arena/VCF registration + RND index | Native `00457FF0` work-record production from registered objects; not RND-R1 closure |
| **M-RND-02** | **ACCEPTED bounded evidence** ([PR #67](https://github.com/jf-stargate/i76/pull/67)) | Accepted original native-root camera and math startup | Persisted original `004C2730` camera/view data across controlled pose changes; not RND-R1 closure |
| **M-RND-03** | **READY** | Accepted [#66](https://github.com/jf-stargate/i76/pull/66) producer and [#67](https://github.com/jf-stargate/i76/pull/67) camera results; reconcile exact state and service contracts | Original-generated record consumed by original `0048FAC0` in one continuous emulator state |
| **M-RND-04** | **CONDITIONAL** | M-RND-03 producer/consumer positive path | Bounded original `00471FD0 → 0047C2F0/00487EA0` clip/draw execution with independent geometry/output checks |
| **M-RND-05** | **READY, preparatory** | Authenticated M06 terrain/WRLD loader evidence and original software terrain LOD map; independent of M-RND-03 | Original M06 visible-terrain tessellation/primitive and material-source ownership, without claiming full G-RND-05 rendering/pixels |

**Dispatch policy:** Milestone ID is a stable *objective*, not a run ID or lock. Create one new owned `agent/runs/i76exe/<run-id>/` per investigation and one PR each. Concurrent workers use distinct local directories under `/media/neon-remote/prj/i76`; inspect existing state and never overwrite another agent's checkout or scratch. After accepted #66/#67, **M-RND-03 and preparatory M-RND-05 may start concurrently** in different worker sessions. M-RND-04 still waits for positive M-RND-03 evidence; full M06 terrain-to-image integration waits for the source contracts from both paths. Do not dispatch conditional tasks on a timer.

## M-RND-01 — Original visibility producer and bucket ownership (P0)

**Question:** Can original `00457FF0`, operating on real `004572B0` registered stock vehicle world entries and a source-backed view/arena context, create original kind-6 work records in original spatial buckets without the harness writing nodes, head pointers or bucket indices?

**Evidence/gap:** [Accepted render traversal](../../agent/runs/i76exe/i76exe-20261023T062154Z-62e3a718/artifacts/RENDER_TRAVERSAL_AND_BUCKET_CONTRACT.md) statically identifies the producer and dynamically verifies `0048FAC0` consuming a *synthetic* kind-6 record. [Accepted camera/arena](../../agent/runs/i76exe/i76exe-20261023T153639Z-95865b83/artifacts/CAMERA_TYPE10_ARCHITECTURE.md) executes original `0048F9B0` with allocator substitutes and original projection initializer. [Accepted native registered camera](../../agent/runs/i76exe/i76exe-20261027T031313Z-32de4d1e/artifacts/MILESTONE_B_NATIVE_CAMERA_NUMERICS.md) supplies a verified stock object/entry pattern. **Do not silently treat world registry `00542830` as the class-update list `0054B204`.**

**Original anchors:** `00457FF0`, `004572B0`, `00542830`, `0048F9B0`, `0048FE10`, work queue `0048FAC0`, ordinary kind-6 consumer `0048F4C0`, view `004C2730`, producer frame callers `00401CC0/00401FA0`. Use sparse PE anchor checks to confirm exact instruction sites, data layout and native source identity; work-record semantics may differ by kind.

**Experiment and independent controls:**
1. Bootstrap current accepted `main`, verify private retail PE, ZFS/GTSi/bus resource digests and private annotated v97 GZF; use fresh read-only Ghidra project and the accepted original VCF/registry, arena and camera initializer programs. If historical reproduction is incomplete, establish a self-contained new procedure.
2. Original `0048F9B0` initializes arenas with only documented allocator responses. Construct and register at least one real stock bus or GTSi using original routines; retain actual active-world entries. Initialize original `00405970` projection with a **controlled but explicitly recorded** view, not a claimed retail follow-camera.
3. Execute original `00457FF0`; instrument original visits/visibility branches and producers, original insertions `0048FE10`, work-record owner/class/kind/priority/bucket fields, pre/post table heads/counts. Do **not** write synthetic queue nodes or fill a bucket to force success.
4. Vary one controlled camera/visibility condition to attempt one visible and one rejected or empty case. Independently inspect zero-object/empty-world control and no unexpected record creation. If positive kind 6 is unreachable, report the exact original branch, measured inputs and missing prerequisites, not manufactured geometry.
5. Repeat successful or bounded-failure original producer execution in a separate fresh process; compare source traces and derived records with a standalone verifier.

**Complete:** At least one source-identifiable **original-produced kind-6** work record is actually inserted into an original arena bucket under original `00457FF0`, with original object identity, producer PCs, insertion, and a negative/empty control independently validated. The bucket need not yet be consumed in this milestone. **Partial:** only producer entry/culling or a different work kind, static source map, or supplied queue record. **Inconclusive:** missing verified fixture or essential initialization. **Invalid:** unaccounted manual node/bucket writes, wrong object ownership, invalid numeric context or unexplained service effects presented as original.

**Deliverables:** bounded report, producer event trace with kind/owner/bucket and branch conditions, before/after arena and world registry summaries, private input hashes, PE anchor map, originals-versus-services ledger, fresh-project reproduction commands and independent verification with negative control, `findings.json`, `manifest.json`, `validation.json`, documentation-impact handoff. Open a run-only reviewable PR; no canonical changes.

## M-RND-02 — Camera pose, view provenance and continuity (P0, independent)

**Question:** Given original `0045EBD0` native root, selected stock vehicle VCF/VLOC attachment and original active-world registry, how do original camera callback(s) update the **same** `004C2730` persistent view across controlled root-pose changes, and which fields/producers become valid for later visibility?

**Evidence/gap:** [Native selected camera](../../agent/runs/i76exe/i76exe-20261027T031313Z-32de4d1e/artifacts/MILESTONE_B_NATIVE_CAMERA_NUMERICS.md) completed `00406AB0` through `00437F90/00472990` for selected GTSi and bus, including a differential zero-root → NaN control, but used an explicitly invoked callback and supplied frame context. [Frame startup](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/FRAME_INITIALIZATION.md) explains missing original math `00493C50` startup effects. [Camera/type-10](../../agent/runs/i76exe/i76exe-20261023T153639Z-95865b83/artifacts/CAMERA_TYPE10_ARCHITECTURE.md) defines `00405970/004C2730`. No prior run demonstrates complete live selected-player post or original camera-mode scheduling.

**Original anchors:** `0045EBD0`, `004AD6F0`, `004572B0`, `00405970`, `00406AB0`, `00437F90`, `00472400`, `00472990`, `004C2730`, source view transform `00472D30` and frustum classifier `00472C10`; static original frame handoff `00403E64 → 00401C90`.

**Experiment and controls:**
1. Build the native selected vehicle/attachment/registry and original projection with verified retail resources; preserve original math seed `00493C50`. Run original camera callback **directly, labeled as a controlled entry**, avoiding all live selected-post/init claims and the separate CAP-CONTROL-01 initialization/integration work.
2. Compare at least **two distinct controlled original-root pose states** over **two or more consecutive camera calls** in a single persistent emulator, retaining camera smoothing state, with a separate cold-start repeat. Use original caller/field-read anchors and report whether transforms originate from native producers or controlled pose writes.
3. Record the 118-dword camera record `004C2730` and known output six-double view region, selected-mode/guard inputs, basis/Gram errors, finite predicates, and source-to-camera transformation. Include a valid-root versus zero/degenerate-root negative control; avoid false numerical-parity inference.
4. Independently calculate only demonstrable invariants (e.g., finite outputs, pose-dependent diffs, persistent write chronology) from source trace and source float/double bytes. If the original camera's state is unchanged across inputs, identify guard/setup evidence and publish partial negative result.

**Complete:** Two distinct, source-identified pose states yield reproducible, **explained and measured** differences in original updated `004C2730`/six-double view fields over repeated original camera callbacks with preserved smoothing state; controlled reset/degenerate-state comparison, original entry/return and independent checks. **Partial:** finite single state, explicit callback only without state continuity, unexplained synthetic root or numerically invalid outputs. **Invalid:** a camera context manufactured in the harness and claimed as original callback state, hidden field writes, or selected-post success inferred from direct camera invocation.

**Deliverables:** camera record offset/meaning table with bounded confidence, original call/field events, typed pose/view samples, numerical condition checks, negative and repeat controls, original-vs-service ledger, independent verifier, full fresh-project reproduction, immutable run + PR + documentation-impact handoff. **Do not** edit original Ghidra symbols or another worker's run.

## M-RND-03 — Genuine original producer → consumer pipeline (P1; gated)

**Question:** Can the **same** constructed/registered original world and original arena, with a measured original camera/view record, run original `00457FF0` and then original `0048FAC0` so producer-created work records trigger original `0048F4C0 → 0045D100/0045D530 → 00471FD0` without queue-node injection?

**Inputs/prerequisites:** M-RND-01 producer evidence with original record ownership, M-RND-02 camera record source/pose semantics, accepted GEO/TMT native construction baseline, private verified stock resources. Their independently validated evidence must be available at the start; do not require M-VEH-02 or a completed live selected post.

**Experiment:** retain one original emulator memory state across arena initialization, registration, camera/visibility, producer, bucket consumer and recorded material/polygon calls. Compare with zero-object, all-culled and **synthetic-record control** (labeled as an external baseline only). Verify producer/consumer refer to the **same** record address, owner and bucket, and observe original queue clearing and path-specific clip/draw substitutions. Test one stock bus and/or GTSi. Do not join independently produced private traces and call that uninterrupted execution.

**Complete:** independently checked original-generated queue record reaches the original consumer in one memory state and causes a genuine downstream original GEO/polygon wrapper path; record exact original producer and consumer events, source geometry identity and explicit clip/draw substitutions. **Partial:** production and consumption individually proven but not linked; positive record culled before GEO; another record kind only. **Blocked:** original producer never emits an eligible record; record the prerequisite rather than synthesizing one.

**Deliverables:** one bounded run-only PR, same-record proof and event timeline, resource/geometry/control identities, explicit numerical/graphics substitutions, independent repeat, full reproduction and documented negative paths. **No pixel-output claim.**

## M-RND-04 — Native clip/draw and material handoff (P2; conditional)

**Question:** Once source-backed scene producer→consumer→polygon submission exists, can a bounded original `00471FD0` path reach original `0047C2F0` clip and `00487EA0` draw behavior (or the correct backend-specific targets) with valid camera, geometry, material and scratch ownership, and measurable geometry/output invariants?

**Prerequisite:** accepted M-RND-03 positive pipeline. Read the original dispatch and inspect the exact backend branches before choosing a clip/draw consumer. VQM/M16/PIX decode or Windows surface dependencies may require independent RES/GEO evidence, not implicit success.

**Experiment:** remove **one** documented clip/draw substitute at a time, retaining other explicit peripheral services; verify memory/scratch ownership, raster bounds, original face and material identity, selected primitive counts, and whether the original routine returns. Compare with a controlled clipped/culled geometry or zero-face case. If pixel buffer output becomes measurable, specify its format/origin and independently verify a bounded subset; otherwise claim only native clip/draw entry/return with observable original-side records. Reproduce on a fresh source project.

**Complete:** one original clip/draw target executes through a measured, owned geometry case with independently verified output or state semantics, a distinct negative control, and no unexplained invalid memory state. **Partial:** reaches clip/draw entry but external service must still replace its body; native but no trustworthy output; historical synthetic-only record. **Invalid:** asserts pixels or GPU equivalence from polygon wrapper counts.

**Deliverables:** isolated original-code run, candidate clip/draw interface, original versus service ledger, bounded control records, verifier and reproducible source/fixture list. Full software or D3D picture is a **separate future acceptance gate**, not required here.

## M-RND-05 — Original M06 visible-terrain primitive and material provenance (P1, independently dispatchable)

**Question:** With byte-verified retail M06 WRLD/TDEF/ZMAP/ZONE and TER pages, can the original engine's **visible terrain** selection/tessellation path be traced and preferably executed to an original-authored terrain primitive and source material identity, without confusing this with the already validated **physics** height sampler or fabricating raster output?

**Why independent:** [M-RND-03](#m-rnd-03--genuine-original-producer--consumer-pipeline-p1-gated) owns the *stock vehicle* class-1 world-visibility → kind-6 bucket → geometry-consumer bridge. This milestone owns the *M06 terrain/environment* source-to-visual-primitive boundary and **does not run or assert completion** of M-RND-03. The finite [RND-v1 contract](subsystems/RND_ACCEPTANCE.md) requires vehicle **and** M06 terrain/environment contribution. It is permissible to begin source-backed terrain producer work before M-RND-03/04 complete; **positive full terrain-to-image acceptance G-RND-05 remains gated** on downstream renderer integration.

**Source evidence, original anchors and prerequisites:**
- [Accepted M06 original terrain/physics run](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/manifest.json), [report](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/AUTHENTIC_TERRAIN_PHYSICS.md), [reproduction](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/REPRODUCE.md) and [TER discovery](subsystems/TER.md): original `004B8A10`, `00493910/00493960/004939D0/00493BD0`, `00471400/00493080`, `006442C0/006442C4/00644380` and actual 16 M06 TER pages with validated material bits. **These establish sampling/physics, not rendering.**
- [Historical terrain visual LOD reference](../../ref/level_format/i76_runtime_terrain_lod_reference.md) describes **binary-static/analytical** `004929B0`, `00490A00`, `004911E0`, `00491A30`, `004922F0/004924B0` and requires fresh retail opcode/xref verification; do **not** assume the old symbol names or complete native rendering from the historical model.
- For optional roads, historical `004B8780` RSEG source/LOD associations may help identify material or UV routing, but editor road-kind-to-terrain material class is **not** direct proof of rendered road texture. Do not investigate polygon **collision** candidate list `0052B94C` (separate M-TER-02).
- Private exact retail PE, ZFS, M06 MSN/WRLD/ZMAP/TER and annotated v97 GZF, with full digests and licensed local storage; original Ghidra 12.1.4 input and all inherited substitutions logged. No pixels or private asset dump is published.

**Experiment and controls:**
1. Pin current accepted `main`, accepted protocol and RND-v1 fixture requirements; read earlier M06 TER original-run data, visual LOD historical code and current renderer traversal reports. Verify private source identities. Resolve **original** callsite and dataflow from loaded M06 terrain/view to visible-region selection, subdivision and eventual triangle/primitive/submit handoff.
2. Construct original M06 terrain state using the accepted loader, then try the smallest reproducible *original-instruction* bounded terrain-visibility/LOD/primitive production with a **controlled, recorded camera**. Log original PCs/branch operands, source TER page/row/col, resulting world positions, material class and producer-to-output buffer/face ownership. Clip, draw, texture decode and device operations may remain substituted if explicit.
3. Independently check vertex heights/material classes against source TER bytes and the accepted typed grid conventions; check triangle winding/ordering or UV only when source evidence supports them. Include a second view/terrain-cell contrast or a clearly rejected/empty-region control and a fresh-project replay. Test that the harness did not author the claimed original primitive output or manufactured a terrain-render list.
4. If native original terrain emission is blocked, publish the exact original caller/precondition, last executed original PC, static writer/reader inventory, and minimal missing initialized state; distinguish a **partial but useful interface map** from positive runtime production.

**Complete:** at least one original-instruction visible-terrain LOD/tessellation path uses authenticated M06 terrain bytes to emit an identifiable terrain primitive or equivalent original-render handoff record, with original writer evidence, material/position provenance, an independent typed source check and negative/contrast control. **Partial:** original renderer producer/primitive path is mapped but not executed, or original source page/material is identified only as physics input. **Inconclusive:** missing authenticated scene or essential initialization prevents testing. **Invalid:** synthetic mesh/vertex list is attributed to original code; material word is mislabeled texture/UV; outputs rely on unreported service writes.

**Deliverables:** one immutable `i76exe` research run and reviewable PR with source/VA map, actual terrain asset identities, original primitive events or precise blocker, source-to-geometry material ledger, independent verifier, reproducibility steps, negative and fresh-repeat control, and `artifacts/DOCUMENTATION_IMPACT.md`. **Do not** modify accepted run/reference files, consumer worker state, project governance, or implement an independent maintained renderer. Do not mark G-RND-05 or RND-R2/I1 complete merely from source-facing producer evidence.

## Relation to RND-v1 completion and new worker dispatch

The contract [`subsystems/RND_ACCEPTANCE.md`](subsystems/RND_ACCEPTANCE.md) sets the finite target scenario and a separate acceptance decision. The present worker queue is not an exhaustive rendering backlog. After a reviewed research run, the coordinator must map observed findings and blockers to **RND-R1**, **RND-R2**, **RND-I1** and the specific `SC-RND` tests rather than continuing a function-by-function search.

- **M-RND-01 → RND-R1** and **M-RND-02 → RND-R1:** merged [#66](https://github.com/jf-stargate/i76/pull/66) and [#67](https://github.com/jf-stargate/i76/pull/67) provide bounded accepted evidence, not a full ratified RND-R1/M06 fixture.
- **M-RND-03 → RND-R2/I1:** now assignable based on accepted #66/#67, but must **join their original behavior in one emulator state**, not splice independent traces. **M-RND-04** remains downstream gated. Neither alone proves original terrain/material output or a framebuffer.
- **M-RND-05 → G-RND-05 preliminary source/primitive provenance:** independently assignable M06 visual-terrain producer experiment, but **full G-RND-05 terrain→material→image acceptance stays blocked** until actual integrated renderer evidence from M-RND-03/04 and further necessary work. **G-RND-06** original image comparator/tolerances remains unassigned, subject to maintainer fixture decision. No independent maintained code is authorized.
- **RND-P1** is not assigned to current original-binary researchers; independent maintained implementation requires its own authorization.

## Common validation and publication contract

For every worker:

- Start with [repository AGENTS](../../AGENTS.md), [bootstrap](../../agent/protocol/BOOTSTRAP.md), current `main` and [RND discovery](subsystems/RND.md); then read the exact linked merged run **manifest, findings, artifacts and source code**, not only an old conversation summary.
- Confirm accepted protocol/schema **at run start**; project planning does not lock future versions. Provenance must include original private PE, ZFS, GZF and any mission resource identities actually used.
- Separate **static original opcodes**, **original-instruction emulation**, **independent analytical checks**, **deliberately controlled fixture state** and **replaced OS/CRT/resource/math/render functions**. No fabricated record or output is positive proof. Log failures and negative branches.
- Produce complete **new-run reproduction** independent of undocumented local paths (old render runs did not always publish `REPRODUCE.md`), a meaningful standalone verifier and a byte-identical or scientifically explained repeat when possible. Check counters are *not* program completion percentage.
- Use separate scratch under `/media/neon-remote/prj/i76`; keep proprietary binaries/resources and private Ghidra databases local; do not publish private raw logs or large resource dumps.
- Publish **only one new immutable owned run per PR** with required `manifest.json`, `findings.json`, `validation.json`, artifact hashes, research report, `artifacts/DOCUMENTATION_IMPACT.md` and precise failure/limits. Do not modify other runs, canonical references, governance or agent branches, and **do not merge**.
- Review through normal protected `main` with required green trusted `integrity`, then human scientific/technical acceptance. Research acceptance is not automatic technical promotion.

## Suggested CLI first-turn prompts (current assignments)

Use a **new** Codex session for each milestone, reading the full accepted section above. Do not dispatch M-RND-04 until M-RND-03's positive path is accepted.

**Worker A — M-RND-03 (READY)**
```text
Bootstrap independently from current protected main at https://github.com/jf-stargate/i76, using AGENTS.md and agent/protocol/BOOTSTRAP.md.
Read manual/roadmap/RND_SUBSYSTEM_MILESTONES.md (M-RND-03), manual/roadmap/subsystems/RND.md, and manual/roadmap/subsystems/RND_ACCEPTANCE.md.
Read and reproduce accepted PR #66 M-RND-01 original kind-6 visibility producer and PR #67 M-RND-02 original camera continuity, plus earlier original synthetic kind-6 consumer reference. Reconcile their incompatible controlled camera/root/setup contexts explicitly.
Create the smallest original-instruction same-emulator-state sequence: native stock vehicle/root+registry, original camera 00406AB0 and persistent 004C2730, original 00457FF0 work-record producer, original 0048FAC0 consumer and downstream 0048F4C0/0045D100/00471FD0 where reachable. Do not inject queue nodes or concatenate independent trace files to claim an integrated result. Record exact same-record address/owner/bucket, record 0x0A side path or an explicit documented exclusion, and original-vs-substituted services.
Run negative/culled and repeat controls, independent verifiers and complete reproduction. Publish exactly one new immutable i76exe research run and reviewable PR, no canonical edits or merge. Use an isolated workspace under /media/neon-remote/prj/i76, distinct from the other worker.
```

**Worker B — M-RND-05 (READY, preparatory)**
```text
Bootstrap independently from current protected main at https://github.com/jf-stargate/i76, using AGENTS.md and agent/protocol/BOOTSTRAP.md.
Read manual/roadmap/RND_SUBSYSTEM_MILESTONES.md (M-RND-05), manual/roadmap/subsystems/RND.md, manual/roadmap/subsystems/TER.md and manual/roadmap/subsystems/RND_ACCEPTANCE.md.
Investigate source-backed original M06 visual terrain path independently of M-RND-03: original M06 TDEF/ZMAP/ZONE/TER loading, visible region and terrain LOD producer 004929B0, 00490A00, 004911E0, 00491A30, 004922F0/004924B0, validating original opcode/call ownership against the retail PE rather than assuming historical names.
Attempt a bounded original-instruction native terrain primitive/handoff produced from authenticated M06 terrain under a controlled documented view. Verify source page/coordinates/heights/material, original writer PCs and negative/contrast case with an independent check and fresh replay. If blocked, publish exact missing original state/branch and a useful static source-to-visual-interface map as partial evidence. Do not conflate terrain physics, road material classes, visible texture/UV, pixel rasterization or polygon collision; do not claim completed G-RND-05.
Publish one isolated immutable i76exe research run, service ledger, full reproduction, documentation impact and reviewable PR. Do not touch Worker A's workspace or PR; do not merge.
```

Any new source findings must be reviewed against the finite RND-v1 acceptance contract before spawning further milestones.
