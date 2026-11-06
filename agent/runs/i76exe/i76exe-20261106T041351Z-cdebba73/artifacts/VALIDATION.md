# Validation and coverage

Independent original-geometry prediction: **109163 passing checks** over 20 scenarios (18 with walker output, two original height rejections). Exact attempts/order/source indices, every plane input triple including facing-filtered candidates, anchors, turn scores, band pairs, fallback decisions, clip counts/rejection stage, emitter returns, cursor progression and final bin ownership match. This count includes empty-bucket chain assertions and is not a count of independent scenes.

Unchanged #140 source/camera/clip/bin verifier: **89,150** checks for primary/contrast/below, including its mutation controls. Five additional original-trace corruptions are rejected (index sequence, anchor, turn score, arena retirement and shade band). Combined scientific count in manifest/validation: **198318**. Asset-free predictive/negative/hash and trusted integrity checks are reported separately.

| Case | Leaves | Whole | Triangles | Attempts | Accepted bins |
| --- | ---: | ---: | ---: | ---: | ---: |
| below | 0 | 0 | 0 | 0 | 0 |
| contrast | 30 | 20 | 25 | 45 | 13 |
| high | 79 | 51 | 134 | 185 | 42 |
| primary | 79 | 69 | 112 | 181 | 30 |
| shade | 79 | 51 | 134 | 185 | 42 |
| x2940 | 76 | 69 | 100 | 169 | 31 |
| x2953.5 | 80 | 69 | 112 | 181 | 30 |
| x2965 | 73 | 62 | 82 | 144 | 32 |
| x2970 | 72 | 60 | 86 | 146 | 33 |
| y120 | 79 | 75 | 154 | 229 | 12 |
| y20 | 0 | 0 | 0 | 0 | 0 |
| y300 | 79 | 76 | 185 | 261 | 0 |
| y40 | 79 | 62 | 68 | 130 | 47 |
| y80 | 79 | 73 | 133 | 206 | 18 |
| z47996.4 | 59 | 47 | 49 | 96 | 32 |
| z47996.6 | 59 | 47 | 49 | 96 | 32 |
| z47999.9 | 61 | 45 | 39 | 84 | 33 |
| z48000.1 | 61 | 45 | 39 | 84 | 33 |
| z48100 | 65 | 51 | 47 | 98 | 43 |
| z48200 | 75 | 70 | 91 | 161 | 33 |

All cases use original camera construction with controlled bus roots. Default=(2952.5,60,48152.5); contrast changes X to 3152.5, x*/y*/z* change the named coordinate, below changes Y to -100. Shade/high keep the primary root and add the explicitly supplied light/resource controls. Height 20 and -100 are rejected before source graph/walker. These are input configurations, not mission-authored camera recovery.

Fresh v100 import has retail-identical full executable section. Eight common #140 cases match **76** source/transform/clip/bin sidecars byte-for-byte; baseline_comparison.json retains digests. The packaged driver was separately executed for **primary, contrast, shade, high** in a second fresh imported project; all four complete trace hashes/scenario summaries match publication. The full default 20-case driver sequence was not rerun after packaging; all 20 cases were individually executed through the same observer and verified.

| Branch | Executed coverage / blocker |
| --- | --- |
| Whole success and zero-return fallback | Both executed; primary 25 and 44 respectively |
| Projected-Y and corner-facing fallback | Executed across camera corpus |
| Shade-band mismatch | 18 leaves in each supplied shade/high control |
| Triangle facing rejection and ignored returns | Executed; plane-call ordering and full attempt sequence checked |
| Depth versus screen rejection | Both compared to original projection-store evidence |
| Terminal-child midpoint / C.start / D.start anchors | Executed; D.start occurs in contrast |
| C.end and D.end anchors | Static only; no qualifying source graph in corpus |
| Additional-center | Zero authentic hits; original graph always provides a preceding anchor; predictor refuses unsupported case |
| High-color triangle scalar bypass | Executed under supplied flag; authentic aux/color/resource semantics unproved |
| General bin rejection/exhaustion | Static guards only; selected positive ordinary clips all accepted |
| Alternate emitter, degenerate/tie/nonfinite arithmetic, native draw/pixels | Unresolved; no invented expectations |

Numerical bounds and original/substituted services are explicit in POLYGON_FACING_AND_SHADE.md and EMISSION_RECONSTRUCTION_HANDOFF.md. Instruction anchors are sparse source evidence; full decompilation, game payloads, database and raw logs remain private. No maintained reconstruction tests are needed because no maintained reconstruction files change.
