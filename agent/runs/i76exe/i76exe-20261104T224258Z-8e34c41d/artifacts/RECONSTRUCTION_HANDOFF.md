# Bounded logical-resource provider handoff

This is an implementation-ready **research proposal**, grounded in retail static behavior and one fully authenticated base-game corpus. It is not a provider implementation, canonical promotion or complete retail lifecycle compatibility claim. All experimental code belongs only to this run.

## Boundary and recommended API

Use explicit source kinds and immutable state rather than infer archive type from a path substring. An archive source should expose:

- `open_archive(read_only_source, limits) -> ArchiveIndex`: authenticate caller-selected input, snapshot or otherwise pin immutable source bytes, validate the entire index before publication.
- `enumerate(index) -> immutable EntryMetadata[]`: retain original directory order/locations, raw 16-byte name, normalized key, identifier, opaque time word, stored span, packed flags and status. Do not hide aliases, tombstones or duplicate candidates.
- `lookup_candidates(index, logical_name) -> EntryIdentity[]`: bounded ASCII profile; never silently sanitize paths or choose among ambiguous duplicate archive records.
- `read_logical(index, entry_identity) -> ResourceLease`: validate identity belongs to index, select statically established mode, decode within a checked expected capacity, require exact success/length, apply postdecode word XOR, return immutable bytes and selected provenance.
- `resolve_registered(snapshot, key, media_state) -> SelectionPlan`: validate 0..255 membership; preserve A/M/C ordering if retail-compatible selection is desired. The plan captures source ordinal/generation and any required media switch before acquisition.
- `acquire(selection_plan) -> ResourceLease | typed error`: avoid a separate size query that reselects; capture source, entry and bytes in one consistent operation. Any modern alternate-source retry policy must be explicit because original004B3030 has none.

`Archive`, frozen `Entry`, `SafeLzo` and `source_model.select` demonstrate these bounded pieces without implementing a mount manager, maintained reconstruction provider, callback execution or PIX parsing. A single-source logical lookup is fully exercised for all 6,116 records, including case-normalized lookup equality. A multi-source selection model is analytical/static only.

Recommended errors: unsupported header/version/profile, invalid table/chain/count, bad logical name, inactive, missing key, ambiguous key, invalid span/overlap, unsupported flags, invalid logical length, backend unavailable, decoder failure, length mismatch, stale selection, source/media unavailable. Never use membership as a substitute for successful acquisition; never return partial decoded bytes.

## Strict profile and arithmetic

All disk words are little endian. Require 28-byte ZFSF header, version1, width16, capacity100. Check count against a policy limit before allocating. On nonnegative counts retail expects floor(count/100)+1 full 3,604-byte tables. Require a finite unique chain, zero final pointer, valid nonoverlapping table extents and exact discovered nonempty-count agreement. Require empty-slot padding zero and no nonempty slot after a table terminator. These last requirements intentionally narrow retail's permissive/unsafe behavior.

Validate `offset <= limit` and `size <= limit-offset` before adding; also reject spans outside signed CRT long addressability. Validate full payload extents against both archive length and directory/header extents. Retain inactive metadata but never expose its payload as active. Identical same-span aliases with matching packed metadata may share storage and remain distinct entry identities; report them. Reject partial overlaps or incompatible aliases. Equal names are not proof of equal bytes, and equal bytes at different offsets are not physical aliases.

Reference policy limits: archive256 MiB, records100,000, logical result0x7FFFFF bytes, offsets/end <=0x7FFFFFFF. The smaller logical cap follows retail's signed SAR packed length; the other limits are conservative policy choices, not recovered format maxima. All authenticated records fit them; largest logical record 400,748 bytes. Inactive records with stale extents, nonzero ignored slots, long/non-ASCII/unsafe names or deliberately exotic layouts may be rejected. Do not describe this profile as accepting every archive retail might attempt to read.

Names are1..15 printable ASCII characters, excluding path separators/colon and dot/dotdot; normalize ASCII lowercase without stripping components or replacing characters. A NUL must occur within the16-byte field. Preserve post-NUL bytes privately for provenance; archive lookup itself compares C strings. Registered-key DWORD comparison includes all 16 bytes and thus needs a zero-padded prepared-key domain. Non-ASCII locale compatibility is unresolved.

Compression predicate: raw if `(flags&6)==0`; otherwise bit 1 selects X before bit 2 selects Y. Safe profile accepts only low bits 0..2 and rejects unknown flags on read. Compressed expected size is signed `int32(packed)>>8` and must be positive/in policy. Raw logical size is stored size even if upper packed bits are nonzero. For nonzero archive key, XOR full little-endian logical DWORDs after decoding and leave trailing bytes unchanged. There is no demonstrated checksum; caller hashes are authenticity/integrity metadata, not a ZFS checksum feature.

## LZO dependency

Bind only documented **safe** X/Y decoders, never the retail unsafe implementations. Pin/identify backend ABI and binary, allocate disjoint buffers, pass exact stored input size and expected output capacity, require rc0 and exact length, discard failures. `SafeLzo` currently supports Linux LP64 only. Porting to Windows/another ABI requires a verified lzo_uint binding and fresh tests. External decoder correctness remains separate from the proven ZFS wrapper contract; do not claim a codec proof from this corpus.

## Ownership and source precedence

Keep archive/index state, stored compressed temporary, decoded buffer, cache record and caller lease as separate objects. Retain immutable logical bytes with source ordinal, source generation, archive digest, directory identity, logical key and decoded length/hash. Close/unmount/provider destruction must not invalidate outstanding lease storage. Do not emulate original key-only forced eviction by freeing active leases.

For retail-style registered selection use the exact A/M/C algorithm in RESOURCE_SOURCE_SELECTION. For the supplied ZIX arrangement, addon duplicate wins over archive; appended mission duplicate loses to direct archive. Media preference can change this. Opening/size/acquisition must use a pinned selection, not three independent lookups. Registering keys and changing media should create a new provider/index generation. Maintain a typed archive source instead of the original case-sensitive `.zfs` substring heuristic.

## Synthetic fixtures and reproducibility

`test_zfs.py` constructs all archive bytes from scratch, including valid literal LZO streams `0x16 + "hello" + 0x11 0x00 0x00`; no retail data is embedded. Its38 tests cover truncated header/table, invalid magic/version/layout/pointers, cycles, extra/missing tables and count mismatch, signed integer overflow, malformed names, tombstones, duplicate names, aliases/overlaps, unsupported flags, malformed/truncated/trailing streams, decoded-size mismatch, sign-bit lengths, both-bit dispatch, raw-size semantics, XOR, recovery, foreign entries and independent outstanding results. Twelve source-model tests cover source/media ordering and bitmap boundaries. Six additional synthetic comparisons document historical-tool differences without invoking original retail code.

See REPRODUCTION.md for a fresh disposable Ghidra import, complete corpus comparison, deterministic private-inventory digest and exact PE-byte checks. Publication contains compact aggregates and instruction hashes only. Original files, inventories, opcode bytes, decompilation and Ghidra databases remain private. Future native reconstruction work needs separate authorization, review, integration tests and explicit decisions on duplicate/source policy and ownership. No PIX text syntax or reconstruction code was changed.

## Remaining uncertainties

No end-to-end retail acquisition/lifecycle execution; no callback cancellation, media switching, OS-directory enumeration order, non-ASCII CRT behavior or concurrent mutation experiment. Identifier/time-word producer semantics, archive writer/update behavior, full shutdown and duplicate bsearch winner remain unresolved. Nonzero XOR is proven statically and modeled synthetically, with no nonzero-key retail archive. Nitro Pack was located but excluded. These limits do not prevent safe enumeration/decoding of the authenticated base-game archive or a precise static registered-selection specification.
