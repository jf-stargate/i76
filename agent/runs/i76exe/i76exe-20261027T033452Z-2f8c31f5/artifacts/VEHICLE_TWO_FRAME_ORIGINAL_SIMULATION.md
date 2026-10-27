# Two consecutive original class-1 vehicle physics and camera updates

**Evidence tier:** original retail i386 instruction emulation, Ghidra 12.1.4 annotated v97, stock GTSi and bus assets. Original executable, archive and annotated Ghidra hashes are in `manifest.json`. **Not a live Windows retail frame.**

## Recovered simulation execution path

The retail class-1 update callback `00463800` is referred to by the class callback descriptor at `004F7788` (data reference). Its controlled *active* branch first checks object activity with original `00406840`, pause with `0044E010`, and delta with original `0049C7A0`. It invokes lifecycle `00465370` and original controller `0043A3C0`. A direct retail `E8` at `0043A481` invokes `0043BDF0`, which writes a 16-word transform through the supplied root `object+0x18` destination and updates the vehicle runtime velocity. This is **actual original-instruction mutation of the constructed root**, not a test script writing the computed pose.

The different *inactive* branch uses original fixed-step interval/timer `0049CBE0/0049CC20/0049CCA0` and terrain/wheel-contact routine `00438FD0 → 0043A5D0`. An idle native-root class callback executed twice but its isolated fixed-step clock supplied zero elapsed seconds. **No nonzero wheel-contact tick, terrain solver or natural game scheduler ordering was validated** in this run.

## Native vehicle and controlled drive experiment

The original `0045EBD0` root constructor and `004AD6F0` VCF/VLOC loader create real stock bus/GTSi class-0x28 attachments. Original `004572B0` creates the world registry entry consumed by camera. This reuses the accepted construction and camera investigations with the same private asset fixtures; licensed bytes remain private. Original spawn-status code stops at the actual VCF CALL boundary, followed by explicit same-state VCF invocation.

With this real node, the harness invokes original class callback `00463800` then original default camera `00406AB0` **twice without resetting state**, for each stock vehicle. Controlled input: runtime `+0xE4 = 0.5`, `+0x104 = 1`, `+0xAC = 0.2`, delta global `004FE420 = 1/60`, input pause globals equal, and an artificially distant camera reference (`x=1000.0`) to select the original active-vehicle path. The original activity comparison, drivetrain, integration and camera instructions run; original trig helper `0049D400` and x87 ftol helper `004BA090` are explicitly intercepted for the unsupported emulated numerical operations, along with existing Win32 heap/resources/palette services.

| Stock vehicle | Frame | Root world Z (double) | Root direction norm squared | Nonfinite root float32 / camera doubles | Camera callback |
|---|---:|---:|---:|---|---|
| Bus | 1 | 0.0033333336468786 | 0.472665675031 | 0 / 0 | Normal return |
| Bus | 2 | 0.005625023506581783 | 0.754793527867 | 0 / 0 | Normal return |
| GTSi | 1 | 0.0033333336468786 | 0.472665675031 | 0 / 0 | Normal return |
| GTSi | 2 | 0.005625023506581783 | 0.754793527867 | 0 / 0 | Normal return |

The vehicle position changes on each class-1 update. Each following original camera update reaches `00437F90` and `00472990` and produces finite six-double view state in the tested camera field range. Camera state is **not reset** between frames. The two independent bus original-instruction replays are byte-identical and their SHA-256 digests are recorded in `evidence/replay_provenance.json`. A separate zero-drive *idle* control completes two class callbacks and two camera callbacks but does not advance the vehicle.

## Important negative result and limits

The derived root direction lengths are **not unit length**; norm squared is 0.472665675031 after frame one and 0.754793527867 after frame two. This is a substantive unresolved numerical accuracy issue and could reflect the controlled drive/runtime setup, other skipped original simulation stages, or Ghidra math. Do **not** equate a finite matrix with an orthonormal basis or authentic vehicle gameplay motion. Nor is a selected callback test proof of the actual game scheduler's invocation ordering.

Additional limits: the fixed-step wheel/terrain path and collision response were not executed through a positive time tick; original complete resource I/O/Windows heap and hardware x87 were not executed; camera mode scheduling, pose realism, raster/clipping and pixels remain untested.

## Follow-up

1. Trace native simulation clock/global delta producer and the original class dispatch scheduler; reach the positive fixed-step wheel/contact branch without fabricating the accumulator table.
2. Trace normal vehicle control initialization and pose normalization after `0043BDF0`; test hardware x87 and constrain matrix orthonormality error.
3. Only after validated original camera/pose continuity, connect subsequent frame visibility and polygon rendering.
