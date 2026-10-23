# Retail vehicle VCF construction — native-instruction evidence

**Scope:** `i76.exe`, original x86 through Ghidra 12.1.4 EmulatorHelper with substituted external services. **Tested inputs:** `noal01.vcf` (GTSi) and `nobus1.vcf` (bus), in separate fresh emulation sessions. This is a bounded vehicle/resource-construction reference, **not** a specification of full retail Windows gameplay, rendering or teardown.

**Evidence anchor:** [accepted research run `i76exe-20261022T232710Z-96c58505`](../../../agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/manifest.json), [findings](../../../agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/findings.json), [PR #16](https://github.com/jf-stargate/i76/pull/16) (merged at `a767860237b5a845db4299cb6f90984c48157c0a`). [Promotion reasoning](../../../agent/promotions/vehicle_vcf_geo_tmt_20261023.md) records why the selected findings are considered appropriate to include here. The original run remains immutable.

## Evidence classes and scope limits

The control paths below are **original retail x86 instructions executed in an emulator**, rather than reconstructed source functions or a live Windows game process. Ghidra analysis and the run's resource digests support address/asset identity, but the experiments substitute heap, CRT, indexed file-resource provider, palette, geometry-change refresh, lighting and renderer dependencies. A successful top-level return is **not** evidence that every optional asset or device-side operation succeeded.

Original identity as **recorded in the source run**: retail `i76.exe` MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`; Ghidra program `i76_mission_v97_verified_names` annotated v97 GZF SHA-256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`. The original executable, ZFS source and Ghidra database are private and **not** published here.

## Original top-level construction

The run enters the original `004AD6F0` top-level VCF path for each vehicle. Original VDF, VTF, WDF and CDF parsing/construction callbacks are reached. The class-1 runtime replaces the initial synthetic runtime owner and is pointed to by `world_object + 0x70`; parser `context + 4` is temporary VCF state and **not** a durable vehicle runtime pointer. See [architecture delta](../../../agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/artifacts/ARCHITECTURE_DELTA.md) and earlier [vehicle object-model reference](../../../ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md) for the related, independent FSM-visible object model.

| Native-emulated observation | GTSi `noal01.vcf` | Bus `nobus1.vcf` |
|---|---:|---:|
| Created world objects | 46 | 44 |
| Verified VDF body-part class, basis and position records | 31 | 29 |
| Class-30 mounted weapon objects | 4 | 4 |
| Owner-specific VTFC/TMT material registrations | 24 | 22 |

The 31/29 tested body records were compared to source VGEO records for class and transforms; the four mounted weapons per vehicle have native WDF transforms checked in the research trace. The **100-byte** VGEO part instantiator is `004B75A0`, not the separate **120-byte** instantiation path `004B7800`. Counts apply only to the two tested fixtures. [Full trace](../../../agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/evidence/native_vehicle_resources.tsv); [structured findings](../../../agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/findings.json).

## Texture-set registration and object ownership

- `00449680`: registers object-specific material/texture slots keyed by world-object identity and a case-folded logical slot name, using its original keyed lookup/registration instructions.
- `0044AB90`: decodes a retail TMT descriptor's header/frame names into the cached descriptor representation.
- `0044AC80`: creates the per-object owner-slot record referring to the TMT cache entry.

Across the tested VTF callbacks, the original instruction path was exercised for **24 + 22 = 46** TMT registrations. The logical VTF slot (often a `.map` name), the referenced TMT descriptor, and that descriptor's frame basenames are **distinct identities**. This demonstrates native-emulated registration and owner-to-descriptor pointers; it **does not demonstrate final MAP/M16/VQM pixel decoding, animation, or rendered polygon material assignment**. For details see [resource trace](../../../agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/evidence/native_vehicle_resources.tsv) and [byte identity digest index](../../../agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/evidence/retail_resource_digests.json).

## GEO materialization and body variant selection

The original `004469A0` geometry cache/loader requests resources and returns geometry handles, using `00446C90` to construct in-memory GEO representations from supplied retail resource bytes. Across both separate vehicle sessions the run recorded **eight non-null constructed GEO payloads** representing **seven byte-verified stock GEO resource identities**. The file-resource provider was substituted; the GEO construction logic itself executed original instructions.

The original `004466C0` group selector was then exercised on one body node per vehicle in the sequence **group 0 → group 4 → group 0** (exterior, cockpit, exterior). The return to group 0 reused the same first cached exterior geometry pointer **without another GEO constructor**. In these limited transitions the tested node's class, parent and basis/position remained stable. The `0044A0B0` texture refresh boundary was substituted, so this is not evidence of rendered surface changes or cache lifetime/teardown correctness. [Native trace](../../../agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/evidence/native_vehicle_resources.tsv).

## Ownership and lifecycle boundaries

The vehicle world object, its class-1 runtime at `+0x70`, body/weapon nodes, object-specific TMT slot records, shared/cache-backed TMT descriptors and GEO handles are **different layers**. Do not equate parser state, per-owner material registration and drawable surface ownership. The experiments did not establish all reference-release conditions, persistent two-vehicle reuse or mission actor bindings; consult [the archived VOM/FSM bridge](../../../ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md) for those separate domains.

## Open issues and provenance

Unresolved next links include original geometry-change texture refresh `0044A0B0`, MAP/M16/VQM pixels and palette; render-record construction at `0045CBE0` and traversal at `0045D100`/`0045D530`; material/geometry reference release and reloading in a persistent process; and original renderer effects, physics or damage. The research run's [open-issues report](../../../agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/artifacts/OPEN_ISSUES.md) is the primary record.

Possible original `.c`/`.h` grouping of the nearby texture/cache routines remains **inferred**, not source-proven. See [source-layout evidence](../../../agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/artifacts/SOURCE_LAYOUT_DELTA.md). For broader mission execution, retain [the v97 mission reference](../../../ref/mission_execution/README.md); this vehicle-construction document does **not** supersede its VM, FSM, damage, or teardown conclusions.
