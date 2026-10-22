# Cold-start acceptance test

Give a new agent only `https://github.com/jf-stargate/i76` and normal repository read access, with no previous conversation context. Require it to discover: root `AGENTS.md`; pinned-main `agent/protocol/VERSION`, `access.yaml`, `BOOTSTRAP.md`; trusted source of authority; current head SHA; human reference and agent evidence locations; allowed branch/run naming; how independent conversations coexist; how to handle stale bases and contradictory findings; why direct main updates, self-approved merges, baseline promotion and governance self-amendment are forbidden; and what to do when GitHub enforcement cannot be verified.

Passing is a genuine independent fresh-agent exercise, not merely a static local test.
