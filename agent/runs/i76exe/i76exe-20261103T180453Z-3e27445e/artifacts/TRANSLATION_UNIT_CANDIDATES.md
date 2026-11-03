# Translation-unit candidates — Pilot 1

All assignments are inferred original-file hypotheses, not recovered filenames. No HIGH candidates. Confidence is qualitative: MODERATE needs independent structural agreement but retains alternatives; LOW is weak; unlisted functions remain UNKNOWN. Member cores may be noncontiguous and are not complete files. Boundary coordinates are VA envelopes, not exclusive ownership claims. All 42 requested-range functions, including intervening functions, appear in ../evidence/function_evidence.tsv with current v100 names.

## TU_TER_01 — MODERATE

Proposed envelope: 004927B0–004937B2, noncontiguous core; outer boundaries unresolved. Original filename: unknown.

Members:

- `004927B0` — lookup_terrain_material_index_at_world_xz
- `00493080` — build_runtime_terrain_page_grid_from_zmap
- `00493160` — TER_ReadPackedTerrainGridWord
- `004931C0` — TER_SampleSurfaceNormalXZ
- `00493550` — TER_SampleBilinearHeightXZ

Supporting evidence: All five members address page grid 00644380; four address reciprocal spacing 006442C4. Initialization writes that spacing, queries read it. This is stronger than their names. No strings unify the core.

Contrary evidence: Zero internal direct call edges and 45 outside callers: this is a public query surface, not a private helper cluster. Visibility functions intervene; the five-byte JMP at 00493150 targets 00493C10. Shared globals may simply expose an engine interface.

Alternatives: One larger terrain file including visibility/finalization is plausible; alternatively initialization and queries were separate files. Material lookup could be separate. Do not infer a boundary from the JMP thunk.

## TU_TER_02 — LOW

Proposed envelope: 00493910–00493BE7; start tentative, end open. Original filename: unknown.

Members:

- `00493910` — terrain_reverse_tag_handler
- `00493960` — report_zone_number_too_large
- `004939D0` — load_zone_satellite_map
- `00493BD0` — zone_satellite_map_context_helper_00493bd0

Supporting evidence: Three loader-side members share 005A4620/28/2C and ZMAP 005A4768/6C; setup writes arrays and loading consumes that state. Loader error/tag strings occur here; 00493BD0 calls grid initialization.

Contrary evidence: No internal direct calls among selected members; callbacks can hide relationships. The small wrapper 00493BD0 touches different state. The bounded range excludes later satellite-map implementation.

Alternatives: Group only 00493910/60/D0 and leave wrapper unassigned, or extend after 00493BD0. The loader/query split remains a hypothesis.

## TU_FSM_01 — LOW

Proposed envelope: 00410490–00412622, noncontiguous core; start open. Original filename: unknown.

Members:

- `00410490` — load_serialized_fsm_linked_state_blocks
- `004105A0` — load_serialized_fsm_record_array_with_bitfields
- `00410720` — load_serialized_fsm_runtime_tables
- `00412500` — initialize_fsm_execution_node_relocations
- `004125C0` — finalize_loaded_fsm_runtime_tables

Supporting evidence: Import functions share stream cursor 005244D0 and companion 005244D4. 00410720 calls both smaller import functions; finalization calls relocation. Only one outside direct caller for the selected core.

Contrary evidence: Three internal edges do not connect the import trio to finalization. Resolver/validation/registration intervene and finalization calls them. Earlier 004102D0 also uses the cursor, so the requested range is not a demonstrated file start.

Alternatives: An import-only file and separate link/finalization file are plausible. A larger mission loader file containing all intervening functions is also plausible. No exact split is established.

## TU_FSM_02 — MODERATE

Proposed envelope: 00412CC0–00414B42; start tentative, end open. Original filename: unknown.

Members:

- `00412CC0` — reset_fsm_instruction_minmax_state
- `00412CE0` — dispatch_fsm_host_command_record
- `00414670` — execute_fsm_vm_token_stream
- `004149F0` — process_pending_fsm_instruction_list

Supporting evidence: Reset, dispatch, interpreter and scheduler share 005244DC/E0/E4. Interpreter calls dispatch; scheduler calls interpreter. Reset establishes the same runtime state. Two outside direct callers reach this selected core.

Contrary evidence: Dispatch calls many host-command adapters across the executable and AI helper 00412830. Shared mutable VM state could cross source files. Its 398-byte post-body interval must not be equated with padding or a source boundary.

Alternatives: Dispatch and interpreter/scheduler could be separate units. One larger FSM file spanning import and AI is not excluded, but the stream-state/execution-state distinction supports testing separate files.

## TU_RES_01 — LOW

Proposed envelope: 0046FEE0–00470390; start open. Original filename: unknown.

Members:

- `0046FEE0` — get_loaded_resource_file_size
- `0046FFC0` — open_resource_file_into_memory
- `00470070` — load_resource_stream_into_loaded_cache
- `004702D0` — canonicalize_resource_key_16byte
- `00470340` — resource_exists_in_cache_or_search_paths

Supporting evidence: Contiguous API/cache group. 0046FFC0 calls 00470070; size/cache/key functions share 00609580. Cache loader uses distinctive 00609560/80/84/88/8C/90/94 state and a memory-pressure diagnostic.

Contrary evidence: Only one internal direct edge, 38 outside callers, and dependencies on PIX and registered-source services. Cache release/other management routines precede the requested range.

Alternatives: Public API wrappers and cache implementation may be separate files; a larger file extending before 0046FEE0 is plausible. This is a weak bounded core, not an exhaustive TU.

## TU_RES_02 — MODERATE

Proposed envelope: 00470660–00470BB5; end open. Original filename: unknown.

Members:

- `00470660` — load_pix_pak_resource_index
- `00470AC0` — free_pix_pak_resource_index
- `00470B20` — load_indexed_resource_record_payload

Supporting evidence: Index setup/teardown/payload lookup share 0058D91C/920 and two share 924/928. Setup writes the same pointer state read by teardown and lookup. PIX/PAK-specific literals support the lifecycle interpretation.

Contrary evidence: Zero internal direct edges. Payload lookup calls cache acquisition outside the group. Nearby index comparators and lookups after 00470B20 are omitted from the bounded membership.

Alternatives: Extend through adjacent PIX helpers after 00470B20; alternatively setup and lookup belong to different files sharing an index. Exact end unresolved.

## TU_RES_04 — MODERATE

Proposed envelope: 004703A0–0047065E; both edges tentative. Original filename: unknown.

Members:

- `004703A0` — load_localized_texture_or_vqm_to_buffer
- `004704A0` — load_localized_texture_resource_variant
- `00470580` — release_localized_texture_resource_variant

Supporting evidence: Three contiguous wrappers share six data targets, including mode 00654B80, locale state 0058D908/C/D and naming table 004F8AAF. Their instruction shapes repeat, and they call three texture services 004478B0/004474B0/00447B20.

Contrary evidence: No internal direct calls. These wrappers may have been emitted in the same broad resource file as adjacent APIs; common template or copied code can mimic TU locality.

Alternatives: A separate localized-texture wrapper file or a single broad resource module are both viable. The data switch at each edge favors a structural subregion, not a proven object boundary.

## TU_RES_03 — MODERATE

Proposed envelope: 004B2E00–004B32EA; both ends open. Original filename: unknown.

Members:

- `004B2E00` — resolve_virtual_filename_to_mounted_source
- `004B3000` — load_registered_resource_payload_bool
- `004B3030` — load_registered_resource_payload

Supporting evidence: Contiguous resolve/wrapper/read chain: 004B3000 calls 004B3030, which calls 004B2E00. Resolver and reader share 005DB998 and 00669EE4. Source-path formatting differs from loaded-cache and PIX state.

Contrary evidence: Resolver takes comparator 00470CA0 as a function pointer: a concrete cross-neighborhood dependency missed by direct-call-only clustering. Registered-source routines extend on both sides.

Alternatives: A larger registered-source file is likely a better candidate than this three-function core. Function-level linking could separate originally co-owned code; distance alone does not prove distinct files.

