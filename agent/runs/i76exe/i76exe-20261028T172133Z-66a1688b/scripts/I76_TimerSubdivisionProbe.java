// Execute original clock initialization and frame subdivision helpers.
//@category i76
import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;import java.math.BigInteger;
public class I76_TimerSubdivisionProbe extends GhidraScript {
 EmulatorHelper e;static final long SP=0x30020000L,STOP=0x70000000L,TIMER=0x26000000L;
 Address a(long p){return toAddr(p);} long u(long p){byte[] b=e.readMemory(a(p),4);long v=0;for(int i=0;i<4;i++)v|=(b[i]&255L)<<(8*i);return v;}
 void w(long p,long v){e.writeMemoryValue(a(p),4,v);}long reg(String r){return e.readRegister(r).longValue()&0xffffffffL;}
 double fp(){BigInteger x=e.readRegister("ST0");int exp=x.shiftRight(64).intValue()&32767;double v=(exp==0&&x.signum()==0)?0:Math.scalb(x.and(BigInteger.ONE.shiftLeft(64).subtract(BigInteger.ONE)).doubleValue(),exp-16383-63);return x.testBit(79)?-v:v;}
 void pop(){for(int i=0;i<7;i++)e.writeRegister("ST"+i,e.readRegister("ST"+(i+1)));}
 void ret(long v){long sp=reg("ESP"),pc=u(sp);e.writeRegister("ESP",sp+4);e.writeRegister("EIP",pc);e.writeRegister("EAX",v);}
 void call(long pc,long...args)throws Exception{
  w(SP,STOP);for(int i=0;i<args.length;i++)w(SP+4+i*4,args[i]);e.writeRegister("ESP",SP);e.writeRegister("EIP",pc);
  for(int n=0;n<10000;n++){pc=reg("EIP");if(pc==STOP)return;
   if(pc==u(0x004bc100L)){ret(1000);continue;}
   if(pc==0x004ba090L){int value=(int)fp();pop();ret(value&0xffffffffL);continue;}
   if(!e.step(monitor))throw new Exception(e.getLastError());
  }throw new Exception("limit");
 }
 public void run()throws Exception{
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("MD5");
  try(PrintWriter out=new PrintWriter(getScriptArgs()[0])){
   out.println("clock_initialized\tdt_bits\tdt\trate\tcount\tstep_bits\tstep\tpositive_returns\tterminated");
   for(int init=0;init<2;init++)for(float dt:new float[]{0,0.001f,1f/60f,0.05f,0.1f,0.2f,1f,2f}){
    e=new EmulatorHelper(currentProgram);try{
     e.writeMemory(a(SP-0x1000),new byte[0x2000]);e.writeMemory(a(TIMER),new byte[16]);for(int k=0;k<8;k++)e.writeRegister("ST"+k,BigInteger.ZERO);
     if(init==1)call(0x0049c7f0L);call(0x0049cbe0L,TIMER,0x3d4ccccdL);w(0x004fe420L,Float.floatToRawIntBits(dt)&0xffffffffL);call(0x0049cc20L,TIMER);
     long count=u(TIMER+8),step=u(TIMER+4);int positive=0;boolean terminated=false;
     for(int k=0;k<22;k++){call(0x0049cca0L,TIMER);double value=fp();pop();if(value<=0){terminated=true;break;}positive++;}
     out.printf(java.util.Locale.ROOT,"%d\t%08X\t%.12g\t%.12g\t%d\t%08X\t%.12g\t%d\t%b%n",init,Float.floatToRawIntBits(dt),dt,Float.intBitsToFloat((int)u(TIMER)),count,step,Float.intBitsToFloat((int)step),positive,terminated);
    }finally{e.dispose();}
   }
  }
 }
}
