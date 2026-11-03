# Boundary analysis — independent pilot 2

Boundary confidence rates **separation into original source files**, independently of the strength of within-fragment coupling. None is HIGH. Nearest functions mean adjacent **defined entries in v100**; intervening bytes may be padding, tables or unrecognized code. [boundaries.tsv](../evidence/boundaries.tsv) records all 15 tested pairs and exact gaps; [instruction_evidence.tsv](../evidence/instruction_evidence.tsv) provides the reviewed original PCs. B01, B06, B09 and B10 have explicit manual instruction checks on both sides. Contextual proposals do not add assignments outside the 42 bounded functions.

## B01 — proposed, MODERATE

Left `004937C0 terrain_runtime_finalize_or_draw_helper`; right `00493910 terrain_reverse_tag_handler`.

Separation evidence: The left function reads mesh/render count 006442EC at 00493839, shares spacing/render state with earlier 00490A00, and writes derived view state. The right function clears loader page-source/map buffers and dispatches its descriptor table (00493927/00493942). Distinctive state clusters change across this adjacent pair.

Common-ownership evidence: The loader exit callback calls the map initializer; that initializer calls loader accessors, and both ultimately describe the same terrain. This may be one terrain source with staged data and helper functions.

Compiler/linker alternatives and judgment: Seven bytes between defined bodies is ordinary layout/alignment, not corroborating evidence. Separate files, adjacent source routines in one file, or linker function contributions all fit. MODERATE is a state-ownership hypothesis, not a recovered object boundary.

## B02 — rejected, LOW

Left `004929B0 TER_ComputeVisibleTerrainBounds`; right `00493080 build_runtime_terrain_page_grid_from_zmap`.

Separation evidence: A proposed sampler/visibility versus grid-setup split would distinguish runtime sampling from initialization.

Common-ownership evidence: Visibility 004929B0 reads 006442C4 and calls 00493550; setup 00493080 writes that reciprocal and map-level render settings. Earlier material sampling precedes visibility, and final map/render work follows later samplers. The actual arrangement defeats a clean semantic cut.

Compiler/linker alternatives and judgment: Six alignment bytes do not identify a TU. One file with mixed initialization and queries is at least as plausible as distinct files using shared globals. Reject this cut as a supported source boundary; LOW is confidence in separation.

## B03 — ambiguous, UNKNOWN

Left `00493080 build_runtime_terrain_page_grid_from_zmap`; right `00493150 load_another_satellite_map`.

Separation evidence: The right member is a Ghidra-marked forwarding thunk rather than a grid implementation routine.

Common-ownership evidence: The thunk has no state of its own and occurs immediately after setup; it may be a startup wrapper in the same original file.

Compiler/linker alternatives and judgment: Original 00493150 jumps to 00493C10, whose loader storage lies outside this local sequence. Three-byte gap and a linker/compiler stub do not locate the wrapper source. UNKNOWN; leave thunk unassigned.

## B04 — ambiguous, UNKNOWN

Left `00493150 load_another_satellite_map`; right `00493160 TER_ReadPackedTerrainGridWord`.

Separation evidence: The left thunk forwards to loader cleanup; the right member reads the installed sampler grid.

Common-ownership evidence: A wrapper between initialization and queries can be normal source order in one TU. No distinctive state belongs to the thunk.

Compiler/linker alternatives and judgment: Eleven alignment bytes plus a five-byte jump fit a generated or deliberate forwarding routine. UNKNOWN, not two asserted original source boundaries around a tiny function.

## B05 — proposed, LOW

Left `004125C0 finalize_loaded_fsm_runtime_tables`; right `00412630 parse_fsm_tactics_tag`.

Separation evidence: Finalizer ends the common load/validate/relocate driver; the next function begins a tactics-record scan at 004C3E50, followed by two related tactics consumers. The reader base/cursor family belongs to preceding import helpers, whereas the tactics family is structurally different.

Common-ownership evidence: Finalization, tactics and interpreter exchange imported tables/mission actors. The reader and VM globals are closely spaced, diagnostics occur in a nearby literal sequence, and tactics is invoked by host dispatch. A single mission TU naturally contains all these helpers.

Compiler/linker alternatives and judgment: The 13-byte gap is consistent with 16-byte function alignment. No linkage, relocation or object contribution metadata distinguishes the alternatives. LOW: the weakest proposed internal separation.

## B06 — proposed, MODERATE

Left `00412830 update_vehicle_ai_target_and_attack_state`; right `00412CC0 reset_fsm_instruction_minmax_state`.

Separation evidence: AI update addresses tactics configuration and callbacks (00412AA0→004C3E54); the next routine resets VM budget/deadline cells (00412CC0→005244DC, 00412CCA→005244E0). Subsequent VM functions own this three-cell family exclusively among defined-function direct references.

Common-ownership evidence: Dispatcher 00412CE0 calls the AI update repeatedly, sometimes passing the budget latch. Configuration and VM execution could be successive functions within one original file; state is not proven file-static.

Compiler/linker alternatives and judgment: The 144-byte interval is largely compiler switch-table/index data, referenced by 00412916 and other computed jumps, not a giant linker separator. Discount gap magnitude. MODERATE comes from the structural state change and contiguous clusters.

## B07 — rejected, LOW

Left `00410720 load_serialized_fsm_runtime_tables`; right `00410A10 fsm_resolve_host_command_name_to_opcode`.

Separation evidence: Serialized reader state stops appearing after 00410720; the next large routine resolves command strings.

Common-ownership evidence: Finalizer calls the resolver and outer 00409740 drives both loading and finalization. No independent source provenance distinguishes reader helpers from load-time validation/relocation.

Compiler/linker alternatives and judgment: Ten alignment bytes are routine. A separately compiled binary reader is possible, but source author ordering is equally plausible. Rejected at LOW separation confidence; the wider import/preparation fragment retains explicit uncertainty.

## B08 — ambiguous, LOW

Left `004149F0 process_pending_fsm_instruction_list`; right `00414B50 reset_fsm_runtime_progress_counter`.

Separation evidence: The next functions manipulate a distinct progress family 00524540/44/48/4C rather than the deadline/budget cells.

Common-ownership evidence: The same outer runtime 0040A320 calls scheduler and progress helpers, and startup initializes both. The dispatcher also calls the following teleport function. These could continue the VM TU.

Compiler/linker alternatives and judgment: The 13-byte gap and requested investigation endpoint are not original file markers. LOW/ambiguous. Do not claim the candidate truly ends at scheduler 004149F0.

## B09 — proposed, MODERATE

Left `00470340 resource_exists_in_cache_or_search_paths`; right `004703A0 load_localized_texture_or_vqm_to_buffer`.

Separation evidence: Left membership helper delegates to PIX 00470C70 and registered membership 004B34F0; right wrapper begins the repeated shared-scratch name-building sequence using 0058D908. The preceding cache/API block instead references cache hash/accounting state.

Common-ownership evidence: Resource facade and texture naming are both API glue; they may be adjacent routines in a common resource source. Their different state can result from different helper purposes in one file.

Compiler/linker alternatives and judgment: Fifteen bytes is ordinary alignment. The sustained three-wrapper scratch ownership distinguishes the fragment, while inlining/shared headers could duplicate it across files. MODERATE, not HIGH.

## B10 — proposed, MODERATE

Left `00470580 release_localized_texture_resource_variant`; right `00470660 load_pix_pak_resource_index`.

Separation evidence: The left release wrapper writes the same name scratch as the other two wrappers and calls 00447B20 at 00470644. The next function initializes PIX/PAK arrays 0058D920 and later 0058D91C. Each family has its own consecutive consumers and lifecycle.

Common-ownership evidence: Scratch bytes 0058D908 and array pointers 0058D91C/20 are close in BSS, compatible with one resource file. Common resource initialization later invokes both cache and PIX lifecycle routines.

Compiler/linker alternatives and judgment: Only one alignment byte separates the bodies, demonstrating that a large gap is unnecessary for a plausible boundary. Object order or same-source ordering both fit. MODERATE; strongest bounded resource separation, jointly with B09.

## B11 — rejected, LOW

Left `004B2D50 format_registered_resource_record_path`; right `004B2E00 resolve_virtual_filename_to_mounted_source`.

Separation evidence: The requested resolver neighborhood begins at the right member, but that is only an investigation anchor.

Common-ownership evidence: The preceding path formatter calls the resolver and uses the same media/path family; earlier registration and enumeration continue the same registered-source structures.

Compiler/linker alternatives and judgment: An input range start is not a TU boundary. Eleven alignment bytes add nothing. Rejected at LOW separation confidence.

## B12 — rejected, LOW

Left `004B3030 load_registered_resource_payload`; right `004B32F0 registered_resource_payload_size_context_helper`.

Separation evidence: The requested range ends with the reader on the left.

Common-ownership evidence: The next 23-byte wrapper calls that reader (004B32F0→004B3030), and the following size function uses the same resolver and path branches. The registered-source implementation plainly continues beyond the requested endpoint.

Compiler/linker alternatives and judgment: Function wrappers can be separate contributions, but five-byte alignment provides no evidence for a TU cut. Rejected at LOW confidence; do not equate our evidence limit with the original end of a file.

## B13 — contextual-proposed, MODERATE

Left `004B3550 registered_resource_lookup_context_helper`; right `004B3570 set_expected_file_crc_validation_records`.

Separation evidence: Context after registered membership/allocation helpers transitions to expected CRC-record configuration at 004B3570 and parser/CRC state near 005DB7C8/005DACD0. The reviewed source-resolver state differs from those validation/parser structures.

Common-ownership evidence: Both can be helpers in one resource/descriptor loader file. Some BSS families are adjacent and CRC validation naturally belongs to loading.

Compiler/linker alternatives and judgment: Eleven padding bytes cannot discriminate source files. MODERATE contextual transition; exact TU endpoints and membership of earlier helpers remain unassigned outside the bounded set.

## B14 — contextual-proposed, MODERATE

Left `00470CA0 compare_resource_record_16byte_key`; right `00470CD0 enumerate_logical_drives`.

Separation evidence: After PIX release/size/existence and a key comparator, logical-drive enumeration writes 00609520 and takes 005C3A20 instead of the PIX array state.

Common-ownership evidence: Comparator 00470CA0 is passed to both PIX and registered-key routines. It may be a generic key utility in another original file or an adjacent utility beside drive discovery; it has no distinctive state.

Compiler/linker alternatives and judgment: Six alignment bytes do not identify object ownership. MODERATE only for a structural transition to drive services, not proof that the comparator and every preceding PIX function shared a TU.

## B15 — contextual-proposed, MODERATE

Left `00493C40 zone_satellite_map_context_helper_00493c40`; right `00493C50 MATH_InitializeApproxInvSqrtSeeds`.

Separation evidence: After loader accessors/cleanup and a four-byte helper, the next function initializes inverse-square-root seed storage 00655180/00655200. Subsequent math helpers have callers across vehicle/terrain code.

Common-ownership evidence: The math initializer is used by startup, as is terrain cleanup; empty/tiny helpers do not identify the left-side TU. Some math may have been kept in an engine utility file.

Compiler/linker alternatives and judgment: Twelve alignment bytes and section ordering fit separate files or one utility source. MODERATE contextual family transition; no proven source placement for the tiny left helper.

## Cross-neighborhood resource comparison

`00470B20` and `004B2E00` are not adjacent functions; the intervening executable is outside this bounded assignment. We propose no exact physical cut between them. Separate state families (PIX/PAK arrays versus registry/source rows), each with contiguous surrounding lifecycle/accessor code, favor distinct candidate fragments. Cache calls registration and PIX calls cache: these dependencies are compatible with separate TUs, a larger all-resource TU or shared utility objects. The shared comparator is a specific counterexample to treating a shared helper as file identity. No noncontiguous cross-neighborhood merge is justified by this run.

The strongest boundary hypotheses are the sustained texture-wrapper-to-PIX state transition B10 and map-to-loader transition B01; the former still has adjacent BSS evidence for common ownership. The weakest proposed cut is B05, where phase distinction and table layout cannot exclude one mission TU. The most important rejected cut is B02: splitting physical terrain sampling from visibility would be an attractive modern module design but fails to explain original interleaving and shared map state. Large gaps after host dispatch/interpreter are switch tables, not TU markers.
