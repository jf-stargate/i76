# Documentation impact — original TU discovery, independent pilot 2

Run `i76exe-20261103T183247Z-f97a49da`, track `i76exe`, original base `deaef41589671984c7e65010b2ecde351ad9ddf4`. Exact retail/v100 identities appear in `manifest.json` and PROVENANCE. PR pending at preparation; no promotion requested.

Disposition: **no canonical change**. The nine inferred TU fragments are navigation hypotheses, not behavioral specifications or authenticated original files. Potential future navigation targets are `manual/reference/engine/terrain_sampling.md`, `mission_vm.md`, `resource_acquisition.md` and the TER/RES subsystem indexes. Historical resource/mission/terrain references remain unchanged. No subsystem milestone is closed.

- `tu2.provenance`: no usable source-file records found in the inspected PE/history scope. Evidence: `evidence/pe_provenance.json`, original PE headers and PROVENANCE; binary-static HIGH within the explicit search limits. This does not prove private source/debug artifacts never existed.
- `tu2.fragments`: nine candidate fragments cover 41/42 bounded functions. Evidence: `membership.tsv`, `state_ownership.tsv`, `instruction_evidence.tsv`, candidate report. Inferred MODERATE at best; defer canonical source-module claims. The sole unknown is the 00493150 forwarding thunk.
- `tu2.boundaries`: separation is weaker than within-fragment coupling; B01/B10 are the strongest tested cuts and B05 the weakest proposed cut. Evidence: boundary report and `boundaries.tsv`. Inferred, no HIGH cut; compiler/linker and one-file alternatives remain.
- `tu2.method`: deterministic static facts do not calibrate source ownership. Evidence: method report, 100-check factual validation, fresh reproduction and P01–P06/B01/B06/B09/B10/N01–N06. No source ground truth or runtime tests.

The functional references and this run are compatible: semantic ownership was never original TU identity. This run specifically resists splitting the terrain map fragment purely into physical sampling versus visible-terrain modules, and it retains a one-mission-TU alternative. Current annotation at 004702D0 is semantically misleading, already noted by accepted resource research; this run changes no annotations.

The maintainer may compare this evidence with the independently produced pilot after review. This investigator did not inspect PR #111 beyond publication metadata and did not compare after analysis. Additional source/object provenance, indirect-access recovery and controlled same-toolchain benchmarks would most improve reliability. A whole-executable authoritative partition is not justified by this pilot.

This handoff proposes no changes to `ref/`, `agent/promotions/`, canonical documentation, baseline data or shared tools. A designated steward may reconcile merged evidence in a separate fresh-base proposal; only the human maintainer can accept it.
