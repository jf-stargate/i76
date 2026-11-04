// @category I76
// Read-only export. Never creates instructions, functions, labels or data.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
public class WrldAudit extends GhidraScript {
 public void run() throws Exception {
  if (!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5())) throw new Exception("wrong executable");
  String[] args=getScriptArgs(); File dir=new File(args[0]); dir.mkdirs();
  DecompInterface d=new DecompInterface(); d.openProgram(currentProgram);
  try(PrintWriter meta=new PrintWriter(new File(dir,"program.txt"))) {meta.println(currentProgram.getName());meta.println(currentProgram.getExecutableMD5());meta.println(currentProgram.getExecutableSHA256());}
  for(int n=1;n<args.length;n++) {
   Address a=toAddr(args[n]); Function f=getFunctionContaining(a);
   try(PrintWriter out=new PrintWriter(new File(dir,args[n]+".txt"))) {
    out.println("TARGET "+a+" FUNCTION "+(f==null?"none":f.getName()+" "+f.getEntryPoint()));
    for(Reference r:currentProgram.getReferenceManager().getReferencesTo(a))out.println("XREF "+r.getFromAddress()+" "+r.getReferenceType());
    if(f==null) {for(int i=0;i<128;i+=4)out.printf("%s %08x%n",a.add(i),currentProgram.getMemory().getInt(a.add(i)));continue;}
    DecompileResults result=d.decompileFunction(f,60,monitor);out.println(result.decompileCompleted()?result.getDecompiledFunction().getC():result.getErrorMessage());
    InstructionIterator it=currentProgram.getListing().getInstructions(f.getBody(),true);
    while(it.hasNext()){Instruction i=it.next();out.println(i.getAddress()+" "+i);}
   }
  }
  d.dispose();println("READ_ONLY_WRLD_EXPORT_OK");
 }
}
