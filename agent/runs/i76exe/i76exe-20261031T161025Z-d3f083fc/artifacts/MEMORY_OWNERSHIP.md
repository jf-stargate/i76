# Typed memory ownership

| Range/global | Classification | Original owner/lifetime |
|---|---|---|
| 004C2730..004C2907 | Inherited retail storage, original initialized | 00405970/00472220 projection; 00406AB0/00472990 view/corners; stable through both producers and consumer |
| 005DCEC0 viewport | Controlled input descriptor | Original camera consumes extent/mode; surface pitch/base unavailable |
| 26000000,26100000 roots; node/runtime/resource heaps | Original constructed over supplied backing | 0045EBD0, spawn prefix, 004AD6F0, 004572B0; distinct owners, parsed GEO cache may share source |
| 00542830,005428A8 | Inherited retail registry storage, original initialized | 004572B0 installs selected camera owner and unselected target |
| 40000000 M06 TER /41000000 MSN | Inherited service storage | Authenticated read-only source payload mapped by file service; original page grid 00644380 |
| 42000000..4201A5DF via 005DD320 | Original initialized over supplied backing | Original terrain source/transform then original vehicle transformed positions. Retail allocation writer 00402FAC |
| 4200D2F0..4201A5DF via 005DD2EC | Original derived pointer into same backing | Terrain auxiliary attributes; original ADD EAX,0xD2F0 at 00402FC5 and store00402FD4 |
| 44000000..4407FFFF via 005DD324 | Original initialized over supplied backing | Terrain edges/leaves then vehicle GEO records; retail writer 00402FE3. Original 00490A92 starts terrain cursor; 0045D571 reloads backing for vehicle |
| 48000000..4805A54F via 00654398/39C/3C0 | Original initialized over supplied backing, 370000 bytes | Original polygon base/active/cursor. Terrain variable stride28+24*n; kind6 stride68, kind10 stride116. Original insertion owns links/cursor |
| 48100000..4811F3FF via 00654390/3B8/3BC | Original initialized over supplied backing,128000 bytes | Secondary spans; not claimed exercised in this pass |
| 48200000..4820BFFF via 006543B0/384 | Original initialized over supplied backing | Primary4096x12 buckets; head/tail/count; both types share table but distinct dispatch semantics |
| 48300000..4830BFFF via 00654388/3A8 | Original initialized over supplied backing | Secondary buckets; initialization clears +0/+8, not identically all dwords |
| 48400000..48400B3F via 006543B4/3A0/38C | Original initialized over supplied backing | Effects list/current/limit, original cleanup argument1 clears state |
| 006543AC/3A4 | Inherited retail globals, original initialized | Terrain establishes -300/source-derived max; no supplied4095 bound. Consumer resets ±1e6 |
| 30010000..30020800 | Controlled call/stack backing | Direct entry, original stack scratch; no emulator resets after scene setup |

Original software scheduling: 00401DE1 terrain, 00401E2C vehicle visibility, 00401E8D consumer with cleanup1. This experiment invokes those bodies directly in that order. Roads/skids/flamer/dust/tracers/HUD/particles/sky/device/timing boundaries are omitted; full frame dispatch is not claimed. Camera/arena lifecycle is retained across the bounded subset.

Terrain scratch becomes reusable after original emitter/clipping copies final vertices into polygon storage. Vehicle overwrite of source scratch does not imply polygon queue overwrite. Standalone verification ties submitted terrain bytes to those copies and all vehicle geometry to retail GEO. Source scratch allocation/install prefix00402F98..00402FF7 executes original instructions, requesting108000 and524288 bytes; no assumed disjoint auxiliary allocation remains. Capacity exhaustion is not tested. Original consumer clears primary buckets at 0048FD6D, resets polygon cursor at 0048FD7B and depth sentinels at 0048FDE2/DEC. No host reset occurs between original producers.
