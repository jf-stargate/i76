# I76 v90 — tentative historical source-layout observations

These are **provisional translation-unit hypotheses**, never recovered original .c/.h filenames or proven boundaries.

| Region | Verified locality | Plausible grouping | Confidence for actual TU boundary |
|---|---|---|---|
| `004211B0–00421E70` | DirectSound initialization, runtime pump, object allocation and release; direct callers of voice clear | General sound-system lifecycle / audio-object implementation | Low/medium (subsystem is clear, object-file edges unverified) |
| `00423600–00423B00` | CB request allocation, enqueue latch, completion callback, clear and death-voice reconciliation | Separate CB speech/voice queue module near general audio routines | Medium for coherent source neighborhood; low for exact start/end |
| `0040BF20–0040C040` | FSM command adapters for triggers, speech, radar, salvage | Small FSM bridge/host-command wrappers | Medium for broad grouping, unproven file boundary |
| `00415020–00415640` | Waypoint progress, path validation, AI state constructor | Path-planning and AI state infrastructure | Low for same original translation unit |
| `00420A20–00420E70` | AI path activation, control reset and predicate based on `AI+0x9C` | AI behavior action/callback neighborhood | Medium semantic locality, low exact source boundary |
| `00458F40` | Generic recursive object-class lookup, consumed by `triggerGate` but not a direct host wrapper | Generic world-object class/tree utility | Medium for subsystem, unknown TU |

Potential header relationships: a common world-object declaration for `+0x60/+0x64/+0x6C/+0x70`, a CB-record structure with `+0x10/+0x14/+0x18/+0x1C/+0x20`, and AI/path context exposing `+0x9C`. These are inferred type interfaces, not recovered header content.
