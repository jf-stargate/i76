# Execution and service boundaries

| Boundary | Final experiment treatment |
|---|---|
| `00461C80/00461D50`, node traversal, `0045F0F0` owner lookup, descriptor scan/fetch and indirect call | Original instructions. No callback/slot/list writes manufacture dispatch. |
| `00461970` class registration and `0049C320` list insertion | Original instructions; parent list-function substitute removed. HeapAlloc supplies backing memory only. |
| Class-1 `00463800` / `00463950`, post predicate `00458BF0` | Original instructions. Primary unselected post predicate is false; direct mode injects callback entry **only as a control**. |
| Class31 post `0046F420`, class34 post `0045FAF0` | Primary cases: logged `SERVICE_PERIPHERAL_POST` immediately returns zero. Original descriptor calls these addresses; service supplies their body behavior. Diagnostic: bodies execute and expose missing initialization. No claim of their correctness. |
| `0045EBD0`, VCF/CDF/resource parsing, native class/world registry, WRLD/TDEF/terrain, clock/math/filter/suspension | Inherited original instruction paths. Full pending initializer and `00463120` branch are not executed. Root staging context still supplied as in parent. |
| OS/CRT/heap/resources | Inherited supplied HeapAlloc/Free, string/format/parse/stat/rand and indexed authenticated resources. File mapping returns private M06.TER bytes. Resource releases do not prove retail ownership teardown. |
| Palette/render/audio/light/equipment and peripheral WRLD | Inherited explicit services in source. Rendering/audio fidelity and optional geometry initialization are outside this experiment. |
| FISTP `004935EE/00493608`, filter FCOS `0049E13B` | Exact 80-bit operand/control/result delegated to x87 C service; surrounding original instructions retained. No hardware-wide parity claim. |
| Trig `0049D400`, CRT `_ftol` `004BA090` | Inherited Java sine/cosine and integer-conversion/stack-pop services. Trig scope extended to post/direct-post; diagnostic deliberately retains original post FSINCOS and fails at unsupported `fcos` P-code. |
| Tick delivery, input, pause, pose, camera relevance | Controlled fields/ticks and authentic spawn basis/position. Original clock computes delta. No live Windows input/AI or retail time scheduling. |
| Native camera guard | Inherited separate direct camera probe; unselected attachment makes its eligibility guard false. It is not evidence of full presentation scheduling. |
| Full WinMain, FSM, real devices and complete selected post | Unexecuted/unresolved. Two dispatcher calls from a harness are a bounded slice. |
| Independent verifier and scalar/Gram comparisons | Research validation only, never substitutes for original dispatch or physics. |

The exhaustive service implementation is the owned Java source. No original proprietary executable/resource payload, Ghidra database, complete disassembly or bulk resource dump is published. Only sparse reviewed opcodes and derived event/state records are public.
