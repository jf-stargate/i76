# Palette callback selection and contracts

Evidence tier: original binary-static instructions and PE descriptor bytes. All addresses are retail VAs. No annotation was installed to turn missing baseline function definitions into functions; such targets were inspected through bounded instruction windows instead.

## Actual pointer initialization

005DD2C4 is **005DCEC0+0x404**, inside a 0x42C-byte context. At 00402EA6, 00476000 constructs the context returned through a local buffer. 00402EAB sets ECX=0x10B; 00402EB2 selects destination005DCEC0; REP MOVSD at00402EBA installs the complete context. Searching only direct stores to005DD2C4 misses this assignment.

Constructors write thirteen descriptor dwords starting at context+0x3E8. Descriptor word7 therefore lands at context+0x404. `descriptors_constants.json` gives exact table addresses, words, target fields and raw-region hashes.

| Constructor / selection | Descriptor | Type word | Callback |
|---|---|---:|---|
| 004761A0, selector argument outside0..3 | 004FA498 | 2 | 0048DC60 |
| 004761A0, selector argument0..3 | 004F9DC0 | 0 | 00475A30 |
| 0042D0C0 | 004EDE98 | 1 | 0042DBE0 |
| 00431500 | 004F0050 | 1 | 0042DBE0 |
| 00433DF0 | 004F1520 | 1 | 004345B0 |

00476000 tests00504BE8 (hardware raster request). If nonzero, plugin name005DD340 is compared case-insensitively with zglide.dll / zredline.dll / zpowervr.dll, selecting mode1 through004314C0→00433DF0; zdx5draw.dll selects mode0→00431500. Unrecognized plugin proceeds to software selection. With raster request zero and00504BF8 nonzero,0042D0C0 is attempted. Successful constructors return their context; failed hardware initialization reports a fallback and clears00504BF8, then uses software selection. Software calls004761A0 with selector5 when004F9F20==0, selector3 otherwise. These recover conditions, not measured stock runtime flag values or successful device creation.

The four nonzero targets above are all targets identified in the five executable descriptor tables. The whole-listing field-offset scan found indirect calls and unrelated0x404 offsets, not an additional direct callback assignment. This bounded static closure cannot exclude dynamically supplied or external code.

## Common calling contract

All four take five stack arguments, caller cleans20 bytes, return in EAX, ordinary cdecl-style ABI: `(context, start_index, copy_count, triplet_source, optional_lum)`. Source and destination copy offsets are both `3*start_index`; copy length is `3*copy_count`. The common correction helper is called with start and the **same third argument as an exclusive end**, not start+count. Full WRLD(0,256) avoids that partial-update discrepancy. Do not normalize it away in an emulator. Context palette occupies +0xE8..+0x3E8 (768 bytes); valid-device state is +0xE0. Descriptor type is +0x3E8. The model supports only the full WRLD update.

| Callback | Preconditions and forced entry0 | Ordered effects |
|---|---|---|
| 0048DC60 | Return0 if context+E0==0; entry0=(0,0,0) | Copy;004795A0 snapshots nearest-color state;004797F0 corrects context; build 256 PALETTEENTRY records, CreatePalette/SetPaletteEntries, Select/RealizePalette;004791E0 refreshes nearest samples and LUM; return1 |
| 00475A30 | Requires context+E0 nonzero and type0; otherwise return0; entry0=(0,0,0) | Copy; snapshot; correction;004791E0; build 256 palette records, force submitted entry0 black, device interface call+0x18; return1 |
| 0042DBE0 | No corresponding early valid-device gate; entry0=(1,1,1) | Copy; snapshot;004791E0;0042D6A0 submits/builds palette/pixel remaps;004797F0 corrects context afterward; return1 |
| 004345B0 | Same entry0=(1,1,1) | Copy; snapshot;004791E0;00434410 builds plugin display state; correction afterward; return1 |

004795A0 snapshots768 bytes to006432E0, initializes squared distances(-256..255), invalidates32768 nearest-cache bytes. 004791E0 repeats that setup using the context at its own call time. Consequently software LUM generation sees corrected context, hardware LUM generation/display conversion sees the earlier context. For a supplied LUM, bytes are copied independently of palette correction. Null LUM reaches generation in **every** callback that reaches004791E0; no null skip is established.

Callback success is not device-success aggregation. For example hardware callbacks return1 after invoking subordinate setup; their subordinate outcomes do not become a faithful transactional success signal. No complete display lifecycle is modeled.

Runtime high-color predicate00495060 tests005DD2A8==1, which is context+0x3E8==1. Pixel surface format at context+8 and global00608408 additionally select conversion paths. Palette-callback identity is backend-dependent and cannot be inferred from a miss8/miss16 mission directory alone.
