import ghidra.app.script.GhidraScript;import ghidra.app.decompiler.*;import ghidra.program.model.address.*;import ghidra.program.model.listing.*;import java.io.*;import java.util.*;
public class I76_TransformConstantsAudit extends GhidraScript{
 Address a(long x){return toAddr(x);}
 int word(long x){byte[] b=new byte[4];try{currentProgram.getMemory().getBytes(a(x),b);}catch(Exception e){return -1;}return (b[0]&255)|((b[1]&255)<<8)|((b[2]&255)<<16)|((b[3]&255)<<24);}
 public void run()throws Exception{try(PrintWriter o=new PrintWriter(new FileWriter(getScriptArgs()[0]))){long[] constants={0x004bd03c,0x004bd040,0x004bd05c,0x004bd060,0x004bd064,0x004bd074,0x004bd078,0x004faed8,0x004fe420,0x0052b93c,0x0052b940,0x0052b944};for(long x:constants){int bits=word(x);o.printf("%08X word=%08X float=%g\n",x,bits,Float.intBitsToFloat(bits));}
 o.println("ORIGINAL MAT4 CONSTANT:");for(int i=0;i<16;i++){int bits=word(0x004faed8+i*4);o.printf("%d:%08X/%g ",i,bits,Float.intBitsToFloat(bits));}o.println();
 Function f=getFunctionContaining(a(0x495000));DecompInterface di=new DecompInterface();di.openProgram(currentProgram);if(f!=null){o.println("NORMALIZATION HELPER="+f.getName()+" "+f.getSignature());DecompileResults d=di.decompileFunction(f,50,monitor);o.println(d.decompileCompleted()?d.getDecompiledFunction().getC():d.getErrorMessage());for(Instruction i:currentProgram.getListing().getInstructions(f.getBody(),true))o.println(i.getAddress()+" "+i.toString());}di.dispose();
 o.println("OBJECT MATRIX CREATORS -- first hundred writes to [REG+0x30] or [REG+0x38] candidates");int n=0;for(Instruction i:currentProgram.getListing().getInstructions(true)){String s=i.toString();if((s.toLowerCase().contains("+ 0x30]")||s.toLowerCase().contains("+ 0x34]")||s.toLowerCase().contains("+ 0x38]"))&&(s.toUpperCase().startsWith("MOV ")||s.toUpperCase().startsWith("FST")||s.toUpperCase().startsWith("LEA "))){o.println(i.getAddress()+" "+s);if(++n>=170)break;}}
 }}
}
