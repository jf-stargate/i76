# Retail object visibility producer to spatial renderer: native original-code research

## Scope and lineage

Original retail i76.exe x86 in Ghidra 12.1.4 annotated v97; continuation of merged vehicle resource run v2.4 and **unmerged** renderer research PRs #24, #26, #29. This run does not revise their evidence. No source reconstruction or replacement renderer was attempted. Exact PE, GZF and ZFS digests appear in the manifest.

## Proven new behavior

The original `00457FF0` visits entries at `00542830` with a per-entry stride `0x78` and active entry count `0054A25C`. We supplied **one controlled active-world-entry record** pointing to the native VCF-built class-66 GTSi/bus exterior body node; this is NOT an entry created through original `004572B0` registration. The original vehicle constructors, body pointers, basis, GEO resources and TMT attachment are unchanged from previous native harnesses. The test's camera context, frustum plane coefficients, entries, near/far depth bounds and render arenas are synthetic.

For each vehicle, original instructions in `00494BE0` and `00472D30` perform object coordinate transformation and view transformation. Original `00472C10` tests the transformed sphere against the frustum. For a controlled neutral frustum it returns `0xFFFFFFFF` (-1), accepting the body; for a controlled strongly negative far-plane offset it returns `1`, rejecting the body. The rejected case allocates/inserts zero records. **Neither outcome was substituted.**

The accepted case runs original `00490590` record preparation followed by original `0048FE10` spatial bucket insertion. It produces a type-6 work item (`record+0x0C=6`) with original body pointer at `record+0x1C`, controlled active entry pointer at `record+0x40`, priority/depth at `+0x10`, and record cursor advanced **68 bytes (`0x44`)**. The controlled near plane was selected to place the record in bucket **1** for repeatable queue-consumer execution; this bucket assignment is **test dependent**, not a universal geometry priority.

Without manually manufacturing or changing the work record, the original `0048FAC0` consumer drains that bucket, enters the original dispatcher `0048F4C0`, then enters **secondary** traversal `0045D530` precisely once per vehicle. The record's original `+0x38` render-mode field is zero, so it does **not** enter primary `0045D100`. No original `0045CBE0` section builder or `00471FD0` polygon submission is reached in this case. This is expected when the passed class-66 body node has no suitable child geometry for the secondary traversal's entry guard (`object+0x64`). Do not conflate successful dispatch with successful drawing.

## Evidence and caveats

- Four cases: two native accept/queue/consume and two native reject/no-queue cases; two separate read-only Ghidra replay traces are byte-identical.
- X87 operations in the original affine/frustum and bin functions execute under Ghidra emulation; numerical agreement with physical x87 hardware is not independently established. The synthetic frustum is an explicitly controlled test, not a retail camera state.
- `00477ED0` palette unlock, `00407930` camera mode and `00477AC0` headlight integration are substituted at their service boundaries. Native VCF setup still uses substituted Windows OS/heap/CRT, resource loading, VQM pixels and raster clipping/drawing.
- The preliminary test with near depth bound -1000 produced real records in spatial bins 1100 and 1101, but the consumer skipped them under the synthetic scan-limit setting. Repositioning the **near depth bound** without altering producer records permitted original consumer dispatch. The complete production frame's near/far range updates are unresolved.
- A separate exploratory class-1 root-entry experiment sometimes produces multiple work records, but it was not stable across vehicles under this synthetic camera and is **excluded** from validation and findings. Correct native active-entry registration, parent/child lifetime, camera/frustum initialization and class-1 work submission remain open.

## Architectural implications / next work

The original renderer preserves persistent world-object identity in a transient 68-byte work-queue envelope: one path leads from the active registry through x87 transform, frustum classification, record allocation, bucket insertion, bucket consumer, dispatcher and secondary object traversal. The object pointer is not copied into a new persistent mesh object. To reach native polygons without forcing render mode, invoke original `004572B0` to create an actual active-world entry for the root vehicle and recover retail camera setup plus depth-range management, then execute `00457FF0 → 0048FAC0 → 0045D530` on that hierarchy. Pixel decode and raster callbacks are still separate unknowns.

All original VAs use retail image base `00400000`. Source-file/TU boundaries near `00457xxx` and `0048Fxxx` remain hypotheses only.
