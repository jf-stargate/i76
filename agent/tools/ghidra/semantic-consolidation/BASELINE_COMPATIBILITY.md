# Exact inputs and compatibility

Repository `jf-stargate/i76` (ID 1240020485); authenticated protected main **3efea4bc25b2614ac93b593ebfa49e57c2170bde**; protocol **1.0.4**. GitHub branch metadata and fetched Git object agreed. Active ruleset 25664125 requires PRs, resolved review threads and `integrity`; zero formal approvals, no bypass actors, current principal cannot bypass. At bootstrap there were no open PRs. Manual human acceptance remains required for shared tooling, regardless of CI.

All four dependencies merged before bootstrap:

| PR | Accepted merge commit | Accepted input |
|---|---|---|
| #101 | 66ccee434e557df9073e188aea66c535531e01bf | v102 dispatch tool, head e38eaa0ef0bdb9b0340f9ddcfb4d727fcaffca40 |
| #102 | 0ead406484c2e1107bfbb22fd83065e45dc4cb2f | Pilot B, head 9efc790a7012e20828a61693cbfa33c2aa7396bf |
| #103 | 5f0a310109d87efd3a2f565605e166e9d1d65ef5 | Pilot A, head 205d31b3d513333546a7fe2dbc10fc3e4894ac0e |
| #104 | 3efea4bc25b2614ac93b593ebfa49e57c2170bde | Pilot C, head 08bb756c0e2c87c2a33112523c29ca13c8f7f055 |

Merged research is accepted evidence for reconciliation, not an automatically promoted behavioral specification. Existing promoted ENG scheduling, vehicle, M06 and renderer references remain separate authorities. This PR changes none of them.

## Private input actually inspected

- Available supplied export: `i76_mission_v98_verified_names.gzf`, SHA-256 **d48df73dc331b87c2bae23f4f481be102aa0a77c6baceb01687de8a6e0e57fbd**. Filename was not used as proof. Imported with no auto-analysis; program name **i76.exe**. Work-copy domain name `input` is an import label, not executable identity.
- Retail PE SHA-256 **bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3**, MD5 **a640ea0097dbb62e0c77b7f2847c7161**. Authenticated actual file and original section-mapped bytes, not only Ghidra metadata.
- Ghidra **12.1.4**, language `x86:LE:32:default`, PE32 i386, pointer width 4, image base `00400000`.
- Input: **2,102 defined functions, 235 external functions, 2,337 total**. The function-manager count includes externals; the body iterator does not. This measured distinction reconciles the apparent 2,102/2,337 discrepancy for this input. It does not establish that all older trials were identical.
- Input symbol table: **27,100 entries**, data-type inventory **359 entries**, comment inventory **3,377 address/kind rows**. Complete private inventories include data-type paths, sizes and components; public digests are in `capture_digests.json`.
- Input has semantic function/global aliases marked USER_DEFINED, default formal parameter names, imported platform typedefs and old comments; it lacks v99–v102 type categories. SourceType alone cannot identify the human versus an earlier migration that authored a symbol. Exact prior migration markers and measured signature/source/storage are used, not an invented author identity.

The current user-side v99/v100/v101/v102 or newer edited export was **not supplied or verified**. Compatibility is claimed only for the measured input and the disposable staged derivative. No private path or database is published; no GZF export is claimed. The validated local project is retained privately and does not replace the supplied export.

## Explicit matrix

| Migration/research | Actual supplied v98 input | Fixed staged baseline before consolidation | New integration disposition |
|---|---|---|---|
| v99 | category absent; separate preview/apply 85 changes, 1 preserved comment | present; 2,102 bodies preserved | retain prior work; spacing int conflicts with original float; height float selects valid ST0 ABI |
| v100 | absent initially; staged after v99, 14 changes | typed camera/surface/callback pointers present | preserve; no partial world prefix propagated beyond extent |
| v101 | absent initially; staged after v100, 26 changes | full 0xB0 world node, 0x0C list and active entry types | preserve opaque runtime/payload distinctions and contextual +68 link |
| v102 | absent initially; staged after v101, 16 changes | 27x0x34 class table and typed dispatch present | four required controls byte-identical as C after new consolidation |
| Pilot A | five original target bodies match; scalar grid, split normal Z | two lattice/material names and ST0 height already present from v99 | apply setup/normal/grid/constants; retain ST0 float; correct void proposal to EAX output-alias return |
| Pilot B | import/live layouts and original bodies match; no live type | target formals still default 10/15/10 words | apply live types and 12/16/12 supplied-word envelopes; preserve import/relocation scalar index |
| Pilot C | six names/parameter counts match original pilot guards | same conservative default parameters | nine default names; separate records and propagated return types deferred |

Prerequisite previews and applies were separate, not concatenated pilot scripts. Historical shared tooling was neither edited nor silently treated as universally safe. The new integration's **before** snapshot is after those prerequisites; reported new readability improvements exclude their earlier gains.

Unknown program bytes/body ranges fail closed. Unfamiliar names/signature sources/storage are preserved. Existing defined data and interior analyst labels block footprint replacement. Conflicting type definitions block dependent signatures. A baseline with equivalent pilot types under different categories may require manual category reconciliation; automatic compatibility is not asserted for it.
