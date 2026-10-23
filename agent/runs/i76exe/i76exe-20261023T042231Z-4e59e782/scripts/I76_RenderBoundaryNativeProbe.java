import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;
public class I76_RenderBoundaryNativeProbe extends GhidraScript {
 static final long STACK=0x34002000L,SENT=0x74000000L,BKT=0x00533DD8L,DEPTHROOT=0x005DD328L;
 static final long OWNER=0x25301230L,GROUP=0x26001000L,OTHER=0x26001100L,S1=0x26002000L,S2=0x26002100L,S3=0x26002200L;
 EmulatorHelper e; PrintWriter out;String test;int steps,vqm,m16; List<String> events=new ArrayList<>();
 Address a(long v){return toAddr(v&0xffffffffL);}long reg(String x){return e.readRegister(x).longValue()&0xffffffffL;}
 void w32(long p,long v){e.writeMemoryValue(a(p),4,v&0xffffffffL);}long u32(long p){byte[] b=e.readMemory(a(p),4);if(b==null||b.length<4)throw new RuntimeException("bad read "+Long.toHexString(p));return (b[0]&255L)|((b[1]&255L)<<8)|((b[2]&255L)<<16)|((b[3]&255L)<<24);}
 void init(){e=new EmulatorHelper(currentProgram);e.writeMemory(a(STACK-0x1000),new byte[0x3000]);e.writeMemory(a(GROUP),new byte[0x2000]);w32(0x005DD328L,0);w32(0x005DD32CL,0);for(String r:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})e.writeRegister(r,0);e.writeRegister("DF",0);steps=vqm=m16=0;events.clear();}
 void ret(long v){long sp=reg("ESP"),next=u32(sp);e.writeRegister("ESP",sp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",v);}
 String cstr(long p){StringBuilder s=new StringBuilder();for(int i=0;i<40;i++){byte[] b=e.readMemory(a(p+i),1);if(b==null||b[0]==0)break;s.append((char)(b[0]&255));}return s.toString();}
 void nstr(long p,String s){e.writeMemory(a(p),(s+"\0").getBytes(StandardCharsets.ISO_8859_1));}
 long hash(long owner){return (((owner*0x6cdL+0xaabL)&0xffffffffL)%0x71L);}
 void call(long addr,long... args)throws Exception{long sp=STACK;w32(sp,SENT);for(int k=0;k<args.length;k++)w32(sp+4L+4L*k,args[k]);e.writeRegister("ESP",sp);e.writeRegister("EIP",addr);boolean finished=false;
   for(int i=0;i<2000;i++){
     long pc=reg("EIP");if(pc==SENT){finished=true;break;}steps++;
     if(pc==0x00447b20L){vqm++;events.add("VQM:"+cstr(u32(reg("ESP")+4)));ret(1);continue;}
     if(pc==0x00471b70L){m16++;events.add("M16:"+cstr(u32(reg("ESP")+8)));ret(1);continue;}
     if(!e.step(monitor))throw new RuntimeException("step failed "+String.format("%08x",pc)+" "+e.getLastError());
   }if(!finished)throw new RuntimeException("steps exhausted");
 }
 void result(String detail){out.println(test+"\t"+steps+"\t"+reg("EAX")+"\t"+vqm+"\t"+m16+"\t"+String.join(",",events)+"\t"+detail);out.flush();}
 void check(boolean ok,String what){if(!ok)throw new RuntimeException(test+": "+what);}
 void slot(long adr,String name,long flags,long cached,long next){nstr(adr+4,name);w32(adr+0x34,cached);w32(adr+0x38,cached+1);w32(adr+0x3c,flags);w32(adr+0x44,next);}
 void setupGroup(long first){w32(BKT+4*hash(OWNER),GROUP);w32(GROUP,OWNER);w32(GROUP+4,first);w32(GROUP+8,0);}
 void trial(String name,int mode)throws Exception{test=name;init();try{
   w32(BKT+4*hash(OWNER),0);
   if(mode==1){setupGroup(0);}
   if(mode==2){setupGroup(S1);slot(S1,"texOne.map",0,0xabc01234L,S2);slot(S2,"texTwo.map",1,0xabc01235L,S3);slot(S3,"texThree.map",2,0xabc01236L,0);}
   if(mode==3){setupGroup(S1);slot(S1,"texOne.map",0,0xabc01234L,S2);slot(S2,"texTwo.map",1,0xabc01235L,S3);slot(S3,"texThree.map",2,0xabc01236L,0);}
   if(mode==4){w32(BKT+4*hash(OWNER),OTHER);w32(OTHER,OWNER+1);w32(OTHER+8,0);}
   call(0x0044A0B0L,OWNER);
   if(mode==0||mode==4){check(reg("EAX")==0&&vqm==0&&m16==0,"no-object result");}
   if(mode==1){check(reg("EAX")==1&&vqm==0&&m16==0,"empty list");}
   if(mode==2||mode==3){check(reg("EAX")==1,"nonempty result");check(vqm==1&&m16==3,"expected three per-slot handles and one stale VQM release");check(u32(S1+0x34)==0 && (u32(S1+0x3c)&2)==2,"native cache invalidate");check(u32(S2+0x34)==0xabc01235L && u32(S2+0x3c)==1,"slot flag1 preserved");check(u32(S3+0x34)==0xabc01236L && u32(S3+0x3c)==2,"slot flag2 preserved");
     // Re-run on same original state and verify VQM invalidation is idempotent, M16 helper still invoked.
     if(mode==3){vqm=0;m16=0;events.clear();call(0x0044A0B0L,OWNER);check(vqm==0 && m16==3,"repeat invalidation sequence");}
   }
   result(mode==2||mode==3?"s1_cache="+u32(S1+0x34)+";s1_flags="+u32(S1+0x3c)+";s2_flags="+u32(S2+0x3c)+";s3_flags="+u32(S3+0x3c):"owner="+Long.toHexString(OWNER));
 }finally{e.dispose();}}
 public void run()throws Exception{
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("Retail executable mismatch");
  String path=getScriptArgs()[0];out=new PrintWriter(new FileWriter(path));out.println("scenario\toriginal_steps\teax\tvqm_intercepts\tm16_intercepts\tboundary_events\tasserted_state");
  for(int k=0;k<5;k++)trial(new String[]{"NO_OWNER","EMPTY_BINDINGS","MIXED_FLAGS","REPEAT_REFRESH","HASH_COLLISION"}[k],k);
  out.close();println("RENDER_NATIVE_PROBE_PASSED cases=5 file="+path);
 }
}
