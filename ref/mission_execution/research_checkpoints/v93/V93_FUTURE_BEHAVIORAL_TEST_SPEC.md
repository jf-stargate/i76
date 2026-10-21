# FSM ordering — deferred test specifications (not executed)

These are specifications for future instrumented retail gameplay / controlled serialized mission tests, not replacement-engine tests.

| ID | Fixture / precondition | Observation predicted from static analysis | Distinguishes |
|---|---|---|---|
| T01 | Two active nodes A->B; A yields immediately, B increments shared script variable then yields | B executes in the same scheduler invocation | Round-robin pass vs one-node-per-frame |
| T02 | A and B both query the same `isAttacked` event | First successful query consumes all three event markers; later query fails unless new event created | Global event arbitration |
| T03 | A queries `whoAttacked` after another node successfully consumes `isAttacked` | Cached attacker identity remains queryable independently of epoch; object validity still required | Event consumption vs ownership |
| T04 | Node A calls AI behavior-changing command, then tests an AI result | AI predicates/actions may execute synchronously before following VM token | Nested call timing |
| T05 | A issues script `rand`, then invokes weighted AI selection, B issues script `rand` | Both draw from one CRT sequence; specific count depends on selection path | Shared random-state coupling |
| T06 | A sets zero-delay success result while B remains runnable | B can execute in same invocation; scheduler does not recheck deadline mid-list | Deadline check placement |
| T07 | A mission deadline is due at beginning of list traversal | Flow state changes before VM traversal; pending nodes still processed within scheduler call | Game-flow vs immediate abort |
| T08 | Two nodes share one arrival-flag source; A queries `isArrived` | A consumes flag; B cannot consume same event without producer setting again | Consuming navigation event |
| T09 | A yields with VM `0x0A` after several host commands | Node retains token pointer and resumes in next enabled scheduler invocation | VM yield persistence |
| T10 | A returns from a nested VM subroutine with `0x0C` | Remains active; only outermost return completes and frees node | Frame-depth handling |
| T11 | Known finite VM loop executes >800 tokens before yielding | Warning flag is raised but node is not automatically yielded | Watchdog vs scheduling quantum |
| T12 | Controlled invalid infinite VM loop reaches hard threshold | **Do not run on live unsaved session**; static path calls `exit(0)` around 1000 tokens | Catastrophic watchdog behavior |

Tests should be performed on disposable saves/missions; avoid deliberately triggering the hard-exit path on a live production game session.
