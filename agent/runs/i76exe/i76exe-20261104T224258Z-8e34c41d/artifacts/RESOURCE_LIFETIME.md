# Resource ownership and safe handoff

Evidence tier: binary-static plus independent reader lifetime tests. No retail lifetime path, forced invalidation, media switch, race or process shutdown was executed. `../evidence/instructions.json` authenticates the inspected functions. This document narrows the provider boundary, not complete runtime compatibility.

| Object | Owner / lifetime | Pointer invalidation boundary |
|---|---|---|
| Archive FILE* and 0x2C handle | Lazily opened by selected mounted-source row; source+108 caches it across size/read calls | `004B9AF0` fclose + frees table offsets, live records, handle; media switch closes every cached source handle and clears each field |
| Directory-offset array / copied live rows | Private archive heap `005DB990`; created by open | Archive close frees both; sort during open changes row order |
| Mounted-source row | Static 0x10C array at006592E0; persists independently of its handle | Initialization/path reconfiguration may replace contents; row address is not a resource lease |
| Registered-key row | Reallocated/sorted heap array; name+membership only | Registration can relocate/reorder it; enumerated row pointers are borrowed metadata |
| Stored compressed bytes | Per-read stored-length heap temporary | Freed immediately after dispatcher returns, including failure; no returned logical pointer aliases it |
| Allocated decoded bytes | Separate expected-length allocation, or caller-supplied buffer | Allocated-success pointer is freed through registered-resource free helper004B3550; caller-buffer bytes belong to caller; failure may leave partial output or leak an internal decoded allocation |
| Raw allocated bytes | Stored-length allocation, or caller buffer | Successful raw pointer owns actual read bytes; XOR operates in that buffer |
| Loaded-file cache record | Different heap; 0x24 header plus inline logical bytes | Refcount retention/purge plus explicit forced eviction; pointers are not archive-directory pointers |
| General resource payload pointer | Borrowed bytes from loaded-cache header+24 or retained whole-PAK interior | Depends on owning route; name alone does not encode ownership |
| Future caller lease | Recommended immutable logical bytes plus selected source identity | Lease independently retains its storage, even after provider close/unmount |

## Archive lifetime versus payload lifetime

`004B3030` and `004B3310` reuse source+108 whenever nonzero. `004B9740(path, 0)` opens rb; size alone can open the archive. `004B9AF0` explicitly closes FILE* and frees two metadata arrays plus handle. The only direct close call found in the v100 cross-references is the media-switch loop in004B2E00. That is not proof that no heap teardown or indirect path can destroy state. Global shutdown/reinitialization sequencing remains unresolved.

Successful logical resource buffers are independent heap allocations or supplied destinations. Closing an archive does **not itself** free previously decoded/raw output or loaded-cache entries. Archive metadata pointers become invalid at close; independent decoded bytes do not borrow from the directory or compressed temporary. A directory view must not be handed out as the lifetime owner of decoded data.

## Cache boundary

`00470070` cache hit retains a 16-bit count and returns record+24 without selecting a source again. On a miss, it queries registered size, rejects <=0, allocates header+length, then calls004B3000/004B3030 with the inline payload and capacity. Failed registered read frees the cache allocation; success inserts it. The header contains key[16], length:u32 at+10, references:u16 at+14, opaque:u16 at+16, hash-next at+18 and purge links at+1C/+20. It does not contain source ID or archive handle.

Size is queried before acquisition, so state can change between the two selections. The original cache path does not retain a mounted-source lease across that boundary. Cache length bookkeeping is based on its earlier size variable. The inspected capacity checks help some changes fail, but unsafe decompression can still exceed the allocation, and the path is not an atomic consistency guarantee.

Ordinary release to zero can queue for later purge; a reference count is not universal protection against forced eviction. `004B2B30` calls004702D0 **before** modifying registration; that helper finds the loaded-cache record by name and calls0046FBE0. The evictor clears a nonzero count, unlinks and HeapFrees the record. Thus runtime registration can invalidate outstanding borrowed payloads regardless of their reference count. If the payload backs retained PIX members, downstream interior pointers could become stale; this is a static implication, not an executed collision/registration experiment.

Media selection closes archive handles without a corresponding loaded-cache purge in that function. Cached bytes can consequently outlive the source handle and selection state. A cache hit's provenance cannot be reconstructed reliably by current source lookup. PIX and direct loaded-file acquisition/release asymmetry remains as documented in accepted PIX/PAK run i76exe-20261104T195642Z-eaccd134; it is outside this ZFS reader's implementation scope.

## Safe independent reader

`Archive.open()` takes a bounded immutable archive snapshot; no original archive handle is exposed. Entries are frozen metadata and keys map to immutable candidate tuples. Reads return immutable bytes owning their complete logical extent. Raw slices are bytes copies; decoded results copy out of a private backend buffer. `close()` drops the reader's snapshot/backend and prevents later reads, while previously returned results remain valid independently. Failures do not populate a payload cache or return partial bytes. Explicit entries must belong to that reader.

The synthetic tests retain multiple results across close, mutate the original construction buffer after snapshot, reject foreign entries, repeat failing and succeeding reads and confirm no error poisons a later good read. This safe ownership is intentionally not retail refcount emulation. A future provider should attach archive digest, entry identity, source/mount generation and logical length to each lease, and keep bytes immutable until the last lease is released. No maintained provider was implemented here.
