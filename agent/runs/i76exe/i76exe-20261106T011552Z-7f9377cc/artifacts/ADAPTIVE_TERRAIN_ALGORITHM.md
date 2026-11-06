# Bounded retail adaptive terrain algorithm

Run i76exe-20261106T011552Z-7f9377cc; pinned main 7c315c103e6eda864f5bd9f3c3736a03b4c1fa7c. Advisory TER/GEO/RND. This is original retail x86 under Ghidra 12.1.4 with declared services, not native Windows execution. Labels in the imported database are navigation only. The entire 765952-byte executable section was compared to the licensed PE before using the current instruction listing. See instruction_anchors.tsv, selected_original_events.tsv and reproduction.json.

## Inputs and selection boundary

The accepted #76 coherent camera fixture is retained: original constructed/registered stock bus, controlled root (2952.5,60,48152.5), identity basis, original projection constructor and two camera callbacks. Contrast moves root X to 3152.5. Neither pose is claimed to be the mission's physics/spawn pose. The same original 472-byte view at 004C2730 survives selection, transform and binning. All source samples are authenticated miss8 M06, with the accepted TDEF/ZMAP/ZONE mapping; this run makes no new mapping promotion and is independent of the coordinate investigation.

004929B0 first samples bilinear height under the camera and rejects when float(cameraY)-height < 0.01. It scales camera X/Z and four original frustum corners into the source lattice. When all four corner heights are <=0, a separate ground-plane intersection branch changes their projected footprint. It expands min/max bounds using the camera and corners; root origins are (minimum & ~31)-32, and the exponent is the bit length of the larger maximum-minus-origin extent. This deliberately yields the next power of two even for an exact power-of-two extent. Original footprint point filtering, angle-based hull ordering (00492EAF FPATAN service), and oriented vertical planes remain original inputs to the independent model, not independently recovered camera-to-hull code. The primary observed root is (512,9568), side 128, three planes.

00490A00 clears frame source/list/arena state, derives two float32 LOD thresholds from the retained camera and viewport, and makes four sampled root vertices in order (x,z), (x+s,z), (x+s,z+s), (x,z+s). It seeds edges (3,2),(0,1),(1,2),(0,3), then calls 004911E0 with those edge pointers in order 3,2,1,0. Rejection before root generation leaves no candidate leaves. Edge and leaf counters are initialized only after successful visible-bounds selection; zero counts in a fresh rejected fixture do not prove their reset on a reused rejected frame.

## Exact bounded subdivision rule

Let A be vertex_a of argument edge c, O vertex_b of argument edge d, size=trunc(O.x-A.x+0.5), h=size>>1, center=(A.x+h,A.z+h). Other corner heights are c.vertex_b=B and d.vertex_a=D. X/Z and raw heights are source coordinates before view transformation.

1. If size/2 <32, for each original vertical visibility plane evaluate distance to center, radius=(size/2)*1.42. Original 004912A0 culls when both distance+radius<0 and distance-radius<0. Retain both comparisons; do not substitute a generic frustum heuristic.
2. h>=32 forces subdivision (004912F0). h==0 emits a leaf (004912F8).
3. Compute float32 squared horizontal camera distance d2. If size²*thresholdX <d2, emit a leaf (00491358). If size²>2*d2, subdivide (0049136D).
4. Replace d2's mantissa with zero by masking float bits with 0xFF800000, then multiply by thresholdZ and store float32 tolerance. This exponent quantization is an original fact, not a smooth generic quadtree error metric.
5. Compare abs((predictedHeight-sampledLow12)*size) to tolerance. First use mean(A.height,O.height) at center. Unless h==1, also test four quarter positions: (-q,+q) with mean(D,centerMean), (+q,+q) with mean(centerMean,O), (-q,-q) with mean(centerMean,A), (+q,-q) with mean(B,centerMean), q=size>>2. A strict exceedance splits at 004913F9/00491451/0049149F/004914EF/0049153B. Equality passes.
6. After all height tests pass, size<=4 emits. For larger regions the original code guards origin coordinates and pointer-grid bounds, then scans FOUR BOUNDARIES, not every interior sample: top and bottom rows right-to-left, left and right columns bottom-to-top, size samples each. Any packed word >=0x4000 AND (word&0xE000)!=0xA000 forces subdivision; otherwise emit. The four load PCs are 004915F7, 0049160F, 00491627, 0049163F; branch targets converge on 0049166C. Primary quad 165 executes word 0x6011 at 40005F3E, 00491623→0049166C, then splits. This is class 3, not a renderer material token.

The boundary scan obtains ONE page pointer for its starting coordinate and performs linear pointer arithmetic thereafter. The model preserves this behavior. It does not repair it by independently resolving a page for each boundary sample. Exact behavior when such a scan crosses an unsupported/default page, negative source coordinates, or allocation exhaustion is unresolved. Ordinary height lookups still use the accepted original sampler. Packed bit 12 remains unresolved.

## Independent reconstruction and scope

verify_topology.py independently constructs the four roots, tests the numerical predicate, and recursively constructs the shared graph. It separately replays original outcomes as a diagnostic cross-check. For nine valid M06 camera configurations, both constructions reproduce every source vertex index/XYZ and the ENTIRE interleaved edge/leaf arena bit-for-bit. No predicted decision differs from the original trace. Root origin, exponent, camera lattice coordinates, threshold bits and plane coefficients are externally provided original bounds outputs; camera-to-visible-hull equivalence is not claimed.

Source midpoint writes, graph structure, original flattened loops, emitter reversed source copies and exact fan membership are checked independently. Full shading/facing and emission-attempt selection are not independently reproduced. This distinction matters: identical source graphs do not certify an entire render mesh or image. See VALIDATION.md and the handoff.
