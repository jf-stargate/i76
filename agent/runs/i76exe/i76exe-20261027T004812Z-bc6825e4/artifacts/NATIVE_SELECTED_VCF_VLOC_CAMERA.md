# Original selected-vehicle VCF/VLOC and camera guard — integrated retail-x86 evidence

**Track:** `i76exe`; **baseline:** original retail i76.exe MD5 `a640ea0097dbb62e0c77b7f2847c7161`, annotated Ghidra v97 `i76_mission_v97_verified_names` imported read-only into Ghidra 12.1.4. The exact SHA-256 identities are in `manifest.json`.

## Question

Previous accepted work separated the original spawn-time `object+0x10` flag setter (PR #40), the original VLOC 0x28 record parser (PR #38), original VCF construction (merged native v2.4), and the default camera guard (PR #37). Does the same emulated world-object state propagate an original status assignment through an original retail VCF/VDF/VLOC parse, **using the original class binder** and then reach the camera guard?

## Execution design and precise original/service boundaries

The test begins with an isolated class-1 world object, working original VCF loader state and byte-verified stock ZFS fixtures. It runs original x86 instructions of the `004513C0` object-creation policy from `00451452` through the actual VCF-call instruction boundary at `0045148B`; the basename/formatting routine `004AD640` is intercepted. The test **stops at the call instruction**, then invokes original `004AD6F0` in the **same emulator memory state** with the known v2.4 resource/context arguments. Thus it proves *state continuity*, **not** unbroken instruction execution of the caller's `CALL` into the callee.

Inside original `004AD6F0`, the original chained resource dispatch reaches VDF VLOC record type `0x28`, runs original `00458BF0` status predicate, original `004B47C0` child constructor wrapper, **original `0045EBD0` node allocation logic and original `00461970` class/runtime registration**, and writes the original runtime field `runtime+0x398`. Ghidra's Windows heap, CRT/string, resource-open, optional lighting/palette and other nonessential services still use explicit existing harness substitutes. The original class binder **is not intercepted** in these tests, unlike the isolated PR #38 experiment. The source includes inherited annotations of every stub in the step loop.

After the native VCF returns, the harness constructs a minimal active-entry pointer from the real constructed class-1 root and calls original camera-mode callback `00406AB0` explicitly. The callback's runtime lookup and null guard run original x86 instructions. The test ends immediately at `00406B13` (non-null) or `00406DF4` (null). This does **not** run the original per-frame camera-mode dispatcher, generate a physically accurate view transform or draw pixels.

## Executed cases

| Vehicle / selection argument | Original creation status before VCF | Status after VCF | VLOC class-40 attachment | Nodes | Original camera callback |
|---|---|---|---|---:|---|
| GTSi, selection 0 | `00020000` | `00020800` | NULL | 46 | null exit `00406DF4` |
| GTSi, selection 1 | `00010010` | `00010810` | `27000800` | 47 | past guard `00406B13` |
| Bus, selection 0 | `00020000` | `00020800` | NULL | 44 | null exit `00406DF4` |
| Bus, selection 1 | `00010010` | `00010810` | `27000800` | 45 | past guard `00406B13` |

The object address and child pointer are *deterministic emulator addresses*, not observed retail Windows process addresses. Both selected vehicles obtain one extra node relative to the unselected VCF baseline. The child class is `0x28` (`40` decimal). The source's 9 original VLOC orientation dwords are independently compared with the original VLOC child record in each selected case, and match **bit-for-bit**. GEO/TMT construction remains live: GTSi `912` geometry cache bindings and `24` successful TMT bindings; bus `856` and `22` respectively. Existing v2.4 exterior/cockpit checks were independently re-exercised during the initial flagged test; the published focused probe omits the subsequent, unrelated mesh-toggle phase.

The low-order status bit is unchanged by the loader; another `0x800` status bit is present at completion. Do not assign a semantic name to that additional bit without tracing its producer. Original `object+0x68` is recorded as a raw link in the trace; after additional children are created it no longer equals the earlier link captured at class registration. Therefore, do **not** interpret it as a stable immutable parent reference based solely on the initial trace label.

## Provenance and reproducibility

- The original resource inputs were extracted from byte-verified retail `I76.ZFS` with the **previously accepted** `extract_private_fixtures.py` script in the v2.4.0 run. Exact VLOC records from `valeprec.vdf` (GTSi) and `vxbus.vdf` (bus) are not published.
- The `148/148` assertion independent verifier compares retail PE/ZFS/Ghidra identities, 28 sparse original PE opcode anchors, retail VLOC `0x28` presence, original spawn/status records, actual GEO/TMT counts, original class-binder observations and exact camera branch outcomes. Every byte of the publication's derived result table is compared against the verified private traces.
- Selected-bus replay #1 and #2 were separate read-only Ghidra executions and are **byte-identical**, SHA256 `541ae35d27ff8124d2e17f602f5940c668a8109e3170683825dc39d58ee94def`.
- GTSi and bus unselected cases completed in an earlier multi-case headless process. That process was subsequently stopped during a third case. The retained private traces include each unselected case's full native loader return and camera null-exit, not a complete all-cases process replay. Separate complete selected GTSi and bus executions were performed afterward. This limitation is important for reproduction claims.
- Neither the full private traces nor original VDF/GEO/TMT/VCF resource payloads or Ghidra database are committed.

## Next original-binary questions

1. Execute actual caller `004513C0` through its `CALL 004AD6F0` after completing its preconditions, instead of splitting the caller and callee with a harness invocation.
2. Trace the complete mode-0x0E camera callback **after** its now-unblocked attachment guard, including original quaternion/x87 math and camera-state initialization.
3. Validate class-0x28 attachment refcounts, sibling/ownership links and unregister/re-register effects under original `004572B0` / `00457420`.
4. Propagate a qualified, numerically validated camera through native visibility and render-queue traversal and later clipping/raster services.
