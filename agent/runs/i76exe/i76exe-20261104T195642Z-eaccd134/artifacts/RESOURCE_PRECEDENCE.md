# Membership, source selection and route precedence

Evidence: authenticated functions in `instructions.json`; accepted prior RES
run `i76exe-20261101T161535Z-22d9956f` and the pinned current
`manual/reference/engine/resource_acquisition.md` are comparison context.
No collision case was executed under original instructions in this run.

## Name policy and table order

General acquire `0046FFC0` copies 16 bytes with `strncpy`, calls `_strlwr`, then
rejects empty keys and keys whose first four bytes equal `null`. It does not
safely validate a null input pointer or ensure termination for >=16-byte input.
A short name becomes zero padded; normal retail stems/extensions fit. No path
stripping or extension inference occurs at this boundary. Caller-specific name
production is a separate operation. Indexed direct entry points assume a
prepared readable 16-byte key; they do not perform case normalization.

All PIX rows are initially zeroed, scanned with unbounded `%s`, and lowercased.
`00470CA0` compares four **little-endian DWORDs**, using the first nonzero
signed wrapped subtraction. Thus this is not byte-lexical order and includes
post-NUL bytes. For accepted printable-ASCII zero-padded keys every DWORD is
below 0x80000000, so differences do not overflow signed order; a tuple of the
four unsigned DWORDs describes their sort order. Arbitrary high-bit/invalid
keys need not form a transitive comparator order. The reader implements the
actual callback arithmetic for equality/comparison and restricts its key domain.

## Multiple PIX files and duplicates

Registered `*.pix` key enumeration order determines PAK ordinals and ingestion
groups. The already sorted registered key table uses the same callback.
After ingestion, the entire member array is sorted with CRT `qsort` and searched
with CRT `bsearch`. The member's PAK ID survives sorting. There is **no inspected
explicit first-index, last-index, directory, or lexical-filename override rule**
for duplicate logical member keys. The comparator ignores PAK ID, offset and
length; equal keys compare zero regardless of source. qsort stability and the
bsearch duplicate winner were not established. Table order alone cannot prove
which equal-key row wins. The reader returns candidate metadata in source order
and rejects ambiguous lookup unless an ordinal is explicitly supplied. This is
an independent safe policy, not a retail-compatibility claim.

Corpus: 264 duplicate keys (each two occurrences); 264 extra entries, 264 distinct
locations, **zero distinct-payload conflicts**. Six keys have repeated occurrences
within one PAK; the rest are across PAKs. No overlaps were found, so equal payloads
can occupy separate byte ranges. These observations establish name membership and
byte equivalence only, not selected original source or successful acquisition.
Three reviewed aggregate duplicate examples appear in `corpus.json`.

## Acquire preference is asymmetric

| Operation | Original behavior |
|---|---|
| `0046FFC0`, `00609564 == 0` | Try `00470B20` PIX member; null falls back to `00470070` loaded-file route |
| `0046FFC0`, `00609564 != 0` | Try loaded-file route; null falls back to PIX member |
| `0046FD40` name release | Always indexed release first; successful membership suppresses direct release |
| `0046FEE0` name size | Always indexed size first; then cached-file size; then registered size |
| `00470340` membership (previous accepted audit) | PIX membership, then registered membership; no open/read check |
| Whole PAK acquisition | Direct `00470070(PAK_name)`, bypassing general preference recursion |

The actual mission-time value of `00609564` is unmeasured. A member hit with a
failed PAK load can produce offset-as-pointer and suppress fallback; a member
size hit does not verify PAK readability. Release reports membership even with
zero aggregate references. These facts distinguish membership, selected row,
acquisition success and returned bytes.

If a direct logical resource and PIX member share a name, direct-first acquire
may return direct bytes while size/release select PIX. If PAK count is nonzero,
name release could decrement that aggregate rather than release the acquired
direct record; if zero, it still reports success. This is a static consequence,
not a demonstrated retail collision bug. Keep provenance with independent leases
rather than reproduce cross-route release hazards.

## Registered sources and loaded cache

`00470070` first checks its hash cache, retaining a hit and returning header+24.
The hash is case-sensitive while chain comparison is case-insensitive; normal
callers lowercase first. A cache hit bypasses fresh source selection. A miss
queries registered size, rejects <=0, allocates, reads registered bytes, and
inserts only a successful read. `004B2E00` returns a **0x10C mounted-source row**,
not the 0x30 registered-key row; membership bits are 256 possible sources.
Ordinary selection starts with the first source member; source mode, active
media selector `004FFF18` and global `00669EE4` can change selection and invoke
media callbacks/close handles. This is a separate precedence system from PIX
member duplicate selection. Exact media configuration is unmeasured.

`004B3030` resolves one source and dispatches a formatted path containing literal
`.zfs` to its archive branch; otherwise loose-file read. It does not retry another
registered source after that source fails. Size lookup and loading can select
twice. A PIX and same-stem PAK are resolved as separate logical keys.

The maintained reconstruction at the pinned commit currently has memory and
directory mounts, lowercase ASCII names up to 255 bytes, newest-mount-first
selection, and generation-checked handles. It is intentionally a different safe
interface. Its cached entries hold copied payload vectors and source mount IDs.
No reader integration or maintained-code change is proposed by this run. A
future PIX provider must document how its own duplicate policy composes with
mount order; retail's ambiguous duplicate winner is not a license to silently
change reconstruction mount precedence.
