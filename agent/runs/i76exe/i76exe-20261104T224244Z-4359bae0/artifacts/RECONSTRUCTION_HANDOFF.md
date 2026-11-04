# Reconstruction handoff

These are candidate research contracts, not maintained implementation changes or renderer certification. Human acceptance and separate documentation reconciliation remain necessary.

Keep resource selection, raw data, initialized state and display state distinct. A suitable independently authored interface could expose owned `RawPaletteRGB8[256]`, `RawLUM[65536]`, `RawTBL[65536]`, `RuntimeShadeTable`, `RuntimeCompositionTable`, plus an explicitly selected display contract. These are handoff names, not recovered C++ classes. Preserve mission ACT/LUM/TBL names literally; do not synthesize miss16 ACT stems or silently repair missing t013_16.act.

Verified operations implemented by scripts/color_model.py:

- Exact-length ACT triples with unsigned8-bit channels, no auto scaling; optional component correction using an explicit256-byte LUT.
- Full WRLD callback buffer/timing model for all four selected callbacks; supplied LUM copied verbatim. Actual device calls and partial palette updates are unsupported.
- LUM lookup with explicit row offset, and the specific0x1F00-masked accumulator contract; integer runtime-column modification with endpoint division32 and extension rows.
- Original nearest-color search/cache integer contract, including first-query reuse, earliest ties, index255 exclusion.
- TBL initialization with row255 identity, ordered source/destination composition, auxiliary tables and safe temporary column255 patch/restoration.
- Contiguous disjoint uint16 display-mask conversion with bit truncation, reserved last entry and explicit backend options. No native plugin/API side effects or PCF conversion are simulated.

Missing complete computations are deliberately unsupported: null-LUM x87/CRT generation; gamma-LUT CRT power generation; upstream float shading/interpolation; external plugin pixels; optional PCF/native16-bit texture decoding and full dispatch. Do not replace these with guessed appearance while reporting faithful behavior. Static equations and precision boundaries are recorded in the ACT/LUM reports.

Synthetic tests deliberately distinguish at least these plausible incorrect implementations:

| Incorrect interpretation | Counterexample |
|---|---|
| Reverse LUM axes | Asymmetric synthetic row+3*column, row200/index129 |
| Reverse TBL axes | Synthetic5*source+destination, source7/dest19 gives54, reversed gives102 |
| Use serialized TBL unchanged | Synthetic row255 differs; initialization installs all256 identity values; retail18 rows differ at250..252 positions |
| Scale all ACT bytes as six-bit / swap channels | Synthetic RGB(1,63,255), RGB565 output differs on channel swap; raw255 remains255 |
| Call same palette processing unconditionally | Synthetic invert LUT makes hardware pre-correction samples/display inputs differ from software, despite equal later channels |
| Search nearest color anew for every query | Two colors in one5-bit cache cell return first-hit result on second query |
| Interpolate32-row LUM endpoint using divisor31 |255→0 gives row31 value8 under original divisor32 |
| Treat all bright/black colors as transparency | Tests use explicit reserved-index operations, not color resemblance |

All model validation is synthetic and/or retail structural observation. It is not original-instruction execution or native device validation. Safe bounds and finally restoration are independent authoring policies, not proof of the original's malformed-input safety. `reproduce.py` rebuilds the private static export, authenticated corpus metadata, reviewed instruction checks and synthetic outputs into a new private directory; the exact private inputs are required.

Historical ref/material_format/i76_material_extraction_reference.md contains useful extraction choices but its palette “auto” scaling and black/magenta alpha are not an original runtime contract established by this evidence. The documented DIB channel-order discrepancy must remain separate from the RGB ACT/display contract pending native tests. Palette selection alone cannot stand in for shade, composition, correction timing and backend conversion.
