# Documentation impact — RES original acquisition semantics

## Research identity

Run `i76exe-20261101T161535Z-22d9956f`, track `i76exe`, subsystem RES; original base `8b16e9f81159c9f0f4dea63e16d69d79355b6d49`. PR pending publication. Retail executable and private v97 GZF identities are measured in `manifest.json`; no database/assets are published.

## Documentation disposition

**Candidate update; no canonical change in this run.** Proposed future target: `manual/reference/engine/resource_acquisition.md` (new), with a scoped link/narrowing in `vehicle_construction.md` if accepted. Historical sources: `ref/game/i76_resource_acquisition_reference.md` acquisition-flow/name-policy sections; `ref/zfs/i76_zfs_structure_and_extraction_reference.md` indexing role; material reference's extraction preferences. Retain `ref/` unchanged.

A separate designated-steward reconciliation should compare this run with the promoted vehicle construction evidence, accepted lazy-texture evidence and historical v54/v56/v64B Ghidra annotations. The v97 source resolver name already recognizes source selection; this run independently ties that interpretation to original return arithmetic and explicitly separates key rows from source rows.

## Evidence-linked candidate findings

Every ID below exists in `findings.json`. All evidence is **binary-static**, with high confidence for the exact instructions/offsets. The full semantic descriptions and qualifications are in `SEMANTIC_RECONSTRUCTION.md` and `RESOURCE_CONTROL_FLOW.md`. `SYMBOL_DECISIONS.tsv` maps each proposal to its strongest original address; `STATIC_AFTER.tsv` supplies function-range PE hashes and call/xref anchors. Those artifacts' exact SHA-256 values and byte lengths are listed in the manifest; `ACCEPTED_SOURCES.tsv` authenticates contrary/historical references at the pinned base.

| Finding | Proposed statement / impact | Original evidence / disposition |
|---|---|---|
| RES.C1 | Acquisition returns shared bytes, not one uniform record handle | `0047011C`, `00470BB2`, callers `004B420A/00446A3E`; correct/narrow API wording |
| RES.C2 | Conditional indexed-first or loaded-file-first priority | `0047000F..00470050`; add both branches, defer actual mission policy value |
| RES.C3 | Key is a zero-padded 16-byte representation at normal entry; table comparison is four word differences | `0046FFCF`, `00470CA0`; add exact normalization and termination limitations |
| RES.C4 | Loaded-file header, retention and inline payload layout | `00470070`, release `0046FE30`; add bounded storage contract, defer full invalidation safety |
| RES.C5 | Historical “used bytes” counts records | `0047029B..004702A7`, `0046FCBF`; correct semantics in future reference; no common symbol migration here |
| RES.C6 | PIX rows and PAK aggregate retention are distinct structures | `00470660`, `00470B20`, `00470BC0`; add member/owner pointer distinction |
| RES.C7 | Registered keys contain source masks; resolver returns a static mounted-source row | `004B2E00`, `004B2B30`; narrow historical “registered record lookup” wording |
| RES.C8 | Selected-source load chooses loose/ZFS by formatted-path substring, supports optional caller buffer | `004B3030`; add dispatch/ownership qualifications; decoder behavior remains outside scope |
| RES.C9 | Existence helper tests membership, not loadability or core cache residency | `00470340`, `00470C70`, `004B34F0`; correct broad historical helper description |
| RES.C10 | Size/release are indexed-first independently of acquisition policy | `0046FEE0`, `0046FD40`, `00470BC0`; add asymmetry and caller contract, defer collision runtime consequences |

## Reconciliation and remaining questions

The promoted vehicle reference already distinguishes original GEO/TMT consumers from substituted file services. This run **confirms that limit** by inspecting `I76_IntegratedVcfResourceProbe.java:58..60`: acquire, size and release are intercepted. Retain the vehicle results, but never cite authentic supplied payloads as original RES execution. Existing GEO, owner-slot/TMT and VQM caches remain separate layers.

Do not promote a claim that directory files always beat PIX, that registered lookup returns a key-table row, that `00470340` checks disk readability, or that historical Python exporter policy is retail lookup policy. Runtime selection values, collision invariants, exact media callback contract, malformed key/PIX behavior, unknown header bytes and complete teardown require the discriminating evidence listed in `UNRESOLVED_SEMANTICS.md`.

## Publication boundary

This handoff edits no `ref/`, `manual/reference/`, common migrations or `agent/promotions/`. Opening or merging a research PR does not certify the proposed semantics. Only a separate, fresh-base steward PR and explicit human acceptance can promote claims.
