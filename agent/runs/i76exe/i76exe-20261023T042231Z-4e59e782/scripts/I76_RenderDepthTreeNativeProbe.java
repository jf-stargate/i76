import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;
import java.util.*;
public class I76_RenderDepthTreeNativeProbe extends GhidraScript {
 static final long ROOT_GLOBAL=0x0054AD28L,BASE=0x26100000L,ROOT=BASE+0x1000L,CAND=BASE+0x2000L,STACK=0x36200000L,SENT=0x74000000L;
 EmulatorHelper e;PrintWriter out;
 Address a(long x){return toAddr(x&0xffffffffL);} long r(String n){return e.readRegister(n).longValue()&0xffffffffL;}
 void w32(long p,long v){e.writeMemoryValue(a(p),4,v&0xffffffffL);}long u32(long p){byte[] b=e.readMemory(a(p),4);return (b[0]&255L)|((b[1]&255L)<<8)|((b[2]&255L)<<16)|((b[3]&255L)<<24);}
 void wf(long p,float f){w32(p,Float.floatToRawIntBits(f)&0xffffffffL);}
 String hx(long v){return String.format("%08x",v&0xffffffffL);}
 void runCase(String label,float x)throws Exception{
  e=new EmulatorHelper(currentProgram);e.writeMemory(a(BASE),new byte[0x4000]);e.writeMemory(a(STACK-0x1000),new byte[0x2000]);
  w32(ROOT_GLOBAL,ROOT);wf(ROOT+0x30,1);wf(ROOT+0x34,0);wf(ROOT+0x38,0);wf(ROOT+0x3c,0);w32(ROOT+0x40,0);w32(ROOT+0x44,0);
  wf(CAND+0x24,x);wf(CAND+0x28,0);wf(CAND+0x2c,0);w32(CAND+0x40,0);w32(CAND+0x44,0);
  w32(STACK,SENT);w32(STACK+4,CAND);e.writeRegister("ESP",STACK);e.writeRegister("EIP",0x0045cb80L);e.writeRegister("DF",0);
  boolean done=false;int steps=0;
  try {for(;steps<500;steps++){
   long pc=r("EIP");if(pc==SENT){done=true;break;}
   if(!e.step(monitor))throw new RuntimeException("native step "+hx(pc)+" "+e.getLastError());
  }
  if(!done)throw new RuntimeException("not terminated");
  boolean linked=u32(ROOT+0x40)==CAND || u32(ROOT+0x44)==CAND;
  if(!linked)throw new RuntimeException("neither depth link assigned at x="+x);
  out.printf("%s\t%f\t%d\t%s\t%s%n",label,x,steps,hx(u32(ROOT+0x40)),hx(u32(ROOT+0x44)));out.flush();
  }finally{e.dispose();}
 }
 public void run()throws Exception{if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new RuntimeException("retail MD5 mismatch");out=new PrintWriter(new FileWriter(getScriptArgs()[0]));out.println("scenario\tpoint_x\tsteps\troot_left_40\troot_right_44");try{runCase("POSITIVE",1000);runCase("NEGATIVE",-1000);}finally{out.close();}println("RENDER_DEPTH_TEST_OK");}
}
