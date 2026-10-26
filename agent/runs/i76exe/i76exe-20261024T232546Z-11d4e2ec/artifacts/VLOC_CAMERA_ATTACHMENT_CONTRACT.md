# VLOC type-0x28 vehicle-camera attachment: original retail execution

**Status:** new research evidence, not canonical promotion. **Pinned base:** `15b2a30c24fcfc038de4d11be192566826e2ec0d`. **Provenance:** retail i76.exe MD5 `a640ea0097dbb62e0c77b7f2847c7161`; private Ghidra 12.1.4 annotated v97 GZF hash and full retail PE/ZFS hashes are in `manifest.json`. This checkpoint follows the still-draft camera PR #37 without rewriting it.

## Previously unresolved runtime+0x398 field

The prior original-code camera experiment (draft PR #37) found that default mode `00406AB0` reads `get_vehicle_runtime_context(vehicle)+0x398` at `00406B02`, exits at `00406DF4` if null, and that native-constructed GTSi/bus vehicles had zero there. The original constructor `00463068` explicitly initializes the field to zero. The **source of the nonzero pointer is now recovered**:

1. Original `004AE000`, annotated `parse_vloc_vehicle_local_attachment_chunk`, dispatches on VLOC record type at `record+8`. The actual eight-way jump table at `004AE2B4` has case `0x28` (index 5) routed to `004AE056`.
2. At `004AE057` it calls original `00458BF0`, which returns true only if the world object is non-null and has `(object+0x10) & 0x10` set. If clear, this callback **returns success without constructing a child**.
3. If set, `004AE067` takes the address of `runtime+0x398`. After calling original child wrapper `004B47C0` and the object class/runtime binder `00461970`, `004AE2A2` stores the produced child pointer into that location. Class discriminator is the original VLOC type `0x28`. The parser copies nine 32-bit transform words and writes additional float-to-double translation fields. Do not interpret x87 conversion results as numerically verified under the emulator.
4. The original camera callback obtains the same runtime through `00467440` and, at `00406B02–00406B0D`, tests the stored attachment pointer. This is **a VLOC-derived vehicle-local object handle**, not merely an independently allocated camera controller.

## Retail resource evidence

Both stock vehicle VDFs actually include the requisite VLOC item: `valeprec.vdf` for the GTSi and `vxbus.vdf` for the bus. In each verified  retail file it begins at offset `0x10A`, has a 60-byte record, type `0x28`. Each VDF also contains VLOC types `0x2A`, `0x23`, `0x24`, and `0x26` at the following respective offsets. See `evidence/vdf_vloc_census.tsv`; private VDF contents are not published. The stock VCF top-level wrappers contain separate `VCFC` chunks and point to these VDFs.

## Original-instruction replay (2 × 4 scenarios)

The replay extracts the exact stock VLOC 0x28 record from separately held private VDF resource bytes. It provides a small controlled class-1 world object and runtime, and invokes original `004AE000` with and without status bit `0x10`. The original `00458BF0` predicate, `004B47C0` wrapper, VLOC field writer, and original default-camera callback through its guard are **not substituted**.

| VDF | Root flag | Stored runtime+0x398 | Original default camera branch |
|---|---|---|---|
| GTSi `valeprec.vdf` | clear | null | returns at `00406DF4` |
| GTSi `valeprec.vdf` | `0x10` | created child | reaches `00406B13` |
| Bus `vxbus.vdf` | clear | null | returns at `00406DF4` |
| Bus `vxbus.vdf` | `0x10` | created child | reaches `00406B13` |

Each callback returns `1`, the flagged cases copy all **nine 32-bit transform source words exactly**, and two complete execution replays produce byte-identical private traces. The only services explicitly substituted are node allocation at `0045EBD0` and class/runtime registration at `00461970`. A second attempted run allowing the full class/runtime binder to proceed in this *isolated* synthetic world entered an unresolved indirect callback at an uninitialized address; that test is **not** counted as a success. The normal-game class registry and allocator remain to be integrated before claiming an entire native vehicle VLOC construction lifecycle.

## Architectural implications and open questions

- The engine deliberately omits this attachment for world objects without bit `0x10`. **Do not label the bit universally as a player flag** until its producer and other consumers are traced; it is a proven eligibility predicate for this VLOC callback.
- This resolves the **direct field producer**, not the higher-level event that chooses the eligible world flag, VDF loading order or camera mode. The real GTSi/bus constructor needs to run with the correct retail world and mission mode so type-0x28 VLOC creates a bona fide native object.
- `00406AB0` was only executed through its guard, not through full camera projection after the guard. No validated camera pose, viewport/raster frame, clipping or pixel accuracy is claimed.
- Other consumers at `004071D1`, `004457FB`, and `0046ECE9` dereference the field; inspect their null policies and lifecycle next.
- Native child-tree ownership and teardown of this particular `0x28` attachment remain unverified, including reference count and repeated registration/camera-mode changes.

**Recommended experiment:** Re-run original top-level `004AD6F0` with appropriate retail status bit/mode, track `004AE000` VLOC callback at its genuine resource-dispatch entry, execute native class registration and follow real active-world/camera mode. Then compare original camera view matrices/frustum, not synthetic values.
