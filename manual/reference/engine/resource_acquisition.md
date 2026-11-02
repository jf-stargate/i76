# Retail resource acquisition — keys, payloads and retention

**Status:** Proposed **binary-static** reference based on [Pilot C](../../../agent/runs/i76exe/i76exe-20261101T161535Z-22d9956f/artifacts/SEMANTIC_RECONSTRUCTION.md), [control flow](../../../agent/runs/i76exe/i76exe-20261101T161535Z-22d9956f/artifacts/RESOURCE_CONTROL_FLOW.md) and [promotion proposal](../../../agent/promotions/semantic_ter_fsm_res_20261102.md). Original retail `i76.exe` SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`. No native end-to-end acquisition executed.

## Acquisition

`0046FFC0` normalizes a 16-byte logical name and selects **PIX-indexed versus loaded-file-first order** according to global `00609564`. A null result from the preferred route attempts the other. The actual default/runtime value of that global was not measured. The returned address is **retained payload bytes**, not a common heap-record handle: it is either inline data at loaded-file header +0x24 or an interior pointer into a retained whole PAK.

| VA | Role and critical limits |
|---|---|
| `0046FFC0` | General acquire with conditional route precedence |
| `00470070` | Loaded-file acquisition/cache and payload pointer; 0x24-byte header with 16-bit reference count, hash and purge links |
| `00470B20` | PIX member lookup (0x1C rows), backing whole-PAK retention (0x18 rows), and offset slice return |
| `00470340` | Indexed or registered **name membership** only; not file readability, cache residency or successful selection |
| `004B2E00` | Search 0x30-byte registered-key rows with 256-bit source membership; return a selected static 0x10C mounted-source row |
| `004B3030` | Resolve chosen loose/ZFS source, read into supplied destination/capacity or allocate |
| `0046FEE0` / `0046FD40` | Query size / release by name, independently PIX-first |

A loaded-file cache record has a 0x24-byte header and inline payload, with a retained reference count; zero references may queue the record for later purge rather than immediately destroying it. `00609584` counts loaded-file **records** (+1/-1), despite a historical “used bytes” alias; separate `00609560` accounts for header-plus-payload bytes.

PIX member records are **not** the same layout as PAK-retention or registered-key records. A registered-key hit identifies membership; selected source behavior may include media callbacks and cached handle closure. The registered reader selects one source and dispatches loose-versus-ZFS based on a `.zfs` substring in the formatted path, not solely on source mode.

## Lifetime asymmetry and failure boundaries

Name-based release `0046FD40` and size lookup `0046FEE0` check PIX first **regardless of the acquire-preference global**. A logical name present in multiple source categories could therefore be acquired via one route and queried/released via another; consequences were not dynamically verified. Do **not** replace this with a uniform collision-safe acquire/size/release API.

The authenticated reporter `0042D5D0` is one RET. Some error paths may continue after an unsuccessful backing load, so a diagnostic call does not certify safe failure behavior. No claims are made about malformed length/key handling, all allocation cleanup, ZFS decoder validation, source-media configuration, active-reference invalidation or full teardown.

## Reconciliation

The legacy [resource reference](../../../ref/game/i76_resource_acquisition_reference.md) calls `00470340` an existence/search helper and `004B2E00` a registered-record lookup. Original return arithmetic narrows these descriptions to membership testing and a **mounted-source** result. The earlier vehicle integration intercepts the resource acquire/size/release boundary; its authenticated GEO/VCF payloads **do not** prove this native RES path executed. GEO/TMT owner caches are separate consumers.

Five candidate RES structures and five propagated return prototypes remain deferred in the [accepted consolidation conflict report](../../../agent/tools/ghidra/semantic-consolidation/CONFLICTS.md); this reference does not assert that they have been installed as Ghidra types. The newly supplied v99 GZF has not been opened for an internal annotation audit.
