# Software sampling and pixel operations

**O**: two authentic TMT/VQM/CBK connected fixture states, original full
00485120 and 004828E0 callbacks returning normally, with 296 total framebuffer
byte stores. **S**: polygon dispatch/gradient producers. **D**: independent
fixed-point address and indexed-output checks for the measured constant-q cases.
Full perspective precision and actual GEO-generated textured spans are **U**.

## Command and dispatch boundary

The callback's command begins with texture-header pointer +00. Span fields:
+28 pending packed span; +2C preceding span cursor; +30 final slot. Callback
entry copies pending +28 to [+30], then processes DWORDs from [+2C]+4 through
[+30] inclusively. A span packs `(x<<21)|(length<<10)|y`, with 11-bit X,
11-bit length and 10-bit Y. A one-span harness sets +2C to preceding slot,
+30 to next slot and +28 to the desired packed word. Zero length is not a
validated empty-span convention; a caller should submit no span instead.

Surface descriptor: +00 byte pitch, +14 base pointer, +1C X byte offset,
+20 Y row offset. Destination = base + (y+Yoffset)*pitch + x + Xoffset.
The tested descriptor has pitch64, no offsets and 4096-byte supplied backing.
Every original writer is checked inside that backing and all untouched bytes
remain 0xA5. This callback performs no destination clipping. Coordinate masks
wrap texture reads; they do not clip framebuffer writes. Upstream clipping and
span construction must guarantee valid destinations.

Static route: 00471FD0 dispatches prepare/draw using primitive flags and tables
004F9538/004F8D38. 004859E0 supplies 00485120 to 00472EE0; 00482FE0 supplies
004828E0 with mode2. 00472EE0 stores texture +0, callback +8 and initialized
span/control state. 004859E0 builds U/V/q planes using the selected triangle's
24-byte projected vertices: U at vertex+0C, V at +10, reciprocal depth at +8;
U/V scales are runtime width/height *65536. The callback name historically
contains “affine”, but 00485120 itself performs reciprocal/perspective division.
004828E0 uses affine fixed-point U/V without q division. Our callback entry and
span/gradient values are explicitly supplied; command construction and the
selected indirect call are traced statically, not executed in the fixture.
The earlier accepted textured 0x15 path selects 00487EA0→00487480, a distinct
varying-light callback; that is not silently substituted for 00485120 here.

## Coordinates and interpolation

Command +0C/+10/+14 store base U/V/q; +40/+44 are dU/dx,dU/dy;
+48/+4C dV/dx,dV/dy; +50/+54 dq/dx,dq/dy. Evaluate planes at span X,Y.
00485120 divides U,V by q (numerator constant1). U,V are in 16.16 texel units.
The initial and residual endpoints use addition of double bias
6755399441055744 and a stored-double low DWORD. With the supplied nearest-even
x87 control word this rounds to signed integer fixed-point values. The original
code's precision includes float stores and x87 intermediate state; portable
rewrites must not assume every intermediate is a float32 or simple integer cast.

For `n=length-1`, residual `r=n&15`, the first loop writes r+1 pixels. It computes
an endpoint r pixels ahead and a linear fixed-point delta using the reciprocal
coefficient table at 004F9D38. Remaining pixels are grouped into 16, with
perspective endpoints recomputed and bias16 conversion of per-segment deltas.
The exact static instructions and constants are published, but this run's
independent numeric oracle covers q=1, zero q-gradients and exactly representable
half/quarter-texel slopes. General varying-q rounding, zero/negative q, degenerate
planes and CPU x87 parity remain unvalidated. It would be wrong to describe the
whole callback as independently reconstructed from these cases.

At 004853D3..00485406 (and unrolled equivalents):

```
sx = SAR32(U_fixed,16) & (width-1)
sy = SAR32(V_fixed,16) & (masked_height-1)
texel = unsigned8(memory[row_cache[sy] + sx])
```

Negative fixed coordinates wrap by the mask, including fractional negatives
whose arithmetic shift rounds down. This equals modulo for power-of-two
positive dimensions; it is **not** general modulo for non-power-of-two shapes.
All 18 shapes decode correctly, but that does not mean each shape is suitable
for this wrapping sampler. The tested 64x64 materials cross negative edges.
Lengths 1/2/5/16/17/33 exercise scalar, pair and 16-pixel unrolled stores.
Every actual texel read address/index and subsequent table read is recorded;
its address must equal the independent coordinate calculation.

## Shade and indexed composition

00485120 takes command+18 constant shade, bias-converts it and masks low DWORD
with 0x1F00. It reads `LUM[row_offset + texel]` and stores that unsigned8 result.
Original scalar anchors are 00485406 sample, 0048540F table lookup,
00485416 store. The final fixture supplies shade15*256, not near-identity row7.
Example bus read: source address20801187 contains58, LUM0061C1DA contains254,
and original00485416 writes254 to framebuffer20500042.

004828E0 instead reads the existing destination and writes
`TBL[(texel<<8)|destination]`. There is no LUM stage on that selected operation.
The test supplies destination165 and authentic m02.tbl after host application
of the accepted source255 identity-row initialization. All source/destination
axes are checked against actual original table-read addresses and output bytes.
The prior color run establishes other TBL operations; no generalization to all
callbacks is made here.

Neither selected callback has an index255 discard branch. Synthetic reserved
index controls include0 and255; actual GTSi samples also include255. Every tested
sample produces a byte store. TBL source255 often preserves the destination
because its initialized row is identity; that is table composition, not a skipped
write. Palette resemblance to black/magenta has no role in these operations.
These are 8-bit framebuffer indices, not RGB display colors.
