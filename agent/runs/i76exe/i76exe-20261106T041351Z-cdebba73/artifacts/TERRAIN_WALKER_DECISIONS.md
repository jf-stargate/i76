# Terrain walker decisions

Research-only i76exe / TER, GEO, RND. Pinned main: `19c755a77db404ba9cb0ab51f307b4261e983aff`. This extends merged PR #140 (`12a904eff8c22ab43df575cd1e9f7d2ddfc6f880`), especially its source-faithful shared edges and late flattening. No maintained reconstruction or canonical reference is changed.

## Exact ordinary decision sequence

`00491A30` traverses the linked leaf list. Let `A,B,C,D` denote leaf edge pointers at +0C,+10,+14,+18 respectively. Flatten `C` forward, `B` forward, `D` backward, `A` backward. Forward recursion (`00492270`) visits child +04 then +08 and appends signed int16 endpoint +00. Reverse recursion (`004922B0`) visits +08 then +04 and appends signed int16 endpoint +02. Save the starts of all four segments; these identify the original four corners even when the boundary has extra vertices. Append the first index as a closing sentinel; the sentinel is excluded from the whole-polygon count N.

Choose the fan anchor as described in TRIANGLE_FALLBACK.md. Initialize previous projected Y from the last boundary vertex: store `r = float32(1/Z)`, then store `previous = float32(Y*r)`. Initialize direction=0, score=0. Visit every index in the closed loop (including the repeated first index). At each visit, store float32 reciprocal and compare the extended product `current=Y*r` with stored previous. If current>previous, subtract the previous direction from score and set direction=+1. Otherwise add the previous direction and set direction=-1. Store current to float32 previous. Equal Y follows the non-rising arm. This is a projected-Y monotonicity gate, not a generic convexity or signed-area test.

The per-leaf callback runs once, with the leaf and maximum reciprocal depth, before the whole-polygon gate. It is not an emitter attempt. In this bounded ordinary path it does not create the accepted polygon records.

A leaf reaches the whole emitter iff:

1. `score == 4-N` at `00491E13/00491E15`.
2. Both corner planes `(corner0,corner1,corner2)` and `(corner0,corner2,corner3)` have strictly negative distance component at `00491ED1/00491EE6`.
3. Both corner shades map to the same masked shade band at `00492077/0049207A`.

No equal-normal or coplanarity condition appears here. The caller passes the full boundary and **first** corner-triangle shade to the emitter at `0049208A`. A nonzero return finishes the leaf; zero enters fallback at `0049209C`. Failure of any earlier gate also enters fallback without a whole attempt. Plane and shade details are in POLYGON_FACING_AND_SHADE.md.

## Measured primary sequence

The independent walker predicts the complete sequence before inspecting original decisions. Original source graph and original post-transform XYZ are its geometry inputs; no emitter list, recorded anchor, recorded planes, branch outcomes or acceptance flags enter prediction.

| Primary stage | Count |
| --- | ---: |
| Source leaves | 79 |
| Turn-gate failures | 3 |
| Corner-facing failures after passing turn gate | 7 |
| Shade-band failures with stock zero light | 0 |
| Whole attempts | 69 |
| Whole successes | 25 |
| Whole zero returns, followed by fallback | 44 |
| Fallback leaves | 54 |
| Non-anchor-adjacent fan triangles considered | 125 |
| Fan triangles filtered by plane facing | 13 |
| Triangle attempts | 112 |
| All emitter attempts | 181 |
| Accepted final bin entries | 30 |

There are five accepted triangle submissions in addition to the 25 whole successes. Attempts rejected by depth or screen clipping consume no persistent polygon arena space. A whole rejection followed by two triangles is three attempts from one source leaf, not three source polygons or three accepted entries.

## Evidence and limits

`evidence/decisions.jsonl` contains every predicted leaf boundary, anchor, score, whole planes, shade bands, fallback reason, filtered fan candidates and ordered attempts for the 18 scenarios that reach the walker. Each attempt includes original-observed indices, clip count, return and accepted status. Two additional invalid-height scenarios produce no walker/attempts. `verification.json` gives all 20 results; sparse authenticated source anchors identify the corresponding instructions.

All 20 use original retail instructions under Ghidra with explicit services, controlled original-created camera roots and licensed M06 geometry. Independent Python floating arithmetic is bounded numerical modeling, not bit-identical hardware x87. Additional-center remains unexecuted; the predictor refuses it. This is not a complete all-input or rendering proof.
