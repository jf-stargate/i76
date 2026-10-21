
//@category I76
// Interstate '76 v65: Vehicle damage and object lifecycle trace
// Read-only analysis. No symbols, types, or comments changed.
//
// Expected game executable:
// MD5 a640ea0097dbb62e0c77b7f2847c7161

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.SourceType;

import java.io.BufferedWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class I76_Vehicle_Damage_Trace_V65
    extends GhidraScript {

    private static final String MD5 =
        "a640ea0097dbb62e0c77b7f2847c7161";

    private static final long[] SEEDS = {
        // FSM predicates and attributed damage
        0x0040B840L, 0x0040B860L,
        0x0040B9E0L, 0x0040AF3DL,
        0x00415640L, 0x004157A0L,

        // Damage processing and vehicle lifecycle
        0x004641E0L, 0x004643C0L,
        0x004644D0L, 0x00464890L,
        0x00465370L, 0x00465620L,
        0x00465AF0L, 0x00466180L,
        0x00466AC0L, 0x00466B70L,
        0x00466C20L, 0x00466CA0L,
        0x00466E20L, 0x00466EB0L,

        // Projectile damage and radial effects
        0x004A0CC0L, 0x004A0DD0L,
        0x004A0EB0L, 0x004A76A0L,
        0x004A7800L, 0x004A7BB0L,
        0x004A7C80L, 0x004A8240L,

        // Entity registry and object lifetime
        0x004572B0L, 0x00457530L,
        0x00457A90L, 0x00457FF0L,
        0x0045EF70L, 0x0045F0F0L
    };

    private Address at(long va) {
        return toAddr(va);
    }

    private String clean(Object o) {
        if (o == null) return "";
        return String.valueOf(o)
            .replace('\t', ' ')
            .replace('\r', ' ')
            .replace('\n', ' ');
    }

    private void row(BufferedWriter w, Object... cells)
            throws Exception {
            for (int i = 0; i < cells.length; i++) {
                if (i > 0) w.write('\t');
                w.write(clean(cells[i]));
            }
            w.newLine();
    }

    private void check(long va, int... bytes)
            throws Exception {
            Address a = at(va);

            for (int i = 0; i < bytes.length; i++) {
                int actual = currentProgram.getMemory()
                    .getByte(a.add(i)) & 0xff;

                if (actual != bytes[i])
                    throw new IllegalStateException(
                            String.format(
                                "PE mismatch at %08X: %02X != %02X",
                                va + i, actual, bytes[i]));
            }
    }

    private void verify() throws Exception {
        if (currentProgram.getImageBase().getOffset()
                != 0x400000L)
            throw new IllegalStateException(
                    "Unexpected executable image base");

        String md5 = currentProgram.getExecutableMD5();

        if (md5 != null && !md5.isEmpty() &&
                !md5.equalsIgnoreCase("unknown") &&
                !md5.equalsIgnoreCase(MD5))
            throw new IllegalStateException(
                    "Executable MD5 mismatch: " + md5);

        check(0x00415872L,
                0xF6,0x85,0x54,0x04,0x00,0x00,0x20);

        check(0x0040B9FEL,
                0xF6,0x87,0x54,0x04,0x00,0x00,0x20);

        check(0x00415893L,
                0xC7,0x86,0xE0,0xA6,0x00,0x00,0x01);

        check(0x004573DBL,0xA8,0x10);
    }

    private String label(Instruction i) {
        if (i == null) return "";

        String s = i.toString().toLowerCase(Locale.ROOT)
            .replace(" ", "");

        if (s.contains("a6e0"))
            return "GROOVE_ATTRIBUTION";

        if (s.contains("a6d4") ||
                s.contains("a6d8") ||
                s.contains("a6dc") ||
                s.contains("a6e4") ||
                s.contains("a6e8") ||
                s.contains("a6ec") ||
                s.contains("a6f0"))
            return "DAMAGE_EVENT_LEDGER";

        if (s.contains("0x454") ||
                s.contains("+454h") ||
                s.contains("+454]"))
            return "VEHICLE_COMPONENT_FLAGS_454";

        if (s.contains("54a264"))
            return "ACTIVE_PRIMARY_OBJECT_GLOBAL";

        if (s.contains("0x200") ||
                s.contains("200h"))
            return "POSSIBLE_WORLD_OBJECT_DEATH_MASK";

        return "";
    }

    private String accessKind(Instruction i) {
        String mnemonic =
            i.getMnemonicString().toUpperCase(Locale.ROOT);

        if (i.getNumOperands() == 0)
            return "UNKNOWN";

        String operand0 =
            i.getDefaultOperandRepresentation(0)
            .toLowerCase(Locale.ROOT);

        boolean memory =
            operand0.contains("[") &&
            operand0.contains("]");

        boolean writes =
            mnemonic.equals("MOV") ||
            mnemonic.equals("OR") ||
            mnemonic.equals("AND") ||
            mnemonic.equals("XOR") ||
            mnemonic.equals("BTS") ||
            mnemonic.equals("BTR") ||
            mnemonic.equals("ADD") ||
            mnemonic.equals("SUB") ||
            mnemonic.equals("INC") ||
            mnemonic.equals("DEC");

        if (memory && writes)
            return "POSSIBLE_MEMORY_WRITE";

        return "READ_OR_OTHER";
    }

    private String context(
            Listing listing, Instruction ins) {
        List<String> before = new ArrayList<>();

        Instruction cursor = ins;

        for (int i = 0; i < 5; i++) {
            cursor = listing.getInstructionBefore(
                    cursor.getAddress());

            if (cursor == null) break;

            before.add(0,
                    cursor.getAddress() + " " + cursor);
        }

        StringBuilder text = new StringBuilder();

        for (String s : before)
            text.append(s).append(" | ");

        text.append(">>> ")
            .append(ins.getAddress())
            .append(" ")
            .append(ins)
            .append(" <<<");

        cursor = ins;

        for (int i = 0; i < 5; i++) {
            cursor = listing.getInstructionAfter(
                    cursor.getAddress());

            if (cursor == null) break;

            text.append(" | ")
                .append(cursor.getAddress())
                .append(" ")
                .append(cursor);
        }

        return text.toString();
            }

    private void exportCalls(
            BufferedWriter out,
            Function f,
            Listing listing,
            FunctionManager fm) throws Exception {

        InstructionIterator it =
            listing.getInstructions(f.getBody(), true);

        while (it.hasNext()) {
            monitor.checkCancelled();

            Instruction ins = it.next();

            if (!ins.getFlowType().isCall())
                continue;

            boolean resolved = false;

            for (Reference ref :
                    ins.getReferencesFrom()) {

                if (!ref.getReferenceType().isCall())
                    continue;

                Function dest = fm.getFunctionContaining(
                        ref.getToAddress());

                row(out,
                        f.getEntryPoint(),
                        f.getName(),
                        ins.getAddress(),
                        ref.getToAddress(),
                        dest == null
                        ? "<unknown>"
                        : dest.getName(),
                        "DIRECT_REFERENCE");

                resolved = true;
                    }

            if (!resolved) {
                row(out,
                        f.getEntryPoint(),
                        f.getName(),
                        ins.getAddress(),
                        "",
                        "",
                        "INDIRECT_OR_UNRESOLVED_CALL");
            }
        }
            }

    @Override
    public void run() throws Exception {
        verify();

        Path home = Paths.get(
                System.getProperty("user.home"));

        Path calls = home.resolve(
                "i76_v65_damage_callgraph.tsv");

        Path accesses = home.resolve(
                "i76_v65_damage_field_accesses.tsv");

        Path assembly = home.resolve(
                "i76_v65_priority_assembly.txt");

        Path decompiled = home.resolve(
                "i76_v65_priority_decompiled.txt");

        FunctionManager fm =
            currentProgram.getFunctionManager();

        Listing listing =
            currentProgram.getListing();

        long callCount = 0;
        long fieldCount = 0;

        // Entire defined-function call graph.
        try (BufferedWriter out =
                Files.newBufferedWriter(calls)) {

            row(out, "caller_address", "caller_name",
                    "call_instruction", "target_address",
                    "target_name", "kind");

            FunctionIterator functions =
                fm.getFunctions(true);

            while (functions.hasNext()) {
                monitor.checkCancelled();

                Function f = functions.next();
                exportCalls(out, f, listing, fm);
                callCount++;
            }
                }

        // Scan all instructions for relevant fields.
        try (BufferedWriter out =
                Files.newBufferedWriter(accesses)) {

            row(out, "instruction_address",
                    "function_address", "function_name",
                    "field_category", "candidate_access",
                    "instruction", "context");

            InstructionIterator instructions =
                listing.getInstructions(true);

            while (instructions.hasNext()) {
                monitor.checkCancelled();

                Instruction ins = instructions.next();
                String category = label(ins);

                if (category.isEmpty())
                    continue;

                Function owner =
                    fm.getFunctionContaining(
                            ins.getAddress());

                row(out,
                        ins.getAddress(),
                        owner == null
                        ? ""
                        : owner.getEntryPoint(),
                        owner == null
                        ? "<undefined>"
                        : owner.getName(),
                        category,
                        accessKind(ins),
                        ins.toString(),
                        context(listing, ins));

                fieldCount++;
            }
                }

        // Full assembly and decompilation for critical
        // engine functions.
        DecompInterface decomp =
            new DecompInterface();

        boolean canDecompile =
            decomp.openProgram(currentProgram);

        try (
                BufferedWriter asm =
                Files.newBufferedWriter(assembly);
                BufferedWriter c =
                Files.newBufferedWriter(decompiled)
            ) {
            for (long va : SEEDS) {
                monitor.checkCancelled();

                Function f = fm.getFunctionAt(at(va));

                asm.write(String.format(
                            "\n===== %08X =====\n", va));

                c.write(String.format(
                            "\n===== %08X =====\n", va));

                if (f == null) {
                    asm.write("NO FUNCTION DEFINED\n");
                    c.write("NO FUNCTION DEFINED\n");
                    continue;
                }

                asm.write(
                        f.getName() + "\n");

                c.write(
                        f.getName() + "\n");

                InstructionIterator instructions =
                    listing.getInstructions(
                            f.getBody(), true);

                while (instructions.hasNext()) {
                    monitor.checkCancelled();

                    Instruction ins =
                        instructions.next();

                    asm.write(
                            ins.getAddress() + "\t" +
                            ins.toString() + "\n");
                }

                if (canDecompile) {
                    try {
                        DecompileResults result =
                            decomp.decompileFunction(
                                    f, 35, monitor);

                        if (result != null &&
                                result.decompileCompleted() &&
                                result.getDecompiledFunction()
                                != null) {

                            c.write(
                                    result.getDecompiledFunction()
                                    .getC());

                        } else {
                            c.write(
                                    "DECOMPILATION FAILED\n");
                        }
                    } catch (Exception ex) {
                        c.write(
                                "DECOMPILER ERROR: " +
                                ex.toString() + "\n");
                    }
                } else {
                    c.write(
                            "DECOMPILER INITIALIZATION FAILED\n");
                }

                c.write("\n");
            }
        } finally {
            decomp.dispose();
        }

        println("I76 v65 damage trace completed.");
        println("Defined functions scanned: " +
                callCount);
        println("Relevant instruction candidates: " +
                fieldCount);
        println("Call graph: " + calls);
        println("Field access inventory: " + accesses);
        println("Priority assembly: " + assembly);
        println("Priority decompilation: " +
                decompiled);
        println("Ghidra project was not modified.");
    }
}

