# Original instructions and supplied services

Original executable-section equality is checked against authenticated retail PE after a fresh annotated GZF import. No function body is patched. Observed execution is Ghidra 12.1.4 emulation, with services below.

| Boundary | Treatment and limit |
| --- | --- |
| `00493C50`, WRLD `004B8A10`, TDEF `00493910` and handlers, mapping wrapper `00471400`, initializer `00493080` | Original bodies, authentic M06 bytes. Direct calls; no WinMain. |
| WRLD peripherals `00423320/00477B00/00478B30/00479780/004B8500/004908F0/00401540` | Inherited #69 return-zero services; graphics/audio/texture setup omitted. |
| Palette ACT/LUM/TBL | Original absent-resource/error branches; `0046FFC0` returns null, reporter logs and returns. No palette success. |
| OS file calls / sprintf / stat | Controlled handles, exact authenticated TER mapping, observed string formatting and stat success. No filesystem mapping lifecycle claim. |
| CRT `004BA090` ftol | Logged truncation and x87 pop. Original callsites retained. |
| `004935EE/00493608` FISTP, `00492EAF` FPATAN | Exact ST/CW passed to the versioned host x87 service inherited unchanged from #69. Original surrounding height/bounds algorithm retained. Baseline raw instruction control reproduced independently. |
| `00490A00/004911E0/00491810/004918B0/004918F0` | Original source generation; supplied backing pointers only. No manufactured source geometry. |
| View and terrain buffers | Explicit controlled affine/visibility/projection fields, zero backing; not original camera outputs. Guard rejects host geometry/polygon writes after producer entry except narrowly scoped CRT copy below. |
| `004937C0/00494E20` | Original transform/composition, all coordinate stores recorded. No replacement numerical routine. |
| `00491A30/0048E190/004922F0` | Original walker, actual RET callback and emitter. Source indices and every copied XYZ field traced. |
| `00490590`, baseline | Original body; returns original null cursor and writes null/+14. Stop after original return before emitter stores. No repair in this state. |
| `0048F9B0`, diagnostics only | Original body and bucket-zero stores. Allocation entry services `00498940/00499CE0` return supplied backing at five private addresses. Diagnostic original initialization is not actual OS allocation or frame lifecycle. |
| `0047BF00/0047B8C0` | Original z/project/screen-clip bodies. First diagnostic rejects; complete controlled projection accepts. No clip-count substitute. |
| Imported memcpy called at `0047BED9` | Supplies exact copy from original clip stack to owned output, logs full data, enforces caller/destination/source/count. Projection and clipping arithmetic remain original. This copy is a service write, explicitly excluded from claims that every final byte was directly written by a retail store. |
| `0048FE10` | Original binning, original bucket mutations and cursor increments traced; final chains independently verified. No fake bin records. |
| `004923F0/00471F00/004924B0`, alternate diagnostic | Original descriptor selector and emitter header stores; observed null pair/descriptor. Stop before vertex copies, no texture success. |
| `00474EA0` below region | Original rejection calls fill; supplied log/return with no framebuffer writes. |

Source scratch: `42000000` XYZ, `43000000` auxiliary, `44000000` edges/leaves; view `45000000`, width descriptor `46000000`. Diagnostic heap services use `48000000..48400000` in separate fresh emulators. All actual services and counts are recoverable from the full private traces. No proprietary payload is published. Rendering, texture acquisition, draw callbacks and framebuffer output are not executed.
