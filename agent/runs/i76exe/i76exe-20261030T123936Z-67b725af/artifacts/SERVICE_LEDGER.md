# Original versus substituted services

| Area | Original instructions executed | Harness action / boundary | Evidence and limit |
|---|---|---|---|
| Terrain parsing and adaptive subdivision | `00493910`, `00490A00`, `004929B0`, `004911E0`, `00491810` and original writers | Authenticated M06.MSN/M06.TER mapped into the emulator | 267 vertices / 743 edges / 172 leaves; no source primitive buffers fabricated |
| Numerical x87 | Original callers at `00492EAF`, `004935EE`, `00493608` | Local host numerical service reproduces FPATAN/FISTP requests, as in accepted M-RND-05 | Explicit substitution; independent arithmetic verifier; not hardware x87 evidence |
| Affine transform | Original `004937C0`, scale composition at `00494E20`, vertex writes and bounds updates | Test-owned identity affine, plus separate translated affine diagnostic | Matrix inputs documented in REPORT; no original-camera provenance claimed |
| Leaf traversal and candidate construction | Original `00491A30`, callbacks `0048E190` / `004922F0`, allocator body `00490590` | Primary leaves polygon cursor `006543C0` zero. Separate diagnostic sets it to a zeroed 1 MiB arena at `0x47000000` | In primary, original allocator returns null. In diagnostic, only backing storage is harness-owned; allocator/emitter bodies remain original |
| Polygon clipping and binning | Original indirect callback `0047BF00`; bin helper `0048FE10` audited | No callback body replacement | All 139 controlled-pool candidates return zero from clip; no bin calls |
| Windows/resource and WRLD initialization | Original call sites retained where invoked | Narrow test shims for file mapping, stat, copy/string and selected peripheral WRLD services; ACT/LUM/TBL report absent | No complete renderer resource or palette initialization claim |
| Output capture | Original writes only; probe reads/copies memory after boundaries | Probe-owned trace and binary snapshots | `harnessOutputWrites=0` for native primitive buffers; snapshots are not injected into the game arena |

The pool diagnostic is reported separately from the untouched primary allocator control. It does not imply the game’s allocator was initialized equivalently in retail.
