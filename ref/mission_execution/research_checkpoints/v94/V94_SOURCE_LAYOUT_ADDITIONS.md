# v94 source-layout observations — provisional, not original file claims

**Binary-derived adjacency:** The FSM serialized stream readers and container deserializers in `004102D0`, `00410490`, `004105A0`, `00410720` occupy a coherent consecutive code region. They use the same `005244D0` (stream pointer) and `005244D4` (dword cursor), and pack runtime records of different types. This provides stronger evidence of a loader implementation neighborhood than the semantic names alone.

**Neighboring logical group:** The long, lexically sequential command-name decoder starts `00410A10` and precedes instance registration and token-relocation code `00412400–004125C0`. The host-command switch, token VM and scheduler follow later at `00412CE0–00414B30`. These may represent several linked translation units; a simple contiguous function address range cannot prove original `.c` file membership.

**Header reconstruction hint, speculative:** The `0x10BC` VM node layout and seven 32-bit globals used in execution strongly suggest a shared private execution-context definition or equivalent common declarations. We cannot identify actual original header-file names or determine whether the node was declared in a header rather than a source file.

**Confidence:** High for adjacency, shared global references, and record layouts; moderate for grouping into a loader neighborhood; low for exact original source-file boundaries or filenames. Kept separate from verified reverse-engineering statements.
