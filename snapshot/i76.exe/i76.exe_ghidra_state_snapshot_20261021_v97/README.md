# Retail `i76.exe` — annotated Ghidra v97 snapshot (2026-10-21)

**Retail PE MD5:** `a640ea0097dbb62e0c77b7f2847c7161`  
**Ghidra:** 12.1.4; annotated baseline `i76_mission_v97_verified_names`.

Generated **read-only** from the cumulative v97 GZF. This new snapshot supplements rather than overwrites the complete historical `20261019_205431` snapshot. The latter has its own independent provenance.

## Contents

The regenerated `function_index.tsv`, `symbols.tsv`, `comments.tsv`, `callgraph.tsv`, `references_from_instructions.tsv`, `defined_data.tsv`, `defined_strings.tsv`, `data_types_structures.tsv`, `rename_inventory.tsv` and companion Markdown files are **whole-program inventories**. They reflect the current v97 program state. `v97_function_delta_from_20261019.tsv` isolates the function boundary/name changes from the previous snapshot.

`decompile/` and `disassembly/` contain **55 deliberately selected, updated mission-related functions**, each with an entry in the corresponding index. These bodies include the FSM VM/scheduler/host dispatcher, resource parsers, instance-key registry, world-object lifecycle and CB audio handlers. They are **not a complete disassembly of the executable**. The previous snapshot contains additional focused bodies; the GZF remains the authoritative complete current project database.

There are **2100 function entries** in this snapshot and **36 observed function entry/name/body-range deltas** relative to the earlier snapshot. These deltas do not imply that every changed item has a new source-code function; Ghidra symbols are annotations.

## Reproduce

In Ghidra 12.1.4 import the separately retained `i76_mission_v97_verified_names.gzf`, then run `scripts/ghidra_history/i76_v101_export_repo_state.java` and `scripts/ghidra_history/i76_v101_export_focused_bodies.java` as read-only headless scripts. The bulk exporter may take substantial time; the focused-body exporter is batched and its argument order is `output_directory start_index count [1-for-decompile]`. Supply the bulk exporter output directory as its first `-postScript` argument. The focused-body exporter is then run in batches against that new snapshot directory.

See [`ref/mission_execution/README.md`](../../../ref/mission_execution/README.md) for the current mission architecture contract and emulation qualifications.
