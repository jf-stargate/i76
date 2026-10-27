import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.util.*;
import java.io.*;
public class I76_WorldTransformIsolatedProbe extends GhidraScript {
 static final long OBJ=0x23000000L,RT=0x23001000L,OUT=0x23002000L,STACK=0x30020000L,RETURN=0x70000000L;
 EmulatorHelper e;PrintWriter o;String scenario;long steps;int callsProj,callsCross,callsBasis,callsNorm;long last;String status;
 Address a(long x){return toAddr(x&0xffffffffL);}long reg(String s){return e.readRegister(s).longValue()&0xffffffffL;}
 long u32(long p){byte[] v=e.readMemory(a(p),4);if(v==null||v.length!=4)throw new RuntimeException("read fault:"+Long.toHexString(p));return ((long)v[0]&255)|(((long)v[1]&255)<<8)|(((long)v[2]&255)<<16)|(((long)v[3]&255)<<24);}
 void w32(long p,long x){e.writeMemoryValue(a(p),4,x&0xffffffffL);}void f(long p,float v){w32(p,Float.floatToRawIntBits(v));}
 void mem(long p,int n){e.writeMemory(a(p),new byte[n]);}
 int bad(long p,int count){int n=0;for(int i=0;i<count;i++){float v=Float.intBitsToFloat((int)u32(p+4*i));if(!Float.isFinite(v))n++;}return n;}
 String matrix(long p){StringBuilder s=new StringBuilder();for(int i=0;i<16;i++){if(i>0)s.append(',');long b=u32(p+i*4);s.append(String.format(Locale.ROOT,"%08x",b));}return s.toString();}
 void event(String what,String s){o.printf("%s\t%s\t%s%n",scenario,what,s);}
 void reset(){e=new EmulatorHelper(currentProgram);mem(OBJ,0x1000);mem(RT,0x1000);mem(OUT,0x1000);mem(STACK-0x3000,0x4000);w32(OBJ+0x70,RT);for(int i=0;i<16;i++)w32(OUT+4L*i,0xccccccccL);for(String rr:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})e.writeRegister(rr,0);e.writeRegister("DF",0);e.writeRegister("ESP",STACK-0x2000L);e.writeRegister("EIP",0x00437f90L);w32(STACK-0x2000L,RETURN);w32(STACK-0x1ffcL,OUT);w32(STACK-0x1ff8L,OBJ);
  f(0x004fe420L,0.016f);f(0x0052b93cL,0);f(0x0052b940L,0);f(0x0052b944L,0);
  steps=0;callsProj=callsCross=callsBasis=callsNorm=0;status="";last=0;
 }
 void runCase(String name,int klass,float[] axis,float[] root,float[] impulse,float angle1,float angle2)throws Exception {scenario=name;reset();try{
  w32(OBJ+0x6c,klass);for(int i=0;i<3;i++){f(OBJ+0x18L+4*i,axis[i]);f(OBJ+0x30L+4*i,root[i]);f(RT+0xd4L+4*i,impulse[i]);}
  f(RT+0x114L,angle1);f(RT+0x118L,angle2);event("INPUT","class="+klass+";axis="+Arrays.toString(axis)+";direction="+Arrays.toString(root)+";runtimeD4="+Arrays.toString(impulse)+";runtime114="+angle1+";runtime118="+angle2+";delta=0.016");
  for(int i=0;i<60000;i++){
   long pc=reg("EIP");steps++;last=pc;
   if(pc==RETURN){status="RETURN";break;}
   if(pc==0x00493ca0L){callsProj++;event("ORIGINAL_PROJECTION_ENTER","pc=00493CA0");}
   if(pc==0x00494c80L){callsCross++;event("ORIGINAL_CROSS_ENTER","pc=00494C80");}
   if(pc==0x00494710L){callsBasis++;event("ORIGINAL_BASIS_ENTER","pc=00494710");}
   if(pc==0x00495000L){callsNorm++;event("ORIGINAL_INV_LENGTH_ENTER","pc=00495000");}
   if(pc==0x00438100L)event("PROJECTION_DONE","g1="+Integer.toHexString((int)u32(0x52b93cL)));
   if(!e.step(monitor)){status="ERROR:"+e.getLastError();break;}
  }
  event("RESULT","status="+status+";pc="+String.format("%08X",last)+";steps="+steps+";proj="+callsProj+";cross="+callsCross+";basis="+callsBasis+";normalize="+callsNorm+";nonfinite="+bad(OUT,16)+";matrix="+matrix(OUT)+";g1="+String.format("%08X",u32(0x0052b93cL))+";g2="+String.format("%08X",u32(0x0052b940L))+";g3="+String.format("%08X",u32(0x0052b944L)));
 }finally{e.dispose();e=null;}}
 public void run()throws Exception{if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("retail mismatch");try(PrintWriter p=new PrintWriter(new FileWriter(getScriptArgs()[0]))){o=p;o.println("scenario\tevent\tdetail");float[] zero={0,0,0},vx={1,0,0},vy={0,1,0},vz={0,0,1},vi={3,4,2};runCase("nonvehicle",30,vx,zero,zero,0,0);runCase("vehicle_zero_direction",1,vx,zero,vi,1,2);runCase("vehicle_direction_z",1,vx,vz,vi,1,2);runCase("vehicle_direction_x",1,vy,vx,vi,1,2);runCase("vehicle_direction_z_zero_runtime",1,vx,vz,zero,0,0);}}
}
