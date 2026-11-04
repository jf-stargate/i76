// Read-only extraction. Complete JSONL and bounded disassembly stay private.
// @category I76.Research
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import com.google.gson.Gson;
import java.util.*;
import java.io.*;
import java.security.MessageDigest;

public class TUInventory extends GhidraScript {
    Gson gson = new Gson();
    String hx(Address a) { return a == null ? null : a.toString(); }
    Map<String,Object> map(Object... v) { Map<String,Object> m=new LinkedHashMap<>();for(int i=0;i<v.length;i+=2)m.put((String)v[i],v[i+1]);return m; }
    String hash(byte[] b) throws Exception { StringBuilder s=new StringBuilder();for(byte x:MessageDigest.getInstance("SHA-256").digest(b))s.append(String.format("%02x",x&255));return s.toString(); }
    boolean detail(long v) { return v>=0x410000L&&v<=0x414e00L || v>=0x46fa00L&&v<=0x470e00L || v>=0x492400L&&v<=0x493e00L || v>=0x4b2800L&&v<=0x4b3700L; }
    Map<String,Object> ref(Reference r) {
        Address t=r.getToAddress();MemoryBlock b=currentProgram.getMemory().getBlock(t);
        Data d=currentProgram.getListing().getDataContaining(t);
        Object val=d==null?null:d.getValue();
        Function owner=getFunctionContaining(r.getFromAddress());
        return map("from",hx(r.getFromAddress()),"to",hx(t),"type",r.getReferenceType().toString(),"read",r.getReferenceType().isRead(),"write",r.getReferenceType().isWrite(),"call",r.getReferenceType().isCall(),"flow",r.getReferenceType().isFlow(),"operand",r.getOperandIndex(),"owner",owner==null?null:hx(owner.getEntryPoint()),"block",b==null?null:b.getName(),"writable",b!=null&&b.isWrite(),"data_base",d==null?null:hx(d.getAddress()),"data_type",d==null?null:d.getDataType().getName(),"string",val instanceof String?val:null);
    }
    public void run() throws Exception {
        String out=getScriptArgs()[0];new File(out).mkdirs();
        long before=currentProgram.getModificationNumber();
        List<Function> fs=new ArrayList<>();currentProgram.getFunctionManager().getFunctions(true).forEachRemaining(fs::add);
        PrintWriter inv=new PrintWriter(out+"/inventory.jsonl","UTF-8");
        PrintWriter detail=new PrintWriter(out+"/detail.jsonl","UTF-8");
        for(int n=0;n<fs.size();n++){
            monitor.checkCancelled();Function f=fs.get(n);List<Object> ranges=new ArrayList<>();
            for(AddressRange r:f.getBody().getAddressRanges()){
                byte[] bytes=new byte[(int)r.getLength()];currentProgram.getMemory().getBytes(r.getMinAddress(),bytes);
                ranges.add(map("start",hx(r.getMinAddress()),"end",hx(r.getMaxAddress()),"bytes",r.getLength(),"sha256",hash(bytes)));
            }
            List<Object> refs=new ArrayList<>(),incoming=new ArrayList<>(),indirect=new ArrayList<>();Set<String> calls=new TreeSet<>();
            InstructionIterator ii=currentProgram.getListing().getInstructions(f.getBody(),true);
            while(ii.hasNext()){
                Instruction i=ii.next();for(Reference r:i.getReferencesFrom()){
                    if(r.getReferenceType().isCall() || !r.getReferenceType().isFlow() || (!f.getBody().contains(r.getToAddress()) && r.getReferenceType().isJump()))refs.add(ref(r));
                    if(r.getReferenceType().isCall() && !i.getFlowType().isComputed()) calls.add(hx(r.getToAddress()));
                }
                if(i.getFlowType().isComputed())indirect.add(map("address",hx(i.getAddress()),"instruction",i.toString(),"type",i.getFlowType().toString()));
                if(detail(f.getEntryPoint().getOffset()))detail.println(gson.toJson(map("function",hx(f.getEntryPoint()),"address",hx(i.getAddress()),"instruction",i.toString(),"refs",Arrays.stream(i.getReferencesFrom()).map(this::ref).toArray())));
            }
            // Entry references include non-call address-taking. Body-interior references retained separately.
            ReferenceIterator ri=currentProgram.getReferenceManager().getReferencesTo(f.getEntryPoint());while(ri.hasNext())incoming.add(ref(ri.next()));
            List<Object> interior=new ArrayList<>();AddressIterator ai=currentProgram.getReferenceManager().getReferenceDestinationIterator(f.getBody(),true);
            while(ai.hasNext()){Address t=ai.next();if(t.equals(f.getEntryPoint()))continue;ReferenceIterator rr=currentProgram.getReferenceManager().getReferencesTo(t);while(rr.hasNext()){Reference r=rr.next();if(!f.getBody().contains(r.getFromAddress()))interior.add(ref(r));}}
            inv.println(gson.toJson(map("entry",hx(f.getEntryPoint()),"name",f.getName(),"external",f.isExternal(),"thunk",f.isThunk(),"thunk_target",f.isThunk()?hx(f.getThunkedFunction(true).getEntryPoint()):null,"size",f.getBody().getNumAddresses(),"ranges",ranges,"calls",calls,"refs",refs,"incoming",incoming,"interior_incoming",interior,"indirect",indirect,"previous",n==0?null:hx(fs.get(n-1).getEntryPoint()),"next",n+1==fs.size()?null:hx(fs.get(n+1).getEntryPoint()),"gap_to_next",n+1==fs.size()?null:fs.get(n+1).getEntryPoint().subtract(f.getBody().getMaxAddress())-1)));
        }
        inv.close();detail.close();
        int ext=0;FunctionIterator ei=currentProgram.getFunctionManager().getExternalFunctions();while(ei.hasNext()){ei.next();ext++;}
        Map<String,Object> meta=map("program",currentProgram.getName(),"executable_sha256",currentProgram.getExecutableSHA256(),"language",currentProgram.getLanguageID().toString(),"compiler_spec",currentProgram.getCompilerSpec().getCompilerSpecID().toString(),"defined_functions",fs.size(),"external_functions",ext,"modification_before",before,"modification_after",currentProgram.getModificationNumber());
        try(PrintWriter w=new PrintWriter(out+"/metadata.json","UTF-8")){w.println(gson.toJson(meta));}println(gson.toJson(meta));
    }
}
