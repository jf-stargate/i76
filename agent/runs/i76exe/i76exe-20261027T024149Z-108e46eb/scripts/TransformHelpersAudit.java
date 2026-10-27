import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import java.util.*;import java.io.*;
public class TransformHelpersAudit extends GhidraScript {
 Address a(long p){return toAddr(p);}
 public void run()throws Exception{long[] ts={0x493CA0L,0x494C80L,0x494710L,0x49C7A0L,0x467440L,0x407210L,0x407236L,0x406D40L,0x493E60L,0x472990L,0x437F90L};
 try(PrintWriter o=new PrintWriter(new FileWriter(getScriptArgs()[0]))){DecompInterface di=new DecompInterface();di.openProgram(currentProgram);for(long t:ts){Function f=getFunctionContaining(a(t));o.println("==== "+String.format("%08X",t)+" FUNC "+(f==null?"NONE":f.getName()+" @ "+f.getEntryPoint()+" .. "+f.getBody().getMaxAddress()));if(f==null)continue;
  DecompileResults rr=di.decompileFunction(f,50,monitor);o.println(rr.decompileCompleted()?rr.getDecompiledFunction().getC():rr.getErrorMessage());o.println("----- INSTRUCTIONS");int n=0;
  for(Instruction in:currentProgram.getListing().getInstructions(f.getBody(),true)){o.println(in.getAddress()+" "+in.toString()+" "+(in.getFlowType().isCall()?Arrays.toString(in.getFlows()):""));if(++n>=800)break;}
 }di.dispose();}
 }
}
