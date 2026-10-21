// @category I76
// i76_v76_fsm_loader_callback_closure.java
// Read-only evidence exporter: mission FSM loading, object registration, node
// allocation/relocation, scheduler lifecycle, and callback side effects.
// Designed for original retail i76.exe, after v71/v72 Ghidra fixes.
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
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.ReferenceManager;
import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.LinkedHashMap;
import java.util.Map;

public class i76_v76_fsm_loader_callback_closure extends GhidraScript {
    private static final String OUTPUT_DIR = "/media/neon-remote/prj/i76/scratch_data/";
    private static final String MD5 = "a640ea0097dbb62e0c77b7f2847c7161";
    // Explicit coverage includes functions omitted from the v75 function inventory.
    private static final String[][] TARGETS = {
        {"00409740", "mission_chunk_entry"},
        {"00409850", "world_object_registration_callback"},
        {"00409980", "world_object_unregister_callback_candidate"},
        {"00409BD0", "fsm_and_vehicle_initialization"},
        {"0040A060", "fsm_gate_mutation"},
        {"0040A320", "frame_gate_and_scheduler"},
        {"0040AEB0", "mission_cached_object_binding"},
        {"0040C020", "host_stop_callback_handler"},
        {"004102D0", "serialized_nav_array"},
        {"00410490", "serialized_node_allocator_and_linker"},
        {"004105A0", "serialized_bitfield_array"},
        {"00410720", "serialized_table_loader"},
        {"00410A10", "command_lookup_from_name"},
        {"004122D0", "mission_label_normalizer_and_resolution"},
        {"00412400", "mission_actor_object_binding"},
        {"00412500", "execution_node_relocator"},
        {"004125C0", "loaded_fsm_finalizer"},
        {"00412630", "ai_vehicle_task_init"},
        {"00414670", "token_vm"},
        {"004149F0", "pending_queue_scheduler"},
        {"004155F0", "epoch_advance"},
        {"004157A0", "damage_source_event"},
        {"0041C2C0", "ramming_epoch_ai_predicate"},
        {"00457270", "world_entry_registration_hook"},
        {"00457420", "world_object_unregistration"}
    };
    private static final String[][] GLOBALS = {
        {"0051F5C0", "fsm_execution_gate"},
        {"0051F620", "fsm_actor_slot_table_base"},
        {"0051F624", "fsm_actor_slot_count"},
        {"0051F628", "pending_node_head"},
        {"0051F62C", "pending_node_count"},
        {"0051F630", "token_count_or_related"},
        {"0051F634", "token_buffer_base_or_related"},
        {"0051F638", "node_execution_source_or_related"},
        {"0051F640", "outer_frame_guard"},
        {"00524550", "shared_epoch"}
    };
    private Address address(String h) { return toAddr(Long.parseLong(h,16)); }
    private BufferedWriter out(Path dir, String name) throws Exception {
        return Files.newBufferedWriter(dir.resolve(name), StandardCharsets.UTF_8);
    }
    private void row(BufferedWriter w,Object... cells) throws Exception {
        for(int i=0;i<cells.length;i++){
            if(i>0)w.write('\t');
            w.write(cells[i]==null ? "" : cells[i].toString().replace('\t',' ').replace('\r',' ').replace('\n',' '));
        }
        w.newLine();
    }
    private void bytes(long at,int... b) throws Exception {
        Address a=toAddr(at);
        for(int i=0;i<b.length;i++) {
            int actual=getByte(a.add(i)) & 255;
            if(actual!=b[i]) throw new IllegalStateException(
                String.format("signature mismatch at %08x got %02x expected %02x",at+i,actual,b[i]));
        }
    }
    private void preflight() throws Exception {
        if(!currentProgram.getName().equalsIgnoreCase("i76.exe") ||
           currentProgram.getImageBase().getOffset()!=0x400000L ||
           !MD5.equalsIgnoreCase(currentProgram.getExecutableMD5()))
            throw new IllegalStateException("Expected original retail i76.exe / MD5 " + MD5);
        FunctionManager fm=currentProgram.getFunctionManager();
        Function f=fm.getFunctionAt(address("0046A7F0"));
        if(f==null || f.getBody().getNumAddresses()!=144)
            throw new IllegalStateException("v71 function ownership incomplete");
        for(String[] rr:new String[][]{
          {"004587D0","clear_world_object_subtree_status_flags_recursive"},
          {"00458860","clear_world_object_and_descendant_status_flags"}}){
            f=fm.getFunctionAt(address(rr[0]));
            if(f==null||!rr[1].equals(f.getName()))
                throw new IllegalStateException("v72 semantic cleanup missing at "+rr[0]);
        }
        bytes(0x004104CCL,0x68,0xBC,0x10,0x00,0x00); // heap node allocation
        bytes(0x004104EDL,0x68,0xBC,0x10,0x00,0x00); // subsequent nodes
        bytes(0x00412546L,0xC7,0x80,0xA0,0x10,0x00,0x00,0,0,0,0); // condition reset
        bytes(0x004155F0L,0xFF,0x05,0x50,0x45,0x52,0x00); // epoch
        bytes(0x0040A64CL,0xEB,0x05); // exclusive AI/FSM branches
        for(String[] p:new String[][]{
          {"004097CD","00410720"},
          {"00409832","004125C0"},
          {"0041092E","00410490"},
          {"004125EB","00412400"},
          {"004125FD","004122D0"},
          {"00412619","00412500"},
          {"00414A58","00414670"},
          {"00414AE4","00414670"}}){
            Instruction ins=currentProgram.getListing().getInstructionAt(address(p[0]));
            boolean found=false;
            if(ins!=null)for(Reference r:ins.getReferencesFrom())
                if(r.getReferenceType().isCall() && r.getToAddress().equals(address(p[1])))
                    found=true;
            if(!found)throw new IllegalStateException("missing call "+p[0]+" -> "+p[1]);
        }
    }
    private Map<String,Function> inventory(Path dir) throws Exception {
        FunctionManager fm=currentProgram.getFunctionManager();
        Map<String,Function> unique=new LinkedHashMap<>();
        try(BufferedWriter w=out(dir,"i76_v76_fsm_targets.tsv")){
            row(w,"site","role","function_entry","function_name","body_bytes","body_ranges","is_exact_entry");
            for(String[] p:TARGETS){
                Address a=address(p[0]);
                Function f=fm.getFunctionAt(a);
                if(f==null) f=fm.getFunctionContaining(a);
                row(w,p[0],p[1],f==null?"":f.getEntryPoint(),
                    f==null?"":f.getName(),f==null?"":f.getBody().getNumAddresses(),
                    f==null?"":f.getBody(),f!=null&&f.getEntryPoint().equals(a));
                if(f!=null)unique.put(f.getEntryPoint().toString(),f);
            }
        }
        return unique;
    }
    private void decompile(Path dir,Map<String,Function> unique) throws Exception {
        DecompInterface dc=new DecompInterface();
        dc.openProgram(currentProgram);
        try(BufferedWriter w=out(dir,"i76_v76_fsm_decompiled.txt")){
            for(Function f:unique.values()){
                monitor.checkCancelled();
                w.write("\n===== "+f.getEntryPoint()+" "+f.getName()+" =====\n");
                DecompileResults r=dc.decompileFunction(f,90,monitor);
                if(!r.decompileCompleted() || r.getDecompiledFunction()==null)
                    w.write("DECOMPILATION FAILED: "+r.getErrorMessage()+"\n");
                else w.write(r.getDecompiledFunction().getC()+"\n");
            }
        } finally { dc.dispose(); }
    }
    private void listInstructions(Path dir, Map<String,Function> unique) throws Exception {
        Listing li=currentProgram.getListing();
        FunctionManager fm=currentProgram.getFunctionManager();
        try(BufferedWriter w=out(dir,"i76_v76_fsm_assembly.tsv")){
            row(w,"owner_entry","instruction_address","instruction","call_targets");
            for(Function f:unique.values()){
                monitor.checkCancelled();
                InstructionIterator it=li.getInstructions(f.getBody(),true);
                while(it.hasNext()){
                    Instruction in=it.next();
                    StringBuilder call=new StringBuilder();
                    for(Reference r:in.getReferencesFrom()){
                        if(r.getReferenceType().isCall()){
                            if(call.length()>0)call.append(';');
                            call.append(r.getToAddress());
                        }
                    }
                    row(w,f.getEntryPoint(),in.getAddress(),in,call);
                }
            }
            // Also inspect explicit callback entry even if not marked as a function.
            Address a=address("00409980"), end=address("00409BBC");
            for(Instruction in=li.getInstructionAt(a);in!=null && in.getAddress().compareTo(end)<=0;
                in=li.getInstructionAfter(in.getAddress())){
                if(monitor.isCancelled())break;
                row(w,"raw_callback_00409980",in.getAddress(),in,"");
            }
        }
    }
    private void calls(Path dir, Map<String,Function> unique) throws Exception {
        FunctionManager fm=currentProgram.getFunctionManager();
        ReferenceManager rm=currentProgram.getReferenceManager();
        Listing li=currentProgram.getListing();
        try(BufferedWriter w=out(dir,"i76_v76_fsm_calls.tsv")){
            row(w,"direction","focus_function","source","reference_type","target","counterpart_function");
            for(Function f:unique.values()){
                monitor.checkCancelled();
                ReferenceIterator incoming=rm.getReferencesTo(f.getEntryPoint());
                while(incoming.hasNext()){
                    Reference r=incoming.next();
                    Function other=fm.getFunctionContaining(r.getFromAddress());
                    row(w,"IN",f.getName(),r.getFromAddress(),r.getReferenceType(),
                        r.getToAddress(),other==null?"":other.getName());
                }
                InstructionIterator it=li.getInstructions(f.getBody(),true);
                while(it.hasNext()){
                    Instruction in=it.next();
                    for(Reference r:in.getReferencesFrom()){
                        if(!r.getReferenceType().isCall())continue;
                        Function other=fm.getFunctionContaining(r.getToAddress());
                        row(w,"OUT",f.getName(),r.getFromAddress(),r.getReferenceType(),
                            r.getToAddress(),other==null?"":other.getName());
                    }
                }
            }
        }
    }
    private void globalRefs(Path dir) throws Exception {
        ReferenceManager rm=currentProgram.getReferenceManager();
        FunctionManager fm=currentProgram.getFunctionManager();
        Listing li=currentProgram.getListing();
        try(BufferedWriter w=out(dir,"i76_v76_fsm_global_xrefs.tsv")){
            row(w,"global_address","role","from","owner","ref_type","instruction");
            for(String[] g:GLOBALS){
                ReferenceIterator it=rm.getReferencesTo(address(g[0]));
                while(it.hasNext()){
                    Reference r=it.next();
                    Function f=fm.getFunctionContaining(r.getFromAddress());
                    Instruction in=li.getInstructionContaining(r.getFromAddress());
                    row(w,g[0],g[1],r.getFromAddress(),f==null?"":f.getName(),
                        r.getReferenceType(),in);
                }
            }
        }
    }
    private void fullTextSearch(Path dir) throws Exception {
        Listing li=currentProgram.getListing();
        FunctionManager fm=currentProgram.getFunctionManager();
        String[] needles={"0x10b8","0x10bc","0x10b0","0x10a8","0x51f628",
                          "0x51f62c","0x51f640","0x524550"};
        try(BufferedWriter w=out(dir,"i76_v76_fsm_whole_text_field_scan.tsv")){
            row(w,"address","owner_entry","owner_name","needle","instruction","warning");
            for(MemoryBlock block:currentProgram.getMemory().getBlocks()){
                if(!block.isExecute())continue;
                InstructionIterator it=li.getInstructions(new AddressSet(block.getStart(),block.getEnd()),true);
                while(it.hasNext()){
                    Instruction ins=it.next();
                    String rendered=ins.toString().toLowerCase();
                    for(String needle:needles){
                        if(!rendered.contains(needle))continue;
                        Function f=fm.getFunctionContaining(ins.getAddress());
                        row(w,ins.getAddress(),f==null?"":f.getEntryPoint(),
                            f==null?"":f.getName(),needle,ins,
                            "literal displacement only; does not capture indirect or computed accesses");
                    }
                }
                monitor.checkCancelled();
            }
        }
    }
    private void descriptorPointers(Path dir) throws Exception {
        // Deliberately inspect original .data bytes, not just Ghidra-created references.
        // Seven retail collision-event descriptors are known to contain the literal
        // callback pointer 0041C2C0 followed by ASCII "clsnDmg".
        try(BufferedWriter w=out(dir,"i76_v76_fsm_collision_descriptor_refs.tsv")){
            row(w,"pointer_address","descriptor_type_dword","callback_pointer",
                "following_16_ascii_bytes","direct_reference_count","interpretation");
            ghidra.program.model.mem.Memory mem=currentProgram.getMemory();
            for(long va=0x004C2000L;va<0x00501800L;va+=4){
                Address at=toAddr(va);
                if(!mem.contains(at))continue;
                if(mem.getInt(at)!=0x0041C2C0)continue;
                StringBuilder ascii=new StringBuilder();
                for(int j=4;j<20;j++){
                    int c=mem.getByte(at.add(j)) & 0xFF;
                    if(c==0)break;
                    ascii.append(c>=32 && c<127 ? (char)c : '.');
                }
                int xrefCount=0;
                ReferenceIterator refs=currentProgram.getReferenceManager().getReferencesTo(at);
                while(refs.hasNext()) { refs.next(); xrefCount++; }
                row(w,at,String.format("0x%08X",mem.getInt(at.subtract(4))),
                    "0041C2C0",ascii,xrefCount,
                    "static .data function-pointer descriptor; callback not a direct CALL");
            }
        }
    }
    private void report(Path dir) throws Exception {
        try(BufferedWriter w=out(dir,"i76_v76_fsm_readme.txt")){
            w.write("I76 v76 FSM loader/callback closure: read-only Ghidra static export\n");
            w.write("Original PE MD5: "+MD5+"\n");
            w.write("Target list includes all v75 lifecycle functions plus missing object callback,\n");
            w.write("loader finalization, command-name lookup, and mission label normalization.\n");
            w.write("Exports never execute gameplay and cannot establish inter-frame timing\n");
            w.write("or absence of indirect dynamic allocations without additional evidence.\n");
            w.write("Does not rename, decompile into project properties, or modify the program.\n");
        }
    }
    @Override public void run() throws Exception {
        preflight();
        Path dir=Paths.get(OUTPUT_DIR);Files.createDirectories(dir);
        Map<String,Function> focus=inventory(dir);
        decompile(dir,focus);
        listInstructions(dir,focus);
        calls(dir,focus);
        globalRefs(dir);
        fullTextSearch(dir);
        descriptorPointers(dir);
        report(dir);
        println("v76 read-only loader/callback closure complete: "+focus.size()+" owner functions; "+dir);
    }
}
