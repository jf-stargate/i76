# Execution, service and substitution ledger

All outputs are conditional on the stated environment. A service marked X was not executed from a retail CRT DLL.

| Boundary | Original execution | Supplied behavior / limit |
|---|---|---|
| PE/GZF inputs | S: SHA-256/MD5 authenticated; curated function regions and constants match retail PE | X: private preferred-base PE mapping in ELF32; disposable GZF import without reanalysis, read-only sessions |
| Context and palettes | O-G/O-H copy at00479202 | X: context points to an owned0x500-byte buffer; raw authenticated ACT or authored synthetic RGB8 bytes at+E8; no scene/backend installation |
| Square helper/cache initialization | O-G/O-H original code | Fresh image starts with its retail initial state; later supplied-LUM calls exercise reuse and invalidation; no nearest substitute |
| Complete null-LUM producer and nearest helper | O-G/O-H all loops, stores, branch/return behavior | No host-generated LUM inserted into the positive null path; each byte and full conversion sequence compared separately |
|004BA090 / MSVCRT._ftol| O-H original thunk through patched IAT; O-G original thunk then interception | X: native authored save-CW/set-truncate/FISTP64/restore-CW/pop; emulated BigInteger finite truncation/pop and EDX:EAX. Neither service is retail CRT code |
|004BA2B6 / MSVCRT._CIpow| O-H original thunk; O-G original thunk then interception | X: native authored CI stack adapter to identified glibc pow or powl; Ghidra replays those returns and counts exact input mismatches. Replay is not independent pow validation |
|00479860 gamma loops and stores| O-H/O-G original reciprocal, normalization, product, conversion call, byte stores and RET | Per-case CW and exact power-service semantics are required inputs; gamma is not certified retail-exact |
| Startup controlfp helper | S:004BA171→004BA320→004BA340→[004BC1B8], new10000/mask30000 | U: external_controlfp execution and full process initialization. Documented interpretation requests53-bit precision; no stock retail CW measurement |
| Supplied-LUM copy control | O-G complete original copy and RET | X: asymmetric authored buffer; this is a negative/control case, not the positive null-LUM output |
| Differential models | D: separately authored C recurrence/search, exact-rational IEEE operations/cache | No Python floating-point substitution for LUM. C gamma uses the same named power service, so it validates surrounding algorithm only |
| Direct tie/cache controls | O-G original nearest calls and original invalidation | X: authored palette/query inputs; observed AL sequence0,0,1 |
| Display, devices, Windows startup, full frame | Not executed | U: no RGB/frame fidelity or retail Windows process claim |

The fresh unserviced controls execute both original thunks and then fail instruction decoding at unresolved imported targets `000C0BFC` and `000C0CDA`. Those are GZF/PE import placeholders in this environment, not actual loaded DLL addresses and not failures observed in the retail game. `evidence/unserviced_imports.json` records them. No external service is silently approximated.

The native conversion boundary fixtures return0 for±0.999,±1 for±1.5, preserve integers beyond signed32, return maximum signed64 for2^63−1, and return signed64 integer-indefinite for2^63/+infinity/NaN with masked invalid. CW remains unchanged. Ghidra's finite service instead rejects nonfinite/out-of-range operands; physical tag/status, errno/math-error hooks and unmasked traps are not emulated. These fixtures define and test the authored services, not the missing MSVCRT implementation.

Runtime library, loader and private input digests are in `evidence/results.json:runtime_identities`. Compiler flags are versioned in `scripts/reproduce.py`; host/compiler metadata is in `evidence/environment.json`. Native execution requires Linux ELF32 compatibility and x87; sandbox compatibility system calls and Ghidra launcher configuration access required approved execution outside the filesystem sandbox. This did not authorize or perform changes to maintained source or private originals.
