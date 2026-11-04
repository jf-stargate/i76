# Registered source selection

Evidence tier: binary-static with independently tested analytical model, authenticated installed ZIX key comparison. No media callback, filesystem enumeration or collision case was executed under original instructions. `../evidence/instructions.json` gives original function ranges and selected assembly; `source_model.py` is a testable specification model, not a resource provider. This selection is separate from PIX-versus-loaded-file precedence at `00609564`.

## Structures and registration

Registered keys occupy 0x30-byte rows at `005DACC8`, count `005DACCC`: +00 key[16], +10 eight little-endian u32 membership words (256 bits). Source i is word i>>5, bit i&31. A key is metadata membership, not proof any source opens or contains a readable record. Enumerator `004B2AC0` returns matching key-row pointers and advances its caller's ordinal; it does not acquire payloads.

Mounted sources are a static array at `006592E0`, stride 0x10C, maximum 256: +00 path[256], +100 mode, +104 root/media index, +108 cached archive handle. Mode0 means path needs a root/media prefix; mode 1 is a directly formatted path. **Mode1 can be an archive or a loose directory.** Mode is not an archive-format flag.

`00471250` initializes resource heaps, writes media-enabled `00669EE4=1`, installs current-volume callback `00470D40`, drive accessor `00470D30`, switch callback `00470D90`, and calls `004B23E0` with i76.zix, then loads PIX indexes. These are demonstrated writes on that initializer, not a measurement of later runtime state.

`004B23E0` stages `addon` and a mode-selected `miss8`/`miss16` path to count loose resources, parses configured root/media and source rows with `004B1DF0`, then appends the final mission directory. Source0 is addon; configured paths begin at source 1. The parser's line helper `004B20F0` lowercases unquoted text, explaining uppercase `DIR:` in the specimen. `dir:` selects mode 1; `cd` prefix plus parsed ordinal selects mode 0. Root/media descriptors have 0x300 stride and three 256-byte text regions: filesystem root, media label, prompt text. Path-buffer limits, input scanning and invalid source indexes are unsafe in retail; this is not a safe general ZIX text parser contract.

`004B28C0` enumerates configured directories with FindFirstFileA/FindNextFileA, excluding directory entries and dot-leading filenames and skipping the source path equal to i76.zfs. Archive membership comes from ZIX rows, not from traversing the archive at registration. ZIX keys are lowercased through `004B95C0`; temporary 0x30 rows carry a single source ordinal at +10. `004B2A70` sorts these by four little-endian DWORD key subtractions and then unsigned source ordinal. Initialization merges equal 16-byte keys into one row by ORing source bits, then frees the temporary rows. The final registered-key comparator `00470CA0` compares only those four DWORDs; it differs from archive `_stricmp` comparison. ASCII zero-padded keys form the validated common domain.

The supplied `orig/I76.ZIX` is independently identified in `../evidence/zix.json`: 93,873 bytes, SHA-256 `1002a75cb2d9e597eeef40e49412cb8b578cbbcafa84af3e0839af86f770dd6b`. Its 6,116 rows all designate source 1, `DIR: i76.zfs`; their normalized key multiset exactly equals the archive's live keys. This validates that installed index specimen, not dynamic registration or every install configuration.

Runtime registration `004B2B30` searches existing source paths case-insensitively, reuses the first matching ordinal, or appends a mode 1 source (rejecting ordinal>255). For an existing key it ORs that source bit; otherwise it reallocates the registered array, clears a new row, copies key, sets its source bit and re-sorts with `00470CA0`. New registrations do not move a source to the front. Returned enumeration pointers can be invalidated by reallocation/sorting.

**Annotation correction:** the first call at `004B2B3C` targets `004702D0`. The baseline misleadingly renders this as `canonicalize_resource_key_16byte`. Its instructions actually hash/search the loaded-file cache and call `0046FBE0` to evict a matching record. It does not lowercase/canonicalize the key. Runtime registration needs an already prepared 16-byte key. That invalidation happens before source/key registration and can free referenced cached bytes; it is not just metadata bookkeeping.

## Selection algorithm: 004B2E00

Bsearch the prepared 16-byte key in 0x30 rows. Missing key returns null and records an error. For a hit, scan source ordinals 0..255 in ascending order, recording:

- A: first membership bit of any mode.
- M: first member whose mode is zero.
- C: first mode 0 member whose root/media index equals active selector `004FFF18`.

Then:

1. If media-enabled `00669EE4` is zero, or M does not exist, return A.
2. If A<M, return A: an earlier direct source wins before any media handling.
3. Otherwise, if C exists, return C. C may be later than another direct source.
4. Otherwise close and clear **every non-null cached archive handle** in the configured source count, then call switch callback `006562D0` with drive letter, requested media label and prompt. Failure returns null; success updates active selector and returns M. No other source is tried.

The return is a source-array address, **not a registered-key row**. A corrupt registered row with no bits can produce base-minus-one-row arithmetic rather than a clean miss; the safe model rejects it. The original initializer's source-index guard also permits 256 (`<0x101`) without a demonstrated lower bound, although valid bitmap indexes are 0..255. A provider must validate indexes itself.

Normal switch callback installed by `00471250` prompts and rescans available CD drives, comparing volume-label prefixes, and loops until suitable media exists; its inspected normal return is 1. The selector supports a zero failure return from other callbacks, but no stock callback cancellation was demonstrated. Closing archive handles occurs before the callback, including on a callback failure. Selection alone, including a size query, can therefore close handles or block for media.

## Loose versus archive acquisition

`004B3030` resolves one source, formats its base path, then calls case-sensitive `strstr(base, ".zfs")`. It tests a substring, not an extension or the mode. For mode 0, formatting is root[media] + backslash + source path when media-disabled, or active-drive colon/backslash + source path when enabled. For other modes it copies source path. An uppercase `.ZFS` or `.zfs` inside a directory name can change this retail dispatch; future providers should represent source kinds explicitly.

If substring exists, lazily open via `004B9740(path, 0)` and cache handle at source+108; use caller-buffer or allocated ZFS record read. Failure returns directly. A failed open leaves handle zero and a later operation can reopen; a failed record read does not close a non-null handle or try another source.

Otherwise format base + backslash + logical name, open rb, determine length by fseek/ftell, allocate or enforce supplied capacity, read once and close. Open/read/capacity failures return directly. **There is no archive-to-loose or loose-to-archive retry within this function.**

`004B3310` independently selects/formats a source and either opens the loose file for length or reuses/lazily opens the archive and queries its live index. Missing/unopenable returns 0. A zero result conflates missing/error/zero-size. Membership `004B34F0` only bsearches the key table and does not select/open a source. A positive archive size can coexist with corrupt compressed data. Size and acquisition can select twice; they are not one atomic source lease.

## Duplicate loose/archive names

For the supplied source order: addon 0 (direct loose) precedes archive 1 (direct), which precedes the appended mission directory. An enumerated addon duplicate wins over the archive; an appended mission loose duplicate loses to the earlier direct archive. If media-mode sources are involved, the A/M/C algorithm above controls selection. There is no unconditional “loose wins”, “archive wins”, “latest registration wins” or read-failure fallback rule.

`00470070` can return an already cached payload before selection. Its header stores name and length but no mounted-source ordinal, so the source selected by a later size request need not own existing cached bytes. Runtime registration invalidates this cache by key, but source switches in `004B2E00` close archive handles without evicting loaded payloads. A returned payload's physical provenance must be captured at acquisition by a safe provider, not inferred later by re-resolving the name.

## Limits

The model's 12 synthetic cases cover early direct overrides, active-media preference, switching, disabled media, duplicate media, bit 255 and invalid membership. They are analytical tests, not original-instruction execution. Actual directory contents at startup, registry configuration, media prompts, races and global teardown were not run. PIX ordering, its whole-PAK ownership and the acquire-preference global retain their separately accepted contract.
