# Legacy research archive and provenance

A first-pass inventory of existing Git-tracked research and analysis scripts is recorded in [legacy_inventory.json](legacy_inventory.json), pinned to commit `8885274be05f6570f8f12272fd86bd5cad16d5a7`. It lists each existing `ref/` and `scripts/` file by Git blob SHA and size, while recording snapshot tree identities without duplicating the 15,500 snapshot entries.

The inventory is **not** a set of research runs. It does not imply that historical conversations had manifests, machine-verified validation, identical baselines, or publication approvals. Do not manufacture run IDs for them.

Legacy human references remain at `ref/`; legacy tools remain at `scripts/`; former Ghidra-related snapshots remain at `snapshot/`. All stay accessible during incremental migration. Future evidence imports must identify actual source archives and checksums and explain what remains provisional.

The editor v01–v20 full-text reports are **not** present under `ref/editor/research_history/` on this Git commit (only the history index is present). Do not claim they are archived in Git until their original text has been independently recovered and committed with its hashes.
