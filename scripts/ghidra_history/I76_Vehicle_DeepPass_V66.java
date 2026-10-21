
//@category I76
// Interstate '76 v66 - Comprehensive Vehicle Deep Pass
//
// Conservative symbol corrections and additional analysis.
// Original executable only.
//
// Modes:
//   APPLY    - apply exact-name renames and comments
//   DRY_RUN  - export without modifying Ghidra
//   ROLLBACK - restore previous names from this script
//
// The script does not change function boundaries, prototypes,
// structures, calling conventions or executable bytes.

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;

import java.io.BufferedWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Locale;

public class I76_Vehicle_DeepPass_V66
    extends GhidraScript {

    private static final String MODE = "APPLY";

    private static final String MD5 =
        "a640ea0097dbb62e0c77b7f2847c7161";

    // Address / current exact name / replacement / evidence
    private static final String[][] RENAMES = {
        {
            "004644D0",
            "vehicle_damage_network_context_helper_004644d0",
            "serialize_vehicle_network_state_and_damage",
            "Constructs vehicle network snapshot, including "
                + "damage flags, condition tiers and part states"
        },
        {
            "004A8240",
            "weapon_ordnance_query_context_helper_004a8240",
            "dispatch_direct_damage_and_record_source_event",
            "Dispatches target-class damage through 00462040, "
                + "then conditionally records source via 004157A0"
        },
        {
            "00466CA0",
            "vehicle_damage_texture_dirty_context_helper_00466ca0",
            "update_vehicle_damage_smoke_emitter_for_integrity",
            "Manages smoke emitter registration, mode and removal "
                + "according to vehicle integrity"
        },
        {
            "00466C20",
            "vehicle_damage_threshold_context_helper_00466c20",
            "compute_vehicle_component_minimum_condition_ratio",
            "Returns minimum of two component-condition ratios "
                + "from runtime arrays"
        },
        {
            "00457A90",
            "entity_instance_table_context_helper_00457a90",
            "collect_visible_world_objects_for_render_buckets",
            "Traverses active world objects, transforms, "
                + "culls and submits render primitives"
        }
    };

    // Address / evidence annotation
    private static final String[][] NOTES = {
        {
            "00465AF0",
            "Verified dead-car flag producer at 00465D68-00465D7F: "
                + "sets runtime+454 bit20; component 6 also sets "
                + "bit4000. Conditional on upstream damage selection."
        },
        {
            "00463A80",
            "Vehicle class callback. Direct calls include "
                + "00465620, 00465AF0, 00466C20, 00466CA0 "
                + "and 00466180. Also coordinates player/network "
                + "destruction consequences."
        },
        {
            "004652B0",
            "Forced destruction intermediary. Directly calls "
                + "00463A80 at 004652F9. Called by FSM destroy "
                + "handler at 0040BA18."
        },
        {
            "00466180",
            "Nonzero second argument initializes destruction, "
                + "timer and explosion effects. Zero argument "
                + "selects subsequent breakup/effects logic."
        },
        {
            "004157A0",
            "Damage source attribution follows class damage "
                + "dispatch at callers 004A821C and 004A8298. "
                + "Dead-car flag+454 bit20 gates A6E0 update."
        },
        {
            "00458810",
            "REVIEW: called with world-object status masks "
                + "including 0x200 in destruction paths. "
                + "Existing getter name requires verification. "
                + "Do not rename without examining implementation."
        },
        {
            "00462040",
            "REVIEW: class-specific damage dispatcher. "
                + "Direct reference to 0046AC50; investigate "
                + "possible indirect class callback dispatch."
        },
        {
            "004A7C80",
            "Acquires temporary target-tree reference, "
                + "dispatches class damage, releases reference, "
                + "then conditionally records damage attribution."
        }
    };

    // Functions for deeper export.
    // These are intentionally concentrated around the
    // remaining uncertain links, not a repeat of all v65.
    private static final String[] ROOTS = {
        "00462040",
        "004620A0",
        "00463A80",
        "004652B0",
        "00458810",
        "00458790",
        "0046AC50",
        "0045ED00",
        "0045EE80",
        "0045EF70",
        "0045F0F0",
        "00466AC0",
        "00466B70",
        "0046D9F0",
        "0046DA30",
        "0046DAF0",
        "00467440",
        "004572B0",
        "00457420",
        "004644D0",
        "004A8240"
    };

    private Address addr(String s) {
        return toAddr(Long.parseLong(s, 16));
    }

    private String clean(Object o) {
        return o == null ? "" :
            o.toString()
            .replace('\t', ' ')
            .replace('\r', ' ')
            .replace('\n', ' ');
    }

    private void row(
            BufferedWriter w, Object... values)
            throws Exception {

            for (int i = 0; i < values.length; i++) {
                if (i > 0) w.write('\t');
                w.write(clean(values[i]));
            }

            w.newLine();
            }

    private void verifyBytes(
            String a, int... expected)
            throws Exception {

            Address p = addr(a);

            for (int i = 0; i < expected.length; i++) {
                int actual = currentProgram.getMemory()
                    .getByte(p.add(i)) & 255;

                if (actual != expected[i]) {
                    throw new IllegalStateException(
                            "Executable signature differs at "
                            + p.add(i));
                }
            }
            }

    private void verifyInstruction(
            String address,
            String mnemonic,
            String fragment) throws Exception {

        Instruction ins = currentProgram.getListing()
            .getInstructionAt(addr(address));

        if (ins == null)
            throw new IllegalStateException(
                    "No instruction at " + address);

        String actual = ins.toString()
            .toLowerCase(Locale.ROOT)
            .replace(" ", "");

        if (!ins.getMnemonicString()
                .equalsIgnoreCase(mnemonic) ||
                !actual.contains(
                    fragment.toLowerCase(Locale.ROOT)
                    .replace(" ", ""))) {

            throw new IllegalStateException(
                    "Unexpected instruction at "
                    + address + ": " + ins);
                    }
            }

    private void verify() throws Exception {
        if (currentProgram.getImageBase()
                .getOffset() != 0x400000L) {
            throw new IllegalStateException(
                    "Unexpected image base");
                }

        String actual = currentProgram
            .getExecutableMD5();

        if (actual != null &&
                !actual.isEmpty() &&
                !actual.equalsIgnoreCase("unknown") &&
                !actual.equalsIgnoreCase(MD5)) {
            throw new IllegalStateException(
                    "Unexpected executable MD5: " + actual);
                }

        verifyBytes("00415872",
                0xF6, 0x85, 0x54, 0x04,
                0x00, 0x00, 0x20);

        verifyInstruction(
                "004A821C", "CALL", "004157a0");

        verifyInstruction(
                "004A8298", "CALL", "004157a0");

        verifyInstruction(
                "00465D68", "OR", "0x4020");
    }

    private void addNote(Function f, String text) {
        String marker = "[I76 v66] " + text;

        String prior = f.getComment();
        if (prior == null) prior = "";

        if (!prior.contains(marker)) {
            f.setComment(
                    prior.isEmpty()
                    ? marker
                    : prior + "\n" + marker);
        }
    }

    private void applyRenames(
            FunctionManager fm,
            BufferedWriter out) throws Exception {

        row(out, "address", "before", "proposed",
                "decision", "evidence");

        for (String[] item : RENAMES) {
            monitor.checkCancelled();

            Function f = fm.getFunctionAt(addr(item[0]));

            if (f == null) {
                row(out, item[0], "<undefined>",
                        item[2], "MISSING", item[3]);
                continue;
            }

            String previous = f.getName();
            boolean rollback = MODE.equals("ROLLBACK");

            String expected =
                rollback ? item[2] : item[1];

            String destination =
                rollback ? item[1] : item[2];

            if (previous.equals(destination)) {
                row(out, item[0], previous,
                        destination, "ALREADY_SET", item[3]);
                continue;
            }

            if (!previous.equals(expected)) {
                row(out, item[0], previous,
                        destination, "SKIPPED_NAME_MISMATCH",
                        item[3]);
                continue;
            }

            if (MODE.equals("DRY_RUN")) {
                row(out, item[0], previous,
                        destination, "WOULD_RENAME", item[3]);
                continue;
            }

            try {
                f.setName(
                        destination, SourceType.USER_DEFINED);

                row(out, item[0], previous,
                        destination,
                        rollback ? "RESTORED" : "RENAMED",
                        item[3]);

            } catch (Exception ex) {
                row(out, item[0], previous,
                        destination, "RENAME_FAILED",
                        ex.toString());
            }
        }
            }

    private void exportAssembly(
            FunctionManager fm,
            Listing listing,
            BufferedWriter out) throws Exception {

        for (String a : ROOTS) {
            monitor.checkCancelled();

            Function f = fm.getFunctionAt(addr(a));

            out.write("\n===== " + a + " =====\n");

            if (f == null) {
                out.write("NO FUNCTION DEFINED\n");
                continue;
            }

            out.write(f.getName() + "\n");

            InstructionIterator iter =
                listing.getInstructions(
                        f.getBody(), true);

            while (iter.hasNext()) {
                monitor.checkCancelled();

                Instruction ins = iter.next();
                StringBuilder bytes =
                    new StringBuilder();

                for (byte b : ins.getBytes()) {
                    bytes.append(
                            String.format("%02X", b & 255));
                }

                out.write(
                        ins.getAddress()
                        + "\t" + bytes
                        + "\t" + ins.toString()
                        + "\n");
            }
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
            for (String a : ROOTS) {
                monitor.checkCancelled();

                out.write(
                        "\n===== " + a + " =====\n");

                Function f = fm.getFunctionAt(addr(a));

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
                            + ex + "\n");
                }

                out.write("\n");
            }
        } finally {
            decompiler.dispose();
        }
            }

    private void exportReferences(
            FunctionManager fm,
            Listing listing,
            BufferedWriter out) throws Exception {

        row(out, "target", "target_name",
                "reference_from", "caller_name",
                "reference_type", "instruction");

        ReferenceManager refs =
            currentProgram.getReferenceManager();

        for (String a : ROOTS) {
            monitor.checkCancelled();

            Address target = addr(a);

            Function f = fm.getFunctionAt(target);

            ReferenceIterator iter =
                refs.getReferencesTo(target);

            while (iter.hasNext()) {
                Reference ref = iter.next();

                Address source = ref.getFromAddress();

                Function caller =
                    fm.getFunctionContaining(source);

                Instruction ins =
                    listing.getInstructionContaining(source);

                row(out,
                        a,
                        f == null ? "<undefined>" :
                        f.getName(),
                        source,
                        caller == null ? "<data or unknown>" :
                        caller.getName(),
                        ref.getReferenceType(),
                        ins == null ? "" : ins.toString());
            }
        }
            }

    private void exportInventory(
            FunctionManager fm,
            BufferedWriter out) throws Exception {

        row(out, "address", "name", "body_bytes");

        FunctionIterator iter =
            fm.getFunctions(true);

        while (iter.hasNext()) {
            monitor.checkCancelled();

            Function f = iter.next();

            row(out,
                    f.getEntryPoint(),
                    f.getName(),
                    f.getBody().getNumAddresses());
        }
            }

    @Override
    public void run() throws Exception {

        if (!MODE.equals("APPLY") &&
                !MODE.equals("DRY_RUN") &&
                !MODE.equals("ROLLBACK")) {
            throw new IllegalStateException(
                    "Invalid mode: " + MODE);
                }

        verify();

        FunctionManager fm =
            currentProgram.getFunctionManager();

        Listing listing =
            currentProgram.getListing();

        Path home = Paths.get(
                System.getProperty("user.home"));

        Path names = home.resolve(
                "i76_v66_name_decisions.tsv");

        Path assembly = home.resolve(
                "i76_v66_deep_assembly.txt");

        Path decompiled = home.resolve(
                "i76_v66_deep_decompiled.txt");

        Path references = home.resolve(
                "i76_v66_target_references.tsv");

        Path inventory = home.resolve(
                "i76_v66_function_inventory.tsv");

        try (BufferedWriter out =
                Files.newBufferedWriter(names)) {

            applyRenames(fm, out);
                }

        if (MODE.equals("APPLY")) {
            for (String[] note : NOTES) {
                monitor.checkCancelled();

                Function f =
                    fm.getFunctionAt(addr(note[0]));

                if (f != null)
                    addNote(f, note[1]);
            }
        }

        try (BufferedWriter out =
                Files.newBufferedWriter(assembly)) {

            exportAssembly(fm, listing, out);
                }

        try (BufferedWriter out =
                Files.newBufferedWriter(decompiled)) {

            exportDecompilation(fm, out);
                }

        try (BufferedWriter out =
                Files.newBufferedWriter(references)) {

            exportReferences(fm, listing, out);
                }

        try (BufferedWriter out =
                Files.newBufferedWriter(inventory)) {

            exportInventory(fm, out);
                }

        println("I76 v66 deep pass complete.");
        println("Mode: " + MODE);
        println("Names: " + names);
        println("Assembly: " + assembly);
        println("Decompiled: " + decompiled);
        println("References: " + references);
        println("Inventory: " + inventory);
    }
}

