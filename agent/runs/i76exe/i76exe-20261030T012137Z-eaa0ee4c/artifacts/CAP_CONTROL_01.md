# CAP-CONTROL-01 — selected initialization prerequisites

**Partial capability progress; selected gameplay/control delivery is not established.** The primary experiment executes original pending dispatcher `00461B80` with unchanged descriptors and original list insertion. It completes six initializers, including class31 and class34, then stops in class32 damage-child construction on an unbound `STRLKUP.DLL` data/function import. It does not reach class-1 initialization through the pending dispatcher. Independent direct controls complete original selected class-1 `00463120` and `00463950`, and separately validate the peripheral initialization and x87 prerequisites. Direct controls do not close the primary lifecycle gap.

Run `i76exe-20261030T012137Z-eaa0ee4c`; base `980037f49b348e14ccdde8ba2961174a8647f090`; protocol 1.0.4 / schema 1.2.0. Read merged [PR #58](https://github.com/jf-stargate/i76/pull/58), its M_ENG_01/service/reproduction artifacts, accepted M06 fixtures and accepted capability roadmap. Roadmap wording still describes #58 as candidate: live merged state, rather than that historical status snapshot, is used here. Run-only proposal; no canonical edits, promotion, reconstruction or merge.

## Primary lifecycle experiment

Original root construction `0045EBD0`, selected spawn-status instructions at `00451452`, VCF loading `004AD6F0`, class registration `00461970`, list allocation/insertion `0049C320` and world registration `004572B0` are inherited from accepted M-ENG-01. Heap/resource/OS/CRT and nonessential services remain explicit in the owned source. The harness supplies the staging context and selects the original selected spawn branch. It does not write control commands or peripheral ownership fields. Authentic M06 mission/terrain and stock bus resources retain accepted hashes.

At pending entry: 16 class nodes and 16 pending entries. `0054B208` holds pending nodes whose value points to a class node; that node's value identifies the owner. It is **not** a pending list of owner pointers. The verifier independently follows both original insertions. `00461B94` reads pending+8; `00461BA7` resolves the class node's owner; descriptor rows have stride `0x34`; `00461BFF` indirectly calls the init slot and returns at `00461C01`. Every observed target agrees with independently read PE descriptor bytes.

| Sequence | Original init target | Descriptor slot | Outcome |
|---|---|---|---|
| 1–4 | `0046D820` | `004F78F0` | Four tire initializers return |
| 5 | `0046F2B0` (class31) | `004F7A5C` | Returns; original animation state created |
| 6 | `0045F810` (class34) | `004F79F4` | Returns; original root/self ownership written |
| 7 | `0046DFE0` (class32) | `004F7A90` | Enters damage-child helper, stops on localization dependency |
| Later, unreached | `00463120` (class1) | `004F7784` | No dispatcher-mediated entry or return claimed |

Original unlink `0049C360` and HeapFree run after completed entries. Damage-child construction also registers additional objects/pending entries; this partial walk is not a drained queue. A separate selected process reproduces the full private trace byte-for-byte. An unselected pending control reaches the same localization stop, so it is not uniquely a selected-post failure.

## Independently validated next prerequisite

The original startup sequence at `00402B3C/00402B49` pushes `lang.txt` and calls `StrLookupCreate` through thunk `0040972C` / IAT `004BC2B0`. `00402B4E` loads the **address of exported data** through IAT `004BC2A8`; `00402B57` stores the returned object through that address. A loader must bind this data import to a cell, not treat its IAT value as the lookup object itself.

During pending initialization, original `0046EA2F` loads IAT `004BC2A8`; `0046EA39` dereferences it to obtain the lookup object. Original `0046EA34` supplies `.45 Handgun`. `0046EA3C` calls thunk `00409726`, which jumps through function IAT `004BC2B4` to `StrLookupFind`. In this GZF environment the unresolved addresses are `000C09F8` (data) and `000C09E8` (code): the data read is uninitialized, then execution stops at `000C09E8`. No localized string, global object or lookup result is manufactured.

Independent Python PE parsing verifies both EXE imports and the measured private retail DLL exports: `StrLookup_Global_Object` at `1000C030` (initial cell zero), `StrLookupCreate` at `10001000`, `StrLookupFind` at `10001AA0`. Fixed startup instruction bytes, source-name/key strings, runtime stop and imported data/function identities corroborate the dependency independently of Ghidra names/decompilation. This is the **next exposed prerequisite**, not proof that all later prerequisites have been enumerated. Next work must recover the authentic localization loader/constructor/resource path, then resume original pending dispatch. The real DLL/`lang.txt` semantics and later new pending nodes remain unexecuted here.

## Peripheral state: positive and negative controls

Direct peripheral controls locate the original class31/34 owners in the constructed native class list; they neither create owners nor write their runtime fields. Original descriptor init targets are invoked directly only in these labeled controls; the primary walk above independently reaches the same targets through its descriptors.

- Class31 owner `27003E00`, runtime `3600C190`: runtime+0 changes from null to original allocated animation `3600EBF0`; its four words are `0x24,9,9,9`. Original post `0046F420` consumes this pointer (including animation+0xC), reads root runtime+0xE0, and returns. It is not a resource-release operation despite an inherited provisional Ghidra name.
- Class34 owner `27003200`, runtime `3600C080`: original `0045F810` writes root `26000000` at runtime+0x78 and self at +0x7C, assigns runtime+8 animation `3600EF70`, and sets root runtime+0x434. Original `0045FAF0` returns with no additional uninitialized-memory warnings. The owner/root linkage explains the prior null-root reads; arbitrary radar bytes are unnecessary for this bounded branch.
- **Omit-init negative:** unchanged raw posts still return in Ghidra, but class31 reads address `0000000C` at `0046F43D` and class34 reads `00000070/00000108/0000006C/0000A9B4`. Return alone is not evidence of correct initialization. These warnings reproduce M-ENG-01's missing peripheral state.

All ordinary construction controls retain one inherited null-string read at `004461E0` (`ram:00000000:1`) during optional geometry-variant lookup. It is reported, not silently counted as clean full execution. Positive peripheral and direct class1 controls add no further uninitialized-memory reads. These results cover the exercised branch, not every radar/texture mode or all object bytes.

## Selected class-1 initialization and post control

A separate fresh emulator calls original `00463120(root)` directly. The entire callback returns: no inherited prefix-only stop at `00463189` remains. Runtime flags change from `00000040` to `00080040`; original seven command-list counts become `6,5,4,5,4,5,4`. Original reference increments, weapon classification/list construction, selected branch and cockpit/camera/HUD helper calls execute with the declared inherited services and authentic available resources. Optional material failures are recorded and their original false-return branch is allowed, rather than asserted to be success. This is not proof of complete visible cockpit preparation.

Then original `00463950(root)` returns. Its original status predicate at `00463960` is true (`eax=1`; selected status `00010810`). Original calls at `00463963` and `0046396C` reach `00459FA0` and `00445BA0`. The gauge path executes the original trig helper and its numerical boundaries described below; force-feedback device behavior is gated by original default state. No `+E4` throttle, `+104` command mode or `+AC` speed is injected. No pre/physics frame or measured control-induced vehicle-state change is claimed by this direct control; complete pending dispatch, original input producer/device path and selected full-frame scheduling remain open.

## Original FSINCOS and faithful bounded numerical execution

PE bytes `D9 FB` at `0049D409` are **FSINCOS**, not FCOS. A raw negative case fails on Ghidra's `fcos` P-code implementation at that exact original instruction. Java `Math.sin/cos` and whole-function replacement at `0049D400` are disabled in the published scenarios.

The bridge delegates the original instruction's exact 80-bit operand and control word to native x87 `fsincos`, returns 80-bit cosine/sine and status, and supplies Ghidra's normalized stack push (ST0=cosine, ST1=sine) with original surrounding instructions retained. It supports masked exceptions and finite `abs(x)<2^63`, rejecting unsupported inputs instead of extending a success claim. It carries C1/C2 used here; it does not claim a complete x87 environment, tag-word, sticky-exception, unmasked-trap, NaN or out-of-range model.

Ghidra's float stores do not faithfully honor directed rounding. Consequently original FSTP-single boundaries `0049D40B/0049D40E` are also delegated to x87 under the same control word; their original destination and pop behavior are retained explicitly by the bridge. Loads, helper prologue, result-register loads and return execute as original instructions. This is **original-instruction emulation with numerical instruction services**, not native execution of the whole executable.

Independent `x87_oracle.c` uses a separate inline assembly sequence `FLD-single; FSINCOS; FSTP-single; FSTP-single`, with no Java or bridge transport code. All 28 bitwise sine/cosine result pairs match: `+0,-0,+1,-1,float(pi/2),float(pi),100` across nearest/down/up/truncate control words `037F/077F/0B7F/0F7F`. This checks operand order, signed zero, directed store rounding and register returns for those cases. No universal transcendental accuracy or hardware-wide parity is claimed. Sampler FISTP, filter FCOS and CRT ftol services remain separately declared.

## Validation, reproduction and publication

See `VALIDATION_REPORT.md`, `REPRODUCE.md`, `SERVICE_LEDGER.md`, structured findings and safe evidence. Public evidence contains reviewed derived events, sparse opcodes, input/DLL hashes and a small numerical oracle table. Full traces, decompilation, licensed payloads and Ghidra projects remain private. Eight final processes use a freshly copied/imported GZF; expected failures are assertions, not swallowed successful runs. Scientific verifier passes 159/159 (156 regeneration checks plus three exact published-evidence comparisons); trusted base unit suite passes 38/38. At bootstrap the main ruleset was disabled; publication recheck found it active (updated 2026-10-30T01:25:54Z). This remains a proposal requiring human acceptance. Human review is required; no merge requested.
