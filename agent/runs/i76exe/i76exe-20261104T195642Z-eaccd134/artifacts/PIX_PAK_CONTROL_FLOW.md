# Original parsing, indexing and payload control flow

Method: fresh private GZF import, no analysis or annotation changes; final audit
reopened using `-readOnly -noanalysis`. Modification number stayed 3 → 3.
`verify_instructions.py` checked all 1,559 emitted instructions and every
function-body range hash against PE section-backed bytes. `instructions.json`
contains range identities for 20 functions and 133 reviewed instruction lines;
full decompilation/inventories remain private. Descriptive names are proposals,
not original source names. This is static evidence, not observed retail execution.

## Initialization at 00470660

1. `00470667..00470677`: allocate 64 × 0x18 PAK rows (`00499D00`). Null allocation
   calls `00404D80`; that dependency displays a message and calls `exit(1)`.
2. `00470687..00470774`: `004B2AC0("*.pix", &cursor)` walks registered-key rows
   in current table order, copying their 16-byte names. Change first dot to
   `.pak`, clear PAK pointer at +10 and aggregate count at +14. Grow in groups
   of 64. Final resize is count × 0x18 (`0047077A..0047079F`). No backing PAK
   opens or byte-range validation happen here.
3. `004707C0..00470882`: first pass reconstructs each `.pix` key and calls
   `004B32F0(key,&length)`. This thin wrapper calls `004B3030` with null
   destination/capacity zero: **allocated registered bytes**, not a size query,
   despite its historical size-context annotation. Find LF, temporarily NUL it,
   scan `%d`, sum counts. `004B3550` HeapFrees successful buffers on registration
   heap `005DB990`; it is not a lookup despite its old context name.
4. `00470888..004708B0`: calloc summed count × 0x1C for member rows, then reset
   the insertion count. No validated stable snapshot ties the two reads together.
5. `004708C6..00470A8F`: second registered read, LF count split, then count
   iterations finding the next LF. Zero seven DWORDs (`004709A0`, `REP STOSD`),
   scan row (`004709C0` pushes `%s %d %d`; offset destinations +14/+18), lowercase
   key (`004709EA`), store PAK enumeration ordinal at +10 (`00470A09`), increment
   successfully ingested row count. Release buffer through `004B3550` on the
   successful count/header path.
6. `00470AA0..00470AA9`: qsort actual ingested count, stride 0x1C, comparator
   `00470CA0`. PAK-retention rows are not moved by this sort.

Neither registered allocation nor this index parser guarantees an extra NUL
terminator after file bytes. The loose branch `004B324A..004B3253` allocates
exactly measured length; it fread's that length. `strchr`/`sscanf` therefore rely
on expected text separators and may read beyond a malformed unterminated input.
The reference reader uses bounded byte operations throughout.

## Failure distinctions

| Trigger | Original instruction path / qualified outcome |
|---|---|
| Allocation failure | `00404D80` exits; different from nonfatal report_error |
| PIX absent/unreadable in first pass | `00470813..00470866`: reporter then continue outer loop |
| No first LF or invalid count | First pass reports; second pass reports (`00470A5A..00470A70`) when non-null buffer; no normal successful-buffer free on that second-pass error path |
| Second-pass null PIX | `00470923` skips that PIX; actual inserted count can be below allocation count |
| Invalid row conversion | `004709CF..00470A31` reports and advances declared iteration; successful inserted count does not increment |
| Missing row LF | Same report path, but next iteration computes the next start from null ESI+1; not safe recovery |
| Changing count between passes | No capacity guard against second-pass count exceeding first-pass allocation |
| Negative/overflowing text | No meaningful safe validation; `%d` and unsigned loop/count arithmetic cannot be treated as a supported large-file policy |
| No indexes / zero total count | Zero-size realloc/calloc semantics and null test can lead to out-of-memory termination; not a proven graceful empty-retail-init case |

`0042D5D0` is **C3 / RET**, authenticated here. A diagnostic call is not a
termination guarantee. Some error branches leak buffers or continue with unsafe
state. They must not be copied into the reader.

## Indexed operations

`00470B20`: bsearch key over member rows, return null on miss; choose PAK by
member +10 and stride 0x18. If cached PAK +10 is null, call `00470070(PAK_name)`
once. Store pointer; report if null. Then increment PAK +14 and return pointer
plus member +14. **No member length read and no decoder call.** With missing PAK,
RET reporter means count still increments and offset is added to zero; offset
zero can return null, nonzero can return a bogus non-null address. This follows
instructions; no missing-retail-PAK execution was performed.

`00470BC0`: bsearch; miss returns zero. Hit returns one even when aggregate PAK
count already zero. Nonzero count decrements; on transition to zero call
`0046FE30(PAK_name)` then clear cached PAK pointer. No per-member refcount exists.

`00470C40`: bsearch; miss returns -1, hit returns +18 length bits.
`00470C70`: same search normalized to membership Boolean.
`00470CA0`: four DWORD differences, returning the first nonzero 32-bit wrapped
subtraction interpreted as signed, including bytes after NUL.

`00470AC0`: iterate all PAK rows; for every non-null cached pointer release one
loaded-file reference by PAK name, independent of aggregate member count. Free
both arrays. It does **not** zero their globals/counts, wait for member refs,
or provide a safe subsequent name-release operation. See `RESOURCE_LIFETIME.md`.

## Dependencies and reproduction limits

`004B2AC0` enumerates unique registered-key rows, not each physical source
occurrence of a PIX name. `004B2E00` selects the source for a registered key;
`004B3030` formats its path and dispatches loose/ZFS using `.zfs` substring.
The two index passes can select/read sources separately. A PIX's and its PAK's
same-stem keys can therefore resolve from different mounted sources; there is
no serialized physical-source binding. Exact CRT duplicate sorting/search
selection is not in this PE and was not executed. No new execution framework
was built. Every published pointer-lifetime statement below is binary-static.
