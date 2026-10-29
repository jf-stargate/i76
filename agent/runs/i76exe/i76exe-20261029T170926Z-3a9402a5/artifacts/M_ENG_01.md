# M-ENG-01 — original descriptor-mediated class-1 scheduling

## Result and boundary

**Yes, in a bounded original-instruction experiment.** Original pre dispatcher `00461C80` and post dispatcher `00461D50` each traverse the original registered class collection, resolve the constructed class-1 owner, read its original descriptor slots and invoke `00463800` / `00463950`. Both callbacks and both dispatchers return in all three tested frames for stock bus and GTSi. No harness callback entry occurs in those dispatcher cases. A separate bus process reproduces the entire private trace byte-for-byte.

This is **not complete WinMain execution**. The harness calls the two dispatcher entry points in controlled order after original clock update. It supplies private resources, OS/CRT/numerical services and two peripheral class post callbacks. The primary vehicles use the original **unselected** spawn status, so class-1 post's `0x10` predicate is false and its input/cockpit/audio side effects are skipped by original instructions. The result proves descriptor/collection scheduling and callback return in this tested state, not complete selected-vehicle post behavior or retail Windows gameplay.

Run `i76exe-20261029T170926Z-3a9402a5`; original base `9312486b92f15305d814c2bf0551f3cf1e233f48`; protocol 1.0.4; schema 1.2.0; advisory owner ENG with VEH/OBJ/TER interfaces. All changes belong to this run. No canonical reference, promotion, shared tool or accepted run is changed.

## Original setup and collection provenance

The parent is the accepted M06 probe in run `i76exe-20261028T174609Z-3f1f83f8`, not a local unpublished script. Its source SHA-256 is `ca1ad48b130ccf4a4227639104325362c7b90dab949cd03f333502260c8b55b7`. Accepted two-frame, startup and M06 evidence (PRs #49/#50/#51), the newer pose extension (#57), ENG/VEH/TER discovery indexes, milestone roadmap and existing vehicle construction promotion were read independently. `evidence/bootstrap.json` records protected-main identity, policy/enforcement, relevant merged PRs and branch discovery. No PR was open at bootstrap.

The licensed PE, annotated v97 GZF, ZFS and miss8 M06 inputs were measured against accepted identities. Fixtures were extracted anew and the GZF copied into a fresh private Ghidra project. Replays use Ghidra 12.1.4/OpenJDK 27-ea, `-readOnly -noanalysis`. Source databases and names remain untouched.

Original root construction `0045EBD0`, VCF construction `004AD6F0`, class binding `00461970`, terrain/math/engine-registry startup and world registration `004572B0` are retained from the parent. The inherited staging context and controlled initial fields remain explicit. The complete `00463120` cockpit/weapon initialization and pending-initialization dispatcher `00461B80` are **not** claimed executed.

Crucial change: the parent's whole-function list-insertion substitute at `0049C320` is removed. Original instructions allocate 12-byte nodes through the declared HeapAlloc service, write next/previous/value and fix neighbor links. Original `00461970` inserts into class collection head `0054B204` and pending head `0054B208`, updating counters. The class collection is distinct from the world/camera registry at `00542830` / count `0054A25C`. World registration alone would not prove class-dispatch membership.

Each primary case has **15 class-collection nodes**, including root `26000000`, class 1, runtime `36000000`. This is not the total number of visual/world objects. Every visited node/value/next is checked against the observed original insertion; every owner has an original class-registration event. Each original pre/post walk visits all 15 in linked-list order, ending at null. The original handle/object resolver `0045F0F0` runs; it is not stubbed. The pending list is left as established by construction, so this remains a controlled dispatcher slice rather than proof of the entire initialization lifecycle.

## Descriptor and call chronology

Sparse PE anchors are published in `evidence/instruction_anchors.tsv`; full original code/decompilation remains private.

| Phase | Original traversal and fetch | Class-1 invocation | Return |
|---|---|---|---|
| Pre | `00461C91` node+8; original lookup at `00461C9C`; descriptor scan stride `0x34`; load `00461D2C` | slot `004F7788` → `00463800`, indirect `00461D38` | callback → `00461D3A`, dispatcher → harness sentinel |
| Post | `00461D61` node+8; original lookup at `00461D6C`; load `00461DFC` | slot `004F778C` → `00463950`, indirect `00461E08` | callback → `00461E0A`, dispatcher → harness sentinel |

Class-1 descriptor is `004F777C`; init slot `004F7784` contains `00463120`. The post entry is **00463950**, not internal `004639A0`. Original descriptor bytes are never overwritten. The harness writes EIP only to begin declared calls or supply documented services; class-1 EIP is reached by the original indirect instruction in primary cases. `HARNESS_ENTRY` distinguishes these from the deliberately direct control.

`evidence/dispatch_events.tsv` retains sequence numbers from the private source traces: original list returns/registration, collection-ready state, every node visit and lookup result, slot/target, indirect call and return, class-1 entry, post predicate and sampled phase state. The independent verifier validates these against the PE, registered identities, source traces and separate controls. It does not infer scheduling from a final pose alone.

## State chronology and controls

Each frame runs original `0049C920` with substituted ticks increasing by 16 ms, then original pre and post dispatch. Math/clock/filter/terrain/engine-registry startup is retained. The initial basis and XYZ come from the authentic M06 spawn; throttle/mode/speed, camera relevance and unpaused gate are controlled as in the parent. All three original pre calls reach the original solver and authentic terrain reads. Contact coverage is not the purpose of this three-frame experiment.

| Frame | Root Y before pre | Root Y after pre and post |
|---|---:|---:|
| 0 | 31.5 | 31.49874496459961 |
| 1 | 31.49874496459961 | 31.49498176574707 |
| 2 | 31.49498176574707 | 31.488710403442383 |

Both vehicles produce these Y values in the tested state. X/Z remain 2952.5/48152.5. Bus first pre changes sampled Y velocity from `00000000` to `BE209043`, runtime flags `00000040` to `00000044`, and basis/timer fields. Original unselected status is `00020800`; post predicate `00458BF0` returns zero at `00463960`. The sampled root basis/position, velocity, timer, status and runtime flags remain unchanged across post. This is **not** a claim of zero writes to every byte of the object/runtime.

- **Empty collection:** original pre and post return before construction with zero callbacks.
- **Direct control:** the same constructed bus executes class-1 pre/post directly. Its nine phase snapshots equal the dispatcher bus snapshots exactly; it is labeled as a control, never scheduler evidence.
- **Separate repeat:** bus trace SHA-256 `85c218115e8b8e3ab2a989446e1eaf2433838d7e062ffb68fbb637e2123e6934` repeats in a separate process with a fresh emulator. Full raw traces remain private.
- **Fresh-project procedure:** the published driver imports a new copied GZF and runs each of five scenarios in a separate process. Final evidence comes from that reproduction, not old local traces.

## Selected-post diagnostic and exact blockers

Mode `-diagnostic`, selected=1, retains original peripheral callbacks and deliberately does not extend the inherited trig service to post dispatch. It records completed pre and class-1 post entry, but no post completion. Original **FSINCOS bytes `D9 FB` at `0049D409`** hit Ghidra's **`Unimplemented CALLOTHER pcodeop (fcos)`**. The source opcode is FSINCOS; the exception names its lower-level P-code operation.

Before that stop, raw peripheral post execution reads incomplete state: `0046F43D` reads `0000000C`, and `0045F978/0045F97B/0045F9A2/0045FAAD` read `00000070/00000108/0000006C/0000A9B4`. These are not valid positive peripheral results. Primary cases replace only class31 `0046F420` and class34 `0045FAF0` post consumers with logged services. Their normal descriptor selection/call remains observable; neither class-1 callback nor either dispatcher is replaced. Recovering their missing ownership/initialization and full selected cockpit/input/audio state is future work.

An exploratory selected run with extended trig returned but introduced unresolved input-service null reads; it is not positive evidence. Earlier accidental diagnostic trig suppression stopped in pre; that configuration was corrected to suppress only post's service before the final diagnostic was regenerated. An intermediate instrumentation compile error was also corrected before the final fresh-project replay. These exploratory artifacts remain private; the final modes and verifier specify the reproducible evidence boundary.

## Validation and milestone disposition

`scripts/verify_schedule.py` passes **3,807/3,807** checks, including five input identities, sparse opcodes and descriptor words; original insertion/membership/next order; all six 15-node walks per dispatcher case; target/callback/return chronology; no harness callback injection; empty/direct/repeat controls; typed finite pose and Gram products; every logged terrain read's address/word; three solver returns per case; and expected diagnostic failure. Assertion count describes this dataset, not general correctness coverage. `--emit` passes 3,804 checks and omits the three published-output comparisons.

Primary execution logs have only the inherited optional-geometry null-byte read at `004461E0`, plus unused x87 registers during math initialization. The verifier rejects new primary memory warnings or errors. Neither warning is reclassified as proof of fully initialized retail state. Private input requirements keep reproducibility conditional; hashes, owned scripts, exact procedure and derived records are public.

**M-ENG-01 bounded criterion is satisfied:** original descriptor/collection traversal invokes and returns from class-1 pre and post in the tested unselected state, without primary harness callback injection. **Partial/unresolved:** selected post side effects, other class post implementations, pending initialization, ordinary input/AI/FSM, clock lifecycle and full WinMain state-machine execution. No maintained reconstruction or canonical promotion is proposed. A documentation steward can reconcile the bounded ENG phase interface separately after human acceptance of this run.

## Publication gate

Scientific validation passes, but required trusted CI is blocked by a pre-existing base archive-test allowlist rejecting accepted schema 1.2.0. See `PUBLICATION_BLOCKER.md` and `evidence/publication_blocker.json`. Combined run validation is partial (3,844/3,845); research is proposed as a draft, not accepted or CI-green.
