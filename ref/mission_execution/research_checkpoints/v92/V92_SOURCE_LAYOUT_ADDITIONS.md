# v92 provisional source-layout evidence (speculative)

These are hypotheses about late-1990s Visual C++ object-file layout, not verified original source filenames. All function and data addresses below are verified from the retail executable.

| Region | Candidate translation-unit affinity | Strength | Evidence and caveats |
|---|---|---|---|
| 0041F8E0–0041FCE0 | `vehicle_control_queue` / per-vehicle buffered-command support | Strong | Consecutive dequeue, enqueue, history-derived enqueue, apply, and drained-query implementations; shared AI ring fields A6C8/A6CC/A6D0 and buffer at 9D68; source-file boundary beyond region not established |
| 0049C7F0–0049CBAC | runtime clock / frame timing | Strong | initializer, elapsed-clock updater, GetTickCount calls, multiple tightly coupled globals at 005A7E10+; function code neighbors are coherent |
| 00402610–00402620 | game-flow state accessor pair | Moderate | Neighboring six-byte getter and ten-byte setter share `g_game_flow_state`; adjacency alone not sufficient to place other 00402xxx routines into same file |
| 00412CE0–004149F0 | mission token VM/command dispatcher | Strong subsystem affinity, weaker per-file boundary | Handler switch dispatch, token VM, and pending-node scheduler are contiguous, but separate translation units or link order could create similar layout |
| 00463800–00463950 | vehicle class lifecycle callbacks | Moderate | Physical-frame callback and nearby post-update callback; precise boundary inferred, not proved |

**Header inference:** shared declarations would need a world-object pointer, AI runtime state, control sample structure, FSM command opcode/prototypes, clock/game-state accessors and state/result globals. No evidence supports original header filenames or ownership of their declarations.
