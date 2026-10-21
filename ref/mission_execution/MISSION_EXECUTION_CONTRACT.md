# Retail mission execution architecture: observed contract

**Specification:** I76-MISSION-0.4.0 (descriptor-state supplement; loader v0.3.0 and host ABI v0.2.0 retained)  
**Binary:** `i76.exe` / MD5 `a640ea0097dbb62e0c77b7f2847c7161`  
**Baseline:** Ghidra 12.1.4 annotated program through v97.  
**Scope:** BWD2 resource dispatch, FSM import/fixups, VM execution, host-command dispatch, AI and object ownership, objective timing and teardown. Research and behavioral-test design only.

**v0.4.0 descriptor-state precedence:** Read `DESCRIPTOR_STATE_AND_REPEATED_LOAD_CONTRACT.md` for parser `seen`-bit persistence and cross-resource reuse; no malformed retail mission was executed.

**v0.3.0 loader precedence:** Read `LOADER_VALIDATION_AND_FAILURE_CONTRACT.md` for current validation, callback and failure-propagation semantics; this **supersedes the broader qualification in §2 below**. The v0.2.0 invocation ABI is unchanged.

**v0.2.0 host ABI precedence:** The detailed argument layout and dispatcher effects in `HOST_COMMAND_ABI_CONTRACT.md` and `ABI_DISPATCH_CONTRACT_96.tsv` supersede the provisional host-command descriptions in `tables/ABI_RUNTIME_COMMANDS.tsv` and v89. The rest of this document carries forward the v0.1.0 architecture. No executable or replacement runtime changes were made.

## 1. Executive architecture

The retail mission system is **not one monolithic FSM**. It includes a resource container parser, compiled script importer, per-mission object identity map, cooperative bytecode VM, synchronous host-call bridge, independent AI behavior state machine, world-object ownership subsystem, objective state array, and asynchronously serviced audio/CB queue. The launch mode gates which path is active. FSM scripts reference live world objects through loader-resolved actor records; later queries can append dynamically discovered actor identities.

The established *normal* data/control dependency is:

```text
BWD2 mission bytes
  -> BWD2 tagged descriptor parser (004B3DB0)
       -> ODEF world objects (004B7AC0)
           -> world-object registration (004572B0)
           -> paired-key instance registry append (00457610 -> 004AD450)
       -> ADEF nested descriptor parser (004B45F0 -> 004B89B0)
           -> FSM chunk handler (00409740)
               -> seven-table serializer reader (00410720 plus helpers)
               -> command name -> opcode fixup (004125C0 -> 00410A10)
               -> actor paired-key lookup and incref (00412400 -> 004AD5B0)
               -> media checks (004122D0)
               -> initial node/token pointer relocation (00412500)
  -> active gameplay frame (00402B30)
       -> world class update callbacks (00461C80, 00461D50)
       -> gated FSM/AI runtime frame (0040A320)
           -> pending-node scheduler (004149F0)
                -> VM interpreter (00414670)
                     -> host dispatcher (00412CE0)
                          -> synchronous AI (00412830) / gameplay commands
           -> damage event epoch increment (004155F0)
       -> weapon and dynamic-object updates
  -> scheduled game-flow transition (00402620)
  -> post-loop audio/CB cleanup, world and instance-registry teardown, FSM shutdown
```

**Ordering caveat:** Diagram outlines established dependencies rather than an exhaustive instruction-by-instruction frame trace. The engine may have additional callbacks, rendering, physics and media activity in these phases. Cross-system operations may execute synchronously inside the host dispatcher. See §§6–9.

**Evidence:** v95 `004B42B0`, `004B3DB0`, `004B45F0`, `004B89B0`, `00409740`; v96 `00412400`; v93 `004149F0`, `00414670`; v88 main-loop disassembly; v90/v97 shutdown.

## 2. Resource and parser contract

### 2.1 Outer container, nested ADEF

The generic parser `004B3DB0` matches tagged records against a **16-byte descriptor**:

| Byte offset | Representation / operation |
|---|---|
| `+0x00` | Four-byte ASCII section tag |
| `+0x04` | Auxiliary descriptor word |
| `+0x08` | Handler function pointer (not at +0 of record) |
| `+0x0C` | Flags controlling matching / required / seen / callback policies |

Selected **binary-confirmed** descriptors: outer `BWD2` at `00500328`, `REV` at `00500338`, `ADEF` at `00500398` with handler `004B45F0` at `005003A0`, `EXIT` at `005003A8`; nested `AREV` at `00500D20`, `FSM` at `00500D30` (handler `00409740` stored at `00500D38`), `EXIT` at `00500D40`. This corrects an earlier v81 inventory that treated a callback-address offset as the start of a descriptor. No original source field names are claimed.

The outer BWD2 loader `004B42B0` establishes a parse cursor and end pointer and invokes the generic parser. Nested `ADEF` is handled by `004B45F0 -> 004B89B0` with the `AREV`/`FSM`/`EXIT` descriptor group. `00409740` receives a chunk **header**, with payload at `chunk+8` and nominal payload byte count `chunk_size-8`.

**C / high (shipped corpus):** All 80 examined files have outer tags `BWD2`, `REV`, `WDEF`, `TDEF`, `RDEF`, `ODEF`, `LDEF`, `ADEF`, `EXIT` in that order, root revision 2 and nested ADEF revision 1. Each nested ADEF contains `AREV`, `FSM`, `EXIT`, including legitimate empty `FSM` chunks. Exactly 25 of 40 missions per `miss8` and `miss16` variant have nonempty FSM payloads. This is **not** a universal constraint on all inputs the retail parser could accept.

**Validation qualification:** The outer BWD2 parser checks aspects of declared boundaries, tag matching and descriptor policy, but a complete accept/reject state machine for malformed resources has **not** been established. The inner counted FSM importer does not visibly enforce its byte-count parameter on each dword read in its own audited routine; absence of that local check does not prove malformed external inputs reach it.

### 2.2 FSM wire format

The FSM chunk contains seven counted table groups, imported into runtime arrays. Their established semantic groups are: command prototypes, actor records, media records, named-position records, initial VM nodes, initial word/global-variable storage and VM token stream. This is the consumer's **seven-group import contract**; exact raw offsets and count encoding are to be taken from the companion v94/v95 byte-level inventories rather than guessed here.

| Group | Confirmed record / runtime representation | Fixup |
|---|---|---|
| Command prototypes | Serialized names (up to 40 bytes); runtime `0x54`-byte records | Map name to opcode and write `record+0x50` |
| Actors | Runtime `0x60`-byte records; 40-byte label, two 32-bit keys at `+0x50/+0x54`, object pointer `+0x58` | Lookup registry by paired keys, acquire counted reference |
| Media | Runtime `0x54`-byte records; filename and status at `+0x50` | Check `.wav` in resource cache/search paths or `.smk` cutscene location |
| Named positions | Runtime `0x58`-byte record: name, vector count at `+0x50`, vector-array pointer at `+0x54` | Load float triplets into separate arrays; **no actor-key binding** |
| Initial VM nodes | 168-byte source initializer (see §5) | Allocate `0x10BC` nodes and relocate frame/IP pointers |
| Initial word data | Shared 32-bit VM variable words | Address targets for node initial context |
| Token stream | `{u32 kind, u32 payload}` records, eight bytes each | Referenced from relocated node instruction pointers |

**C / high:** In each stock resource variant, nonempty FSM scripts total 797 initial VM nodes, 90,923 tokens, 397 actor records, 3,369 media records and 551 named-position records. All 25 nonempty scripts per variant parse exactly. `miss8` and `miss16` have identical tokens and initial node records in all 40 paired missions. Two FSM byte payloads differ only in actor metadata. None of the stock token streams uses `0x02`, `0x03` or `0x0B`.

### 2.3 Command namespace separation

There are two **different** indexes:

1. Serialized **command-record index**: the payload of VM token `0x0D`, used to select a record with stride `0x54`.
2. Engine **runtime opcode**: the numeric field at selected record `+0x50`, obtained at load-time by `00410A10` from the serialized name and dispatched by `00412CE0`.

For example, serialized index 5 is `follow` and resolves to runtime opcode `0x30`; serialized index 8 is `driveControl` and resolves to runtime opcode `0x49`. The full machine-readable mappings are in `tables/ABI_STOCK_COMMAND_TABLE.tsv` and `tables/ABI_RUNTIME_COMMANDS.tsv`.

The executable recognizes 96 command names/opcodes `0x00–0x5F`, including `playScene` (`0x16`). The stock compiled command table has 95 names; `playScene` is absent. The runtime host dispatcher has no normal explicit case for `0x16`, which falls to its `report_error` plus `abort` path. `set` (`0x07`) and `setId` (`0x2F`) use the same handler destination. The presence of a recognized name does **not** establish its support in any original compiler grammar.

## 3. World-object registry and actor identity

### 3.1 Instance-key registry

The global registry context `0054A178`, initialized at `004AD410` through `00457100`, is 16 bytes: a private Win32 heap handle, pointer to an allocated record buffer, record count and capacity. Initially it reserves `0x800` (2,048) 16-byte entries (32 KiB), count zero. Each entry has `key0` at `+0`, `key1` at `+4`, a **non-owning** world-object pointer at `+8`, and an unresolved final word.

`00457610 -> 004AD450` appends an instance key during world-object registration. `00457630 -> 004AD5B0` searches **backward** for the two-key pair and returns the last registered object pointer or zero. Duplicate insertion calls the engine's error routine but still appends. In this specific retail PE, `0042D5D0 report_error` is a **single-byte `RET`**, i.e., its invocation has no reporting/termination effect. This has consequences wherever code assumes diagnostic calls abort execution, but should not be overgeneralized to uninspected builds.

**Defect candidate (B / high control flow, U reachability):** The capacity-growth branch in `004AD450` appears inverted: successful `HeapReAlloc` results cause immediate return without storing the new buffer; null results clear the old pointer and continue toward writing. It is a machine-instruction-supported defect in the growth path, **not** a demonstrated stock gameplay fault or proof any mission reaches 2,048 cumulative registrations.

At `004571A0` the entire registry heap is destroyed; individual unregister (`00457420`) does **not** remove matching entries from this index in the audited code. Accordingly, rows can become stale, but the normal FSM actor-key fixup happens after ODEF load and before ordinary mission execution. Dynamic lookup of a formerly unregistered key remains an open hazard analysis rather than a demonstrated invalid dereference.

### 3.2 Actor binding

`00412400` reads actor `+0x50/+0x54`, looks up the registry, writes the returned pointer to actor `+0x58`, and calls `0045ED00` to acquire a **counted world-object-tree reference** if nonzero. Its 40-byte script label is distinct from the paired key. In 80 shipped mission files, all 794 actor-key occurrences also appear as contiguous eight-byte values in that mission's ODEF section. This supports the expected producer/consumer format but is not proof all named objects instantiate successfully at runtime.

Missing instance lookup writes null, calls the one-byte no-op `report_error`, and continues. `004125C0` continues media/node finalization and the `00409740` callback returns success in this examined path. It follows that **successful parsing does not guarantee all actor bindings are non-null**. The behavior of a later VM command receiving a null actor is command-dependent.

Duplicates are nuanced: the instance registry appends duplicate paired keys with *last registration wins*; the FSM binder separately compares duplicate paired keys/labels and may report inconsistent labels. The shipped corpus includes repeated `user` actor bindings with the same label/key, and these may each own a counted reference. The special label `taurus` causes its resolved pointer to be copied into global `0051F5C4`, a cached object pointer for post-mission/effect contexts; independent ownership is not established for that global.

### 3.3 Dynamic actor records

At least five audited helpers (`0040AFF0`, `0040B0F0`, `0040B1F0`, `0040A8A0`, `0040BA60`) can create a `NoLabel_<index>` record and acquire a counted object hold on successful discovery. Existing matching actor pointers are reused rather than retained anew. The loader reserves `serialized_actor_count + 200` actor slots of `0x60` bytes. Unregistration clears bindings but **does not reduce the actor-record count**. None of the five append routines contains a local capacity guard in the inspected body. There is also a no-target branch in `0040A8A0` that stores a null binding at the next slot without incrementing the count. No overflow is claimed without path-level/corpus reachability testing.

## 4. World-object ownership and lifetime

The world-object node has at least these established fields: `+0x08` logical removal state, `+0x0C` tree-propagated reference count, `+0x60` sibling link, `+0x64` child link, `+0x68` parent-or-previous-sibling backlink, `+0x6C` class and `+0x70` class runtime. The world-object allocation size is `0xB0`; this is a node with intrusive links and **not** a conventional independent shared_ptr-style per-node ownership count.

`0045ED00` recursively adds references to an object tree and its descendants. `0045EF70` releases counted references and may retire/unlink/free nodes when eligible. `0045F0F0` is a **liveness/conditional-release operation**: if object `+0x08` is live it returns the pointer unchanged; if logically removed it consumes the retained reference and returns zero, potentially freeing the node. This is not an unconditional decrement on live objects, despite an inherited function name suggesting that interpretation.

| Holder | Object retention | Release/cleanup | Important distinction |
|---|---|---|---|
| Active-world entry (`0x78` stride) | Counted, via `004572B0` | Unregister callbacks then counted release (`00457420`) | Entry is distinct from object pointer; team buckets point to entries |
| FSM team buckets (8×64) | Borrowed entry pointers | Compacted on unregister (`00409980`) | No extra object incref |
| FSM actor `+0x58` | Counted when nonzero | Unregister callback clears and drops | Dynamic queries share actor reserve |
| AI primary target `AI+A9B4` | Counted | Retarget/null/removal handling (`00412830`, `00409980`) | Direct lifetime management |
| AI damage-source caches `AI+A6E4/E8/EC` | Borrowed identities | Constructor zero; no explicit unregister clearing found | `who*` can later promote to counted actor binding |
| Instance-key index | Borrowed object pointer | Whole-registry teardown; no per-row deletion found | Reverse-key lookup can return stale identity if used late |
| Ordnance `runtime+0x0C` source | Counted in audited ordnance creator | On ordnance retirement | Does not extend to later AI cache lifetime |
| Explosion `runtime+0x0C` source | Borrowed at creation | No paired hold for that field | Auxiliary `+0x10` may retain a different object |
| Class callback queue | Counted while enrolled | Queue retirement | Separate from FSM node scheduler |
| CB message source `record+0x10` | Borrowed | Queue/audio teardown | Completion callback can later inspect object flags |
| FSM VM nodes | Allocated from separate FSM heap | Node completion and bulk heap shutdown | Not themselves world-object owners |

**Ordering guarantee within audited unregister path:** unregister callbacks are invoked before the active-world slot's counted object reference is retired. `00409980` clears FSM actor bindings/AI primary targets and compacts team buckets while the active slot remains available.

**Conditional hazard status:** A damage event can store a borrowed attacker pointer; consuming its epoch does not null the identity field; a later `who*` query can use that pointer without an independent recency/liveness test. Nevertheless ordinary unsuppressed single-player vehicle/class-8/class-9 destruction is largely status/effect driven rather than immediate unregister/free, while modes with more aggressive vehicle replacement also suppress new attacker records. We have **not** shown a retail mission dereferencing a freed cached attacker. The design concern remains conditional (v83–v88).

## 5. VM node and bytecode ABI

### 5.1 Execution-node allocation and fields

Each runnable node is **`0x10BC` bytes**; `00410490` allocates and links it; `00412500` performs initial relocation:

| Node offset | Bytes | Purpose |
|---|---:|---|
| `+0000 .. +0FFF` | `0x1000` | 1,024-word call-frame / operand workspace |
| `+1000 .. +109F` | `0xA0` | 40-word host-command argument storage, **separate** from operand workspace |
| `+10A0` | 4 | Current condition/result |
| `+10A4` | 4 | Token-array base |
| `+10A8` | 4 | Current instruction pointer |
| `+10AC` | 4 | Frame link/base |
| `+10B0` | 4 | Operand cursor |
| `+10B4` | 4 | Host-argument cursor |
| `+10B8` | 4 | Next VM node pointer |

The **168-byte serialized initializer** is `{u32 initial_token_index, u32 context_word_count, u32 context_words[40]}`. The first `N` local context words are relocated to addresses in the initial VM/global-word array. The relocation routine then installs an outermost zero frame link and a saved return IP inside the 4 KiB workspace. This initial frame shares capacity with operands and later nested calls.

### 5.2 Token ISA

Each instruction is `{u32 kind, u32 payload}`, eight bytes. There are fourteen recognized kinds, `1–14`:

| Kind | Behavior / cursor contract |
|---|---|
| `0x01` | Push 32-bit immediate payload; operand cursor +4; IP +8 |
| `0x02` | Push address `frame + payload*4`; operand cursor +4; IP +8 |
| `0x03` | Push value at `frame + payload*4`; operand cursor +4; IP +8 |
| `0x04` | Append frame-relative word **address** to host-argument area; argument cursor +4; IP +8 |
| `0x05` | Append frame-relative word **value** to host-argument area; argument cursor +4; IP +8 |
| `0x06` | Increase operand cursor by `payload*4`; IP +8 |
| `0x07` | Decrease operand cursor by `payload*4`; IP +8 |
| `0x08` | Absolute jump to `token_base + payload*8` |
| `0x09` | Jump to that index when current Boolean result is zero; otherwise IP +8 |
| `0x0A` | Set resume IP to that index; **yield** and return 0 to scheduler |
| `0x0B` | Subroutine call: save prior frame and return IP in workspace and jump to indexed token |
| `0x0C` | Return from frame; discard `payload` words and linkage; return 1 to scheduler only on outermost unwind |
| `0x0D` | Host call: dispatch `command_records[payload]`; host invocation synchronous; then IP +8 |
| `0x0E` | Negate current Boolean result; IP +8 |

**Qualification:** Shipped scripts never use `0x02`, `0x03`, `0x0B`, so frame-relative reads and nested calls are **binary verified but not stock-corpus exercised**. `0x0C payload` is a frame-pop word count, not a branch index; `0x0A` resumes at the explicit payload index, not `IP+8` by default.

### 5.3 Interpreter limits

The VM dispatch rejects unknown token kinds via an error-call path. Its per-invocation instruction counter warns/sets a global flag after the lower ~800-instruction threshold and calls `exit(0)` after the hard ~1,000 threshold; it **does not yield** at the warning threshold. Counts reset each time the scheduler calls the interpreter.

The audited VM/host path lacks explicit local bounds checks on branch target token index, host source-command index, operand cursor, host argument cursor, frame depth and several counted-loader word reads. This is an **audit-scoped absence**; it is not proof an arbitrary corrupt `.MSN` would bypass BWD2 validation or cause any particular crash.

## 6. Cooperative scheduler and reentrancy

The normal FSM frame function `0040A320` uses its outer `DAT_0051F640` gate, then executes the mission scheduler only when `g_is_network_mode` is zero and `DAT_0051F5C0` is zero. Otherwise it calls alternate AI-targeting logic. After this branch it increments damage epoch `00524550` via `004155F0`. Per-frame world-object pre- and post-update callbacks are earlier than this FSM frame in the audited top-level loop; weapon/dynamic updates follow. The damage epoch thus changes **after** mission VM processing in the ordinary path.

`004149F0` visits the **singly linked node list in order**. A node runs until it yields or completes. A completed node is unlinked and `HeapFree`'d, decreasing pending count. A yielded node is kept. The scheduler proceeds to successors **during the same frame**. Each node is visited at most once in an ordinary scheduler pass; there is no round-robin instruction preemption. No direct host dispatcher path was found that appends execution nodes during a pass; initial node creation occurs at mission loading. Indirect/alias modifications remain unexcluded.

VM token `0x0D` invokes `00412CE0` within the current interpreter call, and some commands enter the AI behavior evaluator `00412830` **synchronously**. This is ordinary nested C call activity; it is **not proof of recursive VM entry**. AI table transitions, target retention/release, predicate evaluation and potential weapon requests happen before that host call returns. Shared global `rand()` also couples script random draws and AI weighted selection.

**Ordering-sensitive events:** An earlier VM node may consume a damage marker before a later one evaluates it; the `isAttacked` predicate clears all three damage epoch markers at once. `isArrived` and `isAtFollow` are separately consuming AI events. The list order, rather than simultaneous independent script evaluation, is the observable contract.

## 7. AI behavior bridge and event semantics

The AI behavior table begins at `004C3E50`, has **34 records indexed 0–33** with stride `0x1354`. Each row contains update and optional entry callbacks, selection preconditions, conditional transitions and exit triggers. Exhaustive v79 static enumeration found 30 selection predicates, 101 in-range transition edges and 51 exit-trigger slots (including a null placeholder). Earlier v78 coverage of 12 rows was partial.

The AI evaluator `00412830` and weighted selector `00412680` use **three different predicate decisions**:

- Weighted candidate eligibility: all selected preconditions must succeed, otherwise try another weighted candidate.
- Current-state exit triggers: first nonzero trigger, inspected in table order, causes exit/reselection.
- Nested state transitions: first nonzero transition predicate selects a target state; observed stack depth is tracked at `AI+A93C`, with bounded push when `<0x31`.

Vehicle damage records (writer `004157A0`) store source identities at `AI+A6E4` (normal/ram), `AI+A6E8` (special/shot) and `AI+A6EC` (any attacker); corresponding epochs at `A6D8`, `A6D4`, `A6DC`. The FSM predicates `0040B800`, `0040B410`, `0040B990` match **current or immediately prior epoch** and clear their matched markers to sentinel `-10` on success (`isAttacked` clears all three). In contrast, AI `clsnDmg` predicate `0041C2C0` checks `AI+A6D8 == current_epoch` and does **not** consume it. `who*` commands read cached source identities without requiring an unconsumed or current epoch; on unknown source they may append an actor and retain it.

**Caution:** Predicate behavior follows the inspected code; which ordered interleavings occur in a particular mission has not been demonstrated by a live trace. The imported AI behavior table is not identical to the mission VM token stream.

## 8. Mission-visible movement, audio and objectives

### 8.1 Vehicle movement

- `isArrived` (`0x28`): path-following routine `00415020` sets `AI+0x9C`; `0040B320` consumes a true value by clearing it.
- `isAtFollow` (`0x46`): AI follow/proximity routine `0041EF40` computes and writes `AI+A988`; `0040BDF0` consumes a nonzero value.
- `control` (`0x47`) and `controlAll` (`0x48`): enqueue six-field samples of `0x18` bytes into a ring of **100 slots** starting `AI+9D68` (`0041F9C0`), clear drained flag `AI+A6D0`.
- `driveControl` (`0x49`): *explicitly* consumes a queued sample via `0041FC40 -> 0041F8E0`, normally applies the resulting fields to vehicle control state. The ordinary drivetrain update does **not** directly pop this queue in the audited callgraph; command order controls application cadence.
- `controlDone` (`0x4A`): reads drained flag `AI+A6D0` via `0041FCE0`; **non-consuming**. Empty-ring and ineligible-vehicle behaviors have distinct branches, not yet live-tested.
- `teleport` and `teleportOffset`: `00414BC0` updates transform and selected vehicle motion fields; it does **not** itself set path-arrival `AI+0x9C`.

**Capacity caveat:** 100 physical slots do not imply 100 usable queued samples without ambiguity: the ring uses producer/consumer indices and treats index equality specially.

### 8.2 CB-radio voice queue

The `cb`, `cbPrior`, `cbFromPrior`, `cbFrom`, `stopCB`, `killCB` and `isCBEmpty` commands interact with an **audio/voice-message queue**, not the FSM VM-node list. At `00423620`, the audio subsystem allocates `0x24`-byte message records with text identifier and optional **borrowed** source world-object pointer. Its playback-completion callback at `004238E0` retires completed records and advances the queue. `stopCB` sends special `STOPCBXX` marker/latch; `killCB` clears queued messages; `isCBEmpty` tests the queue head.

CB message timing uses Windows `GetTickCount`, not the mission deadline clock. Audio shutdown clears this queue before the normal active-world registry teardown, but a message source is not independently counted and exceptional mid-game object removal remains a limited lifetime question. The name `callback` here must **not** be conflated with FSM node callbacks or the class callback queue.

### 8.3 Objective flags and global outcome

Per-objective entries are indexed by **1-based** host command ID converted to zero-based internal index. Established flag bits at `00609420 + 4*index`:

- `0x01` hidden: `reveal` clears.
- `0x02` succeeded: `success` sets under audited consistency checks.
- `0x04` failed: `fail` sets under audited consistency checks.

This objective array is independent of global mission completion. `successAll` (`0x0F`), `failAll` (`0x11`) and `failAllObj` (`0x12`) write a target game-flow value (`1` success or `0` failure) and deadline `g_fsm_game_flow_timeout_seconds` (`005244E0`). `failAllObj` additionally sets an objective context. The scheduler checks deadline **before testing whether it has any active VM nodes**; on expiry it calls `set_game_flow_state` at `00402620`. The top-level game loop runs while `g_game_flow_state == 5`, and branches into post-game logic after the state changes.

A deadline armed by a host command is not rechecked after each individual VM instruction in that same scheduler invocation. Even when a deadline is already due at scheduler entry, subsequent pending VM nodes may still execute in that same pass. Result `0x0B` is a separate postgame code and must not be silently equated with a simple failure.

The mission deadline clock at `005A7E14` is accumulated from elapsed Windows `GetTickCount` in `0049C920` **before** the simulation delta is clamped; pause-like display/input modes also affect its progression. Therefore mission time cannot be assumed to advance identically to fixed/clamped physics time.

## 9. Runtime modes and teardown

The active VM branch is `!DAT_0051F640 && !g_is_network_mode && !DAT_0051F5C0`. The damage writer independently requires `!g_damage_side_effects_suppressed` to create attacker-source records. These two mode flags are **not the same variable** and should not be conflated:

| Network/trip flag | Suppressed-damage flag | VM may run when other gates allow | New source events from standard recorder |
|---|---|---|---|
| 0 | 0 | Yes | Yes, subject to damage predicates |
| 0 | 1 | Yes, if nodes actually exist | No |
| 1 | 0 | No: alternate AI update | Potentially yes |
| 1 | 1 | No: alternate AI update | No |

The shell has a path that sets damage suppression with the network/trip flag still zero; this is binary-established. Actual stock mission VM presence in that configuration has **not** been measured. In normal single-player class-1/8/9 damage/destruction paths, object destruction usually marks status and effects without immediately freeing the world object. Mode-dependent player replacement can instead cause immediate unregister; the more aggressive paths normally coincide with attacker-source suppression. This substantially reduces—but does not close—all exceptional stale-identity scenarios.

During normal top-level shutdown, CB/audio cleanup is performed before active-world teardown; the active-world registry then invokes removal callbacks before final object-reference release. The world-instance registry is destroyed as part of that teardown, and the FSM runtime is shut down later. **Do not infer that a module's cleanup order is identical in every error/failure path** without further tracing.

## 10. Validation limits and specification confidence

**Strongly established by machine code and references:** the BWD2 descriptor ABI and core loader call chain; 16-byte instance-key index and reverse lookup; world/actor reference ownership; node size and field map; 14-token interpreter operations; sequential cooperative scheduler; host command record-index versus runtime opcode split; synchronous AI invocation; mode gates; objective deadline scheduler; ring-buffer producer/consumer paths.

**Independently corroborated by shipped resources:** outer/nested BWD2 tags/revisions; 95-name lexicon; 80-file corpus structure; VM-node/token counts, paired-variant equivalence, missing `0x02/0x03/0x0B`; all known actor-key bytes appearing in corresponding ODEF sections.

**Not yet established:** exact malformed resource accept/reject behavior; all descriptor flag meanings; full typed argument contract for every host opcode; every indirect callback/reentrancy path; complete reachability of exceptional stale pointers; all world-object registries and media resource success cases; actual subroutine-call token execution; exact original source-file boundaries; global completeness of static negative assertions.

For tracked disagreements between versions, consult `RECONCILIATION_AND_OPEN_ISSUES.md` and `tables/EVIDENCE_REGISTER.tsv`. The authoritative symbol names are the validated v97 Ghidra names where available; the address is the identity for cross-version comparison.


## v0.3.0 loader contract addendum

The original selected-mission wrapper does **not** propagate parser failures as return-value failures and its top-level caller ignores EAX; the retail diagnostic function is nonterminating. The generic parser has descriptor-specific required/seen, callback-failure and cursor-return policies; the FSM importer does not have comprehensive local source-length validation. See `LOADER_VALIDATION_AND_FAILURE_CONTRACT.md` and `LOADER_FAILURE_MATRIX.tsv`. No malformed retail mission was executed.


## v0.4.0 descriptor state and repeat-load addendum

`004B3DB0` sets `0x80` on matched entries in caller-supplied, statically allocated descriptor tables. The mandatory-entry scan later tests `required(0x40) && !seen(0x80)`, without a per-invocation reset of those descriptor flags inside the parser. The root `BWD2` descriptor at `00500328` is shared by the selected-mission wrapper and at least two generic resource-loader entry points. Thus a previously observed BWD2 match can affect the later parser's required-section **branch**, even if a later resource omits BWD2. The present research does **not** prove that such a modified resource successfully completes loading; other checks and possible external reinitialization remain. See `DESCRIPTOR_STATE_AND_REPEATED_LOAD_CONTRACT.md`, model results and test plan.
