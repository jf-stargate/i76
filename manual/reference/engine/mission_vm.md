# Retail mission VM and cooperative scheduler

**Status:** Proposed binary-static reference; see [promotion decision](../../../agent/promotions/semantic_ter_fsm_res_20261102.md). Original `i76.exe` SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`. This is a semantic model, not original developer source or a tested replacement VM.

Primary evidence: [Pilot B](../../../agent/runs/i76exe/i76exe-20261101T161526Z-a300581d/artifacts/SEMANTIC_RECONSTRUCTION.md), [original-source control-flow audit](../../../agent/runs/i76exe/i76exe-20261101T161526Z-a300581d/artifacts/CONTROL_FLOW.md), historical `ref/mission_execution/MISSION_EXECUTION_CONTRACT.md` and `ref/mission_execution/HOST_COMMAND_ABI_CONTRACT.md`. Pilot B verified 2,489 instructions in six original retail function ranges; it did not run the original VM.

## Execution-node memory (32-bit guest address space)

An imported execution node occupies **0x10BC bytes**; the observed original layout is:

| Offset | Region (bytes) | Meaning |
|---|---:|---|
| `+0000` | `1000` | 1,024 mixed operand/call-frame words |
| `+1000` | `00A0` | 40 separate host-command argument words |
| `+10A0` | 4 | Persistent predicate/condition |
| `+10A4` | 4 | Token-array pointer |
| `+10A8` | 4 | **Entry index during import; token IP after relocation** |
| `+10AC` | 4 | Saved frame pointer |
| `+10B0` | 4 | Operand cursor |
| `+10B4` | 4 | Host argument cursor |
| `+10B8` | 4 | Next runnable node |

The original arrays are mixed DWORDs, not universal arrays of pointers. The `+10A8` phase transition is why live `VmNode*` typing must **not** be propagated back into imported/serialized nodes.

## Functions and ordering

| VA | Responsibility |
|---|---|
| `00410490` | Allocate/link imported 0x10BC nodes |
| `00412500` | Relocate entry indices and initialize runtime frame pointers |
| `00414670` | Interpret 8-byte tokens across 14 token kinds; yield, call and return semantics |
| `004149F0` | Cooperative list traversal; retain yielded nodes, unlink/free completed nodes and continue successors in same pass |
| `00412CE0` | Synchronous host command dispatch, including host cursor reset and IP advancement |
| `0040A320` | Outer mission runtime gate and epoch/scheduling integration |

For explicit yield, the interpreter saves the next token index and returns without removing the node. Completion requires the **restored operand cursor to equal node base**; a null frame by itself is not the completion predicate. The command token indexes a serialized host record, not directly a numeric opcode. The dispatcher resolves its opcode, invokes a synchronous engine service, advances IP and normally resets the host argument cursor; predicate updates are handler-specific, not unconditionally false after every command.

The original caller push envelopes include **16 scheduler words** and **12 interpreter / dispatcher words**. These exceed historical Ghidra-displayed formals and are not proof that all trailing argument roles are identified. The retirement-budget latch and loop-tail count are VM protection/diagnostic behaviors, **not** a scheduler time slice imposed on a yielded node.

## Limits

No dynamic nested call-depth, malformed token, transitive host-service safety, full mission replay or reconstructed interpreter parity is proved. Several token kinds are absent from the accepted sample corpus. The error reporter `0042D5D0` is one RET in the authenticated retail PE; that observation alone does not guarantee safe continuation after resource failures. Existing separate promoted engine frame-scheduling evidence remains authoritative for its bounded class-1 frame conditions.

The merged integration reports live-node decompilation improvements and protects import/relocation signatures, but **those changes have not been verified inside the newly supplied private v99 GZF**.
