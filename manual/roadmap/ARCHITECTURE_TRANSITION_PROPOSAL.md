# I76 research/reconstruction architecture transition — proposal

**Proposal only, dated 2026-10-28.** Companion to [the pinned subsystem inventory](SUBSYSTEM_INVENTORY_20261028.md). The inventory is a read-only crosswalk; this page recommends how to evolve the repository without restricting reverse-engineering tools or rewriting historical evidence.

**Repository baseline:** \`026fd0daacb21b4da122163186a8ec2f4b49d894\` (also preserved at \`archive/pre-subsystem-architecture-20261028\`). This proposal does not merge itself, modify \`main\`, or change any accepted protocol or research run.

## Program / publication tracks

The binary target and the functional subsystem are **orthogonal**:

\`\`\`text
agent/runs/                         # Publication provenance, not an engine module tree
├── i76exe/                         # Existing — original retail engine
├── i76edit/                        # Existing — standalone level builder
├── i76shell/                       # PROPOSED — standalone frontend DLL
└── shared/                         # Existing — cross-target/tool/protocol research
\`\`\`

Within \`i76exe\`, use named functional owners ENG, RES, MLD, OBJ, FSM, VEH, AI, COM, TER, GEO, RND, AUD and NET. This is a planning/indexing scheme; **do not assert original source-file boundaries** based on these labels. \`i76edit\` and \`i76shell\` remain independent Ghidra targets with their own research histories and specific contract interactions with the engine. Avoid implicitly inheriting shell code into engine NET or editor code into engine TER.

The currently accepted \`agent/protocol/access.yaml\` protocol v1.0.3 supports only \`i76exe\`, \`i76edit\`, and \`shared\`. Until a separate governance PR is accepted, \`i76shell\` is a **logical target only, not a permitted run identity**.

## Research versus reconstruction: separate authority, not restricted techniques

**Research workstream:** investigate the original binaries and may freely author Ghidra harnesses, original-instruction emulators, stubs, synthetic service implementations, controlled replicas, analytical models, format decoders, comparison programs and differential tests. It must state what executed original instructions, what was substituted, what was independently modeled and what remains unverified. A script is not excluded from reversing merely because it contains independently implemented algorithms.

**Behavioral contract:** reconcile original instruction evidence, fixture observations, call/data ownership, known limitations and unresolved behavior through the existing \`agent/promotions/\` and \`manual/reference/\` human acceptance flow. A merged run is evidence; it is not automatic promotion of all its hypotheses.

**Reconstruction workstream:** independent engine/format implementations can be maintained in a separately reviewed source area when explicitly authorized; they consume stable behavioral contracts. They should not acquire false authority by copying a speculative model from a reversing harness. They declare fidelity per operation, not an oversimplified all-or-nothing subsystem completion label.

**Shared validation:** accepts original, reconstructed and stubbed implementations behind bounded scenario adapters. Compare exact bytes where necessary, state/event chronology, numeric tolerances, structural invariants and eventually geometry/pixels. Every test retains baseline hashes, original services executed or intercepted, fixture provenance and the intended evidentiary scope. Ghidra-original emulation is useful reference evidence but not automatically an exact live Windows oracle.

In short: **tool creation stays unrestricted within research; durable code ownership and fidelity claims are reviewed independently**.

## Candidate source organization, not yet created

\`\`\`text
i76/
├── agent/
│   ├── runs/{i76exe,i76edit,i76shell,shared}/  # shell pending protocol
│   ├── promotions/
│   └── protocol/
├── manual/
│   ├── reference/engine/
│   └── roadmap/
├── reconstruction/                # FUTURE: independent implementations
│   ├── resource/
│   ├── mission/
│   ├── object/
│   ├── vehicle/
│   ├── terrain/
│   └── rendering/
├── validation/                    # FUTURE: reusable cross-implementation tooling
│   ├── contracts/
│   ├── original/
│   ├── replica/
│   ├── scenarios/
│   └── differential/
├── ref/                           # Existing immutable historical reference
├── scripts/                       # Existing historical tooling
└── snapshot/                      # Existing immutable annotated Ghidra snapshots
\`\`\`

Do not move or flatten run-owned scripts and snapshots to make this tree look complete. Promote reusable harness components separately with reproducibility checks, while historical experiments retain original paths. No new source layout is a condition for the next reverse-engineering experiment.

## Specific changes required to activate \`i76shell\`

Plan a **separate governance PR**, fresh-based and explicitly human-approved, for a publication protocol update (suggest next protocol patch version only after testing). Do not silently edit the active protocol in a research run. At minimum inspect and synchronize:

| Current path | Required change |
| --- | --- |
| [\`agent/protocol/access.yaml\`](../../agent/protocol/access.yaml) | Add \`i76shell\` to allowed track names and run-ID regex; state independent source-binary/Ghidra provenance expectations |
| [\`AGENTS.md\`](../../AGENTS.md) | Discover/classify \`i76shell\` with other binary targets |
| [\`agent/protocol/BOOTSTRAP.md\`](../../agent/protocol/BOOTSTRAP.md) | Onboarding, identity and private-baseline instructions |
| [\`agent/protocol/VERSION\`](../../agent/protocol/VERSION) and [\`SCHEMA_VERSIONS.json\`](../../agent/protocol/SCHEMA_VERSIONS.json) | Coordinated protocol version metadata |
| [\`agent/protocol/schemas/run.schema.json\`](../../agent/protocol/schemas/run.schema.json), [\`v1.1.0/run.schema.json\`](../../agent/protocol/schemas/v1.1.0/run.schema.json) | Track enum and run-ID patterns; require binary and Ghidra baseline provenance for shell just as for game/editor in current v1.1.0 conditionals |
| [\`agent/protocol/tools/validate_protocol.py\`](../../agent/protocol/tools/validate_protocol.py) and [\`.github/scripts/pr_integrity.py\`](../../.github/scripts/pr_integrity.py) | Update duplicated run-ID regex and relevant policy assertions; keep trusted-base validation |
| [\`agent/protocol/tools/test_protocol.py\`](../../agent/protocol/tools/test_protocol.py) and [\`.github/tests/\`](../../.github/tests/) | Positive shell-track case, negative bogus-track/cross-track case, and proof old merged records remain valid |
| [\`agent/protocol/RESEARCH_PROVENANCE.md\`](../../agent/protocol/RESEARCH_PROVENANCE.md) and surrounding docs | Document shell binary identity, Ghidra baseline and prohibited licensed payload treatment |

**Source warning:** shell Ghidra snapshots under \`snapshot/i76shell.dll/\` and shell research under \`ref/game/\` and \`scripts/local_history/\` predate publication tracks. Preserve them as historical sources; do not invent \`agent/runs/i76shell/\` manifests for them.

## Low-risk transition sequence

1. **Inventory first (this draft PR):** review subsystem ownership, 33 accepted run mappings, old script/reference roots and known gaps against pinned main. No governance, tests or existing evidence changed.
2. **Shell publication identity:** if approved, propose the separate synchronized policy/schema/CI change adding \`i76shell\`, with explicit maintainer approval. Do not create shell runs before it is accepted.
3. **Subsystem working index:** reference original functions/structures, active experimental harnesses, prior run evidence, open questions and candidate contracts. Begin with the active ENG/VEH/TER integration cluster, without forcing all work into it.
4. **Reusable validation extraction:** identify duplicated harness framework elements and promote only where reproducibility and ownership justify it; do not rewrite existing run scripts.
5. **Reconstruction authorization:** when desired, propose source structure and component contracts with explicit tests. This is independent of the right to write validation code during reversing.
6. **Milestones next:** only after the subsystem mapping is accepted, define per-subsystem original-behavior, original-execution, contract and independent-implementation milestones.

## Codex CLI continuation handoff

Use a new bounded CLI task with the accepted \`main\` SHA and the two inventory proposals as context. Ask it to **audit and challenge** ownership mappings against actual original callgraphs/observations, not to treat the draft documents as newly promoted facts. It may create any analytical or validation tool needed. Keep unaccepted hypotheses labeled, place substantive new reversing evidence in an owned append-only run, and propose shared-tool or canonical updates through separately reviewed PRs.

An audit should particularly test (a) ENG scheduling boundaries with VEH/TER, (b) original loader/OBJ/FSM ownership, (c) camera and scene producer versus raster submission, and (d) whether older scripts really remain useful/reproducible. It should not begin an all-engine implementation as a side effect of architecture mapping.

## Acceptance boundary

This proposal is non-normative. It does not grant agents autonomous merge authority, authorize retroactive modification of merged runs, insert original licensed assets into the public repository, or modify the current research publication governance. Any later governance, curated contract or shared-code proposal requires its own reviewed acceptance under the current trusted \`main\` rules.