# I76 editor v26: road-coordinate scale and raster rounding

This is a proposed original-binary research record, not accepted documentation.

Original I76EDIT.EXE SHA256: 69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df.
Ghidra 12.1.4 annotated baseline SHA256: 792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f.

The original road RSEG exporter at 004030C0 multiplies editor horizontal coordinates by 5.0 at instructions 004030C9 and 004030D2. Therefore the grading widths 5 and 2 at 00421DF0 are editor-grid units, not world units: 25 and 10 nominal world units respectively. This corrects the unit labels in proposed v25 research PR #20 while preserving its instruction evidence.

Original x87 helper 004235A4 forces FISTP truncation toward zero. The selected caller uses signed remainder of trunc(x*10) divided by ten, incrementing only if greater than four. In a 220-case probe, a Ghidra x87-emulated path diverged from instruction-equivalent host hardware x87 on 37 adjusted FP32 outputs. The emulator's precise FPU semantics cannot be assumed bit-exact without independent confirmation.

A diagnostic reconstruction from 89,595 original RSEG cross-sections in 40 retail miss8 layouts produced 286,683 final-width class-2 probes: 280,598 matched expected terrain surface, 3,403 matched known equivalent surface aliases and 2,682 differed. Probes revisit cells and are not independent. The 240 selected retail-derived integer classifier tuples tested through original Ghidra 00409210 instructions all matched the independent signed32 model, with no execution errors.

These data are reconstructed from exported RSEG geometry, not original editable .I76 road control records; the original editor was not run through a complete export. No proprietary data or GZF are included.
