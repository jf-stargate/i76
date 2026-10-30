# Retail engine class-1 frame scheduling — bounded original-instruction evidence

**Scope:** retail `i76.exe`, Ghidra 12.1.4 original x86 instruction execution in a *controlled* three-frame M06 experiment for unselected stock GTSi and bus. External services, timing, selected status and inputs are explicitly supplied as described below. **This is not an unmodified Windows gameplay loop, a complete WinMain frame, validated selected-player input/cockpit behavior, or a general scheduling contract for every class.**

**Promotion decision:** [bounded ENG frame scheduling](../../../agent/promotions/engine_class1_frame_scheduling_20261029.md), candidate until human acceptance of its containing PR. **Principal accepted run:** [M-ENG-01 manifest](../../../agent/runs/i76exe/i76exe-20261029T170926Z-3a9402a5/manifest.json), [findings](../../../agent/runs/i76exe/i76exe-20261029T170926Z-3a9402a5/findings.json), [report](../../../agent/runs/i76exe/i76exe-20261029T170926Z-3a9402a5/artifacts/M_ENG_01.md), [service ledger](../../../agent/runs/i76exe/i76exe-20261029T170926Z-3a9402a5/artifacts/SERVICE_LEDGER.md), merged [PR #58](https://github.com/jf-stargate/i76/pull/58) at `e06ca00650c1bf1763fac68542f09e13e3b8e883`.

**Original input identities (reported by accepted source runs, not newly hashed here):** `i76.exe` MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`; private annotated Ghidra `i76_mission_v97_verified_names` GZF SHA-256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`. Licensed `I76.ZFS`, `M06.MSN` and `M06.TER` have identities in the [run manifest](../../../agent/runs/i76exe/i76exe-20261029T170926Z-3a9402a5/manifest.json); their payloads are not public.

## Evidence categories and phase boundaries

| Boundary | Original retail anchor | Confidence and specific scope |
| --- | --- | --- |
| WinMain gameplay state 5 scheduling | `004039B8`, pre call `00403D86`, post call `00403DD5`, FSM call `00403DDF` | **Binary-static**, from earlier accepted [frame-startup report F3](../../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/FRAME_INITIALIZATION.md): clock precedes pre/post and FSM in the mapped path; **not** executed here as one WinMain loop |
| Original class registration and node insertion | `00461970`, `0049C320` | **Original-instruction**, in M-ENG-01: original list links and counters rather than parent whole-function insertion substitute; only heap backing is supplied |
| Class-collection roots | head `0054B204`, pending head `0054B208` | **Original-instruction**, in the constructed M06 setup. Distinct from world registry `00542830` (count `0054A25C`); world registration alone does not prove dispatch membership |
| Pre/post descriptor traversal | `00461C80`, `00461D50`; object resolver `0045F0F0` | **Original-instruction** walks 15 nodes for each tested vehicle; original lookup, descriptor scan (stride `0x34`) and indirect callback control flow |
| Class-1 descriptor and slots | descriptor `004F777C`; init `004F7784 → 00463120`, pre `004F7788 → 00463800`, post `004F778C → 00463950` | Original executable descriptor bytes verified unchanged. **Post entry is `00463950`, not internal `004639A0`** |
| Indirect invocation | pre `00461D38`, post `00461E08` | For both tested vehicles, original indirect instructions reach class-1 callbacks and return to their call sites. Direct callback invocation exists **only in the separate control** |

Original-list registration, traversal and callback return are supported by [dispatch events](../../../agent/runs/i76exe/i76exe-20261029T170926Z-3a9402a5/evidence/dispatch_events.tsv), SHA-256 `aef6490e6a4832da0f8e5ec5964fd82a22af52dc7aa6de8386b8a73ffde9c16e`, and [sparse instruction anchors](../../../agent/runs/i76exe/i76exe-20261029T170926Z-3a9402a5/evidence/instruction_anchors.tsv), SHA-256 `1fe3af3ece04f7e29c509d00fdf36c3a430641d212c3a5ccdab6a3bf6ba3dce6`. The original pending-list initializer `00461B80` and complete class-1 `00463120` initialization were **not** executed in this successful dispatch slice.

## Tested phase and state chronology

Each of three frames uses the original clock update `0049C920`, supplied monotonically increasing 16-ms ticks, and then original pre and post dispatchers. Original class-1 pre enters the original solver and sampled authentic M06 terrain reads. Both tested vehicles produce the following sampled root Y values in this controlled unselected configuration; X/Z remain `2952.5, 48152.5`.

| Frame | Y before original pre | Y after pre and post |
| --- | ---: | ---: |
| 0 | 31.5 | 31.49874496459961 |
| 1 | 31.49874496459961 | 31.49498176574707 |
| 2 | 31.49498176574707 | 31.488710403442383 |

The original status is `0x00020800` (unselected). Pre mutates the sampled root pose, velocity, basis, timer and runtime flags; first-frame sampled flags change from `0x00000040` to `0x00000044`. In these cases original post `00463950` reaches original predicate `00458BF0`, which is false, and returns without changing **the sampled fields**. This is **not** proof that post writes no bytes in any case.

The constructed bus's nine sampled before/after phase states match the deliberately direct-callback control, and a separate bus process reproduces the dispatcher trace byte-for-byte. Empty-collection control invokes no callbacks. [Results](../../../agent/runs/i76exe/i76exe-20261029T170926Z-3a9402a5/evidence/results.json), SHA-256 `12c0bbd4d03efab9e084fb65c1fa6e1ffb969a601c08862993d165ca0bccb8af`. The run reports 3,807/3,807 scientific verifier checks, but its historical `validation.json` includes an unrelated then-unfixed trusted-base archive-test failure and remains **partial**; that immutable record must not be retroactively rewritten. The schema test was subsequently repaired in [PR #59](https://github.com/jf-stargate/i76/pull/59).

## Supplied services and boundaries

- **Original code exercised:** math/clock/filter setup, native constructors, class binder/list insertion, world/terrain/suspension routines, class dispatch/lookup/descriptor walk and both class-1 callback entry/return paths in the unselected state.
- **Supplied:** private hash-checked resource contents through a provider; OS/CRT/heap, clock ticks, controlled input/throttle/pause/camera relevance and some ancillary audio/palette/render/light services. FISTP/FCOS at the cited sampler/filter addresses use a bounded x87 hardware shim; other trig and integer-conversion operations retain declared research substitutions.
- **Peripheral post behavior substituted:** class31 `0046F420` and class34 `0045FAF0` body behavior (their original descriptor selection and calls remain observable). Those post implementations are **not** validated by the successful scenarios.
- **Unresolved original selected-player path:** the diagnostic reaches class-1 post but original FSINCOS bytes `D9 FB` at `0049D409` stop under unsupported `fcos` P-code after incomplete peripheral-state reads. This is a **reproducible failure boundary**, not success with selected input, cockpit or audio. No full `00463120`, pending initialization, normal input/FSM, actual game loop, device output, full frame render, general polygon collision or teardown is established.

## Reproduction and interpretation

Follow the accepted run's [reproduction guide](../../../agent/runs/i76exe/i76exe-20261029T170926Z-3a9402a5/artifacts/REPRODUCE.md) and [verifier](../../../agent/runs/i76exe/i76exe-20261029T170926Z-3a9402a5/scripts/verify_schedule.py). Original code execution depends on private licensed PE/GZF/ZFS/M06 fixtures and explicit service substitutions. This documentation review did **not** independently rerun private Ghidra inputs.

For broader scene/terrain semantics see the [TER index](../../roadmap/subsystems/TER.md) and [M06 contact evidence](../../../agent/runs/i76exe/i76exe-20261029T023733Z-bd8eb024/artifacts/M_TER_01.md). Positive tire mode-0 is not proof of populated polygon candidates or general collision. For broader subsystem planning, see [CAP-FRAME-01 and CAP-CONTROL-01](../../roadmap/CAPABILITY_ROADMAP.md). A separate new research run must close selected-post and ordinary input prerequisites before expanding this reference into a full-frame contract.
