# Authentic M06 terrain through original vehicle suspension updates

## Established execution boundary

The new harness executes original retail code with authenticated M06 mission/TER and stock bus/GTSi resources. Each vehicle starts in a fresh emulator, retains state across frames and uses original root construction, class binding, VCF/WDF/CDF parsing, world registration, terrain setup, clock/subdivision, vehicle callback, suspension and camera instructions. The initial pose is copied from the first actual M06 spawn record at mission offset 0xACF6: X=2952.5, Y=31.5, Z=48152.5, with its nine original orientation floats. This is a controlled starting pose, not execution of the entire original spawn scheduler.

Both vehicles complete **32 original 00463800 callbacks**, each reaching positive-time original 00438FD0 and 0043A5D0 and returning to the harness. Original tire routine 0046DC10 records contact mode 0 with nonzero finite compression, and the normal contact branch invokes 00437230. Cameras reach the original 00406DF4 epilogue boundary with finite six-double states. A byte-identical independent bus repeat confirms reproducibility in this environment. A separate four-frame, 100-ms-clock test completes **12 suspension-solver calls**, demonstrating actual three-substep execution per frame rather than merely overwriting a timer field.

This establishes an original-instruction, terrain-aware physics/suspension update under the declared service substitutions. It does not establish Windows gameplay, authentic user input, complete mission scheduling, object collisions or hardware parity for every floating operation.

## F1: original terrain initialization and sampler semantics

The actual initialization path is:

`00493910 → original 004B3DB0 descriptor dispatch → 00493960 / 004939D0 → original 00471400 → Win32 mapping services → 00493BD0 → 00493080`.

Original WRLD loader 004B8A10 runs beforehand and copies all eight 20-byte material property records from the authenticated WREV-9 mission at chunk+0x9F into 00644220. Palette, audio/render and ancillary WRLD dependencies are explicitly substituted; property copying and terrain initialization are not replaced. The original mapper uses CreateFileA/CreateFileMappingA/MapViewOfFile to obtain the supplied read-only TER byte mapping at emulated 40000000. Stat and sprintf are CRT services; no manual ZMAP, scale or runtime page-pointer writes replace the original handlers.

M06.MSN SHA256 is `923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f`. M06.TER is 524,288 bytes / sixteen 0x8000-byte pages, SHA256 `fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea`; the local miss16 counterpart hashes identically. Original 00493080 writes step 5 at 006442C0 and reciprocal 0.2 (0x3E4CCCCD) at 006442C4. All **16,384 grid entries** at 00644380 match independently derived ZMAP mapping, including default-page pointers. Active cells use `(z+24)*128+(x+24)`; their pointers advance through real TER pages, not the editor's 0x8004 working-plane layout.

**00493550 is a bilinear terrain-height sampler**, accepting X/Z doubles and returning height in x87 ST0. The full original function extends through 004937B2. Its existing transform/bounds name and truncated Ghidra C return type are misleading. Original instructions choose four packed height samples, mask low12, interpolate first along X (with two intermediate float stores), then Z, and multiply by float 0.1. 004927B0 returns packed material bits 15–13 using its own coordinate rounding. 004931C0 computes a terrain normal using a triangle selection and approximate inverse square root; it should not be interpreted literally as returning a packed material word because of an old label.

Representative original results after the explicit FISTP correction:

| World X, Z | Height | Material |
|---|---:|---:|
| 2952.5, 48152.5 | 30.74981084912733 | 3 |
| 2480, 48725 | 0.10000000149011612 | 3 |
| 2560, 48640 | 6.70000009983778 | 3 |
| 2557.5, 48637.5 | 6.650000862032186 | 3 |

Additional probes cover M06 materials 0,1,3,5,7. The cross-page sample is important: correct cell selection must cross page boundaries, not silently clamp to the next page. Every logged original read in the height, normal and material consumers is inside the authentic mapping and matches its source uint16. An independent scalar model agrees with all corrected logged height returns to at most **3.55e-15 world units** in these traces. That agreement validates the tested sampler arithmetic, not the whole emulator.

## F2: explicit hardware instruction boundaries

The editor v26 warning was directly applicable. Ghidra 12.1.4's x86 FISTP P-code uses `round(ST0)` without consulting FPUControlWord. Original 00493550 explicitly selects round-down before FISTP at **004935EE and 00493608**. The uncorrected diagnostic gives 30.374825647777843 at the spawn query and 6.70000009983778 at the cross-page query, versus the values above; maximum tested error is approximately 0.3749852. This is not a retail terrain defect.

The published helper receives the exact emulated 80-bit ST0 and control word, performs hardware x87 FISTP qword, then returns the integer. The harness writes the original destination, pops the modeled x87 stack and advances past only that instruction. All surrounding original sampler instructions still execute. This is an explicit emulator instruction correction, not an invisible claim of unmodified Ghidra execution. The independent verifier replays every hardware request and checks the published results. Direct ELF32 sampler execution was unavailable in this environment; no full sampler-on-hardware claim is made.

## F3: restore the suspension filter initializer

The inherited harness skipped **0049E0F0** wholesale under a “cosine helper” label. Original 0046D760 actually calls it with the tire state block at runtime+0x58, parameters 0.7 and 15. The routine computes coefficients, warms a recurrence for 200 iterations, normalizes gain and clears history. Original **0049E1B0** then updates that recurrence during tire contact. Skipping the initializer leaves the filter state invalid for meaningful suspension evaluation.

The new harness executes all original initializer instructions and delegates only **FCOS at 0049E13B** to hardware x87, retaining its exact 80-bit input/output. Typical resulting coefficients are a=-1.278963612281518, b=0.4899999833106996, gain=1, zero history. Four original tire initializers complete per vehicle. Contact-mode compression includes **−0.11104892** and remains within the original **−0.141605..+0.141605** bounds. The original recurrence, clamping and tire position update execute; the compression is not assigned by the harness.

The numerical checks treat the root layout correctly: nine float basis values and three double positions. Scanning all sixteen transform words as float32 can falsely flag finite double bit patterns as NaNs. All tested bases remain near orthonormal (full Gram checks), positions and camera doubles remain finite; maximum direction squared-length error is below 3e-7 in the corrected primary sequences.

## F4: missing engine variant startup, resolved

An inherited construction diagnostic was traced to 004ADA76: “Engine ID not found.” Original 00469F10 consults a 0x60-byte-record registry at 00588E00, count 0058D900. The old placement-like names conceal its use by component selection. Original **00469B00** loads `engsnd.dat` to populate that registry before vehicle construction. Executing it over the authenticated retail resource installs twelve records; CRT strpbrk/sscanf are substituted standard services, while parsing control flow and registry writes remain original.

Retail engsnd.dat SHA256 is `b574743a27cdad3379361072b0df016e3144ac9ed21c275ed8fa418d837ca668`. Bus ID 5 maps to engine component 3, and GTSi ID 1 to component 1. Original CDF parsing then selects engine, brake and suspension records; their runtime fields are independently compared with the authentic VCFC/CDF inputs. **Final primary traces have zero original error-reporter entries.** The earlier missing-registry result is retained as a negative observation, not silently treated as successful vehicle configuration.

## Contact and architecture limits

Original 00440740 executes every measured substep, but its separate four-point probe returns **zero in these upright sequences**. Its native runtime points form a rectangle at local Y=+1; they should not automatically be equated with the four tire centers. Positive suspension contact is established instead by original solver outputs with the airborne bit clear, original mode-0 tire calls, authentic height reads and nonzero compression. No positive special swept-contact record from 00440740 is claimed.

The harness calls the vehicle callback and camera directly in controlled order. It does not execute WinMain, the complete 00463120 cockpit/weapon initialization, class-dispatch queue traversal, AI/FSM scheduling or real input delivery. Existing Win32/CRT/resource/heap/palette/render/ancillary, sine/cosine and ftol boundaries remain declared. An inherited optional-geometry null read at 004461E0 and unused x87-stack register warnings persist during setup; there are no null/unmapped terrain reads in the validated paths. Raw traces and Ghidra databases remain private.

The editor's road findings predict terrain properties, not all environment collisions. The replay confirms the heightfield route and the M06 kind-1/class-3 sample; it does not prove that intersection GEO faces are absent from collision. In particular, 0043E530 can select polygon surfaces from list 0052B94C before falling back to 00493550/004931C0. The editor scene list rooted at 00644200 is a different observed structure until an ownership/consumer bridge is demonstrated.

**Highest-value next investigation:** trace and instantiate the original bridge from scene registration 004925F0 / 00644200 to polygon-surface candidates 0052B94C consumed by 0043E530. Test a real road/intersection fixture against the now-validated terrain fallback, retaining original frame ordering and the distinction between visible pavement, terrain material and collision surfaces.
