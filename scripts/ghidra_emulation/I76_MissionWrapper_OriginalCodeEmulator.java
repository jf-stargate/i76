// Copyright (c) research checkpoint v0.6.0; requires Ghidra 12.1.4
// Executes RETAIL i76.exe wrapper-suffix, nested parsers, and FSM loader instructions.
// World loaders, resource cache, Windows heap/CRT dependencies use explicitly logged substitutes.
import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.*;

public class I76_MissionWrapper_OriginalCodeEmulator extends GhidraScript {
    static final long PARSER=0x004b3db0L, BWD_DESC=0x00500328L, REV_DESC=0x00500338L;
    static final long FIXTURE=0x20000000L, STACK=0x30010000L, FILENAME=0x21000000L, SENTINEL=0x70000000L;
    static final int LIMIT=25000;
    static final long IMPORT_STRNCPY=0x000c0c2aL, IMPORT_SPLITPATH=0x000c0bb6L, IMPORT_STRICMP=0x000c0ca8L;
    EmulatorHelper emu;
    FileWriter writer;
    long steps=0, revInterceptions=0, reports=0, bwdCallbacks=0, crtInterceptions=0, unknownCalls=0;
    final ArrayList<String> notable=new ArrayList<>();

    Address a(long x){return toAddr(x & 0xffffffffL);}
    long reg(String s){return emu.readRegister(s).longValue()&0xffffffffL;}
    long u32(long adr){byte[] b=emu.readMemory(a(adr),4);return ((long)(b[0]&255)|((long)(b[1]&255)<<8)|((long)(b[2]&255)<<16)|((long)(b[3]&255)<<24))&0xffffffffL;}
    void w32(long adr,long value){emu.writeMemoryValue(a(adr),4,value&0xffffffffL);}
    void w(long adr,byte[] bytes){emu.writeMemory(a(adr),bytes);}
    void callbackReturn(long result){long esp=reg("ESP");long ret=u32(esp);emu.writeRegister("ESP",(esp+4)&0xffffffffL);emu.writeRegister("EAX",result);emu.writeRegister("EIP",ret);}
    void logEvent(String scenario,String type,long pc,String detail){notable.add(String.format(Locale.ROOT,"%s\t%s\t%08X\t%s",scenario,type,pc,detail));}
    String cString(long addr,int limit) throws Exception {
        byte[] data=new byte[limit];int n=0;
        while(n<limit){byte v=emu.readMemory(a(addr+n),1)[0];if(v==0)break;data[n++]=v;}
        return new String(data,0,n,StandardCharsets.US_ASCII);
    }
    void writeCString(long addr,String value) {
        w(addr,(value+"\0").getBytes(StandardCharsets.US_ASCII));
    }
    void runtimeStricmp(String name,long pc) throws Exception {
        long sp=reg("ESP"), a1=u32(sp+4),a2=u32(sp+8);
        String s1=cString(a1,260),s2=cString(a2,260);
        int result=s1.compareToIgnoreCase(s2);
        crtInterceptions++;logEvent(name,"CRT_stricmp_stub",pc,s1+" vs "+s2+" -> "+result);
        callbackReturn(result);
    }
    void runtimeSplitpath(String name,long pc) throws Exception {
        long sp=reg("ESP"), path=u32(sp+4), drive=u32(sp+8), dir=u32(sp+12), fname=u32(sp+16), ext=u32(sp+20);
        String raw=cString(path,260),driveStr="",dirStr="",nameStr=raw,extStr="";
        if(raw.length()>=2 && raw.charAt(1)==':'){driveStr=raw.substring(0,2);nameStr=raw.substring(2);}
        int slash=Math.max(nameStr.lastIndexOf('/'),nameStr.lastIndexOf('\\'));
        if(slash>=0){dirStr=nameStr.substring(0,slash+1);nameStr=nameStr.substring(slash+1);}
        int dot=nameStr.lastIndexOf('.');if(dot>=0){extStr=nameStr.substring(dot);nameStr=nameStr.substring(0,dot);}
        if(drive!=0)writeCString(drive,driveStr);if(dir!=0)writeCString(dir,dirStr);
        if(fname!=0)writeCString(fname,nameStr);if(ext!=0)writeCString(ext,extStr);
        crtInterceptions++;logEvent(name,"CRT_splitpath_stub",pc,raw+" -> ext="+extStr);
        callbackReturn(0);
    }
    // Full unmodified retail mission bytes are loaded from an external user-owned file.
    // This harness never packages those bytes. The prefix omission is an in-memory mutation.
    byte[] stockMission;
    static final long WRAPPER_SUFFIX=0x004b4463L, RESOURCE_BUFFER=0x20000000L, BASE_ESP=STACK-0x1000L;
    static final long ROOT_DESCRIPTOR=0x00500328L, WORLD_DESCRIPTOR=0x00500348L, ADEF_DESCRIPTOR=0x00500d20L;
    static final long GLOBAL_CURSOR=0x005db97cL, GLOBAL_END=0x005db980L;
    static final int MAX_STEPS=1500000;
    final Map<Long,Integer> stubCounts=new TreeMap<>();
    long nextHeap=0x22000000L;
    void stdcallReturn(long value,int argBytes){long sp=reg("ESP");long ret=u32(sp);emu.writeRegister("ESP",(sp+4+argBytes)&0xffffffffL);emu.writeRegister("EAX",value);emu.writeRegister("EIP",ret);}
    void stdcallStub(String nm,long pc,long value,int argBytes,String detail)throws Exception{stubCounts.merge(pc,1,Integer::sum);logEvent(nm,"STUB_STDCALL",pc,detail);stdcallReturn(value,argBytes);}
    void stub(String nm,long pc,long value,String detail)throws Exception {
        stubCounts.merge(pc,1,Integer::sum);
        logEvent(nm,"STUB_BOUNDARY",pc,detail);
        callbackReturn(value);
    }
    byte[] fixture(boolean hasBWD,boolean wrongRootRevision,String mutation){
        byte[] b=hasBWD?Arrays.copyOf(stockMission,stockMission.length):Arrays.copyOfRange(stockMission,8,stockMission.length);
        if(wrongRootRevision) {
            int p=hasBWD?16:8;
            b[p]=3;b[p+1]=0;b[p+2]=0;b[p+3]=0;
        }
        int adef=0xba9a-(hasBWD?0:8);
        if(!mutation.equals("none")){
            if(!Arrays.equals(Arrays.copyOfRange(b,adef,adef+4),"ADEF".getBytes(StandardCharsets.US_ASCII)))
                throw new IllegalStateException("M06 ADEF fixture offset differs from corpus");
            if(mutation.equals("wrong_AREV"))b[adef+16]=2;
            else if(mutation.equals("missing_FSM"))b[adef+20]='Q';
            else if(mutation.equals("missing_ADEF"))b[adef]='Q';
            else if(mutation.equals("missing_ADEF_EXIT"))b[adef+28]='Q';
            else throw new IllegalArgumentException("unknown mutation "+mutation);
        }
        return b;
    }
    String scenario(String name,boolean hasBWD,boolean badRevision,String mutation,boolean keep)throws Exception {
        if(emu==null)emu=new EmulatorHelper(currentProgram);
        notable.clear();stubCounts.clear();steps=revInterceptions=reports=bwdCallbacks=crtInterceptions=unknownCalls=0;
        try {
            byte[] b=fixture(hasBWD,badRevision,mutation);
            w(FIXTURE,b);
            w32(GLOBAL_CURSOR,0);w32(GLOBAL_END,0);
            long esp=BASE_ESP-0x320L;
            // Suffix starts after SUB ESP,0x314 and three saved-register PUSHes.
            // Initialize the skipped prologue's local stack area deterministically.
            w(esp,new byte[0x320]);
            w(FILENAME,new byte[512]);
            w32(BASE_ESP,SENTINEL);w32(BASE_ESP+4,FILENAME);
            String missionName=stockMission.length>100000?"T01.MSN":"M06.MSN";
            w(FILENAME,(missionName+"\0").getBytes(StandardCharsets.US_ASCII));
            w(esp+0x10L,(missionName+"\0").getBytes(StandardCharsets.US_ASCII));
            emu.writeRegister("ESP",esp);emu.writeRegister("EIP",WRAPPER_SUFFIX);
            emu.writeRegister("EAX",0);emu.writeRegister("ECX",0);emu.writeRegister("EDX",0);
            emu.writeRegister("EBX",0);emu.writeRegister("ESI",0);emu.writeRegister("EDI",0);emu.writeRegister("EBP",0);
            long bwdBefore=u32(ROOT_DESCRIPTOR+12), worldBefore=u32(WORLD_DESCRIPTOR+12), adefBefore=u32(ADEF_DESCRIPTOR+12);
            boolean returned=false, failed=false;String reason="";ArrayDeque<String> recent=new ArrayDeque<>();
            int rootParses=0,worldParses=0,adefParses=0, fsmCalls=0,fsmNative=0,fsmStubbed=0, revCalls=0, observedOriginalCallbacks=0;
            for(int i=0;i<MAX_STEPS;i++){
                long pc=reg("EIP");
                if(recent.size()>=60)recent.removeFirst();recent.addLast(hex(pc));
                if(pc==SENTINEL){returned=true;reason="returned";break;}
                if(pc>=0x00500000L&&pc<0x00600000L){failed=true;reason="entered mapped data at "+hex(pc);logEvent(name,"DATA_EXECUTION_ENTRY",pc,"recent="+recent.toString());break;}
                if(pc==0x004b44c8L){rootParses++;logEvent(name,"WRAPPER_ROOT_PARSER",pc,"original wrapper calls original root parser");}
                if(pc==0x004b44f1L){worldParses++;logEvent(name,"WRAPPER_WORLD_PARSER",pc,"original wrapper calls original world parser");}
                if(pc==0x004b89caL){adefParses++;logEvent(name,"NESTED_ADEF_PARSER",pc,"original nested ADEF parser call");}
                if(pc==0x004b4610L){revCalls++;logEvent(name,"ORIGINAL_REVISION",pc,"original revision callback");}
                if(pc==0x004b3f31L){logEvent(name,"DESCRIPTOR_SEEN",pc,String.format("entry=%08X flags=%08X",reg("EDI"),u32(reg("EDI")+12)));}
                if(pc==0x004b41afL){logEvent(name,"PARSER_NULL_PATH",pc,"original null branch");}
                if(pc==0x0042d5d0L){reports++;logEvent(name,"ORIGINAL_NOOP_REPORT",pc,"retail one-instruction reporter");}
                if(pc==0x004b45f0L||pc==0x004b89b0L||pc==0x004b4290L||pc==0x004b4790L){observedOriginalCallbacks++;logEvent(name,"ORIGINAL_CALLBACK",pc,"wrapper/nested or exit callback");}
                // Resource-library boundaries. We execute every original instruction in the
                // wrapper suffix, parser and ADEF callback, but provide a deterministic resource
                // byte buffer and avoid touching a Windows filesystem/resource cache.
                if(pc==0x000c0c2aL){
                    long sp=reg("ESP"),dst=u32(sp+4),src=u32(sp+8),cnt=u32(sp+12);
                    if(cnt>512)throw new IllegalStateException("strncpy length="+cnt);
                    byte[] copy=emu.readMemory(a(src),(int)cnt);boolean nul=false;
                    for(int j=0;j<copy.length;j++){if(nul)copy[j]=0;else if(copy[j]==0)nul=true;}
                    w(dst,copy);crtInterceptions++;logEvent(name,"CRT_strncpy_stub",pc,"bytes="+cnt);callbackReturn(dst);steps++;continue;
                }
                if(pc==IMPORT_SPLITPATH){runtimeSplitpath(name,pc);steps++;continue;}
                if(pc==IMPORT_STRICMP){runtimeStricmp(name,pc);steps++;continue;}
                if(pc==u32(0x004bc148L)){stub(name,pc,0,"CRT bsearch -> no mapped media resource in emulator");steps++;continue;}
                if(pc==u32(0x004bc254L)) { // _strlwr imported MSVCRT, cdecl
                    long p=u32(reg("ESP")+4);String ss=cString(p,255);writeCString(p,ss.toLowerCase(Locale.ROOT));stub(name,pc,p,"CRT _strlwr");steps++;continue;
                }
                if(pc==0x000c0c41L) {throw new IllegalStateException("unexpected unknown CRT import address");}
                // Retail wrapper suffix calls strnicmp-like resource selector before opening.
                if(pc==u32(0x004bc260L)){stub(name,pc,1,"resource selector mismatch (intentionally choose ordinary mission path)");steps++;continue;}
                if(pc==0x0046ffc0L){stub(name,pc,FIXTURE,"resource buffer -> supplied retail mission bytes; isolated in-memory fixture");steps++;continue;}
                if(pc==0x0046fee0L){stub(name,pc,b.length,"resource logical byte length "+b.length);steps++;continue;}
                if(pc==0x0046fd40L){stub(name,pc,0,"resource-release operation (no live cache)");steps++;continue;}
                // Stub only the nested non-FSM world resource producers: their semantics
                // require renderer/world/AI initialization unavailable to this harness.
                if(pc==0x004b89e0L||pc==0x00493910L||pc==0x004b8750L||pc==0x004b7a90L||pc==0x004b8f40L){
                    stub(name,pc,1,"opaque world-section producer; original forwarding wrapper still executes");steps++;continue;
                }
                // The original nested ADEF parser and original revision/EXIT callbacks run.
                // The full original FSM importer/finalizer runs on single-load fixtures.
                // Paired parser-state tests stub this callback to avoid inventing mission teardown.
                if(pc==0x00409740L){
                    fsmCalls++;
                    if(keep){fsmStubbed++;stub(name,pc,1,"FSM callback simulated on repeated-load tests; no FSM teardown state modeled");steps++;continue;}
                    fsmNative++;logEvent(name,"ORIGINAL_FSM_IMPORT",pc,"original retail FSM importer and finalizer executed");
                }
                if(pc==u32(0x004bc110L)){stdcallStub(name,pc,0x60000000L,12,"Windows HeapCreate -> synthetic handle; original FSM caller executes");steps++;continue;}
                if(pc==u32(0x004bc108L)){
                    long sp=reg("ESP"),size=u32(sp+12);
                    if(size>1024*1024)throw new IllegalStateException("oversize HeapAlloc request="+size);
                    long ptr=nextHeap;nextHeap+=(size+15)&~15L;nextHeap+=16;
                    w(ptr,new byte[(int)Math.max(size,4)]);
                    stdcallStub(name,pc,ptr,12,"HeapAlloc native import simulated size="+size+" ptr="+hex(ptr));steps++;continue;
                }
                if(pc==0x00401320L){stub(name,pc,1,"player object exists in synthetic world context");steps++;continue;}
                // If the no-op marker lacks analysis bytes, native instructions still execute.
                if(!emu.step(monitor)){failed=true;reason="instruction "+Long.toHexString(pc)+" error "+emu.getLastError();logEvent(name,"EMULATION_FAILURE",pc,"recent="+recent.toString());break;}
                steps++;
            }
            if(!returned&&!failed)reason="instruction limit exceeded at "+hex(reg("EIP"));
            long ret=reg("EAX"),cursor=u32(GLOBAL_CURSOR),end=u32(GLOBAL_END);
            String outcome=String.join("\t",name,hasBWD?"stock":"missing_BWD2",badRevision?"wrong_REV":"valid_REV",mutation,
                String.valueOf(returned),reason,hex(ret),hex(cursor),hex(end),
                hex(bwdBefore),hex(u32(ROOT_DESCRIPTOR+12)),hex(worldBefore),hex(u32(WORLD_DESCRIPTOR+12)),
                hex(adefBefore),hex(u32(ADEF_DESCRIPTOR+12)),String.valueOf(steps),
                String.valueOf(rootParses),String.valueOf(worldParses),String.valueOf(adefParses),String.valueOf(fsmCalls),
                String.valueOf(fsmNative),String.valueOf(fsmStubbed),
                String.valueOf(u32(0x0051f60cL)),String.valueOf(u32(0x0051f614L)),String.valueOf(u32(0x0051f61cL)),
                String.valueOf(u32(0x0051f624L)),String.valueOf(u32(0x0051f62cL)),String.valueOf(u32(0x0051f634L)),
                String.valueOf(u32(0x0051f63cL)),String.valueOf(revCalls),String.valueOf(reports),String.valueOf(stubCounts));
            for(String event:notable)writer.write(event+"\n");writer.flush();
            return outcome;
        }finally{if(!keep){emu.dispose();emu=null;}}
    }
    String hex(long n){return String.format(Locale.ROOT,"%08X",n&0xffffffffL);}
    @Override public void run() throws Exception {
        if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))
            throw new IllegalStateException("Retail PE MD5 mismatch");
        String[] ar=getScriptArgs();if(ar.length<2)throw new IllegalArgumentException("Arguments: <results-dir> <stock-M06.MSN-file>");
        File output=new File(ar[0]);output.mkdirs();stockMission=Files.readAllBytes(Paths.get(ar[1]));
        if(stockMission.length<1000||!Arrays.equals(Arrays.copyOfRange(stockMission,0,4),"BWD2".getBytes(StandardCharsets.US_ASCII)))throw new IllegalArgumentException("not a stock BWD2 mission");
        writer=new FileWriter(new File(output,"instruction_events.tsv"));writer.write("scenario\ttype\tpc\tdetail\n");
        try(FileWriter results=new FileWriter(new File(output,"wrapper_outcomes.tsv"))){
            results.write("scenario\tfixture\trevision\tmutation\treturned\tstatus\twrapper_eax\tglobal_cursor\tglobal_end\tbwd_before\tbwd_after\tworld_before\tworld_after\tadef_before\tadef_after\tsteps\troot_calls\tworld_calls\tadef_calls\tfsm_callbacks_entered\tfsm_native_runs\tfsm_stubbed_runs\tcommand_count\tmedia_count\tposition_count\tactor_count\tnode_count\tinitial_word_count\ttoken_count\trevision_callbacks\treporter_calls\tstub_address_counts\n");
            for(Object[] x:(ar.length>2 && ar[2].equals("nonempty")?new Object[][]{{"W11_T01_nonempty",true,false,"none"}}:new Object[][]{{"W01_stock_cold",true,false,"none"},{"W02_missing_cold",false,false,"none"},{"W03_bad_rev_cold",true,true,"none"},
                {"W07_wrong_AREV",true,false,"wrong_AREV"}, {"W08_missing_FSM",true,false,"missing_FSM"},
                {"W09_missing_ADEF",true,false,"missing_ADEF"},{"W10_missing_ADEF_EXIT",true,false,"missing_ADEF_EXIT"}})){
                String line=scenario((String)x[0],(Boolean)x[1],(Boolean)x[2],(String)x[3],false);
                results.write(line+"\n");println("WRAPPER_RESULT "+line);
            }
            if(!(ar.length>2&&ar[2].equals("nonempty")))for(Object[] x:new Object[][]{
                {"W04a_valid",true,false,"W04b_missing_warm",false,false},
                {"W05a_wrong_rev",true,true,"W05b_missing_warm",false,false},
                {"W06a_missing_cold",false,false,"W06b_valid_after",true,false}
            }){
                emu=new EmulatorHelper(currentProgram);
                try{
                    for(int j=0;j<2;j++){String line=scenario((String)x[j*3],(Boolean)x[j*3+1],(Boolean)x[j*3+2],"none",true);
                        results.write(line+"\n");println("WRAPPER_RESULT "+line);}
                }finally{emu.dispose();emu=null;}
            }
        }finally{writer.close();}
        println("WRAPPER_DONE "+output.getAbsolutePath());
    }
}
