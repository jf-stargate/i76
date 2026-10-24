# Original camera follow updates from retail-constructed and registered vehicles

**Track:** `i76exe` original retail reverse engineering. **Input:** v97 annotated retail binary, read-only Ghidra 12.1.4. This run is independent of still-draft PRs #32/#36, and uses their scripts solely as previous research evidence. The run is not an accepted canonical promotion.

## Newly executed original-code chain

For each of `noal01.vcf` (GTSi) and `nobus1.vcf` (bus), original `004AD6F0` builds the class-1 root and child hierarchy, original `004572B0` registers the root at active-world entry `00542830`, and original `00405970` initializes the 118-dword camera/projection record. Both vehicles retain object `26000000` at the entry, with observed root reference count 4 before camera update.

The default object camera callback entrypoint **`00406AB0` is valid retail code although undefined as a function in the current v97 Ghidra program**. The default mode activator `00406920` installs this callback at `00406A9B`. Invoking its original instructions against the registered root reaches native class acceptance at `00458A90`, then `00467440` returns `object+0x70` as class-specific runtime. The instruction at `00406B02` reads `runtime+0x398` into `EBX`. The pointer is zero in *both* native-VCF-constructed vehicle runtimes, so the conditional at `00406B0B` jumps to return without updating the persistent camera pose. Original constructor `00463068` initializes runtime+`0x398` to zero. This does **not** prove that regular retail gameplay leaves it zero: the missing initialization/ownership path must be traced.

Separately, original callback **`00405B90`** completes with this same registered root and reaches frame-delta processing, original object/view matrix composition helpers `00494E20`, `00494170`, `00494DA0`, and original view update **`00472990`** targeting persistent record **`004C2730`**. The callback's original no-world branch returns after 18 instructions when its stored active entry references NULL (independent controlled-entry test). In the live registered-root experiment, each original callback requires 2,054 emulated instruction steps after initial camera construction; both vehicles complete. Camera state changes, but returned view Y/Z word patterns are not physically reliable: no correct player runtime camera target is provided and Ghidra warns about uninitialized x87/memory state.

## Service boundaries and confidence

* **Native original x86:** full VCF/GEO/TMT vehicle construction, active-root registration, original `00405970` projection, native default callback through its null `+0x398` guard, all original `00405B90` instructions except explicitly identified helper calls, and native `00472990` view composition.
* **Substituted helpers:** `0049D400` trigonometric `FSINCOS` result, `004BA090` x87 integer conversion, **`004944D0` quaternion interpolation due to unsupported `FPATAN`** (controlled identity quaternion). The original matrices and view transform run around these substitutions. Prior vehicle harness still substitutes file/resource bridge, OS/heap/CRT and some rendering services.
* **Unverified:** actual producer of non-null runtime+`0x398`, real camera-mode selection by game loop, final physical pose and x87 numerical parity, accurate world bounds and camera collision, authentic visibility and raster output from the updated camera record.

The result reveals a dependency missing from the current original-code harness. The next experiment must discover which original world/vehicle runtime event makes `runtime+0x398` a valid pointer and then execute **the actual installed mode callback** through the camera-mode dispatcher, *before* trying to use its view record for full spatial queue and raster validation.

## Reproduction

Privately extract 64 verified retail fixtures from I76.ZFS using the merged v2.4 script `agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/scripts/extract_private_fixtures.py` and `evidence/retail_resource_digests.json`. Import the private v97 annotated GZF in Ghidra 12.1.4 and invoke the supplied read-only `I76_RegisteredVehicleFollowCameraProbe.java <fixture-directory> <private-trace.tsv>` under `analyzeHeadless -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath scripts -postScript ...`. Repeat twice; compare private trace SHA256 to `evidence/experiment_summary.json`, and run `verify_camera_follow.py` on the locally stored retail executable/GZF/ZFS and trace files.

No original executable, resource bytes, private Ghidra project, or complete raw instruction traces are published.
