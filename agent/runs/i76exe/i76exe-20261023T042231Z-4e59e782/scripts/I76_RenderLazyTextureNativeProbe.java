import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;import java.nio.charset.StandardCharsets;
public class I76_RenderLazyTextureNativeProbe extends GhidraScript {
 static final long OWNER=0x25301230L,SLOT=0x26003000L,GROUP=0x26001000L,NAME=SLOT+0x14L,STACK=0x34002000L,SENT=0x74000000L;
 static final long BUCKETS=0x00533FA0L,OBJECTBUCKETS=0x00533DD8L,NEW_VQM=0x2900BEEFL;
 EmulatorHelper e;PrintWriter trace;String caseName;int steps,comparisons,loads,releases,m16Calls;
 Address a(long v){return toAddr(v&0xffffffffL);}void w(long p,long v){e.writeMemoryValue(a(p),4,v&0xffffffffL);}long r(String n){return e.readRegister(n).longValue()&0xffffffffL;}
 long u(long p){byte[] b=e.readMemory(a(p),4);return (b[0]&255L)|((b[1]&255L)<<8)|((b[2]&255L)<<16)|((b[3]&255L)<<24);}
 void ret(long val){long sp=r("ESP"),ra=u(sp);e.writeRegister("ESP",sp+4);e.writeRegister("EIP",ra);e.writeRegister("EAX",val);}
 String str(long a){StringBuilder s=new StringBuilder();for(int i=0;i<48;i++){byte[] b=e.readMemory(a(a+i),1);if(b==null||b[0]==0)break;s.append((char)(b[0]&255));}return s.toString();}
 long slotIndex(){long hash=0;String key="texOne.map";for(char c:key.toCharArray())hash=((hash*2)^(c&0xdf))&0xffffffffL;return (((hash^OWNER)*0x6cdL+0xaabL)&0xffffffffL)%0x7edL;}
 void init(){e=new EmulatorHelper(currentProgram);e.writeMemory(a(0x26000000L),new byte[0x8000]);e.writeMemory(a(STACK-0x1000),new byte[0x2000]);comparisons=loads=releases=m16Calls=steps=0;
  String key="texOne.map";e.writeMemory(a(NAME),(key+"\0").getBytes(StandardCharsets.ISO_8859_1));
  e.writeMemory(a(SLOT+4),("texOne.map\0").getBytes(StandardCharsets.ISO_8859_1));w(SLOT,OWNER);w(SLOT+0x30,0x26005100L);w(SLOT+0x34,0x12345678L);w(SLOT+0x38,0x87654321L);w(SLOT+0x3c,0);w(SLOT+0x40,0);w(SLOT+0x44,0);
  w(BUCKETS+4*slotIndex(),SLOT);w(OBJECTBUCKETS+4*((OWNER*0x6cdL+0xaabL&0xffffffffL)%0x71L),GROUP);w(GROUP,OWNER);w(GROUP+4,SLOT);w(GROUP+8,0);
  for(String name:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})e.writeRegister(name,0);e.writeRegister("DF",0);
 }
 void call(long dest,long...args)throws Exception{w(STACK,SENT);for(int k=0;k<args.length;k++)w(STACK+4L+4*k,args[k]);e.writeRegister("ESP",STACK);e.writeRegister("EIP",dest);
  boolean finished=false;for(int i=0;i<3000;i++){
   long pc=r("EIP"),sp=r("ESP");if(pc==SENT){finished=true;break;}steps++;
   if(pc==0x447b20L){releases++;ret(1);continue;}
   if(pc==0x471b70L){m16Calls++;ret(1);continue;}
   if(pc==u(0x4bc210L)){comparisons++;ret(str(u(sp+4)).equalsIgnoreCase(str(u(sp+8)))?0:1);continue;}
   if(pc==0x4474b0L){loads++;if(!str(u(sp+4)).equalsIgnoreCase("texOne.map"))throw new Exception("wrong lazy-load name");ret(NEW_VQM);continue;}
   if(!e.step(monitor))throw new Exception("original step error "+Long.toHexString(pc)+" "+e.getLastError());
  }if(!finished)throw new Exception("limit reached");}
 void check(boolean yes,String msg){if(!yes)throw new IllegalStateException(msg);}
 void log(String phase){trace.println(phase+"\t"+steps+"\t"+r("EAX")+"\t"+loads+"\t"+releases+"\t"+m16Calls+"\t"+comparisons+"\t"+u(SLOT+0x34)+"\t"+u(SLOT+0x3c)+"\t"+u(SLOT+0x30));trace.flush();}
 public void run()throws Exception{
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("retail mismatch");
  trace=new PrintWriter(new FileWriter(getScriptArgs()[0]));trace.println("phase\tcumulative_original_steps\teax\tvqm_load_stubs\tvqm_release_stubs\tm16_release_stubs\tstrcmp_stubs\tslot_vqm_cache\tslot_flags\ttmt_record_ptr");init();try{
    call(0x44a290L,OWNER,NAME,0);check(r("EAX")==0x12345678L && loads==0,"initial cache hit");log("HIT_BEFORE_REFRESH");
    call(0x44a0b0L,OWNER);check(r("EAX")==1&&releases==1&&m16Calls==1&&u(SLOT+0x34)==0&&u(SLOT+0x3c)==2,"refresh invalidates VQM only");log("AFTER_REFRESH");
    call(0x44a290L,OWNER,NAME,0);check(r("EAX")==NEW_VQM&&loads==1&&u(SLOT+0x34)==NEW_VQM&&u(SLOT+0x3c)==0,"native reload updates slot");log("LAZY_RELOAD");
    call(0x44a290L,OWNER,NAME,0);check(r("EAX")==NEW_VQM&&loads==1,"subsequent cache reuse");log("REUSE_AFTER_RELOAD");
    check(u(SLOT+0x30)==0x26005100L,"TMT record identity changed");
  }finally{trace.close();e.dispose();}println("RENDER_LAZY_BIND_NATIVE_PASSED phases=4");
 }
}
