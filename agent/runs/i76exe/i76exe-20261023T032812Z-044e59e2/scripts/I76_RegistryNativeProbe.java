// Retail i76.exe (MD5 a640ea0097dbb62e0c77b7f2847c7161) native x86 registry study.
// Executes original i76.exe Ghidra p-code; OS/CRT/ownership calls are separately logged substitutes.
import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class I76_RegistryNativeProbe extends GhidraScript {
 static final long INIT=0x004ad410, APPEND=0x004ad450, LOOKUP=0x004ad5b0, DESTROY=0x004ad600,
    REGISTER=0x00457610, FIND=0x00457630, ACTOR=0x00412400, REPORT=0x0042d5d0,
    INCREMENT=0x0045ed00, SUPPRESS=0x00452d20, SET_TAURUS=0x0040aeb0;
 static final long CTX=0x0054a178L, HEAP=0x22000000L, STACK=0x30010000L, SENTINEL=0x70000000L,
    ACTORS=0x23000000L, OBJ_A=0x24000100L, OBJ_B=0x24000200L;
 EmulatorHelper emu; PrintWriter out; long steps;int reports,refs,duplicates,heapReallocs,heapAllocations,heapFrees,heapDestroys, suppressVal=0;
 long nextHeap=HEAP; boolean reallocSuccess=true; String active="";
 Address a(long x){return toAddr(x&0xffffffffL);}
 long reg(String s){return emu.readRegister(s).longValue()&0xffffffffL;}
 long u32(long x){byte[] b=emu.readMemory(a(x),4);return ((long)(b[0]&255)|((long)(b[1]&255)<<8)|((long)(b[2]&255)<<16)|((long)(b[3]&255)<<24))&0xffffffffL;}
 void w32(long x,long val){emu.writeMemoryValue(a(x),4,val&0xffffffffL);}
 void w(long x,byte[] b){emu.writeMemory(a(x),b);}
 String hex(long v){return String.format(Locale.ROOT,"%08X",v&0xffffffffL);}
 String str(long x,int max){StringBuilder b=new StringBuilder();for(int i=0;i<max;i++){int c=emu.readMemory(a(x+i),1)[0]&255;if(c==0)break;b.append((char)c);}return b.toString();}
 void log(String type,long pc,String details){out.printf("%s\t%s\t%s\t%s\n",active,type,hex(pc),details);}
 void ret(long result,int args){long sp=reg("ESP"),pc=u32(sp);emu.writeRegister("ESP",(sp+4+args)&0xffffffffL);emu.writeRegister("EAX",result&0xffffffffL);emu.writeRegister("EIP",pc);}
 void call(long address,long... args) throws Exception {
   steps=0;long sp=STACK-0x200;w32(sp,SENTINEL);
   for(int i=0;i<args.length;i++)w32(sp+(i+1)*4,args[i]);
   emu.writeRegister("ESP",sp);emu.writeRegister("EIP",address);
   while(reg("EIP")!=SENTINEL){
     if(++steps>150000)throw new IllegalStateException(active+" step cap at "+hex(reg("EIP")));
     long pc=reg("EIP");
     // Original error reporter is a one-byte RET; observe but never replace its instruction.
     if(pc==REPORT){reports++;log("ORIGINAL_ERROR_RET",pc,"error routine reached; original RET executes");}
     if(pc==APPEND)log("ORIGINAL_APPEND_ENTRY",pc,"count="+u32(CTX+8)+" cap="+u32(CTX+12));
     if(pc==LOOKUP)log("ORIGINAL_LOOKUP_ENTRY",pc,"count="+u32(CTX+8));
     if(pc==0x004ad489L)log("ORIGINAL_GROWTH_BRANCH",pc,"HeapReAlloc EAX="+hex(reg("EAX")));
     if(pc==0x004ad598L)log("ORIGINAL_COUNT_INCREMENT",pc,"count_before="+u32(CTX+8));
     // Stop BEFORE the invalid-memory store on synthetic failed reallocation.
     if(active.equals("GROWTH_NULL_ENTRY") && pc==0x004ad57eL){
       log("STOP_BEFORE_NULL_BACKING_WRITE",pc,"calculated store_address="+hex(reg("EDX"))+" ctx.entries="+hex(u32(CTX+4))+" count="+u32(CTX+8));
       emu.writeRegister("EIP",SENTINEL);break;
     }
     // Non-engine external boundaries only; all original local instructions run.
     if(pc==u32(0x004bc110L)){log("STUB_HEAP_CREATE",pc,"stdcall args=12");ret(0x60000000L,12);continue;}
     if(pc==u32(0x004bc108L)){
       long n=u32(reg("ESP")+12),ptr=nextHeap;nextHeap+=(n+15)&~15L;nextHeap+=0x40;
       if(n>0x100000)throw new IllegalStateException("HeapAlloc oversize");
       w(ptr,new byte[(int)n]);heapAllocations++;
       log("STUB_HEAP_ALLOC",pc,"bytes="+n+" ptr="+hex(ptr));ret(ptr,12);continue;
     }
     if(pc==u32(0x004bc160L)){log("STUB_MSIZE",pc,"return 0x8000");ret(0x8000,0);continue;}
     if(pc==u32(0x004bc0e4L)){
       heapReallocs++;long ptr=reallocSuccess?u32(reg("ESP")+12):0;
       log("STUB_HEAP_REALLOC",pc,"requested="+u32(reg("ESP")+16)+" result="+hex(ptr));ret(ptr,16);continue;
     }
     if(pc==u32(0x004bc104L)){heapFrees++;log("STUB_HEAP_FREE",pc,"stdcall args=12");ret(1,12);continue;}
     if(pc==u32(0x004bc10cL)){heapDestroys++;log("STUB_HEAP_DESTROY",pc,"stdcall args=4");ret(1,4);continue;}
     if(pc==SUPPRESS){if(steps<50||!active.equals("GROWTH_NULL_ENTRY"))log("STUB_SUPPRESSION_QUERY",pc,"returns="+suppressVal);ret(suppressVal,0);continue;}
     if(pc==u32(0x004bc28cL)){ // strncpy(destination,source,n), cdecl
       long callerSp=reg("ESP"),dst=u32(callerSp+4),src=u32(callerSp+8),n=u32(callerSp+12);
       byte[] b=emu.readMemory(a(src),(int)Math.min(n,64));w(dst,b);log("STUB_STRNCPY",pc,"length="+n);ret(dst,0);continue;
     }
     if(pc==u32(0x004bc210L)){
       long callerSp=reg("ESP"),left=u32(callerSp+4),right=u32(callerSp+8);
       int result=str(left,80).compareToIgnoreCase(str(right,80));
       log("STUB_STRICMP",pc,"left="+str(left,48)+" right="+str(right,48)+" result="+result);ret(result,0);continue;
     }
     if(pc==INCREMENT){refs++;log("STUB_REF_ACQUIRE",pc,"object="+hex(u32(reg("ESP")+4))+" reason="+hex(u32(reg("ESP")+8)));ret(0,0);continue;}
     if(!emu.step(monitor))throw new IllegalStateException(active+" original step failed at "+hex(pc)+" / "+emu.getLastError());
   }
   log("FUNCTION_EXIT",address,"EAX="+hex(reg("EAX"))+" steps="+steps+" count="+u32(CTX+8));
 }
 void reset(){if(emu!=null)emu.dispose();emu=new EmulatorHelper(currentProgram);nextHeap=HEAP;reports=refs=duplicates=heapReallocs=heapAllocations=heapFrees=heapDestroys=0;reallocSuccess=true;suppressVal=0;}
 void assertEq(String what,long actual,long expect){if(actual!=expect)throw new IllegalStateException(active+" "+what+" expected "+hex(expect)+" got "+hex(actual));log("ASSERT_PASS",0,what+"="+hex(actual));}
 void actor(long where,String name,long k0,long k1){byte[] b=new byte[0x60];byte[] n=name.getBytes(StandardCharsets.US_ASCII);System.arraycopy(n,0,b,0,Math.min(n.length,39));w(where,b);w32(where+0x50,k0);w32(where+0x54,k1);}
 void initialize() throws Exception {active="INIT";call(INIT,CTX);assertEq("initialized capacity",u32(CTX+12),0x800);assertEq("initialized count",u32(CTX+8),0);assertEq("initial buffer",u32(CTX+4),HEAP);}
 void scenarioNative() throws Exception {
   reset();initialize();long key0=0x41424344L,key1=0x45464748L;
   active="MISS_COLD";call(FIND,key0,key1);assertEq("cold missing lookup",reg("EAX"),0);
   active="APPEND_FIRST";call(REGISTER,key0,key1,OBJ_A);assertEq("first append count",u32(CTX+8),1);assertEq("first ptr stored",u32(HEAP+8),OBJ_A);
   active="FIND_FIRST";call(FIND,key0,key1);assertEq("first matched pointer",reg("EAX"),OBJ_A);
   active="APPEND_DUPLICATE";int previousReports=reports;call(REGISTER,key0,key1,OBJ_B);assertEq("duplicate count",u32(CTX+8),2);assertEq("second ptr stored",u32(HEAP+0x18),OBJ_B);
   if(reports<=previousReports)throw new IllegalStateException("duplicate must reach original reporter");
   active="FIND_LATEST";call(FIND,key0,key1);assertEq("newest match",reg("EAX"),OBJ_B);
   active="OTHER_KEY_MISS";call(FIND,0x58585858,0x59595959);assertEq("unregistered other key",reg("EAX"),0);
   active="ACTOR_MISSING";actor(ACTORS,"missing",0x58585858,0x59595959);int before=refs;call(ACTOR,ACTORS,1);assertEq("missing actor ptr",u32(ACTORS+0x58),0);assertEq("missing actor acquire count",refs,before);
   active="ACTOR_TWO_SAME";actor(ACTORS,"same",key0,key1);actor(ACTORS+0x60,"same",key0,key1);before=refs;call(ACTOR,ACTORS,2);assertEq("same first binding",u32(ACTORS+0x58),OBJ_B);assertEq("same second binding",u32(ACTORS+0x60+0x58),OBJ_B);assertEq("same actor separate acq",refs-before,2);
   active="ACTOR_TWO_DIFFERENT";actor(ACTORS,"first",key0,key1);actor(ACTORS+0x60,"other",key0,key1);previousReports=reports;call(ACTOR,ACTORS,2);if(reports<previousReports+2)throw new IllegalStateException("differently named duplicate actors should report both comparisons");log("ASSERT_PASS",0,"different labels each reach original error routine");
   active="ACTOR_TAURUS";actor(ACTORS,"taurus",key0,key1);call(ACTOR,ACTORS,1);assertEq("taurus actor ptr",u32(ACTORS+0x58),OBJ_B);assertEq("taurus global cache",u32(0x0051f5c4L),OBJ_B);
   active="APPEND_SUPPRESSED_DUPLICATE";suppressVal=1;previousReports=reports;call(REGISTER,key0,key1,OBJ_A);assertEq("suppressed duplicate count",u32(CTX+8),3);assertEq("suppressed duplicate report count",reports,previousReports);
   active="FIND_SUPPRESSED_LATEST";call(FIND,key0,key1);assertEq("suppressed duplicate newest",reg("EAX"),OBJ_A);suppressVal=0;
   active="DESTROY";call(DESTROY,CTX);assertEq("destroyed buffer",u32(CTX+4),0);assertEq("destroyed count",u32(CTX+8),0);assertEq("destroyed capacity",u32(CTX+12),0);
   log("RESULT",0,"native registry and actor scenarios completed heapalloc="+heapAllocations+" refs_stub="+refs+" reporter_native="+reports+" free_stub="+heapFrees+" destroy_stub="+heapDestroys);
 }
 void scenarioGrowth()throws Exception{
   reset();initialize();
   active="GROWTH_SUCCESS_RETURN";
   w32(CTX+8,0x800);w32(CTX+12,0x800);
   call(APPEND,CTX,0x41424344L,0x45464748L,OBJ_A);
   assertEq("grow-success-return EAX",reg("EAX"),0);assertEq("grow-success count unchanged",u32(CTX+8),0x800);assertEq("grow-success buffer unchanged",u32(CTX+4),HEAP);
   assertEq("grow-success invoked realloc",heapReallocs,1);
   log("RESULT",0,"synthetic capacity reached; original non-null-branch returns without append");
   reset();initialize();active="GROWTH_NULL_ENTRY";
   w32(CTX+8,0x800);w32(CTX+12,0x800);reallocSuccess=false;suppressVal=1;
   call(APPEND,CTX,0x41424344L,0x45464748L,OBJ_A);
   assertEq("failed realloc nulled entries",u32(CTX+4),0);
   assertEq("failed realloc increased capacity",u32(CTX+12),0x900);
   assertEq("failed realloc count unchanged before store",u32(CTX+8),0x800);
   log("RESULT",0,"original failed-realloc branch sets backing buffer to null, increments capacity and advances toward invalid write; original write deliberately not executed");
 }
 @Override public void run() throws Exception {
   if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new IllegalArgumentException("Unexpected private retail executable");
   String[] args=getScriptArgs();if(args.length<1)throw new IllegalArgumentException("argument: output.tsv");
   try(PrintWriter pw=new PrintWriter(new FileWriter(args[0]))){out=pw;out.println("scenario\tevent\taddress\tdetail");
     try {scenarioNative();scenarioGrowth();}finally{if(emu!=null)emu.dispose();}
   }
   println("NATIVE_REGISTRY_PROBE_OK "+args[0]);
 }
}
