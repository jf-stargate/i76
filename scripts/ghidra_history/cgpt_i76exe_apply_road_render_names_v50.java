// Interstate '76 road renderer / affine helper naming pass (v50).
// Based on static disassembly of i76.exe SHA256:
// bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3
// Follows jf-stargate/i76 v49 baseline: preserve existing user names.
// Does NOT rebuild function bodies or overwrite non-default function symbols.
//@category i76

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;

public class cgpt_i76exe_apply_road_render_names_v50 extends GhidraScript {
    private static final String MARK = "[i76-road-v50] ";

    private static final String[][] FNS = {
      // address, proposed name, confidence, observed behavior
      {"00494be0", "transform_point_affine_f32_to_f64", "high",
       "Uses float3 point in ECX and 3x3 float basis + double3 translation at EDX+0x28/0x30/0x38; writes three doubles to output stack argument."},
      {"00494da0", "transform_point_array_affine_f32", "high",
       "Transforms count float3 points: input, count, 0x40-byte affine matrix, output; 3x3 float basis and double3 translation."},
      {"00494e20", "compose_affine_transform_m3f_t3d", "high",
       "Composes two transforms using three float3 basis vectors and a double3 translation; returns destination transform pointer."},
      {"00494ef0", "transform_plane_equation_affine", "medium_high",
       "Forms rotated plane normal from float3 input and transform basis; fourth component combines plane offset with translation dot product."},
      {"00471f00", "select_texture_handle_for_render_mode", "high",
       "Returns first 32-bit resource handle unless second is present AND context+0x3c->+0x08 equals 1, then returns second."},
      {"00490590", "begin_render_primitive_pool_record", "medium_high",
       "Obtains active primitive record pointer from 006543c0, stores it at 0065439c, clears record count and link state."},
      {"004905c0", "advance_render_primitive_pool_cursor", "high",
       "Advances 006543c0 by 0x1c plus type/shape size from table 004face0, indexed by record +0x0c."},
      {"0048f4c0", "dispatch_geo_render_pass_by_component_state", "medium",
       "Passes object+0x1c to 0045d100 if component +0x1c nonzero, else 0045d530."},
      {"0048f500", "dispatch_geo_render_pass_with_fallback", "medium_high",
       "Passes object+0x1c to 0045d100 if +0x1c nonzero; otherwise 0045d530 if +0x24 nonzero; else 0045c850."}
    };
    private static final String[][] DATAS = {
      {"004fa928", "rseg_road_texture_filename_ptrs_30", "30 pointers to lower-case .map filenames; first 10 r2anr, next 10 r2ayr, then 5 r2dnr and 5 r2wnr."},
      {"004fa9a0", "rseg_road_kind_mod3_texture_index_map", "Three groups of 20 DWORD indices. Group selected via signed RSEG runtime kind % 3 at 0048ea18-0048ea50."},
      {"0059c1c0", "g_rseg_road_texture_name_slots_16x30", "30 fixed 16-byte texture-name slots copied from 004fa928 at 0048e1b9-0048e1ee."},
      {"0059c3a0", "g_rseg_road_texture_handles_30x8", "30 pairs of 32-bit texture handles; lookup table selected at 0048ec4b."},
      {"0059c490", "g_rseg_road_textures_ready", "Cleared at 0048e1af and 0048e6c2; set to 1 at 0048e6b0; renderer tests at 0048e900."},
      {"005dd320", "g_runtime_render_vertex_xyz_buffer", "float3 render vertex buffer used by 0048e900 and transform array helper; precise coordinate frame needs verification."}
    };
    private static final String[][] ANCHORS = {
      {"0048e1a0", "Retain established name load_road_textures. Copies 30 names, creates texture handle pairs, sets readiness at 0059c490."},
      {"0048e900", "Retain established name render_rseg_road_polygon_strip_pass. Reads runtime RSEG head and kind at node +0x10; selects material using kind % 3 and 20-index tables."},
      {"004b8780", "Retain established name load_rseg_route_corridor_records. Serialized kind at source +0x08 is copied to runtime RSEG node +0x10 at 004b881c/004b8827."},
      {"004b8970", "Retain established name getter of runtime RSEG list head at 005db988."}
    };

    private Address at(String addr) { return toAddr(addr); }
    private void addFnNote(Function fn, String detail) {
        String old = fn.getComment();
        if (old == null) old = "";
        String updated = MARK + detail;
        if (!old.contains(updated)) fn.setComment(old.isEmpty() ? updated : old + "\n" + updated);
    }
    private void addDataNote(Address addr, String detail) {
        CodeUnit cu = currentProgram.getListing().getCodeUnitAt(addr);
        if (cu == null) return;
        String old = cu.getComment(CodeUnit.REPEATABLE_COMMENT);
        if (old == null) old = "";
        String updated = MARK + detail;
        if (!old.contains(updated)) cu.setComment(CodeUnit.REPEATABLE_COMMENT, old.isEmpty() ? updated : old + "\n" + updated);
    }
    private void verify() throws Exception {
        if (currentProgram.getImageBase().getOffset() != 0x400000L)
            throw new IllegalStateException("Unexpected image base; expected 0x00400000");
        String[][] signatures = {{"0048e1a0", "55"}, {"0048e900", "a1"},
                                {"004b8780", "8b"}, {"00494da0", "55"}};
        for (String[] p : signatures) {
            int actual = currentProgram.getMemory().getByte(at(p[0])) & 0xff;
            int expected = Integer.parseInt(p[1], 16);
            if (actual != expected)
                throw new IllegalStateException("Wrong executable bytes at " + p[0]);
        }
    }
    @Override public void run() throws Exception {
        verify();
        int renamed = 0, retained = 0, missing = 0;
        for (String[] row : FNS) {
            if (monitor.isCancelled()) break;
            Address addr = at(row[0]);
            Function fn = getFunctionAt(addr);  // Never name a containing-but-different function.
            if (fn == null) { println("MISSING FUNCTION " + row[0]); missing++; continue; }
            String old = fn.getName();
            if (old.startsWith("FUN_") || old.startsWith("SUB_") || old.startsWith("sub_")) {
                fn.setName(row[1], SourceType.USER_DEFINED);
                renamed++;
                println("RENAMED " + row[0] + " " + old + " -> " + row[1]);
            } else {
                retained++;
                println("PRESERVED " + row[0] + " existing=" + old + " proposed=" + row[1]);
            }
            addFnNote(fn, "Proposed=" + row[1] + "; confidence=" + row[2] + "; " + row[3]);
        }
        for (String[] row : DATAS) {
            if (monitor.isCancelled()) break;
            Address addr = at(row[0]);
            try {
                if (!currentProgram.getMemory().contains(addr)) {
                    println("UNMAPPED DATA " + row[0] + " " + row[1]);
                    continue;
                }
                Symbol s = currentProgram.getSymbolTable().getPrimarySymbol(addr);
                if (s == null) {
                    createLabel(addr, row[1], true, SourceType.USER_DEFINED);
                } else if (s.getSource() != SourceType.USER_DEFINED &&
                           (s.getName().startsWith("DAT_") || s.getName().startsWith("PTR_") || s.getName().startsWith("UNK_"))) {
                    s.setName(row[1], SourceType.USER_DEFINED);
                } else {
                    println("PRESERVED DATA " + row[0] + " " + s.getName());
                }
                addDataNote(addr, row[2]);
            } catch (Exception ex) {
                println("SKIPPED DATA " + row[0] + ": " + ex.getMessage());
            }
        }
        for (String[] anchor : ANCHORS) {
            Function fn = getFunctionAt(at(anchor[0]));
            if (fn != null) addFnNote(fn, anchor[1]);
        }
        println("v50 complete: renamed=" + renamed + " preserved=" + retained + " missing=" + missing);
    }
}
