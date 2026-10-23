import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import java.io.*;
import java.util.*;
public class V25ClassifierDifferential extends GhidraScript {
 static int model(int ax,int ay,int bx,int by,int px,int py) {
  int dx=bx-ax,dy=by-ay;
  int cross=(px-ax)*dy+(ax-bx)*(py-ay);
  if(Math.abs(cross)>=Math.max(Math.abs(dx),Math.abs(dy)))return 0;
  if((bx<ax&&ax<px)||(by<ay&&ay<py))return 1;
  if((px<ax&&ax<bx)||(py<ay&&ay<by))return 1;
  if((ax<bx&&bx<px)||(ay<by&&by<py))return 3;
  if((px<bx&&bx<ax)||(py<by&&by<ay))return 3;
  return 2;
 }
 static int[] generate(int i,Random rng){
  int[] a=new int[6];
  if(i<128){
   a[0]=(i%16)-8;a[1]=(i/16)-4;
   int k=(i/8)%8;
   int[] dx={0,1,3,7,10,-1,-3,-10},dy={10,3,1,0,-10,-7,-1,3};
   a[2]=a[0]+dx[k];a[3]=a[1]+dy[k];
   a[4]=a[0]+(i%9)-4;a[5]=a[1]+(i%7)-3;
  }else if(i<640){
   a[0]=rng.nextInt(70)-35;a[1]=rng.nextInt(70)-35;
   a[2]=a[0]+rng.nextInt(35)-17;a[3]=a[1]+rng.nextInt(35)-17;
   a[4]=a[0]+rng.nextInt(50)-25;a[5]=a[1]+rng.nextInt(50)-25;
  }else if(i<768){
   a[0]=rng.nextInt(10000)-5000;a[1]=rng.nextInt(10000)-5000;
   a[2]=a[0]+rng.nextInt(3000)-1500;a[3]=a[1]+rng.nextInt(3000)-1500;
   a[4]=a[0]+rng.nextInt(3000)-1500;a[5]=a[1]+rng.nextInt(3000)-1500;
  }else{for(int j=0;j<6;j++)a[j]=rng.nextInt();}
  return a;
 }
 public void run()throws Exception{
  PrintWriter out=new PrintWriter(new FileWriter(getScriptArgs()[0]));
  out.println("PROGRAM="+currentProgram.getName()+" MD5="+currentProgram.getExecutableMD5());
  Random rng=new Random(0x1762026L);
  int errors=0,mismatch=0;int[] counts=new int[4];
  for(int i=0;i<896;i++){
   int[] a=generate(i,rng);
   EmulatorHelper emu=new EmulatorHelper(currentProgram);
   try{
    emu.writeRegister("ESP",0x70001000L);
    emu.writeRegister("EIP",0x409210L);
    for(String reg:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})emu.writeRegister(reg,0);
    emu.writeStackValue(0,4,0x7000fff0L);
    for(int j=0;j<6;j++)emu.writeStackValue(4+j*4,4,a[j]);
    emu.setBreakpoint(toAddr(0x7000fff0L));
    boolean ok=emu.run(monitor);
    int got=emu.readRegister("EAX").intValue();
    int exp=model(a[0],a[1],a[2],a[3],a[4],a[5]);
    if(!ok){errors++;out.println("ERROR "+i+" "+emu.getLastError());}
    else if(got!=exp){mismatch++;out.println("MISMATCH "+i+" "+Arrays.toString(a)+" "+got+" expected "+exp);}
    else counts[got]++;
   }catch(Throwable t){errors++;out.println("EXCEPTION "+i+" "+t);}
   finally{emu.dispose();}
  }
  out.println("CASES=896 MISMATCHES="+mismatch+" EMULATION_ERRORS="+errors+
              " COUNTS="+Arrays.toString(counts));
  out.close();
  println("Classifier differential errors="+errors+" mismatches="+mismatch);
  if(errors!=0||mismatch!=0)throw new RuntimeException("Differential validation failed");
 }
}
