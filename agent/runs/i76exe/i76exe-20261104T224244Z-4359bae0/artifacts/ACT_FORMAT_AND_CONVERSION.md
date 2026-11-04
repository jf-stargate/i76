# ACT layout and palette conversion

Binary-static and retail-corpus evidence. All36 resolved selected ACTs are exactly768 bytes, hence256 three-byte entries, with maximum channel byte255. The remaining selected name t013_16.act is unresolved. No size trailer or wider ACT variant was observed in this selected set; retail WRLD copies768 bytes without checking length.

## Channel contract and precision

ACT source `P[3*i+0..2]` is copied unchanged to raw mirror004FA170. Palette callbacks copy it to context+E8. GDI PALETTEENTRY fields are populated in the same order as peRed,peGreen,peBlue, flags4; the hardware RGB-mask builders map byte0 to red mask, byte1 to green, byte2 to blue. These consumers establish the main ACT **RGB8** contract. There is no six-bit→eight-bit multiplication in this path, no “auto” choice based on max<=63, and no BGR swap before these consumers.

A separate helper00476DB0 constructs an8bpp DIB and writes the raw mirror's byte0/1/2 directly into RGBQUAD blue/green/red slots (00476E06..1B). This helper therefore has a **different channel interpretation at that API boundary**. Do not silently repair its observed order or generalize it to all ACT consumers. Its execution/visual role was not measured; this static discrepancy is retained explicitly.

## Correction and timing

00479860 builds ten256-byte component lookup rows at006095A0..00609FA0. Gamma-like exponents are `[0.8,0.9,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.5]`. It forms reciprocal exponent, normalizes byte value by1/255, invokes imported power helper004BA2B6, multiplies255, and converts through004BA090 (import thunk). The mathematical intent is `G[k][v] = integer_convert(255 * pow(v/255, 1/exponent[k]))`. Exact imported-CRT/x87 boundary behavior is not validated by the model; this equation is not a bit-exact cross-platform pow specification. Constants and original instructions are evidence, not captured runtime LUT outputs. Initialization call is00402DA9.

004797F0 selects row by explicit argument when>=1, otherwise low8 bits of00654B8C; values outside1..10 become3. Row address is006094A0+256*k. It applies the LUT independently to all three unsigned bytes for indexes `start <= i < end`. The callbacks pass explicit0. Slot3's intended exponent1 is the neutral/default setting. Raw mirror004FA170 remains uncorrected. 00479970 later copies that mirror to a local palette, applies selected correction over a bounded index interval, and calls the separate callback at context+0x408. A later palette update is not necessarily a repeat of the initial full ACT/LUM operation.

Software callbacks correct before display/LUM setup; hardware callbacks build display remaps and LUM first, then correct their context. See PALETTE_CALLBACKS.md for exact ordered contracts. The model accepts an explicit256-byte LUT so tested application semantics do not rely on an invented CRT replacement.

## High-color conversion

0042D800 consumes three channel masks at format+0x10/+0x14/+0x18 and a16-bit alpha/reserved value at+0x1C. For nonzero contiguous disjoint masks of width `w<=8` with shift `s`, each channel contribution is `floor(channel*2^w/256)<<s`. The implementation's accumulation loops store before increment; this is high-bit truncation, not rounding `channel*max/255`. Contributions add; result is narrowed to16 bits. If result==0, substitute the low set bit of the blue mask when the supplied alpha word==0, otherwise0; OR alpha word. Finally output[255]=0. 0042D6A0 uses this for00608980 and00608460 according to device state;00608408==8 selects palette submission instead.

00434410's plugin high-color path uses fixed masksF800/07E0/001F (RGB565), forces output[0]=output[255]=0, and copies256 words into the structure rooted at0052B91C after its count word. These are actual reserved display values. A separate optional0x20000-byte pixel translation resource and native plugin upload behavior are outside the modeled conversion branch; do not substitute TBL/LUM for that table.

## Reserved indexes / alpha boundary

Software callback entry0 is black; hardware context entry0 starts(1,1,1). Raw ACT stays unchanged. Nearest-color search excludes index255. TBL source row255 becomes identity, so source255 preserves the existing indexed destination in those composition operations. High-color blit0047AA50 selected modes explicitly skip source255; palette conversion reserves output255=0. These are consumer-specific transparency/reservation facts, **not** universal alpha for every ACT index255, black index, or magenta index. No executable evidence here authorizes historical exporter black/magenta heuristics as the game's alpha rule.
