# Original execution and supplied services

The new Java probe is an owned copy of the accepted M06 probe with only a bounded initial-Y parameter and additive frame/substep, material-return and normal-return logging. `evidence/provenance.json` identifies the exact parent bytes. The inherited PR #49 comment is older ancestry, not the source used for this run. Source-code difference is reviewable against the pinned parent script.

| Boundary | Treatment |
|---|---|
| WRLD/TDEF/ZMAP/page initialization; stock vehicle/CDF selection; filter/tires; callback and integrator | Original retail instructions under Ghidra EmulatorHelper |
| FISTP at 004935EE / 00493608 | Exact modeled 80-bit ST0 and control word passed to accepted x87 C service; original destination, pop and PC advancement emulated for only that instruction |
| FCOS at 0049E13B | Exact 80-bit operand/result delegated to x87; surrounding 0049E0F0 initializer, 200 warm-up iterations and recurrence execute originally |
| OS file access/mapping | Supplied CreateFileA/CreateFileMappingA/MapViewOfFile over authenticated, unmodified M06.TER mapped at emulated 40000000 |
| Resources, heap, CRT | Inherited indexed resource provider and allocation services; standard string/format/parse/stat/rand helpers supplied. Resource reference-release services do not establish retail teardown. |
| Palette, renderer/audio and ancillary WRLD services | Inherited explicit stubs; lighting/refresh/release and optional material/equipment side effects remain substituted |
| Selected trig/ftol | Inherited Java sine/cosine and float-to-integer boundaries; integer consumption mode retained. These are additional numerical substitutes beyond the localized hardware fixes. |
| Input, initial pose, camera relevance, pause and tick delivery | Controlled harness fields and source spawn pose; original clock computes delta from supplied ticks. Delta/substep tables are not assigned to manufacture contact. |
| Class dispatch, WinMain, AI/FSM and full 00463120 branch | Not executed end-to-end; vehicle and camera callbacks invoked directly |
| Independent scalar/triangle/Gram checks | Validation tools only; never substituted for original terrain/contact instructions |

`scripts/I76_TerrainPoseProbe.java` is the exhaustive service implementation. Mode must be `math-clock-pop-terrain-host-filter-registry` for the new cases; no `lowered` diagnostic mode is used. The only case variable is the final Y-offset argument: 0, -0.25, -0.25, +1. The inherited raw baseline mode is a labeled numerical negative control and is not positive contact evidence.
