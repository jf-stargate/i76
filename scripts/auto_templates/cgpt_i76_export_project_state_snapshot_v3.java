// Durable Ghidra project state snapshot exporter.
//@category i76

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.data.CategoryPath;
import ghidra.program.model.data.DataType;
import ghidra.program.model.data.DataTypeComponent;
import ghidra.program.model.data.DataTypeManager;
import ghidra.program.model.data.Structure;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.symbol.SymbolTable;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.HashMap;
import java.util.HashSet;
import java.util.TreeSet;
import java.util.Map;

public class cgpt_i76_export_project_state_snapshot_v3 extends GhidraScript {
    private static final String DEFAULT_ROOT = "/media/neon-remote/prj/i76/scratch_data";

    // Keep this target-neutral. It can be run against i76.exe, i76shell.dll, or other binaries.
    // For very large projects, leave decompile/disassembly on semantic functions only.
    private static final boolean EXPORT_DECOMPILE = true;
    private static final boolean EXPORT_DISASSEMBLY = true;
    private static final boolean DECOMPILE_ALL_FUNCTIONS = false;
    private static final boolean DISASSEMBLE_ALL_FUNCTIONS = false;
    private static final int MAX_DECOMPILE_FUNCTIONS = 2500;
    private static final int MAX_DISASSEMBLY_FUNCTIONS = 2500;
    private static final int MAX_INSTRUCTIONS_PER_FUNCTION = 50000;
    private static final int MAX_VALUE_PREVIEW = 160;

    private static class FunctionRow {
        Function fn;
        String name;
        Address entry;
        FunctionRow(Function f) {
            fn = f;
            name = f.getName();
            entry = f.getEntryPoint();
        }
    }

    private File outDir;
    private File decompileDir;
    private File disasmDir;
    private long functionCount = 0;
    private long semanticFunctionCount = 0;
    private long symbolCount = 0;
    private long nonDefaultSymbolCount = 0;
    private long commentCount = 0;
    private long dataCount = 0;
    private long definedStringCount = 0;
    private long structureCount = 0;
    private long callEdgeCount = 0;

    private File chooseOutputRoot() throws Exception {
        try {
            File chosen = askDirectory("Choose snapshot output root directory", "Use this directory");
            if (chosen != null) return chosen;
        } catch (Exception ex) {
            // In headless or canceled contexts, fall through to default.
        }
        return new File(DEFAULT_ROOT);
    }

    private void ensureDir(File f) throws Exception {
        if (!f.exists() && !f.mkdirs()) {
            throw new Exception("could not create directory: " + f.getAbsolutePath());
        }
    }

    private String clean(String s) {
        if (s == null) return "";
        return s.replace("\t", " ").replace("\n", " ").replace("\r", " ");
    }

    private String md(String s) {
        if (s == null) return "";
        return s.replace("\\", "\\\\").replace("`", "'").replace("|", "\\|").replace("\r", " ").replace("\n", "<br>");
    }

    private String json(String s) {
        if (s == null) return "";
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '\\') sb.append("\\\\");
            else if (c == '"') sb.append("\\\"");
            else if (c == '\n') sb.append("\\n");
            else if (c == '\r') sb.append("\\r");
            else if (c == '\t') sb.append("\\t");
            else if (c < 32) sb.append(" ");
            else sb.append(c);
        }
        return sb.toString();
    }

    private String safeFileName(String s) {
        if (s == null || s.length() == 0) return "unnamed";
        return s.replaceAll("[^A-Za-z0-9._+-]+", "_");
    }

    private String addrText(Address a) {
        return a == null ? "" : a.toString();
    }

    private String functionsReferencingAddress(Address a) throws Exception {
        if (a == null) return "";
        TreeSet<String> names = new TreeSet<String>();
        ReferenceIterator refs = currentProgram.getReferenceManager().getReferencesTo(a);
        while (refs.hasNext()) {
            monitor.checkCancelled();
            Reference r = refs.next();
            if (r == null || r.getFromAddress() == null) continue;
            Function f = currentProgram.getListing().getFunctionContaining(r.getFromAddress());
            if (f != null) {
                names.add(f.getName() + "@" + addrText(f.getEntryPoint()));
            }
        }
        StringBuilder sb = new StringBuilder();
        for (String n : names) {
            if (sb.length() > 0) sb.append(" | ");
            sb.append(n);
        }
        return sb.toString();
    }

    private String rangeText(AddressSetView body) {
        if (body == null || body.isEmpty()) return "";
        return body.getMinAddress().toString() + "-" + body.getMaxAddress().toString();
    }

    private boolean isDefaultishName(String name) {
        if (name == null) return true;
        return name.startsWith("FUN_") || name.startsWith("SUB_") ||
               name.startsWith("DAT_") || name.startsWith("LAB_") ||
               name.startsWith("UNK_") || name.startsWith("EXT_") ||
               name.startsWith("s_") || name.startsWith("u_");
    }

    private boolean isSemanticFunction(Function fn) {
        if (fn == null) return false;
        SourceType st = fn.getSymbol().getSource();
        if (st == SourceType.USER_DEFINED || st == SourceType.IMPORTED || st == SourceType.ANALYSIS) {
            if (!isDefaultishName(fn.getName())) return true;
        }
        return !isDefaultishName(fn.getName());
    }

    private String bytesString(Instruction ins) {
        try {
            byte[] bs = ins.getBytes();
            StringBuilder sb = new StringBuilder();
            for (int i = 0; bs != null && i < bs.length; i++) {
                if (i > 0) sb.append(" ");
                int v = bs[i] & 0xff;
                if (v < 0x10) sb.append("0");
                sb.append(Integer.toHexString(v));
            }
            return sb.toString();
        } catch (Exception ex) {
            return "";
        }
    }

    private String operandsString(Instruction ins) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < ins.getNumOperands(); i++) {
            if (i > 0) sb.append(", ");
            sb.append(ins.getDefaultOperandRepresentation(i));
        }
        return sb.toString();
    }

    private boolean containsLower(String haystack, String needle) {
        if (haystack == null || needle == null) return false;
        return haystack.toLowerCase().indexOf(needle.toLowerCase()) >= 0;
    }

    private void scoreModule(Map<String, Integer> scores, Map<String, String> evidence, String module, int points, String why) {
        Integer old = scores.get(module);
        scores.put(module, old == null ? points : old.intValue() + points);
        String prev = evidence.get(module);
        if (prev == null || prev.length() == 0) evidence.put(module, why);
        else if (prev.length() < 300 && prev.indexOf(why) < 0) evidence.put(module, prev + "; " + why);
    }

    private String stringValueAt(Address a) {
        if (a == null) return "";
        try {
            Data d = currentProgram.getListing().getDataAt(a);
            if (d == null) return "";
            Object v = d.getValue();
            if (v instanceof String) return (String)v;
        } catch (Exception ex) {
        }
        return "";
    }

    private String moduleGuess(Function fn) {
        return moduleGuessAndEvidence(fn)[0];
    }

    private String moduleEvidence(Function fn) {
        return moduleGuessAndEvidence(fn)[1];
    }

    private String[] moduleGuessAndEvidence(Function fn) {
        Map<String, Integer> scores = new HashMap<String, Integer>();
        Map<String, String> evidence = new HashMap<String, String>();

        StringBuilder corpus = new StringBuilder();
        try { corpus.append(fn.getName()).append(" "); } catch (Exception ex) {}
        try { corpus.append(fn.getSignature().toString()).append(" "); } catch (Exception ex) {}
        try { corpus.append(fn.getComment()).append(" "); } catch (Exception ex) {}
        try { corpus.append(fn.getRepeatableComment()).append(" "); } catch (Exception ex) {}

        int insnCount = 0;
        try {
            AddressSetView body = fn.getBody();
            Instruction ins = getInstructionAt(fn.getEntryPoint());
            while (ins != null && body.contains(ins.getAddress()) && insnCount < 600) {
                String line = ins.toString();
                corpus.append(line).append(" ");
                Reference[] rr = ins.getReferencesFrom();
                if (rr != null) {
                    for (int i = 0; i < rr.length; i++) {
                        Address to = rr[i].getToAddress();
                        Function tf = getFunctionContaining(to);
                        if (tf != null) corpus.append(tf.getName()).append(" ");
                        Symbol ts = null;
                        try { ts = currentProgram.getSymbolTable().getPrimarySymbol(to); } catch (Exception ex) { ts = null; }
                        if (ts != null) corpus.append(ts.getName()).append(" ");
                        String sv = stringValueAt(to);
                        if (sv.length() > 0) corpus.append(sv).append(" ");
                    }
                }
                ins = ins.getNext();
                insnCount++;
            }
        } catch (Exception ex) {
        }

        String c = corpus.toString().toLowerCase();

        if (containsLower(c, "terrain") || containsLower(c, "zmap") || containsLower(c, "tdef") || containsLower(c, ".ter") ||
            containsLower(c, "005a4628") || containsLower(c, "00644380") || containsLower(c, "height_low12")) {
            scoreModule(scores, evidence, "terrain_runtime", 80, "terrain/ZMAP/TDEF/TER/page-grid evidence");
        }
        if (containsLower(c, "wdef") || containsLower(c, "mission") || containsLower(c, ".msn") || containsLower(c, ".spc") ||
            containsLower(c, "load_and_parse_selected_mission") || containsLower(c, "bwd2")) {
            scoreModule(scores, evidence, "mission_level_runtime", 70, "mission/BWD2/WDEF/MSN evidence");
        }
        if (containsLower(c, "zfs") || containsLower(c, "zix") || containsLower(c, "lzo") || containsLower(c, "archive") ||
            containsLower(c, "record_payload")) {
            scoreModule(scores, evidence, "zfs_resource_archive", 80, "ZFS/ZIX/LZO/archive evidence");
        }
        if (containsLower(c, "vehicle") || containsLower(c, ".vcf") || containsLower(c, ".vdf") || containsLower(c, ".vtf") ||
            containsLower(c, ".wdf") || containsLower(c, "sobj") || containsLower(c, ".geo")) {
            scoreModule(scores, evidence, "vehicle_geometry_runtime", 70, "vehicle/VCF/VDF/WDF/GEO evidence");
        }
        if (containsLower(c, ".tmt") || containsLower(c, ".map") || containsLower(c, ".m16") || containsLower(c, ".vqm") ||
            containsLower(c, ".cbk") || containsLower(c, "texture") || containsLower(c, "palette")) {
            scoreModule(scores, evidence, "texture_material_runtime", 60, "texture/material/MAP/M16/VQM/CBK evidence");
        }
        if (containsLower(c, "directdraw") || containsLower(c, "ddraw") || containsLower(c, "d3d") || containsLower(c, "glide") ||
            containsLower(c, "zglide") || containsLower(c, "render") || containsLower(c, "raster") || containsLower(c, "polygon")) {
            scoreModule(scores, evidence, "render_display_runtime", 65, "DirectDraw/D3D/Glide/render/raster evidence");
        }
        if (containsLower(c, "directsound") || containsLower(c, ".wav") || containsLower(c, "sound") || containsLower(c, "audio")) {
            scoreModule(scores, evidence, "audio_runtime", 60, "DirectSound/WAV/audio evidence");
        }
        if (containsLower(c, "directplay") || containsLower(c, "network") || containsLower(c, "session") || containsLower(c, "modem") ||
            containsLower(c, "winsock")) {
            scoreModule(scores, evidence, "network_multiplayer_runtime", 60, "DirectPlay/network/session evidence");
        }
        if (containsLower(c, "shellmain") || containsLower(c, "i76shell") || containsLower(c, "callback") ||
            containsLower(c, "menu") || containsLower(c, "dialog")) {
            scoreModule(scores, evidence, "shell_ui_contract", 60, "shell/menu/dialog/callback evidence");
        }
        if (containsLower(c, "fopen") || containsLower(c, "fread") || containsLower(c, "fwrite") || containsLower(c, "createfile") ||
            containsLower(c, "readfile") || containsLower(c, "writefile")) {
            scoreModule(scores, evidence, "file_io_runtime", 40, "file API evidence");
        }
        if (containsLower(c, "malloc") || containsLower(c, "free") || containsLower(c, "heap") || containsLower(c, "alloc") ||
            containsLower(c, "cache")) {
            scoreModule(scores, evidence, "memory_cache_runtime", 35, "heap/alloc/cache evidence");
        }
        if (containsLower(c, "winmain") || containsLower(c, "windowproc") || containsLower(c, "wndproc") ||
            containsLower(c, "message") || containsLower(c, "registry") || containsLower(c, "command_line")) {
            scoreModule(scores, evidence, "platform_win32_runtime", 45, "WinMain/WindowProc/registry/command-line evidence");
        }

        String best = "unknown";
        int bestScore = 0;
        for (String k : scores.keySet()) {
            int v = scores.get(k).intValue();
            if (v > bestScore || (v == bestScore && k.compareTo(best) < 0)) {
                best = k;
                bestScore = v;
            }
        }

        if (bestScore == 0) return new String[] { "unknown", "" };
        return new String[] { best, "score=" + bestScore + "; " + evidence.get(best) };
    }

    private List<FunctionRow> collectFunctions() throws Exception {
        List<FunctionRow> rows = new ArrayList<FunctionRow>();
        FunctionIterator it = currentProgram.getListing().getFunctions(true);
        while (it.hasNext()) {
            Function fn = it.next();
            rows.add(new FunctionRow(fn));
            functionCount++;
            if (isSemanticFunction(fn)) semanticFunctionCount++;
            monitor.checkCancelled();
        }
        Collections.sort(rows, new Comparator<FunctionRow>() {
            public int compare(FunctionRow a, FunctionRow b) {
                return a.entry.compareTo(b.entry);
            }
        });
        return rows;
    }

    private void writeReadme(File out, List<FunctionRow> functions) throws Exception {
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "README.md"))));
        pw.println("# Ghidra Project State Snapshot");
        pw.println();
        pw.println("This folder is a durable human-readable and machine-readable export of the current Ghidra program state.");
        pw.println("It is intended for source control, code review, handoff, and offline reference without requiring Ghidra to be open.");
        pw.println();
        pw.println("## Program");
        pw.println();
        pw.println("| Field | Value |");
        pw.println("|---|---|");
        pw.println("| Program | `" + md(currentProgram.getName()) + "` |");
        pw.println("| Language | `" + md(currentProgram.getLanguageID().toString()) + "` |");
        pw.println("| Compiler spec | `" + md(currentProgram.getCompilerSpec().getCompilerSpecID().toString()) + "` |");
        pw.println("| Image base | `" + md(addrText(currentProgram.getImageBase())) + "` |");
        pw.println("| Min address | `" + md(addrText(currentProgram.getMinAddress())) + "` |");
        pw.println("| Max address | `" + md(addrText(currentProgram.getMaxAddress())) + "` |");
        pw.println("| Export time | `" + md(new Date().toString()) + "` |");
        pw.println();
        pw.println("## Contents");
        pw.println();
        pw.println("| File | Purpose |");
        pw.println("|---|---|");
        pw.println("| `manifest.json` | Machine-readable summary of this snapshot. |");
        pw.println("| `function_index.md` / `.tsv` | Function list, signatures, address ranges, comments, semantic-name status. |");
        pw.println("| `symbols.md` / `.tsv` | Symbols and labels, including source type and primary status. |");
        pw.println("| `comments.md` / `.tsv` | Plate, pre, EOL, post, and repeatable comments. |");
        pw.println("| `memory_blocks.tsv` | Program memory block map. |");
        pw.println("| `defined_data.tsv` | Defined data listing with type, size, symbol, and value preview. |");
        pw.println("| `defined_strings.md` / `.tsv` | All defined string data with category and referencing functions. |");
        pw.println("| `function_module_guesses.tsv` | Heuristic semantic module/source-file group guess per function. |");
        pw.println("| `data_types_structures.md` / `.tsv` | Structure definitions and field offsets. |");
        pw.println("| `callgraph.tsv` | Function call edges discovered from instruction references. |");
        pw.println("| `references_from_instructions.tsv` | Instruction-level outgoing references. |");
        pw.println("| `rename_inventory.tsv` | Semantic/default-name inventory for functions and symbols. |");
        pw.println("| `decompile/` | Decompiled C for exported functions. |");
        pw.println("| `disassembly/` | Instruction TSV per exported function. |");
        pw.println();
        pw.println("## Snapshot scale");
        pw.println();
        pw.println("| Metric | Count |");
        pw.println("|---|---:|");
        pw.println("| Functions | " + functions.size() + " |");
        pw.println("| Semantic functions | " + semanticFunctionCount + " |");
        pw.println("| Decompiled function cap | " + MAX_DECOMPILE_FUNCTIONS + " |");
        pw.println("| Disassembly function cap | " + MAX_DISASSEMBLY_FUNCTIONS + " |");
        pw.println("| Defined strings | " + definedStringCount + " |");
        pw.close();
    }

    private void writeManifest(File out) throws Exception {
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "manifest.json"))));
        pw.println("{");
        pw.println("  \"schema\": \"cgpt-ghidra-project-state-snapshot-v3\",");
        pw.println("  \"program_name\": \"" + json(currentProgram.getName()) + "\",");
        pw.println("  \"language\": \"" + json(currentProgram.getLanguageID().toString()) + "\",");
        pw.println("  \"compiler_spec\": \"" + json(currentProgram.getCompilerSpec().getCompilerSpecID().toString()) + "\",");
        pw.println("  \"image_base\": \"" + json(addrText(currentProgram.getImageBase())) + "\",");
        pw.println("  \"min_address\": \"" + json(addrText(currentProgram.getMinAddress())) + "\",");
        pw.println("  \"max_address\": \"" + json(addrText(currentProgram.getMaxAddress())) + "\",");
        pw.println("  \"export_time\": \"" + json(new Date().toString()) + "\",");
        pw.println("  \"counts\": {");
        pw.println("    \"functions\": " + functionCount + ",");
        pw.println("    \"semantic_functions\": " + semanticFunctionCount + ",");
        pw.println("    \"symbols\": " + symbolCount + ",");
        pw.println("    \"non_default_symbols\": " + nonDefaultSymbolCount + ",");
        pw.println("    \"comments\": " + commentCount + ",");
        pw.println("    \"defined_data\": " + dataCount + ",");
        pw.println("    \"defined_strings\": " + definedStringCount + ",");
        pw.println("    \"structures\": " + structureCount + ",");
        pw.println("    \"call_edges\": " + callEdgeCount);
        pw.println("  }");
        pw.println("}");
        pw.close();
    }

    private void writeFunctionIndex(File out, List<FunctionRow> functions) throws Exception {
        PrintWriter tsv = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "function_index.tsv"))));
        PrintWriter mdw = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "function_index.md"))));
        tsv.println("entry\tname\tmodule_guess\tmodule_evidence\tsignature\tbody_range\tbody_size\tparameter_count\tcalling_convention\treturn_type\tsource_type\tis_thunk\tthunk_target\tis_semantic\tcomment\trepeatable_comment");
        mdw.println("# Function Index");
        mdw.println();
        mdw.println("| Entry | Name | Module guess | Signature | Body | Source | Semantic | Comment |");
        mdw.println("|---|---|---|---|---|---|---|---|");
        for (FunctionRow row : functions) {
            Function fn = row.fn;
            String sig = "";
            String cc = "";
            String rt = "";
            try { sig = fn.getSignature().toString(); } catch (Exception ex) { sig = ""; }
            try { cc = fn.getCallingConventionName(); } catch (Exception ex) { cc = ""; }
            try { rt = fn.getReturnType().getDisplayName(); } catch (Exception ex) { rt = ""; }
            AddressSetView body = fn.getBody();
            String thunkTarget = "";
            try {
                Function th = fn.getThunkedFunction(false);
                if (th != null) thunkTarget = th.getEntryPoint().toString() + ":" + th.getName();
            } catch (Exception ex) { thunkTarget = ""; }
            boolean sem = isSemanticFunction(fn);
            String[] mod = moduleGuessAndEvidence(fn);
            String line = addrText(fn.getEntryPoint()) + "\t" + clean(fn.getName()) + "\t" + clean(mod[0]) + "\t" + clean(mod[1]) + "\t" + clean(sig) + "\t" +
                    clean(rangeText(body)) + "\t" + (body == null ? 0 : body.getNumAddresses()) + "\t" +
                    fn.getParameterCount() + "\t" + clean(cc) + "\t" + clean(rt) + "\t" +
                    clean(fn.getSymbol().getSource().toString()) + "\t" + fn.isThunk() + "\t" + clean(thunkTarget) + "\t" +
                    sem + "\t" + clean(fn.getComment()) + "\t" + clean(fn.getRepeatableComment());
            tsv.println(line);
            mdw.println("| `" + md(addrText(fn.getEntryPoint())) + "` | `" + md(fn.getName()) + "` | `" + md(mod[0]) + "` | `" + md(sig) + "` | `" + md(rangeText(body)) + "` | " + md(fn.getSymbol().getSource().toString()) + " | " + sem + " | " + md(fn.getComment()) + " |");
            monitor.checkCancelled();
        }
        tsv.close();
        mdw.close();
    }

    private void writeSymbols(File out) throws Exception {
        PrintWriter tsv = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "symbols.tsv"))));
        PrintWriter mdw = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "symbols.md"))));
        tsv.println("address\tname\ttype\tnamespace\tsource_type\tis_primary\tis_external\tis_defaultish\tobject_string");
        mdw.println("# Symbols");
        mdw.println();
        mdw.println("| Address | Name | Type | Namespace | Source | Primary | Default-ish |");
        mdw.println("|---|---|---|---|---|---|---|");
        SymbolTable st = currentProgram.getSymbolTable();
        SymbolIterator it = st.getAllSymbols(true);
        while (it.hasNext()) {
            Symbol s = it.next();
            symbolCount++;
            boolean def = isDefaultishName(s.getName());
            if (!def) nonDefaultSymbolCount++;
            String ns = "";
            try { ns = s.getParentNamespace() == null ? "" : s.getParentNamespace().getName(); } catch (Exception ex) { ns = ""; }
            String addr = s.getAddress() == null ? "" : s.getAddress().toString();
            String line = addr + "\t" + clean(s.getName()) + "\t" + clean(s.getSymbolType().toString()) + "\t" +
                    clean(ns) + "\t" + clean(s.getSource().toString()) + "\t" + s.isPrimary() + "\t" + s.isExternal() + "\t" + def + "\t" + clean(s.toString());
            tsv.println(line);
            if (!def || s.getSource() == SourceType.USER_DEFINED) {
                mdw.println("| `" + md(addr) + "` | `" + md(s.getName()) + "` | " + md(s.getSymbolType().toString()) + " | " + md(ns) + " | " + md(s.getSource().toString()) + " | " + s.isPrimary() + " | " + def + " |");
            }
            monitor.checkCancelled();
        }
        tsv.close();
        mdw.close();
    }

    private void writeComments(File out) throws Exception {
        PrintWriter tsv = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "comments.tsv"))));
        PrintWriter mdw = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "comments.md"))));
        tsv.println("address\tfunction_entry\tfunction_name\tcomment_type\tcomment");
        mdw.println("# Comments");
        mdw.println();
        mdw.println("| Address | Function | Type | Comment |");
        mdw.println("|---|---|---|---|");
        Listing listing = currentProgram.getListing();
        Iterator<CodeUnit> it = listing.getCodeUnits(true);
        int[] types = new int[] { CodeUnit.PLATE_COMMENT, CodeUnit.PRE_COMMENT, CodeUnit.EOL_COMMENT, CodeUnit.POST_COMMENT, CodeUnit.REPEATABLE_COMMENT };
        String[] names = new String[] { "plate", "pre", "eol", "post", "repeatable" };
        while (it.hasNext()) {
            CodeUnit cu = it.next();
            for (int i = 0; i < types.length; i++) {
                String c = cu.getComment(types[i]);
                if (c != null && c.length() > 0) {
                    Function fn = getFunctionContaining(cu.getAddress());
                    commentCount++;
                    tsv.println(addrText(cu.getAddress()) + "\t" + (fn == null ? "" : addrText(fn.getEntryPoint())) + "\t" + clean(fn == null ? "" : fn.getName()) + "\t" + names[i] + "\t" + clean(c));
                    mdw.println("| `" + md(addrText(cu.getAddress())) + "` | `" + md(fn == null ? "" : fn.getName()) + "` | " + names[i] + " | " + md(c) + " |");
                }
            }
            monitor.checkCancelled();
        }
        tsv.close();
        mdw.close();
    }

    private void writeMemoryBlocks(File out) throws Exception {
        PrintWriter tsv = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "memory_blocks.tsv"))));
        tsv.println("name\tstart\tend\tsize\tread\twrite\texecute\tinitialized\tvolatile\ttype\tsource");
        MemoryBlock[] blocks = currentProgram.getMemory().getBlocks();
        for (int i = 0; i < blocks.length; i++) {
            MemoryBlock b = blocks[i];
            tsv.println(clean(b.getName()) + "\t" + addrText(b.getStart()) + "\t" + addrText(b.getEnd()) + "\t" + b.getSize() + "\t" +
                    b.isRead() + "\t" + b.isWrite() + "\t" + b.isExecute() + "\t" + b.isInitialized() + "\t" + b.isVolatile() + "\t" +
                    clean(b.getType().toString()) + "\t" + clean(b.getSourceName()));
        }
        tsv.close();
    }


    private String stringCategory(String s) {
        if (s == null) return "empty";
        String lower = s.toLowerCase();
        if (lower.indexOf(".msn") >= 0 || lower.indexOf(".spc") >= 0 || lower.indexOf(".lvl") >= 0 || lower.indexOf(".ter") >= 0) return "mission_level";
        if (lower.indexOf(".zfs") >= 0 || lower.indexOf(".zix") >= 0 || lower.indexOf("lzo") >= 0) return "archive_resource";
        if (lower.indexOf(".vcf") >= 0 || lower.indexOf(".vdf") >= 0 || lower.indexOf(".vtf") >= 0 || lower.indexOf(".geo") >= 0 || lower.indexOf(".wdf") >= 0) return "vehicle_geometry";
        if (lower.indexOf(".map") >= 0 || lower.indexOf(".tmt") >= 0 || lower.indexOf(".m16") >= 0 || lower.indexOf(".vqm") >= 0 || lower.indexOf(".cbk") >= 0 || lower.indexOf(".act") >= 0) return "texture_material";
        if (lower.indexOf("glide") >= 0 || lower.indexOf("d3d") >= 0 || lower.indexOf("directdraw") >= 0 || lower.indexOf("hardware") >= 0 || lower.indexOf("software") >= 0) return "render_display";
        if (lower.indexOf(".wav") >= 0 || lower.indexOf("sound") >= 0 || lower.indexOf("audio") >= 0) return "audio";
        if (lower.indexOf("directplay") >= 0 || lower.indexOf("network") >= 0 || lower.indexOf("session") >= 0) return "network";
        if (lower.indexOf("%") >= 0) return "format_string";
        if (lower.indexOf("\\") >= 0 || lower.indexOf("/") >= 0) return "path_or_file";
        return "general";
    }

    private void writeDefinedStrings(File out) throws Exception {
        PrintWriter tsv = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "defined_strings.tsv"))));
        PrintWriter mdw = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "defined_strings.md"))));
        tsv.println("address\tsymbol\tdata_type\tlength\tcategory\tstring\treferences_to_count\treferencing_functions");
        mdw.println("# Defined Strings");
        mdw.println();
        mdw.println("| Address | Symbol | Category | String | Referencing functions |");
        mdw.println("|---|---|---|---|---|");
        Listing listing = currentProgram.getListing();
        Iterator<Data> it = listing.getDefinedData(true);
        while (it.hasNext()) {
            Data d = it.next();
            Object v = null;
            try { v = d.getValue(); } catch (Exception ex) { v = null; }
            if (!(v instanceof String)) continue;
            definedStringCount++;

            String sym = "";
            try {
                Symbol s = currentProgram.getSymbolTable().getPrimarySymbol(d.getAddress());
                if (s != null) sym = s.getName();
            } catch (Exception ex) { sym = ""; }

            String svalue = (String)v;
            String category = stringCategory(svalue);
            Reference[] rt = getReferencesTo(d.getAddress());
            String funcs = "";
            try { funcs = functionsReferencingAddress(d.getAddress()); } catch (Exception ex) { funcs = ""; }

            tsv.println(addrText(d.getAddress()) + "\t" + clean(sym) + "\t" + clean(d.getDataType().getDisplayName()) + "\t" +
                    d.getLength() + "\t" + clean(category) + "\t" + clean(svalue) + "\t" + (rt == null ? 0 : rt.length) + "\t" + clean(funcs));

            if ((rt != null && rt.length > 0) || !isDefaultishName(sym) || category.indexOf("general") < 0) {
                mdw.println("| `" + md(addrText(d.getAddress())) + "` | `" + md(sym) + "` | " + md(category) + " | `" + md(svalue) + "` | " + md(funcs) + " |");
            }
            monitor.checkCancelled();
        }
        tsv.close();
        mdw.close();
    }

    private void writeFunctionModuleGuesses(File out, List<FunctionRow> functions) throws Exception {
        PrintWriter tsv = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "function_module_guesses.tsv"))));
        tsv.println("entry\tname\tmodule_guess\tmodule_evidence\tis_semantic\tcomment");
        for (FunctionRow row : functions) {
            Function fn = row.fn;
            String[] guess = moduleGuessAndEvidence(fn);
            tsv.println(addrText(fn.getEntryPoint()) + "\t" + clean(fn.getName()) + "\t" + clean(guess[0]) + "\t" +
                    clean(guess[1]) + "\t" + isSemanticFunction(fn) + "\t" + clean(fn.getComment()));
            monitor.checkCancelled();
        }
        tsv.close();
    }

    private void writeDefinedData(File out) throws Exception {
        PrintWriter tsv = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "defined_data.tsv"))));
        tsv.println("address\tsymbol\tdata_type\tlength\tvalue_preview\tfunction_context\treferences_from_count\treferences_to_count");
        Listing listing = currentProgram.getListing();
        Iterator<Data> it = listing.getDefinedData(true);
        while (it.hasNext()) {
            Data d = it.next();
            dataCount++;
            String sym = "";
            try {
                Symbol s = currentProgram.getSymbolTable().getPrimarySymbol(d.getAddress());
                if (s != null) sym = s.getName();
            } catch (Exception ex) { sym = ""; }
            String val = "";
            try {
                Object v = d.getValue();
                if (v != null) val = v.toString();
            } catch (Exception ex) { val = ""; }
            if (val.length() > MAX_VALUE_PREVIEW) val = val.substring(0, MAX_VALUE_PREVIEW) + "...";
            Function fn = getFunctionContaining(d.getAddress());
            Reference[] rf = d.getReferencesFrom();
            Reference[] rt = getReferencesTo(d.getAddress());
            tsv.println(addrText(d.getAddress()) + "\t" + clean(sym) + "\t" + clean(d.getDataType().getDisplayName()) + "\t" + d.getLength() + "\t" +
                    clean(val) + "\t" + clean(fn == null ? "" : fn.getName()) + "\t" + (rf == null ? 0 : rf.length) + "\t" + (rt == null ? 0 : rt.length));
            monitor.checkCancelled();
        }
        tsv.close();
    }

    private void writeDataTypes(File out) throws Exception {
        PrintWriter tsv = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "data_types_structures.tsv"))));
        PrintWriter mdw = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "data_types_structures.md"))));
        tsv.println("structure_name\tcategory\tlength\tfield_ordinal\tfield_offset\tfield_length\tfield_name\tfield_type\tfield_comment");
        mdw.println("# Structure Data Types");
        mdw.println();
        DataTypeManager dtm = currentProgram.getDataTypeManager();
        Iterator<DataType> it = dtm.getAllDataTypes();
        while (it.hasNext()) {
            DataType dt = it.next();
            if (!(dt instanceof Structure)) continue;
            Structure st = (Structure)dt;
            structureCount++;
            CategoryPath cp = st.getCategoryPath();
            mdw.println("## `" + md(st.getName()) + "`");
            mdw.println();
            mdw.println("Category: `" + md(cp == null ? "" : cp.getPath()) + "`  ");
            mdw.println("Length: `" + st.getLength() + "`");
            mdw.println();
            mdw.println("| Ordinal | Offset | Length | Name | Type | Comment |");
            mdw.println("|---:|---:|---:|---|---|---|");
            DataTypeComponent[] comps = st.getDefinedComponents();
            for (int i = 0; i < comps.length; i++) {
                DataTypeComponent c = comps[i];
                String fname = c.getFieldName() == null ? "" : c.getFieldName();
                String ftype = c.getDataType() == null ? "" : c.getDataType().getDisplayName();
                String fcom = c.getComment() == null ? "" : c.getComment();
                tsv.println(clean(st.getName()) + "\t" + clean(cp == null ? "" : cp.getPath()) + "\t" + st.getLength() + "\t" +
                        c.getOrdinal() + "\t" + c.getOffset() + "\t" + c.getLength() + "\t" + clean(fname) + "\t" + clean(ftype) + "\t" + clean(fcom));
                mdw.println("| " + c.getOrdinal() + " | " + c.getOffset() + " | " + c.getLength() + " | `" + md(fname) + "` | `" + md(ftype) + "` | " + md(fcom) + " |");
            }
            mdw.println();
            monitor.checkCancelled();
        }
        tsv.close();
        mdw.close();
    }

    private void writeReferencesAndCallGraph(File out, List<FunctionRow> functions) throws Exception {
        PrintWriter refs = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "references_from_instructions.tsv"))));
        PrintWriter calls = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "callgraph.tsv"))));
        refs.println("function_entry\tfunction_name\tinstruction_address\tto_address\treference_type\tis_call\ttarget_function_entry\ttarget_function_name\ttarget_symbol");
        calls.println("caller_entry\tcaller_name\tcallsite\tcallee_entry\tcallee_name\treference_type");
        for (FunctionRow row : functions) {
            Function fn = row.fn;
            Instruction ins = getInstructionAt(fn.getEntryPoint());
            Address max = fn.getBody().getMaxAddress();
            int count = 0;
            while (ins != null && fn.getBody().contains(ins.getAddress()) && ins.getAddress().compareTo(max) <= 0 && count < MAX_INSTRUCTIONS_PER_FUNCTION) {
                Reference[] rr = ins.getReferencesFrom();
                if (rr != null) {
                    for (int i = 0; i < rr.length; i++) {
                        Reference r = rr[i];
                        Function tf = getFunctionContaining(r.getToAddress());
                        Symbol ts = null;
                        try { ts = currentProgram.getSymbolTable().getPrimarySymbol(r.getToAddress()); } catch (Exception ex) { ts = null; }
                        boolean isCall = r.getReferenceType().isCall();
                        refs.println(addrText(fn.getEntryPoint()) + "\t" + clean(fn.getName()) + "\t" + addrText(ins.getAddress()) + "\t" +
                                addrText(r.getToAddress()) + "\t" + clean(r.getReferenceType().toString()) + "\t" + isCall + "\t" +
                                (tf == null ? "" : addrText(tf.getEntryPoint())) + "\t" + clean(tf == null ? "" : tf.getName()) + "\t" + clean(ts == null ? "" : ts.getName()));
                        if (isCall && tf != null) {
                            callEdgeCount++;
                            calls.println(addrText(fn.getEntryPoint()) + "\t" + clean(fn.getName()) + "\t" + addrText(ins.getAddress()) + "\t" +
                                    addrText(tf.getEntryPoint()) + "\t" + clean(tf.getName()) + "\t" + clean(r.getReferenceType().toString()));
                        }
                    }
                }
                ins = ins.getNext();
                count++;
            }
            monitor.checkCancelled();
        }
        refs.close();
        calls.close();
    }

    private void writeRenameInventory(File out, List<FunctionRow> functions) throws Exception {
        PrintWriter tsv = new PrintWriter(new BufferedWriter(new FileWriter(new File(out, "rename_inventory.tsv"))));
        tsv.println("kind\taddress\tname\tmodule_guess\tmodule_evidence\tsource_type\tis_defaultish\tis_semantic\tnotes");
        for (FunctionRow row : functions) {
            Function fn = row.fn;
            boolean def = isDefaultishName(fn.getName());
            String[] mod = moduleGuessAndEvidence(fn);
            tsv.println("function\t" + addrText(fn.getEntryPoint()) + "\t" + clean(fn.getName()) + "\t" + clean(mod[0]) + "\t" + clean(mod[1]) + "\t" + clean(fn.getSymbol().getSource().toString()) + "\t" + def + "\t" + isSemanticFunction(fn) + "\t");
        }
        SymbolIterator it = currentProgram.getSymbolTable().getAllSymbols(true);
        while (it.hasNext()) {
            Symbol s = it.next();
            if (s.getSymbolType() == ghidra.program.model.symbol.SymbolType.FUNCTION) continue;
            boolean def = isDefaultishName(s.getName());
            if (!def || s.getSource() == SourceType.USER_DEFINED) {
                tsv.println("symbol\t" + addrText(s.getAddress()) + "\t" + clean(s.getName()) + "\t\t\t" + clean(s.getSource().toString()) + "\t" + def + "\t" + (!def) + "\t" + clean(s.getSymbolType().toString()));
            }
            monitor.checkCancelled();
        }
        tsv.close();
    }

    private boolean shouldExportFunctionBody(Function fn, boolean allMode) {
        if (allMode) return true;
        return isSemanticFunction(fn);
    }

    private void writeDecompileFiles(List<FunctionRow> functions) throws Exception {
        if (!EXPORT_DECOMPILE) return;
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        int done = 0;
        PrintWriter index = new PrintWriter(new BufferedWriter(new FileWriter(new File(outDir, "decompile_index.tsv"))));
        index.println("entry\tname\tfile\tstatus\terror");
        for (FunctionRow row : functions) {
            Function fn = row.fn;
            if (!shouldExportFunctionBody(fn, DECOMPILE_ALL_FUNCTIONS)) continue;
            if (done >= MAX_DECOMPILE_FUNCTIONS) break;
            String fileName = addrText(fn.getEntryPoint()) + "_" + safeFileName(fn.getName()) + ".c";
            File f = new File(decompileDir, fileName);
            PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(f)));
            pw.println("/*");
            pw.println(" * Program: " + currentProgram.getName());
            pw.println(" * Function: " + fn.getName());
            pw.println(" * Entry: " + fn.getEntryPoint());
            pw.println(" * Signature: " + clean(fn.getSignature().toString()));
            pw.println(" */");
            pw.println();
            String status = "ok";
            String err = "";
            try {
                DecompileResults res = ifc.decompileFunction(fn, 90, monitor);
                if (res != null && res.decompileCompleted() && res.getDecompiledFunction() != null) {
                    pw.println(res.getDecompiledFunction().getC());
                } else {
                    status = "failed";
                    err = res == null ? "null result" : res.getErrorMessage();
                    pw.println("/* decompile failed: " + clean(err) + " */");
                }
            } catch (Exception ex) {
                status = "exception";
                err = ex.toString();
                pw.println("/* decompile exception: " + clean(err) + " */");
            }
            pw.close();
            index.println(addrText(fn.getEntryPoint()) + "\t" + clean(fn.getName()) + "\tdecompile/" + clean(fileName) + "\t" + status + "\t" + clean(err));
            done++;
            monitor.checkCancelled();
        }
        index.close();
        ifc.dispose();
    }

    private void writeDisassemblyFiles(List<FunctionRow> functions) throws Exception {
        if (!EXPORT_DISASSEMBLY) return;
        int done = 0;
        PrintWriter index = new PrintWriter(new BufferedWriter(new FileWriter(new File(outDir, "disassembly_index.tsv"))));
        index.println("entry\tname\tfile\tinstruction_count\ttruncated");
        for (FunctionRow row : functions) {
            Function fn = row.fn;
            if (!shouldExportFunctionBody(fn, DISASSEMBLE_ALL_FUNCTIONS)) continue;
            if (done >= MAX_DISASSEMBLY_FUNCTIONS) break;
            String fileName = addrText(fn.getEntryPoint()) + "_" + safeFileName(fn.getName()) + ".asm.tsv";
            File f = new File(disasmDir, fileName);
            PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(f)));
            pw.println("address\tbytes\tmnemonic\toperands\tinstruction");
            Instruction ins = getInstructionAt(fn.getEntryPoint());
            Address max = fn.getBody().getMaxAddress();
            int count = 0;
            boolean trunc = false;
            while (ins != null && fn.getBody().contains(ins.getAddress()) && ins.getAddress().compareTo(max) <= 0) {
                if (count >= MAX_INSTRUCTIONS_PER_FUNCTION) { trunc = true; break; }
                pw.println(addrText(ins.getAddress()) + "\t" + clean(bytesString(ins)) + "\t" + clean(ins.getMnemonicString()) + "\t" + clean(operandsString(ins)) + "\t" + clean(ins.toString()));
                ins = ins.getNext();
                count++;
            }
            pw.close();
            index.println(addrText(fn.getEntryPoint()) + "\t" + clean(fn.getName()) + "\tdisassembly/" + clean(fileName) + "\t" + count + "\t" + trunc);
            done++;
            monitor.checkCancelled();
        }
        index.close();
    }

    private void makeTar(File dir) throws Exception {
        File parent = dir.getParentFile();
        File tar = new File(parent, dir.getName() + ".tar");
        if (tar.exists()) tar.delete();
        ProcessBuilder pb = new ProcessBuilder("tar", "-cf", tar.getAbsolutePath(), "-C", parent.getAbsolutePath(), dir.getName());
        pb.redirectErrorStream(true);
        Process p = pb.start();
        int rc = p.waitFor();
        if (rc == 0) println("Archive: " + tar.getAbsolutePath());
        else println("warning: tar exited with code " + rc);
    }

    @Override
    public void run() throws Exception {
        File root = chooseOutputRoot();
        ensureDir(root);
        String ts = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
        String base = safeFileName(currentProgram.getName()).replaceAll("\\.+$", "") + "_ghidra_state_snapshot_" + ts;
        outDir = new File(root, base);
        decompileDir = new File(outDir, "decompile");
        disasmDir = new File(outDir, "disassembly");
        ensureDir(outDir);
        ensureDir(decompileDir);
        ensureDir(disasmDir);

        println("Collecting functions...");
        List<FunctionRow> functions = collectFunctions();

        println("Writing function index...");
        writeFunctionIndex(outDir, functions);

        println("Writing symbols...");
        writeSymbols(outDir);

        println("Writing comments...");
        writeComments(outDir);

        println("Writing memory blocks...");
        writeMemoryBlocks(outDir);

        println("Writing defined data...");
        writeDefinedData(outDir);

        println("Writing defined strings...");
        writeDefinedStrings(outDir);

        println("Writing function module guesses...");
        writeFunctionModuleGuesses(outDir, functions);

        println("Writing data type structures...");
        writeDataTypes(outDir);

        println("Writing references and call graph...");
        writeReferencesAndCallGraph(outDir, functions);

        println("Writing rename inventory...");
        writeRenameInventory(outDir, functions);

        println("Writing decompile files...");
        writeDecompileFiles(functions);

        println("Writing disassembly files...");
        writeDisassemblyFiles(functions);

        println("Writing README and manifest...");
        writeReadme(outDir, functions);
        writeManifest(outDir);

        println("Creating tar archive...");
        makeTar(outDir);
        println("Done: " + outDir.getAbsolutePath());
    }
}
