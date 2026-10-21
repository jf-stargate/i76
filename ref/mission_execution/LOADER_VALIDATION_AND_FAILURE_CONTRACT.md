# Interstate '76 — BWD2/FSM loader validation and failure contract

**Specification:** I76-MISSION-0.3.0, loader supplement to v0.2.0 host-command ABI.
**Subject:** retail `i76.exe`, executable MD5 `a640ea0097dbb62e0c77b7f2847c7161`.
**Method:** 17 read-only native Ghidra 12.1.4 decompilations of the independently verified v97 program, an additional read-only eight-function policy pass, full function assembly, direct-call and incoming-reference inventories, and an independent structural check of 80 shipped `.MSN` files. **No malformed game resources were executed.**

## 1. Principal correction: parser rejection does not imply mission-level rejection

The term *success* has at least four distinct meanings here:

1. **Generic parser cursor** (`004B3DB0`): returns the next cursor on allowed paths or `NULL` on selected failure branches. This is the only direct error/continuation signal at the generic level.
2. **Section callback result**: a callback can return zero; the parser applies *descriptor-specific* behavior. Zero is **not** universally fatal.
3. **Selected-mission loader result** (`004B42B0`): after any local failure it calls `report_error`, but all normal exits converge at `004B4534 MOV EAX,1` and return `1`. This does **not** accurately represent the nested parser result.
4. **Top-level game callsite** (`00402B30`, `004034F4`): calls `004B42B0`, cleans its argument, and proceeds with further initialization at `004034FC` without examining the return register.

`report_error` (`0042D5D0`) in this **specific retail binary** is just `RET`. It logs nothing, throws nothing, and does not terminate execution. Other branches may call `abort` or `exit` independently and are not neutralized by this stub. Therefore: **reported** is not synonymous with **rejected**, and **wrapper-returned-success** is not synonymous with **loaded correctly**.

The related *generic resource* helper `004B41E0` is different: it returns a Boolean based on the parser cursor and can return false. That helper should not be used to infer the selected-mission wrapper's return behavior.

**Machine-level evidence:** `v99_loader_full_instructions.tsv` at `004B4510–004B4540`, `v99_reset_and_caller_disasm.tsv` at `004034EF–00403501`, and `v99_loader_native_decompiled.txt` function `0042D5D0`.

## 2. Outer-to-inner callback chain

```text
00402B30 top-level game caller
  004B42B0 selected mission loader, unconditional return 1
    004B3DB0(BWD2/REV descriptors, count=2, 00500328)
        BWD2 => 004B8960, constant success / no-op
        REV  => 004B4610, revision policy
    [if first returned non-null]
    004B3DB0(world section descriptors, count=7, 00500348)
        WDEF => 004B4550 => 004B89E0
        TDEF => 004B4570 => 00493910
        RDEF => 004B4590 => 004B8750
        ODEF => 004B45B0 => 004B7A90
        LDEF => 004B45D0 => 004B8F40
        ADEF => 004B45F0 => 004B89B0
           004B3DB0(AREV/FSM/EXIT descriptors, count=3, 00500D20)
              AREV => 004B4610
              FSM  => 00409740
                 00410720 counted-table reader + helpers
                 004125C0 finalizer (names, actor bindings, media, node pointers)
              EXIT => 004B4290
        EXIT => 004B4790 (player-object check; returns 1)
    resource-cache reference released
```

**ABI:** each descriptor is a 16-byte tuple `{4-byte tag, auxiliary word, callback pointer, flags}`. Callback resides at `+0x08`, flags at `+0x0C`. Handler addresses above are either direct descriptor pointers or assembly-verified forwarding wrappers; original symbol names are *not* authoritative about return types. For example, decompilation calls `004B45F0` `void`, but its assembly (`CALL 004B89B0; ADD ESP,0xC; RET`) leaves the nested Boolean in `EAX`, so the generic parser receives it as the callback result.

## 3. Descriptor-driven validation and state

The generic parser `004B3DB0` can run in **sequential** (`param_6 != 0`, used by missions) or **search/match** (`param_6 == 0`) mode. It does not simply scan an unordered dictionary of independent tagged chunks. In sequential mode, it advances a 16-byte descriptor cursor, maintains state for nested/repeated sections, checks the active four-byte tag, and conditionally advances the serialized chunk cursor by the stored size word at `chunk+4`.

**Machine-observed flag operations (not guesses from historical tag labels):**

| Mask | Directly verified parser behavior | Qualification |
|---|---|---|
| `0x004` | On certain mismatch or unsuccessful-callback paths, invokes error reporter but does not by that bit alone return `NULL`. | Branch context matters; not universally 'ignore error'. |
| `0x008` | Diagnostic call on specified mismatch/failure branches. | Calling reporter is no-op in this build. |
| `0x010` | Can return the current cursor non-null instead of rejecting. | Context-sensitive early return. |
| `0x020` | Can return `NULL` on mismatch or failed callback. | Explicit rejection return. |
| `0x040` | Required descriptor: at finalization, absence of `0x080` records a failure and may force `NULL`. | The `0x040` test is performed against each 16-byte entry. |
| `0x080` | Mutable 'seen' bit: set in the descriptor flags on a matched tag. | The function **writes to descriptor memory**, not to a transient shadow table. |
| `0x100`, `0x200`, `0x400` | Control internal nesting/repetition and local transition state. | Precise behavior depends on earlier matches and callback result; not promoted to single-word semantics. |
| `0x800`, `0x1000`, `0x2000` | Select callback context argument source: caller context (`param_4`), descriptor pointer, or resource identifier (`param_5`). | Combined flags cause diagnostics; delivery still depends on branch. |

The parser tests the optional end pointer before some advances and against a computed next cursor, but it dereferences `chunk+4` for the size before proving the full header is readable and does not provide a general checked-subspan reader to the FSM importer. A zero, extremely short, oversized, or wrapping chunk length is therefore **not proven safely rejected** by these routines. In particular, do not equate `end <= cursor+declared_size` with a complete length and arithmetic-overflow validation procedure.

**Descriptor-seen persistence question:** `0x080` is ORed into each matched descriptor's in-memory flags. `004B84E0`, despite its inherited 'reset parse callbacks' name, registers an object callback; its audited body does **not** clear descriptor flags. This creates a plausible persistent-seen-state concern for repeated loads in one process, but we have not completed whole-program writer closure or demonstrated it in gameplay. No cross-load acceptance claim is made.

## 4. Concrete descriptor configuration

| Tag | Entry | Callback | Flags | Notes |
|---|---|---|---|---|
| `BWD2` | `00500328` | `004B8960` | `0x0044` | Required/seen handling plus diagnostic mode; callback is no-op. |
| `REV\0` | `00500338` | `004B4610` | `0x2020` | Revision check; callback failure may force null via `0x20`. |
| `WDEF` | `00500348` | `004B4550` | `0x2006` | Forwards nested parser status in EAX. |
| `TDEF` | `00500358` | `004B4570` | `0x2006` | Same outer descriptor flags. |
| `RDEF` | `00500368` | `004B4590` | `0x2006` | Same outer descriptor flags. |
| `ODEF` | `00500378` | `004B45B0` | `0x2006` | World-object producer before actor fixups. |
| `LDEF` | `00500388` | `004B45D0` | `0x2006` | Same outer descriptor flags. |
| `ADEF` | `00500398` | `004B45F0` | `0x2006` | Preserves EAX from nested parser. |
| `EXIT` | `005003A8` | `004B4790` | `0x2000` | Missing player calls reporter but callback returns `1`. |
| `AREV` | `00500D20` | `004B4610` | `0x2004` | A failed revision callback is **not automatically** a fatal outcome on this flag set. |
| `FSM\0` | `00500D30` | `00409740` | `0x0001` | Callback returns `1` after import/finalize. |
| `EXIT` | `00500D40` | `004B4290` | `0x1000` | Callback compares its supplied value to the current tag. |

The descriptor **configuration is binary-verified**. It is **not** a specification that every absent, duplicate or out-of-order section must fail. The exact acceptance result of arbitrary reordered/missing tags depends on the sequential parser's mutable state and is not closed by corpus conformance.

## 5. Revision callback: return cases, not just a 'version check'

`004B4610` uses a table of required revision tags at `00500438` and an extension-to-revision table at `005003BC`. Observed branches:

- Recognized fixed revision tag (including `AREV`) with equal expected word at `chunk+8` => returns `1`.
- Recognized fixed tag with different revision word => calls reporter, returns `0`.
- `REV` tag with a recognized file extension and matching revision => returns `1`; wrong expected revision => reports and returns `0`.
- `REV` with an extension not found in the table => reports, **returns `1`** in this retail implementation.
- An unknown revision tag falls through to reporter, **returns `1`**.

The machine-defined expected values for the six nested mission section families are: **`WREV=9`, `TREV=4`, `RREV=1`, `OREV=3`, `LREV=1`, `AREV=1`**. The tested `.MSN` root `REV` is 2. These are *stock observed and table-backed*, not a universal version policy for arbitrary non-mission resource classes.

Because `REV` is configured with `0x2020` and `AREV` with `0x2004`, even the same callback return `0` need not cause identical parser-level behavior. This distinction is demonstrated by descriptor flags and callback branches; **exact final outcomes on altered files were not tested in the executable**.

## 6. FSM importer and fixup failures

`00409740` reads `chunk_size-8` into a local variable and supplies it to `00410720`, but `00410720` uses counted dword reads from its global stream cursor and does **not** locally check consumed bytes against that nominal size on each read. The seven imported groups are: command names (40-byte wire), actors (48-byte wire), media names (40-byte wire), named positions (40-byte name and variable float triples), initial nodes (168-byte serialized), global words, and tokens (8-byte `{kind,payload}`). Allocations use stream-derived counts, with arithmetic and pointer operations not backed by a comprehensive local count/overflow validator in the inspected code.

The FSM callback always returns `1` in the audited normal return path, and the finalizer (`004125C0`) is `void`; therefore importer success is **not** differentiated from partial semantic fixup completion by callback return. Legitimate **empty** FSM chunks (`chunk_size=8`) use a local seven-word zero buffer rather than reading seven counts past the chunk. The shipped corpus has 30 such chunks.

Semantic fixup behavior is similarly nonfatal at this layer:

- **Unknown/missing actor identity:** `00412400` stores `NULL` into actor `+0x58` and reports the lookup failure (no-op reporter); it continues with other actors. An actor initially null may later be unsafe depending on the executed host command, not because the loader reliably rejected it.
- **Duplicate actor key/label mismatch:** report path is diagnostic-only in the audited binder; no global abort on that condition.
- **Media availability:** `004122D0` checks WAV/SMK names and records status per media entry; the finalizer does not use a Boolean all-media-valid result to reject the FSM.
- **Unknown command name:** name-to-opcode mapping is performed per command record; source-level compiler constraints and arbitrary missing-name failure semantics remain deferred; a name's presence in the lookup does not imply its dispatcher case is implemented (`playScene`).
- **VM malformed instruction:** known 14-token interpreter switches; unknown token kinds have separate runtime handling, but no evidence that loader prevalidates the complete token stream against all branch, stack and host-argument bounds before game entry.

**No runtime crash, successful corruption exploit, or safe acceptance of malformed input has been established.** These are scoped observations about return values and local checks.

## 7. Shipped-corpus contract (strong positive, weak negative evidence)

An independent read-only Python inspector parsed **80** shipped mission files (40 `miss8`, 40 `miss16`) from the user's game archive; **zero structural errors**. In all 80: outer tags are `BWD2, REV, WDEF, TDEF, RDEF, ODEF, LDEF, ADEF, EXIT`; nested ADEF is `AREV, FSM, EXIT`, with the revision values listed above, and every recorded chunk lies within its declared parent. Per variant: 25 nonempty and 15 empty FSM chunks, **797** serialized VM nodes and **90,923** tokens. All nonempty command lexica match, and the `miss8/miss16` token hash matches in every mission pair (40/40, counting empty scripts).

The strict Python inspector rejects synthetic altered inputs in memory. Those probes test **our structural-inspection logic only**, not the game's permissive descriptor FSM, which can report errors without rejecting. `INSPECTOR_ONLY_MUTATION_PROBES.json` marks `retail_engine_executed=false` on every case.

**CRC caveat:** `004B35A0` computes a CRC for another resource/anti-tamper context, but its audited incoming calls do **not** place it on `004B42B0 -> 004B3DB0 -> 00409740`. Do **not** claim that the selected mission loader performs a CRC check merely because the executable contains a CRC routine.

## 8. What is closed and what is still unresolved

**Established (binary verified):** exact descriptor layout, selected mission call chain, EAX propagation through wrappers, descriptor masks and their observed branch tests, revision handler result branches, no-op reporter, mission wrapper's unconditional `1`, caller's disregarded return, FSM callback's `1`, empty-chunk special case, missing actor continuation, and CRC non-proven-in-path.

**Established (shipped corpus):** exact successful structural layouts and revision values for 80 `.MSN` files, seven counted FSM tables, zero parsing errors and 40/40 paired token identity.

**Partially specified:** precise treatment of every malformed/repeated/misordered tag sequence; persistence/reset of `0x80` seen flags across repeated mission load cycles; arithmetic-wrapping length behavior; how the resource cache exposes truncated contents; allocation-failure behavior; runtime effects of a semantically incomplete FSM. These cannot be promoted to tested accept/reject claims without safe, isolated original-engine instrumentation.

**Next gated research after this static milestone:** build a safe parser-only dynamic harness or instrument original executable without changing the user's installed game. Repeated-load and wrong-AREV cases should be prioritized; each test must separately record parser cursor, callback return, wrapper result, heap/fixup status and gameplay behavior. Do not collapse these channels into one Boolean outcome.

## 9. Source evidence and reproduction

- `evidence/v99_loader_native_decompiled.txt`: 17 successful Ghidra function decompilations.
- `evidence/v99_loader_full_instructions.tsv`: complete assembly for targeted functions including the primary parser.
- `evidence/v99_loader_call_references.tsv` and `v99_loader_incoming.tsv`: call and reference provenance.
- `evidence/v99_reset_and_caller_disasm.tsv`: top-level caller branch/return proof.
- `evidence/v99_revision_required_table_raw.tsv`: revision table bytes.
- `evidence/v99_selected_bwd2_descriptors.tsv`: descriptor fields.
- `evidence/CORPUS_LOADER_INVENTORY.tsv`, `CORPUS_STATIC_VALIDATION.json`: independent source-corpus verification.
- `evidence/INSPECTOR_ONLY_MUTATION_PROBES.json`: non-executing inspector validation.
- `scripts/*.java`: standalone Ghidra read-only extractors; `audit_loader_corpus.py`: structural corpus inspector. No game executable, mission assets, or third-party font files are redistributed.

**Confidence vocabulary:** **B** = binary control-flow/instruction evidence; **C** = original shipped-corpus observation; **I** = inferred dependency; **U** = unresolved or requiring runtime validation. A fact about a routine's branch cannot be silently upgraded into a claim about all real input files.
