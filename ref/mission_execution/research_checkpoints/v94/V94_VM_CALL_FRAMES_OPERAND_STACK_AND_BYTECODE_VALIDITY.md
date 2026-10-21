# I76 retail mission execution — v94 VM call frames, operand stack and bytecode validity

**Date:** 2026-10-20. **Binary authority:** retail `i76.exe`, MD5 `a640ea0097dbb62e0c77b7f2847c7161`. **Native analysis:** Ghidra 12.1.4 headless, existing annotated v92 project (same foundation as read-only v93); 17 distinct functions successfully decompiled, assembly exported. **Corpus evidence:** original `i76_base(1).tar`, all 40 `miss8/*.MSN` and all 40 `miss16/*.MSN` mission files. **Scope:** analysis only, no engine execution or reimplementation.

## Executive assessment

1. **The VM execution node is 0x10BC bytes with two separate scratch regions:** a 0x1000-byte frame/operand workspace and a 0xA0-byte (40-word) host-command argument array. The last 0x1C bytes hold seven execution/list fields. The frame workspace is *not* the 40-argument array.
2. **The loader constructs an initial synthetic frame**, relocates the input's initial context words into pointers to global VM words, places a null prior-frame sentinel followed by an initial return address, and points the operand cursor beyond that initial frame. VM opcode `0x0B` pushes subsequent frame links and return IPs; `0x0C` restores both and indicates completion only when the stack cursor reaches the node base.
3. **No explicit token/IP bounds, operand-stack capacity checks, host-argument capacity checks, frame-depth checks, or command-index bounds checks were found in the directly decompiled VM and host dispatch path.** There is a VM kind rejection path and an instruction-count ceiling. The nested FSM loader reads its source via a count-based dword cursor and does not consult the source byte length passed to it. This is a scoped static observation, *not* proof that externally malformed mission files can bypass upstream BWD2 validation or cause a specific crash.
4. **All 25 nonempty FSM chunks in 40 shipped `miss8` missions parsed exactly** under the loader-derived seven-table serialization. They contain 90,923 VM tokens across 797 initial execution nodes. No unknown kind, out-of-range static branch/yield/call destination, out-of-range host-command index, invalid initial entrypoint, initial context over 40 words, or invalid global-word relocation index was found.
5. **The shipped corpus never uses VM tokens `0x02`, `0x03`, or `0x0B`.** In particular, the native subroutine call/frame mechanism is present in the engine but not corroborated by a subroutine-call instruction in these 25 stock scripts. The `0x0C` return token occurs 2,700 times; the `0x0A` yield token occurs 2,704 times. The absence is corpus-specific, not proof the compiler cannot generate these tokens.
6. **The `miss8` and `miss16` variants have identical bytecode streams and initial VM node records for all 40 paired missions.** 38 entire FSM payloads are byte-identical; `T11.MSN` and `T15.MSN` vary in a small number of actor-record metadata bytes while retaining the same token streams, node initializers, and table counts.
7. **A Ghidra decompiler parameter-label artifact was detected** in `00410720`: the decompiled source assigns the allocated token pointer through the wrong formal-parameter name on one path. Native machine instructions at `004109CB` and the argument pushes at `00409785` show that the target is the `g_fsm_vm_token_array` output pointer (`0051F638`). Do not infer a retail loader bug from the faulty decompiler variable label.

## A. Node allocation, exact fields, and frame initialization

Allocation at `004104CC` pushes `0x10BC` into `HeapAlloc`. Runtime field accesses from `00412500` and `00414670` establish:

| Node-relative bytes | Size | Verified purpose |
|---|---:|---|
| `+0000..+0FFF` | `0x1000` | Shared frame/context and operand word workspace; 1024 dwords; no observed dynamic stack-limit enforcement |
| `+1000..+109F` | `0xA0` | Forty 32-bit host-command argument slots; command argument cursor reset to `node+0x1000` by dispatcher |
| `+10A0` | 4 | VM condition/result flag |
| `+10A4` | 4 | Token array base |
| `+10A8` | 4 | Current token instruction pointer |
| `+10AC` | 4 | Current frame base / link slot following saved prior frame |
| `+10B0` | 4 | Operand stack write cursor |
| `+10B4` | 4 | Host-command argument write cursor |
| `+10B8` | 4 | Next linked runnable VM node |

Wire node: `u32 initial_instruction_index; u32 initial_context_word_count; 40*u32 initial_context_values` = 168 bytes. `00410490` copies the 40 dwords into node `+0000` and sets `+10B0 = node_base + initial_context_word_count*4`; no independent check on this count is visible there.

For a node initialized with N words, `00412500`:

- Rewrites the first N node words from indices into pointers `g_fsm_vm_initial_word_array + index*4`. This means initial context entries are references, not just scalar values.
- Sets result (`+10A0`) to zero and token base (`+10A4`) from the global token table.
- Converts the initial instruction index at `+10A8` into `token_base + instruction_index*8`.
- Writes zero at `node+N*4` as the outermost saved-frame sentinel, then saves the entry IP at `node+(N+1)*4`.
- Sets frame (`+10AC`) to the saved-IP word, operand cursor (`+10B0`) to the following word and host-argument cursor (`+10B4`) to `node+0x1000`.

The frame is therefore represented *inside* the 1024-word workspace and shares that capacity with operand data. No separate heap-allocated per-call stack frames were observed.

## B. Token instruction set and cursor effects

Each token is a pair `{u32 kind, u32 payload}` occupying 8 bytes. The interpreter jump table at `004149B8` dispatches 14 defined token kinds (`1..14`). The following operations are proven from `00414670`, both decompiled C and individual x86 instructions:

| Token | Effect | Cursors/side effects |
|---|---|---|
| `0x01` | Push immediate 32-bit payload | Write to operand cursor; `SP+=4`, `IP+=8` |
| `0x02` | Push address of frame-relative word `frame+payload*4` | `SP+=4`, `IP+=8` |
| `0x03` | Push value of frame-relative word | `SP+=4`, `IP+=8` |
| `0x04` | Append frame-relative word **address** to host argument array | `ARG+=4`, `IP+=8` |
| `0x05` | Append frame-relative word **value** to host argument array | `ARG+=4`, `IP+=8` |
| `0x06` | Increase operand cursor by `payload*4` without writing data | `SP+=payload*4`, `IP+=8` |
| `0x07` | Decrease operand cursor by `payload*4` | `SP-=payload*4`, `IP+=8` |
| `0x08` | Jump to absolute **token index** | `IP=token_base+payload*8` |
| `0x09` | Jump to token index if result is zero; otherwise advance | Conditional `IP` |
| `0x0A` | Save token-index continuation and yield (return status 0) | `IP=token_base+payload*8`; scheduler retains node |
| `0x0B` | Call token-index subroutine | Write old frame link and `return_IP=current_IP+8` at operand cursor; new frame points to return IP; branch to token index |
| `0x0C` | Return, discarding `payload` frame/argument words plus linkage | Restore saved IP and prior frame; `SP=frame-(payload*4+4)`; status 1 only if `SP==node_base` |
| `0x0D` | Execute host command record at index `payload` synchronously | `00412CE0`; dispatcher resets `ARG=node+0x1000` and advances `IP+=8` |
| `0x0E` | Boolean negate previous result | `result=(result==0)`, `IP+=8` |

In `0x0B`, the two saved frame words are `(previous frame pointer, return IP)`. In `0x0C`, `payload` is the number of frame words removed on return; it is **not** a target token index. This distinction matters to later correctness tests. `0x0A` is a true yield with an explicit resume index; `0x08` is an intra-invocation jump.

## C. Validation boundaries observed in retail code

| Area | Positive observed validation | Missing or unresolved validation in these paths |
|---|---|---|
| Source chunk | BWD2 callback obtains a size and payload pointer; parser iterates seven recognized table categories | `00410720` accepts size but no observed byte-length check before stream word loads; upstream loader validation remains a separate research question |
| VM kind | `004146C5` limits dispatch to 1..14; unknown kind calls `0042D5D0 report_error` | Unknown kind branch does not itself advance `IP`; exact behavior of the error reporter not established by this pass |
| Host command names | `00410A10` recognizes named commands and calls `report_error` + `abort` for unknown names | No observed bound check for **token** `0x0D`'s record index before `00412CE0` computes `base + index*0x54 + 0x50` |
| Host opcode | `00412CE0` falls to `report_error` + `abort` for unsupported command IDs, including `playScene` `0x16` | This check occurs **after** the command record pointer is dereferenced |
| Branch/call/yield destinations | Shipped corpus values all within token count | Runtime VM performs direct `token_base+index*8` without observed range check |
| Operand/frame storage | Fixed `0x1000`-byte workspace | No explicit cursor bounds or call depth check in `00414670` |
| Command arguments | Separate fixed 40-dword array reset after command | No explicit argument-count limit check in `00414670` or dispatcher |
| Execution budget | Soft warning once local instruction count exceeds 800; process `exit(0)` after hard 1000 threshold | Budget is not a stack safety check and does not yield automatically |
| Allocations | Heap allocations sized from stream counts | No comprehensive allocation-failure or count-overflow checks proven in examined loader routines |

**Interpretation:** The retail VM appears designed for trusted precompiled mission bytecode. These are absence-of-check findings within audited routines, **not** a claim about exploitable input vectors. The BWD2 framework and mission-loading wrapper could reject invalid files before the FSM callback.

**Decompiler correction:** `00410720` C output shows a misleading `*param_12` destination when allocating the token array. At `00409785`, the caller passes `&g_fsm_vm_token_array` (`0x0051F638`) as the 15th argument; `004109CB MOV EDX,[ESP+0x4C]` retrieves this same output pointer after the four-register prologue. The instruction writes through that pointer. We did **not** change Ghidra parameter definitions in this pass; the report records the correct machine semantics for later type cleanup.

## D. Independent shipped-mission evidence

From the original game archive, `miss8` contains 40 `.MSN` files. Fifteen have the legitimate `FSM\0` chunk size 8 (no serialized script tables). The other **25** have payloads that exactly fit the inferred wire format:

1. Counted 40-byte named command records (95 names in each nonempty chunk; runtime records 0x54 bytes).
2. Counted actor records (40-byte name + two 32-bit identity/flag values; runtime records 0x60 bytes, with 200 extra reserved slots).
3. Counted 40-byte media records.
4. Counted named-position records, each 40-byte name plus count and 3-float vectors; runtime stride 0x58.
5. Counted initial VM nodes (2-word header plus 40-word context per node).
6. Counted global initial 32-bit words.
7. Counted `{kind, payload}` 8-byte VM tokens.

No unread payload bytes remained in any of the 25, and no count/bounds violations were detected by the independent read-only inspector. Corpus totals: **797 nodes** and **90,923 tokens**; largest single mission has **67 nodes**, **5,070 tokens**, and a maximum initial context of **37 words** versus 40 copied words. Token kind frequencies appear in `v94_shipped_mission_fsm_summary.json`. Kinds `0x02`, `0x03`, and `0x0B` are absent. (A corpus's lack of an opcode does not invalidate the actual runtime implementation of that opcode.)

For all 40 names present in both `miss8` and `miss16`, bytecode and serialized initial nodes are exactly equal. FSM payloads are byte-identical for 38 pairs. Only T11 and T15 differ inside actor metadata (16 and 26 bytes respectively); the changed values are within the actor portion of the payload. This comparison is in `v94_miss8_miss16_fsm_comparison.tsv`.

## E. Confidence, limits, and future test specifications

**High confidence**: actual node memory layout; cursor/frame behavior; 14 token cases; the seven wire tables; complete `miss8`/`miss16` static corpus parsing; token indexes and direct host-command indexing. Native code, Ghidra assembly, and shipped serialized values corroborate each other.

**Medium-high**: lack of local VM bounds checks. This is substantiated by the audited functions but may be mitigated by upstream validators or producer invariants. The decompiler parameter mistake highlights why check-by-assembly is required.

**Still unresolved**: actual maximum runtime nested-call depth (no `0x0B` in shipped corpus), behavior after malformed invalid tokens, stack overrun behavior, whether all stock token indices are dynamically reachable, and exact upstream BWD2 rejected-input policy. **No live gameplay, fuzzing, or malformed-file execution was conducted.**

Suggested later tests:

- Trace single-node push/host-argument/reset/return on a selected retail mission with a debugger, comparing frame pointers with this ABI.
- Compare `0x0A` token-index resume location and next-frame position after yielding.
- Exercise `0x0B/0x0C` call-frame linkage using a safe, purpose-built test environment only in a future validation phase; stock missions don't exercise `0x0B`.
- Validate a sampled end-to-end trace across `controlAll`, `driveControl`, `controlDone`, and scheduler re-entry.
- Test BWD2 byte-count handling separately from nested FSM parsing, without risking user files or installations.
- Preserve known-good corpus baseline to reject any future reimplementation that misreads pointer relocation or token layout.

## Source-layout hypothesis (kept separate)

- **Observed contiguous low-level loader functions:** `004102D0` named-position table; `00410490` node loader; `004105A0` actor table; `00410720` master table loader. Their address adjacency and shared stream globals provide *moderate* evidence of an original source-module or adjacent object-file cluster, not exact `.c` boundaries.
- **Code neighborhoods:** `00410A10–004122A6` 96-name decoder, `00412400–004125C0` FSM fixup/registration/finalizer, `00412CE0–00414B30` host dispatcher/token interpreter/scheduler. Together they support broader subsystem proximity; separate original translation-unit assignments remain speculative.

## Reproducibility and included evidence

`i76_v94_fsm_frame_and_validation.java` (native decompiler, assembly windows, symbols, xrefs), `v94_inspect_shipped_fsm.py` (read-only shipped-mission wire inspector), `v94_compare_resource_variants.py` (miss8/miss16 comparison), `v94_verify_static_and_corpus.py` (machine-checkable assertions and **inspector-only** synthetic edge tests), exported TSVs, JSONs, and logs. The downloadable archive **does not reproduce copyrighted game mission files or the game executable**; the scripts can be rerun against a locally owned game installation.
