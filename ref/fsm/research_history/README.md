# FSM/VOM historical investigation findings

These files preserve research conclusions as originally written at the end of
each pass (v72–v76). They are historical records; some contain **then-current**
statements that were superseded by later checkpoints. In particular, v76
reported that `00409980` was not a Ghidra-defined function. The October 19
20:54:59 PDT snapshot now confirms that it **is defined**, but still has the
Ghidra name `FUN_00409980`. Prefer the current canonical references:

- [FSM runtime reference](../i76_fsm_runtime_reference.md)
- [Vehicle Object Model reference](../../vehicle_object_model/i76_vehicle_object_runtime_reference.md)
- [October 2026 checkpoint](../../game/i76_research_checkpoint_20261019.md)

Focused per-pass TSV/C exports were used to write the original findings;
not all of those focus exports are part of the project's latest Ghidra
snapshot, whose decompile/disassembly scopes are deliberately selective.
