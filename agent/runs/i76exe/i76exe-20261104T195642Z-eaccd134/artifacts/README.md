# PIX/PAK index and resource-reader research

Read `PIX_PAK_FORMAT.md` for the verified text contract and absolute decoded-PAK
offsets; `PIX_PAK_CONTROL_FLOW.md` for original parsing/failure instructions;
`PIX_PAK_CORPUS.md` for authenticated coverage and reviewed metadata;
`RESOURCE_PRECEDENCE.md` and `RESOURCE_LIFETIME.md` for lookup and ownership;
`RECONSTRUCTION_HANDOFF.md` for staged future provider integration.

`REPRODUCE.md` gives commands. The reader and its synthetic tests are in
`../scripts/`. `format_contract.json`, `entry.schema.json` and
`runtime_records.json` are machine-readable contracts. `instructions.json`
contains reviewed assembly and original function-body identities; `corpus.json`
and `examples.json` contain bounded public metadata, aggregate hashes and checks.
`reproduction.json` records a fresh read-only import and unchanged private input
hashes. `DOCUMENTATION_IMPACT.md` is the required separate-promotion handoff.

This run is static instruction/corpus research plus independent reader execution.
It does not claim original runtime collision tests or exact CRT duplicate winners.
No original resource payloads, full inventories or Ghidra databases are published.
