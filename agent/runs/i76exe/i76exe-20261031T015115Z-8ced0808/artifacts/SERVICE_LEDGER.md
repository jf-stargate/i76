# Service and ownership ledger

## Original instruction bodies

Original vehicle construction, resource-backed GEO selection, registration, two camera updates, visibility, queue production/consumption, projection, draw-command/edge/span production, `00473640` finalization and both `0047CB00` callbacks execute in one retained emulator state. The native callback returns twice at `0047CE38`, and finalization returns. Original `00474C60` constructs the descriptor with a supplied allocation return. Original `00474C10` and `004791E0` are separately attempted and stop at their first unmapped imports. Neither original callback body nor original pixel writer is replaced.

## Newly supplied services and data

| Boundary | Supplied action | Limit |
| --- | --- | --- |
| `00474C10 → [004BC110] → 000C0FE2` | None in raw initializer case | Original `HeapCreate` import cannot execute in Ghidra; handle `[0058DAC8]` stays zero. |
| `00474C60 → [004BC108] → 000C0FFE` | One 307,232-byte allocation at `3F000000`, `A5` initial bytes and 16-byte `CD` guards | Service returns a pointer only; original `00474C60` computes and writes all descriptor fields. Its zero heap handle is accepted by this diagnostic service, not proven valid for retail Windows. |
| `004791E0 → 004BA090 → 000C0BFC` | None in original producer attempt | First imported float-to-integer helper is unavailable; original shade-table completion is not claimed. |
| Diagnostic `0061B2A0..0061D29F` | 8,192 exact bytes, `((index & 255)+(index >> 8)) & 255`, hash in report | Supplied *after* failed original producer case. No authentic palette or shade fidelity claim. |
| Controlled offset case, descriptor `005DCEDC` | X offset DWORD 4 after original construction | Separate bounded address variation, not mislabeled as original initialization. |

The framebuffer backing belongs to the diagnostic allocator. The declared writable surface is exactly `3F000000..3F04AFFF` (307,200 bytes, 640 rows × 640 bytes); the allocation adds 32 bytes and guards on both sides. The original pixel writer reaches only X=233..247, Y=313..326 in the primary case. The offset case moves those addresses four bytes right. Before each original store the harness checks the address belongs to the declared surface, records its previous byte, executes one original instruction, then records the new byte. No external service writes to that region after allocation; no service manufactures a pixel. The callback reads the destination at `0047CC25`; the absent-surface case stops there before any unowned read.

## Inherited services

The unchanged PR #75 ledger remains applicable: deterministic OS heap/resource/file/CRT helpers, Ghidra FS/SEH backing, supported math helpers, source ZFS extraction, controlled root poses/camera inputs, queue arena backing, original workspace initialization, guarded draw heap allocations/delete, selected ancillary rendering/texture/lighting stubs and the kind-10 D110 draw service. VQM/M16 texture acquisition returns null, so the native vehicle polygon uses original untextured material fallback. These inherited services do not write the diagnostic framebuffer. See accepted run `i76exe-20261031T011731Z-307babbf/artifacts/SERVICE_LEDGER.md` for the exact predecessor service PCs and ownership limits.

Ghidra's only inherited warning in the final nonempty cases is the optional null geometry-name read at `004461E0`. Original `00474D40` is a statically audited surface reset/release route; this run does not execute teardown or establish retail lock/unlock timing. Original Windows device/surface initialization and palette/resource source remain unresolved. No accepted run, canonical reference or shared tool is modified.
