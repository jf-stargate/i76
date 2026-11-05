# Original versus supplied services

The connected result is one uninterrupted emulator state per authentic material,
with explicit root-function invocations and host initialization between stages.
It is not a continuously running retail process. This ledger applies to the
published final reproduction; earlier private failed experiments are not results.

| Boundary | Original work | Supplied replacement / value |
|---|---|---|
| PE image | Executed opcode bytes checked on every original instruction | PE sections mapped into Unicorn; zero BSS, no WinMain/CRT startup |
| CPU | Original x86 integer/x87 instructions, calls, returns | Unicorn2.1.4 x86-32; initial FPCW037F; CPU precision equivalence beyond fixtures unclaimed |
| Outer resources | Texture consumer calls original0046FFC0/0046FEE0/0046FD40 entries | Entries intercepted: bounded immutable authenticated bytes, sizes, release acknowledgement; no original RES cache/PIX/PAK/ZFS instructions |
| Outer authentication | None attributed to retail execution | Accepted PR134 bounded ZFS reader + liblzo2; accepted PR131 PIX reader; archive SHA asserted; equal duplicate member hashes required |
| TMT relationship | 0044AB90 frame decoding, 0044AC80 slot construction, 0044A290 slot lookup | Authentic TMT chosen from prior accepted bus/GTSi relationship; owner20012000 and logical material supplied; descriptor backing allocated by host |
| Windows heaps | Original allocation request sites and sizes; original structures initialized thereafter | HeapAlloc IAT redirected to deterministic A5 backing/CD guards; heap handles opaque, not initialized Win32 heaps; HeapFree acknowledged if reached |
| CRT | Original inline string copy/append/hash loops | IAT strchr, strrchr, stricmp, strncpy, memmove replaced with bounded ASCII host operations; no native CRT locale guarantee |
| Texture | Original VQM candidate, CBK string, cache row, full decoder and buffer | No host-supplied decoded pixels in authentic connected fixtures; source resources injected only at resource boundary |
| Renderer | Original row cache, plane evaluation, conversion, sample/table reads, stores, return | Root callback invocation and one packed span/command per case; controlled planes, q1, shade15*256; surface backing/pitch/offsets supplied |
| Color state | Original LUM or TBL accesses | Authentic m02.lum copied to0061B2A0; authentic m02.tbl copied to0060AFA0 with host source255 identity-row initialization; no WRLD/ACT/backend callback execution |
| High color/M16 | Original0044A290→00471980 raw selection and flag writes | Qualifying context + initialized empty FULLRES bitmap; no FULLRES.LST parser, hardware backend or M16 decoder |
| Lifecycle | Original decoded-cache hit/ref increment | No full vehicle/geometry lifetime, original HeapCreate, release/eviction/teardown execution or framebuffer display |

IAT substitutions are data writes, not replacement retail opcodes. All executed
instructions outside these named services must be file-backed and byte-equal to
the authenticated EXE. Unknown external PCs fail closed. The full executed PC
inventory carries opcode hashes and retirement counts; it does not publish bytes.
Host direct writes used for fixture setup do not trigger original-instruction
write hooks and are not counted as original framebuffer stores.

The independent decoder supplies the expected result for comparison only; it
never installs its pixels into an authentic connected texture. The synthetic
reserved-index test separately installs a copy of its own original-decoded
synthetic buffer and is labelled synthetic. No synthetic case is an authentic
end-to-end texture fixture.

Color provenance is authentic but scene selection is external: m02 tables were
chosen for the diagnostic, not established as either vehicle's active mission.
The main boundary still missing is authentic GEO/clip/draw-produced textured
commands under an original initialized scene/display context. There is no blocker
to decoded runtime pixels or bounded indexed framebuffer writes in this run.
