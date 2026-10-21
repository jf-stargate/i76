# Interstate '76 — descriptor state, shared BWD2 tables and repeat-load contract

**Specification**: I76-MISSION-0.4.0, supplement to v0.3.0.  
**Retail executable**: `i76.exe`, MD5 `a640ea0097dbb62e0c77b7f2847c7161`.  
**Method**: read-only Ghidra 12.1.4 extraction against verified v97 symbols; independent inspection of parser machine instructions, static descriptor bytes, incoming references and callers; bounded Python *logic-only* probes. **No original-engine malformed-resource execution.**

## 1. Principal finding

The generic BWD2 parser at `004B3DB0` **mutates its caller-supplied descriptor table in place** and retains the `0x80` *seen* bit. For sequential matching (`param_6 != 0`), the exact machine operations are:

- `004B3F2C`: `MOV EAX,[EDI+0xC]` (load entry flags)
- `004B3F2F`: `OR AL,0x80` (mark matched entry seen)
- `004B3F31`: `MOV [EDI+0xC],EAX` (write back to original descriptor)
- `004B4160–004B416B`: at completion, test `0x40` (required) and `0x80` (seen); a required-but-unseen entry enters the report/failure path at `004B4177`.

There is **no clearing of `0x80` in the audited parser**. This is an exact local statement, not a whole-process nonexistence proof. This matters because descriptors at `00500328` and `00500D20` are **static addresses reused by multiple parser invocations**, not fresh stack records.

## 2. The root table is shared beyond mission loading

The root descriptor table begins at `00500328` and has two 16-byte entries. The following distinct paths pass the **same address** to `004B3DB0`:

| Caller/callsite | Role | Instruction evidence |
|---|---|---|
| `004B41E0` / `004B423F` | Generic named-resource loader | `004B4234 PUSH 0x500328` (and parser call `004B423F`) |
| `004B42B0` / `004B44C8` | Selected-mission loader | `004B44C2 PUSH 0x500328`, call `004B44C8` |
| `004B4A80` / `004B4AEF` | Another named-resource loading path | `004B4AE4 PUSH 0x500328`, call `004B4AEF` |

Generic resource loader `004B41E0` has numerous direct callers throughout the resource and object subsystems (see the untruncated callsite inventory). Therefore a previous **successful generic BWD2 parse**, not necessarily a previous *mission*, can set the root seen state. It would be misleading to assume that the first selected mission loads against pristine descriptor flags.

The outer world-section descriptor array (`00500348`, seven entries) and nested ADEF table (`00500D20`, three entries) are likewise static, shared between parse invocations. World and ADEF records have no `0x40` *required* bit in the stock descriptor bytes, so their persistent `seen` bits **do not independently activate this particular required-section check**. Other parser state and callback policies can still affect them.

## 3. Initial descriptor state

The original image's 12 mission-relevant descriptor records all have `0x80` clear. Key examples:

| Address | Tag | Flags before any parse | Required (`0x40`)? |
|---|---|---|---|
| `00500328` | `BWD2` | `0x0044` | Yes |
| `00500338` | `REV` | `0x2020` | No |
| `00500348` | `WDEF` | `0x2006` | No |
| `00500398` | `ADEF` | `0x2006` | No |
| `00500D20` | `AREV` | `0x2004` | No |
| `00500D30` | `FSM` | `0x0001` | No |

The expected warm value for `BWD2`, once its match branch executes, is `0x00C4`: its existing `0x0044` OR `0x0080`. This is **runtime state**, not an edit to the retail PE on disk.

## 4. First-pass versus later-pass check: static control-flow trace

The following traces hold the surrounding conditions constant (sequential mode, readable bounded resource, valid `REV` callback and ordinary descriptor exhaustion) and isolate the BWD2 required/seen bit. These are **branch-derived conditional outcomes**, not claims of a successful modified-resource load in retail gameplay.

| Scenario | Initial BWD2 seen | BWD2 encountered? | Required-bit result | Broader parser/game result |
|---|---|---|---|---|
| Fresh table, normal root | 0 | Yes | Seen set, required passes | Dependent on revisions, bounds, callbacks |
| Fresh table, BWD2 omitted | 0 | No | Required check can return null | Other paths also possible |
| Table warmed by earlier BWD2 match, BWD2 omitted | 1 | No | **Required check no longer rejects omission** | Other checks remain; runtime untested |
| Table warmed, `REV` callback rejects | 1 | Irrelevant | Cannot override `0x20`-policy rejection from revision callback | Rejected on that path |
| Fresh table, prior BWD2 match then later callback fails | 1 | Yes | Seen state retained unless an unobserved reset occurs | Parse may fail for independent reason |

Sequential parser behavior at `004B3E90–004B3F27` may advance past an absent expected descriptor to the next descriptor. The subsequent mandatory-scan loop uses the **persisted** flag value rather than a per-invocation matched-descriptor set. On a root whose first expected `BWD2` chunk is absent but the following `REV` chunk matches, the `0x40`/`0x80` check is therefore state-dependent.

A Python micro-model included in this checkpoint executes **only** that required/seen Boolean clause and the explicit match-bit update. It does not emulate the full BWD2 parser and is not an engine-runtime test.

## 5. Writer and reset closure: what we can and cannot prove

The v100 Ghidra reference audit enumerated references to **every byte** of the twelve static mission descriptor records. Five explicit code references to the tables were found, all pointer uses in the three outer-parser call families and nested ADEF wrapper. In the audited `004B3DB0` body, the only descriptor-flag write is the `OR 0x80` store; no `AND 0x7F`, descriptor-copy reinitialization, or `memset` appears in this function. Its loop-local parsing state is separately reinitialized on each invocation, but this does **not** reset the referenced tables.

The function at `004B84E0`, named `reset_mission_resource_parse_callbacks` in inherited Ghidra symbols, only registers the world-object-tree callback used by mission loading; it does not restore descriptor bytes. This inherited name is misleading. No Ghidra rename was applied in this checkpoint, to avoid changing the established v97 baseline.

**Closure limit:** direct references and the audited call graph support persistent descriptor bits across ordinary same-process calls. They do not rule out every indirect write, external patch, global-memory reinitialization, or unexamined lifecycle path. A whole-process repeated-load trace is still required to establish actual values in a particular gameplay sequence.

## 6. Implications for loader acceptance and security interpretation

1. The parser's required-check has **historical state**. A successful prior BWD2 match can satisfy a later required check independently of the later input.
2. The root table is **cross-resource shared**. A non-mission resource load may be sufficient to warm it before mission loading.
3. The incorrect semantic name for `004B84E0` should not be used as evidence of clearing flags.
4. This is **not** proof that arbitrary malformed missions load or run. Revision callbacks, length checks, section callbacks, resource-cache behavior, object initialization, and the top-level engine can independently fail.
5. No claim of memory corruption, crash, exploitability or safe acceptance has been established by this static pass.

## 7. Evidence / reproduction

- `evidence/v100_descriptor_initial_values.tsv`: 12 immutable image values for static descriptor flags.
- `evidence/v100_descriptor_references.tsv`: explicit static references to every byte of selected descriptor arrays.
- `evidence/v100_parser_call_sites.txt`: machine-instruction windows around all parser incoming calls and key wrapper functions.
- `evidence/v99_loader_full_instructions.tsv`: full parser assembly, including the exact `seen` write and final required test.
- `evidence/v99_loader_native_decompiled.txt`: decompiler-side functional trace.
- `evidence/v100_targeted_decompilation.txt`: refreshed native audit of loader, parser, revision callback and reset helper.
- `i76_v100_descriptor_lifecycle.java`: reproducible read-only Ghidra extractor.
- `descriptor_required_seen_model.py` and `evidence/REQUIRED_SEEN_MODEL_RESULTS.json`: unit-sized logic-only probes with explicit runtime-test disclaimer.
- `DESCRIPTOR_STATE_TEST_PLAN.md`: proposed fault-isolated gameplay observations for future work.

The v0.3.0 loader contract remains authoritative for **callback failure return paths, complete descriptor masks, revision policy and FSM import**, and the v0.2.0 ABI remains authoritative for the 96 host commands. This v0.4.0 supplement supersedes v0.3.0's characterization of persistent seen state as a merely *plausible* parser-local behavior; it remains **not dynamically observed**.

**Confidence**: **B/high** on machine-level bit mutation, required check, static address reuse and the absence of a parser-local clear; **I/medium-high** on cold/warm branch outcomes under specified preconditions; **U** on real repeated-session malformed-file behavior.
