# Retail terrain sampling — original C-level contract

**Evidence tier:** Binary-static technical reference, subject to the linked promotion decision; see [promotion decision](../../../agent/promotions/semantic_ter_fsm_res_20261102.md). **Executable:** retail `i76.exe` SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`. Not original developer source. Research: [Pilot A](../../../agent/runs/i76exe/i76exe-20261101T161505Z-44beefbb/artifacts/SEMANTIC_RECONSTRUCTION.md); reconciled migration: [PR #105](../../../agent/tools/ghidra/semantic-consolidation/CONFLICTS.md).

## Storage and ownership

`00493080` populates 16,384 runtime page pointers (`00644380`) initially with a shared default page, then overlays an 80×80 ZMAP at page offsets +24 in each dimension. Pointers are borrowed from separate loader-owned page storage. Each game page is 128×128 16-bit sample words, **0x8000 bytes**, not the editor working-plane 0x8004 stride. The entry's spacing is an input argument (caller `00493BD0` supplies `5.0f`); its reciprocal is stored separately. This path does not allocate the pages or establish their lifetime.

The sample word has low 12 height bits, high three material-class bits and an **unresolved bit 12**. Neither page ID nor high-bit class is a direct material-property pointer.

## Original entry points

| Address | Recovered responsibility | Critical qualification |
|---|---|---|
| `00493080` | Build page-pointer grid, store spacing/reciprocal and mode settings | Borrowed page lifetime; ZMAP bounds not proven |
| `00493160` | Return `packed & 0x0FFF` from integer lattice coordinates | Historical “packed word” name is misleading; `004931A4` is interior |
| `00493550` | Four-corner **bilinear** world-height query | Two stack doubles, **numeric ST0** result; original C float/double declaration unknown |
| `004927B0` | Rounded-sample discrete material class (`packed >> 13`) | Outside admission returns 5; invalid flattened index returns 0 |
| `004931C0` | Triangle-selected approximate normal into caller-owned 3-float buffer | Output +4, X double +8, Z double +16; **EAX returns output pointer**, no hidden return |

Lattice addressing adds 3072 per axis, splits low seven bits for local sample and higher bits for the page grid. The helper lacks an explicit **negative page-index check**; do not silently present it as safe for arbitrary int32 coordinates. World-query admission uses an x87 integer-bias idiom and inclusive normal-range sample indices, not a straightforward portable clamp.

## Numeric interpretation

The height query uses RC-down x87 FISTP to select corner samples, performs two X-row interpolations with float stores while RC is down, restores rounding control, then interpolates Z and scales to world height. Ghidra's printed `ROUND` or intermediary world-to-float casts are not a precise account of those original instructions. The material function selects one rounded sample rather than interpolating four classes.

The normal function samples triangle-specific neighbors, retains an unusual original world-minus-index branch test, calculates float slopes and applies an approximate inverse square root. This is **not** simply the derivative of bilinear height. PR #105 reconciles Pilot A's proposed void signature with static return/caller evidence: `00493210` and `00493516` reload the explicit output pointer into EAX, and caller `00440B8E` dereferences that value after the call. Whether the original C declaration used that return is not recovered.

## Unresolved / non-promoted

Grid-spacing global `006442C0` is represented as `int` by an older v99 annotation, but original float storage/consumption supports `float`. The accepted integration deliberately preserves the mismatch pending a guarded type migration. Unresolved bit12 semantics, nonordinary x87 state, NaN/extreme-coordinate behavior, loader teardown and exact normal purpose are not established.

Prior M06 terrain and editor studies corroborate limited behavior but do not establish complete original game execution or a bit-exact portable sampler. **Do not infer that this reference was verified against the private v99 GZF.**
