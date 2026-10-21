// @category I76
// i76_v74_fsm_scheduler_event_timing.java
// Interstate '76 VOM/FSM v74: scheduler, damage event epoch, and VM dispatch.
// READ-ONLY. Never renames, sets comments, edits code, or mutates function bodies.
// Based on verified v71 ownership, v72 renames and v73 event-field inventory.
// Run in Ghidra CodeBrowser with the original i76.exe program open.
// Outputs i76_v74_fsm_*.tsv/.txt in OUTPUT_DIR.
// The exported instruction/reference evidence is not a runtime execution trace.

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
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
import java.util.Map;
import java.util.TreeMap;

public class i76_v74_fsm_scheduler_event_timing extends GhidraScript {
    private static final String OUTPUT_DIR =
        "/media/neon-remote/prj/i76/scratch_data/";
    private static final String EXPECTED_MD5 =
        "a640ea0097dbb62e0c77b7f2847c7161";
    private static final long COUNTER_ADDRESS = 0x00524550L;

    private static final String[][] FOCUS = {
        {"00409BD0", "subsystem_initialization"},
        {"0040A320", "vehicle_fsm_frame_driver"},
        {"0040A130", "per_frame_ai_vehicle_updates"},
        {"0040F870", "player_control_change_flush"},
        {"00414670", "fsm_vm_token_executor"},
        {"004149F0", "pending_fsm_command_scheduler"},
        {"00414B50", "reset_fsm_progress_count"},
        {"00414B60", "update_fsm_progress_compare"},
        {"00414B90", "reset_fsm_secondary_progress"},
        {"004155E0", "reset_damage_event_epoch"},
        {"004155F0", "increment_damage_event_epoch"},
        {"00415600", "read_damage_event_epoch"},
        {"00415640", "init_ai_private_event_fields"},
        {"004157A0", "write_damage_event_fields"},
        {"0040B410", "consume_shot_marker"},
        {"0040B800", "consume_ram_marker"},
        {"0040B990", "consume_any_marker"},
        {"0041C2C0", "ai_ram_epoch_predicate"},
        {"0041D240", "ai_safe_drive_epoch_consumer"}
    };
    // Important callsites, asserted by Ghidra direct CALL reference, not decompiler text.
    private static final String[][] REQUIRED_CALLS = {
        {"0040A644", "004149F0"}, // VM pending-work processor
        {"0040A64E", "0040A130"}, // AI vehicle update
        {"0040A653", "00414B60"}, // FSM progress update
        {"0040A658", "004155F0"}, // increment epoch
        {"00414A58", "00414670"}, // first VM run path
        {"00414AE4", "00414670"}  // second VM run path
    };
    private static final String[][] WINDOWS = {
        {"00403DB0", "00403E10", "top_level_frame_call_site"},
        {"0040A320", "0040A355", "fsm_frame_early_exit_gate"},
        {"0040A5D0", "0040A680", "fsm_vs_ai_branch_and_epoch_increment"},
        {"004149F0", "00414B42", "pending_fsm_dispatch_paths"},
        {"004155D0", "00415610", "counter_reset_increment_and_read"},
        {"004157F0", "004158B1", "record_event_counter_and_credit"},
        {"0040B410", "0040B44F", "shot_epoch_consumer"},
        {"0040B800", "0040B83F", "ram_epoch_consumer"},
        {"0040B990", "0040B9DC", "any_event_epoch_consumer"}
    };
    private Address a(String hex) {
        return toAddr(Long.parseLong(hex, 16));
    }
    private static String cell(Object value) {
        return value == null ? "" : value.toString().replace('\t',' ')
            .replace('\r',' ').replace('\n',' ');
    }
    private BufferedWriter output(Path dir, String name) throws Exception {
        return Files.newBufferedWriter(dir.resolve(name), StandardCharsets.UTF_8);
    }
    private void row(BufferedWriter out, Object... cols) throws Exception {
        for (int i=0; i<cols.length; ++i) {
            if (i>0) out.write('\t');
            out.write(cell(cols[i]));
        }
        out.newLine();
    }
    private void verifyBytes(long site, int... expected) throws Exception {
        Address loc = toAddr(site);
        for (int i=0; i<expected.length; i++) {
            if ((getByte(loc.add(i)) & 0xff) != expected[i])
                throw new IllegalStateException("Original instruction differs at " + loc.add(i));
        }
    }
    private void preflight() throws Exception {
        if (!currentProgram.getName().equalsIgnoreCase("i76.exe") ||
            currentProgram.getImageBase().getOffset()!=0x00400000L)
            throw new IllegalStateException("Load original i76.exe at image base 00400000");
        if (!EXPECTED_MD5.equalsIgnoreCase(currentProgram.getExecutableMD5()))
            throw new IllegalStateException("Unexpected executable MD5: " +
                currentProgram.getExecutableMD5());
        verifyBytes(0x00415872L,0xF6,0x85,0x54,0x04,0x00,0x00,0x20);
        verifyBytes(0x0040A338L,0x0F,0x85,0xA1,0x03,0x00,0x00);
        verifyBytes(0x0040A64CL,0xEB,0x05);
        verifyBytes(0x004155F0L,0xFF,0x05,0x50,0x45,0x52,0x00);
        FunctionManager fm = currentProgram.getFunctionManager();
        Function f = fm.getFunctionAt(a("0046A7F0"));
        if (f==null || f.getBody().getNumAddresses()!=144)
            throw new IllegalStateException("v71 function-body repair not present");
        String[][] renamed = {
            {"004587D0", "clear_world_object_subtree_status_flags_recursive"},
            {"00458860", "clear_world_object_and_descendant_status_flags"}
        };
        for (String[] pair:renamed) {
            f = fm.getFunctionAt(a(pair[0]));
            if (f==null || !pair[1].equals(f.getName()))
                throw new IllegalStateException("v72 rename missing: " + pair[0]);
        }
        Listing listing = currentProgram.getListing();
        for (String[] pair:REQUIRED_CALLS) {
            Instruction ins = listing.getInstructionAt(a(pair[0]));
            if (ins==null)
                throw new IllegalStateException("No instruction at " + pair[0]);
            boolean verified = false;
            for (Reference r:ins.getReferencesFrom()) {
                if (r.getReferenceType().isCall() && r.getToAddress().equals(a(pair[1]))) {
                    verified = true;
                    break;
                }
            }
            if (!verified) throw new IllegalStateException(
                "Required direct scheduler call not resolved: " + pair[0] +
                " -> " + pair[1]);
        }
        if (!currentProgram.getMemory().contains(toAddr(COUNTER_ADDRESS)))
            throw new IllegalStateException("Damage event epoch address is unmapped");
    }
    private TreeMap<String,Function> getFocus(Path dir) throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        TreeMap<String,Function> selected = new TreeMap<>();
        try (BufferedWriter out=output(dir,"i76_v74_fsm_functions.tsv")) {
            row(out,"entry","role","name","body_bytes","body_ranges");
            for (String[] target:FOCUS) {
                monitor.checkCancelled();
                Function f = fm.getFunctionAt(a(target[0]));
                if (f==null) throw new IllegalStateException(
                    "Missing required FSM function " + target[0]);
                selected.put(f.getEntryPoint().toString(),f);
                row(out,f.getEntryPoint(),target[1],f.getName(),
                    f.getBody().getNumAddresses(),f.getBody());
            }
        }
        return selected;
    }
    private void exportCallFlow(Path dir,TreeMap<String,Function> selected)
            throws Exception {
        Listing listing=currentProgram.getListing();
        FunctionManager fm=currentProgram.getFunctionManager();
        ReferenceManager refs=currentProgram.getReferenceManager();
        try (BufferedWriter out=output(dir,"i76_v74_fsm_calls.tsv")) {
            row(out,"direction","focus_entry","focus_name","from_address",
                "reference_type","to_address","other_function");
            for (Function f:selected.values()) {
                monitor.checkCancelled();
                ReferenceIterator incoming=refs.getReferencesTo(f.getEntryPoint());
                while(incoming.hasNext()) {
                    Reference r=incoming.next();
                    if(!r.getReferenceType().isCall()) continue;
                    Function other=fm.getFunctionContaining(r.getFromAddress());
                    row(out,"IN",f.getEntryPoint(),f.getName(),r.getFromAddress(),
                        r.getReferenceType(),r.getToAddress(),
                        other==null?"":other.getName());
                }
                InstructionIterator it=listing.getInstructions(f.getBody(),true);
                while(it.hasNext()) {
                    Instruction ins=it.next();
                    for (Reference r:ins.getReferencesFrom()) {
                        if(!r.getReferenceType().isCall()) continue;
                        Function other=fm.getFunctionContaining(r.getToAddress());
                        row(out,"OUT",f.getEntryPoint(),f.getName(),r.getFromAddress(),
                            r.getReferenceType(),r.getToAddress(),
                            other==null?"":other.getName());
                    }
                }
            }
        }
    }
    private void exportCounterRefs(Path dir) throws Exception {
        FunctionManager fm=currentProgram.getFunctionManager();
        Listing listing=currentProgram.getListing();
        ReferenceManager refs=currentProgram.getReferenceManager();
        try (BufferedWriter out=output(dir,"i76_v74_fsm_epoch_xrefs.tsv")) {
            row(out,"counter_address","from","function_entry","function_name",
                "ref_type","instruction","note");
            ReferenceIterator it=refs.getReferencesTo(toAddr(COUNTER_ADDRESS));
            int rows=0;
            while(it.hasNext()) {
                Reference ref=it.next();
                Function f=fm.getFunctionContaining(ref.getFromAddress());
                Instruction ins=listing.getInstructionContaining(ref.getFromAddress());
                row(out,toAddr(COUNTER_ADDRESS),ref.getFromAddress(),
                    f==null?"":f.getEntryPoint(),f==null?"":f.getName(),
                    ref.getReferenceType(),ins==null?"":ins,
                    "static direct xref only; indirect references excluded");
                rows++;
            }
            if(rows==0) throw new IllegalStateException("No counter references found");
        }
    }
    private void exportWindows(Path dir) throws Exception {
        Listing listing=currentProgram.getListing();
        FunctionManager fm=currentProgram.getFunctionManager();
        try(BufferedWriter out=output(dir,"i76_v74_fsm_windows.tsv")) {
            row(out,"window","address","function_entry","mnemonic",
                "instruction","outgoing_call_targets");
            for(String[] win:WINDOWS) {
                monitor.checkCancelled();
                InstructionIterator it=listing.getInstructions(
                    new AddressSet(a(win[0]),a(win[1])),true);
                while(it.hasNext()) {
                    Instruction ins=it.next();
                    Function f=fm.getFunctionContaining(ins.getAddress());
                    StringBuilder targets=new StringBuilder();
                    for(Reference r:ins.getReferencesFrom()) {
                        if(!r.getReferenceType().isCall()) continue;
                        if(targets.length()>0) targets.append(";");
                        targets.append(r.getToAddress());
                    }
                    row(out,win[2],ins.getAddress(),
                        f==null?"":f.getEntryPoint(),ins.getMnemonicString(),ins,
                        targets);
                }
            }
        }
    }
    private void exportDecompile(Path dir,TreeMap<String,Function> selected)
            throws Exception {
        DecompInterface di=new DecompInterface();
        if(!di.openProgram(currentProgram))
            throw new IllegalStateException("Decompiler cannot open i76.exe");
        try(BufferedWriter out=output(dir,"i76_v74_fsm_decompiled.txt")) {
            out.write("I76 v74 FSM event epoch, scheduler and VM executor; static evidence only\n");
            for(Map.Entry<String,Function> entry:selected.entrySet()) {
                monitor.checkCancelled();
                Function f=entry.getValue();
                out.write("\n===== " + f.getEntryPoint() + " " + f.getName()+" =====\n");
                DecompileResults res=di.decompileFunction(f,90,monitor);
                if(res!=null && res.decompileCompleted() &&
                    res.getDecompiledFunction()!=null)
                    out.write(res.getDecompiledFunction().getC());
                else
                    out.write("DECOMPILE FAILED: " + (res==null?"null":cell(res.getErrorMessage())));
                out.write("\n");
            }
        } finally {
            di.dispose();
        }
    }
    @Override
    public void run() throws Exception {
        preflight();
        Path dir=Paths.get(OUTPUT_DIR);
        Files.createDirectories(dir);
        TreeMap<String,Function> chosen=getFocus(dir);
        exportCounterRefs(dir);
        exportCallFlow(dir,chosen);
        exportWindows(dir);
        exportDecompile(dir,chosen);
        println("I76 v74: scheduler/epoch export complete; " + chosen.size() +
            " functions. No Ghidra state changed. Output: " + dir);
    }
}
