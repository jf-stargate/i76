# Palette arithmetic: complete conditional generation and isolated CRT dependencies

This run completes original-instruction null-LUM generation and return with explicit finite truncation services, compares complete 65,536-byte outputs with two independent models, and isolates the remaining retail CRT dependency. Gamma remains a conditional family of tables: original instructions plus interchangeable, identified power services produce materially different bytes. None of the published gamma hashes is certified as the retail Windows result.

Research only, binary track i76exe, advisory RND / RES. Base commit `999fcc0798c7756bab34d0fa46e43bf2a21e8236`. Retail PE SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`; v100 GZF SHA-256 `f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0`. See manifest for measured MD5, private storage references, artifact digests and runtime identities.

## Evidence and novelty

PR #133 (merge `6f8c668`) established RGB8 source bytes, backend correction timing, LUM axes, descending column generation, first-query nearest-cache reuse and extension rows. PR #81 established one original-produced column with a supplied finite `_ftol`; its subsequent [promotion](../../../../promotions/rnd_original_shade_column_20261031.md) deliberately limited the claim to that column and bounded raster consumption. This run preserves those conclusions. The newest accepted run at bootstrap was PR #134, ZFS logical resources; no open PRs existed. No accepted complete null-LUM or exact gamma numerical experiment was found. The live ruleset was active, requiring PRs, resolved threads and `integrity`, with zero required formal approvals and no bypass actors. Publication is a proposal, never self-merge.

New evidence here is full generator execution, native x87 comparison across precision/rounding modes, every original conversion result compared with exact rational arithmetic, full gamma generation under named substitutes, direct cache/tie controls, complete output hashes, and the executable's startup precision request. `evidence/arithmetic_audit.json` contains curated x87/p-code/control-transfer metadata and retail function-region hashes. It contains no full function exports or executable payloads.

Evidence labels used below:

- **O-G**: original retail instructions in read-only Ghidra emulation, with substitutions stated.
- **O-H**: authenticated retail instruction regions executed by the host's native 32-bit x87 compatibility mode. This is a controlled Linux process, not a retail Windows process.
- **D**: independently authored C/x87 or Python exact-rational calculation.
- **X**: harness-selected context, control word, resources or import service.
- **S**: static original-instruction evidence; **U**: unexecuted or unidentified retail runtime dependency.

## Null-LUM control flow, ABI and ownership

`004791E0` takes two caller-cleaned stack arguments: context and optional LUM pointer. It saves EBX/EBP/ESI/EDI, allocates 0x1C bytes, and returns with ordinary RET. There is no allocation, local error return, palette-length check or null-context check. Invalid pointers, corrupted global state and imported-service exceptions are outside its success domain. Do not convert it into a recovered Boolean API: on the observed generation return EAX is 256 from the loop, not an explicit success code. The supplied path leaves incidental EAX after cache invalidation. Its meaning is not established as a status contract.

The original first snapshots context+0xE8..+0x3E7 to `006432E0` (768 bytes), even when LUM is supplied. If global pointer `0059BB88` is zero, it sets that pointer to `0059B788` and fills 512 dwords for signed differences -256..255 at `0059B388..0059BB87`. Otherwise it trusts/reuses the pointer and existing squares. It unconditionally resets 32,768 cache bytes at `0063B2E0..006432DF` to FF.

A nonnull second argument selects the 0x4000-dword copy to `0061B2A0..0062B29F` at `0047924C`, then returns at `00479255`. O-G verifies the complete copy of an authored asymmetric 65,536-byte fixture, cache invalidation, no additional conversions, and successful return. This second invocation also exercises square-table reuse after generation.

Null selects generation. Columns increase 0..255. Each column writes active rows 31..8, then 7..0, then 112 copies of row31 into rows32..143 and 112 copies of row0 into rows255 down144. The outer increment and test at `0047951E..2F` reaches RET `0047953C`. O-G counts 8,192 generator nearest calls, 24,576 generator conversion calls and exactly 65,536 generator byte stores. Three extra direct nearest queries are separate controls in the final probe metadata. The table is row-addressed `L[row*256+column]`, while generation is column-major. No LUM file is written; storage is static and later runtime column updates remain the separate #133 contract.

## Exact arithmetic and memory spills

For each RGB byte x, with `op` meaning an x87 arithmetic operation at the selected PC/RC and `f32` meaning a binary32 store at RC:

```
initial = float32_bits(0x3C23D70A)
norm    = float32_bits(0x3B808081)
a       = float32_bits(0x3D25294A)
b       = float32_bits(0x3D6E23B9)
state   = initial
step    = f32(op(op(op(x * norm) - initial) * a))
for row = 31 down to 0:
    q[row] = clamp_signed32(low32(ftol(op(state * 255))), 0, 255)
    state = f32(op(state + step))
    if row == 8:
        step = f32(op(op(1 - state) * b))
```

The initial x87 subtraction result is not first narrowed to binary32. Nor is `(1-state)` narrowed before the second multiplication. Both steps are stored as binary32; each recurrence addition is stored as binary32 after every iteration, including the final iteration of each phase. `255` and `1` are exact binary32 constants. `1/255` here is the specific **binary32** constant, not exact rational 1/255 and not the gamma routine's double constant. The initial channel normalization uses FILD from a dword; all byte inputs are exact integers.

The red/green/blue state slots in the post-prologue stack are +0x30/+0x34/+0x10, and their step slots are +0x18/+0x1C/+0x20. Temporary PUSH arguments shift accesses by 12 bytes around nearest calls. The first recurrence begins at `00479394`; red is finally stored at `004793AD`, green at `004793B9`, blue at `004793C5`. Second-phase stores are `004794B8/C4/D0`. Initial step/state stores are `004792F3`, `00479309/0D/11/15/19`; second steps store at `0047940D/1A/24`. The audit records original instruction semantics and PC-free p-code for these boundaries.

The rational model rounds each arithmetic operation at precision24/53/64 and each spill at precision24, under nearest-even/down/up/truncate RC. It uses integer numerators and denominators; Python float and Python pow never supply LUM arithmetic. Its domain is finite normal palette arithmetic with masked exceptions, not generalized x87 exception/status/tag emulation.

All 256 possible byte-channel inputs and all 32 converted levels were compared under all twelve tested control words. The converted vectors agree across modes. The native original FTOL-result sequences for a synthetic palette whose channels cover all byte values independently agree with those vectors in all twelve modes. This supports mode-independent **final LUM byte generation within this domain and the finite truncation service contract**, even though intermediate steps/states differ. It does not generalize to arbitrary floats, reserved PC=01, unmasked exceptions, arbitrary CRT conversion, or gamma.

Early-spill arithmetic is still wrong as an intermediate contract: channel4 at row7 has correct second step `15364765/268435456` versus early-spill `3841191/67108864`. Both convert that query to the same integer. The fixture deliberately reports zero complete-table differences for this counterfactual instead of inventing an output discrepancy. `precision_examples` retains exact rational differences; complete-table hashes alone would miss them.

## Nearest search and cache

For clamped RGB8 queries, key = `(R>>3)*1024 + (G>>3)*32 + (B>>3)`. FF is the empty sentinel. On miss, sum signed integer squared channel differences over candidates0..254 and replace the current minimum only on strict less-than. Maximum distance is195075, so these bounded distances do not overflow signed32. Candidate255 cannot be returned. Fill the cell using the **unquantized first query**; subsequent queries reuse its byte without searching or measuring distance. This retains the #81/#133 result.

Only AL is a stable return contract of `004796A0`: the cached hit path leaves higher EAX bits from the cache address. The generator masks EAX with FF before storing. The independent model restricts queries to RGB8; the original helper itself does not validate its signed stack arguments before shifts/addressing.

O-G direct control with palette entries0=(0,0,0),1=2=(4,0,0),255=(2,0,0) returns 0 for query(2,0,0): first-minimum tie and candidate255 exclusion. Query(4,0,0) then returns cached0. After original cache reinitialization, the same query returns1. Complete synthetic comparisons show 553 differing bytes if cache is disabled,149 if ties choose the last candidate, and1214 if row-major generation replaces column-major generation. See machine-readable differential fixtures.

## Gamma: recovered exact boundaries and unresolved power

`00479860` aligns ESP to8, saves callee-saved registers, puts ten exact **binary64** exponent constants on the stack, and writes ten consecutive 256-byte rows at `006095A0..00609F9F`. It has no initialized guard, no allocation/free, no local error path, and recomputes all entries each call. Static caller `00402DA9` follows `00493C50`, a separate table-initialization routine that does not set CW. The accepted correction consumer chooses numbered slots1..10; slot3 is exponent1. No actual displayed palette or device call is executed here.

For each binary64 exponent e:

1. FLD binary64 1 at `00479915`; FDIV binary64 e at `0047991B`; **FSTP binary64 reciprocal** at `00479923`.
2. For v=0..255, reload that reciprocal, FILD v, multiply **binary64** constant bits `0x3F70101010101010` at `0047992F`, and FXCH. The call at `00479937` passes ST0=reciprocal exponent, ST1=normalized base to `_CIpow` thunk `004BA2B6` → IAT`004BC1FC`.
3. The caller does not narrow normalized base to binary64 before the import, and does not narrow the returned ST0 before multiplication by binary64 255 at `0047993C`.
4. `_ftol` thunk `004BA090` → IAT`004BC27C` converts that product. Store AL at `00479947`. There is **no explicit endpoint fixup or clamp** in this routine. Overflow/nonfinite outputs therefore depend on the service and low-byte result; they are not a saturating-table contract.

This is not safely reducible to a host `int(255*pow(v/255,1/e))`: where each boundary rounds matters. The model verifies all 2,560 exact power operands and all returned-value arithmetic/stores against captured original-service traces. Independent C constructs the tables separately under the same explicitly selected service. Full-table and individual-row hashes are published.

There is also a startup precision request. Original call `004BA171` reaches helper`004BA320`, which pushes mask`0x30000`, new value`0x10000`, then calls`004BA340` → imported `_controlfp` at IAT`004BC1B8`. Microsoft's [documented control masks](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/control87-controlfp-control87-2) identify this as a 53-bit precision request. This is a static call/argument observation plus documented ABI interpretation. The external CRT startup was not executed. The exact loaded DLL, incoming RC/exception masks, later call graph and intervening external changes remain unverified. Accordingly53-bit nearest is a relevant conditional case, not a measured retail-process CW. A listing-wide audit also finds FLDCW operations and one FINIT elsewhere; it does not assert global immutability of CW.

## Conditional numerical results and what they establish

Three corpus-selected retail palettes m05.act,m15.act,t01.act are reauthenticated against original ZFS records and the accepted #133 corpus, without installing callback correction or entry-zero normalization. Synthetic gray, permuted RGB and duplicate/tie palettes are authored by the harness. These are selected contexts, not proof of the game's scene or backend selection. An initial m02 experiment reproduces the #81 resource identity and extends it to complete generation; the finalized corpus matrix uses the three separately reauthenticated selected palettes.

For PC64/nearest (`0x037F`) and the supplied double glibc pow service, the full gamma SHA-256 is `98ec5d21af3d8b58fc1243b989897ebe30859d4276e029aeac865b99e78ed1c6`. PC53/nearest (`0x027F`) produces a different complete hash; see RESULTS.md for exact hashes generated from the evidence.

The PC64 double-power case has all endpoints0/255, yet the exponent1 slot maps input1 to0: a returned binary64 approximation multiplied in extended precision can sit immediately below1. PC53 arithmetic changes143 bytes relative to that PC64 case. PC24 changes167. Extended powl under PC64 gives endpoints0/254 and changes97 bytes relative to double pow. These comparisons expose a real unresolved service/precision choice. They cannot identify the historical MSVCRT algorithm by similarity to a resource file or a modern library.

The service ledger identifies both authored FTOL and glibc power as substitutions. Native FTOL tests cover positive/negative fractions, values beyond signed32, the signed64 boundary, infinity and NaN, and verify CW preservation. Masked invalid conversion yields signed64 integer-indefinite in the authored hardware service; Ghidra's finite converter refuses nonfinite/out-of-range input. These are test results about our services, **not recovered retail `_ftol` exception semantics**. All actual LUM conversion inputs are in a safe finite range. The external MSVCRT binary and implementation are still U.

Ghidra's p-code arithmetic does not consult FPUControlWord for the arithmetic/store operations under study. Native x87 does. A low-precision control explicitly demonstrates gamma disagreement and power-input mismatches under Ghidra, while the same instruction execution atPC64 agrees. Gamma power in Ghidra is replayed from the identified native substitute, with every operand pair checked; this is deliberately not a second independent power implementation. The independent rational and C comparisons supply separate validation of surrounding arithmetic, not MSVCRT parity.

## Boundaries and next experiment

The complete conditional LUM generator can now be reproduced without Python floating-point assumptions. Its outputs have been checked both as bytes and as full original conversion sequences. Existing retail LUM payloads are compared separately; no equality or authoring provenance is assumed. Raw context installation, backend correction and later column239 mutation remain distinct operations from #133.

The remaining retail numerical dependency is narrow: authenticate the actual 32-bit MSVCRT used by the target runtime, execute `_controlfp`, `_ftol` and `_CIpow` (including any dispatch tables, data, CPU/runtime initialization and math-error handlers), capture raw input/return ST values and CW/status, then replay this same matrix. Do not certify modern glibc, a Windows replacement DLL, or a mathematical expression as that CRT. A faithful implementation must select a documented numerical compatibility contract or leave retail-exact gamma unsupported pending that experiment. No maintained reconstruction code, canonical documentation, original assets or existing runs are changed by this proposal.
