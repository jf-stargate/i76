# Deferred validation — descriptor state across resource and mission loads

This is a **test specification, not an execution report**. No original retail executable was run with malformed inputs. Run only in a disposable, offline VM/sandbox with an independently copied resource tree and reversible checkpoints. Prefer debugger observation of unmodified retail instructions; never test against the installed game or the user's saved games.

## Instrumentation

Capture these separately, without collapsing them into a single success/failure value:

1. The two root descriptor flags at `00500328+0x0C` and `00500338+0x0C`; seven world flags at `00500348+i*16+0x0C`; ADEF flags at `00500D20+i*16+0x0C`.
2. Entry/exit for `004B3DB0` (descriptor pointer, count, source cursor, end cursor, parse mode, return cursor).
3. Exact write at `004B3F31` and required-check branch at `004B4160–004B419F`.
4. Caller path (`004B41E0`, `004B42B0` or `004B4A80`), callback return values, outer selected-mission wrapper result, and top-level gameplay continuation.
5. Resource-cache lifetime, world object load effects, FSM-heap initialization and any exceptions/crashes.

## Test cases

| ID | Setup | Manipulation | Required observation | Risk control |
|---|---|---|---|---|
| S-01 | Fresh process, valid stock mission | None | Initial flags; `BWD2` seen after match; normal completion | Stock-only control |
| S-02 | Same process after S-01 | Load a second *unaltered* mission | Whether root/world/ADEF descriptor flags were cleared between calls | Stock-only control |
| S-03 | Fresh process, generic resource before mission | Observe a successful generic `004B41E0` root parse | Does generic load prewarm `00500334`? | Observation only |
| S-04 | Fresh-process isolated parser | BWD2 tag missing, REV valid | Which branch rejects and what cursor is returned | Stop before callbacks that allocate world or FSM |
| S-05 | Same isolated process after valid BWD2 parse | Repeat S-04 | Whether required-flag rejection differs while other conditions match | Stop before world mutations |
| S-06 | Warmed descriptor table | Wrong REV revision | Does `0x20` callback-failure rule reject independently of warmed seen? | Strict bounded fixture |
| S-07 | Warmed and cold comparisons | Duplicate/out-of-order chunks | Capture exact state transitions, no claims from Python structural inspector | Parser-only |
| S-08 | Valid stock mission after failed parse | Retry valid resource | Whether failure leaves descriptor bits or other state contaminated | Full reset between trials |

The original code's allocation and file-length checks are incomplete; do not execute truncated or absurd-length payloads inside the full game process. First build a read-only/emulated control-flow trace or a guarded parser-only harness that cannot reach gameplay. Approval of a behavioral test campaign is distinct from this static research milestone.

## Classification required in reports

- **B**: x86 control-flow proof, exact branch or field write.
- **C**: original stock mission observation.
- **I**: conditional prediction from the static code or micro-model.
- **D**: independently captured dynamic runtime trace.
- **U**: genuinely unresolved.

A passing v0.4 `descriptor_required_seen_model.py` case is **I**, not **D**.
