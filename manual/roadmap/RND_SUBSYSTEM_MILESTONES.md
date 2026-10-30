# RND original render pipeline — bounded worker milestones

**Status: proposed technical planning for human review; not original-code evidence, a promoted contract or authorization for maintained reconstruction.** Source accepted `main`: `8b0cf1912b3b717e2e2eb7500e44b08f37a2972a` (2026-10-29 PDT). **Binary publication track:** `i76exe`; advisory owner [RND](subsystems/RND.md) with OBJ, GEO, VEH, ENG and RES interfaces. **Capability path:** [OBJ-02 → CAP-CAMERA-01 → CAP-SLICE-01](CAPABILITY_ROADMAP.md). Research publication is governed by the current [agent bootstrap](../../agent/protocol/BOOTSTRAP.md) and [access policy](../../agent/protocol/access.yaml), not this plan.

This is a **second, parallel subsystem workstream**. An independently started CLI agent already owns CAP-CONTROL-01 selected-player post/init; the RND assignments below do not implement or assert completion of that work. The overall project end state and maintained reconstruction authorization remain decisions under [project objectives](PROJECT_OBJECTIVES.md).

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
         READY / independent              READY / independent
                  │                           │
                  └─────────────┬─────────────┘
                                ▼
                M-RND-03 producer → consumer
                      after 01 + 02 evidence
                                │
                                ▼
                M-RND-04 native clip/draw boundary
                      conditional after 03

 Active external CAP-CONTROL-01 selected-player agent ──┐
                                                       └─► later CAP-SLICE-01
                   (not a prerequisite for M-RND-01/02)
```

| Milestone | State for dispatch | Required predecessor | Primary outcome |
| --- | --- | --- | --- |
| **M-RND-01** | **READY** | Accepted camera projection/arena/VCF registration + RND index | Native `00457FF0` work-record production from registered objects |
| **M-RND-02** | **READY** | Accepted original native-root camera and math startup | Persisted original `004C2730` camera/view data across controlled pose changes |
| **M-RND-03** | **CONDITIONAL** | M-RND-01 + M-RND-02 accepted or independently reproducible, sufficiently validated compatible inputs | Original-generated record consumed by original `0048FAC0` in one continuous emulator state |
| **M-RND-04** | **CONDITIONAL** | M-RND-03 producer/consumer positive path | Bounded original `00471FD0 → 0047C2F0/00487EA0` clip/draw execution with independent geometry/output checks |

**Dispatch policy:** Milestone ID is a stable *objective*, not a run ID or lock. Create one new owned `agent/runs/i76exe/<run-id>/` per investigation and one PR each. Concurrent workers use distinct local directories under `/media/neon-remote/prj/i76`; inspect existing state and never overwrite another agent's checkout or scratch. Independent RND-01/02 agents may start concurrently after the maintainer accepts this plan. M-RND-03/04 should wait for their prerequisites, not be sent automatically on a timer.

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
1. Build the native selected vehicle/attachment/registry and original projection with verified retail resources; preserve original math seed `00493C50`. Run original camera callback **directly, labeled as a controlled entry**, avoiding all live selected-post/init claims and the separate CAP-CONTROL-01 agent's code.
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

## Common validation and publication contract

For every worker:

- Start with [repository AGENTS](../../AGENTS.md), [bootstrap](../../agent/protocol/BOOTSTRAP.md), current `main` and [RND discovery](subsystems/RND.md); then read the exact linked merged run **manifest, findings, artifacts and source code**, not only an old conversation summary.
- Confirm accepted protocol/schema **at run start**; project planning does not lock future versions. Provenance must include original private PE, ZFS, GZF and any mission resource identities actually used.
- Separate **static original opcodes**, **original-instruction emulation**, **independent analytical checks**, **deliberately controlled fixture state** and **replaced OS/CRT/resource/math/render functions**. No fabricated record or output is positive proof. Log failures and negative branches.
- Produce complete **new-run reproduction** independent of undocumented local paths (old render runs did not always publish `REPRODUCE.md`), a meaningful standalone verifier and a byte-identical or scientifically explained repeat when possible. Check counters are *not* program completion percentage.
- Use separate scratch under `/media/neon-remote/prj/i76`; keep proprietary binaries/resources and private Ghidra databases local; do not publish private raw logs or large resource dumps.
- Publish **only one new immutable owned run per PR** with required `manifest.json`, `findings.json`, `validation.json`, artifact hashes, research report, `artifacts/DOCUMENTATION_IMPACT.md` and precise failure/limits. Do not modify other runs, canonical references, governance or agent branches, and **do not merge**.
- Review through normal protected `main` with required green trusted `integrity`, then human scientific/technical acceptance. Research acceptance is not automatic technical promotion.

## Suggested CLI first-turn prompts

Use a **new** Codex session for each distinct assigned milestone. The short prompt is sufficient only because full objectives and procedures are in this accepted repository file:

**Worker A (READY)**
```text
Bootstrap independently against current protected main at https://github.com/jf-stargate/i76, following AGENTS.md and agent/protocol/BOOTSTRAP.md.
Your assigned objective is M-RND-01 in manual/roadmap/RND_SUBSYSTEM_MILESTONES.md, using manual/roadmap/subsystems/RND.md.
Read linked accepted evidence, confirm private source identities, and implement the bounded original-00457FF0 visibility-producer experiment with genuine original registered objects and original render arena.
Do not synthesize a spatial record to claim original producer success. Include negative/control cases, explicit services, independent verification and full reproduction. Publish exactly one isolated immutable i76exe research run and PR; do not merge.
Use an isolated directory under /media/neon-remote/prj/i76. Do not touch the independently active CAP-CONTROL-01 agent.
```

**Worker B (READY)**
```text
Bootstrap independently against current protected main at https://github.com/jf-stargate/i76, following AGENTS.md and agent/protocol/BOOTSTRAP.md.
Your assigned objective is M-RND-02 in manual/roadmap/RND_SUBSYSTEM_MILESTONES.md, using manual/roadmap/subsystems/RND.md.
Read linked accepted camera/root evidence, verify source identities and extend controlled original-00406AB0 camera continuity across two distinct native-root poses and consecutive calls while preserving persistent 004C2730 and smoothing state.
Distinguish harness-controlled pose from native camera writes; do not investigate selected-player post/init owned by the active CAP-CONTROL-01 agent. Publish one isolated immutable i76exe research run, original-versus-substituted ledger, independent checks, negative/repeat controls, reproduction and reviewable PR; no merge.
Use a distinct isolated directory under /media/neon-remote/prj/i76.
```

Do **not** dispatch M-RND-03 or M-RND-04 merely because these IDs exist; gate them on prerequisite evidence and normal review. If active agent work later overlaps or supersedes a milestone, reconcile against `main` rather than launching a duplicate.
