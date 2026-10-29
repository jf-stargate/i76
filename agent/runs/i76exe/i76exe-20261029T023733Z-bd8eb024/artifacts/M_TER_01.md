# M-TER-01 — controlled vertical-pose M06 contact extension

## Result and scope

The original M06 bus suspension experiment completes a new -0.25 world-unit initial-Y case and its independent repeat, an unchanged-pose control and a +1.0 initial-Y countercase. Every case returns from 32 original `00463800` callbacks and 32 `0043A5D0` solvers. The lowered repeat is byte-identical. The unmodified accepted five-scenario baseline also reproduces with its unchanged 35,452-check verifier. This is original-instruction Ghidra execution with declared services, not Windows gameplay or a promoted TER contract.

Run: `i76exe-20261029T023733Z-bd8eb024`; base `81bc3b0c16dd93191e59a2d85de5d7b9ea77629e`; protocol 1.0.4; schema 1.2.0. The accepted M-TER-01 criteria are in `manual/roadmap/ENGINE_SUBSYSTEM_MILESTONES.md` at that base. Only this owned run is proposed.

## Inputs, methods and original entry points

All PE/GZF/ZFS/MSN/TER hashes were independently measured against accepted run `i76exe-20261028T174609Z-3f1f83f8`; fixture extraction was rerun from the authenticated ZFS. No old local trace or uncommitted harness was used as evidence. A copied private GZF was imported into a fresh project; a second fresh project was used to test the published replay procedure. Source scripts and their manifest hashes were fetched from GitHub at the pinned base. `evidence/provenance.json` records the lineage, identities and private trace digests.

The same original WRLD/TDEF/mapping startup (`004B8A10`, `00493910`, `00493080`), math startup (`00493C50`), engine registry (`00469B00`), stock VCF construction, original filter initialization (`0049E0F0`) and clock/subdivision are retained. Queries execute `00493550`, `004927B0`, `004931C0`; original vehicle callback `00463800` reaches `00438FD0`, `0043A5D0`, `0046DC10` and mode-0 branch `00437230` in the measured cases. None of those functions is replaced by an analytical model.

The basis and X/Z come from the first authentic spawn at MSN offset `0xACF6`; only its copied Y=31.5 is varied. Inputs are controlled bus drive 0.5 at runtime+0xE4, mode+0x104=1, initial speed proxy+0xAC=0.2, selected/native-root/native-registry=1, unpaused relevance gate and 16-ms substituted clock increments. The harness calls the original clock and vehicle callback directly. It does not execute the original spawn scheduler, class dispatcher or complete WinMain/input/FSM lifecycle.

## Cases and observations

Frame indices are zero-based. Mode-0 counts are individual tire returns, not frames of continuous grounding. A mode-1 return is reported by number; no broader meaning is inferred here.

| Case | Initial Y | Callback / solver returns | First tire mode 0 | Mode-0 tire returns | Special four-point positive returns |
|---|---:|---:|---:|---:|---:|
| control | 31.5 | 32 / 32 | 14 | 8 | 0 |
| lower | 31.25 | 32 / 32 | 26 | 4 | 0 |
| lower_repeat | 31.25 | 32 / 32 | 26 | 4 | 0 |
| raised | 32.5 | 32 / 32 | 31 | 4 | 0 |

Each case has 128 original tire returns. Lowered mode-0 compression at frame 26 ranges from -0.10416168 to -0.10383668; total lowered compression spans the original limits -0.141605..+0.141605. Original output, recurrence and clamping produce these values; the harness assigns neither compression nor tire mode. Control final position is (2952.68774414,31.652212142944336,48153.0625); lowered is (2952.65698242,31.418840408325195,48153.07421875). Full per-frame position, velocity words, flags, tire modes/compressions and separate special-probe EAX are in `evidence/frames.tsv`.

Unexpected but reproducible: lowering the initial root does not produce earlier first mode-0 tire output. A normal/material query occurs at frame 0 in the lowered run, while its mode-0 tires first occur at frame 26. The normal/material surface query, tire mode and special four-point probe are distinct observations. This run does not establish the causal branch/state explanation or a monotonic suspension law.

All 32 special `00440740` returns per case are zero. Positive tire mode-0 compression therefore does not demonstrate positive special contact, polygon contact or general collision.

## Independent validation

`scripts/verify_pose.py` first invokes the accepted baseline verifier unchanged. All five baseline traces match that verifier's environment-specific source hashes and pass 35,452 checks, including raw-Ghidra and slow-frame controls. It then validates the four new traces with 40,753 further checks (76,205 total; counts describe this exact dataset, not coverage). Validation-only published evidence comparisons are included in the latter count; `--emit` omits five such comparisons.

- Original terrain reads: 1,730 each for control/lower/repeat, 1,722 raised. Every logged address is inside the authentic TER mapping and its uint16 equals the source. All 16,384 original page pointers match independent ZMAP derivation. Sparse source-read examples, including contact-frame reads, are published; complete private traces are hashed.
- Height: every logged return and fixed initialization sample is compared with independent four-source-sample bilinear evaluation, preserving the two intermediate float stores and float 0.1 multiplier. Maximum error is 3.552713678800501e-15 in all cases.
- Materials: fixed queries and contact-path `004927B0` returns match packed source bits. Contact normal/material returns in these pose cases use material 3; no new material-class coverage is claimed.
- Normals: each original normal is compared with a geometric cross product from its three actually read source triangle points. Maximum component discrepancy is 8.92398802010419e-6 and squared-length error 1.8414730710292204e-5, within declared 3e-5 / 5e-5 tolerances for the original approximate inverse square root. Source offsets and words, original normal bits and oracle are in `normal_checks.tsv`. No bit-exact hardware-normal claim is made.
- State: typed nine-float basis Gram products, three double positions, camera doubles, original tire bounds, positive substep duration, four tires per frame and callback/solver returns are checked.
- Corrections: all localized FISTP requests retain original round-down control and agree with independent floor plus fresh hardware replay; all four FCOS requests per vehicle replay exactly. The initializer is not skipped. Sparse operand/control/result records are in `selected_events.tsv`.
- Controls: after removing only added instrumentation events/context, zero-offset trace events equal the unmodified baseline bus events exactly. Lowered repeat is byte-identical. A second full fresh-project reproduction produces identical nine raw traces and the same derived evidence.

## Execution and numerical boundaries

Use `artifacts/SERVICE_LEDGER.md` and `REPRODUCE.md`. The original two sampler FISTP instructions (`004935EE`, `00493608`) and filter FCOS (`0049E13B`) are delegated operand-by-operand to x87 hardware. Remaining inherited trig/ftol and OS/CRT/resource/heap/render/audio/palette boundaries remain explicit. Full filter instructions, coefficient warm-up and recurrence execute originally.

Inherited setup warnings remain: unused x87 register reads at `00493C68`, optional-geometry null read at `004461E0`, and an unwritable `/var/tmp` Ghidra cache-maintenance file. No added null/unmapped terrain read or original reporter entry occurs. The early verifier attempt during an incomplete raw baseline file failed its hash check; it was rerun only after baseline completion and passed. That orchestration error is not original execution evidence. Private databases, resource bytes, raw logs and full traces are excluded.

## Milestone acceptance and remaining work

**Completed within scope:** new source-verified M06 vertical-pose cases, authentic reads, independent numerical checks, full original callbacks, unchanged control, separate repeat, special/tire distinction, self-contained reproduction and documentation handoff.

**Partial:** reproducibility remains conditional on licensed private inputs and the exact GZF/toolchain; this is still controlled callback execution. Only one stock vehicle and one spawn neighborhood are newly extended.

**Inconclusive:** why lowered pose delays first mode-0 output, and which conditions make special `00440740` positive. Its measured zero is a valid negative result, not failed validation.

**Unresolved/out of scope:** new page-seam/material domains beyond baseline probes, general polygon collision, ordinary input and scheduler delivery, other missions/vehicles and hardware-wide numerical parity. No canonical promotion or maintained reconstruction is proposed.
