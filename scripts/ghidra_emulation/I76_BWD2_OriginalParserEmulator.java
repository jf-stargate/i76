// Copyright (c) research checkpoint v0.5.0; requires Ghidra 12.1.4
// Executes RETAIL i76.exe instructions for the BWD2 parser. No rewriting/parsing logic here.
import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.*;

public class I76_BWD2_OriginalParserEmulator extends GhidraScript {
    static final long PARSER=0x004b3db0L, BWD_DESC=0x00500328L, REV_DESC=0x00500338L;
    static final long FIXTURE=0x20000000L, STACK=0x30010000L, FILENAME=0x20020000L, SENTINEL=0x70000000L;
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
        byte[] data=emu.readMemory(a(addr),limit);int n=0;while(n<data.length&&data[n]!=0)n++;
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
    byte[] loadFixture(boolean hasBWD) throws Exception {
        // Exact first two stock chunks from retail M06.MSN (BWD2 + REV=2).
        byte[] header=new byte[]{0x42,0x57,0x44,0x32,8,0,0,0,0x52,0x45,0x56,0,12,0,0,0,2,0,0,0};
        return hasBWD?header:Arrays.copyOfRange(header,8,20);
    }
    String execute(String name,boolean hasBWD,boolean warm,int revResult,boolean preserveSession) throws Exception {
        if(emu==null)emu=new EmulatorHelper(currentProgram);notable.clear();steps=revInterceptions=reports=bwdCallbacks=crtInterceptions=unknownCalls=0;
        try {
            if(warm){w32(BWD_DESC+12,0x00c4);}
            long before=u32(BWD_DESC+12), revBefore=u32(REV_DESC+12);
            byte[] bytes=loadFixture(hasBWD);
            w(FIXTURE,bytes);
            // Revision-data mutation is confined to the emulated fixture, never to a game file.
            if(revResult!=2)w32(FIXTURE+(hasBWD?16:8),revResult);
            w(FILENAME,"M06.MSN\0".getBytes(StandardCharsets.US_ASCII));
            long esp=STACK-0x1000;
            // cdecl 7 arguments, return sentinel. Registered operands are originals from 004B44C8.
            long[] args={SENTINEL,FIXTURE,BWD_DESC,2,0,FILENAME,1,FIXTURE+bytes.length};
            for(int i=0;i<args.length;i++)w32(esp+4L*i,args[i]);
            emu.writeRegister("ESP",esp);emu.writeRegister("EIP",PARSER);
            emu.writeRegister("EAX",0);emu.writeRegister("ECX",0);emu.writeRegister("EDX",0);
            emu.writeRegister("EBX",0);emu.writeRegister("ESI",0);emu.writeRegister("EDI",0);emu.writeRegister("EBP",0);
            boolean reached=false,failed=false;String reason="";boolean reqEncountered=false;
            for(int i=0;i<LIMIT;i++){
                long pc=reg("EIP");
                if(pc==SENTINEL){reached=true;reason="returned";break;}
                if(pc==0x004b3f31L){logEvent(name,"seen_store",pc,String.format("descriptor=%08X flags_before=%08X",reg("EDI"),u32(reg("EDI")+12)));}
                if(pc==0x004b4160L || pc==0x004b4163L){reqEncountered=true;logEvent(name,"required_check",pc,String.format("flags=%08X",u32(BWD_DESC+12)));}
                if(pc==0x004b4177L){logEvent(name,"required_error",pc,"required BWD2 absent from descriptor history");}
                if(pc==0x004b41afL){logEvent(name,"parser_null_branch",pc,"EAX will be cleared");}
                if(pc==0x004b41bbL){logEvent(name,"parser_nonnull_branch",pc,"readable cursor expected");}
                // Parser AND REV callback execute their ORIGINAL i76.exe x86 instructions.
                // Only external Windows C runtime imports are emulated.
                if(pc==0x004b4610L){revInterceptions++;logEvent(name,"REV_callback_enter",pc,"original retail body");}
                if(pc==IMPORT_SPLITPATH){runtimeSplitpath(name,pc);steps++;continue;}
                if(pc==IMPORT_STRICMP){runtimeStricmp(name,pc);steps++;continue;}
                if(pc==IMPORT_STRNCPY){
                    // Imported MSVCRT strncpy. The host OS's CRT isn't mapped into Ghidra's PE image;
                    // emulate ONLY the standard C library copy and return, preserving parser instructions.
                    long crtEsp=reg("ESP"), dest=u32(crtEsp+4), src=u32(crtEsp+8), count=u32(crtEsp+12);
                    if(count>64)throw new IllegalStateException("unbounded strncpy stub: "+count);
                    byte[] orig=emu.readMemory(a(src),(int)count), copy=Arrays.copyOf(orig,orig.length);
                    boolean nul=false;for(int j=0;j<copy.length;j++){if(nul)copy[j]=0;else if(copy[j]==0)nul=true;}
                    w(dest,copy);crtInterceptions++;logEvent(name,"CRT_strncpy_stub",pc,String.format("from=%08X to=%08X count=%d",src,dest,count));
                    callbackReturn(dest);steps++;continue;
                }
                if(pc==0x004b8960L){bwdCallbacks++;}
                if(pc==0x0042d5d0L){reports++;}
                if(!emu.step(monitor)){failed=true;reason="Ghidra emulation step failed: "+emu.getLastError()+" at 0x"+Long.toHexString(pc);break;}
                steps++;
            }
            if(!reached&&!failed)reason="step limit reached";
            long result=reg("EAX"),after=u32(BWD_DESC+12),revAfter=u32(REV_DESC+12);
            String status=String.format(Locale.ROOT,"%s\t%s\t%s\t%d\t%08X\t%08X\t%08X\t%08X\t%d\t%d\t%d\t%s\t%s",name,hasBWD?"stock":"missing_BWD2",warm?"warm_seeded":((before&0x80)!=0?"warm_retained":"cold"),steps,before,after,revBefore,revAfter,revInterceptions,crtInterceptions,reports,reached?"true":"false",reached?(result==0?"NULL":String.format("%08X",result)):reason.replace('\t',' '));
            for(String line:notable){writer.write(line+"\n");}writer.flush();
            return status;
        }finally{if(!preserveSession){emu.dispose();emu=null;}}
    }
    @Override public void run() throws Exception {
        if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new IllegalStateException("unexpected retail PE MD5: "+currentProgram.getExecutableMD5());
        String[] args=getScriptArgs();String dir=args.length>0?args[0]:"/mnt/data/i76_parser_emulation_v0.5.0/results";
        File output=new File(dir);output.mkdirs();
        writer=new FileWriter(new File(output,"instruction_events.tsv"));writer.write("scenario\ttype\tpc\tdetail\n");
        try(FileWriter tsv=new FileWriter(new File(output,"emulation_outcomes.tsv"))){
            tsv.write("scenario\tfixture\tinitial_state\tsteps\tbwd_flags_before\tbwd_flags_after\trev_flags_before\trev_flags_after\tnative_rev_callbacks_entered\texternal_crt_calls_stubbed\treporter_calls\treturned\teax_or_failure\n");
            for(Object[] x:new Object[][]{{"C01_stock_cold",true,false,2},{"C02_missing_cold",false,false,2},{"C03_missing_warm",false,true,2},{"C04_stock_warm",true,true,2},{"C05_rev_rejected",true,false,3}}){
                String line=execute((String)x[0],(Boolean)x[1],(Boolean)x[2],(Integer)x[3],false);
                tsv.write(line+"\n");println("EMU_RESULT "+line);
            }
            // TRUE repeated parser calls against the same emulated memory and descriptor table:
            // the second call inherits flags written by the first ORIGINAL x86 execution.
            for(Object[] pair:new Object[][]{
                {"C06a_session1_stock",true,2,"C06b_session1_missing",false,2},
                {"C07a_session2_missing",false,2,"C07b_session2_stock",true,2},
                {"C08a_session3_stock",true,2,"C08b_session3_rev_reject",true,3},
                {"C09a_session4_bad_rev",true,3,"C09b_session4_missing",false,2},
                {"C10a_session5_missing_bad_rev",false,3,"C10b_session5_missing_valid_rev",false,2}
            }){
                emu=new EmulatorHelper(currentProgram);
                try {
                    for(int k=0;k<2;k++){
                        String nm=(String)pair[k*3], line=execute(nm,(Boolean)pair[k*3+1],false,(Integer)pair[k*3+2],true);
                        tsv.write(line+"\n");println("EMU_RESULT "+line);
                    }
                }finally{emu.dispose();emu=null;}
            }
        } finally {writer.close();}
        println("EMULATOR_DONE output="+dir);
    }
}
