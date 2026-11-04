# I76 developer-console grammar — version 0.1

**Status:** Initial implementation contract for the independently authored reconstruction.
This is **not** an attempt to reproduce the retail `i76shell.dll` command language,
game mission scripts, or the behavior of an original Interstate '76 console.

## Design

A single registry describes **commands** (operations) and **console variables**
(CVars, typed runtime state). This combines the registered-command/variable approach
used by Unreal and Source with hierarchical operation names, without implementing a
general-purpose operating-system shell.

```text
command-line     = whitespace?, invocation?, whitespace?;
invocation       = command-name, { whitespace, argument };
command-name     = command-word, { whitespace, command-word };
argument         = bare-argument | quoted-argument;
quoted-argument  = '"', { quoted-character }, '"';
whitespace       = one or more ASCII spaces, tabs, CR or LF;
```

Registry lookup uses the **longest registered command name**: `resource mount`
is a single registered command, distinct from `resource`. Command and CVar
identifiers are lowercase ASCII and case-sensitive. Argument bytes and filename
case are preserved until the owning subsystem validates them. Quoted and bare
segments may be adjacent within one token; empty double quotes yield an empty
token. In double quotes, `\"` and `\\` escape a quote and a backslash; every
other backslash is literal. Unquoted backslashes are always literal (important
for Windows paths). Unterminated quotes, control characters, commands longer
than 4096 bytes, and more than 64 tokens are rejected before execution.
Blank interactive lines are not dispatched; an explicitly submitted empty
command is an error.

One invocation is accepted per line. No pipes, shell expansions, environment
substitutions, redirects, semicolons, subshells, or filesystem execution.
`--` ends option recognition and is not passed to the command; named options
are **reserved**, not implemented by this milestone. An unknown `--option`
is rejected. Legacy resource and level commands that take a single trailing
path or name still accept unquoted spaces as a compatibility concession, but
quoting is recommended. Other commands have fixed argument counts.

## Commands

```text
help
help resource
help resource mount
find paused

resource mount "/path/to/Interstate 76"
resource list
resource unmount 2

level inspect M06.MSN
level prepare demo.level
level activate
object spawn vehicle "Test Vehicle"
object list

sim pause
sim step 60
sim status
```

`sim pause`, `sim resume`, `sim step` and `sim status` are aliases
for the preexisting top-level `pause`, `resume`, `step` and `status`
commands. The old spellings remain supported. Application UI commands
(`play`, `menu`, `back`, `options` and menu numbers) belong to the shell
frontend, not the engine registry.

## CVars

A CVar name is a single dotted identifier. A bare name queries its current
value; a trailing value requests an assignment. `name ?` or `help name`
shows its registered description and access mode. Read-only variables reject
writes without changing engine state.

| CVar | Type | Access | Meaning |
| --- | --- | --- | --- |
| `sim.paused` | boolean | Read/write | Calls the runtime pause setter |
| `sim.tick_rate` | unsigned integer | Read-only | Configured fixed tick rate |
| `sim.tick` | unsigned integer | Read-only | Current simulation tick |
| `world.objects` | unsigned integer | Read-only | World object count |

Boolean assignments accept only `true`, `false`, `1` or `0`.
All values come from live runtime state; no placeholder renderer or
audio variables have been introduced. Example:

```text
sim.paused
sim.paused true
sim.paused ?
sim.tick_rate
world.objects
```

## Implementation boundaries

- `console.cpp`: lexing, longest-name lookup, metadata, help/search, arity
  validation, read/write CVar operations and alias translation.
- `command.cpp`: existing semantic command implementations. A compatibility
  bridge preserves their tested behavior while the new registry becomes
  the shared entry point for headless and terminal shell dispatch.
- Shell navigation remains frontend-owned; shell and engine headless paths
  share the core registry for engine commands. SDL menu dispatch is unchanged.
- Malformed input and invalid typed values do not mutate the runtime.
  All console results use existing diagnostic sinks.

`i76_console_complete(prefix)` exposes ordered registry completion candidates
for frontend integration. **Tab-key interactive completion, typed positional
schemas beyond argument counts, built-in persistence, CFG execution, additional
CVar types/flags and engine lifecycle callbacks are deferred.**
