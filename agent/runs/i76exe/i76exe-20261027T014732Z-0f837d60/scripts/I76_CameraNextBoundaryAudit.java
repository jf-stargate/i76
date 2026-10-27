import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.scalar.*;
import java.util.*;
import java.io.*;
public class I76_CameraNextBoundaryAudit extends GhidraScript {
 public void run() throws Exception {
  try(PrintWriter out=new PrintWriter(new FileWriter(getScriptArgs()[0]))){
   for(long[] span: new long[][]{{0x406AB0L,0x406E00L},{0x406920L,0x406AB0L},{0x4070E0L,0x407350L},{0x472990L,0x472B00L}}){
    out.printf("\n=== %08X..%08X ===\n",span[0],span[1]);
    for(long pc=span[0];pc<span[1];){Address a=toAddr(pc);Instruction ins=getInstructionAt(a);if(ins==null){pc++;continue;}
     out.printf("%08X  %-8s  %s",pc,ins.getMnemonicString(),ins.toString());
     if(ins.getFlowType().isCall()||ins.getFlowType().isJump()){Address[] f=ins.getFlows();out.print("  flows="+Arrays.toString(f));}
     out.println();pc+=ins.getLength();}
   }
  }
 }
}
