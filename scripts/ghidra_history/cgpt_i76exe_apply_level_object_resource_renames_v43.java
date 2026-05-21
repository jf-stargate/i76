// Applies current Interstate '76 level/object/resource reconstruction names.
// Safe-by-default: renames default/provisional symbols, skips unrelated user-defined names.
//@category i76

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

public class cgpt_i76exe_apply_level_object_resource_renames_v43 extends GhidraScript {

    private static final String DEFAULT_OUT_ROOT = "/media/neon-remote/prj/i76/scratch_data";
    private static final String RUN_PREFIX = "i76_apply_level_object_resource_renames_v43";

    private static class FnRename {
        String addr, name, note;
        FnRename(String addr, String name, String note) { this.addr = addr; this.name = name; this.note = note; }
    }

    private static class DataRename {
        String addr, name, note;
        DataRename(String addr, String name, String note) { this.addr = addr; this.name = name; this.note = note; }
    }

    private FnRename[] functionRenames() {
        return new FnRename[] {
            // BWD2 / mission chunk parsing
            new FnRename("004b3db0", "parse_tagged_chunk_descriptor_table", "Core BWD2 descriptor-table dispatcher used by mission/resource sections."),
            new FnRename("004b41e0", "parse_bwd2_resource_with_descriptor_table", "Opens named resource into memory, gets size, dispatches descriptor table, releases resource ref."),
            new FnRename("004b4290", "handle_bwd2_exit_chunk", "Shared EXIT chunk handler used by descriptor tables."),
            new FnRename("004b42b0", "load_and_parse_selected_mission_resource", "Mission/resource loader path that opens/parses selected BWD2 resource."),
            new FnRename("004b4610", "validate_mission_revision_chunks", "Revision chunk validator used for WREV/RREV/OREV/etc."),

            // World/level sections
            new FnRename("004b8a10", "load_wrld_world_resource_config", "WRLD resource/config handler: ACT/LUM/TBL/NPT/sky/surface/HZD-style fields."),
            new FnRename("00493910", "parse_tdef_terrain_definition", "TDEF terrain section handler for ZMAP/ZONE terrain configuration."),
            new FnRename("004b8780", "load_rdef_rseg_route_corridor_records", "RSEG route/corridor loader; chunks serialized 0x18 records into runtime nodes."),
            new FnRename("004b8960", "load_iseg_tseg_record_context", "Shared ISEG/TSEG record-table context helper from RDEF table."),

            // Terrain runtime
            new FnRename("004927b0", "lookup_runtime_terrain_surface_class", "Terrain surface-class lookup using packed TER word bits."),
            new FnRename("004929b0", "terrain_runtime_lookup_context_helper", "Terrain lookup helper adjacent to height/surface path."),
            new FnRename("00493080", "build_runtime_terrain_page_grid_from_zmap", "Builds 128x128 runtime page-pointer grid from 80x80 ZMAP using +24/+24 offset."),
            new FnRename("00493160", "sample_runtime_terrain_height", "Samples terrain height through runtime page grid and TER page data."),
            new FnRename("004931c0", "sample_runtime_terrain_packed_word", "Samples raw packed TER word through runtime page grid."),
            new FnRename("00490a00", "build_adaptive_terrain_root_primitives", "Seeds adaptive terrain root vertices/edges/primitives."),
            new FnRename("00490fb0", "prepare_adaptive_terrain_render_context", "Prepares adaptive terrain render/tessellation context."),
            new FnRename("004911e0", "subdivide_or_emit_adaptive_terrain_quad", "Exact adaptive terrain LOD predicate: hard half_scale floor, error tests, special-surface scan, split/emit."),
            new FnRename("00491810", "allocate_terrain_leaf_primitive_node", "Allocates/links emitted terrain primitive node."),
            new FnRename("004918b0", "allocate_terrain_edge_record", "Allocates terrain edge record used by shared-edge adaptive tessellation."),
            new FnRename("004918f0", "split_terrain_edge_midpoint", "Splits/reuses terrain edge midpoint record."),
            new FnRename("00491a30", "flatten_terrain_primitive_edges_and_compute_planes", "Flattens edge refs and computes terrain polygon planes/normals."),
            new FnRename("00492270", "terrain_runtime_record_helper_00492270", "Terrain runtime helper from adaptive path; semantics still partial."),
            new FnRename("004922b0", "terrain_runtime_record_helper_004922b0", "Terrain runtime helper from adaptive path; semantics still partial."),
            new FnRename("004922f0", "terrain_runtime_record_helper_004922f0", "Terrain runtime helper from adaptive path; semantics still partial."),
            new FnRename("004924b0", "terrain_runtime_record_helper_004924b0", "Terrain runtime helper from adaptive path; semantics still partial."),
            new FnRename("004937c0", "terrain_runtime_finalize_or_draw_helper", "Terrain runtime draw/finalization helper from traced terrain path."),
            new FnRename("00494a90", "compute_triangle_plane_or_normal", "Called by terrain flatten path to compute plane/normal-like data."),

            // ODEF object placement / class cases / spawn and regen
            new FnRename("004b7a90", "parse_odef_object_definition_section", "ODEF top-level descriptor-table section handler."),
            new FnRename("004b7ac0", "load_odef_object_record", "ODEF/OBJ record handler; dispatches by class byte at payload +0x5c."),
            new FnRename("004b7b96", "odef_case_load_vcf_object", "ODEF class case body for class 0x01/0x08/0x09; formats label.vcf and loads VCFC path."),
            new FnRename("004b7be9", "odef_case_load_sdf_object", "ODEF class case body for static classes; formats label.sdf and parses SDF child table."),
            new FnRename("004b7cef", "odef_case_fallback_or_null_object", "Fallback/null-ish ODEF class case for unmapped class families."),
            new FnRename("004b8230", "copy_odef_basis_position_to_runtime_transform", "Copies ODEF basis +0x08..+0x28 and float position +0x2c/+0x30/+0x34 into runtime transform block."),
            new FnRename("004b81c0", "bind_odef_vehicle_geometry_context", "ODEF vehicle/object geometry binding helper called from class paths."),
            new FnRename("00450f90", "register_odef_spawn_or_regen_transform", "Stores spawn/regen transform records into fixed tables."),

            // LDEF / SDF / SOBJ / child descriptor path
            new FnRename("004b8f40", "parse_ldef_static_entity_section", "LDEF top-level descriptor-table section handler."),
            new FnRename("004b8f70", "load_ldef_static_world_entity_record", "LDEF/OBJ handler; formats label.sdf and parses scene object descriptor."),
            new FnRename("004b7ea0", "parse_scene_object_descriptor_resource", "Parses SDF child descriptor table 00500b18."),
            new FnRename("004b7f70", "handle_sdfc_scene_descriptor_header", "SDFC handler in SDF child descriptor table."),
            new FnRename("004b7ff0", "handle_sgeo_scene_geometry_record", "SGEO handler in SDF child descriptor table."),
            new FnRename("004b8050", "handle_schk_add_chunk_to_parent_object", "SCHK handler; adds/attaches chunk to parent object."),
            new FnRename("004b8470", "load_sobj_scene_object_geometry_id", "SOBJ handler; formats part.geo and calls GEO loader path."),
            new FnRename("004b8ed0", "create_lobj_light_object", "LOBJ light-object child handler in SDF descriptor path."),

            // VCF / vehicle-object path
            new FnRename("004ad640", "format_8char_resource_basename_with_suffix", "Masks high bits from 8-byte label, rejects empty basename, appends optional suffix."),
            new FnRename("004ad6f0", "load_vehicle_config_for_world_object", "Loads/parses label.vcf through VCFC descriptor path for ODEF VCF classes."),
            new FnRename("004adb90", "parse_vcfc_vehicle_config_root", "VCFC root parser for vehicle/object config."),
            new FnRename("004ad950", "parse_vcfc_vdf_vtf_wdf_resource_refs", "VCFC helper parsing VDF/VTF/WDF resource refs."),
            new FnRename("004ae5e0", "load_vcfc_referenced_resource", "Helper used by VCFC resource reference parser."),
            new FnRename("004b3650", "parse_vdf_vehicle_definition_resource", "VDF vehicle/object definition parser."),
            new FnRename("004b7800", "instantiate_vdf_vehicle_geometry_part_sets", "Instantiates VDF geometry part sets."),

            // GEO/render-record path
            new FnRename("00446c90", "construct_geometry_from_geo_buffer", "Main OEG./GEO constructor; validates magic, reads counts, allocates runtime geometry."),
            new FnRename("004469a0", "load_geo_resource_by_formatted_name", "GEO loader called by SOBJ path after formatting part.geo."),
            new FnRename("0045cbe0", "build_lit_geo_render_records_from_sections", "Builds lit render records from GEO sections; transform/light/material path."),
            new FnRename("0045d100", "render_world_object_geo_pass", "Higher-level world-object GEO render pass."),
            new FnRename("0045d530", "render_world_object_geo_recursive_pass", "Recursive/child world-object GEO render pass."),
            new FnRename("00471fd0", "submit_lit_textured_polygon_to_renderer", "Submits lit textured polygon to renderer."),
            new FnRename("00478430", "compute_geo_vertex_lighting_from_normals", "Computes GEO vertex lighting from normals/material/light context."),
            new FnRename("00493550", "transform_world_object_bounds_or_geometry", "Applies world-object transform to bounds/geometry."),
            new FnRename("00494e20", "compose_transform_matrix_or_basis", "Composes runtime transform matrix/basis."),
            new FnRename("00494da0", "transform_geometry_vertex_array", "Transforms geometry vertex array in render path."),
            new FnRename("00494ef0", "transform_section_centroid_or_plane", "Transforms section centroid/plane-like data."),
            new FnRename("004925f0", "link_world_object_and_bounds", "World-object link/bounds helper used by placement paths."),

            // Resource acquisition / cache / PIX/PAK / ZFSF
            new FnRename("0046fab0", "loaded_resource_cache_lookup", "Loaded resource cache lookup helper."),
            new FnRename("0046fb30", "initialize_loaded_resource_cache_heap", "Initializes loaded-resource cache heap/state."),
            new FnRename("0046fbe0", "loaded_resource_cache_insert_or_ref", "Loaded resource cache insert/reference helper."),
            new FnRename("0046fd40", "release_resource_file_reference", "Releases loaded-resource file reference after descriptor parse."),
            new FnRename("0046fee0", "get_loaded_resource_file_size", "Returns loaded resource size for BWD2 parser."),
            new FnRename("0046ffc0", "open_resource_file_into_memory", "Main resource open path below BWD2 parser; lowercases name and checks indexed/cache paths."),
            new FnRename("00470070", "load_resource_stream_into_loaded_cache", "Loads resource payload into cache using registered-resource payload helpers."),
            new FnRename("00470340", "resource_exists_in_cache_or_search_paths", "Resource existence/find helper used for optional state/resource paths."),
            new FnRename("00470660", "load_pix_pak_resource_index", "Scans *.pix, derives .pak, parses name/offset/size rows, sorts index."),
            new FnRename("00470b20", "load_indexed_pix_pak_resource_payload", "Loads payload from indexed PIX/PAK resource record."),
            new FnRename("00470c70", "find_indexed_pix_pak_resource_record", "Finds indexed PIX/PAK resource record by key."),
            new FnRename("00470ca0", "indexed_pix_pak_resource_helper", "PIX/PAK indexed resource helper near loader path."),
            new FnRename("004b2ac0", "find_next_resource_file_record_by_pattern", "Resource file record pattern iterator/helper."),
            new FnRename("004b2b30", "register_resource_key_for_zix_path", "Registers resource key/path mapping, callback-table entry from shell contract."),
            new FnRename("004b2e00", "find_registered_resource_record_by_key", "Looks up registered resource record by lowercase key."),
            new FnRename("004b3000", "load_registered_resource_payload_bool", "Boolean wrapper around registered resource payload loading."),
            new FnRename("004b3030", "load_registered_resource_payload", "Loads registered resource payload via ZFS/loose/indexed path."),
            new FnRename("004b32f0", "registered_resource_payload_size_context_helper", "Registered resource payload-size helper/context."),
            new FnRename("004b3310", "get_registered_resource_payload_size", "Gets registered resource payload size."),
            new FnRename("004b3550", "registered_resource_lookup_context_helper", "Registered resource lookup context helper."),
            new FnRename("004b9800", "open_zfsf_archive", "Opens ZFSF archive."),
            new FnRename("004b9bd0", "read_zfsf_record_payload", "Reads raw ZFSF record payload."),
            new FnRename("004b9db0", "read_zfsf_record_allocated_payload", "Allocates and reads ZFSF record payload."),
            new FnRename("004b9fc0", "zfsf_decompress_record_payload_by_lzo_mode", "Dispatches ZFSF LZO1X/LZO1Y decompression by flags."),

            // ADEF/FSM
            new FnRename("00409740", "initialize_fsm_runtime_heap_and_tables", "ADEF/FSM top-level heap/table bootstrap."),
            new FnRename("00410720", "load_serialized_fsm_runtime_tables", "Loads serialized FSM runtime tables."),
            new FnRename("004105a0", "fsm_load_record_array_with_bitfields", "FSM serialized array loader with bitfields."),
            new FnRename("004102d0", "fsm_load_record_array_with_vec3_lists", "FSM serialized array loader with vec3 lists."),
            new FnRename("00410490", "fsm_load_linked_state_blocks", "FSM linked state-block loader."),
            new FnRename("00410a10", "fsm_match_command_name_to_id", "FSM command/predicate name matcher returning command ID."),
            new FnRename("004125c0", "finalize_loaded_fsm_runtime_tables", "FSM finalizer after serialized tables loaded."),
            new FnRename("00412400", "fsm_register_instance_ids_from_mission", "Registers FSM instance IDs from mission data."),
            new FnRename("004122d0", "fsm_validate_wav_smk_resource_list", "Validates project WAV/SMK resource list."),
            new FnRename("00412500", "fsm_relocate_command_table_internal_pointers", "Relocates FSM command-table internal pointers."),
        };
    }

    private DataRename[] dataRenames() {
        return new DataRename[] {
            // Descriptor tables
            new DataRename("00500ca0", "bwd2_wdef_descriptor_table", "WDEF table: WREV/WRLD/EXIT."),
            new DataRename("004fae18", "bwd2_tdef_descriptor_table", "TDEF table: TREV/ZMAP/ZONE/EXIT."),
            new DataRename("00500cd0", "bwd2_rdef_descriptor_table", "RDEF table: RREV/RSEG/ISEG/TSEG/EXIT."),
            new DataRename("00500ae8", "bwd2_odef_descriptor_table", "ODEF table: OREV/OBJ/EXIT."),
            new DataRename("00500b18", "sdf_child_descriptor_table", "SDF child table: SDFC/SOBJ/SGEO/SCHK/LOBJ/EXIT."),
            new DataRename("00500d20", "bwd2_adef_descriptor_table", "ADEF table: AREV/FSM/EXIT."),
            new DataRename("00500d50", "extended_x_resource_descriptor_table", "Extended X resource table: XDFC/XGEO/EXIT."),
            new DataRename("00500d80", "bwd2_ldef_descriptor_table", "LDEF table: LREV/OBJ/EXIT."),
            new DataRename("004fef70", "vcfc_descriptor_table", "VCFC root descriptor table."),
            new DataRename("004feff0", "vdfc_reference_descriptor_table", "VCFC/VDFC reference descriptor table."),
            new DataRename("004ff0b0", "vdfc_descriptor_table", "VDFC descriptor table used by VCFC parser."),
            new DataRename("004ff1d0", "vtfc_descriptor_table", "VTFC descriptor table used by VCFC parser."),
            new DataRename("004ff330", "vcst_vehicle_state_descriptor_table", "Optional VSF/VCST descriptor table."),
            new DataRename("004ff450", "component_cdf_descriptor_table", "ECNK/component CDF descriptor table."),

            // ODEF class dispatch tables
            new DataRename("004b7e24", "odef_class_case_jump_table", "Jump table indexed by ODEF class case map."),
            new DataRename("004b7e44", "odef_class_to_case_map", "Maps ODEF class byte-1 to case index; class-specific VCF/SDF/fallback policy."),

            // Terrain globals/arrays
            new DataRename("0059c560", "terrain_primitive_list_head", "Adaptive terrain primitive list head."),
            new DataRename("0059c574", "terrain_primitive_list_tail", "Adaptive terrain primitive list tail/current."),
            new DataRename("005dd320", "terrain_generated_vertex_records", "Generated terrain vertex records, 0x0c stride."),
            new DataRename("005dd2ec", "terrain_projected_vertex_aux_records", "Terrain projected/auxiliary vertex records."),
            new DataRename("006442ec", "terrain_generated_vertex_count", "Generated terrain vertex counter."),
            new DataRename("006442c8", "terrain_lod_projected_error_global_x", "Adaptive terrain projected/error global used in split predicate."),
            new DataRename("006442cc", "terrain_lod_projected_error_global_z", "Adaptive terrain projected/error global used in split predicate."),

            // RSEG runtime globals
            new DataRename("005db988", "rseg_runtime_node_list_head", "RSEG runtime linked-node list head."),
            new DataRename("005db98c", "rseg_runtime_node_count", "RSEG runtime node count."),

            // Spawn/regen tables
            new DataRename("0053fd88", "odef_spawn_transform_table", "ODEF spawn transform table, 0x40 entries, 0x40 bytes each."),
            new DataRename("00540d98", "odef_spawn_transform_count", "ODEF spawn transform count."),
            new DataRename("0053ecb0", "odef_regen_transform_table", "ODEF regen transform table, 0x40 entries, 0x40 bytes each."),
            new DataRename("00540d9c", "odef_regen_transform_count", "ODEF regen transform count."),

            // Resource/load/cache globals
            new DataRename("005db97c", "current_bwd2_loaded_resource_ptr", "Current loaded resource pointer while parsing descriptor table."),
            new DataRename("006564e0", "indexed_or_registered_resource_table", "Registered/indexed resource table area referenced by lookup path."),
            new DataRename("00609560", "loaded_resource_cache_head", "Loaded-resource cache list/global cluster start."),
            new DataRename("00609594", "loaded_resource_cache_tail_or_state", "Loaded-resource cache list/global cluster end/state."),

            // FSM globals
            new DataRename("0051f5b4", "fsm_command_table_or_globals", "FSM command/global table cluster."),
            new DataRename("0051f608", "fsm_runtime_globals_cluster", "FSM runtime globals initialized by ADEF/FSM bootstrap."),
            new DataRename("005244d0", "fsm_serialized_stream_cursor", "FSM serialized stream cursor/global pointer."),
            new DataRename("005244d4", "fsm_serialized_stream_limit", "FSM serialized stream limit/base pointer."),
        };
    }

    @Override
    protected void run() throws Exception {
        String root = askString("I76 rename report output root", "Output root", DEFAULT_OUT_ROOT);
        if (root == null || root.trim().length() == 0) root = DEFAULT_OUT_ROOT;
        File rootDir = new File(root.trim());
        if (!rootDir.exists()) rootDir.mkdirs();

        String stamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
        File outDir = new File(rootDir, RUN_PREFIX + "_" + stamp);
        outDir.mkdirs();

        File fnReport = new File(outDir, "function_renames.tsv");
        File dataReport = new File(outDir, "data_labels.tsv");
        File manifest = new File(outDir, "manifest.json");

        int tx = currentProgram.startTransaction("apply I76 level/object/resource renames v43");
        boolean commit = false;
        try (BufferedWriter fw = new BufferedWriter(new FileWriter(fnReport));
             BufferedWriter dw = new BufferedWriter(new FileWriter(dataReport))) {
            fw.write("address\told_name\tnew_name\tstatus\tnote\n");
            dw.write("address\told_name\tnew_name\tstatus\tnote\n");

            for (FnRename r : functionRenames()) {
                applyFunctionRename(r, fw);
            }
            for (DataRename r : dataRenames()) {
                applyDataLabel(r, dw);
            }
            commit = true;
        } finally {
            currentProgram.endTransaction(tx, commit);
        }

        try (BufferedWriter mw = new BufferedWriter(new FileWriter(manifest))) {
            mw.write("{\n");
            mw.write("  \"format\": \"i76_level_object_resource_rename_report\",\n");
            mw.write("  \"version\": 43,\n");
            mw.write("  \"program\": \"" + esc(currentProgram.getName()) + "\",\n");
            mw.write("  \"policy\": {\n");
            mw.write("    \"odef_vcf_classes\": \"0x01,0x08,0x09; class 0x01 also handles spawn/regen specials\",\n");
            mw.write("    \"odef_sdf_classes\": \"0x02,0x03,0x04,0x07,0x0a,0x0b,0x0c,0x50,0x52,0x53\",\n");
            mw.write("    \"odef_fallback_classes\": \"0x05,0x06,0x0d..0x4f,0x51; class 0/blank diagnostic\",\n");
            mw.write("    \"ldef\": \"label.sdf\",\n");
            mw.write("    \"sobj\": \"partName.geo\"\n");
            mw.write("  },\n");
            mw.write("  \"outputs\": [\"function_renames.tsv\", \"data_labels.tsv\"]\n");
            mw.write("}\n");
        }

        createTar(rootDir, outDir);
        println("Wrote rename reports to: " + outDir.getAbsolutePath());
    }

    private void applyFunctionRename(FnRename r, BufferedWriter w) throws Exception {
        Address a = parseAddressSafe(r.addr);
        if (a == null) {
            w.write(r.addr + "\t\t" + r.name + "\tbad_address\t" + escTsv(r.note) + "\n");
            return;
        }
        Function f = getFunctionAt(a);
        if (f == null) {
            w.write(r.addr + "\t\t" + r.name + "\tmissing_function\t" + escTsv(r.note) + "\n");
            return;
        }
        String old = f.getName();
        String status;
        if (old.equals(r.name)) {
            status = "already";
        } else if (canReplaceFunctionName(old)) {
            try {
                f.setName(r.name, SourceType.USER_DEFINED);
                status = "renamed";
            } catch (Exception e) {
                status = "error:" + e.getClass().getSimpleName() + ":" + e.getMessage();
            }
        } else {
            status = "skipped_existing_user_name";
        }
        addPlateComment(a, r.name + "\n" + r.note);
        w.write(r.addr + "\t" + escTsv(old) + "\t" + escTsv(r.name) + "\t" + escTsv(status) + "\t" + escTsv(r.note) + "\n");
    }

    private void applyDataLabel(DataRename r, BufferedWriter w) throws Exception {
        Address a = parseAddressSafe(r.addr);
        if (a == null) {
            w.write(r.addr + "\t\t" + r.name + "\tbad_address\t" + escTsv(r.note) + "\n");
            return;
        }
        SymbolTable st = currentProgram.getSymbolTable();
        Symbol oldSym = st.getPrimarySymbol(a);
        String old = oldSym == null ? "" : oldSym.getName();
        String status;
        if (old.equals(r.name)) {
            status = "already";
        } else if (oldSym == null || canReplaceDataName(old)) {
            try {
                Symbol s = st.createLabel(a, r.name, SourceType.USER_DEFINED);
                s.setPrimary();
                status = "labeled";
            } catch (Exception e) {
                status = "error:" + e.getClass().getSimpleName() + ":" + e.getMessage();
            }
        } else {
            status = "skipped_existing_user_name";
        }
        addPlateComment(a, r.name + "\n" + r.note);
        w.write(r.addr + "\t" + escTsv(old) + "\t" + escTsv(r.name) + "\t" + escTsv(status) + "\t" + escTsv(r.note) + "\n");
    }

    private boolean canReplaceFunctionName(String n) {
        if (n == null) return true;
        String l = n.toLowerCase();
        return l.startsWith("fun_") || l.startsWith("sub_") || l.startsWith("thunk_fun_") ||
               l.startsWith("i76_") || l.startsWith("cgpt_") || l.startsWith("unknown_") ||
               l.contains("context_helper") || l.endsWith("_helper");
    }

    private boolean canReplaceDataName(String n) {
        if (n == null || n.length() == 0) return true;
        String l = n.toLowerCase();
        return l.startsWith("dat_") || l.startsWith("ptr_") || l.startsWith("off_") ||
               l.startsWith("byte_") || l.startsWith("word_") || l.startsWith("dword_") ||
               l.startsWith("i76_") || l.startsWith("cgpt_") || l.startsWith("unknown_");
    }

    private Address parseAddressSafe(String s) {
        try {
            return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(s);
        } catch (Exception e) {
            return null;
        }
    }

    private void addPlateComment(Address a, String text) {
        try {
            CodeUnit cu = currentProgram.getListing().getCodeUnitAt(a);
            if (cu != null) {
                String old = cu.getComment(CodeUnit.PLATE_COMMENT);
                String marker = "I76 rename v43";
                String addition = marker + ": " + text;
                if (old == null || old.length() == 0) {
                    cu.setComment(CodeUnit.PLATE_COMMENT, addition);
                } else if (!old.contains(marker)) {
                    cu.setComment(CodeUnit.PLATE_COMMENT, old + "\n\n" + addition);
                }
            }
        } catch (Exception ignored) {}
    }

    private void createTar(File rootDir, File outDir) {
        try {
            File tarFile = new File(rootDir, outDir.getName() + ".tar");
            ProcessBuilder pb = new ProcessBuilder("tar", "-cf", tarFile.getAbsolutePath(), "-C", rootDir.getAbsolutePath(), outDir.getName());
            pb.redirectErrorStream(true);
            Process p = pb.start();
            p.waitFor();
        } catch (Exception e) {
            println("WARNING: could not create tar: " + e.getMessage());
        }
    }

    private String esc(String s) {
        if (s == null) return "";
        return s.replace("\\", "\\\\").replace("\"", "\\\"").replace("\n", "\\n").replace("\r", "\\r");
    }

    private String escTsv(String s) {
        if (s == null) return "";
        return s.replace("\t", " ").replace("\n", " | ").replace("\r", " ");
    }
}
