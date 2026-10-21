
//@category I76
// Interstate '76 - Class Dispatch and Object Lifetime v67
//
// High-confidence semantic corrections.
// Full class callback descriptor inventory.
// World-object/vehicle status flag writer inventory.
// Focused decompilation and assembly export.
//
// Modes: APPLY, DRY_RUN, ROLLBACK.
// No executable bytes or function boundaries modified.

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.mem.Memory;

import java.io.BufferedWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Locale;

public class I76_Class_Damage_V67 extends GhidraScript {

    private static final String MODE = "APPLY";

    private static final String OUTPUT_DIRECTORY =
        "/media/neon-remote/prj/i76/scratch_data/";

    private static final String EXPECTED_MD5 =
        "a640ea0097dbb62e0c77b7f2847c7161";

    // Address / exact previous name / replacement / evidence
    private static final String[][] RENAMES = {
        {
            "00458810",
            "get_world_object_class_id",
            "or_world_object_and_descendant_status_flags",
            "ORs supplied mask into object+10 and "
                + "propagates it to the child subtree"
        },
        {
            "00458790",
            "world_object_bounds_context_helper_00458790",
            "or_world_object_subtree_status_flags_recursive",
            "Recursively traverses child and sibling links "
                + "and ORs mask into node+10"
        },
        {
            "00457420",
            "entity_instance_id_lookup_or_update",
            "unregister_active_world_object_entry_and_release",
            "Invokes unregister callbacks, releases object "
                + "reference, frees entry storage and clears slot"
        },
        {
            "004620A0",
            "has_world_object_class_damage_handler",
            "initialize_runtime_node_sentinel_fields",
            "Writes -1 to node+68 and zero to node+70; "
                + "does not test or return handler availability"
        },
        {
            "00466AC0",
            "vehicle_damage_part_state_context_helper_00466ac0",
            "get_vehicle_damage_child_primary_condition",
            "Reads class-specific first condition field "
                + "from indexed child object at runtime+3A8"
        },
        {
            "00466B70",
            "vehicle_damage_part_state_context_helper_00466b70",
            "get_vehicle_damage_child_secondary_condition",
            "Reads class-specific second condition field "
                + "from indexed child object at runtime+3A8"
        },
        {
            "0046AC50",
            "apply_vehicle_damage_context_and_destruction",
            "apply_destructible_world_object_damage_and_effects",
            "Separate class-descriptor callback handling "
                + "destructible world objects and effect spawning"
        },
        {
            "00463A80",
            "vehicle_class_damage_or_release_callback",
            "apply_vehicle_class_damage_and_destruction",
            "Vehicle class damage callback at table "
                + "004F77A4; handles part damage and death"
        }
    };

    private static final String[] FOCUS = {
        "00462040",
        "004620A0",
        "00463A80",
        "0046AC50",
        "00458810",
        "00458790",
        "00457420",
        "004572B0",
        "004652B0",
        "00466AC0",
        "00466B70",
        "004157A0",
        "004A7C80",
        "004A8240"
    };

    private Address at(String value) {
        return toAddr(Long.parseLong(value, 16));
    }

    private Address at(long value) {
        return toAddr(value);
    }

    private String hex(long value) {
        return String.format(
                Locale.ROOT, "%08X", value & 0xffffffffL);
    }

    private String clean(Object value) {
        return value == null ? "" :
            value.toString()
            .replace('\t', ' ')
            .replace('\r', ' ')
            .replace('\n', ' ');
    }

    private void row(BufferedWriter out, Object... cells)
            throws Exception {

            for (int i = 0; i < cells.length; i++) {
                if (i != 0) out.write('\t');
                out.write(clean(cells[i]));
            }

            out.newLine();
    }

    private long readDword(long address) throws Exception {
        return currentProgram.getMemory()
            .getInt(at(address)) & 0xffffffffL;
    }

    private void checkBytes(
            String address, int... expected)
            throws Exception {

            Address a = at(address);

            for (int i = 0; i < expected.length; i++) {
                int actual = currentProgram.getMemory()
                    .getByte(a.add(i)) & 255;

                if (actual != expected[i]) {
                    throw new IllegalStateException(
                            "Instruction mismatch at " + a.add(i));
                }
            }
            }

    private void verify() throws Exception {
        if (currentProgram.getImageBase()
                .getOffset() != 0x400000L) {
            throw new IllegalStateException(
                    "Unexpected executable image base");
                }

        String md5 = currentProgram.getExecutableMD5();

        if (md5 != null &&
                !md5.isEmpty() &&
                !md5.equalsIgnoreCase("unknown") &&
                !md5.equalsIgnoreCase(EXPECTED_MD5)) {

            throw new IllegalStateException(
                    "Unexpected executable MD5: " + md5);
                }

        checkBytes("00462080",
                0x8B, 0x0C, 0x8D, 0x08, 0x77, 0x4F, 0x00);

        checkBytes("00462096", 0xFF, 0xD1);

        checkBytes("00458824", 0x0B, 0xCF);

        checkBytes("00458828", 0x89, 0x48, 0x10);

        checkBytes("004652F3",
                0x89, 0x81, 0x54, 0x04, 0x00, 0x00);

        checkBytes("004620A4",
                0xC7, 0x40, 0x68,
                0xFF, 0xFF, 0xFF, 0xFF);

        if (readDword(0x004F77A4L) != 0x00463A80L) {
            throw new IllegalStateException(
                    "Vehicle class callback pointer mismatch");
        }

        if (readDword(0x004F773CL) != 0x0046AC50L) {
            throw new IllegalStateException(
                    "Destructible class callback pointer mismatch");
        }
    }

    private void annotate(Function f, String evidence) {
        String marker = "[I76 v67] " + evidence;
        String old = f.getComment();

        if (old == null) old = "";

        if (!old.contains(marker)) {
            f.setComment(old.isEmpty()
                    ? marker
                    : old + "\n" + marker);
        }
    }

    private void exportRenames(
            FunctionManager fm,
            BufferedWriter out) throws Exception {

        row(out, "address", "previous_name",
                "proposed_name", "decision", "evidence");

        for (String[] item : RENAMES) {
            monitor.checkCancelled();

            Function f = fm.getFunctionAt(at(item[0]));

            if (f == null) {
                row(out, item[0], "<undefined>",
                        item[2], "MISSING_FUNCTION", item[3]);
                continue;
            }

            boolean undo = MODE.equals("ROLLBACK");
            String expected = undo ? item[2] : item[1];
            String replacement = undo ? item[1] : item[2];
            String actual = f.getName();

            if (actual.equals(replacement)) {
                row(out, item[0], actual, replacement,
                        "ALREADY_SET", item[3]);
                continue;
            }

            if (!actual.equals(expected)) {
                row(out, item[0], actual, replacement,
                        "SKIPPED_NAME_MISMATCH", item[3]);
                continue;
            }

            if (MODE.equals("DRY_RUN")) {
                row(out, item[0], actual, replacement,
                        "WOULD_RENAME", item[3]);
                continue;
            }

            try {
                f.setName(
                        replacement, SourceType.USER_DEFINED);

                if (!undo) annotate(f, item[3]);

                row(out, item[0], actual, replacement,
                        undo ? "RESTORED" : "RENAMED",
                        item[3]);

            } catch (Exception ex) {
                row(out, item[0], actual, replacement,
                        "FAILED", ex.toString());
            }
        }
            }

    private void exportClassTable(
            FunctionManager fm,
            BufferedWriter out) throws Exception {

        row(out, "index", "descriptor_address",
                "class_id", "damage_callback_slot",
                "callback_address", "callback_name",
                "raw_13_dwords");

        // 27 descriptors, each 0x34 bytes.
        // Descriptor base = 004F76E0.
        // Callback is at descriptor + 0x28.
        // End of descriptor region = 004F7C5C.

        final long base = 0x004F76E0L;
        final int count = 27;
        final int stride = 0x34;

        for (int i = 0; i < count; i++) {
            monitor.checkCancelled();

            long descriptor = base + i * stride;
            long classId = readDword(descriptor);
            long callbackSlot = descriptor + 0x28;
            long callback = readDword(callbackSlot);

            Function f = callback == 0 ? null :
                fm.getFunctionAt(at(callback));

            StringBuilder raw = new StringBuilder();

            for (int j = 0; j < 13; j++) {
                if (j > 0) raw.append(" ");
                raw.append(hex(readDword(
                                descriptor + j * 4)));
            }

            row(out, i, hex(descriptor),
                    hex(classId), hex(callbackSlot),
                    hex(callback),
                    callback == 0 ? "<none>" :
                    f == null ? "<unresolved>" : f.getName(),
                    raw);
        }
            }

    private void exportFlagWriterCandidates(
            FunctionManager fm,
            Listing listing,
            BufferedWriter out) throws Exception {

        row(out, "instruction_address",
                "containing_function", "offset_category",
                "mnemonic", "destination_operand",
                "instruction");

        InstructionIterator it =
            listing.getInstructions(true);

        while (it.hasNext()) {
            monitor.checkCancelled();

            Instruction ins = it.next();

            if (ins.getNumOperands() < 1) continue;

            String mnemonic = ins.getMnemonicString()
                .toUpperCase(Locale.ROOT);

            // Write-capable instructions only.
            if (!(mnemonic.equals("MOV") ||
                        mnemonic.equals("OR") ||
                        mnemonic.equals("AND") ||
                        mnemonic.equals("XOR") ||
                        mnemonic.equals("ADD") ||
                        mnemonic.equals("SUB") ||
                        mnemonic.equals("INC") ||
                        mnemonic.equals("DEC") ||
                        mnemonic.equals("BTS") ||
                        mnemonic.equals("BTR"))) {
                continue;
                        }

            String destination =
                ins.getDefaultOperandRepresentation(0)
                .toLowerCase(Locale.ROOT)
                .replace(" ", "");

            if (!destination.contains("[")) continue;

            String category = "";

            if (destination.contains("+0x454]")) {
                category = "POSSIBLE_VEHICLE_FLAGS_454";
            } else if (destination.contains("+0x10]")) {
                category = "POSSIBLE_WORLD_OBJECT_FLAGS_10";
            }

            if (category.isEmpty()) continue;

            Function owner = fm.getFunctionContaining(
                    ins.getAddress());

            row(out, ins.getAddress(),
                    owner == null ? "<undefined>" :
                    owner.getName(),
                    category, mnemonic, destination,
                    ins.toString());
        }
            }

    private void exportDecompilation(
            FunctionManager fm,
            BufferedWriter out) throws Exception {

        DecompInterface decompiler =
            new DecompInterface();

        boolean opened =
            decompiler.openProgram(currentProgram);

        try {
            for (String address : FOCUS) {
                monitor.checkCancelled();

                out.write("\n===== " + address
                        + " =====\n");

                Function f = fm.getFunctionAt(
                        at(address));

                if (f == null) {
                    out.write("NO FUNCTION DEFINED\n");
                    continue;
                }

                out.write(f.getName() + "\n");

                if (!opened) {
                    out.write(
                            "DECOMPILER UNAVAILABLE\n");
                    continue;
                }

                try {
                    DecompileResults result =
                        decompiler.decompileFunction(
                                f, 60, monitor);

                    if (result != null &&
                            result.decompileCompleted() &&
                            result.getDecompiledFunction()
                            != null) {

                        out.write(
                                result.getDecompiledFunction()
                                .getC());
                    } else {
                        out.write(
                                "DECOMPILATION FAILED\n");
                    }

                } catch (Exception ex) {
                    out.write(
                            "DECOMPILER ERROR: "
                            + ex.toString() + "\n");
                }

                out.write("\n");
            }
        } finally {
            decompiler.dispose();
        }
            }

    @Override
    public void run() throws Exception {
        if (!MODE.equals("APPLY") &&
                !MODE.equals("DRY_RUN") &&
                !MODE.equals("ROLLBACK")) {
            throw new IllegalStateException(
                    "Invalid MODE: " + MODE);
                }

        verify();

        Path directory = Paths.get(OUTPUT_DIRECTORY);
        Files.createDirectories(directory);

        if (!Files.isWritable(directory)) {
            throw new IllegalStateException(
                    "Output directory is not writable: "
                    + directory);
        }

        FunctionManager fm =
            currentProgram.getFunctionManager();

        Listing listing =
            currentProgram.getListing();

        Path decisions = directory.resolve(
                "i76_v67_name_decisions.tsv");

        Path table = directory.resolve(
                "i76_v67_class_callbacks.tsv");

        Path flags = directory.resolve(
                "i76_v67_status_flag_candidates.tsv");

        Path decompiled = directory.resolve(
                "i76_v67_focus_decompiled.txt");

        try (BufferedWriter out =
                Files.newBufferedWriter(decisions)) {
            exportRenames(fm, out);
                }

        try (BufferedWriter out =
                Files.newBufferedWriter(table)) {
            exportClassTable(fm, out);
                }

        try (BufferedWriter out =
                Files.newBufferedWriter(flags)) {
            exportFlagWriterCandidates(
                    fm, listing, out);
                }

        try (BufferedWriter out =
                Files.newBufferedWriter(decompiled)) {
            exportDecompilation(fm, out);
                }

        println("I76 v67 completed.");
        println("Mode: " + MODE);
        println("Output directory: " + directory);
        println("Renames: " + decisions);
        println("Class descriptors: " + table);
        println("Flag candidates: " + flags);
        println("Decompiler output: " + decompiled);
    }
}

