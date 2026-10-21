
//@category I76
// i76_v71_boundary_consolidation.java
//
// Repair false function boundaries identified by v70.
// Preserves code, disassembly, parent symbols and data.
//
// Modes: AUDIT, APPLY
// Default is AUDIT.
//
// IMPORTANT:
// Save a Ghidra project backup before selecting APPLY.

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;

import java.io.BufferedWriter;
import java.nio.file.*;
import java.util.*;

public class i76_v71_boundary_consolidation
    extends GhidraScript {

    private static final String MODE = "AUDIT";

    private static final String OUTPUT =
        "/media/neon-remote/prj/i76/scratch_data/";

    private static final String EXPECTED_MD5 =
        "a640ea0097dbb62e0c77b7f2847c7161";

    // Parent function followed by:
    // false entry address - inclusive body end.
    //
    // These are exact ranges from v70.
    private static final String[][] GROUPS = {
        {"004621E0", "0046251B-0046257C"},
        {"00462660", "004628A9-004628B2"},

        {"0046A7F0",
            "0046A80C-0046A830",
            "0046A831-0046A857",
            "0046A858-0046A85F",
            "0046A860-0046A87F"},

        {"0046BB60", "0046BB78-0046BB8C"},
        {"0046BB90", "0046BCAA-0046BCB3"},
        {"0046D160", "0046D17C-0046D201"},

        {"0046D2E0",
            "0046D575-0046D57A",
            "0046D57B-0046D58F"},

        {"0046D590", "0046D6B1-0046D6BA"},
        {"0046DFE0", "0046E08E-0046E19B"},

        {"0046F5B0",
            "0046F5C9-0046F5ED",
            "0046F5EE-0046F5FF",
            "0046F600-0046F60F",
            "0046F610-0046F639",
            "0046F63A-0046F646"},

        {"0046F650", "0046F665-0046F6A1"},
        {"004A2000", "004A2016-004A2069"},

        {"004A2070",
            "004A20C2-004A2188",
            "004A2189-004A2248",
            "004A2249-004A2431"}
    };

    private static final String[][] RENAMES = {
        {
            "004587D0",
            "world_object_geometry_context_helper_004587d0",
            "clear_world_object_subtree_status_flags_recursive"
        },
        {
            "00458860",
            "world_object_geometry_context_helper_00458860",
            "clear_world_object_and_descendant_status_flags"
        }
    };

    private static class Plan {
        Function parent;
        AddressSet combined;
        ArrayList<Address> fragments = new ArrayList<>();
    }

    private Address address(String text) {
        return toAddr(Long.parseLong(text, 16));
    }

    private String format(Object value) {
        return value == null ? "" :
            value.toString()
            .replace('\t', ' ')
            .replace('\n', ' ')
            .replace('\r', ' ');
    }

    private void row(
            BufferedWriter out, Object... fields)
            throws Exception {

            for (int i = 0; i < fields.length; i++) {
                if (i != 0) out.write("\t");
                out.write(format(fields[i]));
            }
            out.newLine();
            }

    private void verifyProgram() throws Exception {
        if (currentProgram.getImageBase()
                .getOffset() != 0x00400000L) {
            throw new IllegalStateException(
                    "Unexpected executable image base");
                }

        String md5 = currentProgram.getExecutableMD5();

        if (md5 == null ||
                !md5.equalsIgnoreCase(EXPECTED_MD5)) {
            throw new IllegalStateException(
                    "Executable MD5 mismatch: " + md5);
                }
    }

    private ArrayList<Plan> preflight(
            BufferedWriter out) throws Exception {

        FunctionManager fm =
            currentProgram.getFunctionManager();

        ReferenceManager rm =
            currentProgram.getReferenceManager();

        ArrayList<Plan> plans = new ArrayList<>();

        row(out, "parent", "fragment",
                "fragment_end", "body_bytes",
                "external_call_count", "decision");

        // First validate all names, ranges and ownership.
        for (String[] group : GROUPS) {
            monitor.checkCancelled();

            Function parent =
                fm.getFunctionAt(address(group[0]));

            if (parent == null)
                throw new IllegalStateException(
                        "Missing parent: " + group[0]);

            Plan p = new Plan();
            p.parent = parent;
            p.combined =
                new AddressSet(parent.getBody());

            for (int i = 1; i < group.length; i++) {
                String[] pair = group[i].split("-");

                Address entry = address(pair[0]);
                Address end = address(pair[1]);

                Function f = fm.getFunctionAt(entry);

                if (f == null)
                    throw new IllegalStateException(
                            "Missing candidate fragment: "
                            + entry);

                if (!f.getName().equalsIgnoreCase(
                            "FUN_" + pair[0])) {
                    throw new IllegalStateException(
                            "Fragment was renamed: "
                            + entry + " " + f.getName());
                            }

                if (!f.getBody()
                        .getMinAddress().equals(entry) ||
                        !f.getBody()
                        .getMaxAddress().equals(end)) {
                    throw new IllegalStateException(
                            "Boundary changed at: "
                            + entry);
                        }

                long length =
                    end.subtract(entry) + 1;

                if (f.getBody()
                        .getNumAddresses() != length) {
                    throw new IllegalStateException(
                            "Discontiguous fragment at "
                            + entry);
                        }

                p.fragments.add(entry);
                p.combined.add(f.getBody());
            }

            plans.add(p);
        }

        // Validate reference ownership after the full
        // proposed parent bodies have been constructed.
        //
        // A direct CALL into a fragment, or a jump from
        // outside its reconstructed parent, blocks repair.
        for (Plan p : plans) {
            for (Address entry : p.fragments) {
                monitor.checkCancelled();

                Function f = fm.getFunctionAt(entry);

                int unsafe = 0;

                ReferenceIterator refs =
                    rm.getReferencesTo(entry);

                while (refs.hasNext()) {
                    Reference ref = refs.next();

                    RefType type =
                        ref.getReferenceType();

                    if (type.isCall()) {
                        unsafe++;
                    } else if (type.isJump() &&
                            !p.combined.contains(
                                ref.getFromAddress())) {
                        unsafe++;
                                }
                }

                row(out,
                        p.parent.getEntryPoint(),
                        entry,
                        f.getBody().getMaxAddress(),
                        f.getBody().getNumAddresses(),
                        unsafe,
                        unsafe == 0
                        ? "PREFLIGHT_OK"
                        : "UNSAFE_REFERENCE");

                if (unsafe != 0) {
                    throw new IllegalStateException(
                            "External flow into fragment "
                            + entry);
                }
            }
        }

        return plans;
            }

    private void applyPlans(
            ArrayList<Plan> plans,
            BufferedWriter out) throws Exception {

        FunctionManager fm =
            currentProgram.getFunctionManager();

        row(out, "parent", "action",
                "result", "details");

        // Run the entire repair in a single transaction.
        // If any step fails, roll back the changes.
        int tx = currentProgram.startTransaction(
                "I76 v71 boundary consolidation");

        boolean success = false;

        try {
            for (Plan p : plans) {
                monitor.checkCancelled();

                for (Address entry : p.fragments) {
                    if (!fm.removeFunction(entry)) {
                        throw new IllegalStateException(
                                "Could not remove false function "
                                + entry);
                    }
                }

                p.parent.setBody(p.combined);

                row(out,
                        p.parent.getEntryPoint(),
                        "MERGE_BODY",
                        "SUCCESS",
                        "Fragments: "
                        + p.fragments.size()
                        + "; body bytes: "
                        + p.combined
                        .getNumAddresses());
            }

            for (String[] item : RENAMES) {
                Function f = fm.getFunctionAt(
                        address(item[0]));

                if (f == null)
                    throw new IllegalStateException(
                            "Missing rename target "
                            + item[0]);

                if (f.getName().equals(item[2])) {
                    row(out, item[0], "RENAME",
                            "ALREADY_SET", item[2]);
                    continue;
                }

                if (!f.getName().equals(item[1])) {
                    throw new IllegalStateException(
                            "Unexpected symbol at "
                            + item[0] + ": "
                            + f.getName());
                }

                f.setName(
                        item[2],
                        SourceType.USER_DEFINED);

                row(out, item[0], "RENAME",
                        "SUCCESS", item[2]);
            }

            success = true;

        } finally {
            currentProgram.endTransaction(
                    tx, success);
        }
            }

    private void exportParentDecompilation(
            ArrayList<Plan> plans,
            BufferedWriter out) throws Exception {

        DecompInterface decompiler =
            new DecompInterface();

        if (!decompiler.openProgram(currentProgram)) {
            out.write("Decompiler unavailable\n");
            decompiler.dispose();
            return;
        }

        try {
            for (Plan p : plans) {
                monitor.checkCancelled();

                Function f = currentProgram
                    .getFunctionManager()
                    .getFunctionAt(
                            p.parent.getEntryPoint());

                out.write("\n===== "
                        + f.getEntryPoint()
                        + " " + f.getName()
                        + " =====\n");

                DecompileResults result =
                    decompiler.decompileFunction(
                            f, 90, monitor);

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

                out.write("\n");
            }
        } finally {
            decompiler.dispose();
        }
            }

    @Override
    public void run() throws Exception {
        if (!MODE.equals("AUDIT") &&
                !MODE.equals("APPLY")) {
            throw new IllegalStateException(
                    "Invalid MODE");
                }

        verifyProgram();

        Path dir = Paths.get(OUTPUT);
        Files.createDirectories(dir);

        Path preflightPath = dir.resolve(
                "i76_v71_boundary_preflight.tsv");

        Path decisionsPath = dir.resolve(
                "i76_v71_boundary_decisions.tsv");

        Path decompiledPath = dir.resolve(
                "i76_v71_parent_decompiled.txt");

        ArrayList<Plan> plans;

        try (BufferedWriter out =
                Files.newBufferedWriter(
                    preflightPath)) {
            plans = preflight(out);
                    }

        if (MODE.equals("APPLY")) {
            try (BufferedWriter out =
                    Files.newBufferedWriter(
                        decisionsPath)) {
                applyPlans(plans, out);
                        }
        } else {
            try (BufferedWriter out =
                    Files.newBufferedWriter(
                        decisionsPath)) {
                row(out, "mode", "result");
                row(out, MODE, "NO_CHANGES");
                        }
        }

        try (BufferedWriter out =
                Files.newBufferedWriter(
                    decompiledPath)) {
            exportParentDecompilation(
                    plans, out);
                    }

        println("I76 v71 completed.");
        println("Mode: " + MODE);
        println("Parents: " + plans.size());
        println("Preflight: " + preflightPath);
        println("Decisions: " + decisionsPath);
        println("Decompilation: " + decompiledPath);
    }
}

