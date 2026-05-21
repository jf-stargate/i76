// @category i76
// Export focused evidence for ODEF/OBJ class case bodies and resource suffix decisions.
// v42: created after v13 inventory showed VCF matches are class-specific.

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.mem.*;
import ghidra.util.exception.CancelledException;

import java.io.*;
import java.text.SimpleDateFormat;
import java.util.*;

public class cgpt_i76exe_export_odef_class_case_truth_v42_fixed extends GhidraScript {
    private static final String DEFAULT_ROOT = "/media/neon-remote/prj/i76/scratch_data";
    private File outDir;

    private static class Target {
        String label;
        String addr;
        int before;
        int after;
        Target(String label, String addr, int before, int after) {
            this.label = label; this.addr = addr; this.before = before; this.after = after;
        }
    }

    private Address A(String s) {
        try {
            return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(s);
        } catch (Exception e) {
            return null;
        }
    }

    private String esc(String s) {
        if (s == null) return "";
        return s.replace("\\", "\\\\").replace("\t", "\\t").replace("\r", "\\r").replace("\n", "\\n");
    }

    private String sym(Address a) {
        if (a == null) return "";
        Symbol s = getSymbolAt(a);
        if (s != null) return s.getName(true);
        Function f = getFunctionAt(a);
        if (f != null) return f.getName(true);
        return "";
    }

    private String bytesHex(Instruction ins) {
        try {
            byte[] b = ins.getBytes();
            StringBuilder sb = new StringBuilder();
            for (int i=0;i<b.length;i++) sb.append(String.format("%02x", b[i] & 0xff));
            return sb.toString();
        } catch (Exception e) {
            return "";
        }
    }

    private String refsFrom(Address a) {
        try {
            Reference[] rr = currentProgram.getReferenceManager().getReferencesFrom(a);
            StringBuilder sb = new StringBuilder();
            for (Reference r: rr) {
                if (sb.length() > 0) sb.append(";");
                Address to = r.getToAddress();
                sb.append(r.getReferenceType().toString()).append(":").append(to).append(":").append(esc(sym(to)));
            }
            return sb.toString();
        } catch (Exception e) {
            return "";
        }
    }

    private String scalarOps(Instruction ins) {
        StringBuilder sb = new StringBuilder();
        try {
            for (int i=0;i<ins.getNumOperands();i++) {
                Object[] objs = ins.getOpObjects(i);
                for (Object o: objs) {
                    if (o instanceof Scalar) {
                        if (sb.length() > 0) sb.append(";");
                        Scalar sc=(Scalar)o;
                        sb.append("op").append(i).append("=0x").append(Long.toHexString(sc.getUnsignedValue()));
                    }
                }
            }
        } catch (Exception e) {
        }
        return sb.toString();
    }

    private void writeInstructionWindow(PrintWriter pw, String label, Address center, int before, int after) {
        Listing listing = currentProgram.getListing();
        Instruction ci = listing.getInstructionAt(center);
        if (ci == null) {
            ci = listing.getInstructionContaining(center);
        }
        if (ci == null) {
            pw.println(label+"\t"+center+"\tNO_INSTRUCTION\t\t\t\t\t\t");
            return;
        }
        Instruction start = ci;
        for (int i=0;i<before;i++) {
            Instruction p = start.getPrevious();
            if (p == null) break;
            Function f0 = getFunctionContaining(ci.getAddress());
            Function f1 = getFunctionContaining(p.getAddress());
            if (f0 != null && f1 != null && !f0.equals(f1)) break;
            start = p;
        }
        Instruction ins = start;
        int count = before + after + 1;
        for (int i=0; ins != null && i<count; i++, ins=ins.getNext()) {
            Function f0 = getFunctionContaining(ci.getAddress());
            Function f1 = getFunctionContaining(ins.getAddress());
            if (f0 != null && f1 != null && !f0.equals(f1)) break;
            pw.println(label+"\t"+ins.getAddress()+"\t"+esc(sym(ins.getAddress()))+"\t"+
                esc(ins.getMnemonicString())+"\t"+esc(ins.toString())+"\t"+
                bytesHex(ins)+"\t"+esc(refsFrom(ins.getAddress()))+"\t"+esc(scalarOps(ins)));
        }
    }

    private void writeFunctionSummary(PrintWriter pw, String label, String addrStr) {
        Address a=A(addrStr);
        Function f = a == null ? null : getFunctionAt(a);
        if (f == null && a != null) f = getFunctionContaining(a);
        if (f == null) {
            pw.println(label+"\t"+addrStr+"\t\t\t\tMISSING");
            return;
        }
        pw.println(label+"\t"+f.getEntryPoint()+"\t"+esc(f.getName(true))+"\t"+f.getBody().getNumAddresses()+"\t"+esc(f.getSignature().toString())+"\tOK");
    }

    private void writeStringRefs(PrintWriter pw, String needle) {
        Memory mem = currentProgram.getMemory();
        Listing listing = currentProgram.getListing();
        ReferenceManager rm = currentProgram.getReferenceManager();
        byte[] pat = (needle + "\0").getBytes();
        AddressSetView set = mem.getLoadedAndInitializedAddressSet();
        Address cur = set.getMinAddress();
        while (cur != null) {
            try {
                Address found = mem.findBytes(cur, set.getMaxAddress(), pat, null, true, monitor);
                if (found == null) break;
                ReferenceIterator it = rm.getReferencesTo(found);
                boolean any=false;
                while (it.hasNext()) {
                    Reference r = it.next();
                    any=true;
                    Address from = r.getFromAddress();
                    Function f = getFunctionContaining(from);
                    pw.println(esc(needle)+"\t"+found+"\t"+from+"\t"+(f==null?"":f.getEntryPoint())+"\t"+(f==null?"":esc(f.getName(true)))+"\t"+esc(refsFrom(from)));
                }
                if (!any) pw.println(esc(needle)+"\t"+found+"\t\t\t\t");
                cur = found.add(1);
            } catch (CancelledException ce) {
                break;
            } catch (Exception e) {
                break;
            }
        }
    }

    private void writeDataDwords(PrintWriter pw, String label, String addrStr, int count) {
        Address a=A(addrStr);
        if (a == null) return;
        Memory mem = currentProgram.getMemory();
        for (int i=0;i<count;i++) {
            Address ea = a.add(i*4);
            try {
                int v = mem.getInt(ea);
                Address ptr = A(String.format("%08x", v));
                String ps = "";
                if (ptr != null && mem.contains(ptr)) ps = sym(ptr);
                pw.println(label+"\t"+i+"\t"+ea+"\t0x"+String.format("%08x", v)+"\t"+esc(ps));
            } catch (Exception e) {
                pw.println(label+"\t"+i+"\t"+ea+"\t\tERR");
            }
        }
    }

    private void setupOutDir() throws Exception {
        String root = askString("Output root", "Output root", DEFAULT_ROOT);
        if (root == null || root.trim().length() == 0) root = DEFAULT_ROOT;
        File rootDir = new File(root.trim());
        String ts = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
        outDir = new File(rootDir, "i76_odef_class_case_truth_v42_" + ts);
        outDir.mkdirs();
    }

    private void tarOutput() {
        try {
            File tar = new File(outDir.getParentFile(), outDir.getName()+".tar");
            ProcessBuilder pb = new ProcessBuilder("tar", "-cf", tar.getAbsolutePath(), "-C", outDir.getParentFile().getAbsolutePath(), outDir.getName());
            pb.redirectErrorStream(true);
            Process p = pb.start();
            p.waitFor();
        } catch (Exception e) {
            println("tar creation failed: " + e);
        }
    }

    @Override
    protected void run() throws Exception {
        setupOutDir();

        Target[] windows = new Target[] {
            new Target("odef_handler_entry_004b7ac0", "004b7ac0", 0, 80),
            new Target("odef_initial_basename_check_004b7adb", "004b7adb", 18, 42),
            new Target("odef_class_dispatch_004b7b70", "004b7b70", 20, 70),
            new Target("odef_case0_004b7b96", "004b7b96", 20, 95),
            new Target("odef_case1_004b7be9", "004b7be9", 35, 120),
            new Target("odef_case5_004b7c80", "004b7c80", 35, 100),
            new Target("odef_case6_004b7cb0", "004b7cb0", 35, 100),
            new Target("odef_case7_004b7cef", "004b7cef", 35, 100),
            new Target("format_label_optional_suffix_004ad640", "004ad640", 0, 100),
            new Target("load_vehicle_config_for_world_object_004ad6f0", "004ad6f0", 0, 140),
            new Target("parse_scene_object_descriptor_resource_004b7ea0", "004b7ea0", 0, 120),
            new Target("ldef_obj_handler_004b8f70", "004b8f70", 0, 130),
            new Target("sobj_geo_loader_004b8470", "004b8470", 0, 100)
        };

        try (PrintWriter pw = new PrintWriter(new File(outDir, "function_summary.tsv"))) {
            pw.println("label\tentry\tsymbol\tbody_addrs\tsignature\tstatus");
            String[][] funcs = {
                {"ODEF_OBJ_handler","004b7ac0"},
                {"format_label_optional_suffix","004ad640"},
                {"load_vehicle_config_for_world_object","004ad6f0"},
                {"parse_scene_object_descriptor_resource","004b7ea0"},
                {"LDEF_OBJ_handler","004b8f70"},
                {"SOBJ_geo_loader","004b8470"},
                {"build_transform_from_ODEF_record","004b8230"}
            };
            for (String[] f: funcs) writeFunctionSummary(pw, f[0], f[1]);
        }

        try (PrintWriter pw = new PrintWriter(new File(outDir, "odef_case_instruction_windows.tsv"))) {
            pw.println("window\taddress\tsymbol\tmnemonic\tinstruction\tbytes\trefs_from\tscalars");
            for (Target t: windows) writeInstructionWindow(pw, t.label, A(t.addr), t.before, t.after);
        }

        try (PrintWriter pw = new PrintWriter(new File(outDir, "resource_suffix_string_refs.tsv"))) {
            pw.println("needle\tstring_address\tfrom_address\tfrom_function\tfrom_function_name\tfrom_refs");
            String[] needles = {".vcf",".sdf",".geo","spawn","regen","Object found with no geometry"};
            for (String n: needles) writeStringRefs(pw, n);
        }

        try (PrintWriter pw = new PrintWriter(new File(outDir, "odef_dispatch_tables.tsv"))) {
            pw.println("table\tindex\taddress\tvalue\tsymbol_or_note");
            writeDataDwords(pw, "odef_jump_table_004b7e24", "004b7e24", 8);
            Address map=A("004b7e44");
            Memory mem=currentProgram.getMemory();
            if (map != null) {
                for (int cls=1; cls<=0x53; cls++) {
                    Address ea=map.add(cls-1);
                    int v=-1;
                    try { v = mem.getByte(ea) & 0xff; } catch (Exception e) {}
                    pw.println("odef_class_map_004b7e44\t0x"+String.format("%02x", cls)+"\t"+ea+"\t"+v+"\tcase_index");
                }
            }
        }

        try (PrintWriter pw = new PrintWriter(new File(outDir, "manifest.json"))) {
            pw.println("{");
            pw.println("  \"format\": \"i76_odef_class_case_truth\",");
            pw.println("  \"version\": 42,");
            pw.println("  \"purpose\": \"Validate whether ODEF resource suffix behavior is class-specific after VCF inventory evidence\",");
            pw.println("  \"outputs\": [\"function_summary.tsv\", \"odef_case_instruction_windows.tsv\", \"resource_suffix_string_refs.tsv\", \"odef_dispatch_tables.tsv\"]");
            pw.println("}");
        }

        tarOutput();
        println("Wrote " + outDir.getAbsolutePath());
    }
}
