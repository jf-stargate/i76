# Ghidra Project State Snapshot

This folder is a durable human-readable and machine-readable export of the current Ghidra program state.
It is intended for source control, code review, handoff, and offline reference without requiring Ghidra to be open.

## Program

| Field | Value |
|---|---|
| Program | `i76.exe` |
| Language | `x86:LE:32:default` |
| Compiler spec | `windows` |
| Image base | `00400000` |
| Min address | `00400000` |
| Max address | `ffdfffff` |
| Export time | `Mon Oct 19 20:54:59 PDT 2026` |

## Contents

| File | Purpose |
|---|---|
| `manifest.json` | Machine-readable summary of this snapshot. |
| `function_index.md` / `.tsv` | Function list, signatures, address ranges, comments, semantic-name status. |
| `symbols.md` / `.tsv` | Symbols and labels, including source type and primary status. |
| `comments.md` / `.tsv` | Plate, pre, EOL, post, and repeatable comments. |
| `memory_blocks.tsv` | Program memory block map. |
| `defined_data.tsv` | Defined data listing with type, size, symbol, and value preview. |
| `defined_strings.md` / `.tsv` | All defined string data with category and referencing functions. |
| `function_module_guesses.tsv` | Heuristic semantic module/source-file group guess per function. |
| `data_types_structures.md` / `.tsv` | Structure definitions and field offsets. |
| `callgraph.tsv` | Function call edges discovered from instruction references. |
| `class_descriptor_slots.tsv` | Original class interface callbacks, 13 slots per class, function boundary resolution. |
| `candidate_function_status.tsv` | Status and bytes for all 29 known missing-function candidates. |
| `candidate_incoming_references.tsv` | Incoming code/data references to the candidate addresses. |
| `focused_export_scope.tsv` | Exactly which function bodies were selected for decompilation/disassembly. |
| `references_from_instructions.tsv` | Instruction-level outgoing references. |
| `rename_inventory.tsv` | Semantic/default-name inventory for functions and symbols. |
| `decompile/` | Decompiled C for exported functions. |
| `disassembly/` | Instruction TSV per exported function. |

## Snapshot scale

| Metric | Count |
|---|---:|
| Functions | 2097 |
| Semantic functions | 2093 |
| Known candidate functions now defined | 29 |
| Known candidate functions still missing | 0 |
| Class table signature verified | true |
| Decompiled function cap | 2500 |
| Disassembly function cap | 2500 |
| Defined strings | 4020 |
