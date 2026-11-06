# Numerical behavior and emulator limits

Findings F4/F5, original `00493550..004937B2`, `004927B0`, `004931C0`. **New CPU evidence:** 668 cases across retail M06, CD M02, controlled repeated-page M06 and controlled bit12 M06. All native sample/height/class outputs agree exactly with the independent model; all 392 world-height queries compare exact rational values against native 80-bit ST0. Original height instructions execute unchanged on x86 in 32-bit mode; the Linux loader, grid and backing are substituted. This is not Windows execution or whole-engine hardware parity.

## Admission before interpolation

Under tested CW `037F` (64-bit x87 significand, nearest/even), X and Z are independently multiplied as double inputs by stored float reciprocal `0x3e4ccccd`. The original then adds double bias `0x4338000000000000` (6755399441055744), stores double and interprets its low signed int32. The instruction sequence is:

```text
p = round_x87_64_nearest(world_double * exact_value_of_float32(0.2))
b = round_x87_64_nearest(p + exact_double_bias)
d = round_binary64_nearest(b)
index = signed32(low_32_bits_of_double_encoding(d))
reject if signbit(indexX | indexZ | (10240-indexX) | (10240-indexZ))
```

For ordinary nonoverflowing indices admission accepts 0..10240 inclusive. **Do not replace the sequence with a single mathematical `round()`**: rounding the addition at extended precision before storing double creates a narrow double-rounding region near half-integers. Tests include -2.502, -2.5013, -2.5012, -2.5001, -2.50001, -2.5 and -2.49999; some values slightly more negative than -2.5 still admit index zero. The independent rational model accounts for each storage/precision stage. `coordinate_cases.jsonl` records exact admission results and the distinct floor results.

At ordinary world sample centers `world = integer*5`, multiplying by float32(0.2) usually yields a small positive fractional residue. A position at such a center is not automatically an exact bilinear endpoint in the world-height query. Direct lattice sampling remains exact. The material query repeats the bias conversion and samples one rounded location; it does not interpolate class values.

## Four corners, stores and return

After admission, the height routine saves rounding control, sets RC-down (`004935CA`, control `077F`), multiplies both world doubles by the reciprocal, and stores scaled values as binary64 under RC-down (`004935D9`, `004935E5`/`004935E8`). FISTP qword at `004935EE` and `00493608` floors those values; only their low32 integers feed addressing.

All four height words are independently resolved and masked to 12 bits. With `fx=sx-ix`, `fz=sz-iz`, arithmetic order is:

```text
row0 = store_binary32_down(h00 + (h10-h00)*fx)
row1 = store_binary32_down(h01 + (h11-h01)*fx)
restore caller's RC bits at 00493792
result_ST0 = (row0 + (row1-row0)*fz) * exact_value_of_float32(0.1)
```

The row stores are at `0049375D` and `00493769`. Intermediate x87 arithmetic also observes the current RC and precision control; the standalone rational model explicitly rounds each operation to a 64-bit significand, each row to 24 bits and scaled stores to 53 bits. After restoration the final Z interpolation/multiplier uses the original caller RC. All tested calls restore CW `037F`. There is **no final float or double store in the original sampler**. Published `native_row_bits` records both actual CPU float32 stores (captured after return, before the subsequent material call), and `emulated_row_bits` records the corresponding Ghidra stores. Both native rows are independently checked. Published `original_st0_le` is the actual 10-byte little-endian native result; `original` is its double rendering. A future API returning double introduces an explicit final binary64 rounding.

## New restriction on earlier emulation claims — F5

The accepted hardware-assisted FISTP service is retained for the two original sites. It repairs Ghidra's known FISTP/rounding-control limitation. It does **not** repair all floating-point arithmetic and stores. On the final corpus, native-vs-Ghidra height differences occur in M06 30/98, M02 17/98, alias 27/98 and bit12 30/98 world cases. Maximum absolute difference is 3.0517600407287127e-6. These are recorded diagnostics, not counted as successful bit-exact emulator heights.

Example `0093_interior`, world input `[1919.999, 47529.999]`: native height `31.099695459659536`, Ghidra `31.099698511419579`; error `3.0517600407287127e-06`. The original row stores require downward rounding. Ghidra trace addresses, floor integers and source words still match the independent resolver for all captured reads. This narrows any assumption that correcting FISTP makes the complete emulated height numerically exact; it confirms the later static reference's explicit RC-down qualification.

## Normals, classes and bit12

`004931C0` writes a separate triangle-selected approximate query normal. Its admission matches the bias test; index conversion subsequently uses supplied CRT `_ftol` truncation, not the height sampler's RC-down FISTP sequence. The original world-minus-index branch test and approximate inverse-square-root helper are preserved. Its 3-float outputs and returned pointer are logged, finite-checked and compared unchanged under the bit12 control; a native CPU or independent exact numerical normal model is **not** supplied. These normal values remain E-tier.

Rendering `00490FB0` samples neighboring heights for lighting slopes/intensity; accepted visual evidence and this run's static audit distinguish that consumer from the collision/query normal. Neither is asserted to be the derivative of the bilinear height function, and no renderer-normal API is inferred.

Toggling bit12 of every private M06 TER word leaves all tested sample heights, native world heights/classes and emulated query normals unchanged. The source-position helper masks low12. The known rendering split predicate uses class-bearing words with `>=0x4000` and `&0xe000`; bit12 cannot change that predicate for a fixed class. **Overall bit12 semantics remain unresolved**; no claim covers every original consumer, arbitrary geometry path or a complete render replay.

Unmeasured: nondefault x87 PC/RC inputs, NaN/infinity/extreme doubles, denormals/exceptions, arbitrary malformed grids, negative-slot memory behavior, native `_ftol`/normal parity, teardown/indirect default writes and further missions. Exact rational arithmetic here is an independent bounded reference, not maintained reconstruction code.
