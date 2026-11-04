# Distinct records and payload lifetime

Evidence tier: binary-static, plus independent Python snapshot tests. Python
results are not execution evidence for retail pointers/refcounts.

| Object | Verified width / fields | Ownership |
|---|---|---|
| Serialized PIX row | Variable text: name, signed decimal offset, signed decimal length; no binary record width | Input file bytes; mutable temporary registered allocation while parsing |
| Indexed member | 0x1C; +00 key[16], +10 PAK ordinal:u32, +14 byte offset bits:u32, +18 byte length bits:u32 | Index-owned calloc array `0058D91C`, count `0058D928`; sorted in place; no member payload pointer/refcount |
| PAK retention row | 0x18; +00 logical PAK key[16], +10 whole-PAK payload pointer:va32, +14 aggregate member references:u32 | Index-owned array `0058D920`, count `0058D924`; one loaded-file lease while cached pointer exists |
| Registered key | 0x30; +00 key[16], +10..2F source membership bitmap[32] | Registration table `005DACC8`, count `005DACCC`; metadata, not payload cache |
| Mounted source | 0x10C; +00 path[256], +100 mode:u32, +104 root/media index:u32, +108 cached archive handle:va32 | Static source array `006592E0`, capacity 256; handles can close separately |
| Loaded-file cache record | Header 0x24; +00 key[16], +10 length:u32, +14 refs:u16, +16 opaque:u16, +18 hash-next:va32, +1C/+20 purge links:va32, +24 inline bytes | Cache heap `00609594`; hash table `00609580`; release to zero queues for eviction |

`va32` means an original 32-bit address, not a host pointer. The opaque +16 field
is not assigned a meaning. Widths are instruction-supported strides/accesses;
none of these runtime rows is asserted to be a C source declaration.

## Normal indexed lifecycle

1. Index construction clears each PAK pointer/count; metadata is allocated before
   any PAK payload is acquired.
2. First member acquisition loads whole PAK via `00470070`, obtaining one loaded
   cache reference. The PAK row stores its payload pointer, not the cache header.
3. Every successful member-row lookup increments the PAK's 32-bit aggregate
   count. Other member names in that PAK share it. Return is an interior slice
   pointer, with length obtained separately from indexed metadata.
4. While that cached pointer persists, repeated acquisition of the same row
   yields the same base+offset address. No copy is made, no member-specific
   allocation exists, and no member length is read in acquire.
5. Indexed release searches by name, decrements nonzero aggregate count. At zero,
   `0046FE30(PAK_name)` releases the one cache lease and the PAK pointer is cleared.
   It does not immediately HeapFree the PAK. Loaded-file zero refs join a purge
   list and may be evicted later. A later acquire may reuse or reload storage;
   cross-zero-transition pointer identity is not guaranteed.

Returned slices must not be freed. A normal balanced caller retains them only
while its acquisition remains live, subject to original cache invalidation
behavior. Aggregate counting is not tracking which member was acquired: a release
of a different indexed name in the same PAK can consume the aggregate. No overflow
protection is visible for the 32-bit PAK count or 16-bit loaded-file count.

## Failures, teardown and reinitialization

Missing/unreadable PAK: `00470070` can return null, but the one-RET reporter at
`0042D5D0` allows `00470B20` to increment aggregate count and add offset anyway.
A failed call is therefore not guaranteed to be ownership-neutral or a clean null.
A later attempt sees null cached pointer and retries, but prior phantom aggregate
refs may persist. Release after failure can decrement such a count; no native
execution established its complete effect. The safe reader does not cache failures.

Truncated PAK: whole-file loading can read the shortened stream successfully if
source size now agrees with that stream. Member range is unchecked, so the returned
pointer/consumer read can exceed allocation. If the lower read fails, the null
backing-load hazard applies. No per-member bounds validation can be inferred from
loaded-file capacity checks.

Zero-length member: indexed lookup ignores member length; with a nonempty valid
PAK it can still increment and return base+offset. A zero-size whole PAK is rejected
by the loaded-cache size<=0 test, leading to the same missing-load hazard. There
are no observed zero-size members in this corpus; those retail paths were not run.

Teardown `00470AC0` releases **one** cache lease for every non-null PAK pointer,
regardless of live aggregate member count, then frees both metadata arrays. It does
not reset pointer/count globals or protect outstanding slices. Payload may remain
in the cache temporarily, but ownership no longer protects it from eviction;
release/query through freed index metadata is unsafe. This does not establish a
supported teardown-with-active-references API. Reinitialization overwrites globals
and has no entry guard or built-in teardown, so repeated init without disciplined
external sequencing can leak prior arrays/backing leases. Calling teardown twice
is not established safe. External caller invariants remain unresolved.

Prior accepted cache research also shows explicit invalidation/purge can evict
records; no universal guarantee against forced invalidation is asserted here.

## Safe reference ownership

`Reader.acquire()` returns a read-only Python memoryview over one immutable PAK
snapshot. The reader holds the snapshot after a successful bounded read and full
range validation; failed reads/validation leave it unset. Multiple acquisitions
share the same snapshot object. Each view independently retains its bytes owner,
so `Reader.close()` drops the reader's cache without invalidating existing views.
Reacquire after close reads a new snapshot. There are no emulated retail counts,
name-based releases or unsafe dangling pointers. This safe lifetime is tested,
but deliberately differs from retail lifetime and is not integrated with the
maintained reconstruction's generation-checked lease interface.
