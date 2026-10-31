# Service and byte-ownership ledger

Original producer body 004791E0 and original nearest-color body 004796A0 execute intact. No table entries are supplied by the host. A host-write guard rejects every overlap with 0061B2A0..0062B29F. This run deliberately stops at 0047951E after a complete first column; runCall resumes its caller in the harness, without claiming original function return. Table allocation ownership is static image storage, not heap backing.

| Boundary | Supplied effect | Attribution limit |
| --- | --- | --- |
| Source context 3D000000+E8 | Copy authenticated ZFS m02.act (768 bytes) into a controlled 0x500-byte object | Authentic resource bytes; selection, context allocation and installation are controlled. No retail palette update/normalization or scene association. |
| 004BA090 for target 004791E0, serviced cases only | Decode ST0, truncate toward zero, logical FPU pop; return signed 64-bit EDX:EAX; ESP+=4, EIP=return; leave control word | Host numerical service, never called native CRT. All 96 before/after states retained and checked. |
| Raw 004BA090 -> 000C0BFC | No service | Exact original decode failure retained; raw call uses PR77's descriptor argument and is not an authenticated palette setup. |
| Missing context -> 00479202 source E8 | Guard before original unowned REP read | Harness ownership guard, not original validation or original error return. Zero table/pixel stores. |
| Original surface/scene/queue/command/span/raster path | Inherited PR77 declared allocation/resource/OS/CRT/camera/trig/ancillary services | Same original source/command/span/callback inputs independently compared to unchanged PR77. No host pixel writes. |
| GEO-time 004796A0 | Inherited service returns zero | Command color remains controlled; only producer-time helper executes intact. Material-color fidelity is not claimed. |

The `_ftol` convention is supported by Wine's primary [MSVCRT compatibility implementation](https://github.com/wine-mirror/wine/blob/master/dlls/msvcrt/math.c): it uses a temporary truncate rounding mode, signed 64-bit conversion with pop, restored control word and EDX:EAX result. This is compatibility-source support, not retail MSVCRT provenance. Our service covers only measured finite values. General exceptional inputs, FPU tag/status equivalence and arbitrary caller register/flag side effects are not claimed. The independent verifier checks exact measured stack cleanup, result registers, seven remaining logical FPU registers, input decoding and control word. Original producer does not branch on service-generated flags in this prefix.

Original instructions copy palette samples, initialize squared distances and nearest cache, calculate shade arithmetic, search/cache nearest indices, write 256 table bytes, read the table, and write 210 framebuffer bytes. Native setup hashes and final column snapshot confirm actual memory effects in addition to pre-instruction register/store records. Unchanged source bytes and allocation sentinels are not credited as original stores.

Inherited ledgers remain authoritative for their scopes: PR77 run i76exe-20261031T015115Z-8ced0808 and PR75 run i76exe-20261031T011731Z-307babbf, plus their accepted predecessors. Those ledgers explicitly cover controlled poses/clock/view inputs, resource providers, guarded heap backing, texture-null fallback and omitted lighting/ancillary paths. No function body inside CB00 or its table producer is patched. No accepted run or shared tool is modified.
