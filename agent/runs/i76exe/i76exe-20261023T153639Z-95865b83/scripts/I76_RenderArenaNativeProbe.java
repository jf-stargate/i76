import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;
import java.util.*;
public class I76_RenderArenaNativeProbe extends GhidraScript {
 static final long TARGET=0x0048f9b0L,SENT=0x70000000L,STACK=0x31000000L;
 EmulatorHelper e; PrintWriter out;int calls=0,steps=0;long cursor=0x24000000L;
 Address a(long p){return toAddr(p&0xffffffffL);}long reg(String s){return e.readRegister(s).longValue()&0xffffffffL;}
 long read(long p){byte[] b=e.readMemory(a(p),4);return (b[0]&255L)|((b[1]&255L)<<8)|((b[2]&255L)<<16)|((b[3]&255L)<<24);}
 void put(long p,long v){e.writeMemoryValue(a(p),4,v&0xffffffffL);}
 void ret(long value){long sp=reg("ESP"),next=read(sp);e.writeRegister("ESP",sp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",value);}
 void hexlog(String key,long val){out.printf("%s\t%08X%n",key,val);}
 @Override public void run() throws Exception {
 if(!currentProgram.getExecutableMD5().equalsIgnoreCase("a640ea0097dbb62e0c77b7f2847c7161"))throw new Exception("retail program identity");
 String[] args=getScriptArgs();out=new PrintWriter(new FileWriter(args[0]));e=new EmulatorHelper(currentProgram);
 try{
  e.writeMemory(a(0x24000000L),new byte[0x200000]);e.writeMemory(a(STACK-0x10000),new byte[0x11000]);
  for(String s:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})e.writeRegister(s,0);
  put(STACK-0x100,SENT);e.writeRegister("ESP",STACK-0x100);e.writeRegister("EIP",TARGET);e.writeRegister("DF",0);
  boolean done=false;
  for(int i=0;i<2000000;i++){
   steps=i;long pc=reg("EIP");if(pc==SENT){done=true;break;}
   if(pc==0x00498940L || pc==0x00499ce0L){long sp=reg("ESP"),size=read(sp+4),align=pc==0x00498940L?read(sp+8):0;long v=cursor;cursor=(cursor+size+15L)&~15L;calls++;
    out.printf("ALLOC\t%d\t%08X\tsize=%d\talign=%d\tret=%08X%n",calls,pc,size,align,v);ret(v);continue;
   }
   if(!e.step(monitor))throw new Exception("emulator stopped at "+Long.toHexString(pc)+": "+e.getLastError());
  }
  if(!done)throw new Exception("native 0048F9B0 incomplete");
  out.println("RETURN\t"+reg("EAX")+"\tsteps="+steps+"\tallocations="+calls);
  for(long g:new long[]{0x654398,0x65439c,0x6543c0,0x6543bc,0x654390,0x6543b8,0x6543b0,0x654388,0x654384,0x6543a8,0x6543b4,0x6543a0,0x65438c,0x59c540})hexlog(String.format("G_%08X",g),read(g));
  long aBase=read(0x6543b0L),bBase=read(0x654388L);
  int nonzero=0;
  for(int j=0;j<4096;j++){for(int k=0;k<3;k++){if(read(aBase+12L*j+4*k)!=0)nonzero++;if(read(bBase+12L*j+4*k)!=0)nonzero++;}}
  out.println("TABLE_VERIFY\tentriesPerTable=4096\tstride=12\tnonzero="+nonzero);
  if(calls!=5||reg("EAX")!=1||nonzero!=0||read(0x654384)!=aBase+0xC000L||read(0x6543a8)!=bBase+0xC000L)throw new Exception("native arena contract differs");
 }finally{e.dispose();out.close();}
 }
}
