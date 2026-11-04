# LUM initialization, lookup axes and runtime modification

Evidence tier: binary-static plus selected retail corpus. All18 distinct mission-selected names resolve to18 distinct65536-byte payloads authenticated against I76.ZFS. Length is measured rather than assumed from an old tool. Every specimen has32 distinct256-byte rows. File names are m05.lum,m15.lum,t01..t13.lum,t15..t17.lum; t14 is not selected. All40 mode pairs resolve to the same LUM bytes; M14 differs only in name case.

## Supplied-resource path

004791E0 tests argument2 for null at0047923C/40. Non-null takes a16384-dword copy at00479242..4C into0061B2A0. It does not multiply ACT by LUM or interpret LUM as RGB bytes at initialization. It does not apply palette correction to supplied LUM bytes. ACT/context supplies nearest-color state separately.

## Lookup contract

The runtime table is byte-addressed. Direct software span reads establish:

`out_index = LUM[shade_row_offset + uint8(source_index)]`.

The palette/texture index is the low byte/column, not the row. Examples0047CC49 masks an interpolated accumulator with0x1F00 and0047CC55 reads a byte at0061B2A0+EDX+ECX; EDX is the zero-extended flat source byte. It adds signed integer step0059BBA0 to accumulator0059BC50 per pixel, then masks again. Negative/overflowing states are masked, not clamped to rows0..31. The reference model takes explicit uint32 accumulator and returns `LUM[(accumulator & 0x1F00)+source]` for this contract.

00485120 samples a byte from a decoded indexed texture at00485406, uses precomputed row offset0059BC50, reads LUM at0048540F, and writes the returned byte directly to destination00485416. At004852B1..CB it loads a binary32 shade input from the span object+0x18, adds double constant004FAF18 (6755399441055744), stores double to0059BC50, then masks its low dword with0x1F00. This is a bit-level float-to-fixed conversion idiom; the current x87 rounding environment is an input to exact results. It is not equivalent for arbitrary floats to `int(light)*256`. The model leaves upstream float interpolation/conversion unsupported and accepts the recovered row offset explicitly.

Other directly identified textured readers:00485CC0,00486860,00487480,00488220,00488E40,00489BE0,0048A870,0048B690,0048C320, plus0047CB00/0047CFC0 flat paths. Their byte accesses/owners are listed in table_references.json. They use unsigned sampled or flat indexes and return an index byte. Some establish a constant row before the inner loop; others mask a varying accumulator for each access. Do not impose one universal upstream shade-unit formula on all callbacks. No selected display callback performs a two-dimensional LUM read itself: callbacks copy or generate it; the span consumers establish the axes.

## Null-LUM generator (recovered structure; not executable model)

004791E0 first snapshots the current context's768-byte palette, builds squared-distance helpers, and invalidates nearest-cache cells. For each palette column0..255, it computes three normalized channel values using float constant bits8180803B (~1/255). All channels begin at float bits0AD7233C (~0.01). For rows31 down8 (24 iterations), it converts current channels*255 through imported004BA090, clamps each signed integer to0..255, chooses nearest palette index via004796A0, writes one byte, and advances each channel by a stored binary32 step `(normalized_channel - initial)*float_bits4A29253D` (~1/24.8). After24 advances, steps become `(1-current)*float_bitsB9236E3D` (~1/17.2); eight analogous iterations write rows7 down0. Channel states/steps are stored to binary32 at the demonstrated instructions, with x87 intermediates. After generation, rows32..143 repeat row31 and rows144..255 repeat row0. No new original LUM file is written.

004796A0's cache key is `((R>>3)*32+(G>>3))*32+(B>>3)`. On an empty cell(255 sentinel), it evaluates sum of three squared channel differences against palette entries0..254, retaining the earliest entry on ties. Distance uses the **unquantized first query** in that cell; later queries reuse that result. The process is order-dependent and is not the same as always finding the nearest color, nor searching a quantized cell center. This exact integer/cache portion is independently modeled and tested. Generator loop order is column-major then descending rows, which matters to cache reuse.

The report recovers arithmetic structure and constants; the standalone model deliberately raises unsupported for null LUM pending original-instruction/CRT validation of x87 narrowing, conversion, cache traversal and generated outputs as one complete operation. No Python floating implementation is claimed equivalent. Supplied-LUM use is completely modeled without that dependency.

## Later runtime writes

00478B80 changes one **column**, using low8 bits of first/last/column arguments. Initial accumulator=`first*65536+32768`; signed step=`trunc_toward_zero(((last-first)*65536)/32)`. For rows0..31, store bits16..23 and add step; then extend row31 through32..143 and row0 through144..255. It divides by32, not31, so the last active row need not equal the last endpoint.

The main loop calls00478B80(context,224,239,239) at004035EB..00403604. Thus even supplied raw LUM need not remain byte-identical through runtime. Its column239 is made an index ramp, not regenerated from ACT. The function is modeled with bounded buffers and explicit operands. Other aliasing/external writers are not excluded by this static inventory.

Retail observations: all18 raw LUMs already exhibit those extension-row equality patterns, but that agreement does not prove the null generator reproduced their bytes, their authoring provenance, or that runtime writes are absent. Bright/dark row behavior follows generator arithmetic; labels like physical lux, luminance units, or a universal illumination percentage remain unproved.
