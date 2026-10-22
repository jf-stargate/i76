# Baseline identity registry

This directory is a registry of **metadata**, not executable binaries, Ghidra GZF databases or full decompilation dumps. The actual annotated Ghidra baseline must be kept in private storage and identified by a verified SHA-256 digest and unambiguous program name.

For each track record: original file name, verified retail MD5/SHA-256, Ghidra version, program identity, annotated snapshot hash, local/retrieval reference, when it was measured, and any uncertain matches. The engine and editor are separate executable identities and must never share a presumed annotation baseline.

A new agent must discover existing `ref/` and `snapshot/` records before claiming that a baseline is available. **No verified SHA-256 inventory or accessible private Ghidra snapshot is included in this first directory scaffold.** Do not fabricate one to satisfy a schema.

Use `agent/protocol/RESEARCH_PROVENANCE.md` for run references. Adding a canonical baseline requires an explicit reviewed promotion and validation, not simply passing JSON schema tests.
