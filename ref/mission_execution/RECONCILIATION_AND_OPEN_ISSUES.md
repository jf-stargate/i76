# v0.4.0 loader reconciliation and outstanding issues

This document supersedes the v0.3.0 `RECONCILIATION_AND_OPEN_ISSUES.md` *for descriptor persistence*; other v0.3.0 findings remain authoritative in their respective sections. Host-command invocation contracts from v0.2.0 remain unchanged.

| ID | Status | Finding / qualification | Evidence |
|---|---|---|---|
| L-01 | Closed, B/high | Selected-mission wrapper `004B42B0` returns 1 independently of the nested parser's null return. | v99 assembly `004B4534` |
| L-02 | Closed, B/high | Top-level gameplay caller ignores selected-mission wrapper return. | v99 game callsite `004034F4` |
| L-03 | Closed, B/high | ADEF wrapper preserves nested parser result in EAX despite a misleading void signature. | `004B45F0`, `004B89B0` |
| L-04 | Closed, B/high | Retail reporter `0042D5D0` is a one-byte RET; missing-player callback reports but returns 1. | v99 decomp and assembly |
| L-05 | Closed, B/high | Revision handler has distinct success, failure and unknown-tag paths. | v99 `004B4610` |
| L-06 | Closed, B/high | Parser marks matched descriptors `0x80` at `004B3F31` and required-scan tests `0x40/0x80` at `004B4160–004B416B`. | v99 assembly |
| L-07 | Closed, B/high | FSM importer does not locally validate every streamed count against its chunk byte length; callback returns 1 on audited path. | v99 loader code |
| L-08 | Closed, C/high | All 80 shipped mission resources satisfy the independent structural inspector. | v99 corpus inventory |
| L-09 | Open, B+U | Exact generic parser acceptance for all malformed/repeated/reordered tags needs path-level verification. | v99 parser; deferred parser-only instrumentation |
| L-10a | **Closed within parser, B/high** | `seen` is written into the static descriptor array and **not cleared within** `004B3DB0`. The inherited `004B84E0` “reset” helper does not clear it either. | v100 static references, v99 `004B3F2C–31`, v100 re-decomp |
| L-10b | **Closed within direct caller graph, B/high** | Three distinct loader functions share root table `00500328`, enabling cross-resource history. | v100 five static descriptor references and three parser callsite traces |
| L-10c | Open, U | Whether any unexamined indirect reinitialization occurs between two actual mission loads. | Need debugger watchpoint/runtime trace; no whole-program negative proof |
| L-10d | **Conditionally inferred, I** | Root BWD2 omission can fail the required check cold but cease failing **that check** after a prior matching BWD2 parse; other checks remain. | Verified flags and required/match bit code; logic-only tests |
| L-11 | Open, U | Actual retail behavior for truncated sections, wrapping sizes, absurd counts and allocator failure. | No original-engine malformed execution |
| L-12 | Open, U | State available to gameplay after partial ODEF, actor or media fixups. | Requires safe real-run instrumentation |
| L-13 | Closed within selected chain, B | CRC routine `004B35A0` has no proven role in selected-mission BWD2 parse. | v99 callgraph |
| L-14 | Open, U | Resource-cache truncation and decompression boundary guarantees. | Provider inspection outstanding |
| L-15 | **Terminology correction, B** | Ghidra label `reset_mission_resource_parse_callbacks` (`004B84E0`) suggests an unsupported descriptor reset; the body registers an object callback. | v100 native body, v99 earlier native |
| L-16 | Open, U | Whether command/resource flags outside these 12 descriptor records have stronger state-reset dependencies. | Additional parser table inventory or dynamic watchpoints |

**New v0.4.0 evidence precedence:** `DESCRIPTOR_STATE_AND_REPEATED_LOAD_CONTRACT.md` explains exact persistent-state behavior; `LOADER_VALIDATION_AND_FAILURE_CONTRACT.md` remains authoritative for the rest of the nested BWD2/FSM failure-state policy. Nothing here claims that a malformed retail mission has been run or accepted.
