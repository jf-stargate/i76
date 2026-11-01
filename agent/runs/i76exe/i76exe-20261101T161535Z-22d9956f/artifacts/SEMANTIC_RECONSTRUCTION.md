# Resource acquisition: proposed C-level design

Pilot C, RES / `i76exe`. This is an independent **binary-static** reconstruction, not recovered original source and not a maintained implementation. The six target functions and bounded ownership/caller dependencies were decompiled from a fresh import of the private v97 GZF. Function-body hashes were independently compared with authenticated retail PE bytes. No acquisition function was emulated or run under Windows. See [identity and reproduction](REPRODUCE.md), [instruction anchors](../evidence/SYMBOL_DECISIONS.tsv), and [hashes/calls/xrefs](../evidence/STATIC_AUDIT.tsv).

## 1. The useful interface is name → retained bytes

**C1 / high confidence:** `0046FFC0` returns a payload address, not a common resource record. The evidence is the two actual return producers: `00470070` returns `record + 0x24` (`0047011C`, `004702AC`), while `00470B20` returns `package_bytes + member_offset` (`00470BAA..00470BB2`). Callers `004B41E0` and `004469A0` pass these addresses directly to BWD2/GEO consumers. The old `uint *` / `int` decompiler result types express 32-bit values, not the semantic payload type.

[resource_design.h](resource_design.h) gives C-compatible ABI proposals and five separate, offset-checked PE32 storage layouts. `va32` means an original 32-bit address; it is not a host pointer. No struct is imposed on the Ghidra database. Descriptive prototypes are:

```c
uint8_t *res_acquire(const char *logical_name);                 // 0046FFC0
uint8_t *res_acquire_loaded_file(const char *logical_name);     // 00470070
bool res_is_indexed_or_registered(const char *logical_name);   // 00470340
uint8_t *res_acquire_pix_member(const char *key16);             // 00470B20
MountedSource32 *res_select_source(const char *key16);         // 004B2E00
uint8_t *res_read_registered(const char *key16, uint32_t *out_size,
                           uint8_t *destination, int32_t capacity); // 004B3030
```

These are proposed human-readable signatures, **not applied type migrations**. The functions use caller-cleaned x86 stack arguments and EAX returns; `00470340` and the `004B3000` wrapper express truth values. The by-value two-word basename formatter at `004AD640` is a different interface, not a pointer-based filename loader.

## 2. Normalization and lookup priority

**C2 / high confidence:** `0046FFC0` copies 16 bytes with `strncpy`, calls `_strlwr`, rejects an empty result and any result whose first four bytes compare equal to `"null"`, then reads global `00609564`. For zero it calls PIX first (`0047001D`), then loaded-file acquisition on null (`0047002E`). For nonzero it calls loaded-file acquisition first (`0047003F`), then PIX on null (`00470050`). This proves the conditional priority, not the value of that global in a particular mission. Its historical “directory first” name is too narrow: loaded-file misses may obtain ZFS members as well as loose files.

```c
/* Explanatory pseudocode; preserve the original limitations below. */
res_acquire(name):
    key = strncpy16_then_strlwr(name)
    if key[0] == 0 || strncmp(key, "null", 4) == 0: return NULL
    if global_00609564 != 0:
        bytes = acquire_loaded_file(key)
        return bytes ? bytes : acquire_pix_member(key)
    bytes = acquire_pix_member(key)
    return bytes ? bytes : acquire_loaded_file(key)
```

The local-array address test after `_strlwr` is **not** an input null check: `0046FFCF` has already called `strncpy` with the original input. The caller must supply readable, terminated filename storage. A 16-character or longer source is not guaranteed termination within the local array before `_strlwr`. The cache subsequently copies only 15 bytes, without an explicit store to name byte 15 (`00470250..00470280`); names of length 15 therefore have an additional uninitialized-termination risk. Ordinary eight-character stems plus four-character extensions fit, but these instructions do not establish a universal safe truncation policy.

**C3 / high confidence:** indexed and registered tables compare all 16 key bytes as four little-endian 32-bit differences (`00470CA0..00470CC9`), returning the first nonzero wrapped subtraction. This is neither `strcmp` nor `memcmp` lexical ordering; even bytes after a NUL participate. A short name passed through `strncpy(...,16)` is zero padded. PIX rows are zeroed then lowercased by `00470660`; direct calls to `00470B20` or `004B2E00` do not normalize or pad the supplied key. Case-insensitive cache chain comparison does not eliminate the separate case-sensitive hash calculation in `00470070`; callers should use the normalized entry path.

`004AD640` is only a name producer: it zeroes a shared 16-byte buffer at `005DABB0`, copies eight by-value argument bytes, compares with `null`, masks high bits with `0x7f`, terminates at byte 8 and optionally appends the caller's suffix (`004AD64E..004AD6E5`). The buffer is reused on the next call. It does not choose `.geo` versus `.vcf`, and does not establish thread safety or check arbitrary suffix length.

## 3. Loaded-file cache

**C4 / high confidence:** `00470070` hashes signed name bytes by `h = 2*h XOR byte`, negates a negative signed result, and uses signed remainder modulo 2009 into the pointer array referenced by `00609580`. It follows `+0x18` links and `_stricmp`s stored names. A hit removes a zero-reference record from the purge list, increments a **16-bit** count at `+0x14`, and returns inline bytes at `+0x24` (`00470084..00470123`). This is retention, not a fresh copy. Integer overflow and the `INT_MIN` negation corner case are not sanitized by these instructions.

On a miss it may evict one purge-tail record when global `00609584 >= 00609588`. Then it queries `004B3310`; size <= 0 returns null. Allocation is `size + 0x24` on heap `00609594`, with purge-and-retry on allocation failure. `004B3000` loads into the inline payload; a false return frees the uninserted allocation and returns null (`00470151..00470200`). Only successful loads enter the hash table with count 1 and cleared purge links (`0047022B..004702AC`).

The header's `+0x10` is the size queried **before** loading; the out-size variable passed to the load can change, but the header store uses the saved original size. Do not assume a concurrent file change is reconciled. `+0x16..17` has no established semantic meaning or explicit initialization in this path.

**C5 / high confidence:** `00609584` counts records, despite the old `g_loaded_resource_cache_used_bytes` annotation: successful insert increments it by one (`0047029B..004702A7`) and eviction decrements it (`0046FCBF`). `00609560` instead subtracts/adds header-plus-payload bytes. We propose “loaded record count” and “remaining byte budget” respectively; neither global was renamed. The threshold's initialization/runtime configuration was not part of the audited cluster.

## 4. PIX members retain whole PAK payloads

**C6 / high confidence:** `00470B20` searches the sorted 28-byte member table (`0058D91C`, count `0058D928`). A hit chooses a 24-byte PAK entry by member `+0x10`. Its `+0x10` caches the **whole PAK byte pointer**, obtained through `00470070(package_name)`, not recursively through the general entry point. Each member acquisition increments PAK entry `+0x14`; the returned bytes are the package pointer plus member `+0x14`. Member `+0x18` length is not consulted during acquisition.

The dependency `00470660` supplies strong construction evidence: 64 × 24-byte initial PAK entries, growth and final resize; names copied from `*.pix` enumeration and changed to `.pak`; member storage allocated as count × 28 bytes, zeroed per row, filled by `%s %d %d`, lowercased and sorted (`00470667..00470722`, `00470882..00470AAF`). This establishes member name versus backing filename and offset versus length. It does not prove safe handling of malformed PIX text or duplicate keys. The acquisition code has no visible offset/length bounds check.

## 5. Registration resolves a source; it is not another payload cache

**C7 / high confidence:** `004B2E00` first searches 48-byte registered-key rows at pointer `005DACC8`, count `005DACCC`, using a copied 16-byte key. The remaining 32 bytes are a membership bitset across 256 static source slots. Registration `004B2B30` allocates/resizes key rows, zeroes new rows, sets the chosen source bit and sorts them; source rows are static at `006592E0` with stride `0x10c`.

The return is a **source row**, not the 48-byte key row. `004B2E8A..004B2F01` scans source membership in increasing slot order, tracking first member, first member with `path_mode == 0`, and first such member matching selector `004FFF18`. Normally it returns the first member. If `00669EE4 != 0` and a zero-mode member exists, an earlier nonzero-mode first member still wins; otherwise it prefers a zero-mode member matching the selector. With no matching selector it closes cached ZFS handles in active sources, calls callback `006562D0` with drive/root metadata, returns null on callback failure, and on success updates the selector and returns the first zero-mode member (`004B2F03..004B2FF5`). This is source-selection logic with side effects. Exact media policy names remain provisional.

**C8 / high confidence:** `004B3030` formats the selected row's path. Nonzero `+0x100` copies its path directly. Zero uses a root indexed by `+0x104` (root stride `0x300`) when `00669EE4 == 0`, or a drive-prefixed path otherwise. A case-sensitive `strstr(path, ".zfs")` chooses archive handling; **the mode field is not itself loose-versus-ZFS type**.

For a loose path it appends the logical filename, opens `rb`, measures length, writes `*out_size`, allocates on the registration heap if destination is null or checks the supplied capacity, then reads one complete item and closes the file. Read failure frees only a self-allocated buffer. For a ZFS path it lazily opens/stores a handle at source `+0x108`, then delegates to `004B9BA0` for a caller buffer or `004B9DB0` for allocation. This run verifies that dispatch, **not archive decoding internals**. It does not retry a different registered source if the selected source cannot open/read the resource. `00470070` normally selects once for size and again for load, so a cache miss is not one indivisible selection transaction.

## 6. Queries, callers and evidence reconciliation

**C9 / high confidence:** `00470340` lowercases a 16-byte copy and tries `00470C70`, then `004B34F0`. These are binary searches of member and registered-key tables. It does not inspect loaded-cache hash buckets, open files, run source selection or verify that a PAK/archive member remains readable. It also lacks the acquisition entry's `null` prefix rejection. “Indexed or registered” is the narrower semantic name.

**C10 / high confidence with unresolved collision behavior:** successful acquisition requires a matching **name-based release**, not `free(returned_pointer)`. `0046FD40` lowercases the name and always tries indexed release first; `00470BC0` decrements the shared PAK member count and releases the one loaded-file reference to the PAK at zero. Direct loaded-file release `0046FE30` decrements the 16-bit count and queues zero-reference records for purge. Zero references permits later eviction; it does not immediately free the allocation. The size helper `0046FEE0` also tries indexed size first, independent of `00609564`. Thus no universal collision-safe acquire/size/release contract is established for a name present both as direct file and PIX member. See [unresolved cases](UNRESOLVED_SEMANTICS.md).

Original caller `004B41E0` checks its own null/sentinel inputs, acquires, gets size, parses, and releases at `004B4278` even after parse failure. Original GEO loader `004469A0` acquires at `00446A3E`, obtains size, constructs a separate GEO object at `00446A8E`, releases source bytes at `00446A9E`, and caches the resulting handle in different 32-byte geometry records. This independently explains why GEO pointer reuse is not proof of RES-cache reuse. TMT descriptor decoding `0044AB90` allocates its own frame-name storage; owner/material slot caching remains an adjacent layer.

The accepted vehicle run `i76exe-20261022T232710Z-96c58505` supplied authentic `noal01.vcf`, `nobus1.vcf`, GEO and TMT bytes but its `I76_IntegratedVcfResourceProbe.java:58..60` intercepts **0046FFC0, 0046FEE0 and 0046FD40**. Its native consumers and byte digests are valuable evidence for caller interfaces, not execution of this acquisition path. The accepted lazy-texture run `i76exe-20261023T042231Z-4e59e782` tests owner-slot invalidation/rebind with substituted payload services; those slots are not LoadedFile32 records.

Historical ZFS extraction and material/vehicle resolvers independently identify bytes, resource IDs and PIX offsets. Exporter preferences such as VQM-first, direct-MAP overrides and combined Python indexes are not lookup priority in `0046FFC0`. This run confirms the original dispatch and record arithmetic without asserting that every historical inventory row was selected by retail code. It does not assign original `.c` module names or close RES runtime validation.
