# Future read-only PIX/PAK provider contract

The verified text layout and absolute logical-PAK offsets are sufficient to
implement an independent provider over extracted, authenticated PIX/PAK files.
The run-owned reader is a reference implementation only. No maintained code,
canonical documentation, annotated baseline or governance was changed.

## Proposed boundary

Use an explicit mount/source identity, parsed immutable PIX entries and a backing
byte-stream resolver. Parse metadata once, validate count/name/decimal fields,
then request the **whole logical PAK stream** by same-stem key. Validate every
`offset <= length` and `size <= length-offset` before exposing a bounded span.
Keep source ID, original key, row ordinal, PAK key, offset, size and payload hash
with diagnostics. Membership must not imply successful acquisition. Expose
candidate enumeration separately from resolution; ambiguity should be an error
or an explicitly selected provider policy. Do not silently claim retail first/last
winner behavior.

The safe reader implements:

```python
index = parse_index(pix_bytes)           # strict bounded text parser
candidates = index.candidates(name)      # metadata; no PAK read
entry = index.lookup(name, ordinal=...)  # ambiguous keys require explicit selection
reader = Reader(pix_path)
view = reader.acquire(name, ordinal=...) # immutable, bounded memoryview
reader.close()                          # outstanding views retain backing owner
```

Metadata includes each token's actual serialized byte position. ASCII lowercase
and 16-byte zero-padding match verified ordinary keys; `compare16()` reproduces
four little-endian wrapped DWORD subtractions. Keys outside the supported domain
are rejected. Original malformed-input behavior is not a compatibility target.

## Integration stages for the WebUI reconstruction thread

1. **Extracted-pair provider:** implement text parsing, same-stem backing lookup,
   bounded immutable spans and provenance-bearing handles. Reuse reconstruction
   store normalization/error/result conventions; enforce the provider's narrower
   retail key domain. Add an explicit provider kind rather than teach consumers
   to guess offsets. Keep existing newest-mount-first selection explicit.
2. **Real consumer smoke checks:** resolve reviewed GEO/TMT/MAP/M16/VQM samples
   using mounted user files, compare recorded lengths/hashes, then exercise GEO
   and texture consumers. CBK lookup must also cover top-level registered resources;
   this corpus has no indexed CBK. A missing loose GEO is not evidence of absence.
3. **Retail ZFS adapter:** independently validate archive directory/decompression
   and implement a bounded logical-stream resolver. PIX offsets address decoded
   PAK bytes, never compressed physical ZFS bytes. Keep this layer separate from
   PIX parsing; existing extraction tools are comparison evidence only.
4. **Compatibility decisions:** decide and document cross-mount collision policy,
   same-name PIX variants, shared PAK cache budgets and unload/refcount semantics.
   Retain source in a generation-checked handle and release that source, rather
   than copying original PIX-first name-release asymmetry. These are independent
   safe design decisions requiring their own implementation review.

Current store (`reconstruction/include/i76/resource.h`, `src/resource.cpp`) caches
copied vectors under generation handles, limits a payload to 16 MiB and mounts to
32, rejects busy unmount/shutdown, and selects newest mount first. A future shared
whole-PAK allocation will need an owned backing object per live span or deliberate
copying; a raw pointer into an unpinned mapping would violate safe lifetime. The
reference reader's 128 MiB PAK cap is not a proposed store-limit change.

## Remaining gaps and release criteria

No gap remains in the observed base-game PIX token fields or PAK member offset
calculation. Gaps concern exact CRT equal-key winner behavior, non-ASCII locale
normalization, actual runtime preference/media configuration, original caller
sequencing around cache invalidation/index teardown, and variants outside this
base corpus. ZFS flag decoding is inherited comparison evidence, not newly proven
here. There is no PIX member decompression dependency to invent. Do not advertise
full original-source precedence or full retail lifetime compatibility based on
this reader. A staged extracted-pair provider can proceed without those claims;
a direct compressed-retail-archive provider still needs the independently checked
ZFS stream layer.

## Reconciliation with historical tools

Pinned `scripts/local_history/i76_zfs_inmemory_asset_graph_reports_v1.py`
(SHA-256 in `corpus.json`) and the vehicle texture resolver v5 parse text lines
and slice `PAK[offset:offset+size]`. The corpus inspector compared every one of
23,507 parsed row tuples and payload hashes against the graph script with zero
mismatches. Ten reviewed sample spans were also resolved through `Reader` and
independent file seek/read; all entries receive that full-reader check as well.
The historical vehicle resolver v5 also built an index from the six selected
pairs and resolved all ten reviewed names to the same backing PIX/PAK, offsets,
lengths and payload hashes, with no warnings (`examples.json` records its script
hash). These checks support the original-instruction interpretation, not vice versa.

A synthetic difference was reproduced: historical `int(token,0)` rejects `0010`,
where original `%d` and this reader read decimal 10. Historical line splitting
also accepts a missing final LF; original LF scanning requires the separator.
Historical normalization uppercases basename/strips paths in some resolver
layers; original general acquire only copies/lowercases. Historical first/last
or preferred-extension choices do not establish original duplicate winner or
acquire/release route behavior. GEO/image decoding/export heuristics were not
adopted as format authority.
