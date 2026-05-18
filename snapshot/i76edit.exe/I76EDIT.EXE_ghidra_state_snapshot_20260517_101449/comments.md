# Comments

| Address | Function | Type | Comment |
|---|---|---|---|
| `00400000` | `` | eol | Magic number |
| `00400178` | `` | eol | .text |
| `004001a0` | `` | eol | .rdata |
| `004001c8` | `` | eol | .data |
| `004001f0` | `` | eol | .idata |
| `00400218` | `` | eol | .rsrc |
| `00400240` | `` | eol | .reloc |
| `00401a90` | `i76edit_winmain_and_message_loop` | plate | [cgpt_i76edit_level_renames_v2:high] Top-level editor startup/message loop. Evidence: title/version strings, command-line usage string, color-depth check, DispatchMessage/PeekMessage/TranslateMessage, initial load/render calls. |
| `00402290` | `i76edit_find_existing_editor_window` | plate | [cgpt_i76edit_level_renames_v2:medium] References editor title string and FindWindowA; likely single-instance guard helper. |
| `004022b0` | `i76edit_export_road_records` | plate | [cgpt_i76edit_level_renames_v2:medium] References 'Exporting Road %d.' and writes via __write call chain; likely per-road export serializer. |
| `004024d0` | `i76edit_export_one_road_geometry_chunk` | plate | [cgpt_i76edit_level_renames_v5:medium] Called by runtime road export; writes per-road geometry/segment data and participates in road chunk body size accumulation. |
| `00402550` | `i76edit_export_road_segment_mesh_records` | plate | [cgpt_i76edit_level_renames_v5:medium] Road export helper that dispatches to lower-level segment writers 00402720/004029b0 based on road/edge state.<br><br>[cgpt_i76edit_level_renames_v6:high] Road export helper called from RSEG writer. Walks road segment nodes and emits interpolated road mesh/segment records. |
| `00404710` | `i76edit_delete_selected_road_ui` | plate | [cgpt_i76edit_level_renames_v2:medium] References 'Delete this road?' and 'Delete Road'; UI command path for road deletion. |
| `00406090` | `i76edit_edit_surface_type_panel` | plate | [cgpt_i76edit_level_renames_v2:medium] References terrain surface labels such as 'Dirt(non-road)' and 'Light Vegitation'; uses dialog/control APIs. |
| `00406ff0` | `i76edit_create_main_window_and_controls` | plate | [cgpt_i76edit_level_renames_v2:medium] Startup/UI creation path. Evidence: RegisterClassA/CreateWindowExA/LoadMenuA and editor title string. |
| `00408d10` | `i76edit_load_path_records` | plate | [cgpt_i76edit_level_renames_v3] Loads PATH chunk records from the .I76 workspace stream. |
| `00408ec0` | `i76edit_save_path_records` | plate | [cgpt_i76edit_level_renames_v3] Saves PATH chunk records to the .I76 workspace stream. |
| `00409050` | `i76edit_export_runtime_all_path_chunks` | plate | [cgpt_i76edit_level_renames_v4:high] Runtime path export wrapper. Calls path-tree initialization/helper and then i76edit_export_runtime_path_tree using global path root DAT_00439be4. |
| `00409eb0` | `i76edit_load_object_records` | plate | [cgpt_i76edit_level_renames_v3] Loads OBJ chunk object records from the .I76 workspace stream; version-gated object record sizes are visible. |
| `0040a280` | `i76edit_save_object_zone_lists` | plate | [cgpt_i76edit_level_renames_v3] Writes object/zone list data during .I76 object save path. |
| `0040a400` | `i76edit_export_runtime_object_obj_records` | plate | [cgpt_i76edit_level_renames_v3] Exports object records into runtime BWD2/ODEF chunk.<br><br>[cgpt_i76edit_level_renames_v6:high] Runtime ODEF object exporter. Emits OBJ records of size 0x6c, resolves object zone origin, scales coordinates, and writes object filename/type/position fields. |
| `0040a660` | `i76edit_convert_int_to_runtime_object_scale_float` | plate | [cgpt_i76edit_level_renames_v5:medium] Converts integer object field to float and multiplies by global scale constant 004320bc; used during runtime object export.<br><br>[cgpt_i76edit_level_renames_v6:high] Converts integer object coordinate component to runtime float by multiplying by global scale constant at 004320bc. |
| `0040a680` | `i76edit_prepare_object_export_zone_lookup` | plate | [cgpt_i76edit_level_renames_v5:medium] Initializes object export support structures, walks all object buckets 00439be8..00439d28, registers each object payload, finalizes lookup, and primes zone/export state.<br><br>[cgpt_i76edit_level_renames_v6:medium] Prepares object export zone lookup state before OBJ serialization; traverses the global object bucket/list at 00439be8. |
| `0040a6e0` | `i76edit_refresh_exportable_object_zone_ids` | plate | [cgpt_i76edit_level_renames_v5:medium] Walks object buckets and updates object zone ids for selected runtime-relevant object type ids 2,3,0x50,0x51,0x52,0x53. |
| `0040ac20` | `i76edit_refresh_object_zone_membership_from_zone_map` | plate | [cgpt_i76edit_level_renames_v4:medium] Iterates object lists across 0x50 buckets and updates object +0x0c from the zone map based on object cell coordinates. |
| `0040ca50` | `i76edit_load_extended_zone_records` | plate | [cgpt_i76edit_level_renames_v3] Loads extended zone/terrain records when TREV/version is greater than 3. |
| `0040cbe0` | `i76edit_save_extended_zone_records` | plate | [cgpt_i76edit_level_renames_v3] Saves linked-list based extended zone/terrain records after the ZONE section. |
| `0040d5f0` | `i76edit_sample_weighted_height_field` | plate | [cgpt_i76edit_level_renames_v5:medium] Samples a weighted float point cloud/height helper: accumulates inverse-distance weighted contributions, clamps to 0..4095-ish range, returns float. |
| `0040d700` | `i76edit_build_distance_weighted_sample_table` | plate | [cgpt_i76edit_level_renames_v5:medium] Builds a derived double/weight sampling table from point records using distance-weighted interpolation. |
| `0040d880` | `i76edit_rasterize_sampler_to_128x128_word_plane` | plate | [cgpt_i76edit_level_renames_v4:low] Builds/updates a word terrain/zone plane by sampling a floating helper over width/height loops. Provisional until helper 0040d5f0 is traced.<br><br>[cgpt_i76edit_level_renames_v5:medium] Rasterizes a sampler into a 128x128 word plane by calling i76edit_sample_weighted_height_field over grid coordinates. |
| `0040d940` | `i76edit_convert_zone_id_to_cell_xy` | plate | [cgpt_i76edit_level_renames_v4:medium] Finds zone id origin and converts returned fixed/world coordinates back to cell x/y by arithmetic shift by 7. |
| `0040d9d0` | `i76edit_build_zone_height_or_surface_workset` | plate | [cgpt_i76edit_level_renames_v5:low] Large workset builder around zone terrain/surface data; allocates local tables and feeds runtime zone builders. Provisional until its callees are widened. |
| `0040e3c0` | `i76edit_release_render_terrain_pipeline` | plate | [cgpt_i76edit_level_renames_v2:high] Terrain release-render pipeline. Evidence: strings 'Merging Terrain map with Painted map.', 'Rendering Roads.', 'Smoothing Roads.', 'Grading Objects.', 'Filling objects with current height.' |
| `0040e790` | `i76edit_build_zone_128x128_packed_height_surface_alt` | plate | [cgpt_i76edit_level_renames_v4:low] Large terrain/zone payload builder similar to 0041aaa0, with 0x208/0x8000 work buffers and map scans. Name is intentionally provisional.<br><br>[cgpt_i76edit_level_renames_v6:medium] Alternate 128x128 zone raster builder. Shares the same terrain-plane access and 0x8000 work-buffer pattern as the runtime zone exporter, but includes an extra smoothing/sampling path. |
| `0040f4e0` | `i76edit_load_linked_object_records` | plate | [cgpt_i76edit_level_renames_v3] Loads additional/linked object records for newer OREV versions. |
| `0040f6b0` | `i76edit_save_linked_object_records` | plate | [cgpt_i76edit_level_renames_v3] Saves linked object records after the base OBJ section. |
| `0040fa00` | `i76edit_export_runtime_all_linked_object_chunks` | plate | [cgpt_i76edit_level_renames_v4:high] Runtime LDEF payload wrapper. Iterates linked-object/export helper at 00417ef0 over global list/root DAT_0163ce60 until non-negative completion. |
| `0040fb50` | `i76edit_build_or_emit_linked_object_road_links` | plate | [cgpt_i76edit_level_renames_v5:low] Walks linked-object/road adjacency state and calls geometry/link helpers 004100f0/004103c0. Provisional. |
| `004113c0` | `i76edit_export_runtime_path_tree` | plate | [cgpt_i76edit_level_renames_v3] Runtime export helper that writes count placeholder, serializes path tree nodes, then backpatches count.<br><br>[cgpt_i76edit_level_renames_v6:high] Runtime path-tree writer. Writes a count placeholder, serializes enabled path roots, backpatches per-root node counts, then backpatches total root count. |
| `00411520` | `i76edit_find_next_enabled_path_node` | plate | [cgpt_i76edit_level_renames_v4:medium] Walks a linked list and returns the next node whose payload flags at +0x50 have bit 0 set. |
| `00411550` | `i76edit_export_runtime_path_tree_nodes_recursive` | plate | [cgpt_i76edit_level_renames_v3] Recursive runtime path tree node writer; emits scaled x/y/z coordinate triples.<br><br>[cgpt_i76edit_level_renames_v6:high] Recursive path node writer. Emits 12-byte xyz triples scaled by 00432110, with z currently written as zero. |
| `00411810` | `i76edit_initialize_terrain_buffers` | plate | [cgpt_i76edit_level_renames_v2:medium] References 'Initializing Terrain...' and 'Initializing Painted Terrain...'; called from terrain setup paths. |
| `00411b30` | `i76edit_get_or_assign_zone_map_cell_id` | plate | [cgpt_i76edit_level_renames_v4:medium] Bounds-checks an 80x80 zone map coordinate, reads byte zone id at DAT_00439ef0, and can assign a new id if the cell is -1 and assignment is requested. |
| `00411ba0` | `i76edit_get_or_create_zone_cell_backing` | plate | [cgpt_i76edit_level_renames_v5:medium] Called by zone-sample lookup; likely ensures the backing zone/cell data exists before terrain plane access.<br><br>[cgpt_i76edit_level_renames_v6:medium] Zone-cell backing allocator/accessor used by terrain surface/height sampling helpers. |
| `00411be0` | `i76edit_initialize_painted_terrain_layers` | plate | [cgpt_i76edit_level_renames_v2:medium] References 'Initializing Terrain...' and 'Initializing Painted Terrain...'; likely layer/buffer setup wrapper. |
| `00412120` | `i76edit_get_terrain_plane_row_ptr` | plate | [cgpt_i76edit_level_renames_v5:high] Returns row pointers into one of six terrain planes. Row stride is 0x8004 bytes = 0x2001 dwords; selector 0 uses 009bc824, 1 uses 0043c554, 2 uses 00ebcaa4, 3 uses 0113cbe4, 4 uses 00c3c964, 5 uses 013bcd24.<br><br>[cgpt_i76edit_level_renames_v6:high] Returns row pointers into one of six terrain planes. Row stride is 0x8004 bytes = 0x2001 dwords; selector 0 uses 009bc824, 1 uses 0043c554, 2 uses 00ebcaa4, 3 uses 0113cbe4, 4 uses 00c3c964, 5 uses 013bcd24. |
| `004121d0` | `i76edit_find_zone_cell_origin_by_zone_id` | plate | [cgpt_i76edit_level_renames_v4:medium] Searches the 80x80 byte zone map at DAT_00439ef0 for a zone id and returns x/y origins scaled by 0x80, or -1/-1 when not found. |
| `00412300` | `i76edit_world_xy_to_zone_local_triplet` | plate | [cgpt_i76edit_level_renames_v5:high] Converts world X/Y into zone/local coordinates: zone id from 80x80 byte map at 00439ef0 using x>>7,y>>7; local x/y are signed modulo 128.<br><br>[cgpt_i76edit_level_renames_v6:high] Converts world X/Y into zone id and signed local 0..127-ish coordinates using the 80x80 zone map at 00439ef0 with x>>7,y>>7 cell selection. |
| `004123a0` | `i76edit_load_workspace_surface_terrain_tables` | plate | [cgpt_i76edit_level_renames_v2:medium] References 'Loading Workspace...', 'Loading Painted Surface...', 'Loading Painted Terrain...', and 'Loading Surfaces...'; read-side workspace/layer loader. |
| `00412500` | `i76edit_save_workspace_terrain_arrays` | plate | [cgpt_i76edit_level_renames_v3] Writes workspace terrain/painter arrays: 0x1900 header/table followed by five 0x280140 byte planes.<br><br>[cgpt_i76edit_level_renames_v6:high] Workspace terrain-array writer. Writes 00439ef0 size 0x1900, then five 0x280140-byte terrain planes at 009bc820, 00ebcaa0, 0113cbe0, 00c3c960, and 013bcd20. |
| `004125a0` | `i76edit_alloc_first_unused_base_terrain_row` | plate | [cgpt_i76edit_level_renames_v5:medium] Scans the base terrain plane at 009bc820 in 0x8004-byte row slots and marks the first empty row as used. |
| `004125f0` | `i76edit_merge_or_normalize_terrain_planes` | plate | [cgpt_i76edit_level_renames_v4:medium] Copies/merges 0x280140 terrain planes and normalizes 80x80 word maps; handles 0x8000 sentinel and surface id values around 0x63/0x64/0xc7. |
| `00412e50` | `i76edit_main_window_proc_command_dispatch` | plate | [cgpt_i76edit_level_renames_v2:high] Main window procedure / command dispatcher. Evidence: DefWindowProcA/PostQuitMessage/GetOpenFileNameA/GetSaveFileNameA, open/save/export strings, and many thunked command handlers. |
| `004153e0` | `i76edit_show_edit_terrain_layer_dialog` | plate | [cgpt_i76edit_level_renames_v2:medium] References 'Edit Terrain Layer' and 'Modify the Terrain Layer.'; called from main window command dispatcher. |
| `004157f0` | `i76edit_delete_road_node_and_cleanup_edges` | plate | [cgpt_i76edit_level_renames_v4:medium] Removes a road/list node from global road list and frees edge/link allocations at payload offsets +0x40/+0x44/+0x48/+0x4c. |
| `00415980` | `i76edit_link_road_edge_neighbors` | plate | [cgpt_i76edit_level_renames_v5:medium] Updates road node neighbor/edge pointers at payload offsets +0x40/+0x48 and reciprocal links. |
| `00415ae0` | `i76edit_load_road_records` | plate | [cgpt_i76edit_level_renames_v3] Loads ROAD chunk records from the .I76 workspace stream. |
| `00415ca0` | `i76edit_save_road_records` | plate | [cgpt_i76edit_level_renames_v3] Saves ROAD chunk records to the .I76 workspace stream. |
| `00415e30` | `i76edit_export_runtime_all_road_chunks` | plate | [cgpt_i76edit_level_renames_v4:high] Runtime RDEF payload helper. Iterates road list through i76edit_export_road_records, then writes three EXIT terminators. |
| `00416620` | `i76edit_delete_selected_objects_ui` | plate | [cgpt_i76edit_level_renames_v2:medium] References 'Delete Object(s)' confirmation strings; UI command path for object deletion. |
| `00417ef0` | `i76edit_export_runtime_linked_object_obj_records` | plate | [cgpt_i76edit_level_renames_v5:medium] Serializes runtime linked-object records, patches record count/size via lseek/write, and advances through linked-object list until completion.<br><br>[cgpt_i76edit_level_renames_v6:high] Runtime linked-object exporter. Emits OBJ records of size 0x6c for linked/spline-like objects and follows helper 004181c0 to emit sampled geometry/positions. |
| `004181c0` | `i76edit_export_linked_object_sampled_segments` | plate | [cgpt_i76edit_level_renames_v6:medium] Chooses linked-object sampling mode based on payload +0xbc and +0x78/+0xc8 flags, dispatching to 00418270 or 00418490. |
| `00418270` | `i76edit_export_linked_object_linear_samples` | plate | [cgpt_i76edit_level_renames_v6:medium] Samples linked-object segment geometry and calls i76edit_write_scaled_xy_height_sample for each accepted sample. |
| `00418490` | `i76edit_export_linked_object_curved_samples` | plate | [cgpt_i76edit_level_renames_v6:medium] Alternate curved/smoothed linked-object segment sampler; calls trig helpers and i76edit_write_scaled_xy_height_sample. |
| `00418730` | `i76edit_write_scaled_xy_height_sample` | plate | [cgpt_i76edit_level_renames_v3] Writes one 12-byte scaled coordinate/height sample; used by terrain/path export helpers.<br><br>[cgpt_i76edit_level_renames_v6:high] Writes a scaled XY/height sample record used by road and linked-object export helpers. |
| `00418870` | `i76edit_load_mission_file` | plate | [cgpt_i76edit_level_renames_v2:high] Mission load path. Evidence: 'Opening %s...', 'Loading Elevations...', 'Loading Objects...', 'Loading Roads...', 'Loading Paths...', 'Loading Terrain...', and invalid mission-file message. |
| `0041a7e0` | `i76edit_save_editor_mission_file` | plate | [cgpt_i76edit_level_renames_v2:high] Editor save path. Evidence: 'Saving Terrain...', 'Saving Roads...', 'Saving Objects...' and __open/__write/__close call chain. |
| `0041aaa0` | `i76edit_export_runtime_zone_128x128_packed_height_surface` | plate | [cgpt_i76edit_level_renames_v4:low] Large terrain/zone payload builder that allocates 0x208/0x8000 working buffers and scans map arrays; used near export/zone paths. Name is intentionally provisional.<br><br>[cgpt_i76edit_level_renames_v6:high] Builds and writes one 0x8000-byte runtime zone raster: 128x128 uint16. Low 12 bits are height; high bits encode terrain/surface class from the surface plane, including special handling around surface ids 0x63/0x64. |
| `0041adc0` | `i76edit_export_runtime_tdef_zmap_and_zone_payloads` | plate | [cgpt_i76edit_level_renames_v2:medium] References 'Exporting Zone %d of %d.' and opens/writes output files; likely zone serializer used during export.<br><br>[cgpt_i76edit_level_renames_v6:high] Runtime TDEF exporter. Writes TREV v4, builds ZMAP size 0x1909 with one-byte active-zone count plus 80x80 zone-id map, writes a ZONE descriptor, opens a side payload stream, then emits one 0x8000 packed zone payload per active zone. |
| `0041b150` | `i76edit_export_runtime_mission_file` | plate | [cgpt_i76edit_level_renames_v2:high] Runtime/export path. Evidence: 'Exporting...', 'Exporting Objects.', 'Exporting Linked Objects.', file-open/write/seek calls, and file-permission error string. |
| `0041bcb0` | `i76edit_write_bwd2_exit_chunk` | plate | [cgpt_i76edit_level_renames_v4:high] Writes an 8-byte BWD2 EXIT chunk: tag 'EXIT', size=8. Used as a section terminator throughout runtime export. |
| `0041bcf0` | `i76edit_write_bwd2_revision_chunk` | plate | [cgpt_i76edit_level_renames_v4:high] Writes a 12-byte BWD2 chunk: uint32 tag, uint32 size=0x0c, uint32 revision/version. Called for VER/WREV/RREV/OREV/LREV/AREV. |
| `0041c430` | `i76edit_alloc_linked_list_node3` | plate | [cgpt_i76edit_level_renames_v4:medium] Allocates a 0x0c node and links prev/next pointers around payload pointer/value at +0x8. |
| `0041e120` | `i76edit_set_status_bar_text` | plate | [cgpt_i76edit_level_renames_v4:high] Copies caller text into status string globals and sends WM_USER+1 style message 0x401 to status/control window, followed by UpdateWindow. |
| `0041ea60` | `i76edit_export_height_txt_debug_view` | plate | [cgpt_i76edit_level_renames_v2:medium] References 'height.txt' and uses drawing/GDI plus fprintf; likely diagnostic terrain-height dump/view path. |
| `0041f2b0` | `i76edit_get_or_create_zone_surface_sample` | plate | [cgpt_i76edit_level_renames_v5:medium] Given world/cell X/Y and surface selector, normalizes special surface ids 0x63/0x64, ensures zone/cell backing data exists, then returns a terrain-plane sample.<br><br>[cgpt_i76edit_level_renames_v6:high] Maps world/local coordinates to a zone cell and returns/creates a terrain surface/height sample used while building 128x128 runtime zone rasters. |
| `0041f5a0` | `i76edit_object_type_has_runtime_position_override` | plate | [cgpt_i76edit_level_renames_v4:medium] Returns true for object type ids 1, 8, and 9; used by runtime object export to choose alternate coordinate handling. |
| `00420ee0` | `i76edit_export_grade_debug_for_roads` | plate | [cgpt_i76edit_level_renames_v4:medium] Opens grade.txt, walks roads/nodes, emits road grading diagnostics, and calls road cleanup when invalid edge state is detected. |
| `00421070` | `i76edit_build_grade_debug_road_link_table` | plate | [cgpt_i76edit_level_renames_v5:low] Grade/debug-side analogue to linked-object road link builder using globals 0043c110/0043c114/0043c12c/0043c130. |
| `00422f30` | `_sprintf` | plate | Library Function - Single Match<br> _sprintf<br><br>Library: Visual Studio 1998 Release |
| `00422fa0` | `_free` | plate | Library Function - Single Match<br> _free<br><br>Library: Visual Studio 1998 Release |
| `00422ff0` | `_fclose` | plate | Library Function - Single Match<br> _fclose<br><br>Library: Visual Studio 1998 Release |
| `00423060` | `_strtok` | plate | Library Function - Single Match<br> _strtok<br><br>Library: Visual Studio 1998 Release |
| `00423140` | `_fread` | plate | Library Function - Single Match<br> _fread<br><br>Library: Visual Studio 1998 Release |
| `00423290` | `__fsopen` | plate | Library Function - Single Match<br> __fsopen<br><br>Library: Visual Studio 1998 Release |
| `004232e0` | `_malloc` | plate | Library Function - Single Match<br> _malloc<br><br>Library: Visual Studio 1998 Release |
| `00423300` | `__nh_malloc` | plate | Library Function - Single Match<br> __nh_malloc<br><br>Library: Visual Studio 1998 Release |
| `00423350` | `__heap_alloc` | plate | Library Function - Single Match<br> __heap_alloc<br><br>Library: Visual Studio 1998 Release |
| `00423390` | `__cinit` | plate | Library Function - Single Match<br> __cinit<br><br>Library: Visual Studio 1998 Release |
| `004233c0` | `_exit` | plate | Library Function - Single Match<br> _exit<br><br>Library: Visual Studio 1998 Release |
| `004233e0` | `__exit` | plate | Library Function - Single Match<br> __exit<br><br>Library: Visual Studio 1998 Release |
| `00423420` | `doexit` | plate | Library Function - Single Match<br> _doexit<br><br>Library: Visual Studio 1998 Release |
| `004234d0` | `__initterm` | plate | Library Function - Single Match<br> __initterm<br><br>Library: Visual Studio 1998 Release |
| `004234f0` | `__fpmath` | plate | Library Function - Single Match<br> __fpmath<br><br>Library: Visual Studio 1998 Release |
| `004235a4` | `__ftol` | plate | Library Function - Single Match<br> __ftol<br><br>Library: Visual Studio |
| `004235d0` | `_atol` | plate | Library Function - Single Match<br> _atol<br><br>Library: Visual Studio 1998 Release |
| `00423680` | `_atoi` | plate | Library Function - Single Match<br> _atoi<br><br>Library: Visual Studio 1998 Release |
| `00423690` | `__atoi64` | plate | Library Function - Single Match<br> __atoi64<br><br>Library: Visual Studio 1998 Release |
| `00423770` | `_atof` | plate | Library Function - Single Match<br> _atof<br><br>Library: Visual Studio 1998 Release |
| `00423800` | `_fprintf` | plate | Library Function - Single Match<br> _fprintf<br><br>Library: Visual Studio 1998 Release |
| `00423850` | `_rand` | plate | Library Function - Single Match<br> _rand<br><br>Library: Visual Studio 1998 Release |
| `00423880` | `_strncpy` | plate | Library Function - Single Match<br> _strncpy<br><br>Library: Visual Studio 1998 Release |
| `00423980` | `__makepath` | plate | Library Function - Single Match<br> __makepath<br><br>Library: Visual Studio 1998 Release |
| `00423a20` | `__splitpath` | plate | Library Function - Single Match<br> __splitpath<br><br>Library: Visual Studio 1998 Release |
| `00423b80` | `_strncat` | plate | Library Function - Single Match<br> _strncat<br><br>Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release |
| `00423cb0` | `_strncmp` | plate | Library Function - Single Match<br> _strncmp<br><br>Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release |
| `00423cf0` | `_realloc` | plate | Library Function - Single Match<br> _realloc<br><br>Library: Visual Studio 1998 Release |
| `00423eb0` | `_strchr` | plate | Library Function - Single Match<br> _strchr<br><br>Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release |
| `00423f70` | `__lseek` | plate | Library Function - Single Match<br> __lseek<br><br>Library: Visual Studio 1998 Release |
| `004242c0` | `__amsg_exit` | plate | Library Function - Single Match<br> __amsg_exit<br><br>Library: Visual Studio 1998 Release |
| `004242f0` | `__flsbuf` | plate | Library Function - Single Match<br> __flsbuf<br><br>Library: Visual Studio 1998 Release |
| `00424440` | `__output` | plate | Library Function - Single Match<br> __output<br><br>Library: Visual Studio 1998 Release |
| `00424df0` | `write_char` | plate | Library Function - Single Match<br> _write_char<br><br>Library: Visual Studio 1998 Release |
| `00424e40` | `write_multi_char` | plate | Library Function - Single Match<br> _write_multi_char<br><br>Library: Visual Studio 1998 Release |
| `00424e80` | `write_string` | plate | Library Function - Single Match<br> _write_string<br><br>Library: Visual Studio 1998 Release |
| `00424ec0` | `get_int_arg` | plate | Library Function - Single Match<br> _get_int_arg<br><br>Library: Visual Studio 1998 Release |
| `00424ed0` | `get_int64_arg` | plate | Library Function - Single Match<br> _get_int64_arg<br><br>Library: Visual Studio 1998 Release |
| `00424ef0` | `get_short_arg` | plate | Library Function - Single Match<br> _get_short_arg<br><br>Library: Visual Studio 1998 Release |
| `00424f00` | `__heap_init` | plate | Library Function - Single Match<br> __heap_init<br><br>Library: Visual Studio 1998 Release |
| `00424fb0` | `___sbh_new_region` | plate | Library Function - Single Match<br> ___sbh_new_region<br><br>Library: Visual Studio 1998 Release |
| `00425120` | `___sbh_release_region` | plate | Library Function - Single Match<br> ___sbh_release_region<br><br>Library: Visual Studio 1998 Release |
| `00425180` | `___sbh_decommit_pages` | plate | Library Function - Single Match<br> ___sbh_decommit_pages<br><br>Library: Visual Studio 1998 Release |
| `00425260` | `___sbh_find_block` | plate | Library Function - Single Match<br> ___sbh_find_block<br><br>Library: Visual Studio 1998 Release |
| `004252c0` | `___sbh_free_block` | plate | Library Function - Single Match<br> ___sbh_free_block<br><br>Library: Visual Studio 1998 Release |
| `00425310` | `___sbh_alloc_block` | plate | Library Function - Single Match<br> ___sbh_alloc_block<br><br>Library: Visual Studio 1998 Release |
| `00425590` | `___sbh_alloc_block_from_page` | plate | Library Function - Single Match<br> ___sbh_alloc_block_from_page<br><br>Library: Visual Studio 1998 Release |
| `00425710` | `___sbh_resize_block` | plate | Library Function - Single Match<br> ___sbh_resize_block<br><br>Library: Visual Studio 1998 Release |
| `004257e0` | `___sbh_heap_check` | plate | Library Function - Single Match<br> ___sbh_heap_check<br><br>Library: Visual Studio 1998 Release |
| `004259b0` | `__close` | plate | Library Function - Single Match<br> __close<br><br>Library: Visual Studio 1998 Release |
| `00425a80` | `__freebuf` | plate | Library Function - Single Match<br> __freebuf<br><br>Library: Visual Studio 1998 Release |
| `00425ac0` | `_fflush` | plate | Library Function - Single Match<br> _fflush<br><br>Library: Visual Studio 1998 Release |
| `00425b10` | `__flush` | plate | Library Function - Single Match<br> __flush<br><br>Library: Visual Studio 1998 Release |
| `00425b90` | `flsall` | plate | Library Function - Single Match<br> _flsall<br><br>Library: Visual Studio 1998 Release |
| `00425c20` | `__filbuf` | plate | Library Function - Single Match<br> __filbuf<br><br>Library: Visual Studio 1998 Release |
| `00425d10` | `__read` | plate | Library Function - Single Match<br> __read<br><br>Library: Visual Studio 1998 Release |
| `00425f80` | `__openfile` | plate | Library Function - Single Match<br> __openfile<br><br>Library: Visual Studio 1998 Release |
| `00426190` | `__getstream` | plate | Library Function - Single Match<br> __getstream<br><br>Library: Visual Studio 1998 Release |
| `00426230` | `__callnewh` | plate | Library Function - Single Match<br> __callnewh<br><br>Library: Visual Studio 1998 Release |
| `00426260` | `__setdefaultprecision` | plate | Library Function - Single Match<br> __setdefaultprecision<br><br>Library: Visual Studio 1998 Release |
| `00426280` | `__ms_p5_test_fdiv` | plate | Library Function - Single Match<br> __ms_p5_test_fdiv<br><br>Library: Visual Studio 1998 Release |
| `004262d0` | `__ms_p5_mp_test_fdiv` | plate | Library Function - Single Match<br> __ms_p5_mp_test_fdiv<br><br>Library: Visual Studio 1998 Release |
| `00426440` | `__cftoe` | plate | Library Function - Single Match<br> __cftoe<br><br>Library: Visual Studio 1998 Release |
| `00426580` | `__cftof` | plate | Library Function - Single Match<br> __cftof<br><br>Library: Visual Studio 1998 Release |
| `00426680` | `__cftog` | plate | Library Function - Single Match<br> __cftog<br><br>Library: Visual Studio 1998 Release |
| `00426730` | `__cftoe_g` | plate | Library Function - Single Match<br> __cftoe_g<br><br>Library: Visual Studio 1998 Release |
| `00426760` | `__cftof_g` | plate | Library Function - Single Match<br> __cftof_g<br><br>Library: Visual Studio 1998 Release |
| `00426800` | `__shift` | plate | Library Function - Single Match<br> __shift<br><br>Library: Visual Studio 1998 Release |
| `00426830` | `__cintrindisp2` | plate | Library Function - Single Match<br> __cintrindisp2<br><br>Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 |
| `0042686e` | `__cintrindisp1` | plate | Library Function - Single Match<br> __cintrindisp1<br><br>Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 |
| `004268a4` | `__ctrandisp2` | plate | Library Function - Single Match<br> __ctrandisp2<br><br>Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 |
| `00426a15` | `__ctrandisp1` | plate | Library Function - Single Match<br> __ctrandisp1<br><br>Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 |
| `00426a41` | `__fload` | plate | Library Function - Single Match<br> __fload<br><br>Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 |
| `00426a80` | `__trandisp1` | plate | Library Function - Single Match<br> __trandisp1<br><br>Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 |
| `00426ae7` | `__trandisp2` | plate | Library Function - Single Match<br> __trandisp2<br><br>Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 |
| `004279e0` | `__isctype` | plate | Library Function - Single Match<br> __isctype<br><br>Library: Visual Studio 1998 Release |
| `00427a80` | `__allmul` | plate | Library Function - Single Match<br> __allmul<br><br>Library: Visual Studio 1998 Release |
| `00427ac0` | `__fltin` | plate | Library Function - Single Match<br> __fltin<br><br>Library: Visual Studio 1998 Release |
| `00427b70` | `__stbuf` | plate | Library Function - Single Match<br> __stbuf<br><br>Library: Visual Studio 1998 Release |
| `00427c10` | `__ftbuf` | plate | Library Function - Single Match<br> __ftbuf<br><br>Library: Visual Studio 1998 Release |
| `00427c60` | `__mbsdec` | plate | Library Function - Single Match<br> __mbsdec<br><br>Library: Visual Studio 1998 Release |
| `00427cc0` | `__mbsnbcpy` | plate | Library Function - Single Match<br> __mbsnbcpy<br><br>Library: Visual Studio 1998 Release |
| `00427d50` | `__setmbcp` | plate | Library Function - Single Match<br> __setmbcp<br><br>Library: Visual Studio 1998 Release |
| `00427f30` | `getSystemCP` | plate | Library Function - Single Match<br> _getSystemCP<br><br>Library: Visual Studio 1998 Release |
| `00427f80` | `_CPtoLCID` | plate | Library Function - Single Match<br> _CPtoLCID<br><br>Library: Visual Studio 1998 Release |
| `00427fe0` | `setSBCS` | plate | Library Function - Single Match<br> _setSBCS<br><br>Library: Visual Studio 1998 Release |
| `00428020` | `___initmbctable` | plate | Library Function - Single Match<br> ___initmbctable<br><br>Library: Visual Studio 1998 Release |
| `00428030` | `__dosmaperr` | plate | Library Function - Single Match<br> __dosmaperr<br><br>Library: Visual Studio 1998 Release |
| `004280a0` | `__alloc_osfhnd` | plate | Library Function - Single Match<br> __alloc_osfhnd<br><br>Library: Visual Studio 1998 Release |
| `00428160` | `__set_osfhnd` | plate | Library Function - Single Match<br> __set_osfhnd<br><br>Library: Visual Studio 1998 Release |
| `00428210` | `__free_osfhnd` | plate | Library Function - Single Match<br> __free_osfhnd<br><br>Library: Visual Studio 1998 Release |
| `004282a0` | `__get_osfhandle` | plate | Library Function - Single Match<br> __get_osfhandle<br><br>Library: Visual Studio 1998 Release |
| `004283a0` | `__ioinit` | plate | Library Function - Single Match<br> __ioinit<br><br>Library: Visual Studio 1998 Release |
| `004285b0` | `_calloc` | plate | Library Function - Single Match<br> _calloc<br><br>Library: Visual Studio 1998 Release |
| `00428650` | `__fcloseall` | plate | Library Function - Single Match<br> __fcloseall<br><br>Library: Visual Studio 1998 Release |
| `004286c4` | `__global_unwind2` | plate | Library Function - Single Match<br> __global_unwind2<br><br>Library: Visual Studio |
| `00428706` | `__local_unwind2` | plate | Library Function - Single Match<br> __local_unwind2<br><br>Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual Studio 2003 Release |
| `00428a50` | `__ismbblead` | plate | Library Function - Single Match<br> __ismbblead<br><br>Library: Visual Studio 1998 Release |
| `00428ac0` | `x_ismbbtype` | plate | Library Function - Single Match<br> _x_ismbbtype<br><br>Library: Visual Studio 1998 Release |
| `00428b00` | `__setenvp` | plate | Library Function - Single Match<br> __setenvp<br><br>Library: Visual Studio 1998 Release |
| `00428bf0` | `__setargv` | plate | Library Function - Single Match<br> __setargv<br><br>Library: Visual Studio 1998 Release |
| `00428c90` | `parse_cmdline` | plate | Library Function - Single Match<br> _parse_cmdline<br><br>Library: Visual Studio 1998 Release |
| `00428e70` | `___crtGetEnvironmentStringsW` | plate | Library Function - Single Match<br> ___crtGetEnvironmentStringsW<br><br>Library: Visual Studio 1998 Release |
| `00429070` | `___crtGetEnvironmentStringsA` | plate | Library Function - Single Match<br> ___crtGetEnvironmentStringsA<br><br>Library: Visual Studio 1998 Release |
| `004292e0` | `__FF_MSGBANNER` | plate | Library Function - Single Match<br> __FF_MSGBANNER<br><br>Library: Visual Studio 1998 Release |
| `00429320` | `__NMSG_WRITE` | plate | Library Function - Single Match<br> __NMSG_WRITE<br><br>Library: Visual Studio 1998 Release |
| `00429550` | `__write` | plate | Library Function - Single Match<br> __write<br><br>Library: Visual Studio 1998 Release |
| `00429780` | `__getbuf` | plate | Library Function - Single Match<br> __getbuf<br><br>Library: Visual Studio 1998 Release |
| `004297d0` | `__isatty` | plate | Library Function - Single Match<br> __isatty<br><br>Library: Visual Studio 1998 Release |
| `00429800` | `_wctomb` | plate | Library Function - Single Match<br> _wctomb<br><br>Library: Visual Studio 1998 Release |
| `004298a0` | `__aulldiv` | plate | Library Function - Single Match<br> __aulldiv<br><br>Library: Visual Studio 1998 Release |
| `00429910` | `__aullrem` | plate | Library Function - Single Match<br> __aullrem<br><br>Library: Visual Studio 1998 Release |
| `00429990` | `__commit` | plate | Library Function - Single Match<br> __commit<br><br>Library: Visual Studio 1998 Release |
| `00429a00` | `__open` | plate | Library Function - Single Match<br> __open<br><br>Library: Visual Studio 1998 Release |
| `00429a20` | `__sopen` | plate | Library Function - Single Match<br> __sopen<br><br>Library: Visual Studio 1998 Release |
| `00429e40` | `__statusfp` | plate | Library Function - Single Match<br> __statusfp<br><br>Library: Visual Studio 1998 Release |
| `00429e60` | `__clearfp` | plate | Library Function - Single Match<br> __clearfp<br><br>Library: Visual Studio 1998 Release |
| `00429e80` | `__control87` | plate | Library Function - Single Match<br> __control87<br><br>Library: Visual Studio 1998 Release |
| `00429ed0` | `__controlfp` | plate | Library Function - Single Match<br> __controlfp<br><br>Library: Visual Studio 1998 Release |
| `00429f20` | `__abstract_cw` | plate | Library Function - Single Match<br> __abstract_cw<br><br>Library: Visual Studio 1998 Release |
| `00429fd0` | `__hw_cw` | plate | Library Function - Single Match<br> __hw_cw<br><br>Library: Visual Studio 1998 Release |
| `0042a060` | `__abstract_sw` | plate | Library Function - Single Match<br> __abstract_sw<br><br>Library: Visual Studio 1998 Release |
| `0042a0c0` | `_tolower` | plate | Library Function - Single Match<br> _tolower<br><br>Library: Visual Studio 1998 Release |
| `0042a1b0` | `__ZeroTail` | plate | Library Function - Single Match<br> __ZeroTail<br><br>Library: Visual Studio 1998 Release |
| `0042a220` | `__IncMan` | plate | Library Function - Single Match<br> __IncMan<br><br>Library: Visual Studio 1998 Release |
| `0042a290` | `__RoundMan` | plate | Library Function - Single Match<br> __RoundMan<br><br>Library: Visual Studio 1998 Release |
| `0042a340` | `__CopyMan` | plate | Library Function - Single Match<br> __CopyMan<br><br>Library: Visual Studio 1998 Release |
| `0042a360` | `__FillZeroMan` | plate | Library Function - Single Match<br> __FillZeroMan<br><br>Library: Visual Studio 1998 Release |
| `0042a370` | `__IsZeroMan` | plate | Library Function - Single Match<br> __IsZeroMan<br><br>Library: Visual Studio 1998 Release |
| `0042a390` | `__ShrMan` | plate | Library Function - Single Match<br> __ShrMan<br><br>Library: Visual Studio 1998 Release |
| `0042a440` | `__ld12cvt` | plate | Library Function - Single Match<br> __ld12cvt<br><br>Library: Visual Studio 1998 Release |
| `0042a610` | `__ld12tod` | plate | Library Function - Single Match<br> __ld12tod<br><br>Library: Visual Studio 1998 Release |
| `0042a630` | `__ld12tof` | plate | Library Function - Multiple Matches With Different Base Names<br> __ld12tod<br> __ld12tof<br><br>Library: Visual Studio 1998 Release |
| `0042a6e0` | `FID_conflict:__atodbl` | plate | Library Function - Multiple Matches With Different Base Names<br> __atodbl<br> __atoflt<br><br>Library: Visual Studio 1998 Release |
| `0042a760` | `FID_conflict:__atodbl` | plate | Library Function - Multiple Matches With Different Base Names<br> __atodbl<br> __atoflt<br><br>Library: Visual Studio 1998 Release |
| `0042a7a0` | `__fptostr` | plate | Library Function - Single Match<br> __fptostr<br><br>Library: Visual Studio 1998 Release |
| `0042a830` | `__fltout` | plate | Library Function - Single Match<br> __fltout<br><br>Library: Visual Studio 1998 Release |
| `0042a8a0` | `___dtold` | plate | Library Function - Single Match<br> ___dtold<br><br>Library: Visual Studio 1998 Release |
| `0042a960` | `FID_conflict:_memcpy` | plate | Library Function - Multiple Matches With Different Base Names<br> _memcpy<br> _memmove<br><br>Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release |
| `0042aab0` | `__87except` | plate | Library Function - Single Match<br> __87except<br><br>Library: Visual Studio 1998 Release |
| `0042ad90` | `___crtGetStringTypeA` | plate | Library Function - Single Match<br> ___crtGetStringTypeA<br><br>Library: Visual Studio 1998 Release |
| `0042aec0` | `___strgtold12` | plate | Library Function - Single Match<br> ___strgtold12<br><br>Library: Visual Studio 1998 Release |
| `0042b680` | `___crtMessageBoxA` | plate | Library Function - Single Match<br> ___crtMessageBoxA<br><br>Library: Visual Studio 1998 Release |
| `0042b720` | `__chsize` | plate | Library Function - Single Match<br> __chsize<br><br>Library: Visual Studio 1998 Release |
| `0042bae0` | `___crtLCMapStringA` | plate | Library Function - Single Match<br> ___crtLCMapStringA<br><br>Library: Visual Studio 1998 Release |
| `0042bd10` | `_strncnt` | plate | Library Function - Single Match<br> _strncnt<br><br>Library: Visual Studio 1998 Release |
| `0042bd40` | `___addl` | plate | Library Function - Single Match<br> ___addl<br><br>Library: Visual Studio 1998 Release |
| `0042bd70` | `___add_12` | plate | Library Function - Single Match<br> ___add_12<br><br>Library: Visual Studio 1998 Release |
| `0042bde0` | `___shl_12` | plate | Library Function - Single Match<br> ___shl_12<br><br>Library: Visual Studio 1998 Release |
| `0042be20` | `___shr_12` | plate | Library Function - Single Match<br> ___shr_12<br><br>Library: Visual Studio 1998 Release |
| `0042be60` | `___mtold12` | plate | Library Function - Single Match<br> ___mtold12<br><br>Library: Visual Studio 1998 Release |
| `0042bf50` | `$I10_OUTPUT` | plate | Library Function - Single Match<br> _$I10_OUTPUT<br><br>Library: Visual Studio 1998 Release |
| `0042c560` | `__raise_exc` | plate | Library Function - Single Match<br> __raise_exc<br><br>Library: Visual Studio 1998 Release |
| `0042c8d0` | `__handle_exc` | plate | Library Function - Single Match<br> __handle_exc<br><br>Library: Visual Studio 1998 Release |
| `0042cc40` | `__set_errno` | plate | Library Function - Single Match<br> __set_errno<br><br>Library: Visual Studio 1998 Release |
| `0042ccf0` | `__statfp` | plate | Library Function - Single Match<br> __statfp<br><br>Library: Visual Studio 1998 Release |
| `0042cd10` | `__clrfp` | plate | Library Function - Single Match<br> __clrfp<br><br>Library: Visual Studio 1998 Release |
| `0042cd30` | `__ctrlfp` | plate | Library Function - Single Match<br> __ctrlfp<br><br>Library: Visual Studio 1998 Release |
| `0042cdd0` | `___ld12mul` | plate | Library Function - Single Match<br> ___ld12mul<br><br>Library: Visual Studio 1998 Release |
| `0042d080` | `___multtenpow12` | plate | Library Function - Single Match<br> ___multtenpow12<br><br>Library: Visual Studio 1998 Release |
| `0042d100` | `__setmode` | plate | Library Function - Single Match<br> __setmode<br><br>Library: Visual Studio 1998 Release |
| `0042d180` | `__set_exp` | plate | Library Function - Single Match<br> __set_exp<br><br>Library: Visual Studio 1998 Release |
| `0042d2c0` | `__decomp` | plate | Library Function - Single Match<br> __decomp<br><br>Library: Visual Studio 1998 Release |
| `0042d4a0` | `__strcmpi` | plate | Library Function - Single Match<br> __strcmpi<br><br>Library: Visual Studio 1998 Release |
| `0042d530` | `__tell` | plate | Library Function - Single Match<br> __tell<br><br>Library: Visual Studio 1998 Release |
| `0042d550` | `__itoa` | plate | Library Function - Single Match<br> __itoa<br><br>Library: Visual Studio 1998 Release |
| `0042d590` | `xtoa` | plate | Library Function - Single Match<br> _xtoa<br><br>Library: Visual Studio 1998 Release |
| `0042d5f0` | `__ltoa` | plate | Library Function - Single Match<br> __ltoa<br><br>Library: Visual Studio 1998 Release |
| `0042d680` | `x64toa` | plate | Library Function - Single Match<br> _x64toa@20<br><br>Library: Visual Studio 1998 Release<br>__stdcall x64toa,20 |
| `0042d740` | `__strnicmp` | plate | Library Function - Single Match<br> __strnicmp<br><br>Library: Visual Studio 1998 Release |
| `01644000` | `` | plate | IMAGE_IMPORT_DESCRIPTOR |
| `01644014` | `` | plate | IMAGE_IMPORT_DESCRIPTOR |
| `01644028` | `` | plate | IMAGE_IMPORT_DESCRIPTOR |
| `0164403c` | `` | plate | IMAGE_IMPORT_DESCRIPTOR |
| `01644050` | `` | plate | IMAGE_IMPORT_DESCRIPTOR |
| `01644078` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164407c` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644080` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644084` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440b4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440b8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440bc` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440c0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440c4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440c8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440cc` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440d0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440d4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440d8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440dc` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440e0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440e4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440e8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440ec` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440f0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440f4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440f8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016440fc` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644100` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644104` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644108` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164410c` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644110` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644114` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644118` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164411c` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644120` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644164` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644168` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164416c` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644170` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644174` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644178` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164417c` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644180` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644184` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644188` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164418c` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644190` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644194` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644198` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164419c` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441a0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441a4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441a8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441ac` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441b0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441b4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441b8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441bc` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441c0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441c4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441c8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441cc` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441d0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441d4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441d8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441dc` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441e0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441e4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441e8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441ec` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441f0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441f4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441f8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016441fc` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644200` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644204` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644208` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164420c` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644210` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644214` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644218` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164421c` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644220` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644224` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644228` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644280` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644284` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644288` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164428c` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644290` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644294` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644298` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164429c` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442a0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442a4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442a8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442ac` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442b0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442b4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442b8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442bc` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442c0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442c4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442c8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442cc` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442d0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442d4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442d8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442dc` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442e0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442e4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442e8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442ec` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442f0` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442f4` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442f8` | `` | eol | IMAGE_THUNK_DATA32 |
| `016442fc` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644300` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644304` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644308` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164430c` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644310` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644314` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644318` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164431c` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644320` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644324` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644328` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164432c` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644330` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644334` | `` | eol | IMAGE_THUNK_DATA32 |
| `01644388` | `` | eol | IMAGE_THUNK_DATA32 |
| `0164438c` | `` | eol | IMAGE_THUNK_DATA32 |
| `016443bc` | `` | pre | 17  Ordinal_17  <<not bound>> |
| `016443c0` | `` | pre | 16  Ordinal_16  <<not bound>> |
| `016443c4` | `` | pre | 6  Ordinal_6  <<not bound>> |
| `016443c8` | `` | pre | 8  CreateToolbarEx  <<not bound>> |
| `016443f8` | `` | pre | 377  SetWindowExtEx  <<not bound>> |
| `016443fc` | `` | pre | 373  SetViewportExtEx  <<not bound>> |
| `01644400` | `` | pre | 354  SetMapMode  <<not bound>> |
| `01644404` | `` | pre | 308  Polyline  <<not bound>> |
| `01644408` | `` | pre | 200  GetDeviceCaps  <<not bound>> |
| `0164440c` | `` | pre | 299  PolyBezier  <<not bound>> |
| `01644410` | `` | pre | 65  DPtoLP  <<not bound>> |
| `01644414` | `` | pre | 10  BitBlt  <<not bound>> |
| `01644418` | `` | pre | 75  Ellipse  <<not bound>> |
| `0164441c` | `` | pre | 30  CreateCompatibleBitmap  <<not bound>> |
| `01644420` | `` | pre | 251  GetStockObject  <<not bound>> |
| `01644424` | `` | pre | 31  CreateCompatibleDC  <<not bound>> |
| `01644428` | `` | pre | 360  SetPixel  <<not bound>> |
| `0164442c` | `` | pre | 67  DeleteDC  <<not bound>> |
| `01644430` | `` | pre | 271  GetViewportExtEx  <<not bound>> |
| `01644434` | `` | pre | 315  Rectangle  <<not bound>> |
| `01644438` | `` | pre | 378  SetWindowOrgEx  <<not bound>> |
| `0164443c` | `` | pre | 275  GetWindowOrgEx  <<not bound>> |
| `01644440` | `` | pre | 284  MoveToEx  <<not bound>> |
| `01644444` | `` | pre | 281  LineTo  <<not bound>> |
| `01644448` | `` | pre | 324  SaveDC  <<not bound>> |
| `0164444c` | `` | pre | 274  GetWindowExtEx  <<not bound>> |
| `01644450` | `` | pre | 364  SetROP2  <<not bound>> |
| `01644454` | `` | pre | 322  RestoreDC  <<not bound>> |
| `01644458` | `` | pre | 331  SelectObject  <<not bound>> |
| `0164445c` | `` | pre | 55  CreatePen  <<not bound>> |
| `01644460` | `` | pre | 70  DeleteObject  <<not bound>> |
| `01644464` | `` | pre | 245  GetROP2  <<not bound>> |
| `016444a8` | `` | pre | 363  HeapDestroy  <<not bound>> |
| `016444ac` | `` | pre | 359  HeapAlloc  <<not bound>> |
| `016444b0` | `` | pre | 398  LoadLibraryA  <<not bound>> |
| `016444b4` | `` | pre | 301  GetStringTypeW  <<not bound>> |
| `016444b8` | `` | pre | 523  SetEndOfFile  <<not bound>> |
| `016444bc` | `` | pre | 48  CreateFileA  <<not bound>> |
| `016444c0` | `` | pre | 141  FlushFileBuffers  <<not bound>> |
| `016444c4` | `` | pre | 298  GetStringTypeA  <<not bound>> |
| `016444c8` | `` | pre | 617  WideCharToMultiByte  <<not bound>> |
| `016444cc` | `` | pre | 226  GetEnvironmentStringsW  <<not bound>> |
| `016444d0` | `` | pre | 630  WriteFile  <<not bound>> |
| `016444d4` | `` | pre | 224  GetEnvironmentStrings  <<not bound>> |
| `016444d8` | `` | pre | 425  MultiByteToWideChar  <<not bound>> |
| `016444dc` | `` | pre | 150  FreeEnvironmentStringsW  <<not bound>> |
| `016444e0` | `` | pre | 251  GetModuleFileNameA  <<not bound>> |
| `016444e4` | `` | pre | 587  UnhandledExceptionFilter  <<not bound>> |
| `016444e8` | `` | pre | 149  FreeEnvironmentStringsA  <<not bound>> |
| `016444ec` | `` | pre | 297  GetStdHandle  <<not bound>> |
| `016444f0` | `` | pre | 534  SetHandleCount  <<not bound>> |
| `016444f4` | `` | pre | 481  RtlUnwind  <<not bound>> |
| `016444f8` | `` | pre | 548  SetStdHandle  <<not bound>> |
| `016444fc` | `` | pre | 264  GetOEMCP  <<not bound>> |
| `01644500` | `` | pre | 238  GetFileType  <<not bound>> |
| `01644504` | `` | pre | 162  GetCPInfo  <<not bound>> |
| `01644508` | `` | pre | 277  GetProcAddress  <<not bound>> |
| `0164450c` | `` | pre | 156  GetACP  <<not bound>> |
| `01644510` | `` | pre | 23  CloseHandle  <<not bound>> |
| `01644514` | `` | pre | 598  VirtualAlloc  <<not bound>> |
| `01644518` | `` | pre | 466  ReadFile  <<not bound>> |
| `0164451c` | `` | pre | 331  GetVersion  <<not bound>> |
| `01644520` | `` | pre | 169  GetCommandLineA  <<not bound>> |
| `01644524` | `` | pre | 601  VirtualFree  <<not bound>> |
| `01644528` | `` | pre | 408  LocalFree  <<not bound>> |
| `0164452c` | `` | pre | 295  GetStartupInfoA  <<not bound>> |
| `01644530` | `` | pre | 253  GetModuleHandleA  <<not bound>> |
| `01644534` | `` | pre | 361  HeapCreate  <<not bound>> |
| `01644538` | `` | pre | 365  HeapFree  <<not bound>> |
| `0164453c` | `` | pre | 532  SetFilePointer  <<not bound>> |
| `01644540` | `` | pre | 368  HeapReAlloc  <<not bound>> |
| `01644544` | `` | pre | 210  GetCurrentProcess  <<not bound>> |
| `01644548` | `` | pre | 577  TerminateProcess  <<not bound>> |
| `0164454c` | `` | pre | 106  ExitProcess  <<not bound>> |
| `01644550` | `` | pre | 146  FormatMessageA  <<not bound>> |
| `01644554` | `` | pre | 243  GetLastError  <<not bound>> |
| `01644558` | `` | pre | 336  GetWindowsDirectoryA  <<not bound>> |
| `0164455c` | `` | pre | 613  WaitForSingleObject  <<not bound>> |
| `01644560` | `` | pre | 60  CreateProcessA  <<not bound>> |
| `01644564` | `` | pre | 396  LCMapStringW  <<not bound>> |
| `01644568` | `` | pre | 455  RaiseException  <<not bound>> |
| `0164456c` | `` | pre | 395  LCMapStringA  <<not bound>> |
| `016445c4` | `` | pre | 473  SendMessageA  <<not bound>> |
| `016445c8` | `` | pre | 591  UpdateWindow  <<not bound>> |
| `016445cc` | `` | pre | 500  SetFocus  <<not bound>> |
| `016445d0` | `` | pre | 491  SetCursor  <<not bound>> |
| `016445d4` | `` | pre | 248  GetFocus  <<not bound>> |
| `016445d8` | `` | pre | 238  GetDC  <<not bound>> |
| `016445dc` | `` | pre | 205  FindWindowA  <<not bound>> |
| `016445e0` | `` | pre | 339  InvalidateRgn  <<not bound>> |
| `016445e4` | `` | pre | 471  SendDlgItemMessageA  <<not bound>> |
| `016445e8` | `` | pre | 460  ReleaseDC  <<not bound>> |
| `016445ec` | `` | pre | 215  GetAsyncKeyState  <<not bound>> |
| `016445f0` | `` | pre | 519  SetRect  <<not bound>> |
| `016445f4` | `` | pre | 18  CallWindowProcA  <<not bound>> |
| `016445f8` | `` | pre | 459  ReleaseCapture  <<not bound>> |
| `016445fc` | `` | pre | 522  SetScrollPos  <<not bound>> |
| `01644600` | `` | pre | 556  ShowWindow  <<not bound>> |
| `01644604` | `` | pre | 144  DispatchMessageA  <<not bound>> |
| `01644608` | `` | pre | 382  LoadMenuA  <<not bound>> |
| `0164460c` | `` | pre | 370  LoadCursorA  <<not bound>> |
| `01644610` | `` | pre | 506  SetMenu  <<not bound>> |
| `01644614` | `` | pre | 445  RegisterClassA  <<not bound>> |
| `01644618` | `` | pre | 85  CreateWindowExA  <<not bound>> |
| `0164461c` | `` | pre | 300  GetSystemMetrics  <<not bound>> |
| `01644620` | `` | pre | 48  CheckMenuItem  <<not bound>> |
| `01644624` | `` | pre | 374  LoadIconA  <<not bound>> |
| `01644628` | `` | pre | 128  DefWindowProcA  <<not bound>> |
| `0164462c` | `` | pre | 294  GetScrollRange  <<not bound>> |
| `01644630` | `` | pre | 435  PostQuitMessage  <<not bound>> |
| `01644634` | `` | pre | 442  PtInRect  <<not bound>> |
| `01644638` | `` | pre | 482  SetCapture  <<not bound>> |
| `0164463c` | `` | pre | 413  MoveWindow  <<not bound>> |
| `01644640` | `` | pre | 204  FillRect  <<not bound>> |
| `01644644` | `` | pre | 9  BeginPaint  <<not bound>> |
| `01644648` | `` | pre | 182  EndPaint  <<not bound>> |
| `0164464c` | `` | pre | 368  LoadBitmapA  <<not bound>> |
| `01644650` | `` | pre | 75  CreateDialogParamA  <<not bound>> |
| `01644654` | `` | pre | 54  ClientToScreen  <<not bound>> |
| `01644658` | `` | pre | 541  SetWindowPos  <<not bound>> |
| `0164465c` | `` | pre | 314  GetWindowLongA  <<not bound>> |
| `01644660` | `` | pre | 538  SetWindowLongA  <<not bound>> |
| `01644664` | `` | pre | 523  SetScrollRange  <<not bound>> |
| `01644668` | `` | pre | 209  FlashWindow  <<not bound>> |
| `0164466c` | `` | pre | 228  GetClientRect  <<not bound>> |
| `01644670` | `` | pre | 405  MessageBoxA  <<not bound>> |
| `01644674` | `` | pre | 579  TranslateMessage  <<not bound>> |
| `01644678` | `` | pre | 431  PeekMessageA  <<not bound>> |
| `016446cc` | `` | pre | 9  GetOpenFileNameA  <<not bound>> |
| `016446d0` | `` | pre | 11  GetSaveFileNameA  <<not bound>> |
| `01644700` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164470c` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164471e` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164472e` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644746` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164475c` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164476e` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164477c` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644788` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644794` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016447a2` | `` | plate | IMAGE_IMPORT_DESCRIPTOR - DLL NAME |
| `016447b0` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016447c0` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016447d4` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016447e8` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016447f6` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644802` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644812` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644822` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164482a` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644838` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644848` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164485e` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164486a` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164487e` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644888` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164489a` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016448a6` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016448b8` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016448c6` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016448d2` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016448e0` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016448ea` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016448f6` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644908` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164491c` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164492e` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164493a` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164494a` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164495c` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164496c` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164497a` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164498a` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `0164499c` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016449ae` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016449bc` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016449ce` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016449e4` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016449f0` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `016449fc` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644a0a` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644a16` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644a24` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644a32` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644a44` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644a56` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644a68` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644a78` | `` | plate | IMAGE_IMPORT_DESCRIPTOR - DLL NAME |
| `01644a84` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644a94` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644aa0` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644aaa` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644ab4` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644ac4` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644ad0` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644ae0` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644af2` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644b04` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644b16` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644b28` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644b32` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644b46` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644b54` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644b5e` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644b6a` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644b78` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644b84` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644b90` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644ba4` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644bb0` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644bbc` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644bd2` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644be4` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644bfe` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644c08` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644c12` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644c1c` | `` | plate | IMAGE_IMPORT_DESCRIPTOR - DLL NAME |
| `01644c26` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644c3a` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644c4e` | `` | plate | IMAGE_IMPORT_DESCRIPTOR - DLL NAME |
| `01644c5c` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644c6e` | `` | plate | IMAGE_IMPORT_DESCRIPTOR - DLL NAME |
| `01644c7c` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644c8a` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644c9e` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644cb2` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644cc0` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644cd2` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644ce6` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644cf8` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644d0a` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644d18` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644d26` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644d36` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644d44` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644d50` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644d62` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644d6e` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644d78` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644d84` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644d94` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644da2` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644db4` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644dc4` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644dd0` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644dec` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644e02` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644e1c` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644e32` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644e4a` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644e64` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644e7e` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644e94` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644ea0` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644eb4` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644ec2` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644ed4` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644ee6` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644ef6` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644f06` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644f16` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01644f26` | `` | plate | IMAGE_IMPORT_BY_NAME |
| `01646ea0` | `` | plate | Rsrc_Dialog_65_409 Size of resource: 0x1c0 bytes<br> |
| `01646ea0` | `` | eol | version (must be 1) |
| `01647060` | `` | plate | Rsrc_Dialog_64_409 Size of resource: 0xbe bytes<br><br>Number of Items in Dialog: 3<br>Menu: None<br>Class: Predefined<br>Title: "About I76edit"<br>Font Size: 8h<br>Font Name: "MS Sans Serif"<br><br>Item 1: <br>   Class: Static<br>   Title: Button<br>   Data: None<br>Item 2: <br>   Class: Static<br>   Title: "V .5  9/3/96"<br>   Data: None<br>Item 3: <br>   Class: Button<br>   Title: "OK"<br>   Data: None |
| `01647060` | `` | eol | style of dialog box |
| `01647120` | `` | plate | Rsrc_Dialog_72_409 Size of resource: 0xb4 bytes<br> |
| `01647120` | `` | eol | version (must be 1) |
| `016471d4` | `` | plate | Rsrc_Dialog_76_409 Size of resource: 0x38c bytes<br><br>Number of Items in Dialog: 20<br>Menu: None<br>Class: Predefined<br>Title: "Object Layer"<br>Font Size: 8h<br>Font Name: "MS Sans Serif"<br><br>Item 1: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 2: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 3: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 4: <br>   Class: Combo Box<br>   Title: ""<br>   Data: None<br>Item 5: <br>   Class: Static<br>   Title: "Object Label:"<br>   Data: None<br>Item 6: <br>   Class: Static<br>   Title: "Object Class File:"<br>   Data: None<br>Item 7: <br>   Class: Static<br>   Title: "Object Class ID:"<br>   Data: None<br>Item 8: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 9: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 10: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 11: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 12: <br>   Class: Static<br>   Title: "dist-Z"<br>   Data: None<br>Item 13: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 14: <br>   Class: Static<br>   Title: "dist-X/length"<br>   Data: None<br>Item 15: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 16: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 17: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 18: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 19: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 20: <br>   Class: Static<br>   Title: "Stringed Objects:"<br>   Data: None |
| `016471d4` | `` | eol | style of dialog box |
| `01647560` | `` | plate | Rsrc_Dialog_3eb_409 Size of resource: 0x1b0 bytes<br><br>Number of Items in Dialog: 9<br>Menu: None<br>Class: Predefined<br>Title: "Road Toolbox"<br>Font Size: 8h<br>Font Name: "MS Sans Serif"<br><br>Item 1: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 2: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 3: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 4: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 5: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 6: <br>   Class: Combo Box<br>   Title: ""<br>   Data: None<br>Item 7: <br>   Class: Static<br>   Title: "Road Type"<br>   Data: None<br>Item 8: <br>   Class: Button<br>   Title: "4 Lanes"<br>   Data: None<br>Item 9: <br>   Class: Button<br>   Title: "2 Lanes"<br>   Data: None |
| `01647560` | `` | eol | style of dialog box |
| `01647710` | `` | plate | Rsrc_Dialog_78_409 Size of resource: 0x2ee bytes<br><br>Number of Items in Dialog: 15<br>Menu: None<br>Class: Predefined<br>Title: "Vehicle Layer"<br>Font Size: 8h<br>Font Name: "MS Sans Serif"<br><br>Item 1: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 2: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 3: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 4: <br>   Class: Button<br>   Title: "AI Control"<br>   Data: None<br>Item 5: <br>   Class: Button<br>   Title: "User Control"<br>   Data: None<br>Item 6: <br>   Class: Static<br>   Title: "Vehicle Label"<br>   Data: None<br>Item 7: <br>   Class: Static<br>   Title: "Vehicle Class File"<br>   Data: None<br>Item 8: <br>   Class: Static<br>   Title: "Vehicle Control Source:"<br>   Data: None<br>Item 9: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 10: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 11: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 12: <br>   Class: Combo Box<br>   Title: ""<br>   Data: None<br>Item 13: <br>   Class: Static<br>   Title: "Team Affiliation:"<br>   Data: None<br>Item 14: <br>   Class: Combo Box<br>   Title: ""<br>   Data: None<br>Item 15: <br>   Class: Static<br>   Title: "Vehicle Type"<br>   Data: None |
| `01647710` | `` | eol | style of dialog box |
| `01647a00` | `` | plate | Rsrc_Dialog_79_409 Size of resource: 0x65a bytes<br><br>Number of Items in Dialog: 38<br>Menu: None<br>Class: Predefined<br>Title: "Set World Defs"<br>Font Size: 8h<br>Font Name: "MS Sans Serif"<br><br>Item 1: <br>   Class: Button<br>   Title: "Browse"<br>   Data: None<br>Item 2: <br>   Class: Button<br>   Title: "Browse"<br>   Data: None<br>Item 3: <br>   Class: Button<br>   Title: "Browse"<br>   Data: None<br>Item 4: <br>   Class: Button<br>   Title: "Browse"<br>   Data: None<br>Item 5: <br>   Class: Button<br>   Title: "Browse"<br>   Data: None<br>Item 6: <br>   Class: Static<br>   Title: "Intro Movie Name"<br>   Data: None<br>Item 7: <br>   Class: Static<br>   Title: "Outro Movie Name"<br>   Data: None<br>Item 8: <br>   Class: Static<br>   Title: "Palette File"<br>   Data: None<br>Item 9: <br>   Class: Static<br>   Title: "Luma Table"<br>   Data: None<br>Item 10: <br>   Class: Static<br>   Title: "Xlucency Table 1"<br>   Data: None<br>Item 11: <br>   Class: Static<br>   Title: "Objectives File"<br>   Data: None<br>Item 12: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 13: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 14: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 15: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 16: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 17: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 18: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 19: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 20: <br>   Class: Static<br>   Title: "Music Track"<br>   Data: None<br>Item 21: <br>   Class: Static<br>   Title: "Time of Day"<br>   Data: None<br>Item 22: <br>   Class: Button<br>   Title: "Browse"<br>   Data: None<br>Item 23: <br>   Class: Button<br>   Title: "Browse"<br>   Data: None<br>Item 24: <br>   Class: Static<br>   Title: "Sky Texture"<br>   Data: None<br>Item 25: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 26: <br>   Class: Button<br>   Title: "Browse"<br>   Data: None<br>Item 27: <br>   Class: Static<br>   Title: "Scrounge Texture"<br>   Data: None<br>Item 28: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 29: <br>   Class: Button<br>   Title: "Browse"<br>   Data: None<br>Item 30: <br>   Class: Static<br>   Title: "Surface Texture"<br>   Data: None<br>Item 31: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 32: <br>   Class: Button<br>   Title: "Browse"<br>   Data: None<br>Item 33: <br>   Class: Static<br>   Title: "Level Map"<br>   Data: None<br>Item 34: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 35: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 36: <br>   Class: Static<br>   Title: "Far Clip Dist"<br>   Data: None<br>Item 37: <br>   Class: Static<br>   Title: "Level Discription"<br>   Data: None<br>Item 38: <br>   Class: Edit<br>   Title: ""<br>   Data: None |
| `01647a00` | `` | eol | style of dialog box |
| `0164805c` | `` | plate | Rsrc_Dialog_3ec_409 Size of resource: 0x13c bytes<br><br>Number of Items in Dialog: 6<br>Menu: None<br>Class: Predefined<br>Title: "Path Toolbox"<br>Font Size: 8h<br>Font Name: "MS Sans Serif"<br><br>Item 1: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 2: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 3: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 4: <br>   Class: Button<br>   Title: "Check2"<br>   Data: None<br>Item 5: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 6: <br>   Class: Static<br>   Title: "Path Label:"<br>   Data: None |
| `0164805c` | `` | eol | style of dialog box |
| `01648198` | `` | plate | Rsrc_Dialog_7c_409 Size of resource: 0x492 bytes<br> |
| `01648198` | `` | eol | version (must be 1) |
| `0164862c` | `` | plate | Rsrc_Dialog_7e_409 Size of resource: 0x49c bytes<br><br>Number of Items in Dialog: 31<br>Menu: None<br>Class: Predefined<br>Title: "Terrain Tools"<br>Font Size: 8h<br>Font Name: "MS Sans Serif"<br><br>Item 1: <br>   Class: Button<br>   Title: "Raise Terrain"<br>   Data: None<br>Item 2: <br>   Class: Button<br>   Title: "Lower Terrain"<br>   Data: None<br>Item 3: <br>   Class: Button<br>   Title: "Paint Terrain"<br>   Data: None<br>Item 4: <br>   Class: Button<br>   Title: "Erase Terrain"<br>   Data: None<br>Item 5: <br>   Class: Button<br>   Title: "High"<br>   Data: None<br>Item 6: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 7: <br>   Class: Static<br>   Title: "Current Height"<br>   Data: None<br>Item 8: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 9: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 10: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 11: <br>   Class: Static<br>   Title: "Brushes:"<br>   Data: None<br>Item 12: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 13: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 14: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 15: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 16: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 17: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 18: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 19: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 20: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 21: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 22: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 23: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 24: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 25: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 26: <br>   Class: Static<br>   Title: "Grading:"<br>   Data: None<br>Item 27: <br>   Class: Edit<br>   Title: ""<br>   Data: None<br>Item 28: <br>   Class: Static<br>   Title: "Detail:"<br>   Data: None<br>Item 29: <br>   Class: Static<br>   Title: "Starting Display Height"<br>   Data: None<br>Item 30: <br>   Class: Button<br>   Title: ""<br>   Data: None<br>Item 31: <br>   Class: Static<br>   Title: "Repaint"<br>   Data: None |
| `0164862c` | `` | eol | style of dialog box |
| `01648ac8` | `` | plate | Rsrc_Version_1_409 Size of resource: 0x2cc bytes |
| `01648d94` | `` | plate | Rsrc_Icon_1_409 Size of resource: 0x2e8 bytes |
| `0164907c` | `` | plate | Rsrc_Icon_2_409 Size of resource: 0x128 bytes |
| `016491a4` | `` | plate | Rsrc_Icon_3_409 Size of resource: 0x8a8 bytes |
| `01649a4c` | `` | plate | Rsrc_Icon_4_409 Size of resource: 0xea8 bytes |
| `0164a8f4` | `` | plate | Rsrc_GroupIcon_66_409 Size of resource: 0x3e bytes |
| `0164a934` | `` | plate | Rsrc_Menu_67_409 Size of resource: 0x2e8 bytes<br><br>&File<br>  &New\\tCtrl+N<br>  &Open...\\tCtrl+O<br>  &Save...\\tCtrl+S<br>  &Export...\\tCtrl+E<br>  -------------------<br>  E&xit<br><br>&Edit<br>  &Elevation Layer<br>  &Terrain Layer<br>  &Surface Layer<br>  &Road Layer<br>  &Object Layer<br>  &GP Layer<br>  &WorldDefs Layer<br>  &Delete Zones<br><br>&View<br>  &Elevation Layer<br>  &Terrain Layer<br>  &Surface Layer<br>  &Road Layer<br>  &Object Layer<br>  &GP Layer<br>  -------------------<br>  &Zone Grid<br><br>&Help<br>  &About I76edit...<br> |
| `0164a934` | `` | eol | Version number of menu |
| `0164ac1c` | `` | plate | Rsrc_f1_6a_409 Size of resource: 0x52 bytes |
| `0164ac70` | `` | plate | Rsrc_f1_86_409 Size of resource: 0xc bytes |
| `0164ac7c` | `` | plate | Rsrc_f1_84_409 Size of resource: 0x10 bytes |
| `0164ac8c` | `` | plate | Rsrc_f1_82_409 Size of resource: 0xc bytes |
| `0164ac98` | `` | plate | Rsrc_Bitmap_6a_409 Size of resource: 0xef0 bytes |
| `0164bb88` | `` | plate | Rsrc_Bitmap_86_409 Size of resource: 0x158 bytes |
| `0164bce0` | `` | plate | Rsrc_Bitmap_84_409 Size of resource: 0x248 bytes |
| `0164bf28` | `` | plate | Rsrc_Bitmap_82_409 Size of resource: 0x158 bytes |
| `0164c080` | `` | plate | Rsrc_Bitmap_6c_409 Size of resource: 0x134 bytes |
| `0164c1b4` | `` | plate | Rsrc_Bitmap_6e_409 Size of resource: 0x134 bytes |
| `0164c2e8` | `` | plate | Rsrc_Bitmap_87_409 Size of resource: 0xd0 bytes |
| `0164c3b8` | `` | plate | Rsrc_Bitmap_73_409 Size of resource: 0x128 bytes |
| `0164c4e0` | `` | plate | Rsrc_Bitmap_74_409 Size of resource: 0x128 bytes |
| `0164c608` | `` | plate | Rsrc_Bitmap_75_409 Size of resource: 0x128 bytes |
| `0164c730` | `` | plate | Rsrc_Bitmap_77_409 Size of resource: 0x128 bytes |
| `0164c858` | `` | plate | Rsrc_Bitmap_88_409 Size of resource: 0x128 bytes |
| `0164c980` | `` | plate | Rsrc_Bitmap_89_409 Size of resource: 0x128 bytes |
| `0164caa8` | `` | plate | Rsrc_Bitmap_8a_409 Size of resource: 0x128 bytes |
| `0164cbd0` | `` | plate | Rsrc_Bitmap_8b_409 Size of resource: 0x128 bytes |
| `0164ccf8` | `` | plate | Rsrc_Bitmap_8c_409 Size of resource: 0x128 bytes |
| `0164ce20` | `` | plate | Rsrc_Bitmap_8d_409 Size of resource: 0x128 bytes |
| `0164cf48` | `` | plate | Rsrc_Bitmap_8e_409 Size of resource: 0xd0 bytes |
| `0164d018` | `` | plate | Rsrc_Bitmap_8f_409 Size of resource: 0x128 bytes |
| `0164d140` | `` | plate | Rsrc_Bitmap_7f_409 Size of resource: 0x194 bytes |
| `0164d2d4` | `` | plate | Rsrc_Bitmap_90_409 Size of resource: 0x194 bytes |
| `0164d468` | `` | plate | Rsrc_Bitmap_91_409 Size of resource: 0x194 bytes |
| `0164d5fc` | `` | plate | Rsrc_Bitmap_92_409 Size of resource: 0x194 bytes |
| `0164d790` | `` | plate | Rsrc_Bitmap_93_409 Size of resource: 0x194 bytes |
| `0164d924` | `` | plate | Rsrc_Bitmap_94_409 Size of resource: 0x194 bytes |
| `0164dab8` | `` | plate | Rsrc_Bitmap_95_409 Size of resource: 0x194 bytes |
| `0164dc4c` | `` | plate | Rsrc_Bitmap_96_409 Size of resource: 0x194 bytes |
| `0164dde0` | `` | plate | Rsrc_Bitmap_97_409 Size of resource: 0x194 bytes |
| `0164df74` | `` | plate | Rsrc_Bitmap_98_409 Size of resource: 0x194 bytes |
| `0164e108` | `` | plate | Rsrc_Accelerator_80_409 Size of resource: 0x80 bytes |
| `0164e188` | `` | plate | Rsrc_Cursor_5_409 Size of resource: 0x134 bytes |
| `0164e2bc` | `` | plate | Rsrc_GroupCursor_70_409 Size of resource: 0x14 bytes |
| `0164e2d0` | `` | plate | Rsrc_Cursor_6_409 Size of resource: 0x134 bytes |
| `0164e404` | `` | plate | Rsrc_GroupCursor_68_409 Size of resource: 0x14 bytes |
