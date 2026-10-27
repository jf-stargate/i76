import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;
import java.util.*;
public class I76_Flag10NativeProbe extends GhidraScript {
 static final long OBJ=0x21000000L, STACK=0x31010000L, SENT=0x70000000L;
 EmulatorHelper e; PrintWriter out; int services;
 Address a(long n){return toAddr(n & 0xffffffffL);}
 String h(long n){return String.format(Locale.ROOT,"%08X",n&0xffffffffL);}
 long reg(String x){return e.readRegister(x).longValue() & 0xffffffffL;}
 long read(long n){byte[] b=e.readMemory(a(n),4);if(b==null||b.length!=4)throw new IllegalStateException("Read at "+h(n));return (b[0]&255L)|((b[1]&255L)<<8)|((b[2]&255L)<<16)|((b[3]&255L)<<24);}
 void write(long n,long val){e.writeMemoryValue(a(n),4,val&0xffffffffL);}
 void setup(int id,int local,int team){
   e=new EmulatorHelper(currentProgram);services=0;e.writeMemory(a(OBJ),new byte[0x200]);
   e.writeMemory(a(STACK-0x10000),new byte[0x11000]);
   write(0x541028L,local);write(OBJ+0x10,0);
   write(STACK+0x70,(long)team<<16);
   for(String rr:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})e.writeRegister(rr,0);
   e.writeRegister("EBX",OBJ);e.writeRegister("EBP",id);e.writeRegister("ESP",STACK);e.writeRegister("DF",0);
 }
 int steps(long start,long target, boolean service)throws Exception{
   e.writeRegister("EIP",start);
   for(int i=0;i<300;i++){
     long pc=reg("EIP");if(pc==target)return i;
     if(service&&(pc==0x454700L||pc==0x4ad640L)){services++;
       long sp=reg("ESP"),ret=read(sp);e.writeRegister("ESP",sp+4);e.writeRegister("EAX",pc==0x4ad640L ? 0x21005000 : 0);e.writeRegister("EIP",ret);continue;
     }
     if(!e.step(monitor))throw new Exception("x86 emulation error at "+h(pc)+" "+e.getLastError());
   }
   throw new Exception("Timed out at "+h(reg("EIP")));
 }
 long predicate()throws Exception{
   long sp=STACK-0x3000;write(sp,SENT);write(sp+4,OBJ);
   e.writeRegister("ESP",sp);e.writeRegister("EIP",0x458bf0L);
   for(int i=0;i<20;i++){
     if(reg("EIP")==SENT)return reg("EAX");
     if(!e.step(monitor))throw new Exception("Native flag predicate error "+h(reg("EIP"))+": "+e.getLastError());
   }
   throw new Exception("Predicate did not return");
 }
 void scenarioA(String name,int id,int local,int team)throws Exception{
   setup(id,local,team);
   try{
     int count=steps(0x451286L,0x4512caL,true);count+=steps(0x4512caL,0x4512e5L,true);
     long actual=read(OBJ+0x10),expect=((long)team<<16)|((id&0xffff)==(local&0xffff)?0x10L:0x20L);
     long elig=predicate(),expectedElig=(expect&0x10)!=0?1:0;
     out.printf(Locale.ROOT,"%s\t00451180\t%d\t%d\t%d\t%08X\t%08X\t%d\t%d\t%d\t%d\t%s%n",name,id,local,team,actual,expect,elig,expectedElig,services,count,actual==expect&&elig==expectedElig&&services==2?"PASS":"FAIL");
     if(elig!=expectedElig)throw new Exception("VLOC predicate mismatch "+name);
     if(actual!=expect)throw new Exception("First spawn wrong "+name+" "+h(actual));
   }finally{e.dispose();e=null;}
 }
 void scenarioB(String name,int flag)throws Exception{
   setup(flag,0,0);
   try{
     int count=steps(0x451452L,0x451471L,false);count+=steps(0x451471L,0x45148bL,true);
     long actual=read(OBJ+0x10),expect=(flag!=0?0x10010L:0x20000L);
     long elig=predicate(),expectedElig=(expect&0x10)!=0?1:0;
     out.printf(Locale.ROOT,"%s\t004513C0\t%d\t-\t-\t%08X\t%08X\t%d\t%d\t%d\t%d\t%s%n",name,flag,actual,expect,elig,expectedElig,services,count,actual==expect&&elig==expectedElig&&services==1?"PASS":"FAIL");
     if(elig!=expectedElig)throw new Exception("VLOC predicate mismatch "+name);
     if(actual!=expect)throw new Exception("Second spawn wrong "+name+" "+h(actual));
   }finally{e.dispose();e=null;}
 }
 public void run()throws Exception{
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("Wrong original retail image");
  try(PrintWriter w=new PrintWriter(new FileWriter(getScriptArgs()[0]))){out=w;w.println("scenario\tfunction\tspawn_id_or_flag\tlocal_id\tteam\tstatus_actual\tstatus_expected\tvloc_eligibility\tvloc_expected\tintercepted_services\tinstructions\tresult");
    scenarioA("player_matched",3,3,5);scenarioA("player_unmatched",2,3,5);scenarioA("id_zero_matched",0,0,0);
    scenarioA("id_wrap_low16",0x10003,3,1); // EBP used as short 16-bit ID
    scenarioB("startup_secondary",0);scenarioB("startup_primary",1);scenarioB("startup_nonzero",9);
  }
 }
}
