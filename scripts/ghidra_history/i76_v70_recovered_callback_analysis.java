
//@category I76
// i76_v70_recovered_callback_analysis.java
//
// Original Interstate '76 executable.
// Conservative recovered-callback naming and boundary audit.
//
// APPLY    = guarded renames and read-only evidence export
// DRY_RUN  = read-only evidence export
// ROLLBACK = restore names from the table below
//
// Does not define, delete, resize, or disassemble functions.

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;

import java.nio.file.*;
import java.io.*;
import java.util.*;

public class i76_v70_recovered_callback_analysis
    extends GhidraScript {

    private static final String MODE = "APPLY";

    private static final String OUTPUT =
        "/media/neon-remote/prj/i76/scratch_data/";

    private static final String EXPECTED_MD5 =
        "a640ea0097dbb62e0c77b7f2847c7161";

    // Address, expected current name, proposed name.
    // Class IDs are deliberately retained where the specific
    // retail/gameplay object type is not yet established.
    private static final String[][] RENAMES = {
        {"00462580", "FUN_00462580",
            "allocate_class_08_vehicle_runtime_and_aux_state"},
        {"004628C0", "FUN_004628c0",
            "forward_class_08_09_vehicle_velocity_copy"},
        {"00463980", "FUN_00463980",
            "invoke_force_feedback_for_flagged_vehicle"},
        {"00467700", "FUN_00467700",
            "apply_class_18_damage_and_zero_runtime_state"},
        {"0046A7C0", "FUN_0046a7c0",
            "allocate_class_16_damage_runtime"},
        {"0046A7F0", "FUN_0046a7f0",
            "apply_class_16_damage_and_update_integrity"},
        {"0046B780", "FUN_0046b780",
            "allocate_class_09_vehicle_runtime"},
        {"0046B7D0", "FUN_0046b7d0",
            "initialize_class_09_runtime_and_player_display"},
        {"0046B8B0", "FUN_0046b8b0",
            "update_class_09_vehicle_dynamics_and_explosion"},
        {"0046BB90", "FUN_0046bb90",
            "apply_class_09_damage_and_begin_explosion"},
        {"0046BCC0", "FUN_0046bcc0",
            "copy_class_09_vehicle_transform_matrix"},
        {"0046BCF0", "FUN_0046bcf0",
            "forward_class_09_collision_damage_response"},
        {"0046D160", "FUN_0046d160",
            "allocate_class_07_damage_motion_runtime"},
        {"0046D210", "FUN_0046d210",
            "initialize_class_07_runtime_from_object_tree"},
        {"0046D2E0", "FUN_0046d2e0",
            "update_class_07_interpolated_world_position"},
        {"0046D590", "FUN_0046d590",
            "apply_class_07_damage_and_destroy_geometry"},
        {"0046D6C0", "FUN_0046d6c0",
            "copy_default_class_07_transform_matrix"},
        {"0046E1A0", "FUN_0046e1a0",
            "release_vehicle_attachment_effect_record"},
        {"0046F650", "FUN_0046f650",
            "allocate_class_0a_damage_motion_runtime"},
        {"0046F6B0", "FUN_0046f6b0",
            "update_class_0a_motion_transform"},
        {"0046F700", "FUN_0046f700",
            "apply_class_0a_damage_and_destroy_geometry"},
        {"0046F7F0", "FUN_0046f7f0",
            "zero_class_07_0a_motion_output_fields"},
        {"0046F840", "FUN_0046f840",
            "copy_class_0a_transform_with_runtime_position"},
        {"0046F9A0", "FUN_0046f9a0",
            "apply_class_04_damage_and_unregister_object"},
        {"004A2440", "FUN_004a2440",
            "recycle_chunk_manager_runtime_record"}
    };

    // Additional entries generated during analysis.
    // These are AUDIT ONLY until boundaries are verified.
    private static final String[] BOUNDARY_REVIEW = {
        "0046251B",
        "004628A9",
        "0046A80C",
        "0046A831",
        "0046A858",
        "0046A860",
        "0046BB78",
        "0046BCAA",
        "0046D17C",
        "0046D575",
        "0046D57B",
        "0046D6B1",
        "0046E08E",
        "0046F5C9",
        "0046F5EE",
        "0046F600",
        "0046F610",
        "0046F63A",
        "0046F665",
        "004A2016",
        "004A20C2",
        "004A2189",
        "004A2249"
    };

    private static final String[] OTHER_REVIEW = {
        "00470CA0",  // PIX resource comparator
        "004587D0",  // suspected recursive flag clearer
        "00458860",  // suspected object flag clearer
        "004A2000",  // suspicious contiguous function body
        "004A2070"   // suspicious contiguous function body
    };

    private Address at(String s) {
        return toAddr(Long.parseLong(s, 16));
    }

    private long read32(String s) throws Exception {
        return currentProgram.getMemory()
            .getInt(at(s)) & 0xffffffffL;
    }

    private String clean(Object o) {
        if (o == null) return "";
        return o.toString().replace('\t', ' ')
            .replace('\n', ' ').replace('\r', ' ');
    }

    private void row(BufferedWriter w, Object... cells)
            throws Exception {

            for (int i = 0; i < cells.length; i++) {
                if (i > 0) w.write('\t');
                w.write(clean(cells[i]));
            }
            w.newLine();
    }

    private void verify() throws Exception {
        if (currentProgram.getImageBase()
                .getOffset() != 0x400000L)
            throw new IllegalStateException(
                    "Unexpected executable image base");

        String md5 = currentProgram.getExecutableMD5();
        if (md5 != null && !md5.isEmpty() &&
                !md5.equalsIgnoreCase("unknown") &&
                !md5.equalsIgnoreCase(EXPECTED_MD5))
            throw new IllegalStateException(
                    "Executable MD5 mismatch");

        if (read32("004F77A4") != 0x00463A80L ||
                read32("004F77D8") != 0x0046BB90L ||
                read32("004F7840") != 0x0046D590L ||
                read32("004F7874") != 0x0046F700L ||
                read32("004F7770") != 0x0046F9A0L)
            throw new IllegalStateException(
                    "Class callback table mismatch");
    }

    private void exportRenameDecisions(
            BufferedWriter w) throws Exception {

        FunctionManager fm =
            currentProgram.getFunctionManager();

        row(w, "address", "previous", "proposed",
                "decision");

        for (String[] item : RENAMES) {
            monitor.checkCancelled();

            Function f = fm.getFunctionAt(at(item[0]));
            if (f == null) {
                row(w, item[0], "<missing>",
                        item[2], "MISSING_FUNCTION");
                continue;
            }

            boolean undo = MODE.equals("ROLLBACK");
            String expected = undo ? item[2] : item[1];
            String target = undo ? item[1] : item[2];
            String actual = f.getName();

            if (actual.equals(target)) {
                row(w, item[0], actual,
                        target, "ALREADY_SET");
                continue;
            }

            if (!actual.equals(expected)) {
                row(w, item[0], actual,
                        target, "SKIPPED_NAME_MISMATCH");
                continue;
            }

            if (MODE.equals("DRY_RUN")) {
                row(w, item[0], actual,
                        target, "WOULD_RENAME");
                continue;
            }

            try {
                f.setName(target, SourceType.USER_DEFINED);
                row(w, item[0], actual, target,
                        undo ? "RESTORED" : "RENAMED");
            } catch (Exception ex) {
                row(w, item[0], actual, target,
                        "FAILED: " + ex);
            }
        }
            }

    private Function priorFunction(Address address) {
        Function previous = null;
        FunctionIterator it =
            currentProgram.getFunctionManager()
            .getFunctions(true);

        while (it.hasNext()) {
            Function f = it.next();
            if (f.getEntryPoint().compareTo(address) >= 0)
                break;
            previous = f;
        }
        return previous;
    }

    private String bytes(Address a, int length) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < length; i++) {
            try {
                int b = currentProgram.getMemory()
                    .getByte(a.add(i)) & 0xff;

                if (i > 0) sb.append(' ');
                sb.append(String.format(
                            Locale.ROOT, "%02X", b));
            } catch (Exception ex) {
                break;
            }
        }
        return sb.toString();
    }

    private int referenceCount(Address a) {
        ReferenceIterator it =
            currentProgram.getReferenceManager()
            .getReferencesTo(a);

        int count = 0;
        while (it.hasNext()) {
            it.next();
            count++;
        }
        return count;
    }

    private void exportBoundaryAudit(
            BufferedWriter w) throws Exception {

        row(w, "address", "current_name",
                "status", "body_range", "body_bytes",
                "previous_function", "previous_end",
                "gap_bytes", "incoming_references",
                "entry_instruction", "first_32_bytes");

        LinkedHashSet<String> all =
            new LinkedHashSet<String>();

        Collections.addAll(all, BOUNDARY_REVIEW);
        Collections.addAll(all, OTHER_REVIEW);

        FunctionManager fm =
            currentProgram.getFunctionManager();
        Listing listing = currentProgram.getListing();

        for (String value : all) {
            monitor.checkCancelled();

            Address a = at(value);
            Function f = fm.getFunctionAt(a);
            Function containing =
                fm.getFunctionContaining(a);
            Function before = priorFunction(a);

            String status =
                f != null ? "FUNCTION_ENTRY" :
                containing != null ? "INSIDE_FUNCTION" :
                listing.getInstructionAt(a) != null
                ? "INSTRUCTION_NO_FUNCTION" :
                "UNDEFINED_OR_DATA";

            String range = "";
            long bodySize = 0;

            if (f != null) {
                range = f.getBody().getMinAddress()
                    + "-" + f.getBody().getMaxAddress();
                bodySize = f.getBody().getNumAddresses();
            }

            String priorEnd = "";
            String gap = "";

            if (before != null) {
                Address end =
                    before.getBody().getMaxAddress();

                priorEnd = end.toString();

                gap = Long.toString(
                        a.getOffset() - end.getOffset() - 1);
            }

            Instruction ins = listing.getInstructionAt(a);

            row(w, value,
                    f == null ? "<not defined>" : f.getName(),
                    status, range, bodySize,
                    before == null ? "" :
                    before.getEntryPoint()
                    + ":" + before.getName(),
                    priorEnd, gap, referenceCount(a),
                    ins == null ? "" : ins.toString(),
                    bytes(a, 32));
        }
            }

    private LinkedHashSet<String> reviewTargets() {
        LinkedHashSet<String> result =
            new LinkedHashSet<String>();

        Collections.addAll(result, BOUNDARY_REVIEW);
        Collections.addAll(result, OTHER_REVIEW);
        return result;
    }

    private void exportAssembly(BufferedWriter w)
            throws Exception {

            FunctionManager fm =
                currentProgram.getFunctionManager();
            Listing listing = currentProgram.getListing();

            for (String value : reviewTargets()) {
                monitor.checkCancelled();

                Address a = at(value);
                Function f = fm.getFunctionAt(a);

                w.write("\n===== " + value + " =====\n");

                if (f != null) {
                    w.write(f.getName() + "\n");

                    InstructionIterator it =
                        listing.getInstructions(f.getBody(), true);

                    int n = 0;
                    while (it.hasNext() && n < 3000) {
                        Instruction ins = it.next();

                        w.write(ins.getAddress()
                                + "\t"
                                + bytes(ins.getAddress(),
                                    ins.getLength())
                                + "\t" + ins + "\n");
                        n++;
                    }
                } else {
                    w.write("NO FUNCTION ENTRY\n");

                    Instruction ins =
                        listing.getInstructionAt(a);

                    int n = 0;
                    while (ins != null && n < 80 &&
                            ins.getAddress().getOffset()
                            < a.getOffset() + 0x180) {

                        w.write(ins.getAddress()
                                + "\t"
                                + bytes(ins.getAddress(),
                                    ins.getLength())
                                + "\t" + ins + "\n");

                        if (ins.getMnemonicString()
                                .equalsIgnoreCase("RET"))
                            break;

                        ins = listing.getInstructionAfter(
                                ins.getAddress());
                        n++;
                            }
                }
            }
    }

    private void exportDecompilation(BufferedWriter w)
            throws Exception {

            FunctionManager fm =
                currentProgram.getFunctionManager();

            DecompInterface decompiler =
                new DecompInterface();

            boolean opened =
                decompiler.openProgram(currentProgram);

            try {
                for (String value : reviewTargets()) {
                    monitor.checkCancelled();

                    w.write("\n===== " + value + " =====\n");

                    Function f = fm.getFunctionAt(at(value));

                    if (f == null) {
                        w.write("NO FUNCTION ENTRY\n");
                        continue;
                    }

                    w.write(f.getName() + "\n");

                    if (!opened) {
                        w.write("DECOMPILER UNAVAILABLE\n");
                        continue;
                    }

                    try {
                        DecompileResults r =
                            decompiler.decompileFunction(
                                    f, 60, monitor);

                        if (r != null &&
                                r.decompileCompleted() &&
                                r.getDecompiledFunction() != null)
                            w.write(
                                    r.getDecompiledFunction().getC());
                        else
                            w.write("DECOMPILATION FAILED\n");

                    } catch (Exception ex) {
                        w.write("ERROR: " + ex + "\n");
                    }
                    w.write("\n");
                }
            } finally {
                decompiler.dispose();
            }
    }

    @Override
    public void run() throws Exception {

        if (!MODE.equals("APPLY") &&
                !MODE.equals("DRY_RUN") &&
                !MODE.equals("ROLLBACK"))
            throw new IllegalStateException("Invalid MODE");

        verify();

        Path dir = Paths.get(OUTPUT);
        Files.createDirectories(dir);

        Path decisions = dir.resolve(
                "i76_v70_rename_decisions.tsv");
        Path boundary = dir.resolve(
                "i76_v70_boundary_audit.tsv");
        Path assembly = dir.resolve(
                "i76_v70_boundary_assembly.txt");
        Path decompiled = dir.resolve(
                "i76_v70_boundary_decompiled.txt");

        try (BufferedWriter w =
                Files.newBufferedWriter(decisions)) {
            exportRenameDecisions(w);
                }

        try (BufferedWriter w =
                Files.newBufferedWriter(boundary)) {
            exportBoundaryAudit(w);
                }

        try (BufferedWriter w =
                Files.newBufferedWriter(assembly)) {
            exportAssembly(w);
                }

        try (BufferedWriter w =
                Files.newBufferedWriter(decompiled)) {
            exportDecompilation(w);
                }

        println("I76 v70 complete.");
        println("Mode: " + MODE);
        println("Renames: " + decisions);
        println("Boundary audit: " + boundary);
        println("Assembly: " + assembly);
        println("Decompilation: " + decompiled);
    }
}

