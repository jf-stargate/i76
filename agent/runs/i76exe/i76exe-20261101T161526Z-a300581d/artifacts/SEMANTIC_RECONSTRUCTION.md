# Mission VM and cooperative scheduler — semantic recovery pilot B

This run reconstructs an execution architecture, rather than proposing original developer symbols. The companion [C11 source sketch](vm_architecture.c) contains the conceptual types and six coherent roles. It is explanatory source with unresolved address-mapping, heap, stream and gameplay services declared as extern boundaries; it is not a usable replacement interpreter. No original instructions were executed. Claims below are **binary-static** unless explicitly marked derived, corpus, or unresolved.

## Evidence and reconciliation

The original PE SHA-256 is `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`. A fresh disposable Ghidra 12.1.4 import of private v97 GZF `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce` supplied decompilation. All **2,489 instructions** in the six selected functions match both the original PE and accepted v97 listings; see `evidence/BINARY_VERIFICATION.json`. Historical labels were not used as proof. No v98–v102 migration was applied to this private copy.

Accepted evidence at pinned base `8b16e9f81159c9f0f4dea63e16d69d79355b6d49`:

- `ref/mission_execution/MISSION_EXECUTION_CONTRACT.md` §§5–6: confirms node layout, ISA and list scheduling, with exact thresholds and completion test refined below.
- `ref/mission_execution/HOST_COMMAND_ABI_CONTRACT.md` §1: confirms separate host workspace, record-index/opcode distinction and dispatcher-owned IP advance. The sketch does not reset the predicate on ordinary commands.
- `ref/mission_execution/RECONCILIATION_AND_OPEN_ISSUES.md`: preserves loader/persistence qualifications; none of its open full-game questions is closed here.
- v93 ordering and v94 call-frame research in `ref/mission_execution/research_checkpoints/`: confirms the static execution model. v94's then-unresolved reporter behavior is narrowed by the authenticated PE's single RET at `0042D5D0`.
- Parser v0.5 and loader v0.6 checkpoints: original-instruction experiments for parser/loader subsets with substituted services. They did **not** execute the T01 VM and therefore do not provide dynamic VM or nested-call validation.
- `snapshot/i76.exe/i76.exe_ghidra_state_snapshot_20261021_v97/{decompile,disassembly}/`: accepted current mission snapshots. v98 host audit in `ref/mission_execution/evidence/v98_native_selected.txt` corroborates the bridge. Newer accepted v100/v101 tools concern other types; open PR #101's v102 class-dispatch proposal is outside this run.

There is no current promoted mission-VM page under `manual/reference/`. The existing engine frame-scheduling promotion provides broader context, not an independent nested-VM runtime test. All canonical files and accepted runs remain unchanged.

## Storage, widths and lifecycle

`VmNode32` is exactly `0x10BC` bytes. Every address field is a **32-bit guest address**, not a host pointer. Actual target memory is little-endian x86. The portable C layout uses `uint32_t` fields and offset assertions; Ghidra uses four-byte pointer types only for actual live cursors/links. Workspace elements and argument slots stay raw words, because either may contain an address or a scalar.

| Offset | Bytes | Recovered meaning |
|---|---:|---|
| 0000 | 1000 | 1024 mixed operand/context/frame words |
| 1000 | A0 | 40 mixed host argument words, distinct from operands |
| 10A0 | 4 | persistent condition, zero/nonzero truth |
| 10A4 | 4 | shared token-array address |
| 10A8 | 4 | entry **index during import**, IP address after relocation |
| 10AC | 4 | frame address, points at saved return IP |
| 10B0 | 4 | operand write cursor |
| 10B4 | 4 | host-argument write cursor |
| 10B8 | 4 | next execution node |

Sizes/offsets in this table are hexadecimal. All bytes have a structural region assignment; the **contents** of unwritten workspace/argument words remain unknown. `HostRecord32.unknown_00_4f` explicitly leaves unrelated command-prototype internals unknown. Neither the full mission environment nor AI internals are invented as original structures.

`00410490` first reads node count, allocates nodes with `HeapAlloc(heap,0,0x10BC)` and appends them in serialized order, terminating the last link with zero. It then reads each 168-byte seed: entry index, context count N, and 40 context words. It copies all 40 words and sets operand cursor to `node+4*N`. Zero nodes produces a null head. Allocation flags are **zero**, not HEAP_ZERO_MEMORY; no assumed calloc behavior or universal allocation policy is justified. No allocation-failure recovery was found in this routine.

`00412500` rewrites the first N words as `global_word_base + 4*index`, converts entry index to `token_base + 8*index`, clears condition and installs the synthetic outer frame. For node base A:

```text
A ... A+4*N-4      N relocated global-word addresses
A+4*N             previous-frame word = 0
A+4*(N+1)         saved return IP = entry IP   <- frame
A+4*(N+2)         next operand write position <- operand_cursor
A+1000            first host slot            <- host_cursor
```

Unused copied seed words beyond N can be overwritten by the synthetic frame; remaining allocation bytes are not initialized here. Runtime token and global-word storage is shared; only the node is freed on completion. Bulk FSM heap lifecycle is outside this pilot.

## Interpreter semantics

A token is `{u32 kind, u32 payload}`. `00414670` loops within **one node** until explicit suspension, outer return, or failure. `p` below is the raw 32-bit payload; address arithmetic is modulo 2^32. In particular frame-relative offsets can encode negative displacements in two's complement; they must not be treated as universally nonnegative array indices.

| Kind | Effect |
|---:|---|
| 1 | write immediate p at operand cursor, cursor +=4, IP +=8 |
| 2 | write address `frame+4*p` to operand workspace, cursor +=4, IP +=8 |
| 3 | write word read from `frame+4*p` to operand workspace, cursor +=4, IP +=8 |
| 4 | append address `frame+4*p` to **host** workspace, host cursor +=4, IP +=8 |
| 5 | append word read from `frame+4*p` to **host** workspace, host cursor +=4, IP +=8 |
| 6 | operand cursor +=4*p without initializing skipped words; IP +=8 |
| 7 | operand cursor -=4*p; IP +=8 |
| 8 | IP = token_base+8*p; continue this invocation |
| 9 | if condition==0 take indexed jump, otherwise IP +=8 |
| 10 | IP = token_base+8*p; return 0 immediately, preserving node |
| 11 | push saved frame then return IP; install frame at return-IP word; indexed jump |
| 12 | restore IP and prior frame; operand cursor = old_frame-(4*p+4); return 1 only if cursor==node base |
| 13 | invoke source command record p synchronously; dispatcher performs normal IP advance and argument reset |
| 14 | condition = (condition==0), IP +=8 |

Address versus value is one extra memory read: token 4 passes a reference to a frame slot, whereas token 5 passes the slot's contents. Initial frame context slots contain **addresses of global words**. Consequently a frame-relative value can itself be a pointer. Host slot consumers often dereference it to get a scalar or actor index. Do not model token 5 as an unconditional final scalar-value conversion.

### Nested and outer return

For an old operand cursor S and frame F, call writes `[S]=F`, `[S+4]=IP+8`, sets frame=S+4 and operand cursor=S+8, then jumps. Return reads saved IP from `[frame]` and old frame from `[frame-4]`, and computes new cursor `frame-4*(p+1)`. The operand words being discarded lie **before the saved linkage**, not simply at the current operand top. Additional locals/temporaries above frame are abandoned by restoring from frame, regardless of current cursor.

Completion is the exact **cursor==node-base** comparison at `004148F4`, not frame==0. For the initialized outer frame, `return N` computes A, restores entry IP and the zero frame, and returns completion before fetching entry again. A nested call with p argument words just below its linkage restores the caller cursor to the start of those words. A malformed p is not checked against the null sentinel. Thus the usual outer/nested distinction follows producer invariants, not a protected frame-depth counter.

### Instruction budget and failure

A local counter starts at zero for every interpreter invocation. At loop entry, `retired>800` sets global `005244DC` to one: first eligible execution is token **802**, after 801 loop-tail increments. It neither yields nor calls the reporter at that threshold. The latch is shared with some synchronous AI calls; it is not reset on interpreter entry. After a normally loop-tail-reaching token, the counter increments; reaching **1000** invokes process `exit(0)`. Yield and completing return bypass that tail, so a yield/completion in dispatch 1000 returns normally. Nested returns and host calls otherwise count as one token each, not their transitive work.

An unknown kind reaches `report_error` at `00414958` without changing IP. Because the reporter is RET in this retail PE, it repeats that token, sets the budget latch, and ultimately reaches exit(0), absent external intervention/fault. This is a static deduction from the complete path, not a malformed-bytecode execution experiment. Unsupported host opcode has a separate report+abort path. No local bounds checks on indices/cursors/frames were found in the six-function path; this does not establish upstream malformed-file reachability or complete input safety.

## Host interface and recovered call envelopes

Token 13 payload indexes **0x54-byte serialized command records**. Dispatcher reads opcode at +0x50 and switches over engine IDs, then normally resets host cursor to node+0x1000 and advances IP by eight. The interpreter must not advance it a second time. Predicates may write condition; output-variable commands write through argument references; side-effect commands commonly preserve the prior condition. Some host handlers call AI evaluator `00412830` synchronously. This alone establishes ordinary nested C calls, not recursion into VM execution.

A new readability qualification is that the historical Ghidra formal counts omit caller-supplied words. Call-stack arithmetic, authenticated against the PE, gives:

| Function | Actual cdecl words supplied at examined calls | Explanatory mapping |
|---|---:|---|
| scheduler 004149F0 | 16 | tokens count/base; command base/count; media base/count; position base/count; actor base/count-pointer; head-pointer/count-pointer; initial-word base/count; heap; opaque forwarded word |
| interpreter 00414670 | 12 | node; token base; command base/count; media base/count; position base/count; actor base/count-pointer; opaque forwarded word; node visit ordinal |
| dispatcher 00412CE0 | 12 | node; source record index; command base/count; media base/count; position base/count; actor base/count-pointer; opaque forwarded word; local scratch pointer |

The first ten published interpreter/dispatcher parameters have the same stack offsets as before. Scheduler param 15 remains heap. The scheduler's extra word comes from runtime caller `[EBP+8]`; its ultimate purpose remains **unresolved**, and it is not treated as another heap. Scheduler's ordinal starts at zero and increments after each visited node. No consumer of that ordinal in the interpreter, or of the two trailing dispatcher words, was identified. The interpreter prepares 80 local scratch bytes (first byte copied from 00504C28, remaining 79 zero) and passes the address. Do not interpret scratch as the node's host argument buffer or infer diagnostic semantics from its presence. These ABI envelope proposals expose the raw calls without claiming original source prototypes.

Evidence: runtime call `0040A5F0–0040A649` (16 pushes, cleanup 0x40), scheduler calls `00414A34–00414A5D` and `00414AC4–00414AE9` (12 pushes, cleanup 0x30), interpreter call `00414909–0041494E` (12 pushes, cleanup 0x30). Scheduler reads extra word into EBX at `00414A24` from ESP+0x50 after 16 bytes of saved registers; interpreter forwards arg11 from ESP+0x90 after its 0x64-byte prologue. This is precisely why formal parameter count alone is insufficient.

## Scheduler and mission runtime architecture

`004149F0` first compares mission elapsed time with global deadline and calls the game-flow setter if due, **even if the list is empty**. It then consumes completed heads until a head yields, and traverses successors with a retained predecessor. Completed nodes decrement count, are unlinked, and are passed to HeapFree(heap,0,node). Yielded nodes keep workspace, condition, token base, resume IP, frame, both cursors and next link across frames. Neither yield nor scheduling clears partial host arguments.

The unified predecessor loop in the sketch is a **derived equivalent** for well-formed lists and normal host services that do not mutate links. Order is serialized list order; following nodes run in the same pass. Yield does not restart the head. There is no instruction round robin, priority queue, sleep-time field, or implicit condition wait. A polling script must explicitly arrange its next resume index. A due game-flow transition does not short-circuit traversal; deadlines set during a host call are not rechecked until a later scheduler entry.

`0040A320` runs the relevant path only when `0051F640==0`; after bounds/progress preparation it invokes the scheduler when `is_network_or_trip_runtime_mode()==0 && 0051F5C0==0`, otherwise alternate AI targeting. It updates progress comparison and increments damage epoch through `004155F0` **after** either path. The sketch abstracts the vehicle/radar/control preparation and cleanup, rather than reconstructing AI/gameplay outside the pilot.

An earlier node can consume a shared one-shot condition before a later node sees it. The node condition and frame are private, but actors/global words, AI events, media and deadline state are shared. v93 supplies the transitive damage-event and shared-rand evidence; this run does not re-audit all event helpers. Direct callgraph evidence has the VM entered from two scheduler sites. Indirect callback recursion or alias-based list modification remains unexcluded.

## Corpus versus static capability and limits

**Inherited corpus evidence**, not a new dynamic run: v94's 40 miss8 and 40 miss16 resources contain 25 nonempty scripts per variant, 797 initial nodes and 90,923 tokens per variant. Token kinds 2, 3 and 11 are absent. Their semantics above are nevertheless directly instruction-supported. Static occurrence does not demonstrate dynamic reachability of every other token. No full mission, host-command inventory, AI state behavior, loader validity contract, original source module boundary, or nested-call execution depth is claimed recovered here.
