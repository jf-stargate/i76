// @category I76
import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import java.io.*;
import java.util.*;
public class V27NativeNeighborMatrix extends GhidraScript {
 static final long RET=0x7000fff0L, ST=0x70001000L, A=0x70002000L, B=0x70002010L, SEC=0x70002100L;
 static long u(int v){return ((long)v)&0xffffffffL;}
 static String key(int x,int y){return x+","+y;}
 void word(EmulatorHelper e,long a,long v){e.writeMemoryValue(toAddr(a),4,v);}
 void flt(EmulatorHelper e,long a,float f){word(e,a,u(Float.floatToRawIntBits(f)));}
 long reg(EmulatorHelper e,String r){return e.readRegister(r).longValue()&0xffffffffL;}
 void scenario(int mode,int seedheight,int seedmaterial,PrintWriter o) throws Exception {
  EmulatorHelper e=new EmulatorHelper(currentProgram);
  Map<String,Integer> heights=new TreeMap<>(),materials=new TreeMap<>();
  heights.put(key(20,20),seedheight);materials.put(key(20,20),seedmaterial);
  int nclassifier=0,nneighbor=0,nread=0,nmatRead=0,nHeightWrites=0,nMatWrites=0,cycles=0;
  List<String> changes=new ArrayList<>();boolean ended=false;String err="";
  try {
   e.writeRegister("ESP",ST);e.writeRegister("EIP",0x421df0);
   for(String r:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})e.writeRegister(r,0);
   e.writeRegister("FPUControlWord",0x037f);e.writeRegister("FPUStatusWord",0);e.writeRegister("FPUTagWord",0xffff);
   e.writeStackValue(0,4,RET);e.writeStackValue(4,4,A);e.writeStackValue(8,4,B);e.writeStackValue(12,4,u(Float.floatToRawIntBits(1f)));
   flt(e,A,20f);flt(e,A+4,20f);flt(e,B,22f);flt(e,B+4,20f);
   word(e,0x43c12c,mode);word(e,0x43c130,1);word(e,0x43c114,SEC);
   word(e,SEC+8,600);word(e,SEC+20,600);
   word(e,0x4379f4,1);word(e,0x4379fc,2);word(e,0x437a00,0);
   flt(e,0x4379d8,19f);flt(e,0x4379e0,19f);flt(e,0x4379e8,25f);flt(e,0x4379f0,25f);
   for(long addr:new long[]{RET,0x401046,0x4013c0,0x401244,0x401474,0x4010eb,0x409210})e.setBreakpoint(toAddr(addr));
   for(cycles=0;cycles<12000;cycles++){
    boolean ok=e.run(monitor);long ip=reg(e,"EIP");
    if(!ok){err="run failed at "+Long.toHexString(ip)+" "+e.getLastError();break;}
    if(ip==RET){ended=true;break;}
    if(ip==0x4010eb){nneighbor++;if(!e.step(monitor))throw new RuntimeException("neighbor thunk failed");continue;}
    if(ip==0x409210){nclassifier++;if(!e.step(monitor))throw new RuntimeException("classifier failed");continue;}
    if(ip==0x401046||ip==0x4013c0||ip==0x401244||ip==0x401474){
     long esp=reg(e,"ESP");long ret=e.readStackValue(0,4,false).longValue();
     int x=(int)e.readStackValue(4,4,false).longValue();int y=(int)e.readStackValue(8,4,false).longValue();
     String k=key(x,y);
     if(ip==0x401046){nmatRead++;e.writeRegister("EAX",materials.getOrDefault(k,0));}
     else if(ip==0x4013c0){nread++;int pl=(int)e.readStackValue(12,4,false).longValue();e.writeRegister("EAX",pl==1?heights.getOrDefault(k,0x8000):0);}
     else if(ip==0x401244){int value=(int)e.readStackValue(12,4,false).longValue();heights.put(k,value&0xffff);nHeightWrites++;changes.add("H "+k+" "+value);}
     else{int m=(int)e.readStackValue(12,4,false).longValue();materials.put(k,m);nMatWrites++;changes.add("M "+k+" "+m);}
     e.writeRegister("ESP",esp+4);e.writeRegister("EIP",ret&0xffffffffL);continue;
    }
    err="unexpected stop "+Long.toHexString(ip);break;
   }
   o.println("SCENARIO mode="+mode+" seedheight="+seedheight+" seedmaterial="+seedmaterial+" returned="+ended+" cycles="+cycles+" classifier="+nclassifier+" original_neighbor_calls="+nneighbor+" height_reads="+nread+" surface_reads="+nmatRead+" height_writes="+nHeightWrites+" surface_writes="+nMatWrites+" valid_cells="+heights.size()+" error="+err);
   for(String c:changes)o.println(c);
   if(!ended)throw new RuntimeException("Scenario did not finish "+err);
  }finally{e.dispose();}
 }
 public void run() throws Exception {
  if(!currentProgram.getExecutableMD5().equalsIgnoreCase("4c7ed9e8a54fcadbf1895f34aa9918fe"))throw new RuntimeException("input mismatch");
  try(PrintWriter o=new PrintWriter(new FileWriter(getScriptArgs()[0]))){
   o.println("Original 00421df0 + 00409210 + 00421be0 instructions. Replaced terrain getter/setters only, synthetic terrain map; x87 EmulatorHelper warning applies.");
   scenario(3,600,6,o);scenario(5,600,6,o);scenario(5,600,0,o);
  }
  println("V27_NATIVE_NEIGHBOR_OK");
 }
}
