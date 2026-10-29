# Original `i76.exe` subsystem discovery indexes

**Status:** advisory navigation and investigation planning, not a new original-source partition, finding promotion, or publication requirement. Start from [root agent onboarding](../../../AGENTS.md), pin current `main`, and follow [bootstrap](../../../agent/protocol/BOOTSTRAP.md) and [documentation governance](../DOCUMENTATION_WORKFLOW.md) before relying on these pages. The [architecture inventory](../SUBSYSTEM_INVENTORY_20261028.md) describes all thirteen proposed functional owners; this pilot covers the closely interacting engine/vehicle/terrain cluster.

| Index | Functional scope | First investigation entry point |
| --- | --- | --- |
| [ENG — lifecycle and frame scheduling](ENG.md) | Clock/math initialization, frame phases, class callbacks, lifecycle | WinMain static order and original frame/subdivision probe |
| [VEH — construction and dynamics](VEH.md) | Class-1 runtime, VCF construction, pose integration, tires and suspension | Promoted construction reference and authentic-terrain replay |
| [TER — physical environment](TER.md) | TDEF/ZMAP/ZONE, TER pages, height/material/normal, road/surface interfaces | M06 original loader/sampler and editor cross-track survey |

These are **functional research ownership labels**, not recovered C translation units, exclusive write rights, or independent binary publication tracks. An original function, run, or script may legitimately be linked from several indexes. The editor (`i76edit.exe`) is a separate binary whose authoring/format observations can inform TER; editor internals remain editor-owned. The shell is also a distinct target, subject to whatever publication tracks the *currently accepted* protocol permits.

## Reading evidence and status

1. **Promoted technical reference**: a separately reviewed and merged [promotion decision](../../../agent/promotions/README.md) and its [curated reference](../../reference/README.md), limited to its explicitly selected claims. At this pilot's pinned base, [vehicle construction](../../reference/engine/vehicle_construction.md) is the relevant promoted contract.
2. **Accepted research evidence**: a merged immutable `agent/runs/<track>/<run-id>/` containing [manifest, findings, validation and artifacts](../../../agent/protocol/README.md). It records what a particular investigation observed; `findings.json` status `proven` is **not** a promotion decision.
3. **Historical checkpoint**: `ref/`, `scripts/`, `snapshot/` and linked reports. Useful and sometimes independently validated, but not silently promoted or updated by this index.
4. **Binary-static**: identified retail opcodes, data tables, call sites or control flow; does not establish reachability through a complete running game.
5. **Original-instruction, substituted services**: retail instructions run under Ghidra and/or localized hardware arithmetic services; declared OS, CRT, resource, clock, math, renderer or other dependencies are supplied/overridden. Not equivalent to an unmodified Windows executable.
6. **Independent analytical model**: separate parser, numerical interpolation, exporter or verifier; agreement corroborates a specific operation and fixture, not the entire retail callgraph.
7. **Inferred / unresolved**: proposed semantic naming, source ownership, behavior outside a measured path, or a specifically open test. Neither a passing validator nor a successful PR merge resolves these automatically.

## Cold-start workflow

Read the pinned `main` [AGENTS.md](../../../AGENTS.md) and [bootstrap](../../../agent/protocol/BOOTSTRAP.md) first; check live PRs and applicable protocol. Select the `i76exe` track and an advisory subsystem index. Follow its *promoted reference → merged runs' reports and validation → source scripts/REPRODUCE → evidence/manifest* links, checking hashes and input provenance. Read the named adjacent indexes and separate binary-track references. Distinguish an experiment's manually invoked callbacks from a real WinMain frame. Finally propose one bounded question and the exact original entry points, fixtures, substitutions, expected evidence and failure criteria. Do not take the recommendations in these files as permission to mutate historic runs or begin reconstruction.

## Reusable index template (for later owners)

- **Identity/boundary:** functional ID, primary binary track, adjacent owner/track interfaces, explicit exclusions.
- **Original anchors:** a *small* address/structure/callchain table, exact evidence links, binary-static versus emulated scope, disputed labels.
- **Evidence ladder:** promoted references (if any); accepted run manifest/findings/artifacts; historical `ref/` and cross-binary sources; unresolved contradictions.
- **Harness catalog:** owned script and reproduction/validation links; original code executed versus independent models/services supplied; private licensed inputs and toolchain; observed pass status versus unexecuted here.
- **Current state:** binary-static; original-instruction execution with substitutes; analytical comparisons; inference; specifically untested behavior.
- **Dependencies and bounded next investigations:** inter-index links, target addresses, reusable harness, required private prerequisites, expected proof artifacts and limiting assumptions.

Keep indexes short relative to the underlying evidence; never move, rewrite, rehash, rename or retroactively relabel accepted runs. Research code is allowed to contain emulators and provisional independent implementations without becoming a maintained reconstruction. Canonical claims still require immutable evidence → reviewed promotion → curated reference, as described by the [documentation workflow](../DOCUMENTATION_WORKFLOW.md).

**Pilot provenance:** prepared against accepted `main` `524a25d67228b9960566432b397f9c2ef51ea613` (publication protocol `1.0.3`). This provenance is not a substitute for checking a newer `main` before the next investigation or accepting the PR.
