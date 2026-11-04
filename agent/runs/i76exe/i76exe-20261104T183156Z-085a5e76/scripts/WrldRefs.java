// @category I76
// Read-only targeted xrefs and original data observations.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
public class WrldRefs extends GhidraScript {
 public void run() throws Exception {
  try(PrintWriter out=new PrintWriter(getScriptArgs()[0])) {
   for(long[] range:new long[][]{{0x644220,0x6442c0},{0x4c2340,0x4c2350},{0x4ed800,0x4ed804},{0x4fa0b4,0x4fa154}}) {
    for(long p=range[0];p<range[1];p++)for(Reference r:currentProgram.getReferenceManager().getReferencesTo(toAddr(p))) {
     Function f=getFunctionContaining(r.getFromAddress());out.println(toAddr(p)+" "+r.getFromAddress()+" "+r.getReferenceType()+" "+(f==null?"DATA":f.getEntryPoint()+" "+f.getName())+" "+currentProgram.getListing().getInstructionAt(r.getFromAddress()));
    }
   }
   for(long p=0x4fa0b4;p<0x4fa154;p+=20) {
    long ptr=Integer.toUnsignedLong(currentProgram.getMemory().getInt(toAddr(p)));StringBuilder s=new StringBuilder();
    for(int k=0;k<32;k++){byte b=currentProgram.getMemory().getByte(toAddr(ptr+k));if(b==0)break;s.append((char)b);}
    out.println("DERIVED_NAME "+toAddr(p)+" "+toAddr(ptr)+" "+s);
   }
  }
 }
}
