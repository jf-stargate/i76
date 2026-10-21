# v97 provisional translation-unit map additions

These are historical source-file hypotheses, not binary facts or developer-supplied names.

| Address neighborhood | Observed verified relationship | TU inference | Confidence |
|---|---|---|---|
| `004AD410–004AD637` | Instance-key registry init/append/reverse-lookup/destroy contiguous; shared 16-byte context layout; same private heap | One registry implementation file plausible | Moderate (high subsystem coherence) |
| `00457100–004571A0` | Active-world registry initialization/destruction; invokes lower-level instance registry operations | Distinct higher-level object lifecycle module plausible | Low–moderate |
| `00457610–00457647` | Thin wrappers dispatching instance-key registration and lookup | Likely wrappers in world-object API implementation | Moderate |
| `00412400–004125FF` | Actor identity binding, runtime relocation and FSM finalization | Separate mission/VM loading module | Moderate |
| `0042D5D0` | One-byte global error/report stub called by numerous subsystems | Debug/release stub likely linked globally; original source provenance unknown | Low |

New evidence: `004AD410` initializes a dedicated heap with a 2048-record reserve; `004AD600` destroys it. This makes the contiguous low-level registry group more likely to originate from a single implementation unit, but no linker map or COFF original object names have been recovered.
