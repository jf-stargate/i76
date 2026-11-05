import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.nio.file.*;
import java.math.BigInteger;
import java.util.*;
import java.io.*;
/* Original instructions, exact-integer finite FTOL substitute, replayed power.
 * Does not claim MSVCRT execution or architectural x87 CW semantics. */
public class NumericProbe extends GhidraScript {
 EmulatorHelper e; TreeSet<Long> seen=new TreeSet<>(); int ftols,pows,queries,stores; long steps; byte[] pe,power; int replayMismatch;
 Address a(long v){return toAddr(v&0xffffffffL);} long r(String n){return e.readRegister(n).longValue()&0xffffffffL;} long u(long p){byte[] b=e.readMemory(a(p),4);return ((b[0]&255L)|((b[1]&255L)<<8)|((b[2]&255L)<<16)|((b[3]&255L)<<24));}
 void w(long p,long v){e.writeMemoryValue(a(p),4,v);} String sha(byte[] b)throws Exception{StringBuilder s=new StringBuilder();for(byte x:java.security.MessageDigest.getInstance("SHA-256").digest(b))s.append(String.format("%02x",x&255));return s.toString();}
 BigInteger ext(byte[] b,int off){byte[] v=new byte[11];for(int k=0;k<10;k++)v[10-k]=b[off+k];return new BigInteger(v);}
 long trunc(BigInteger v){int ex=v.shiftRight(64).intValue()&32767; if(ex==32767)throw new IllegalStateException("nonfinite unsupported");BigInteger m=v.and(BigInteger.ONE.shiftLeft(64).subtract(BigInteger.ONE));int shift=(ex==0?1:ex)-16383-63;BigInteger i=shift<0?m.shiftRight(-shift):m.shiftLeft(shift);if(v.testBit(79))i=i.negate();if(i.bitLength()>63)throw new IllegalStateException("out of range unsupported");return i.longValue();}
 void pop(){for(int k=0;k<7;k++)e.writeRegister("ST"+k,e.readRegister("ST"+(k+1)));e.writeRegister("ST7",0);}
 void ret(){long sp=r("ESP"),pc=u(sp);e.writeRegister("ESP",sp+4);e.writeRegister("EIP",pc);}
 void reset(int cw){e=new EmulatorHelper(currentProgram);for(String rn:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})e.writeRegister(rn,0);e.writeRegister("ESP",0x30010000L);e.writeRegister("DF",0);e.writeRegister("FPUControlWord",cw);for(int k=0;k<8;k++)e.writeRegister("ST"+k,0);e.writeMemory(a(0x30000000),new byte[0x20000]);}
 void call(long target,long...args)throws Exception{long sp=0x30010000;w(sp,0x70000000);for(int k=0;k<args.length;k++)w(sp+4+4*k,args[k]);e.writeRegister("ESP",sp);e.writeRegister("EIP",target);for(long n=0;n<150000000L;n++){long pc=r("EIP");if(pc==0x70000000){steps+=n;return;}
 if(pc==0x4ba090){seen.add(pc);if(!e.step(monitor))throw new Exception("FTOL thunk");long v=trunc(e.readRegister("ST0"));pop();e.writeRegister("EAX",v&0xffffffffL);e.writeRegister("EDX",v>>32);ftols++;ret();continue;}
 if(pc==0x4ba2b6){seen.add(pc);if(!e.step(monitor))throw new Exception("power thunk");if(pows>=2560)throw new Exception("power bound");int at=pows*30;if(!e.readRegister("ST1").equals(ext(power,at))||!e.readRegister("ST0").equals(ext(power,at+10)))replayMismatch++;pop();pop();for(int k=7;k>0;k--)e.writeRegister("ST"+k,e.readRegister("ST"+(k-1)));e.writeRegister("ST0",ext(power,at+20));pows++;ret();continue;}
 if(pc==0x4796a0)queries++;if(pc==0x4793a4||pc==0x4794af||pc==0x4794ed||pc==0x47950b)stores++;
 seen.add(pc);if(!e.step(monitor))throw new Exception(String.format("stop %08x: %s",pc,e.getLastError()));}throw new Exception("step bound");}
 long le(byte[]b,int at){return (b[at]&255L)|((b[at+1]&255L)<<8)|((b[at+2]&255L)<<16)|((b[at+3]&255L)<<24);}
 byte[] raw(long va,int n){int h=(int)le(pe,60),s=h+24+((pe[h+20]&255)|((pe[h+21]&255)<<8)),ns=(pe[h+6]&255)|((pe[h+7]&255)<<8);for(int k=0;k<ns;k++){int at=s+40*k;long rva=le(pe,at+12),size=le(pe,at+16),off=le(pe,at+20),x=va-0x400000-rva;if(x>=0&&x+n<=size)return Arrays.copyOfRange(pe,(int)(off+x),(int)(off+x+n));}throw new IllegalArgumentException("unmapped raw");}
 public void run()throws Exception{String[] z=getScriptArgs();pe=Files.readAllBytes(Path.of(z[0]));if(!sha(pe).equals("bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3"))throw new Exception("PE identity");byte[] pal=Files.readAllBytes(Path.of(z[1]));power=Files.readAllBytes(Path.of(z[3]));int cw=Integer.parseInt(z[4]);reset(cw);e.writeMemory(a(0x310000e8),pal);call(0x4791e0,0x31000000,0);Files.write(Path.of(z[2]+".lum"),e.readMemory(a(0x61b2a0),65536));long esp=r("ESP"),eax=r("EAX"),fcw=r("FPUControlWord");call(0x479860);Files.write(Path.of(z[2]+".gamma"),e.readMemory(a(0x6095a0),2560));
 byte[] supplied=new byte[65536];for(int k=0;k<65536;k++)supplied[k]=(byte)(k*73+(k>>8));e.writeMemory(a(0x32000000),supplied);int beforeFtol=ftols;call(0x4791e0,0x31000000,0x32000000);if(ftols!=beforeFtol||!Arrays.equals(supplied,e.readMemory(a(0x61b2a0),65536)))throw new Exception("supplied path");for(byte b:e.readMemory(a(0x63b2e0),32768))if(b!=(byte)255)throw new Exception("cache reset");
 int[] nearest=new int[3];call(0x4796a0,2,0,0);nearest[0]=(int)r("EAX")&255;call(0x4796a0,4,0,0);nearest[1]=(int)r("EAX")&255;call(0x4791e0,0x31000000,0x32000000);call(0x4796a0,4,0,0);nearest[2]=(int)r("EAX")&255;
 int checked=0;for(long pc:seen){var i=currentProgram.getListing().getInstructionAt(a(pc));int len=i==null?1:i.getLength();byte[] b=new byte[len];currentProgram.getMemory().getBytes(a(pc),b);if(!Arrays.equals(b,raw(pc,len)))throw new Exception("instruction mismatch");checked++;}
 String result="{\"direct_nearest\":"+Arrays.toString(nearest)+",\"supplied_copy_verified\":true,\"steps\":"+steps+",\"ftols\":"+ftols+",\"pows\":"+pows+",\"queries\":"+queries+",\"stores\":"+stores+",\"unique_pc_retail_checked\":"+checked+",\"power_operand_mismatches\":"+replayMismatch+",\"lum_return_eax\":"+eax+",\"lum_return_esp\":"+esp+",\"cw\":"+fcw+"}";Files.writeString(Path.of(z[2]+".json"),result+"\n");println(result);e.dispose();}
}
