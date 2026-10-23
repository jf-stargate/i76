import ghidra.app.script.GhidraScript;import ghidra.app.emulator.EmulatorHelper;import ghidra.program.model.address.Address;import java.io.*;import java.util.*;
public class I76_CameraNativeProbe extends GhidraScript{
 static final long SENT=0x70000000L,STACK=0x31000000L;EmulatorHelper e;PrintWriter out;
 Address a(long p){return toAddr(p&0xffffffffL);}long reg(String n){return e.readRegister(n).longValue()&0xffffffffL;}
 long u32(long p){byte[] b=e.readMemory(a(p),4);return (b[0]&255L)|((b[1]&255L)<<8)|((b[2]&255L)<<16)|((b[3]&255L)<<24);}
 void w32(long p,long v){e.writeMemoryValue(a(p),4,v&0xffffffffL);}float f(long p){return Float.intBitsToFloat((int)u32(p));}
 @Override public void run()throws Exception{
 if(!currentProgram.getExecutableMD5().equalsIgnoreCase("a640ea0097dbb62e0c77b7f2847c7161"))throw new Exception("retail mismatch");
 out=new PrintWriter(new FileWriter(getScriptArgs()[0]));e=new EmulatorHelper(currentProgram);try{
 e.writeMemory(a(STACK-0x10000L),new byte[0x11000]);for(String s:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})e.writeRegister(s,0);e.writeRegister("DF",0);
 w32(0x5dd2a8L,2);w32(0x654b8aL,0);
 for(long p=0x5dcec0L;p<0x5dcfc0L;p+=4)w32(p,0);
 w32(0x5dcedcL,0);w32(0x5dcee0L,0);w32(0x5dcee4L,479);w32(0x5dcee8L,639);
 long sp=STACK-0x100;w32(sp,SENT);w32(sp+4L,0);e.writeRegister("ESP",sp);e.writeRegister("EIP",0x405970L);
 int max=450000;int steps=0;boolean done=false;java.util.ArrayDeque<String> hist=new java.util.ArrayDeque<>();
 for(;steps<max;steps++){long pc=reg("EIP");if(pc==SENT){done=true;break;}if(hist.size()>24)hist.removeFirst();hist.addLast(Long.toHexString(pc));if(pc==0x004ba090L){java.math.BigInteger ext=e.readRegister("ST0");int exponent=ext.shiftRight(64).and(java.math.BigInteger.valueOf(0x7fffL)).intValue();double mant=ext.and(java.math.BigInteger.ONE.shiftLeft(64).subtract(java.math.BigInteger.ONE)).doubleValue();double value=(exponent==0&&mant==0)?0:Math.scalb(mant,exponent-16383-63);if(ext.testBit(79))value=-value;int converted=(int)value;long sp3=reg("ESP"),next3=u32(sp3);e.writeRegister("ESP",sp3+4);e.writeRegister("EIP",next3);e.writeRegister("EAX",converted&0xffffffffL);out.printf("FTOL_BOUNDARY\t004BA090\tconverted=%d\tvalue=%.9g\tST0=%s%n",converted,value,ext.toString(16));continue;}
   if(pc==0x0049d400L){long arg=u32(reg("ESP")+4L);float radians=Float.intBitsToFloat((int)arg);long sp2=reg("ESP"),next=u32(sp2);e.writeRegister("ESP",sp2+4);e.writeRegister("EIP",next);e.writeRegister("EAX",Float.floatToRawIntBits((float)Math.sin(radians))&0xffffffffL);e.writeRegister("EDX",Float.floatToRawIntBits((float)Math.cos(radians))&0xffffffffL);out.printf("MATH_BOUNDARY\t0049D400\tinput=%08X\tsin=%08X\tcos=%08X%n",arg,reg("EAX"),reg("EDX"));continue;}
   if(!e.step(monitor)){out.println("ERROR\tpc="+Long.toHexString(pc)+";details="+e.getLastError()+";history="+hist);break;}}
 out.println("CAMERA_INIT\tcompleted="+done+";steps="+steps+";eax="+Long.toHexString(reg("EAX")));
 for(long off:new long[]{0,4,8,0x1c,0x20,0x24,0x28,0x30,0x34,0x38,0x3c,0x40,0x44,0x48,0x4c,0x50,0x54,0x58,0x5c,0x60,0x68,0x70,0x78,0xa4,0xa8,0xe8,0xec,0xf8,0xfc,0x1d4}){long p=0x4c2730L+off;out.printf("CAMERA_FIELD\t%03X\t%08X\t%+.9g%n",off,u32(p),f(p));}
 if(!done)throw new Exception("Original camera initialization did not complete");
 }finally{out.close();e.dispose();}
 }
}
