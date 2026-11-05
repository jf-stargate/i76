# ZFS payload dispatch and bounded decoder boundary

Evidence: `../evidence/instructions.json`, verified original PE versus v100 Ghidra function ranges, the full corpus, and independent synthetic tests. Embedded names in the baseline are annotations; the following arithmetic and call sites establish algorithm identity independently of those names.

## Original wrapper contract

`004B9BD0..004B9DA8` (473 bytes) bsearches a live name, reads stored length from record+18 and offset from +10, and tests packed flags with mask 6. The bsearch result is dereferenced without a null check. Archive-level allocated reader `004B9DB0..004B9DCB` (28 bytes) calls it with destination=NULL, capacity=0. Caller-buffer wrapper `004B9BA0` returns whether the result pointer is non-null.

Raw: with a supplied destination, require signed capacity >= stored length; otherwise allocate stored length. Seek to the absolute payload offset, then `fread(destination, stored_length, 1, FILE*)`. No prefix is removed, no framing header is consumed, no offset is relative to the table. Raw records bypass the LZO wrapper. Zero-length fread would return zero and is a retail failure; the safe reference reader permits an empty raw result as an explicit policy difference.

Compressed: allocate a separate stored-length temporary, read stored bytes, derive expected logical size using SAR 8, then either allocate that size or require supplied capacity >= it. Call `004B9FC0..004BA087` (200 bytes) with five stack arguments: stored pointer, stored length, low-byte flags, decoded destination, declared decoded length. **The fifth argument is unused by the dispatcher.** Ghidra's inherited `thiscall`/`fastcall` signatures are misleading: stack pushes, caller cleanup and actual callee loads establish this interface. The dispatcher's local output-length variable is passed to the decoder; its value is overwritten, never compared with expected length. Successful wrapper output size is the declared size, irrespective of actual decoder output count.

Dispatcher initializes the embedded library at `004BA980` using 0x1000 and size parameters 2,4,4,4,4,4,4. This supports a LZO 1.00 interface lineage, not an independently authenticated source release/build. The initializer checks nonzero version and ABI sizes and invokes a runtime configuration self-test. Failure returns false; later calls can retry because initialized state remains zero.

| Original predicate | Called entry | Algorithm evidence |
|---|---|---|
| flags & 2 | `004BABD8` | LZO1X: token>=64 uses distance `1+((token>>2)&7)+next*8`, total match length `(token>>5)+1`; first-literal short-match distance includes 0x801 |
| else flags & 4 | `004BAA00` | LZO1Y: token>=64 uses distance `1+((token>>2)&3)+next*4`, total match length `(token>>4)-1`; first-literal short-match distance includes 0x401 |
| neither | no decoder | Dispatcher returns false, although the outer reader normally bypasses it for this case |

Original instructions at 004BAC74/79/7C and 004BAA9C/A0/A3 distinguish these modes. The total lengths include the two-byte base match copy. Their distinction agrees with the corresponding LZO1X/LZO1Y branches of the [upstream decoder source distributed by Debian](https://sources.debian.org/src/lzo2/2.10-3/src/lzo1x_d.ch/). This source comparison labels the retail arithmetic; specimen success alone does not choose the algorithm. Flags 6 dispatch X because the 0x04 bit is tested second. Bit 0 is filtered at open. Other low-byte bits do not change these original predicates; the safe profile rejects unknown bits instead of silently treating an unknown flag as raw.

At decoder EOF both originals write actual output length and return 0 for a valid end marker with exactly consumed input, -1 for the inspected invalid end-marker length, -4 for consumption beyond the supplied end, or -8 for input left after EOF. The wrapper accepts **only zero**, converts it to boolean true, and writes an error string for other returns. These are inspected EOF exits, not a comprehensive safe malformed-stream error taxonomy: earlier unchecked reads/copies can fault or corrupt memory before EOF.

## XOR and checksums

After successful raw read or decompression, archive key+1C is XORed into each complete little-endian 32-bit logical output word. The final 0..3 bytes remain unchanged. XOR is **after**, not before, LZO. There is no checksum validation or additional transformation on the inspected read route. Retail key is zero; nonzero-key behavior is binary-static plus synthetic reference tests, not a nonzero-key retail specimen test. No historical extractor transformation was adopted for it.

## Error and memory behavior

Header/table fread errors or invalid constants/table counts return null. Several archive-open failures free the handle but not all subordinate allocations. Record fread failure frees its temporary/internal raw allocation; too-small supplied capacity returns null. Decoder failure frees the compressed temporary and returns null, but does not free a newly allocated decoded destination. Supplied output may already contain partial output. Allocation failure calls `00404D80`, which displays a message and exits(1). Cache diagnostic reporter `0042D5D0` is one RET: its size-budget diagnostics do not stop cache loading by themselves.

The unsafe embedded decoders receive an output-length **pointer**, not an output capacity; they use input length at final consumption checks, with no systematic pre-copy input/output/lookbehind checks. They can write beyond the expected-size allocation. A short but otherwise successful stream can leave the allocated tail uninitialized while retail reports the larger declared length, then XORs that declared extent. No original deliberately corrupted resource was executed in this investigation. These static hazards must not become a reconstruction contract.

## Independently bounded backend

`SafeLzo` binds system `liblzo2.so.2` **safe** X/Y APIs: C `int fn(const void *src, lzo_uint src_len, void *dst, lzo_uint *dst_len, void *workmem)`. The wrapper supports Linux LP64 only and uses unsigned long (8-byte lzo_uint), 8-byte pointers and 4-byte int. It allocates disjoint input/output storage, initializes output length to validated expected capacity, passes stored length exactly and NULL workspace, then requires rc==0 and actual length==expected. Any failure discards output; there is no alternate-algorithm retry. Read-only logical results are independent Python bytes objects. No original decompressor code is redistributed.

Measured backend is LZO 2.10; exact installed ELF identity is recorded in `../evidence/provenance.json`. Decompression safe entry points need no compression workspace. Upstream [safe decoder source](https://sources.debian.org/src/lzo2/2.10-3/src/lzo1x_d.ch/) supplies its input/output/lookbehind guards. Their implementation correctness is an external dependency; Python bounds checks do not prove the C library memory-safe. The wrapper's mode choice, allocation limit, capacity and length/return checks are independently established and tested.

Full corpus: 1,526 X and 4,097 Y records decode through the **statically selected** algorithms and match extracted hashes; 493 records use raw bytes. As a diagnostic crosscheck only, opposite-mode safe decoding rejects 1,525 X specimens and every Y specimen. One X stream also decodes identically as Y, demonstrating why “try both and pick success” cannot establish original dispatch. The 50 tests include valid X/Y literal streams, flags 6 priority, truncation, too-short/too-long expected output, trailing input, recovery after errors and XOR ordering. They validate the wrapper contract, not the entire external codec implementation.
