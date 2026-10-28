# Original frame subdivision and missing startup math initialization

## Scope and standing

This is a new `i76exe` evidence run against accepted main `ea2d96e2155a53f40cbb1a5e12e2edd563a5a34a`, protocol 1.0.3, schema 1.1.0. It proposes no canonical promotion. At bootstrap, PR #48 was merged and PR #49 remained the sole open draft, head `5c4378827e1062131e30af0184a9732d809447d6`. Its passing integrity check did not make its findings accepted. We independently reproduced the candidate's numerical observation, then changed one prerequisite at a time.

Accepted merged evidence already follows spawn selection, VCF/VLOC attachment, original root construction and world registration: runs `i76exe-20261026T235108Z-12215047`, `i76exe-20261027T004812Z-bc6825e4`, `i76exe-20261027T014732Z-0f837d60`, `i76exe-20261027T024149Z-108e46eb`, and `i76exe-20261027T031313Z-32de4d1e`. These are immutable evidence, not automatic promotions. The existing vehicle-construction promotion is narrower than simulation/camera scheduling. See `manual/reference/engine/vehicle_construction.md` and `agent/promotions/vehicle_vcf_geo_tmt_20261023.md` at the pinned base.

## F1: clock startup is required; the timer subdivides a frame

**Binary-static plus original-instruction emulation with substituted GetTickCount and CRT `_ftol`.** Existing names are preserved, but “fixedstep accumulator” is misleading for these three routines.

- `0049C7F0`, called from WinMain at `00403247`, initializes clock defaults and the twenty float reciprocals `1/n`, `n=1..20`, at `005A7E20..005A7E6C`. The array is indexed relative to `005A7E1C`, which itself holds a frame counter. The loop's `FDIVR` and `FSTP` are at `0049C899` and `0049C89F`.
- `0049CBE0(timer,0.05f)` stores reciprocal rate 20 at timer+0, clears +4 and +8. The vehicle embeds this triple at runtime+0x444/+0x448/+0x44C. Original vehicle initialization at `00463120` and the direct-update branch call it; this test calls the same original initializer explicitly rather than claiming the complete initialization callback ran.
- `0049CC20` loads frame delta `004FE420`, multiplies by timer rate, converts through `_ftol`, adds one and caps the count at 20. It overwrites timer+8 with `n=min(trunc(dt*rate)+1,20)` for tested nonnegative finite deltas. It stores `float(dt * float(1/n))` at timer+4. Instruction `0049CC45` reads the indexed reciprocal table. It does not add prior elapsed time or preserve a remainder.
- `0049CCA0` decrements timer+8 and returns timer+4 while the count is nonzero; otherwise it returns zero. Its caller compares the returned duration with zero. A zero frame delta can leave a count but does not trigger positive-time physics.

The 16-case original-instruction sweep covers dt 0, 0.001, 1/60, 0.05, 0.1, 0.2, 1 and 2 seconds, with and without original clock startup. Without startup, all return durations are zero because the reciprocal table is zero. With startup, 0.05 emits **two 0.025** steps; 0.1 emits three approximately 0.0333333 steps; 0.2 emits five approximately 0.04 steps. A synthetic 2-second delta reaches the 20-step cap and emits approximately 0.1, so this helper alone does not guarantee a hard 0.05 maximum. The actual clock normally constrains delta separately. Do not describe the helper as waiting until 0.05 seconds have accumulated.

The original clock update `0049C920`, with GetTickCount supplied as 1000 then 1016 ms, produces float delta `0.0160000324` through its own instructions. No delta is manually written in the guarded contact scenario.

## F2: missing math startup explains the reproduced non-unit basis

**Original-instruction emulation, controlled comparison.** WinMain calls `00493C50` at `00402DA4`, before clock and mission setup. This routine fills 256 bytes at `00655180` using original `FSQRT`/`FDIVR` instructions and patches byte `00655200` to 0xFF. It is the seed table for approximate reciprocal square root `00495000`, not a terrain/map table despite existing tentative names.

The observed chain is `00463800 → 0043A3C0 → 0043BDF0 → 00494710 → 00495000`. `00494710` normalizes a cross product to build a basis. `00495000` reads the seed at `00495023`; zero-filled startup state yields a poor inverse-square-root approximation. Original yaw construction `00493DA0` and composition remain in the replay; no replacement normalization or matrix is injected.

| Controlled bus replay | First direction squared length | Second |
|---|---:|---:|
| Candidate-compatible startup | 0.472665675031 | 0.754793527867 |
| Only emulate `_ftol` stack pop | 0.472665675031 | 0.754793527867 |
| Only execute original `00493C50` | 1.00000858309 | 1.00000858309 |

All three row lengths and pairwise products are published as Gram matrices. With math startup, the Gram upper triangle is approximately `(1.00000858309,0,0,1,0,1.00000858309)`. This is **near** orthonormal, not exactly orthonormal. The approximate original math and emulator rounding remain relevant. A second bus execution is byte-identical, and GTSi independently shows the same correction. Cameras reach original `00406DF4` after `00472990` with finite tested values on both frames; the camera probe stops at that epilogue boundary rather than proving full Windows presentation.

The `_ftol` substitution used in the candidate does not pop ST0. Adding a pop alone did not change the reproduced basis. This rules it out as the cause of this particular deviation in these two controlled frames; it does not prove the old substitution correct generally. The corrected boundary follows Ghidra's ST0..ST6 shift model. Java Math sine/cosine and integer conversion remain explicit substitutions. No claim of hardware x87 parity.

## F3: original ordering and positive contact-path entry; terrain boundary remains open

**Static ordering, dynamically verified entry only.** In WinMain's gameplay state 5, `004039B8` calls original clock update before input and simulation. Its active path calls world pre-update dispatcher `00461C80` at `00403D86`, post-update `00461D50` at `00403DD5`, then FSM vehicle frame `0040A320` at `00403DDF`. Later presentation uses the selected camera callback. This ordering is static evidence; the replay does not execute WinMain.

The dispatchers search a class-descriptor table with 0x34-byte stride and call its pre/post slots indirectly at `00461D38`/`00461E08`. Original PE data identifies class 1 at `004F777C`, initialization callback `00463120` at `004F7784`, pre callback `00463800` at `004F7788`, and post callback **00463950** at `004F778C`. Do not mistake the internal address 004639A0 for the descriptor's entry point.

Original `00463800` chooses direct control/lifecycle integration when the activity predicate returns 2 or status bit 0x20 is set, provided the pause gate permits it. Otherwise it initializes this frame's subdivision and loops lifecycle `00465370` and wheel physics `00438FD0`. Predicate `00406840` computes distance from the camera; the branch called “active” by existing annotations actually includes farther-away objects. These labels should not be treated as proof of retail scheduling intent.

With original math startup, clock startup and timer initializer, a camera near the controlled bus selects the latter branch. Original `0049CC20/0049CCA0` yields positive dt; original lifecycle and `00438FD0` execute, and original `00440740` begins wheel-point contact probing. The guarded run stops at `00493550`, where scale `006442C4` and terrain table state are still zero. This is **not a completed vehicle simulation frame with validated ground contact**.

An earlier exploratory continuation without the guard entered `0043A5D0` and produced finite poses, but the original terrain sampler read uninitialized addresses 0, 2, 0x100 and 0x102 at `00493652`, `004936A5`, `004936F8`, `0049373D`. Those downstream results are invalid contact evidence and excluded from positive findings. The final published harness stops before them. The sampler's decompilation is truncated/misleading: its inferred return type hides the x87 height result and the original instructions continue beyond the decompiled body. Follow the instructions and actual terrain block pointers at `00644380` rather than trusting its existing semantic name.

## Limits and highest-value next investigation

The stock VCF resources, original root/attachment/registration and persistent vehicle state are reused. Heap, CRT, resource supply, palette/render and ancillary services remain substituted as in the pinned candidate harness. Some inherited optional-geometry/unused-x87 uninitialized-read warnings also occur during construction; this investigation does not certify the entire initialized state. Drive inputs, camera distance and pause state are controlled. No original scheduler execution, authentic terrain contact, hardware numerical parity, rendered pixels or complete mission architecture is claimed.

**Next:** recover original mission terrain initialization feeding `006442C4` and the packed-height block pointer table `00644380`; bind a hash-verified retail mission terrain fixture in this same replay. Then remove the guard only after proving all four original sampler reads use valid loaded blocks, and demonstrate positive contact records, suspension-solver completion, full callback return and pose/contact flags across frames. Preserve this run's original math/clock initialization. This is a narrower and more actionable boundary than repeating the two-frame active-control experiment.
