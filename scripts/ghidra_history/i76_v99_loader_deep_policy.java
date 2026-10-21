// @category I76
// Read-only supplementary loader policy inspection.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import java.io.*;
public class i76_v99_loader_deep_policy extends GhidraScript {
 public void run() throws Exception {
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("MD5 mismatch");
  File out=new File(getScriptArgs()[0]);out.mkdirs();
  DecompInterface d=new DecompInterface();d.openProgram(currentProgram);
  try(PrintWriter c=new PrintWriter(new File(out,"v99_reset_and_caller.txt"),"UTF-8");PrintWriter a=new PrintWriter(new File(out,"v99_reset_and_caller_disasm.tsv"),"UTF-8")){
   a.println("function\taddress\tinstruction");for(String key:new String[]{"004b84e0","00402b30","004b41e0","004b4550","004b4570","004b4590","004b45b0","004b45d0"}){
    Function f=getFunctionAt(toAddr(key));c.println("\n==== "+key+" "+(f==null?"UNDEFINED":f.getName())+" ====");if(f==null)continue;
    if(!key.equals("00402b30")){DecompileResults r=d.decompileFunction(f,16,monitor);if(r.decompileCompleted())c.println(r.getDecompiledFunction().getC());else c.println("FAIL: "+r.getErrorMessage());}
    InstructionIterator it=currentProgram.getListing().getInstructions(f.getBody(),true);int n=0;while(it.hasNext()){
     Instruction i=it.next();long address=i.getAddress().getOffset();if(!key.equals("00402b30")||(address>=0x403490&&address<=0x4035a0)) a.printf("%s\t%s\t%s%n",key,i.getAddress(),i.toString());n++;
    }c.println("count instructions="+n);
   }
  }
  d.dispose();Memory m=currentProgram.getMemory();try(PrintWriter z=new PrintWriter(new File(out,"v99_revision_required_table_raw.tsv"),"UTF-8")){
   z.println("address\tword0\tword1\tas_ascii");for(long p=0x5003b8;p<0x500480;p+=8){Address a=toAddr(Long.toHexString(p));int n=m.getInt(a);byte[] t=new byte[4];m.getBytes(a,t);StringBuilder q=new StringBuilder();for(byte b:t)q.append(b==0?'_':(b>=32&&b<=126?(char)b:'.'));
    z.printf("%08x\t%08x\t%08x\t%s%n",p,n,m.getInt(a.add(4)),q);
   }
  }
  println("V99_POLICY_READONLY_OK");
 }
}
