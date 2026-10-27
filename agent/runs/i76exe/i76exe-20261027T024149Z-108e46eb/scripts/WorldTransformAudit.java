import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.lang.*;
import ghidra.program.model.pcode.*;
import java.util.*;
import java.io.*;
public class WorldTransformAudit extends GhidraScript {
 Address a(long x){return toAddr(x);}
 public void run() throws Exception {
  long[] targets={0x437F90L,0x437F00L,0x438000L,0x458CB0L,0x493E60L,0x494E20L,0x406AB0L,0x406D10L,0x4589F0L,0x458A90L,0x458BF0L,0x45EBD0L,0x45EF40L,0x4B8230L,0x4B47C0L,0x451180L,0x4513C0L,0x4AEB90L,0x494BE0L};
  PrintWriter o = new PrintWriter(new FileWriter(getScriptArgs()[0]));
  DecompInterface di=new DecompInterface();di.openProgram(currentProgram);di.setSimplificationStyle("decompile");
  for(long t:targets){Address at=a(t);Function f=getFunctionContaining(at);o.printf("\n\n======== TARGET %08X ========\n",t);
   if(f==null){o.println("No defined function");continue;}
   o.printf("Function %s entry %s end %s signature %s\n",f.getName(),f.getEntryPoint(),f.getBody().getMaxAddress(),f.getSignature());
   o.println("REFERENCES TO ENTRY:");int n=0;
   for(Reference r:getReferencesTo(f.getEntryPoint())){o.printf(" %s type=%s source=%s\n",r.getFromAddress(),r.getReferenceType(),r.getSource());if(++n>130){o.println("...[truncated]");break;}}
   o.println("DECOMPILE:");DecompileResults result=di.decompileFunction(f,40,monitor);o.println(result.decompileCompleted()?result.getDecompiledFunction().getC():"ERROR "+result.getErrorMessage());
   o.println("DISASSEMBLY:");int cnt=0;
   for(Instruction ins:currentProgram.getListing().getInstructions(f.getBody(),true)){
    o.printf(" %s  %-10s %-48s",ins.getAddress(),ins.getMnemonicString(),ins.toString());
    if(ins.getFlowType().isCall()||ins.getFlowType().isJump())o.print(" flow="+Arrays.toString(ins.getFlows()));
    o.println();if(++cnt>1400){o.println("...[truncated]");break;}
   }
  }
  o.close();di.dispose();
 }
}
