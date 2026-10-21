// @category I76
// Interstate '76 v73: Vehicle Object Model <-> FSM event lifecycle.
// Read-only evidence export. No function creation, renaming, or datatype changes.
//
// Required program: original i76.exe (MD5 a640ea0097dbb62e0c77b7f2847c7161),
// post-v71 function ownership, post-v72 status-flag helper renames.
//
// This pass follows distinct state domains:
//   world_object+0x10 bit 0x200  : isDead observation
//   vehicle_runtime+0x454 bit 0x20 : fatal vehicle status
//   ai_private+0xA6D4..0xA6F0: event stamps/sources/credit
// The listing scan reports displacement accesses only; it does NOT prove
// object-base identity, field type, aliasing, or temporal ordering.
//
// Outputs under OUTPUT_DIR:
//   i76_v73_fsm_event_functions.tsv
//   i76_v73_fsm_event_fields.tsv
//   i76_v73_fsm_event_instructions.tsv
//   i76_v73_fsm_event_edges.tsv
//   i76_v73_fsm_event_decompiled.txt
//
// Run in CodeBrowser with i76.exe open. Save a new snapshot after review,
// but this script itself does not change the program database.

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.ReferenceManager;
import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Locale;
import java.util.Map;
import java.util.TreeMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class i76_v73_fsm_event_lifecycle extends GhidraScript {
    private static final String OUTPUT_DIR =
        "/media/neon-remote/prj/i76/scratch_data";
    private static final String EXPECTED_MD5 =
        "a640ea0097dbb62e0c77b7f2847c7161";

    // Focus on callbacks/host commands, event slots, direct and radial damage,
    // class destruction, and network-replicated death. 00412CE0 is the
    // established 96-command dispatcher; its output can be large.
    private static final String[][] FOCUS = {
        {"00409BD0", "fsm_vehicle_subsystem_init"},
        {"0040AF00", "fsm_sit_vehicle_guard"},
        {"0040AFF0", "who_rammed_source_A6E4"},
        {"0040B0F0", "who_shot_source_A6E8"},
        {"0040B1F0", "who_attacked_source_A6EC"},
        {"0040B410", "event_A6D4_poll_and_clear"},
        {"0040B800", "event_A6D8_poll_and_clear"},
        {"0040B990", "event_A6DC_poll_clear_all"},
        {"0040B840", "fsm_isDead_world_flag_0200"},
        {"0040B860", "fsm_isGroovesFault_credit_A6E0"},
        {"0040B9E0", "fsm_destroy_vehicle_guard"},
        {"00412CE0", "host_command_dispatch"},
        {"00415640", "ai_fsm_private_state_init"},
        {"004157A0", "event_source_and_kill_credit_producer"},
        {"0041C2C0", "secondary_event_A6D8_consumer"},
        {"00462040", "class_damage_dispatch"},
        {"00463A80", "vehicle_class_damage_and_world_death"},
        {"00464890", "network_damage_and_death_reconciliation"},
        {"00465370", "vehicle_lifecycle_frame_update"},
        {"00465AF0", "component_damage_sets_runtime_death"},
        {"00466180", "catastrophic_breakup_sets_world_death"},
        {"004572B0", "world_entry_registration"},
        {"00457420", "world_entry_unregistration"},
        {"00457530", "active_primary_entry_lookup"},
        {"00458790", "world_subtree_status_set"},
        {"004587D0", "world_subtree_status_clear"},
        {"00458810", "world_descendant_status_set"},
        {"00458860", "world_descendant_status_clear"},
        {"004A7C80", "radial_damage_before_source_event"},
        {"004A8240", "direct_damage_before_source_event"}
    };

    private static final String[] EVENT_FIELDS = {
        "a6d4", "a6d8", "a6dc", "a6e0", "a6e4",
        "a6e8", "a6ec", "a6f0"
    };

    // Match displacement inside bracketed memory operands, rather than any
    // numeric literal equal to the offset. Also handles base+index+offset.
    private static final Pattern MEMORY = Pattern.compile("\\[([^\\]]+)\\]");
    private static final Pattern PLUS_HEX =
        Pattern.compile("\\+\\s*0x([0-9a-f]+)");

    private Address addr(String hex) {
        return toAddr(Long.parseLong(hex, 16));
    }

    private String clean(Object o) {
        if (o == null) return "";
        return o.toString().replace('\t',' ').replace('\n',' ')
                   .replace('\r',' ');
    }

    private void row(BufferedWriter out, Object... columns) throws Exception {
        for (int i = 0; i < columns.length; ++i) {
            if (i > 0) out.write('\t');
            out.write(clean(columns[i]));
        }
        out.newLine();
    }

    private BufferedWriter writer(Path dir, String file) throws Exception {
        return Files.newBufferedWriter(dir.resolve(file), StandardCharsets.UTF_8);
    }

    private void requireBytes(long location, int... expected) throws Exception {
        Address at = toAddr(location);
        for (int i = 0; i < expected.length; i++) {
            int value = getByte(at.add(i)) & 0xff;
            if (value != expected[i]) {
                throw new IllegalStateException(String.format(
                    "Signature mismatch at %08X: got %02X expected %02X",
                    location+i, value, expected[i]));
            }
        }
    }

    private void validate() throws Exception {
        if (!currentProgram.getName().equalsIgnoreCase("i76.exe"))
            throw new IllegalStateException("Not the i76.exe program");
        if (currentProgram.getImageBase().getOffset() != 0x00400000L)
            throw new IllegalStateException("Unexpected image base");
        String md5 = currentProgram.getExecutableMD5();
        if (!EXPECTED_MD5.equalsIgnoreCase(md5))
            throw new IllegalStateException("Wrong executable MD5: " + md5);

        // Prove source, dead-state gate, and sticky attribution are the same
        // retail-code instructions previously reviewed in v63/v72.
        requireBytes(0x00415872L, 0xF6,0x85,0x54,0x04,0x00,0x00,0x20);
        requireBytes(0x0041588FL, 0x3B,0x38);
        requireBytes(0x00415893L, 0xC7,0x86,0xE0,0xA6,0x00,0x00,0x01);
        requireBytes(0x0040B9FEL, 0xF6,0x87,0x54,0x04,0x00,0x00,0x20);

        FunctionManager fm = currentProgram.getFunctionManager();
        String[][] expected = {
            {"004587D0", "clear_world_object_subtree_status_flags_recursive"},
            {"00458860", "clear_world_object_and_descendant_status_flags"}
        };
        for (String[] item : expected) {
            Function f = fm.getFunctionAt(addr(item[0]));
            if (f == null || !item[1].equals(f.getName()))
                throw new IllegalStateException("Missing v72 rename at " + item[0]);
        }
        // Guard against going backward to the pre-v71 split boundaries.
        String[][] bodies = {
            {"0046A7F0", "144"}, {"0046D160", "162"},
            {"0046DFE0", "444"}, {"004A2070", "962"}
        };
        for (String[] item : bodies) {
            Function f = fm.getFunctionAt(addr(item[0]));
            if (f == null || f.getBody().getNumAddresses() !=
                             Long.parseLong(item[1]))
                throw new IllegalStateException("v71 body ownership changed at " + item[0]);
        }
    }

    private TreeMap<String, Function> focus(Path dir) throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        TreeMap<String, Function> found = new TreeMap<>();
        try (BufferedWriter out = writer(dir,"i76_v73_fsm_event_functions.tsv")) {
            row(out,"requested_address","investigation_role","status",
                "function_entry","name","body_bytes","body_ranges");
            for (String[] item : FOCUS) {
                monitor.checkCancelled();
                Function f = fm.getFunctionAt(addr(item[0]));
                if (f == null) {
                    row(out,item[0],item[1],"MISSING_ENTRY","","","","");
                    continue;
                }
                found.put(f.getEntryPoint().toString(),f);
                row(out,item[0],item[1],"FUNCTION_ENTRY",f.getEntryPoint(),
                    f.getName(),f.getBody().getNumAddresses(),f.getBody());
            }
        }
        // Fail rather than silently omitting the core model contracts.
        String[] required = {"0040B840","0040B860","00415640","004157A0",
            "00463A80","00464890","00465AF0","00466180","004A8240"};
        for (String key : required)
            if (!found.containsKey(addr(key).toString()))
                throw new IllegalStateException("Required function unavailable: " + key);
        return found;
    }

    private void disassembly(Path dir, TreeMap<String, Function> focus)
            throws Exception {
        Listing listing = currentProgram.getListing();
        try (BufferedWriter out = writer(dir,"i76_v73_fsm_event_instructions.tsv")) {
            row(out,"function_entry","function_name","address","mnemonic",
                "instruction");
            for (Function f : focus.values()) {
                monitor.checkCancelled();
                InstructionIterator it = listing.getInstructions(f.getBody(),true);
                while (it.hasNext()) {
                    Instruction ins = it.next();
                    row(out,f.getEntryPoint(),f.getName(),ins.getAddress(),
                        ins.getMnemonicString(),ins);
                }
            }
        }
    }

    private void edges(Path dir, TreeMap<String, Function> focus)
            throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager refs = currentProgram.getReferenceManager();
        Listing listing = currentProgram.getListing();
        try (BufferedWriter out = writer(dir,"i76_v73_fsm_event_edges.tsv")) {
            row(out,"direction","focus_function","focus_name","source_address",
                "source_function","reference_type","destination_address",
                "destination_function");
            for (Function f : focus.values()) {
                monitor.checkCancelled();
                ReferenceIterator incoming = refs.getReferencesTo(f.getEntryPoint());
                while (incoming.hasNext()) {
                    Reference r = incoming.next();
                    if (!r.getReferenceType().isCall() && !r.getReferenceType().isJump())
                        continue;
                    Function caller = fm.getFunctionContaining(r.getFromAddress());
                    row(out,"IN",f.getEntryPoint(),f.getName(),r.getFromAddress(),
                        caller == null ? "" : caller.getName(),r.getReferenceType(),
                        r.getToAddress(),f.getName());
                }
                InstructionIterator it = listing.getInstructions(f.getBody(),true);
                while (it.hasNext()) {
                    Instruction ins = it.next();
                    for (Reference r : ins.getReferencesFrom()) {
                        if (!r.getReferenceType().isCall()) continue;
                        Function callee = fm.getFunctionContaining(r.getToAddress());
                        row(out,"OUT",f.getEntryPoint(),f.getName(),r.getFromAddress(),
                            f.getName(),r.getReferenceType(),r.getToAddress(),
                            callee == null ? "" : callee.getName());
                    }
                }
            }
        }
    }

    private String eventField(String displacement) {
        for (String s : EVENT_FIELDS)
            if (s.equals(displacement)) return "ai_private+0x" + s.toUpperCase(Locale.ROOT);
        if ("454".equals(displacement)) return "candidate_runtime+0x454";
        return null;
    }

    private String access(String instruction, String mnemonic, String memoryText) {
        // Instruction text is an aid for review. A multi-operand instruction
        // may refer to two memory locations; therefore unknown cases are not
        // automatically treated as writes or as state transitions.
        int comma = instruction.indexOf(',');
        String destination = comma >= 0 ? instruction.substring(0,comma) : instruction;
        boolean left = destination.contains(memoryText);
        String m = mnemonic.toUpperCase(Locale.ROOT);
        if (m.startsWith("CMP") || m.startsWith("TEST") || m.startsWith("PUSH") ||
            m.startsWith("FLD") || m.startsWith("FILD")) return "READ";
        if (m.startsWith("MOV") || m.startsWith("FST") || m.startsWith("FIST"))
            return left ? "WRITE" : "READ";
        if (m.startsWith("OR") || m.startsWith("AND") || m.startsWith("XOR") ||
            m.startsWith("ADD") || m.startsWith("SUB") || m.startsWith("INC") ||
            m.startsWith("DEC")) return left ? "READ_MODIFY_WRITE" : "READ";
        return "REVIEW";
    }

    private void fieldAccesses(Path dir) throws Exception {
        Listing listing = currentProgram.getListing();
        FunctionManager fm = currentProgram.getFunctionManager();
        try (BufferedWriter out = writer(dir,"i76_v73_fsm_event_fields.tsv")) {
            row(out,"address","function_entry","function_name","field_candidate",
                "access_estimate","mnemonic","instruction","classification_limit");
            InstructionIterator it = listing.getInstructions(true);
            int scanned = 0;
            int records = 0;
            while (it.hasNext()) {
                Instruction ins = it.next();
                if ((++scanned & 0x1fff) == 0) monitor.checkCancelled();
                String listingText = ins.toString().toLowerCase(Locale.ROOT);
                Matcher memory = MEMORY.matcher(listingText);
                while (memory.find()) {
                    Matcher displacement = PLUS_HEX.matcher(memory.group(1));
                    while (displacement.find()) {
                        String field = eventField(displacement.group(1));
                        if (field == null) continue;
                        Function f = fm.getFunctionContaining(ins.getAddress());
                        row(out,ins.getAddress(),f == null ? "" : f.getEntryPoint(),
                            f == null ? "" : f.getName(),field,
                            access(listingText,ins.getMnemonicString(),memory.group(0)),
                            ins.getMnemonicString(),ins,
                            "displacement_and_opcode_only; verify base type and dataflow");
                        records++;
                    }
                }
            }
            println("v73 exact displacement scan: " + scanned +
                " instructions; " + records + " candidate accesses");
        }
    }

    private void decompile(Path dir, TreeMap<String, Function> focus)
            throws Exception {
        DecompInterface decompiler = new DecompInterface();
        if (!decompiler.openProgram(currentProgram))
            throw new IllegalStateException("Ghidra decompiler could not open i76.exe");
        try (BufferedWriter out = writer(dir,"i76_v73_fsm_event_decompiled.txt")) {
            out.write("Interstate '76 v73 VOM/FSM evidence; original i76.exe; read-only\n");
            for (Map.Entry<String,Function> e : focus.entrySet()) {
                monitor.checkCancelled();
                Function f = e.getValue();
                out.write("\n===== " + f.getEntryPoint() + " " + f.getName() + " =====\n");
                DecompileResults result = decompiler.decompileFunction(f,90,monitor);
                if (result != null && result.decompileCompleted() &&
                    result.getDecompiledFunction() != null)
                    out.write(result.getDecompiledFunction().getC());
                else
                    out.write("DECOMPILATION FAILED: " +
                        (result == null ? "no result" : clean(result.getErrorMessage())) + "\n");
            }
        } finally {
            decompiler.dispose();
        }
    }

    @Override
    public void run() throws Exception {
        validate();
        Path dir = Paths.get(OUTPUT_DIR);
        Files.createDirectories(dir);
        println("v73 VOM/FSM event-lifecycle evidence: read-only export");
        TreeMap<String, Function> selected = focus(dir);
        disassembly(dir,selected);
        edges(dir,selected);
        fieldAccesses(dir);
        decompile(dir,selected);
        println("v73 complete: " + selected.size() + " focus functions; output: " + dir);
        println("No symbols, functions, code, types or annotations were changed.");
    }
}
