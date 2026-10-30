# Validation report

- Fresh copied-GZF project; eight sequential separate Ghidra processes, original MD5 and M06 hashes checked by probe. Python independently measures PE/GZF/ZFS/M06/DLL identities.
- Scientific verifier: **159/159 passed**; regeneration **156/156**. Fixed original opcode/descriptor/startup anchors; native list provenance; pending init order/return and exact expected stop; separate byte repeat; initialized/omit-init peripheral comparison; selected direct class1 state; raw FSINCOS negative; seven operands × four rounding modes versus separately compiled native full-helper oracle.
- Trusted `main` `.github/tests`: **38/38 passed**. The schema-test regression described in #58 is repaired on the captured base; it is not copied forward as a blocker.
- Trusted-base path/schema/hash and PR head inspection: recorded in PR publication status. Run records are hashed and validated before submission. Scientific tests do not confer promotion or merge authority.
- Expected negatives are preserved: three pending cases stop at `000C09E8` after uninitialized imported data read `0046EA39 → 000C09F8`; noinit reproduces six total memory warnings (one inherited setup warning plus five missing peripheral reads); rawx87 fails at original `0049D409` on unsupported fcos P-code.
- Positive peripheral/class1 controls retain only inherited `004461E0 → 00000000:1` optional-geometry string warning. This limits global initialization claims. Uninitialized x87 register warnings from Ghidra's stack model during inherited math startup are also not whole-machine proof.
- No full selected pending completion, input delivery/change, selected scheduler frame, live Windows/device, native render, complete cockpit or gameplay execution. Hardware numerical claims are restricted to the bounded instruction/value/rounding cases, not universal FPU status/exception equivalence.

Public `results.json` records full raw-trace hashes and exact memory warnings; `selected_events.json` contains reviewed derived events with source line numbers; `x87_oracle.tsv` is a small numerical table. Licensed bytes, DLL/database files and full traces are excluded.
