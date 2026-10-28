// Read-only frame timing, table initialization, pose and scheduler audit.
//@category i76
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import java.io.*;import java.util.*;
public class I76_TerrainAudit extends GhidraScript {
 public void run() throws Exception {
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("binary identity");
  Set<Function> fs=new TreeSet<>((a,b)->a.getEntryPoint().compareTo(b.getEntryPoint()));
  try(PrintWriter o=new PrintWriter(getScriptArgs()[0])){
   for(String s:new String[]{"0058d900","00588e00","00469f10"}){
    Address a=toAddr(Long.parseLong(s,16));o.println("XREF "+s);
    for(Reference r:getReferencesTo(a)){Function f=getFunctionContaining(r.getFromAddress());o.println(r.getFromAddress()+" "+r.getReferenceType()+" "+(f==null?"data":f.getEntryPoint()+" "+f.getName()));if(f!=null)fs.add(f);}
    Function f=getFunctionAt(a);if(f!=null)fs.add(f);
   }
   for(int i=1;i<getScriptArgs().length;i++){Function f=getFunctionContaining(toAddr(Long.parseLong(getScriptArgs()[i],16)));if(f!=null)fs.add(f);}
   DecompInterface di=new DecompInterface();di.openProgram(currentProgram);
   for(Function f:fs){o.println("\nFUNCTION "+f.getEntryPoint()+" "+f.getName());
    DecompileResults d=di.decompileFunction(f,60,monitor);o.println(d.decompileCompleted()?d.getDecompiledFunction().getC():d.getErrorMessage());
    InstructionIterator ii=currentProgram.getListing().getInstructions(f.getBody(),true);while(ii.hasNext()){Instruction in=ii.next();StringBuilder h=new StringBuilder();for(byte b:in.getBytes())h.append(String.format("%02x",b&255));o.println(in.getAddress()+"\t"+h+"\t"+in.toString());}
   }di.dispose();
  }
 }
}
