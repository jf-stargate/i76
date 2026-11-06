import java.io.*;
import java.nio.file.*;
import java.util.*;
// Original instruction driver using the accepted M06 service harness.
//@category i76
public class CoordinateProbe extends TerrainHarnessBase {
 String active="init";
 @Override void observe(long pc)throws Exception {
  long ptr=-1,slot=-1,off=-1;
  if(pc==0x4931a4L){ptr=reg("EAX")+2*reg("ECX");off=reg("ECX");}
  if(pc==0x493652L){ptr=reg("EDX")+2*reg("EDI");off=reg("EDI");}
  if(pc==0x4936a5L){ptr=reg("ECX")+2*reg("EAX");off=reg("EAX");}
  if(pc==0x4936f8L){ptr=reg("ECX")+2*reg("EDX");off=reg("EDX");}
  if(pc==0x49373dL){ptr=reg("EAX")+2*reg("ECX");off=reg("ECX");}
  if(pc==0x49287bL){ptr=reg("EAX")+2*reg("ECX");off=reg("ECX");}
  if(pc==0x49319dL||pc==0x493736L)slot=reg("EAX");
  if(pc==0x49364bL||pc==0x49369eL)slot=reg("EDX");
  if(pc==0x4936f1L)slot=reg("ECX");
  if(slot>=0)log("SLOT",pc,"id="+active+";slot="+slot+";pointer="+hx(u32(0x644380L+slot*4)));
  if(ptr>=0)log("READ",pc,"id="+active+";address="+hx(ptr)+";sample="+off+";word="+hx(u32(ptr)&65535));
  if(pc==0x493760L)log("ROW0",pc,"id="+active+";bits="+hx(u32(reg("EBP")+12))+";cw="+hx(reg("FPUControlWord")));
  if(pc==0x49376cL)log("ROW1",pc,"id="+active+";bits="+hx(u32(reg("EBP")-4))+";cw="+hx(reg("FPUControlWord")));
  if(pc==0x49360bL)log("FLOOR",pc,"id="+active+";ix="+(int)u32(reg("EBP")-16)+";iz="+(int)u32(reg("EBP")-12)+";sx="+rd64(reg("EBP")+8)+";sz="+rd64(reg("EBP")+16));
 }
 public void run()throws Exception {
  String[] ar=getScriptArgs();
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("PE identity");
  missionBytes=Files.readAllBytes(Paths.get(ar[0]));terrainBytes=Files.readAllBytes(Paths.get(ar[1]));
  if(ar.length>5 && ar[5].equals("bit12"))for(int j=1;j<terrainBytes.length;j+=2)terrainBytes[j]^=0x10;
  if(ar.length>5 && ar[5].equals("alias")){
   int zm=tag(missionBytes,"ZMAP")+9;boolean done=false;
   for(int z=0;z<80&&!done;z++)for(int x=0;x<79&&!done;x++){
    int at=zm+z*80+x;if((missionBytes[at]&255)!=255&&(missionBytes[at+1]&255)!=255&&missionBytes[at]!=missionBytes[at+1]){
     missionBytes[at+1]=missionBytes[at];done=true;
    }
   }
   if(!done)throw new Exception("no alias candidate");
  }
  mode="host-pop";scenario=Paths.get(ar[0]).getFileName().toString();
  host=new ProcessBuilder(ar[4]).start();hostIn=new DataOutputStream(host.getOutputStream());hostOut=new DataInputStream(host.getInputStream());
  trace=new PrintWriter(ar[3]);trace.println("scenario\tkind\tpc\tdetail");
  try {
   reset(new byte[64],"terrain.msn");
   mem(TER,terrainBytes.length);e.writeMemory(a(TER),terrainBytes);mem(MSN,missionBytes.length);e.writeMemory(a(MSN),missionBytes);
   tdefOff=tag(missionBytes,"TDEF");
   runCall(0x493c50L);
   runCall(0x493910L,MSN+tdefOff+8,0,MSN+tdefOff+u32(MSN+tdefOff+4));
   log("INIT",0x493910L,"eax="+reg("EAX")+";step="+hx(u32(0x6442c0L))+";reciprocal="+hx(u32(0x6442c4L)));
   Files.write(Paths.get(ar[3]+".grid.bin"),e.readMemory(a(0x644380L),65536));
   Files.write(Paths.get(ar[3]+".default.bin"),e.readMemory(a(0x59c588L),32768));
   for(String line:Files.readAllLines(Paths.get(ar[2]))) {
    if(line.isEmpty()||line.startsWith("#"))continue;
    String[] c=line.split("\t");active=c[0];String kind=c[1];double x=Double.parseDouble(c[2]),z=Double.parseDouble(c[3]);
    log("CASE",0,"id="+active+";kind="+kind+";x="+x+";z="+z);
    if(kind.equals("sample")) {runCall(0x493160L,(long)x,(long)z);log("RESULT",0x493160L,"id="+active+";value="+(reg("EAX")&65535));}
    else {
     runCall(0x493550L,darg(x,false),darg(x,true),darg(z,false),darg(z,true));
     log("RESULT",0x493550L,"id="+active+";value="+x87()+";st0="+e.readRegister("ST0").toString(16)+";cw="+hx(reg("FPUControlWord")));pop87();
     runCall(0x4927b0L,darg(x,false),darg(x,true),darg(z,false),darg(z,true));
     log("CLASS",0x4927b0L,"id="+active+";value="+(reg("EAX")&65535));
     runCall(0x4931c0L,0x26008000L,darg(x,false),darg(x,true),darg(z,false),darg(z,true));
     log("NORMAL",0x4931c0L,"id="+active+";bits="+vec(0x26008000L,3)+";eax="+hx(reg("EAX")));
    }
   }
  } finally {trace.close();if(e!=null)e.dispose();hostIn.close();int code=host.waitFor();if(code!=0)throw new Exception("x87 exit "+code);}
 }
}
