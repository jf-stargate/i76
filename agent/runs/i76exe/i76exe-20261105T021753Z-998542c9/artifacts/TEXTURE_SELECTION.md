# Texture selection and dependency contract

Candidate research, track i76exe, advisory RES/GEO/RND. Base
`999fcc0798c7756bab34d0fa46e43bf2a21e8236`. Evidence classes: **O** original
PE instructions executed in Unicorn 2.1.4 with explicit substitutions; **S**
PE-authenticated static instructions; **B** authenticated retail bytes; **D**
independently derived algorithm; **X** harness state/services; **U** unresolved.
No original Windows process or maintained reconstruction is asserted.

## Material names and owners

Prior accepted lazy-texture run `i76exe-20261023T042231Z-4e59e782` executed
invalidation/rebind with substituted texture services. Integrated run
`i76exe-20261023T044729Z-42a0573a` recorded real bus/GTSi owner material
`V1 MD UN.MAP`, TMTs `1xb1MDUN.TMT` / `4al1MDUN.TMT`, and selected first
frames `xb11mdu1.map` / `al11mdu1.map`; it substituted 004474B0 and raster.
The promoted software renderer still describes untextured bus fallback.
PR #133 supplies static sampler/table semantics, not original decoded pixels.
PR #131 and #134 authenticate outer bytes and establish provider contracts;
they did not execute original texture decoding.

**O+B+X, this run:** each connected fixture starts with the authentic TMT
resource at 0044AB90, which builds its name array; 0044AC80 creates a real
owner slot from that descriptor and the supplied owner/material identity.
0044A290 finds that slot and calls the original texture loader. First-frame
selection inside slot creation, VQM name derivation, CBK dependency acquisition,
decoding and texture pointer installation are original instructions. The owner
identity and choice of TMT/material relationship are supplied using the earlier
accepted relationship; no GEO, VTF, vehicle construction, animation clock or
scene selection executes in this fixture. Do not join unrelated runs into a
claim that one full vehicle frame executed here.

## 004474B0 actual order

1. Copy incoming name into 16-byte scratch, truncate at **first** dot, append
   `.vqm`. Search the 109-bucket decoded-texture cache using that key.
2. A matching decoded-cache row wins **before** inspecting 00609564; revive a
   zero-ref row from LRU if needed and increment its 16-bit reference count.
3. On cache miss and nonzero 00609564, acquire the incoming name first. If that
   returns nonnull, return it through the direct path; no VQM decode/cache row.
4. Otherwise query `.vqm` length via 0046FEE0. Nonzero length selects VQM; acquire
   it and then acquire the C-string dependency at VQM+8. Missing CBK reports,
   releases VQM, returns zero. It **does not fall back to MAP** after selecting
   VQM. The VQM acquisition result itself is not safely checked before use.
5. Allocate width*raw_height+8 on the texture heap, call 0044B430 with claimed
   capacity width*raw_height+24, allocate/cache a 0x24-byte record, release the
   CBK and VQM resource leases, return the owned runtime texture.
6. If VQM length is zero and 00609564 is zero, acquire the incoming name as the
   fallback. With nonzero preference, the earlier failed incoming-name attempt
   is not retried here. Missing all candidates returns zero.

Original synthetic controls in `evidence/selection.json` distinguish both
preferences, each fallback, missing CBK, all missing, and a cached VQM surviving
a later change to MAP-first preference. These are texture-format selection
experiments with supplied resource services. They do not retest original
PIX/PAK lookup or registered-source precedence.

The hash is repeated `h = 2*h XOR (byte & 0xDF)`, then wrapped-32-bit
`(h*0x6CD+0xAAB)%109`; equality is CRT case-insensitive string comparison.
Stripping at the first dot and unbounded scratch copies are not a safe path API.
The independent reader deliberately requires bounded flat resource names.

## M16 is a separate selected return

0044A290 tests supplied context+0x3C -> descriptor+8 == 1. It then calls
00471980 on owner-slot+0x38, using the slot's current frame name. A nonzero M16
return supersedes the indexed slot+0x34 for that call. Failure continues to
indexed acquisition/reuse. 00471980 replaces the **last** dot with `.m16`, tests
length, acquires raw bytes, and caches that pointer. It marks FULLRES bits if
bit 0x40000000 is absent, using the lazily initialized 1741-bit hash bitmap.
Hash membership is not exact filename membership.

**O+B+X:** both connected states subsequently take this M16 branch using
supplied qualifying contexts and an initialized empty FULLRES bitmap. Authentic
M16 headers change from `[64,0x80000040]` to `[64,0xC0000040]`. The acquired
M16 lengths are 4250 and 4284, not a tightly packed 64x64 RGB16 buffer.
No M16 payload decode, high-color pixels or software indexed sampling of those
M16 bytes is claimed. See each `m16_observation` in execution evidence.

00471C10 is a distinct pair API: primary 004474B0 result at +0, optional raw
M16 at +4 only when 00495060 observes 005DD2A8==1; returns 0/1/2. This is
**S**, not the executed owner-slot selector. PCF/hardware texture processing and
FULLRES.LST parsing remain outside the executed fixture.

## Buffer form and failure scope

004478B0 also synthesizes VQM and honors the preference global, but must not be
silently treated as a conventional capacity API. Its original comparisons allow
provided-size <= required-size and reject larger sizes in the observed branches;
the VQM decoder receives a computed required length, not the caller's actual
allocation capacity. This is **S**, not executed malformed-buffer evidence.
0044B430 itself checks only its output-length arithmetic. Allocation failures,
resource races and malformed tokens are unsafe or only partially recovered.
A modern bounded decoder should reject them explicitly.

`mcalt101.map` is a second-format **O+B+X** acquisition fixture: original loader
falls back to MAP and returns the supplied authentic resource pointer unchanged.
It establishes direct MAP ownership at that boundary, not an M16 decoder or
second direct-MAP framebuffer fixture. Exact source identities/offsets/hashes
are in selection and execution JSON. The resource provider was substituted.
