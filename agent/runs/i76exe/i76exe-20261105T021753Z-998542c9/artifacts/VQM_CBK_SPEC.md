# VQM/CBK indexed decoding

**O/S/B/D** contract for the authenticated retail EXE. `decoder.py` is an
independently authored bounded experiment, not maintained reconstruction code.
`evidence/instruction_validation.json` authenticates static exports;
`executed_instructions.json` authenticates every executed instruction address,
length and hash against original PE bytes. Opcode payloads remain private.

## Input and output

| Offset | VQM field / verified use |
|---|---|
| +0, u32 LE | width; output stride is this exact width |
| +4, u32 LE | raw height word; copied unchanged to output; raw word used in capacity multiplication |
| +8 | NUL-terminated CBK dependency passed directly to resource acquire |
| +0x14 | opaque word; skipped by decoder; semantics unresolved |
| +0x18 | u16 LE block tokens |

Retail specimens use dependency strings within the historical 12-byte name
area +8..+0x13. The loader itself imposes no 12-byte bound. The independent
profile requires a NUL before token data; it does not assign semantics to the
opaque word. For example 3abrtms1.vqm's opaque word is 124, not another mip
level consumed by this decoder.

CBK texels start at +4, with 16 bytes per tile. The first DWORD agrees with the
number of tiles in this corpus and is treated as a count by the bounded decoder.
**Original 0044B430 never consults that DWORD.** An original synthetic execution
with zero there and complete tile backing produces identical output. Neither
input length, CBK count, nor token range is validated by retail code.

Output is `u32 width; u32 raw_height; u8 pixels[width*height]`. Pixel origin is
first decoded block/first tile row at +8. Output row y begins at +8+y*width.
There is no row padding, RGB conversion, palette lookup, vertical inversion,
alpha conversion or output pointer per row inside the decoder. Alignment of the
backing allocation is a heap service property, not a serialized pitch field.

## Algorithm

For valid nonflagged dimensions:

```
block_columns = ceil(width/4)
block_rows    = ceil(height/4)
for by in [0, block_rows):
  for bx in [0, block_columns):
    t = read_u16_le(VQM + 24 + 2*(by*block_columns+bx))
    for sy in [0, min(4,height-4*by)):
      for sx in [0, min(4,width-4*bx)):
        pixel = (t & 255) if (t & 0x8000) else CBK[4+16*t+4*sy+sx]
        output[8+(4*by+sy)*width+4*bx+sx] = pixel
```

Bit15 means solid fill; bits8..14 in a solid token do not select a tile or change
its byte value. A codebook token uses all 15 remaining bits as the tile ordinal;
there is no one-based adjustment. Traversal is blocks left-to-right, then
four-row groups top-to-bottom, with row-major bytes inside each tile. Partial
right/bottom blocks consume tokens but clip writes to resource dimensions.
The 125x180 authentic fixture and 1x1/3x2/5x7/7x5/9x1/1x9 synthetic cases
exercise edge branches. Synthetic tiles vary independently by tile, row and
column; solid tokens include 0x81FE/0x80FF/0x8000. They distinguish transpose,
vertical flip, block-column traversal, tile ordinal off-by-one and extra solid
flag interpretations.

At 0044B440..0044B449, the decoder requires wrapped unsigned
`width*raw_height + 24 <= supplied_capacity`; failure returns zero before output
writes. On success it copies the two header words. Height for traversal is
`SAR32(raw_height<<3,3)`: high three bits are removed, but bit28 sign-extends.
For the bounded corpus profile this equals the nonnegative low29-bit height.
The allocator at 004476D2..E4 requests raw product+8 and passes raw product+24
to the decoder. Capacity tests confirm actual required output+16 is the accepted
claim, although actual allocation remains required output. Do not allocate an
extra 16 output bytes merely because the parameter adds 24.

No mip chain or alternate-resolution branch is consumed by 0044B430. Resource
selection and post-load FULLRES flags are separate. All 5987 unique VQM names
in this base-game archive have unflagged input heights and exactly one token
plane. This is not proof that other products or every unsupported flag variant
has the same contract. The safe decoder rejects flagged inputs and dimensions
outside its 4-Mpixel policy, and checks count, token span, name termination and
tile bounds. These checks are host policy, not retail behavior.

## Validation domain

The independent decoder accepts all 5987 unique VQM resources (6000 PIX rows
before duplicate-name coalescing), spanning 18 dimension pairs. It processes
1,871,085 solid and 1,516,521 codebook tokens. Its canonical aggregate includes
source/CBK/output hashes without publishing a full asset inventory or pixels.
20 bounded authentic original-execution comparisons cover every distinct shape
plus the named bus/GTSi fixtures. Every output byte and header matches the
independent decoder; full buffer and texel-only SHA-256 values are published.
This is not original execution of all 5987 resources. No historical exporter
was used as a decoding oracle.
