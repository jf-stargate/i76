# Original Interstate ’76 software renderer — bounded technical contract

**Status:** accepted bounded renderer reference under merged [PR #79](https://github.com/jf-stargate/i76/pull/79) and its [historical promotion](../../../agent/promotions/rnd_software_renderer_20261031.md); the **bounded original palette/shade extension is accepted** via merged [PR #84](https://github.com/jf-stargate/i76/pull/84) and its [promotion decision](../../../agent/promotions/rnd_original_shade_column_20261031.md). **Track:** retail `i76.exe` (`i76exe`); advisory RND, GEO, OBJ, VEH and RES. **Original reference baseline:** protected `main` at `6d151459f92b75aaadd5221dc8edd8e4776651ff` (2026-10-31); **palette extension documentation base:** `3f06c23744765a5b209e4363add0a28853371f2a`. The earlier reference reconciles merged PRs [#66](https://github.com/jf-stargate/i76/pull/66), [#70](https://github.com/jf-stargate/i76/pull/70), [#73](https://github.com/jf-stargate/i76/pull/73), [#75](https://github.com/jf-stargate/i76/pull/75) and [#77](https://github.com/jf-stargate/i76/pull/77). The new bounded source-backed evidence is merged [PR #81](https://github.com/jf-stargate/i76/pull/81).

**Claim boundary:** the positive path consists of **original retail x86 instructions executed under Ghidra EmulatorHelper with substituted services**, not a continuously executed Windows/WinMain frame. It starts from authentic stock-bus VCF/GEO bytes and controlled camera/vehicle poses; produces original work records, projection, draw commands/edges/spans and **210 original 8-bit pixel writes**. **In PR #77** those pixel bytes come from an externally supplied *synthetic* shade table; **in PR #81** original instructions construct **256 shade entries in just one color column** from authenticated `m02.act` data installed in a controlled context, and 210 indexed stores consume one such entry. The producer does **not** naturally return or generate all 65,536 bytes. GEO-time original material-color binding, original ACT/LUM selection, numerical CRT service and true RGB output remain unestablished. Neither complete image fidelity, rendered M06 terrain, authentic textures, full original frame, hardware-x87 parity, nor a maintained renderer has been demonstrated. Every count/value below applies to the declared fixtures. [Evidence limits](#evidence-classes-and-constraints), [palette dependencies](#6-source-backed-original-shade-column-and-indexed-raster-consumption) and [open gates](#services-ownership-limits-and-deferred-claims) are part of this contract.

## Evidence classes and constraints

- **O — original-executed:** retired retail instructions, register/byte-store chronology or original return in the cited Ghidra run. Authenticated source bytes are still *emulator* evidence, not a retail Windows process.
- **S — binary-static:** retail instruction/dispatch/constant audit with PE/GZF byte matching; does not establish the path executed in the positive case.
- **D — independently derived:** numerical reconstruction or verifier result from the emitted data, with stated rounding tolerance and fixture domain; not an additional original instruction.
- **X — externally supplied:** test harness inputs, allocations, resources, math/CRT/OS/texture services or diagnostic data. Do not attribute supplied bytes to original code.
- **U — unresolved:** no accepted execution/provenance for the proposed general behavior.

**Authenticated private input identities** (recorded, not rehashed by this documentation pass): `i76.exe` MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`; `I76.ZFS` SHA-256 `0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d`; private annotated Ghidra 12.1.4 program `i76_mission_v97_verified_names`, baseline SHA-256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`. See [PR #77 manifest](../../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/manifest.json) and [provenance](../../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/evidence/provenance.json). Original binaries, GZF and full private traces are not present in this public repository.

In the integrated stock-bus fixture: selected camera root `26000000`, distinct unselected target root `26100000` (orientation +90°, target Z=+50), target registry entry `005428A8`, active world root `00542830`, persistent camera/view `004C2730`. The camera callback `00406AB0` runs twice; target position, active camera inputs, 640×480 viewport/color mode 2, `0.016` frame delta and far scan bound `4095` are controlled **X** inputs. Target Z=-50, empty world and camera-only are negative controls. Two direct camera invocations are not native scheduler integration. [R70][r70] [S70][s70]

## 1. World ownership and original work-record lifecycle

The original `0045EBD0` constructor, `004AD6F0` VCF entry and `004572B0` registration create separate selected and unselected stock buses. Original `00457FF0` iterates the registered world through `00458086` and produces a **kind 6** record for the target, using `00490590` and original bucket insertion `0048FE10`. Original `0048FAC0` subsequently consumes that *same* record via `0048F4C0`, `0045D530`, `0045CBE0`, `00471FD0`, then clears bucket state with `0048FCFE/0048FD07/0048FD10`. No producer queue node, owner, head or bucket index is host-authored. Original arena constructor `0048F9B0` issues five allocation requests (370000, 128000, 49152, 49152, 2880 bytes); allocator backing is **X**. The 4096 buckets are 12 bytes each. World registry `00542830` is **not** class dispatch head `0054B204`. [R66][r66] [R70][r70] [E70][e70]

| Kind-6 record field (byte offset) | Original PC and measured meaning | Class, scope |
| --- | --- | --- |
| `+0x0C` DWORD | `00458677` stores kind `6` | **O** original produced |
| `+0x14` DWORD | `0048FE10` insertion links to next record; in integrated positive points to kind-10 `38015584` | **O**, linked after first insertion |
| `+0x1C` DWORD | `00458688` stores target root `26100000` (single-bus producer `26000000`) | **O**, world-object owner |
| `+0x20/+0x24/+0x28` float32 | classified view-space point from original camera/frustum computation | **O** values; geometric label **D**, exact in [R66][r66] |
| `+0x2C` float32 | registered target radius | **O** sample; sphere interpretation **D** |
| `+0x30` DWORD | measured mode/priority selector `0`; **not** bucket index | **O** value, semantics limited |
| `+0x34` DWORD | measured flags `0x100` | **O** value; other bits **U** |
| `+0x38` DWORD | pass selector `0` in real root record (not synthetic consumer `1`) | **O** |
| `+0x3C` DWORD | cache state `0` for this kind | **O** sample; other lifetimes **U** |
| `+0x40` DWORD | `00458690` stores registry entry `005428A8` | **O**, **kind-6 only** |
| `0x44` total bytes | `004586C4` cursor movement; size table `004FACF8` = `0x28 + 0x1C` | **O/S**, fixture |

The positive PR #66 *single-root* record was `3800AAA0`, owner `26000000`, registry `00542830`, bucket 48; the integrated PR #70 *two-root* record is `38015540`, owner `26100000`, registry `005428A8`, bucket 44 at `3808F0A0` (table base `3808EE90`). These **are different allocator environments**; record addresses are not retail-global constants. The integrated consumer sees the same `38015540` and persistent view `004C2730`, then clears head, tail and count and resets cursor. The original `0048FE10` depth-based bucket assignment, not record `+0x30`, owns bucket selection. [R66][r66] [R70][r70]

**Kind 10 is not kind 6.** An initial camera-owner headlight scratch record at `38015540`, depth -5, is rejected without bucket membership or cursor advancement; the next accepted kind 6 *reuses that address*. A distinct accepted target kind-10 record at `38015584` uses 0x74 bytes, owner `27006600`, dispatches through `00490640` with a separate eight-vertex wrapper; original consumer clears kind-10 `+0x3C` at `0048FCCD`. Kind-10 `+0x40` belongs to its matrix, **not** the kind-6 registry pointer. Selection and transient scratch states are not evidence of corruption. [R70][r70]

## 2. GEO traversal, 24-byte projected vertices and dispatch

The integrated original kind-6 consumer uses record substructure `3801555C` at `0045D530`; `0045CBE0` traverses target child `27006800` with original GEO object `36003CD0` sourced from `xb11bdym.geo`. The GEO contains 16 source vertices and five parsed four-corner sections. The original run submits two nonempty quads through `00471FD0` in native depth-tree order. Source vertex bytes at GEO offset `+0x24..+0xE3` hash `31d85d852950cc079175612da560b3aa0054ac187d1cf8a3fd435e19fff55468`; the original material lookup reports `V1 MD RT.MAP`, but VQM/M16 acquisition returns **X null**, so original fallback emits **untextured** wrapper flags `0x101`. This proves neither texture decoding nor authentic material appearance. [R70][r70] [E70][e70]

| Dispatch site / address | Original outcome and limit |
| --- | --- |
| `00471FD0`, clip call `004720A8`, clip table `004F9538` | **O** wrapper masks flags to `0x1FF` and uses `0x101 → 0047C8D0` for two kind-6 quads |
| `0047C8D0`, original RET `0047C92F`, return `004720AF` | **O** four vertices each; 24-byte source/destination stride; projected output `+0x00` screen X, `+0x04` screen Y, `+0x08` reciprocal Z, `+0x14` copied attribute; `+0x0C/+0x10` untouched, **not proven UV** |
| Secondary clip call `00472145`, return `0047214C` | **O** `0x101` bounds fallback clears bit `0x100`, invokes original `0047BF00` at index `0x01`; no actual plane intersection occurred |
| Draw call `004721AC`, draw table `004F8D38` | **O** index `0x01 → 0047CE40`, invoked twice and returning to `004721B3` in #75 |
| Kind-10 initial `0x80` | **X** initial `0047BF00` copy substitute and `0047D110` draw substitute; no native kind-10 draw claim |
| Textured pair at index `0x15` | **S** `0047C2F0/00487EA0`, with eventual callback `00487480`; **not** an executed textured positive case |

**Correction to the #70 service ledger:** in that harness the interception predicate was `pc == selectedClip`. In the kind-6 secondary call, `selectedClip` is `0047C8D0`, so secondary `0047BF00` was **already original**, not a supplied polygon-copy routine. #73 records its actual entry/return; #75 removes the `0047CE40` substitute. Earlier intercepted-draw results remain limited to their own run. [R73][r73] [S73][s73]

For projection, **D**, `x_screen = cx + x_view*sx/z_view`, `y_screen = cy + y_view*sy/z_view`, `q=1/z_view` with source world→view row-vector transforms. Original `0047C8D0` performs the stores; independently derived arithmetic agrees for eight vertices with absolute tolerance `2e-5` and relative `2e-6`. First output: `(232.3985595703125, 312.606689453125, 0.021972518414258957)`. The original wrapper descriptor at `005DCEC0` had zero first extents in #73; fallback did **not** demonstrate working raster ownership. Float tolerances are not hardware-x87 parity. [R73][r73] [N73][n73]

## 3. Original 96-byte draw commands, 32-byte edges and interpolation

With original workspace startup thunk `00473620 → 004736B0` called explicitly, and CRT allocation/delete **X** services, original `0047CE40`, `00472DF0`, `00472EE0`, `00472F20`, scanline `00473670/00473960` and inverse `0048D140` execute. The original command arena is `[3E0014A0,3E0114A0)`. `0047CE78/0047CE8E` reserve two **0x60-byte** commands downwards at `3E011440` and `3E0113A0`. Four original **0x20-byte** edges follow at `3E011420`, `3E011400`, `3E011380`, `3E011360`. Addresses are deterministic fixture allocations, not fixed executable globals. [R75][r75] [E75][e75]

| Command byte offset | Original PC / ownership and observed value | Class |
| --- | --- | --- |
| `+0x00` | `00472EEA`: 32-bit call color/control `0` | **O** field, **X** caller argument |
| `+0x04` | `00474234`: deferred list link when *next* command appended; finalizer terminates tail | **O**, lifecycle-dependent |
| `+0x08` | `00472EEE`: callback pointer `0047CB00` | **O** |
| `+0x18` | `0047CF68`: float32 shade-plane constant | **O** values, gradient meaning **D** |
| `+0x1C` | `00472EF5`: zero/control | **O**, other semantics **U** |
| `+0x20/+0x24` | `00473FAB/00473D8F`: left/right edge-chain heads | **O** |
| `+0x28` | `00472EF8`: initial `-1`; `0047324F`: current/final pending packed span | **O** |
| `+0x2C` | span-list base, zero until finalization | **O** observed state |
| `+0x30` | `00473FFF`: preliminary Y extent (2/12); at finalization becomes last reserved span-slot pointer | **O**, phase-dependent |
| `+0x34` | `00472F13`: serial `4/8` | **O** |
| `+0x38` | deferred scanline/bucket link | **O** write; complete semantics **U** |
| `+0x58/+0x5C` | `0047CF9D/0047CFA0`: float32 X/Y shade gradients | **O**, **D** arithmetic |
| Other command words | No general contract inferred from padding/unchanged zeros | **U** |

Each edge is populated by **original `00472F20`**, not a host-provided rasterizer:

| Edge byte offset | Observed meaning | Scope |
| --- | --- | --- |
| `+0x00` | fixed-point X | **O** stored, **D** checked integer conversion |
| `+0x04/+0x08` | linked-list pointers | **O** |
| `+0x0C` | owning 0x60 command pointer | **O** |
| `+0x10` | initial integer Y | **O** |
| `+0x14` | copied reciprocal depth | **O** |
| `+0x18` | fixed-point X increment per row | **O**; independently computed **D** |
| `+0x1C` | exclusive terminal Y | **O** |

Original workspace startup creates ten scanline arrays at capacity 128; original growth increases to 512 with **X** allocations/free. Source-backed commands cover Y intervals `[313,315)` and `[315,327)`. The original 18 inverse-matrix float32 words and six shade-plane float32 words match the independent, spill-aware float32 computation bit-for-bit **only for this corpus**; ideal infinite-precision constants 8064 differ from measured `8063.3154296875` and `8063.84619140625`. Original x87 intermediate/spill behavior is not generalized or independently reproduced for arbitrary scene polygons. [R75][r75] [N75][n75]

## 4. Native packed spans and deferred callback boundary

The original finalizer `00473640 → 00474380` and incremental helper `00472FD0` generate original packed spans; the **observed** writer is `00473236`, with accumulator store `0047324F`. `00474270` is a **static alternate emitter**, not the writer reached in this case. The on-wire 32-bit packed span is **D** decoded from native writes as:

```text
packed = (x << 21) | (length << 10) | y
x      = (packed >> 21) & 0x7ff      (11 bits)
length = (packed >> 10) & 0x7ff      (11 bits)
y      = packed & 0x3ff             (10 bits)
```

In this fixture, **O** gives 14 scanlines, `x=233`, `length=15`, `y=313..326`; span lists start at `3E011354` and `3E011320` with `FFFFFFFF` sentinels. The last span for each command remains in command `+0x28`, whereas `+0x30` points to its reserved (still-zero) destination. Thus the state at #75's **pre-instruction** `0047CB00` boundary consists of *buffer plus pending command word*, not a falsely complete buffer. #77 executes **original `0047CB2F`** twice to copy each pending span into its slot, then finishes both callbacks. These two stages reconcile without altering either immutable run. [R75][r75] [R77][r77]

## 5. Thirteen-DWORD surface descriptor and indexed pixel writer

PR #75's inherited descriptor at `005DCEC0` had zero pitch/base and would calculate first destination `000000E9`; #75 **stopped before the first callback instruction** and did not return the finalizer. PR #77 separately invokes **original `00474C60(dst,width,height,external_base,mode)`**, using `dst=005DCEC0`, `640,480,0,0`. The original routine requests `width*height+32 = 307232` bytes at import `000C0FFE` (caller `00474CA9`); only **X** pointer `3F000000`, sentinel bytes `A5` and guards `CD` are supplied. Original `REP MOVSD` at `00474D32` copies **13 DWORDs (0x34 bytes)** into the descriptor. The zero heap handle is accepted solely by this diagnostic service. This does **not** recover original OS heap/device creation, ownership chronology or surface locking. [R77][r77] [F77][f77]

| Descriptor byte offset (DWORD) | Value in 640×480 positive | Exact source anchor and meaning | Class |
| --- | --- | --- | --- |
| `+0x00` (0) | `00000280` = 640 | `00474CE3`, byte pitch read by `0047CB0C..0047CB21` | **O** |
| `+0x04` (1) | `200001E0` | `00474D17`, flags; bit semantics **U** | **O/U** |
| `+0x08` (2) | `00000000` | `00474CF3`, caller mode | **O**, input **X** |
| `+0x0C` (3) | `00012C00` = 76800 | `00474D09`, `width*height/4` | **O/D** |
| `+0x10` (4) | `00000000` | `00474CED`, `width*height mod 32` | **O/D** |
| `+0x14` (5) | `3F000000` | `00474CBA`, aligned byte base read by callback | **O** field, pointer **X** |
| `+0x18` (6) | `3F000000` | `00474CB1`, raw allocation reference for release | **O** field, pointer **X** |
| `+0x1C` (7) | `00000000` | `00474C22`, X byte offset | **O**; offset 4 in **X** variation |
| `+0x20` (8) | `00000000` | `00474C22`, Y row offset | **O** |
| `+0x24` (9) | `0000027F` = 639 | `00474D11`, inclusive X maximum | **O** |
| `+0x28` (10) | `000001DF` = 479 | `00474D12`, inclusive Y maximum | **O** |
| `+0x2C` (11) | `00000001` | `00474CFC`, allocated-backing ownership state; teardown **U** | **O/U** |
| `+0x30` (12) | `00000000` | `00474C22`, meaning **unresolved** | **O/U** |

Original `0047CB00` reads pitch, offsets and aligned base at `0047CB0C..0047CB21`, and calculates the **byte** destination for each span at `0047CB6D/0047CB7C/0047CB8A`:

```text
destination_byte = aligned_base + pitch * (y + y_offset) + x + x_offset
```

This is **D** arithmetic recovered from **O/S** dataflow; offsets are byte contributions (no DWORD multiplication). The positive 640×480 buffer is `3F000000..3F04AFFF`, 307200 writable bytes, top-down pitch 640. Original `0047CB2F` completes the two pending spans. The original shade lookup `0047CC55` indexes the **X-supplied** 8192-byte diagnostic table at `0061B2A0`; a measured shade mask `1F00`, command color 0 and table index 7936 produce output byte 31. Original `0047CC62` (`MOV BYTE PTR [EDI],AL`) retires **210 byte stores**, one at each x=233..247, y=313..326. Both `0047CB00` callbacks return at original `0047CE38`, and the finalizer returns. Other statically authenticated unrolled writer PCs were not taken for these length-15 spans. The only original-executed output **in PR #77** is this **8-bit indexed diagnostic pattern**. [R77][r77] [F77][f77] [E77][e77]

The diagnostic table is **not retail-provenance data**: `table[i] = ((i & 255) + (i >> 8)) & 255`, SHA-256 `9208ae951af7fe2624047061396611af79b718114d45bb918acf20ce1e0a6a7e`. **In #77**, original palette producer `004791E0` was separately entered but blocked at original `004BA090 →` imported float-to-integer `000C0BFC`; the input palette was not authenticated in that run. The later #81 experiment preserves this raw failure but separately supplies a narrowly bounded numerical service and authenticated source palette bytes. [R81][r81] [S81][s81] Original heap initializer `00474C10` stopped at imported `HeapCreate` `000C0FE2`. Static release path `00474D40` was **not** exercised. The table, backing allocation and initial `A5` bytes belong to the **harness**; final 31 bytes belong to the **original pixel-writing instructions using that table**. No retail palette colors, color fidelity or complete image may be inferred. [S77][s77] [R77][r77]

## 6. Source-backed original shade column and indexed raster consumption

Merged PR #81 [findings][f81] and the [accepted bounded promotion (PR #84)](../../../agent/promotions/rnd_original_shade_column_20261031.md) extend #77's diagnostic result **without retroactively changing it**. This is still **O original-instruction emulation**, with **X** palette selection/installation, host numerical services and raster allocation, and **D** independently checked recurrence. The 797 instruction rows checked against the authenticated retail PE are **S** provenance for the inspected code; they are not an independently executed full game. No new private Ghidra reproduction was performed by this documentation pass. [R81][r81] [N81][n81] [V81][v81]

### Producer ownership and precise memory contract

| Byte range / entry point | Original instruction operation and fixture result | Evidence classification / boundary |
| --- | --- | --- |
| `004791E0`, context `+0xE8`; copy `00479202` to `006432E0` | Original `004791F7` computes source `+0xE8` and original `REP MOVSD` copies 768 ACT palette bytes (256 RGB triplets). | **O** copy; **X** controlled `0x500`-byte context at `3D000000` and source installation; retail palette selection **U** |
| `0059B388..0059BB87` | `00479220` initializes 512 DWORDs containing squared signed differences `-256..255` if the cached pointer `0059BB88` was absent. | **O/S** static memory and measured initial hash; no heap-ownership claim |
| `0063B2E0..006432DF` | `0047923E` initializes 32,768 cache bytes to `FF`; `004796A0` searches/caches nearest palette results, with cache result store at `00479733`. | **O/S/D** first-encounter cache by quantized 5/5/5 RGB; original search only palette indices `0..254`, first minimum wins ties |
| `[0061B2A0,0062B2A0)` | **65,536-byte static image-owned table**, index `shade*256 + color`; null producer second argument computes, while nonnull branch `0047924C` copies `0x10000` bytes (`0x4000` DWORDs). | **S/O** branches/extent; only one calculated color column observed, supplied LUM branch not exercised |
| `004793A4`, `004794AF`, `004794ED`, `0047950B` | For **color 0**, exactly 24 original stores to shade rows `31..8`, eight to rows `7..0`, 112 copies of row 31 into rows `32..143`, and 112 copies of row 0 into rows `144..255`: **256 original stores**. | **O/D** full color-0 column only; deliberate stop **before `0047951E`**, not original producer `RET` |
| `0047CC49/0047CC55`; writer `0047CC62` | Callback masks shade with `0x1F00`, combines command color, reads `0061B2A0 + index` and writes the returned **indexed byte**. | **O** two callback returns and 210 stores; read window 32×256 = **8,192 bytes**, **not** full producer ownership |

The source was authenticated uncompressed retail `m02.act` from `I76.ZFS`, **768 bytes**, ZFS record offset `23736814`, recorded source SHA-256 `d1f57fdef1029e2f2b41d25c2db52f641ada6d55b89342970c50bc49bd9bccb8`. Its first RGB entry was `(1,1,1)`; the run **directly installed it into a harness-owned palette context** without running retail selection or entry-zero normalization. The exact `m02.act` bytes are *authentic resource input* but are **not proven to be the palette selected for the stock-vehicle scene**. Neither table entries nor output pixels were host-written in the #81 positive case; setup services, scratch and backing memory remained external. [I81][i81] [F81][f81] [S81][s81]

### Native shade calculation versus supplied numerical service

Original `004796A0` squared-distance nearest-palette lookup executed **inside the producer**, with search candidate entries `0..254`, first equal-distance minimum, and lookup cache keyed by the first 5 bits of each quantized RGB channel. The original 32 computed shade levels use two float32 recurrences (24 + 8); a standalone verifier checks float32 spill/storage points, 96 conversion operands, 32 nearest-color calls, cache behavior, 256 original-store chronology and final column bytes. The eight **distinct table index values** are `0, 43, 59, 249, 250, 251, 252, 254`. These are palette indices, not observed RGB pixels or evidence of physical lighting accuracy. [R81][r81] [V81][v81] [N81][n81]

Without an external service, original path `00479327 → 004BA090 → [004BC27C] → 000C0BFC` fails at the unmapped imported **MSVCRT.dll `_ftol`**. For the serviced positive, the host decoded a measured finite x87 ST0 value, truncated toward zero, popped ST0, returned signed EDX:EAX and advanced ESP over the return address while keeping the original control word `0x037F`. The run retained before/after states for **96 calls** (e.g., ST0 `2.5499999430030584` → `2`), and independently verified their stack/FPU/integer effects. This is **X numerical assistance**, not original CRT execution or unmeasured NaN/overflow/FPU exception parity. Missing-palette input was intercepted by a harness guard at `00479202`; that is not a retail input validator. [C81][c81] [S81][s81] [V81][v81]

### Exactly what the original raster consumed

The original stock-bus geometry/view/draw-command and **14-span** inputs were checked against #77's unchanged baseline; no new scene polygons were manufactured. All **210** `0047CC55` reads used **table index 7936 = (31 << 8) + 0**, hence only shade **row 31, column 0** (one of the 256 native-generated entries). All **210** `0047CC62` stores wrote **indexed byte `0`**, not all eight distinct table values: X=233..247, Y=313..326, pitch=640, external base `3F000000`. Both callbacks returned. The independently checked 307,200-byte sentinel-plus-pixels frame SHA-256 is `caf6c543352cfa5ebbaf808a36215a662389ff2f524a62e90ab73301960c6ff7`; the guarded backing remains **X**. [N81][n81] [V81][v81] [S81][s81]

Compare the **same original indexed writer** in #77: 210 byte **31** stores came from the **X-supplied 8,192-byte diagnostic table** `((i & 255) + (i >> 8)) & 255` (SHA-256 `9208ae951af7fe2624047061396611af79b718114d45bb918acf20ce1e0a6a7e`). #81 does **not** demonstrate that the #77 diagnostic table represented all 65,536 producer bytes. The larger original table and smaller masked callback read window are complementary memory facts; the original source-color and final-pixel values remain fixture-specific and different between runs. [R77][r77] [R81][r81] [F81][f81]

### Original ACT/LUM and material binding not yet executed

Binary-static callers of `004791E0` include `0047615B`, `0042DC36`, `00434606`, `00475AC4` and `0048DD56`; historical annotations are not original source names. Original `004B8A10` reads ACT/LUM names from WRLD `+26/+33`, copies ACT to `004FA170` and dispatches through `005DD2C4`; `0048DC60` updates context `+0xE8` and calls `004791E0`, with differing entry-zero normalization in other update paths. Original `00478B80` can overwrite a complete column through a separate integer ramp. **None of those selection/normalization/update pathways was executed as the palette setup in #81.** [R81][r81] [X81][x81]

GEO constructor `00446C90`, call `00446F44`, passes source GEO section triplet `+8/+9/+A` to nearest lookup `004796A0` and stores its index at runtime section `+8`. Crucially, #81 retained the **inherited GEO-time substitution** for that helper (returns `0`), while running **the original helper within shade production**. Therefore the **command color 0** used for 210 stores is controlled, **not verified authentic stock-vehicle material color**. TMT names, VQM/M16 and textures do not gain RGB semantics from this result. To establish authentic scene color, a later original-instruction experiment must prove WRLD-driven ACT/LUM selection/backend/context installation, original GEO material-color translation without substitution, propagated distinguishable command colors and their table read/write lineage; full-table return, overwritten columns, textures, device/frame integration and RGB fidelity remain additional requirements. [F81][f81] [S81][s81] [X81][x81]

## Verification and recorded controls

| Run / evidence | Scientific checks recorded, method and bounded implication |
| --- | --- |
| [#66 producer][r66] | 196 verifier checks; original store/ownership and behind/empty + separately fresh byte-identical repeat; only isolated producer, not consumer |
| [#70 integration][r70] | 1,402 source-backed checks, same record and view through consumer/GEO; camera-only/behind/empty controls, fresh project repeat; no native draw |
| [#73 projection][r73] | 2,769 checks, retail dispatch and source numeric oracle; four deliberate corruptions rejected, native C8D0 and secondary BF00, not clipping intersection |
| [#75 draw][r75] | 11,350 new native checks + 292 delegated source checks; two commands/four edges/14 spans, six corruptions rejected, fresh GZF finalizer repeat; **zero callback instructions/pixels in this run** |
| [#77 raster][r77] | 3,601 standalone positive checks + 85 checks in three rejected corruptions; 459 verified retail instruction rows, byte-identical fresh-GZF frame/trace/guards; same 210 stores shift four bytes when descriptor `+0x1C` is **X**-changed to 4; behind and absent-surface yield zero stores |
| [#81 source-backed shade][r81] | Original 256-store single column and two callbacks/210 byte-0 stores; 96 serviced conversions, 797 retail-PE-matched instruction rows, standalone source/recurrence/cache/pixel verification, missing-input/raw failure, rejected corruption and fresh-GZF exact repeat; **producer stopped before `0047951E`**, and GEO-time nearest remained substituted |

The main diagnostic surface hash is `83c3331612753d0ad64fe64d857a9b65715de102b210bbd24f3166e27b440f50`, changed output bytes 210; 16-byte guards on both sides remained `CD`. In the X-offset variation, all 210 stores shift to x=237..251 and buffer hash becomes `cd5629b589e239a672e07f43e962b9a77a65fe69a368c6b5d58cef31265a9689`. The absent-surface control stops before an unowned read at `0047CC25` (`000000E9`), not a completed callback. Independent verifiers use measured original shade-index registers but **do not rederive the full x87 shade-index trajectory**. Verification counts are checks, **not renderer coverage percentages**. [E77][e77] [C77][c77] [V77][v77]

## Services, ownership limits and deferred claims

Inherited **X** services remain essential: hash-checked retail resource extraction, OS/CRT heap and string helpers, unsupported trig/float-conversion, initial FS/SEH segment, selected ancillary lighting/palette/material/weapon routines, controlled camera/poses/viewport and depth-scan bound, zero-backed scratch, and null VQM/M16 texture service. #75 adds guarded CRT `operator new/delete` backing (91,148 bytes in four allocations, plus 128 guard bytes) and explicit invocation of original workspace initializer `00473620`. #77 additionally supplies 307232-byte framebuffer allocation and a synthetic diagnostic shade table. #81 replaces **that table input** with 256 original-written source-backed bytes in column 0, while still supplying palette selection/context installation, finite-range `_ftol`, inherited GEO-time nearest-color result and surface allocation. These are research scaffolds, **not authentic game services or maintained implementation**. [S81][s81] [S66][s66] [S70][s70] [S75][s75] [S77][s77]

**Explicitly deferred, requiring new separately accepted evidence:** (1) original WRLD ACT/LUM selection, backend context installation and normalization, original GEO material-color lookup without substitution, correctly propagated source material indices, full shade-table generation and natural producer return (rather than #81's one-col/host-`_ftol` boundary); (2) original `00474C10` heap/device/lock lifecycle, allocation ownership and executed `00474D40` release; (3) native kind-10 `0047D110` and textured `0047C2F0/00487EA0/00487480` positive cases with source-authenticated UV/texture pixels; (4) positive clipping-plane intersection rather than fallback only; (5) source-backed M06 terrain/environment contribution, complete viewable frame and two-scene differential; (6) normal original WinMain rendering schedule, selected-player physics/input and numerical hardware-x87 parity. The [RND-v1 acceptance contract](../../roadmap/subsystems/RND_ACCEPTANCE.md) still governs RND-RESEARCH/INTEGRATED/PRODUCT gates, none of which is claimed closed here. See [historical vehicle object model](../../../ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md) and [promoted VCF/GEO/TMT construction](vehicle_construction.md) for adjacent but separate ownership.

## Immutable evidence directory

- [R66][r66] / [E66][e66] / [S66][s66] — #66 original kind-6 producer, events and service ledger; [findings](../../../agent/runs/i76exe/i76exe-20261030T020552Z-41acec02/findings.json), [verifier](../../../agent/runs/i76exe/i76exe-20261030T020552Z-41acec02/scripts/verify_producer.py), [handoff](../../../agent/runs/i76exe/i76exe-20261030T020552Z-41acec02/artifacts/DOCUMENTATION_IMPACT.md).
- [R70][r70] / [E70][e70] / [S70][s70] — #70 same-state original consumer/GEO and kind-10 lifecycle; [findings](../../../agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe/findings.json), [verifier](../../../agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe/scripts/verify_integration.py), [handoff](../../../agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe/artifacts/DOCUMENTATION_IMPACT.md).
- [R73][r73] / [N73][n73] / [S73][s73] — #73 native projection and actual dispatch; [findings](../../../agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6/findings.json), [verifier](../../../agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6/scripts/verify_polygon.py), [handoff](../../../agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6/artifacts/DOCUMENTATION_IMPACT.md).
- [R75][r75] / [E75][e75] / [N75][n75] / [S75][s75] — #75 commands, edges, native span finalizer, ledgers; [findings](../../../agent/runs/i76exe/i76exe-20261031T011731Z-307babbf/findings.json), [verifier](../../../agent/runs/i76exe/i76exe-20261031T011731Z-307babbf/scripts/verify_draw.py), [handoff](../../../agent/runs/i76exe/i76exe-20261031T011731Z-307babbf/artifacts/DOCUMENTATION_IMPACT.md).
- [R77][r77] / [F77][f77] / [E77][e77] / [C77][c77] / [S77][s77] / [V77][v77] — #77 descriptor, native writer, diagnostic controls; [findings](../../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/findings.json), [verifier](../../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/scripts/verify_raster.py), [handoff](../../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/artifacts/DOCUMENTATION_IMPACT.md).
- [R81][r81] / [F81][f81] / [S81][s81] / [N81][n81] / [C81][c81] / [I81][i81] / [X81][x81] / [V81][v81] — #81 one source-backed original shade column and indexed consumption; [manifest](../../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/manifest.json), [findings](../../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/findings.json), [verifier](../../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/scripts/verify_palette.py), [handoff](../../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/artifacts/DOCUMENTATION_IMPACT.md), [new promotion](../../../agent/promotions/rnd_original_shade_column_20261031.md).

[r66]: ../../../agent/runs/i76exe/i76exe-20261030T020552Z-41acec02/artifacts/REPORT.md
[e66]: ../../../agent/runs/i76exe/i76exe-20261030T020552Z-41acec02/evidence/producer_events.json
[s66]: ../../../agent/runs/i76exe/i76exe-20261030T020552Z-41acec02/artifacts/SERVICE_LEDGER.md
[r70]: ../../../agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe/artifacts/REPORT.md
[e70]: ../../../agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe/evidence/events.json
[s70]: ../../../agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe/artifacts/SERVICES.md
[r73]: ../../../agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6/artifacts/REPORT.md
[n73]: ../../../agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6/evidence/numerical_results.json
[s73]: ../../../agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6/artifacts/SERVICE_LEDGER.md
[r75]: ../../../agent/runs/i76exe/i76exe-20261031T011731Z-307babbf/artifacts/REPORT.md
[e75]: ../../../agent/runs/i76exe/i76exe-20261031T011731Z-307babbf/evidence/draw_events.json
[n75]: ../../../agent/runs/i76exe/i76exe-20261031T011731Z-307babbf/evidence/numerical_results.json
[s75]: ../../../agent/runs/i76exe/i76exe-20261031T011731Z-307babbf/artifacts/SERVICE_LEDGER.md
[r77]: ../../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/artifacts/REPORT.md
[f77]: ../../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/evidence/field_provenance.json
[e77]: ../../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/evidence/raster_results.json
[c77]: ../../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/evidence/controls.json
[s77]: ../../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/artifacts/SERVICE_LEDGER.md
[v77]: ../../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/scripts/verify_raster.py
[r81]: ../../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/artifacts/REPORT.md
[f81]: ../../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/findings.json
[s81]: ../../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/artifacts/SERVICE_LEDGER.md
[n81]: ../../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/evidence/measurements.json
[c81]: ../../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/evidence/controls.json
[i81]: ../../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/evidence/input_provenance.json
[x81]: ../../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/evidence/retail_xrefs.json
[v81]: ../../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/scripts/verify_palette.py
