# Original editor object/identity and FSM bridge

**Evidence baseline: editor v01–v07**, independently checked against the retail executable and shipped missions.

The public builder has a dormant external `fsmcomp` launcher, but no original compiler executable or full input grammar was recovered. Normal public-editor export at `0041B150` produces an empty 28-byte FSM payload. In the examined shipped missions, multiplayer M-series FSM sections were empty while A/S/T missions carried nonempty compiled scripts. The offline versus network game runtime also has differing scheduler paths.

The editor—not `fsmcomp`—generates the **eight-byte object instance keys** during level export. It copies the first eight resource-name bytes and encodes an instance ordinal across the high bits. The `.IXP` mapping sidecar consists of a u32 count followed by records `name[40], key[8]`; compiled FSM actors include the same 48-byte identity pair. The game looks up exact eight-byte keys, not actor display names.

The workspace stores mutable object lists, and save/reload traversal can change their order. Because export regenerates IDs, duplicates can acquire different ordinals even when no edits were made. This is a **code-derived conditional identity hazard**, not an observed session failure.

## The top-level OBJ record: 108 bytes

| Offset | Size | Meaning |
| --- | --- | --- |
| 0x00 | 8 | OBJ tag and length |
| 0x08 | 8 | Instance key |
| 0x10 | 36 | Nine f32 rotation matrix coefficients |
| 0x34 | 12 | Three f32 serialized X/Y/Z coordinates |
| 0x40 | 36 | Unused/reserved in inspected reader; zero in accepted retail OBJ records, but editor writer does not explicitly initialize all bytes |
| 0x64 | 4 | Class identifier |
| 0x68 | 4 | Status/option flags |

The editor copies workspace status `+0x60` to OBJ `+0x68`. The runtime preserves it as `WorldObject+0x10`; the editor exposes team bits `0x00070000` and a bit-`0x10` two-state vehicle property. Runtime-class callback selection need not replace serialized class identity: e.g. classes 3/11/12 may use the shared class-2 callbacks.

In retail T15 the compiled actor `shack1` references key `ahut1` with two matching world objects (classes 3 and 11). The game registry normally appends duplicate full keys, and lookup searches backward. Whether both resource constructions actually completed is a separate runtime validation question, not proven by static lookup logic.

Vehicle/object heap lifecycle research appears separately in [runtime notes](runtime_object_lifetime_notes.md); none of those runtime allocation mechanisms is necessarily part of editor authoring.
