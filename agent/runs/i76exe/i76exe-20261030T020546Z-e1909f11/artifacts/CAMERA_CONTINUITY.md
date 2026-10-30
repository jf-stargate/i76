# M-RND-02 — original camera continuity under controlled native-root poses

Run `i76exe-20261030T020546Z-e1909f11`; original base `d2072e673492b8fa72b268028890e6ef51dc2537`; protocol 1.0.4, schema 1.2.0. **Bounded milestone outcome: complete in original-instruction emulation with substituted services.** This is research evidence proposed for review, not canonical promotion, a retail Windows frame, hardware x87 parity or selected-player scheduling.

## Result

Original `00406AB0` returns normally through its actual RET at `00406DFE` on repeated direct invocations with the **same emulator, constructed vehicle, registered world entry, persistent 472-byte `004C2730`, and smoothing globals**. Stock bus and GTSi both distinguish controlled translation and orientation. The bus sequence repeats byte-for-byte in a separately imported Ghidra project and fresh process. Independent Python checks validate 58 calls across eight experiments, including negative and history-reset controls.

The camera origin at `view+0x160` is stable when only call history changes. The basis, transformed frustum corners and derived bounds evolve through original smoothing. Translation moves the origin by the supplied translation; rotating the root rotates the original VLOC-derived camera offset. The six-double region `+0x160..+0x18F` consists of **camera origin plus first transformed frustum corner**; it is not six camera coordinates or a six-double matrix.

## Source and experimental ownership

Private retail PE SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`, original ZFS SHA-256 `0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d`, annotated v97 GZF SHA-256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`. All measured locally; no payloads published. See `manifest.json`, `evidence/provenance.json` and `REPRODUCE.md`.

The accepted original-node/VCF service scaffold is copied into the owned probe, with exact lineage digest in provenance. Original `0045EBD0` constructs the root at emulated `26000000`; controlled class-1 staging bindings follow construction. Original spawn-status instructions select the vehicle; original `004AD6F0` builds its VCF/VDF/VLOC hierarchy and loads original GEO/TMT resources through supplied resource boundaries. Actual live runtime comes from `root+0x70`, not the staging runtime. Original VLOC is `27000800`, class 0x28, with immediate parent `27000A00` in the constructed hierarchy. It is not asserted to be a direct root child.

Original `004572B0` creates active-world entry `00542830`, owner `26000000`, count 1, and increments the root reference. The harness supplies this returned entry to `004C2908`. Original `00493C50` executes before projection/callbacks, retaining the accepted math-startup correction. Original `00405970(0)` initializes the camera once from a controlled 640×480 viewport and copies 118 dwords. Each scenario starts a fresh emulator; within a sequence it is never reconstructed.

**Controlled inputs:** after construction/registration, the harness writes nine root basis float32 fields at `+0x18..+0x3B` and three root translation doubles at `+0x40..+0x57`. These are controlled poses of an original-created root, **not original physics-produced poses**. Velocity-like inputs at live runtime `+0xD4..+0xDC` are explicitly supplied as float32 `(2,0,1)` to exercise original smoothing. Frame delta `004FE420` is supplied as float32 0.016; original `0049C7A0` reads it. `0049C8B0` reads **unchanged retail-mapped `004FE428` = float32 0.06**, not a live clock update. Integer angle inputs `00536770/78/80` are each 1; mode global `004C2728` remains mapped zero. No selected post/init, original clock/scheduler, terrain, visibility producer or renderer is executed as a completion claim.

A/B/C are defined exactly:

| Pose | Root basis rows | Root translation doubles |
| --- | --- | --- |
| A | `(1,0,0); (0,1,0); (0,0,1)` | `(0,0,0)` |
| B | same identity | `(10,20,30)` |
| C | `(0,0,-1); (0,1,0); (1,0,0)` | `(10,20,30)` |

Primary persistent sequence: **A,A,B,B,C,C,A,A**. The callback's original instructions are forbidden by the probe from changing the controlled 64-byte root-pose region. Six original root-read sites at `0043802E/31/45/B2/BC/C6` are logged with actual ESI=`26000000`. Original `00437F90` supplies a matrix; original `00494E20`, `00458CB0` and a second composition produce the 64-byte source passed to `00472990`. Both its raw bytes and the final 118 dwords are published. The harness never writes camera output during persistent callbacks.

## Measured differences and controls

Selected bus origin after A: `(-0.40767502784729004, 2.022514820098877, 3.470278739929199)`. After B: `(9.59232497215271, 22.022514820098877, 33.4702787399292)`. After C: `(13.4702787399292, 22.022514820098877, 30.40767502784729)`. These are **emulated controlled measurements**, not retail gameplay coordinates. GTSi shows the same supplied translation and root rotation applied to its distinct original attachment offset.

| Bus experiment | Calls | Measured outcome |
| --- | ---: | --- |
| persistent A,A,B,B,C,C,A,A | 8 | Finite origin/corners, pose-dependent differences, retained smoothing history |
| independent fresh-project repeat | 8 | Entire private trace and filtered public events byte-identical |
| stationary A×8 | 8 | Origin fixed; smoothing/basis/corners evolve; time-matched B minus A origin exactly `(10,20,30)` |
| explicit reset before each A,A,B,B,C,C,A,A | 8 | Camera and both smoothing regions restored to initial bytes; equal-pose adjacent outputs identical |
| cold B,B | 2 | First B equals reset-B; differs from history-bearing persistent-B |
| zero basis, same sequence of translations | 8 | Node, registry and VLOC remain genuine; all six view doubles become NaN; no valid-view claim |
| controlled null live `runtime+0x398` | 8 | Original null-VLOC guard exits; zero changed camera/smoothing dwords; prior projection remains finite |
| GTSi persistent A,A,B,B,C,C,A,A | 8 | Finite pose-dependent updates and near-unit basis with its own stock attachment |

The reset is a **separate deliberate counterfactual**, not part of the persistent positive experiment. It restores the full 472 bytes plus `004C2964..004C297B` and `0052B93C..0052B947`. Fixed-pose return to A in the persistent sequence recovers the same origin but a different basis/corners from the first A. Thus “camera changed” alone would conflate pose response with history; the stationary and reset comparisons separate them.

For the first four identity-orientation bus calls, original `00437F90` smooths three floats via `s_next = s_previous + (2*dt)*(target-s_previous)`, under its source threshold/range guards. With supplied dt the factor is approximately 0.032. The verifier derives a fixed target from the initial cold step, then predicts the next three observations within 2e-9 absolute/relative tolerance. The inferred target is approximately `(0.008,-0.024,0.128)`; this is a bounded inference for these controlled inputs, not a general camera law. Original writer PCs are `004381AF`, `0043821A`, `00438269`. Separate angular history stores occur at `00406C4B`, `00406CB9`, `00406D10`; current angle inputs at `00406B3A/7C/88` also remain in memory across calls.

## Camera record map (retail offsets, bounded confidence)

| Offset from `004C2730` | Width and measured interpretation | Evidence / confidence |
| --- | --- | --- |
| `+0x00..+0x3B` | Projection/viewport scalars, includes zoom float at +0x34 | Original 00405970/00472400; high for sampled fields, no comprehensive struct naming |
| `+0x3C` | 32-bit supplied viewport-context pointer | Original read at 0047240F; high |
| `+0x40..+0x63` | Nine float32 inverse orientation coefficients | Original 00472990→00494F70→REP copy 00472C05; independent exact transpose check, high |
| `+0x64..+0x67` | Matrix padding/remaining copied word | Preserved in 16-dword matrix copy; semantic meaning unresolved |
| `+0x68,+0x70,+0x78` | Three double inverse translations | Independent `-Rᵀ t` check, original 00472D30 consumer; high |
| `+0x80,+0x88,+0x90` | Double center of world AABB over source origin plus four transformed frustum corners | Original 00472B6F/80/86; independent min/max midpoint check, high in valid cases |
| `+0x98` | Double maximum radius about that center | Original 00472BF0; independent five-point distance check, high |
| `+0xA0..+0xFF` | Frustum-plane region used by classifier 00472C10 | Binary-static reads, native projection writers observed; no classifier execution claim |
| `+0x100..+0x12F` | Additional projection/frustum intermediates | Captured; full semantics unresolved |
| `+0x130..+0x15F` | Four local corner triples, float32 | Original 00472990 indexes with stride 12; high |
| `+0x160..+0x177` | Three double source camera-origin coordinates | Exact source+0x28..+0x3F copy at 004729AD/B6/BF/CE/FD; high |
| `+0x178..+0x1D7` | Four transformed corner triples, float64 | Original 00472A40/62/85 loop; independently verified `local_corner × R + t`; high |

The full 118-dword record ends at `004C2907`. `004C2908` is the adjacent active-entry pointer, **outside** the record. Angular state `004C2964..297B` is also outside it. Older camera probes sampled only 432 bytes; this run captures all 472. One must retain both the record and out-of-record smoothing state for this continuity comparison.

The valid bus inverse-basis Gram upper triangle remains near `(1,0,0,1,0,1)`, with maximum absolute entry error below 0.0001. The verifier calculates this from float32 bytes; it does not normalize or repair emulator results. Exact orthonormality and hardware x87 equality are not inferred. For the sampled origin `(0,0,0)`, actual original `00472D30` outputs match float32-rounded inverse translations after each valid callback.

## Verification and limitations

`evidence/camera_events.tsv` is an exact allowlisted projection of private source traces, including full typed byte samples, original call/read events, and **changed-dword** chronology. Stores that leave bits unchanged are not write events; no claim is made that the trace records all memory accesses. Replaying the changed-dword events from each before-sample independently reconstructs every byte of the after-camera and both smoothing regions. Sparse opcodes are checked directly against the original PE, including every changed-state writer PC. `numerics.json` is independently derived from these bytes. No proprietary resource bytes or full original-code dumps are public.

Original instruction emulation uses Ghidra 12.1.4/OpenJDK 27-ea. The inherited construction path reports uninitialized x87 registers at `00438340` and a null optional-geometry key read at `004461E0`; these remain limitations, not silently repaired state. Sine/cosine and float-to-int are explicit substitutions; x87 integer conversion consumes ST0 through Ghidra's register-shift model. Optional geometry/material/light, Windows heap, resource and CRT services remain bounded substitutions in `SERVICES.md`. Corrected math startup and measured near-unit results improve numerical conditioning but cannot certify all constructor state or hardware parity.

No original selected-player post lifecycle, callback scheduling, real physics pose production, native world-to-queue visibility, pixels or complete CAP-CAMERA-01/CAP-SLICE-01 is claimed. The compatible handoff to a later M-RND-03 is a reproducible **controlled** original-updated camera record, with exact pose, services, history and invalid-state controls, not an authentic live player camera.

## Publication reconciliation

Main advanced during this investigation to `a474af7f893d240706e4bfa752e4dc0212e46ebd` via documentation PR #65. Its accepted protocol files are unchanged. The updated RND milestone still explicitly permits this controlled direct-callback experiment; the new RND-v1 acceptance contract separates camera continuity evidence from full subsystem closure. This run supports the controlled part of G-RND-02 and the camera portion of RND-R1. **It does not close RND-R1, SC-RND-01's authenticated M06 scene condition, or any RND-v1 research/integration/product gate.** No M06 mission fixture is loaded here. Tolerances in this research verifier test internal source-byte arithmetic identities and observed conditioning; they are not a ratified fidelity threshold for an implementation or final image. Original run base is retained under the isolated run-only policy.
