// Apply Interstate '76 level/static-object/material/terrain symbol baseline from the
// v8-v47 reconstruction pass.
//
// v49 fixes Ghidra 12.0.4 API signatures for askDirectory() and createBookmark().
//
// Ghidra: tested style for 12.0.4 compatibility.
// Category: flat i76 category, no subcategories.
//
// This script is intentionally conservative:
//   - It renames only default/provisional/confidence-prefixed function names.
//   - It does not overwrite unrelated user-defined symbols.
//   - It applies comments/bookmarks even when a rename is skipped.
//   - It writes TSV logs into an interactive output directory.
//   - It creates a timestamped output folder and a sibling .tar archive.
//
// Recommended location:
//   /home/z/ghidra_scripts/cgpt_i76exe_apply_level_static_material_terrain_renames_v49.java
//
//@category i76

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class cgpt_i76exe_apply_level_static_material_terrain_renames_v49 extends GhidraScript {

    private static final String DEFAULT_OUT_DIR = "/media/neon-remote/prj/i76/scratch_data";

    private static class FnSpec {
        String addr;
        String name;
        String confidence;
        String module;
        String comment;
        FnSpec(String addr, String name, String confidence, String module, String comment) {
            this.addr = addr;
            this.name = name;
            this.confidence = confidence;
            this.module = module;
            this.comment = comment;
        }
    }

    private static class DataSpec {
        String addr;
        String name;
        String confidence;
        String module;
        String comment;
        DataSpec(String addr, String name, String confidence, String module, String comment) {
            this.addr = addr;
            this.name = name;
            this.confidence = confidence;
            this.module = module;
            this.comment = comment;
        }
    }

    private static class CommentSpec {
        String addr;
        String kind;
        String module;
        String text;
        CommentSpec(String addr, String kind, String module, String text) {
            this.addr = addr;
            this.kind = kind;
            this.module = module;
            this.text = text;
        }
    }

    private static final FnSpec[] FUNCTIONS = new FnSpec[] {
        new FnSpec("00446c90", "construct_geometry_from_geo_buffer", "high", "geo_static_vehicle_mesh",
            "Parses/builds runtime geometry from GEO buffer. Reused by vehicle and static-object reconstruction. Exporter v14-v47 confirms static SDF/SGEO child partName.geo instances parse through this path."),

        new FnSpec("0045cbe0", "build_lit_geo_render_records_from_sections", "medium_high", "geo_render_records",
            "Builds lit textured render records from GEO sections. Prior tracing suggests reverse corner walk, per-corner UV copy, and lighting/normal index handling. Relevant to static GEO UV/material fidelity."),

        new FnSpec("0045d100", "render_lit_geo_world_object_pass_a", "medium", "geo_render_records",
            "World/static lit GEO render pass candidate. Kept as medium confidence pending deeper render-path trace for material/alpha/road handling."),

        new FnSpec("0045d530", "render_lit_geo_world_object_pass_b", "medium", "geo_render_records",
            "Companion world/static lit GEO render pass candidate. Relevant to final material/alpha validation and possible renderer-specific state."),

        new FnSpec("00471fd0", "submit_lit_textured_polygon_to_renderer", "medium_high", "render_submit",
            "Low-level lit textured polygon submit path. Candidate next trace target for alpha state, keyed transparency, and material flags."),

        new FnSpec("00478430", "compute_geo_vertex_lighting_from_normals", "medium", "geo_lighting",
            "Computes lighting from GEO normal/lighting indices. Relevant to static object visual parity after geometry/material binding."),

        new FnSpec("004911e0", "adaptive_terrain_should_subdivide_patch", "high", "terrain_lod",
            "Adaptive terrain subdivision predicate. Confirmed hard split while half_scale >= 0x20 and special-surface forced split when word >= 0x4000 && (word & 0xe000) != 0xa000."),

        new FnSpec("00493550", "apply_world_object_transform_to_bounds_or_geometry", "medium", "world_object_transform",
            "Applies world-object transform to geometry/bounds. Relevant to ODEF/LDEF object placement and static SDF/SGEO hierarchy validation."),

        new FnSpec("00495060", "is_miss16_high_color_resource_mode", "high", "mission_color_depth",
            "High-color/miss16 resource-mode predicate. Prior name corrected from heap/global guess. Relevant to miss8 direct MAP vs miss16 M16/VQM resource differences."),

        new FnSpec("004b3650", "parse_vdf_vehicle_definition_resource", "high", "vehicle_vdf",
            "Parses VDF vehicle definition. Included here because ODEF class-specific VCF path still flows toward VDF/VTF/GEO for class 0x01/0x08/0x09."),

        new FnSpec("004b7800", "instantiate_vdf_vehicle_geometry_part_sets", "medium_high", "vehicle_vdf_geo",
            "Instantiates VDF vehicle geometry part sets. Related to VCF-backed ODEF classes; static SDF path is separate."),

        new FnSpec("004b7ac0", "handle_level_odef_obj_record_by_class", "high", "level_object_dispatch",
            "Main ODEF/OBJ class-dispatch handler. v42/v43 evidence: class-specific resource policy, not all VCF and not all SDF. Static classes route to SDF; selected actor/vehicle classes route to VCF; spawn/regen markers are special."),

        new FnSpec("004b8230", "copy_odef_transform_and_resolve_object_label", "high", "level_object_dispatch",
            "Copies ODEF 3x3 basis and position into runtime transform block and prepares/resolves object label. Validates ODEF +0x08 basis and +0x2c/+0x30/+0x34 position interpretation."),

        new FnSpec("004b8470", "load_sobj_child_geo_resource", "high", "sdf_static_object",
            "SDF child SOBJ/SGEO loader that formats/loads partName.geo. Exporter v12-v47 confirms SDF SGEO declared parts resolve to embedded GEO assets."),

        new FnSpec("004b8f70", "handle_ldef_obj_static_scene_object", "high", "level_object_dispatch",
            "LDEF/OBJ static scene-object handler. Formats/resolves label.sdf for normal records; distinct from ODEF class-specific dispatch."),

        new FnSpec("004af8f0", "load_vtfc_vehicle_texture_map_sets", "high", "material_vtfc",
            "Loads VTFC vehicle texture map sets. Retained for cross-reference: static material work now shows VQM-first is often correct for M06 static GEO material families."),

        new FnSpec("004b0150", "bind_optional_vtfc_texture_map_slot", "high", "material_vtfc",
            "Binds optional VTFC texture map slot. Useful comparison point for static GEO material lookup and MAP->M16/VQM fallback."),

        new FnSpec("004b0190", "bind_vtfc_six_face_map_slots", "high", "material_vtfc",
            "Binds VTFC six-face MAP slots. Static material path differs but reuses embedded resource naming patterns."),

        new FnSpec("004ad6f0", "load_vehicle_config_for_world_object", "high", "vehicle_vcf",
            "Loads VCF-backed world object/vehicle config. ODEF class 0x01/0x08/0x09 use label.vcf except spawn/regen special markers."),

        new FnSpec("004adb90", "parse_vcfc_vehicle_config_root", "high", "vehicle_vcf",
            "Parses VCFC vehicle config root. Included for ODEF VCF-backed class chain completeness."),

        new FnSpec("004ad950", "parse_vcfc_vdf_vtf_wdf_resource_refs", "high", "vehicle_vcf",
            "Parses VCF references to VDF/VTF/WDF resources. Included for ODEF VCF-backed class chain completeness."),

        new FnSpec("004b9800", "open_zfsf_archive", "high", "resource_zfs",
            "Opens ZFSF archive. Embedded resource index is required for static SDF child GEO and material assets."),

        new FnSpec("004b9bd0", "read_zfsf_record_payload", "high", "resource_zfs",
            "Reads ZFSF record payload. Static objects/materials resolve many assets through embedded PIX/PAK/ZFS resource index."),

        new FnSpec("004b9db0", "read_zfsf_record_allocated_payload", "high", "resource_zfs",
            "Allocated ZFSF payload reader. Cross-reference for standalone embedded resource extraction."),

        new FnSpec("004b9fc0", "zfsf_decompress_record_payload_by_lzo_mode", "high", "resource_zfs_lzo",
            "ZFSF LZO decompression wrapper; accepts only return code 0. Embedded assets for static objects/materials rely on this stack."),

        new FnSpec("0044b430", "decode_vqm_cbk_4x4_blocks_to_indexed_pixels", "high", "material_vqm_cbk",
            "Decodes VQM/CBK 4x4 indexed blocks. Static material pass v41+ shows VQM-first is generally correct for M06 building/static texture families; road/junction details remain type-specific."),

        new FnSpec("00450f90", "write_spawn_regen_marker_table_entry", "medium_high", "level_object_dispatch",
            "Special spawn/regen marker table writer. ODEF class 0x01 labels 'spawn' and 'regen' are not ordinary label.vcf geometry objects.")
    };

    private static final DataSpec[] DATA_LABELS = new DataSpec[] {
        new DataSpec("00500b18", "sdf_child_descriptor_table", "high", "sdf_static_object",
            "Descriptor table used by SDF child parser/loader path. Static object reconstruction confirms SDF SGEO declared parts -> partName.geo embedded assets."),

        new DataSpec("004fa170", "active_runtime_palette_buffer_or_table", "medium", "palette_material",
            "Runtime palette/table bytes observed in EXE; not necessarily the correct static/terrain palette. Static/terrain reconstruction shows mission ACT/LUM/TBL/PCF context may differ by miss8/miss16 and material family."),

        new DataSpec("00504a04", "shell_launch_config_scalar_copy", "medium_high", "shell_contract",
            "Shell launch/session config scalar copied from ShellMain arg10 +0x6c after return. Included for durable shell-to-engine contract continuity."),

        new DataSpec("00504a08", "shell_launch_config_short_text_block", "medium_high", "shell_contract",
            "Shell launch/session config text block copied from ShellMain arg10 +0x70. Included for durable shell-to-engine contract continuity."),

        new DataSpec("00504a30", "shell_launch_config_dword_array", "medium_high", "shell_contract",
            "Shell launch/session config dword array copied from ShellMain arg10 +0x98. Included for durable shell-to-engine contract continuity.")
    };

    private static final CommentSpec[] INLINE_COMMENTS = new CommentSpec[] {
        new CommentSpec("004b7b96", "plate", "level_object_dispatch",
            "ODEF VCF case body. Calls transform/label helper, formats .vcf, then calls load_vehicle_config_for_world_object. Applies to ordinary class 0x01 and classes 0x08/0x09; spawn/regen are special."),

        new CommentSpec("004b7be9", "plate", "level_object_dispatch",
            "ODEF SDF case body. Calls transform/label helper, formats .sdf, and parses BWD2 resource using SDF child descriptor table at 00500b18. Applies to static object classes such as 0x02/0x03/0x04, 0x07, 0x0a-0x0c, and 0x50/0x52/0x53."),

        new CommentSpec("004911e0", "repeatable", "terrain_lod",
            "Terrain surface class is encoded in high bits of TER word. Height = word & 0x0fff; surface_class = word >> 13. Surface class 3 is now strong road-surface candidate; class 7 likely roadbed/shoulder candidate for M06."),

        new CommentSpec("004b8470", "repeatable", "sdf_static_object",
            "Static scene SDF child loader. Reconstruction v12-v47: SDF SGEO declared part records contain part name, parent name, local basis/position; partName.geo resolves through embedded PIX/PAK/ZFS asset index."),

        new CommentSpec("0044b430", "repeatable", "material_vqm_cbk",
            "VQM/CBK decode is important for static-object material correctness. M06 static materials generally require VQM-first; I2D road/junction and AT ground/pad families may require overrides. Road/RSEG material type mapping still needs game/editor tracing."),

        new CommentSpec("00471fd0", "repeatable", "render_submit",
            "Trace target for alpha/blend/material state. Reconstruction v43-v44: static cutout texture AW_1BR_1 requires black-key alpha; exporter emits RGBA PNG and MTL transparency hints, but runtime source state remains to be verified."),

        new CommentSpec("00495060", "repeatable", "mission_color_depth",
            "miss8/miss16 resource divergence matters. M06 miss8 terrain uses direct 128x128 indexed MAP TT181SD_.MAP; miss16 points to MAP names resolving through M16/VQM. Static object classes often still use M16/VQM siblings.")
    };

    private File outDir;
    private BufferedWriter fnLog;
    private BufferedWriter dataLog;
    private BufferedWriter commentLog;
    private BufferedWriter manifest;

    @Override
    public void run() throws Exception {
        File base = askDirectory("Choose output base directory for rename logs (default: " + DEFAULT_OUT_DIR + ")", "OK");
        String ts = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
        outDir = new File(base, "cgpt_i76exe_level_static_material_renames_v48_" + ts);
        if (!outDir.mkdirs() && !outDir.isDirectory()) {
            throw new IOException("Could not create output directory: " + outDir.getAbsolutePath());
        }

        fnLog = openLog("function_renames.tsv", "address\trequested_name\told_name\taction\tconfidence\tmodule\tnote\n");
        dataLog = openLog("data_labels.tsv", "address\trequested_name\told_name\taction\tconfidence\tmodule\tnote\n");
        commentLog = openLog("comments.tsv", "address\tkind\taction\tmodule\tnote\n");
        manifest = openLog("manifest.json", "");

        int tx = currentProgram.startTransaction("cgpt i76 level/static/material rename baseline v48");
        boolean commit = false;
        int fnApplied = 0, fnSkipped = 0, dataApplied = 0, dataSkipped = 0, commentsApplied = 0;
        try {
            for (FnSpec spec : FUNCTIONS) {
                boolean ok = applyFunctionSpec(spec);
                if (ok) fnApplied++; else fnSkipped++;
                if (monitor.isCancelled()) break;
            }
            for (DataSpec spec : DATA_LABELS) {
                boolean ok = applyDataSpec(spec);
                if (ok) dataApplied++; else dataSkipped++;
                if (monitor.isCancelled()) break;
            }
            for (CommentSpec spec : INLINE_COMMENTS) {
                applyCommentSpec(spec);
                commentsApplied++;
                if (monitor.isCancelled()) break;
            }
            commit = true;
        } finally {
            currentProgram.endTransaction(tx, commit);
            writeManifest(ts, fnApplied, fnSkipped, dataApplied, dataSkipped, commentsApplied, commit);
            closeQuiet(fnLog);
            closeQuiet(dataLog);
            closeQuiet(commentLog);
            closeQuiet(manifest);
        }

        createTarArchive(outDir);
        println("wrote: " + outDir.getAbsolutePath());
        println("tar:   " + outDir.getAbsolutePath() + ".tar");
        println("function renames applied=" + fnApplied + " skipped=" + fnSkipped);
        println("data labels applied=" + dataApplied + " skipped=" + dataSkipped);
        println("comments applied=" + commentsApplied);
    }

    private BufferedWriter openLog(String name, String header) throws IOException {
        BufferedWriter bw = new BufferedWriter(new FileWriter(new File(outDir, name)));
        if (header != null && header.length() > 0) bw.write(header);
        return bw;
    }

    private Address addressFromString(String s) {
        try {
            return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(s);
        } catch (Exception e) {
            return null;
        }
    }

    private boolean applyFunctionSpec(FnSpec spec) throws Exception {
        Address a = addressFromString(spec.addr);
        if (a == null) {
            logFn(spec, "", "bad_address", "could_not_parse_address");
            return false;
        }
        Function f = getFunctionAt(a);
        if (f == null) {
            f = getFunctionContaining(a);
        }
        if (f == null) {
            logFn(spec, "", "missing_function", "no_function_at_or_containing_address");
            setCommentAt(a, CodeUnit.REPEATABLE_COMMENT, mkFnComment(spec, "Function missing at/containing target address."));
            return false;
        }

        String old = f.getName();
        boolean canRename = isSafeFunctionNameToOverwrite(old);
        if (!canRename && old.equals(spec.name)) {
            setFunctionComment(f, mkFnComment(spec, "Name already matches baseline."));
            logFn(spec, old, "already_named", "name_already_matches");
            return true;
        }
        if (!canRename) {
            setFunctionComment(f, mkFnComment(spec, "Rename skipped because existing name appears user-defined."));
            logFn(spec, old, "skipped_existing_user_name", "existing_name_not_overwritten");
            return false;
        }

        try {
            f.setName(spec.name, SourceType.USER_DEFINED);
            setFunctionComment(f, mkFnComment(spec, "Renamed by conservative baseline script."));
            createBookmark(a, "i76", "rename_v49: " + spec.name + " [" + spec.confidence + "]");
            logFn(spec, old, "renamed", "ok");
            return true;
        } catch (Exception e) {
            setFunctionComment(f, mkFnComment(spec, "Rename failed: " + e.getMessage()));
            logFn(spec, old, "rename_failed", sanitize(e.getMessage()));
            return false;
        }
    }

    private boolean applyDataSpec(DataSpec spec) throws Exception {
        Address a = addressFromString(spec.addr);
        if (a == null) {
            logData(spec, "", "bad_address", "could_not_parse_address");
            return false;
        }
        SymbolTable st = currentProgram.getSymbolTable();
        Symbol primary = st.getPrimarySymbol(a);
        String old = primary == null ? "" : primary.getName();

        boolean canRename = (primary == null) || isSafeDataNameToOverwrite(old);
        if (!canRename && old.equals(spec.name)) {
            setCommentAt(a, CodeUnit.REPEATABLE_COMMENT, mkDataComment(spec, "Name already matches baseline."));
            logData(spec, old, "already_named", "name_already_matches");
            return true;
        }
        if (!canRename) {
            setCommentAt(a, CodeUnit.REPEATABLE_COMMENT, mkDataComment(spec, "Rename skipped because existing name appears user-defined."));
            logData(spec, old, "skipped_existing_user_name", "existing_name_not_overwritten");
            return false;
        }

        try {
            if (primary == null) {
                createLabel(a, spec.name, true, SourceType.USER_DEFINED);
            } else {
                primary.setName(spec.name, SourceType.USER_DEFINED);
            }
            setCommentAt(a, CodeUnit.REPEATABLE_COMMENT, mkDataComment(spec, "Labeled by conservative baseline script."));
            createBookmark(a, "i76", "data_label_v49: " + spec.name + " [" + spec.confidence + "]");
            logData(spec, old, "labeled", "ok");
            return true;
        } catch (Exception e) {
            setCommentAt(a, CodeUnit.REPEATABLE_COMMENT, mkDataComment(spec, "Label failed: " + e.getMessage()));
            logData(spec, old, "label_failed", sanitize(e.getMessage()));
            return false;
        }
    }

    private void applyCommentSpec(CommentSpec spec) throws Exception {
        Address a = addressFromString(spec.addr);
        if (a == null) {
            logComment(spec, "bad_address", "could_not_parse_address");
            return;
        }
        int type = CodeUnit.REPEATABLE_COMMENT;
        if ("plate".equals(spec.kind)) type = CodeUnit.PLATE_COMMENT;
        if ("pre".equals(spec.kind)) type = CodeUnit.PRE_COMMENT;
        if ("post".equals(spec.kind)) type = CodeUnit.POST_COMMENT;
        setCommentAt(a, type, "[i76 " + spec.module + "]\n" + spec.text);
        createBookmark(a, "i76", "comment_v49: " + spec.module);
        logComment(spec, "commented", "ok");
    }

    private void setFunctionComment(Function f, String text) {
        try {
            f.setComment(text);
        } catch (Exception e) {
            // If function comment fails, try code-unit repeatable comment at entry.
            setCommentAt(f.getEntryPoint(), CodeUnit.REPEATABLE_COMMENT, text);
        }
    }

    private void setCommentAt(Address a, int type, String text) {
        try {
            Listing listing = currentProgram.getListing();
            CodeUnit cu = listing.getCodeUnitAt(a);
            if (cu == null) cu = listing.getCodeUnitContaining(a);
            if (cu != null) cu.setComment(type, text);
        } catch (Exception e) {
            // Conservative: comments are best-effort; logging happens at caller.
        }
    }

    private String mkFnComment(FnSpec spec, String note) {
        return "[i76 level/static/material baseline v48]\n" +
            "name: " + spec.name + "\n" +
            "confidence: " + spec.confidence + "\n" +
            "module: " + spec.module + "\n" +
            spec.comment + "\n" +
            "note: " + note;
    }

    private String mkDataComment(DataSpec spec, String note) {
        return "[i76 level/static/material baseline v48]\n" +
            "label: " + spec.name + "\n" +
            "confidence: " + spec.confidence + "\n" +
            "module: " + spec.module + "\n" +
            spec.comment + "\n" +
            "note: " + note;
    }

    private boolean isSafeFunctionNameToOverwrite(String old) {
        if (old == null) return true;
        String s = old.toLowerCase();
        return s.startsWith("fun_") || s.startsWith("function_") ||
               s.startsWith("sub_") || s.startsWith("undefined") ||
               s.startsWith("thunk_fun_") || s.startsWith("cgpt_todo_") ||
               s.startsWith("maybe_") || s.startsWith("unknown_") ||
               s.startsWith("i76_todo_");
    }

    private boolean isSafeDataNameToOverwrite(String old) {
        if (old == null || old.length() == 0) return true;
        String s = old.toLowerCase();
        return s.startsWith("dat_") || s.startsWith("byte_") ||
               s.startsWith("word_") || s.startsWith("dword_") ||
               s.startsWith("qword_") || s.startsWith("float_") ||
               s.startsWith("undefined") || s.startsWith("ptr_") ||
               s.startsWith("cgpt_todo_") || s.startsWith("maybe_") ||
               s.startsWith("unknown_") || s.startsWith("i76_todo_");
    }

    private void logFn(FnSpec spec, String old, String action, String note) throws IOException {
        fnLog.write(spec.addr + "\t" + spec.name + "\t" + sanitize(old) + "\t" + action + "\t" +
            spec.confidence + "\t" + spec.module + "\t" + sanitize(note) + "\n");
    }

    private void logData(DataSpec spec, String old, String action, String note) throws IOException {
        dataLog.write(spec.addr + "\t" + spec.name + "\t" + sanitize(old) + "\t" + action + "\t" +
            spec.confidence + "\t" + spec.module + "\t" + sanitize(note) + "\n");
    }

    private void logComment(CommentSpec spec, String action, String note) throws IOException {
        commentLog.write(spec.addr + "\t" + spec.kind + "\t" + action + "\t" + spec.module + "\t" + sanitize(note) + "\n");
    }

    private String sanitize(String s) {
        if (s == null) return "";
        return s.replace('\t', ' ').replace('\n', ' ').replace('\r', ' ');
    }

    private void writeManifest(String ts, int fnApplied, int fnSkipped, int dataApplied, int dataSkipped, int commentsApplied, boolean commit) throws IOException {
        manifest.write("{\n");
        manifest.write("  \"script\": \"cgpt_i76exe_apply_level_static_material_terrain_renames_v49.java\",\n");
        manifest.write("  \"timestamp\": \"" + ts + "\",\n");
        manifest.write("  \"program\": \"" + sanitize(currentProgram.getName()) + "\",\n");
        manifest.write("  \"transaction_committed\": " + (commit ? "true" : "false") + ",\n");
        manifest.write("  \"function_specs\": " + FUNCTIONS.length + ",\n");
        manifest.write("  \"function_renames_applied\": " + fnApplied + ",\n");
        manifest.write("  \"function_renames_skipped\": " + fnSkipped + ",\n");
        manifest.write("  \"data_specs\": " + DATA_LABELS.length + ",\n");
        manifest.write("  \"data_labels_applied\": " + dataApplied + ",\n");
        manifest.write("  \"data_labels_skipped\": " + dataSkipped + ",\n");
        manifest.write("  \"comments_applied\": " + commentsApplied + ",\n");
        manifest.write("  \"notes\": [\n");
        manifest.write("    \"v48 captures reconstruction/exporter findings through v47.\",\n");
        manifest.write("    \"Road placement is good, but road material/type/UV selection remains unresolved and should be traced in game/editor binaries.\",\n");
        manifest.write("    \"Terrain UV baseline: world-repeat repeat=1.0. Static GEO UV V-flip required.\",\n");
        manifest.write("    \"M06 static material baseline: VQM-first with I2D/AT family overrides and black-key alpha for cutouts.\"\n");
        manifest.write("  ]\n");
        manifest.write("}\n");
    }

    private void closeQuiet(BufferedWriter bw) {
        if (bw == null) return;
        try { bw.flush(); bw.close(); } catch (Exception e) { }
    }

    private void createTarArchive(File folder) {
        try {
            File parent = folder.getParentFile();
            String name = folder.getName();
            ProcessBuilder pb = new ProcessBuilder("tar", "-cf", name + ".tar", name);
            pb.directory(parent);
            Process p = pb.start();
            int rc = p.waitFor();
            if (rc != 0) println("warning: tar exited with status " + rc);
        } catch (Exception e) {
            println("warning: could not create tar archive: " + e.getMessage());
        }
    }
}
