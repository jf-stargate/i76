// @category I76
// Interstate '76 — v72 Vehicle Object Model / FSM bridge.
// Baseline: Ghidra i76.exe snapshot 2026-10-19 18:34:29 PDT (v71 ownership fixed).
//
// This pass PRESERVES functions, boundaries, data, types and existing comments.
// It applies ONLY two explicitly reviewed status-flag helper renames and
// exports read-only evidence needed to reconcile FSM-visible and runtime state.
//
// Modes: AUDIT | APPLY_RENAMES. Set MODE to AUDIT to skip even the renames.
// All mutation is guarded by program MD5, exact symbol identities, and one
// all-or-nothing Ghidra transaction. Run in the i76.exe CodeBrowser.
//
// Outputs:
//   i76_v72_vom_fsm_sites.tsv
//   i76_v72_vom_fsm_edges.tsv
//   i76_v72_vom_fsm_flag_candidates.tsv
//   i76_v72_vom_fsm_decompiled.txt
//   i76_v72_rename_decisions.tsv
//
// These exports are investigative evidence, not proof of object-field aliasing.

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.*;

public class I76_FSM_V72_VOM_Bridge extends GhidraScript {

    private static final String MODE = "APPLY_RENAMES"; // or "AUDIT"
    private static final String OUTPUT_DIR =
        "/media/neon-remote/prj/i76/scratch_data";
    private static final String EXPECTED_MD5 =
        "a640ea0097dbb62e0c77b7f2847c7161";

    // Intentional: include instruction sites inside larger functions as well
    // as independently defined function entries. Missing ownership is reported.
    private static final String[][] SITES = {
        {"0040B840", "isDead_predicate_object_flags_0x200"},
        {"00413C2C", "isDead_host_opcode_36"},
        {"0040B860", "isGroovesFault_predicate_ai_A6E0"},
        {"00413BB0", "isGroovesFault_host_opcode_88"},
        {"0040AF3D", "sit_dead_car_guard_runtime_0x454"},
        {"0040B9FE", "destroy_dead_car_guard_runtime_0x454"},
        {"0040B0F0", "recent_damage_source_query"},
        {"0040B1F0", "who_attacked_query"},
        {"0040B990", "damage_state_slot_match_query"},
        {"0040BD90", "setSkill_runtime_profile_updater"},
        {"00413645", "setSkill_host_opcode_69"},
        {"004157A0", "record_vehicle_damage_source_event"},
        {"00415872", "dead_car_attribution_gate"},
        {"0041588F", "primary_actor_identity_comparison"},
        {"00415893", "ai_kill_credit_latch_write"},
        {"004A8240", "direct_damage_dispatch_before_attribution"},
        {"004A821C", "direct_damage_source_callsite_a"},
        {"004A8298", "direct_damage_source_callsite_b"},
        {"00462040", "world_class_damage_handler_dispatch"},
        {"00463A80", "vehicle_class_damage_to_world_dead_flag_0x200"},
        {"00465AF0", "vehicle_damage_component_dispatch"},
        {"00465D68", "vehicle_dead_flag_producer_0x20"},
        {"00465D7F", "vehicle_dead_flag_producer_context"},
        {"00465370", "vehicle_lifecycle_and_destruction_update"},
        {"00466180", "vehicle_catastrophic_breakup"},
        {"004572B0", "active_world_object_registration"},
        {"00457420", "active_world_object_unregistration"},
        {"00457530", "active_primary_world_entry_getter"},
        {"00458790", "set_world_subtree_flags"},
        {"00458810", "set_world_and_descendant_flags"},
        {"004587D0", "clear_world_subtree_flags"},
        {"00458860", "clear_world_and_descendant_flags"},
        {"0045F0F0", "fsm_object_reference_lifetime_helper"}
    };

    private static final String[][] RENAMES = {
        {"004587D0", "world_object_geometry_context_helper_004587d0",
            "clear_world_object_subtree_status_flags_recursive"},
        {"00458860", "world_object_geometry_context_helper_00458860",
            "clear_world_object_and_descendant_status_flags"}
    };

    // Guard against accidentally running on a pre-v71 Ghidra database.
    // Sizes were verified against the 18:34:29 exported function inventory.
    private static final String[][] V71_PARENT_BODIES = {
        {"004621E0", "925"}, {"00462660", "595"},
        {"0046A7F0", "144"}, {"0046BB60", "45"},
        {"0046BB90", "292"}, {"0046D160", "162"},
        {"0046D2E0", "688"}, {"0046D590", "299"},
        {"0046DFE0", "444"}, {"0046F5B0", "151"},
        {"0046F650", "82"}, {"004A2000", "106"},
        {"004A2070", "962"}
    };

    // Candidate displacement/bit-constant search. These text matches are an
    // overinclusive discovery aid; DO NOT interpret hits as field ownership.
    private static final String[] TOKENS = {
        "0x454", "0xa6e0", "0xa6d4", "0xa6d8", "0xa6dc",
        "0xa6e4", "0xa6e8", "0xa6ec", "0xa6f0", "0x200",
        "0x0054a264"
    };

    private Address at(String hex) {
        return toAddr(Long.parseLong(hex, 16));
    }

    private String fmt(Object object) {
        if (object == null) return "";
        return object.toString().replace('\t',' ').replace('\n',' ')
            .replace('\r',' ');
    }

    private void row(BufferedWriter out, Object... values) throws IOException {
        for (int i = 0; i < values.length; i++) {
            if (i > 0) out.write('\t');
            out.write(fmt(values[i]));
        }
        out.newLine();
    }

    private BufferedWriter writer(Path dir, String name) throws IOException {
        return Files.newBufferedWriter(dir.resolve(name), StandardCharsets.UTF_8);
    }

    private String description(Function f) {
        return f == null ? "" : f.getName();
    }

    private Function owner(Address address) {
        return currentProgram.getFunctionManager().getFunctionContaining(address);
    }

    private String siteInstruction(Address address) {
        Instruction ins = currentProgram.getListing().getInstructionContaining(address);
        if (ins == null) return "NO_INSTRUCTION";
        return (ins.getAddress().equals(address) ? "" : "INSIDE_INSTRUCTION ")
            + fmt(ins);
    }

    private void verifyEnvironment() throws Exception {
        if (!MODE.equals("AUDIT") && !MODE.equals("APPLY_RENAMES"))
            throw new IllegalStateException("Unknown MODE: " + MODE);
        if (!currentProgram.getName().equalsIgnoreCase("i76.exe"))
            throw new IllegalStateException("Unexpected program: " + currentProgram.getName());
        if (currentProgram.getImageBase().getOffset() != 0x00400000L)
            throw new IllegalStateException("Unexpected image base");
        String md5 = currentProgram.getExecutableMD5();
        if (md5 == null || !md5.equalsIgnoreCase(EXPECTED_MD5))
            throw new IllegalStateException("Wrong executable MD5: " + md5);
        for (String[] ren : RENAMES) {
            Function f = currentProgram.getFunctionManager().getFunctionAt(at(ren[0]));
            if (f == null) throw new IllegalStateException("Missing function " + ren[0]);
            String actual = f.getName();
            if (!actual.equals(ren[1]) && !actual.equals(ren[2]))
                throw new IllegalStateException("Unexpected name at " + ren[0]
                    + ": " + actual);
        }
        for (String[] pair : V71_PARENT_BODIES) {
            Function f = currentProgram.getFunctionManager().getFunctionAt(at(pair[0]));
            long expectedSize = Long.parseLong(pair[1]);
            if (f == null || f.getBody().getNumAddresses() != expectedSize)
                throw new IllegalStateException("v71 body ownership differs: " + pair[0]
                    + "; do not use this script on an unmerged snapshot");
        }
        // Verify code exists at the three critical v63 instruction sites.
        verifyBytes("00415872", 0xF6, 0x85, 0x54, 0x04, 0x00, 0x00, 0x20);
        verifyBytes("0040B9FE", 0xF6, 0x87, 0x54, 0x04, 0x00, 0x00, 0x20);
        verifyBytes("0040AF3D", 0xF6, 0x86, 0x54, 0x04, 0x00, 0x00, 0x20);
    }

    private void verifyBytes(String addr, int... bytes) throws Exception {
        Address base = at(addr);
        for (int i = 0; i < bytes.length; i++) {
            int actual = currentProgram.getMemory().getByte(base.add(i)) & 0xff;
            if (actual != bytes[i]) throw new IllegalStateException(
                "Signature mismatch at " + base.add(i));
        }
    }

    private void exportSites(Path dir) throws Exception {
        try (BufferedWriter out = writer(dir,"i76_v72_vom_fsm_sites.tsv")) {
            row(out, "site", "reason", "instruction", "containing_function_entry",
                "containing_function_name", "body_range", "body_bytes");
            for (String[] spec : SITES) {
                monitor.checkCancelled();
                Address address = at(spec[0]);
                Function f = owner(address);
                row(out, address, spec[1], siteInstruction(address),
                    f == null ? "" : f.getEntryPoint(), description(f),
                    f == null ? "" : f.getBody(),
                    f == null ? "" : f.getBody().getNumAddresses());
            }
        }
    }

    private void exportEdges(Path dir) throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager rm = currentProgram.getReferenceManager();
        Listing listing = currentProgram.getListing();
        TreeMap<String, Function> unique = new TreeMap<>();
        for (String[] s : SITES) {
            Function f = owner(at(s[0]));
            if (f != null) unique.put(f.getEntryPoint().toString(), f);
        }
        try (BufferedWriter out = writer(dir,"i76_v72_vom_fsm_edges.tsv")) {
            row(out,"direction","focus_entry","focus_name","from_address",
                "from_function","reference_type","to_address","to_function");
            for (Function f : unique.values()) {
                monitor.checkCancelled();
                ReferenceIterator incoming = rm.getReferencesTo(f.getEntryPoint());
                while (incoming.hasNext()) {
                    Reference r = incoming.next();
                    if (!r.getReferenceType().isCall() && !r.getReferenceType().isJump()) continue;
                    Function source = fm.getFunctionContaining(r.getFromAddress());
                    row(out,"IN",f.getEntryPoint(),f.getName(),r.getFromAddress(),
                        description(source),r.getReferenceType(),r.getToAddress(),f.getName());
                }
                InstructionIterator it = listing.getInstructions(f.getBody(), true);
                while (it.hasNext()) {
                    monitor.checkCancelled();
                    Instruction ins = it.next();
                    for (Reference r : ins.getReferencesFrom()) {
                        if (!r.getReferenceType().isCall()) continue;
                        Function target = fm.getFunctionContaining(r.getToAddress());
                        row(out,"OUT",f.getEntryPoint(),f.getName(),r.getFromAddress(),
                            f.getName(),r.getReferenceType(),r.getToAddress(),
                            description(target));
                    }
                }
            }
        }
    }

    private void exportFlagCandidates(Path dir) throws Exception {
        Listing listing = currentProgram.getListing();
        // Full-code scan catches producers outside the selected VOM/FSM functions.
        // Restrict candidate classification to textual assembly, not semantic proof.
        try (BufferedWriter out = writer(dir,"i76_v72_vom_fsm_flag_candidates.tsv")) {
            row(out,"instruction","function_entry","function_name",
                "token","mnemonic","assembly","candidate_only");
            InstructionIterator it = listing.getInstructions(true);
            int examined = 0;
            int hits = 0;
            while (it.hasNext()) {
                Instruction ins = it.next();
                if ((++examined & 0x0fff) == 0) monitor.checkCancelled();
                String assembly = fmt(ins).toLowerCase(Locale.ROOT);
                for (String token : TOKENS) {
                    // A token must end before the next hexadecimal digit.
                    int index = assembly.indexOf(token);
                    while (index >= 0) {
                        int end = index + token.length();
                        if (end == assembly.length() ||
                            Character.digit(assembly.charAt(end),16) < 0) {
                            Function f = owner(ins.getAddress());
                            row(out,ins.getAddress(),
                                f == null ? "" : f.getEntryPoint(),
                                description(f),token,ins.getMnemonicString(),
                                assembly,"YES");
                            ++hits;
                            break;
                        }
                        index = assembly.indexOf(token,index + 1);
                    }
                }
            }
            println("v72 opcode candidate scan: " + examined +
                " instructions; " + hits + " token matches (not verified field uses)");
        }
    }

    private void exportDecompiled(Path dir) throws Exception {
        TreeMap<String, Function> functions = new TreeMap<>();
        for (String[] spec : SITES) {
            Function f = owner(at(spec[0]));
            if (f != null) functions.put(f.getEntryPoint().toString(),f);
        }
        DecompInterface decomp = new DecompInterface();
        if (!decomp.openProgram(currentProgram))
            throw new IllegalStateException("Cannot initialize Ghidra decompiler");
        try (BufferedWriter out = writer(dir,"i76_v72_vom_fsm_decompiled.txt")) {
            row(out,"I76 v72: current-program decompilation, selected VOM/FSM ownership set");
            for (Function f : functions.values()) {
                monitor.checkCancelled();
                out.write("\n===== " + f.getEntryPoint() + " " + f.getName() + " =====\n");
                DecompileResults result = decomp.decompileFunction(f, 90, monitor);
                if (result != null && result.decompileCompleted() &&
                    result.getDecompiledFunction() != null) {
                    out.write(result.getDecompiledFunction().getC());
                } else {
                    out.write("DECOMPILATION FAILED: " +
                        (result == null ? "no result" :
                            fmt(result.getErrorMessage())) + "\n");
                }
            }
        } finally {
            decomp.dispose();
        }
    }

    private void applyRenames(Path dir) throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        // Revalidate both immediately before entering the mutation transaction.
        for (String[] item : RENAMES) {
            Function f = fm.getFunctionAt(at(item[0]));
            if (f == null || (!f.getName().equals(item[1]) &&
                              !f.getName().equals(item[2])))
                throw new IllegalStateException("Rename preflight changed: " + item[0]);
        }
        if (MODE.equals("AUDIT")) {
            try (BufferedWriter out = writer(dir,"i76_v72_rename_decisions.tsv")) {
                row(out,"address","existing","proposed","result");
                for (String[] item : RENAMES)
                    row(out,item[0],fm.getFunctionAt(at(item[0])).getName(),
                        item[2],"AUDIT_ONLY");
            }
            return;
        }
        int transaction = currentProgram.startTransaction("I76 v72 two status-flag helper renames");
        boolean commit = false;
        try {
            for (String[] item : RENAMES) {
                Function f = fm.getFunctionAt(at(item[0]));
                if (!f.getName().equals(item[2]))
                    f.setName(item[2],SourceType.USER_DEFINED);
            }
            commit = true;
        } finally {
            currentProgram.endTransaction(transaction,commit);
        }
        // Log reflects committed state, not intended mutations.
        try (BufferedWriter out = writer(dir,"i76_v72_rename_decisions.tsv")) {
            row(out,"address","previous_expected","new_name","result");
            for (String[] item : RENAMES) {
                Function f = fm.getFunctionAt(at(item[0]));
                row(out,item[0],item[1],f == null ? "" : f.getName(),
                    f != null && f.getName().equals(item[2])
                    ? "VERIFIED_AFTER_COMMIT" : "MISMATCH");
            }
        }
    }

    @Override
    public void run() throws Exception {
        verifyEnvironment();
        Path dir = Paths.get(OUTPUT_DIR);
        Files.createDirectories(dir);
        println("I76 v72: evidence exports from current Ghidra program...");
        exportSites(dir);
        exportEdges(dir);
        exportFlagCandidates(dir);
        exportDecompiled(dir);
        // Only after all read-only analysis outputs succeed do we mutate symbols.
        applyRenames(dir);
        println("I76 v72 complete. Mode: " + MODE);
        println("Evidence: i76_v72_vom_fsm_*.tsv/.txt");
        println("Rename log: i76_v72_rename_decisions.tsv");
        println("Output directory: " + dir);
    }
}
