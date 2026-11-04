# Original translation-unit candidates — independent pilot 2

**Result:** nine provisional TU fragments cover 41 of the 42 bounded defined functions; one forwarding thunk remains UNKNOWN. These are **source-file hypotheses**, not independently verified compilation-unit boundaries. No original filename is recovered. MODERATE is the highest defensible candidate grade in this run; boundary confidence is separately reported. Fragments may merge into larger original files and do not purport to partition the executable.

Track `i76exe`; accepted base `deaef41589671984c7e65010b2ecde351ad9ddf4`; Ghidra 12.1.4; v100 GZF SHA-256 `f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0`; retail PE SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`. PR #111 was excluded; only its publication metadata was inspected. Semantic research called Pilot A/B/C in accepted references is earlier semantic work, not PR #111's TU pilot.

Every intervening defined function is included: terrain 13, mission 15, resource neighborhoods 11 + 3. An envelope is the span from the first member entry to the last member's body end, not a claim that every byte/function inside belongs to the candidate. Members outside the requested ranges are discussed only as context. Names below are current v100 annotations, not original symbols. Counts/addresses are binary-static facts; the assignments are inference.

## TER-map

Envelope `004927B0–00493908`; **MODERATE**; original filename **unverified**.

| Member VA | Current name |
|---|---|
| `004927B0` | `lookup_terrain_material_index_at_world_xz` |
| `00492890` | `terrain_map_context_helper_00492890` |
| `004929B0` | `TER_ComputeVisibleTerrainBounds` |
| `00493080` | `build_runtime_terrain_page_grid_from_zmap` |
| `00493160` | `TER_ReadPackedTerrainGridWord` |
| `004931C0` | `TER_SampleSurfaceNormalXZ` |
| `00493550` | `TER_SampleBilinearHeightXZ` |
| `004937C0` | `terrain_runtime_finalize_or_draw_helper` |

Supporting evidence: Shared page-grid base 00644380 and reciprocal 006442C4 connect material/lattice/normal/height queries to setup. Visibility also reads the reciprocal and calls the height sampler; its private helper 00492890 has exactly one incoming caller. The final helper 004937C0 reads grid spacing and mesh state 006442D4/006442EC also used by the earlier terrain builder 00490A00. Keeping these responsibilities together is more consistent with the overlapping state than cutting solely at sampler/render semantics. P06 and B01 give original PCs.

Contradictory evidence: None of the eight selected state targets is exclusive to these eight members. Renderer functions before the requested range also own this state, and broad terrain consumers access the reciprocal directly. Only two distinct internal direct-call edges occur in the bounded fragment. This could be a larger terrain TU or multiple files sharing exported state. The five-byte thunk 00493150 interrupts the envelope.

Alternative assignments: A larger map/render TU extending toward 004907E0/00490A00 is plausible, but those functions are context, not assigned members here. Alternatively split sampling from visibility/finalization with shared extern globals. That cleaner reconstruction design is not established original file organization. This is the sole noncontiguous candidate: excluding the forwarding thunk is explained by its loader target, not evidence of linker hot/cold splitting.

## TER-loader

Envelope `00493910–00493BE7`; **MODERATE**; original filename **unverified**.

| Member VA | Current name |
|---|---|
| `00493910` | `terrain_reverse_tag_handler` |
| `00493960` | `report_zone_number_too_large` |
| `004939D0` | `load_zone_satellite_map` |
| `00493BD0` | `zone_satellite_map_context_helper_00493bd0` |

Supporting evidence: Four adjacent functions implement descriptor dispatch and callbacks. Original table 004FAE18 contains ZMAP→00493960 at 004FAE30, ZONE→004939D0 at 004FAE40, EXIT→00493BD0 at 004FAE50. 00493910 clears 005A4628/005A4768 and passes the table; callbacks share zone-count and page-source storage. P05 records the original accesses. Nearby accessors 00493BF0/00493C00 expose that storage to grid setup.

Contradictory evidence: The dispatch table also contains TREV→004B4610, outside this fragment: callback co-registration alone is not common TU ownership. EXIT calls the preceding map initializer, and that initializer calls accessors just after this fragment. A loader-owned buffer at 005A6068 is cleaned by 00493C10, whose forwarding thunk is back at 00493150.

Alternative assignments: One larger map+loader file remains possible. The loader fragment probably extends through nearby accessors/cleanup, but those are not silently added as bounded members. Assigning 00493150 to this TU is plausible but weaker than recognizing its forwarding relationship, so it remains UNKNOWN.

## FSM-import-prepare

Envelope `00410490–00412622`; **MODERATE**; original filename **unverified**.

| Member VA | Current name |
|---|---|
| `00410490` | `load_serialized_fsm_linked_state_blocks` |
| `004105A0` | `load_serialized_fsm_record_array_with_bitfields` |
| `00410720` | `load_serialized_fsm_runtime_tables` |
| `00410A10` | `fsm_resolve_host_command_name_to_opcode` |
| `004122D0` | `validate_project_wav_smk_resource_list` |
| `00412400` | `register_fsm_instance_ids_from_mission` |
| `00412500` | `initialize_fsm_execution_node_relocations` |
| `004125C0` | `finalize_loaded_fsm_runtime_tables` |

Supporting evidence: The first three bounded members share reader base/cursor 005244D0/005244D4; the whole-program inventory confines those two cells to the importer and its immediately preceding helpers 004102B0/004102D0. Finalizer 004125C0 calls the command resolver, resource validator, instance registrar and relocator. Outer caller 00409740 invokes both table loading and finalization. Original P01 plus direct_calls.tsv verify this organization.

Contradictory evidence: The preparation helpers take tables through arguments and do not touch the reader globals. Their inclusion rests on contiguous order, a common finalization driver and a load-time phase, not file-static linkage. The execution-node layout also crosses to the interpreter and scheduler. Reader and VM globals lie close together (005244D0 versus 005244DC), compatible with one larger original TU.

Alternative assignments: Keep a narrow serialized-reader TU fragment (00410490/004105A0/00410720, plus preceding helpers) separate from command matching/finalization; or merge import/preparation and execution, perhaps also tactics. MODERATE describes a plausible load-time fragment; the extended helper membership and its separation from execution are substantially weaker than the reader core.

## FSM-tactics

Envelope `00412630–00412C2F`; **MODERATE**; original filename **unverified**.

| Member VA | Current name |
|---|---|
| `00412630` | `parse_fsm_tactics_tag` |
| `00412680` | `select_ai_behavior_weighted_candidate` |
| `00412830` | `update_vehicle_ai_target_and_attack_state` |

Supporting evidence: Adjacent tag lookup, weighted selection and AI update address the same large tactics-record family beginning at 004C3E50. The parser scans with stride 0x1354 to endpoint 004D86E4; selector and update address fields within those records, and update calls selector at 00412A3F/00412BEA. Original callback calls at 00412AA0/00412B63 use field +4 of this family. Distinctive record layout is stronger than the AI labels alone.

Contradictory evidence: These initialized tables have no direct writes recorded at the reviewed absolute targets. Several references are indexed DATA references, not identified read/write access. The VM dispatcher calls the AI update, and tag lookup has mission/host callers. The adjacent VM globals and diagnostic strings could belong to a single mission source file. No exclusive mutable-state count supports this candidate.

Alternative assignments: An original tactics implementation file with VM-facing entry points is plausible. Equally, these may be three helpers inside a larger mission file. The boundary after preparation is LOW, even though the three-function relationship is MODERATE. Do not infer source privacy from a static configuration table.

## FSM-execute

Envelope `00412CC0–00414B42`; **MODERATE**; original filename **unverified**.

| Member VA | Current name |
|---|---|
| `00412CC0` | `reset_fsm_instruction_minmax_state` |
| `00412CE0` | `dispatch_fsm_host_command_record` |
| `00414670` | `execute_fsm_vm_token_stream` |
| `004149F0` | `process_pending_fsm_instruction_list` |

Supporting evidence: Budget latch 005244DC is reset by 00412CC0, written by interpreter 00414670 and read by host dispatch 00412CE0. Dispatcher writes deadline 005244E0 and action 005244E4, which scheduler 004149F0 reads; these three exact cells have no users outside the four members in the defined-function inventory. Scheduler→interpreter→dispatcher is a direct chain. P02 gives the original PCs.

Contradictory evidence: The dispatcher has 80 distinct outgoing direct edges from the group and calls the preceding tactics update; many services and execution-node layouts cross candidate boundaries. Tight coupling does not prove the latch/deadline were C file-static. Preparation and execution globals are adjacent. Later progress helpers 00414B50–00414BA0 and teleport 00414BC0 have mission/dispatcher callers.

Alternative assignments: Merge this fragment with import/preparation and possibly tactics into one mission TU. Alternatively separate interpreter and host ABI into files that share exported state. We reject a size/gap-driven cut between dispatcher and interpreter: original switch-table data occupies the gap.

## RES-cache-api

Envelope `0046FEE0–00470390`; **MODERATE**; original filename **unverified**.

| Member VA | Current name |
|---|---|
| `0046FEE0` | `get_loaded_resource_file_size` |
| `0046FFC0` | `open_resource_file_into_memory` |
| `00470070` | `load_resource_stream_into_loaded_cache` |
| `004702D0` | `canonicalize_resource_key_16byte` |
| `00470340` | `resource_exists_in_cache_or_search_paths` |

Supporting evidence: Size/acquire/cache-load/invalidation/membership routines are consecutive. Size/load/invalidation share 00609580; load also maintains cache heap/accounting/purge cells. Earlier setup/eviction/release routines 0046FA80–0046FE30 touch the same distinctive cache state. Acquisition delegates PIX or loaded cache; membership delegates PIX/registered checks. The name at 004702D0 is stale: original 0047032F calls eviction.

Contradictory evidence: Two facade routines have no cache-state writes and delegate other resource routes. Only one internal direct edge is present in the bounded group; the distinctive initializer/teardown/evictor functions lie before the range. No selected cell is exclusive to the bounded members. Calls to PIX/registered helpers do not establish common file ownership.

Alternative assignments: The cache implementation might be one file and the acquire/size/membership facade another, possibly with PIX in the facade file. Preserve the bounded fragment provisionally rather than invent a noncontiguous facade TU based solely on API semantics. A larger resource file containing wrappers and PIX is also possible.

## RES-texture-wrappers

Envelope `004703A0–0047065E`; **MODERATE**; original filename **unverified**.

| Member VA | Current name |
|---|---|
| `004703A0` | `load_localized_texture_or_vqm_to_buffer` |
| `004704A0` | `load_localized_texture_resource_variant` |
| `00470580` | `release_localized_texture_resource_variant` |

Supporting evidence: The three consecutive wrappers write the same 0058D908 name scratch buffer and nearby word 0058D90C. The whole defined-function inventory finds those exact write targets only in these three functions. They repeat a mode-dependent suffix/name construction sequence and call distinct texture services 004478B0, 004474B0 and 00447B20. P03 verifies all three writes.

Contradictory evidence: Copied source/header inline code or a shared global buffer exposed across files can produce the same pattern. The implementation could be adjacent helpers inside a larger resource file. The global mode input 00654B80 is widely shared, and nearby BSS storage alone cannot prove file separation.

Alternative assignments: A compact original texture-name wrapper file is plausible. Merge into the cache/API or PIX resource file if later evidence finds a common file identity; alternatively place each next to its texture implementation, though that would require explaining the repeated scratch ownership and adjacency.

## RES-pix-pak

Envelope `00470660–00470BB5`; **MODERATE**; original filename **unverified**.

| Member VA | Current name |
|---|---|
| `00470660` | `load_pix_pak_resource_index` |
| `00470AC0` | `free_pix_pak_resource_index` |
| `00470B20` | `load_indexed_resource_record_payload` |

Supporting evidence: Initializer 00470660 installs arrays 0058D91C/0058D920; teardown and lookup read them. Array counts 0058D924/0058D928 also recur. P04 verifies initialization/lookup binding. Neighbors 00470BC0/00470C40/00470C70 use the same arrays, so the requested endpoint is demonstrably inside a coherent implementation neighborhood.

Contradictory evidence: No internal direct edges occur among the three bounded members: state ownership supplies the relationship. Initializer uses registered-source services; lookup uses cache loader 00470070. Comparator 00470CA0 is passed by address by both PIX and registered-source routines. One all-resource file could own both state families. None of this proves original linkage.

Alternative assignments: Likely extend the fragment through release/size/membership helpers, but keep those as context here. The common comparator could be a shared utility or live in either file; do not merge PIX and registration merely because both use 16-byte keys. Nor treat the public endpoint at 00470B20 as a TU end.

## RES-registered-source

Envelope `004B2E00–004B32EA`; **MODERATE**; original filename **unverified**.

| Member VA | Current name |
|---|---|
| `004B2E00` | `resolve_virtual_filename_to_mounted_source` |
| `004B3000` | `load_registered_resource_payload_bool` |
| `004B3030` | `load_registered_resource_payload` |

Supporting evidence: Resolver 004B2E00 and reader 004B3030 form a direct dependency; bool wrapper 004B3000 directly calls the reader and converts its return. Resolver touches key table 005DACC8 and mounted-source/handle state including 006593E8; reader shares source-selection/path/media state. Earlier registration and later size helpers continue these structures. N06 and state_ownership.tsv make the cross-neighborhood relationships explicit.

Contradictory evidence: The bounded fragment omits registration, directory enumeration, size/read wrappers and membership helpers. Some state is general media/path configuration. Incoming calls from cache/PIX cross a large address interval but are normal API dependencies. A single large resource TU could still include all neighborhoods.

Alternative assignments: Expand only after further review toward 004B23E0–004B3550, or split registry selection from archive/file I/O with explicit state interfaces. Do not assign 004B3000 to cache ownership just because cache is its sole incoming direct caller. The exact start/end of this TU is unknown.

## Unassigned

`00493150 load_another_satellite_map` is UNKNOWN. Its entire body is a jump to `00493C10`, an out-of-range cleanup/accessor-family function referencing loader-owned 005A6068. Locality would put the thunk in the map/sampler envelope; target ownership suggests the loader. A linker/compiler forwarding artifact, deliberate stub or separate source wrapper can explain either placement. Original source ownership cannot be resolved from a five-byte jump. This is an assignment gap, not a missing inventory row.

Machine comparison inputs: [membership](../evidence/membership.tsv), [bounded inventory](../evidence/bounded_inventory.tsv), [connectivity](../evidence/group_connectivity.tsv), [state ownership](../evidence/state_ownership.tsv), [cross-group relationships](../evidence/cross_group.tsv), and [instruction ledger](../evidence/instruction_evidence.tsv). Connectivity counts distinct caller-entry/callee-target pairs, not callsite counts. State counts use an explicitly reviewed 36-address panel, not all globals or source-level objects. See METHOD_EVALUATION for limits.
