// @category I76
// Read-only targeted xrefs and original data observations.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
public class HzdRefs extends GhidraScript {
 public void run() throws Exception {
  try(PrintWriter out=new PrintWriter(getScriptArgs()[0])) {
   for(long[] range:new long[][]{{0x504838,0x5049c0}}) {
    for(long p=range[0];p<range[1];p++)for(Reference r:currentProgram.getReferenceManager().getReferencesTo(toAddr(p))) {
     Function f=getFunctionContaining(r.getFromAddress());out.println(toAddr(p)+" "+r.getFromAddress()+" "+r.getReferenceType()+" "+(f==null?"DATA":f.getEntryPoint()+" "+f.getName())+" "+currentProgram.getListing().getInstructionAt(r.getFromAddress()));
    }
   }
  }
 }
}
