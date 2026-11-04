# Retail WRLD serialized format candidate

Research-only specification for retail executable SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`, verified v100 GZF `f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0`. **Binary-static + retail-corpus**, not a native execution result or promoted reference.

All offsets below start at the payload, after the eight-byte `WRLD`/total-length header. The callback sees the header: `serialized_offset = EBX displacement - 8`. All 80 investigated records have total length **339 (0x153)**, payload **331 (0x14b)**. WDEF length is 367 (0x16f). Their sibling WREV is **9**; the first WRLD word is **not** a revision. Root REV is 2. These are the only observed layouts, not a proof of historical revision universality.

## Packed on-disk candidate

This is a byte-layout description, not a castable runtime object. Decode little-endian unaligned words explicitly. `le_f32` denotes four wire bytes interpreted as IEEE-754 binary32 by downstream x87 FLD; it is not a portable C built-in.

```c
typedef struct {
    /* +0x00 */ le_f32 scalar0;
    /* +0x04 */ le_f32 scalar1;
    /* +0x08 */ le_f32 scalar2;
    /* +0x0c */ unsigned char unknown_0c[4];
    /* +0x10 */ le_i32 integer10;
} i76_wrld_material_wire; /* 0x14 bytes, no padding */

typedef struct {
    /* +0x000 */ le_i32 audio_selection;
    /* +0x004 */ char movie_before[13];
    /* +0x011 */ char movie_after[13];
    /* +0x01e */ char palette[13];
    /* +0x02b */ char luminance[13];
    /* +0x038 */ char blend_table[13];
    /* +0x045 */ char notepad[13];
    /* +0x052 */ char sky[13];
    /* +0x05f */ char scrounge[13];
    /* +0x06c */ char terrain_default[13];
    /* +0x079 */ char map_name[13];
    /* +0x086 */ char horizon_manifest[13];
    /* +0x093 */ le_i32 environment_selector;
    /* +0x097 */ i76_wrld_material_wire material[8];
    /* +0x137 */ le_i32 projection_integer;
    /* +0x13b */ unsigned char unknown_tail[16];
} i76_wrld_serialized_candidate; /* exactly 0x14b bytes */
```

## Coverage and evidence

| Payload range, half-open | Bytes | Established interpretation | Evidence / limits |
|---|---:|---|---|
| 000..004 | 4 | Audio selection word | 004b8a17 -> 00423320 stores 004ed800; 00423368 uses it for CD track validation/play. Legacy “enabled flag” alias is misleading. No safe Boolean interpretation. |
| 004..011, 011..01e | 26 | Two 13-byte movie names | Exact three MOV dword + one MOV byte copies at 004b8bdd..004b8c20, later movie calls. |
| 01e..093 | 117 | Nine adjacent 13-byte name slots | Nine source addresses, 13-byte spacing, corpus NUL termination; direct consumers in dependencies table. Unlike movie slots, most retail string operations are unbounded. Slot extents combine adjacent starts and corpus, not a claim retail enforces 13 bytes. |
| 093..097 | 4 | Signed environment selector | 00477b26 ADD, CDQ/IDIV24, scale/divide; selects built-in texture. “Hour” is plausible inference, not a required UI name. |
| 097..137 | 160 | Eight 20-byte entries copied | 004b8b26..004b8b47 copies exactly 8 x 5 dwords to 00644220..006442c0. |
| Within each entry +00,+04,+08 | 96 total | Three binary32 members | 00492777/87/97 FLD, index *20. Physical names such as friction/roughness remain leads from aliases; this run only promotes numeric types. |
| Within each entry +0c | 32 total | Opaque copied bytes | No bounded getter trace resolves type or physical meaning. Zero in this corpus is not a reserved-byte guarantee. |
| Within each entry +10 | 32 total | Signed int32 member | 004927a7 FILD, index *20. Do not reinterpret as float just because adjacent members are floats. |
| 137..13b | 4 | Signed integer converted to float | 004b8c2a FILD; 004b8c31 stores 004c271c; conditionally passed into projection setup. 600 in every observed file; exact visual unit deferred. |
| 13b..14b | 16 | Opaque, unaccessed by handler | Variable in corpus. Not safe to discard or mark reserved. |

Coverage totals 331 bytes without gaps or overlaps. The per-entry table is a nested view of 097..137, not extra bytes. No authoritative reserved region is established. Detailed bytewise zero/stable/variable spans (decimal, half-open) are in `evidence/corpus.json`; zero-filled spans include portions of strings and numeric values and must not be conflated with reserved fields.

Every name is observed NUL-terminated ASCII inside its slot across the 80 files. Empty names are valid observations for movies, scrounge and HZD. Preserve original 13 bytes, including bytes after the first NUL, separately from the display string. Encoding beyond ASCII is unestablished; the independent reader rejects non-ASCII before NUL but preserves opaque/post-NUL bytes. Original retail scans are not an encoding validator.

## Typed-field falsification and confidence

`fields.json` enumerates every byte with type, offset, width and original access. Confidence is high for offsets, copied extents and scalar access types; resource role confidence comes from the consumer map. Field-name physical interpretations beyond those consumers remain deferred.

For **each name slot**, `evidence/corpus.json` provides independent miss8/M01 and miss8/M06 values and both miss16 variants, plus all other files. Movie/scrounge empty cases and mode-pair changes falsify any “always loaded/nonempty” rule. A 13-character unterminated synthetic field is rejected by our reader even though retail may scan into its neighbor. A future mission whose adjacent source starts or WREV differ would invalidate extending this candidate unchanged.

For **audio_selection**, M01=9 and M06=1, and S01 differs across modes; this falsifies Boolean/revision interpretations. Track availability/configuration can invalidate “this word guarantees music playback.” For **environment_selector**, M01=M06=15 while other specimens use 0,6,9,21. The original signed arithmetic, not those stock values, establishes numeric interpretation; negative inputs may select outside the table and are not endorsed.

For **every material row/member**, the whole-block copy plus indexed getters establishes 4-byte width, 20-byte stride and float/signed type. `numeric_observations.json` cross-checks all rows in all specimens and gives M01/M06 observations. Stable zero floats and integers are not sufficient to name physics behavior; future different values must be accepted/preserved without guessing. Row +0c has no typed proposal. Physical labels inherited in Ghidra do not complete a consumer proof.

For **projection_integer**, M01/M06 and all others contain 600, but x87 FILD (not FLD) establishes its signed source type. The camera path chooses a built-in alternative unless 00654b8a is nonzero, so unconditional far-distance behavior is not proved. Unknown tail bytes are explicitly untyped.

## Bounds and revision policy

004b8a10 does not read the WRLD length word at header+4, receive a local capacity, or compare any field to the declared end. It returns 1 after side effects. The caller's generic parser end pointer does not substitute for field bounds; its callback address calculation uses descriptor flag bit1, while WRLD flags=1 passes the header unchanged. Retail name scans are unbounded; numeric accesses are unconditional, and ACT/TBL copies lack acquired-resource length checks here.

An independent reader should require a complete bounded chunk, exactly 331 payload bytes for this WREV9 candidate, exactly one WREV word, and an explicit unsupported-revision/layout result otherwise. Preserve unknown records as opaque in a broader inventory rather than treating them as this struct. Empty fields are representable; resource resolution is a separate stage. Never emulate unsafe scans, signed selector indexing, missing resource-size checks, or diagnostic-only failure handling.
