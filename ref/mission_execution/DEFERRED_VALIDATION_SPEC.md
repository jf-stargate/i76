# Behavioral validation specifications — research-only, not executed

These are proposed observations of the *retail engine*, intended to help close static ambiguities or provide acceptance tests if the project later undertakes source reconstruction. They do not authorize or imply starting a replacement mission runtime.

| Test ID | Preconditions | Stimulus | Observables / expected result within audited path | Status |
|---|---|---|---|---|
| T-01 | Valid mission, two pending nodes | Both test same `isRammed` event; earlier consumes it | Earlier true and clears A6D8; later false unless new event injected | Predicted B, not executed |
| T-02 | Valid actor; recent `isAttacked` epoch | Invoke isAttacked then isShot/isRammed | First consumes A6DC and clears A6D4/A6D8; latter markers unavailable | Predicted B, not executed |
| T-03 | Cached attacker and consumed epoch | Call whoAttacked | Source identity lookup still possible; marker expiry alone does not erase pointer | Predicted B, not executed |
| T-04 | Two runnable VM nodes | First yields; second sets a shared variable | Second runs same scheduler pass; first is resumed only on next pass | Predicted B, not executed |
| T-05 | Node with long branch loop | Execute >800 and near 1000 tokens without yielding | Over-budget flag, no cooperative preemption; hard exit path at threshold | Predicted B, not executed |
| T-06 | AI transition path invokes weighted selection | Compare sequences with/without prior VM rand command | Shared CRT rand state changes AI outcomes where random branch entered | Conditional, not executed |
| T-07 | Route completed | Query isArrived twice without producer update | First true; second false | Predicted B, not executed |
| T-08 | Follow state has been computed true | Query isAtFollow twice without AI producer | First true and clears A988; second false | Predicted B, not executed |
| T-09 | Idle control queue | Enqueue one sample; query controlDone; driveControl; query again | Completion 1 -> 0 -> 1; one sample popped per eligible call | Predicted B, not executed |
| T-10 | Two queued control samples | Two consecutive driveControl commands in one VM turn | Both consumed in same turn; later physics sees last resulting control values subject to vehicle eligibility | Conditional, not executed |
| T-11 | Control ring near wrap | Enqueue/dequeue and hit full/empty boundary | Indices wrap 100; observe how error stub and sample collision behave | Open, not executed |
| T-12 | Objective hidden but valid | Reveal then success; separately fail first | Hidden bit clears; success/fail flags set under mutually exclusive checks | Predicted B, not executed |
| T-13 | 0-delay successAll | Schedule result with no nodes left | Next scheduler invocation checks deadline even with empty list, sets flow state | Predicted B, not executed |
| T-14 | Due deadline with multiple runnable nodes | Enter scheduler and let timeout fire | Game-flow state changes, remaining nodes still eligible this pass; top-level loop exits later | Predicted B, not executed |
| T-15 | Frame hitch during mission timer | Compare elapsed `005A7E14` to clamped simulation delta | Deadline clock may advance further than physics delta | Predicted B, not executed |
| T-16 | Duplicate instance keys | Register two distinct objects with same paired key | Both records append; reverse lookup finds newest pointer | Predicted B, not executed |
| T-17 | Serialized actor key absent | Load mission with unresolved key, then avoid dereferencing actor | Loader retains null actor binding, does not reject through audited path | Predicted B, not executed |
| T-18 | Distinct actor registration count near 2048 | Attempt growth in disposable retail process | Verify nonnull HeapReAlloc immediate return and null fall-through, document actual OS behavior | High-risk; defer |
| T-19 | CB queue with source object | Submit, play, complete audio | Separate message queue advances via `004238E0`, VM list unchanged | Predicted B, not executed |
| T-20 | Normal mission teardown with active CB messages | End mission | Audio/CB records cleared before active-world slots released | Predicted B, not executed |
| T-21 | Vehicle damage and source pointer | Destroy class 1, 8, or 9 in unsuppressed mission | Usually retains world node despite destruction status; inspect epoch and actor cache | Conditional, not executed |
| T-22 | Suppressed vs unsuppressed shell launch | Sample `(N,S,C,F)` at each frame | VM branch governed by N/C/F; attacker recording governed by S | Predicted B, not executed |
| T-23 | Paired miss8/miss16 mission | Parse independently and compare VM | Identical tokens and initial execution-node records; only noted actor metadata differences | **Corpus validated**, not gameplay |
| T-24 | Empty vs nonempty FSM mission | Parse and load both | Parser accepts empty nested FSM; nonempty has 95-name table | **Corpus validated**; runtime load still separate |

Suggested passive trace record: game frame index; `GetTickCount` and accumulated elapsed float; `N/S/C/F` mode globals; game-flow state; FSM head/count; current node address/IP; opcode and command-record index; AI state and epoch; object pointer/+0x08/+0x0C; ref acquire/release; CB head. Capture only in controlled, authorized local testing. **Do not run malformed-input stress tests against important files or production systems.**
