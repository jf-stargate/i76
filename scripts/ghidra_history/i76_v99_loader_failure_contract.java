// @category I76
// Read-only audited extraction against retail I76 Ghidra v97 baseline.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;
public class i76_v99_loader_failure_contract extends GhidraScript {
  String clean(String s){return s==null?"":s.replace('\t',' ').replace('\r',' ').replace('\n',' ');}
  String[] funcs={"004b3db0","004b42b0","004b41e0","004b4290","004b4790","004b4610","004b45f0","004b89b0","00409740","00410720","004125c0","00412400","004122d0","004b35a0","0042d5d0","004b7ac0","004b7a90"};
  public void run() throws Exception {
    if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("PE MD5 mismatch");
    File out=new File(getScriptArgs()[0]);out.mkdirs();
    DecompInterface d=new DecompInterface();d.openProgram(currentProgram);int ok=0,fail=0;
    try(PrintWriter c=new PrintWriter(new File(out,"v99_loader_native_decompiled.txt"),"UTF-8");
        PrintWriter asm=new PrintWriter(new File(out,"v99_loader_full_instructions.tsv"),"UTF-8");
        PrintWriter calls=new PrintWriter(new File(out,"v99_loader_call_references.tsv"),"UTF-8");
        PrintWriter incoming=new PrintWriter(new File(out,"v99_loader_incoming.tsv"),"UTF-8")) {
      asm.println("function\taddress\tinstruction");calls.println("caller\tcallsite\tdestination\tcallee");incoming.println("target\tfrom\tcaller\ttype");
      for(String addr:funcs){Address a=toAddr(addr);Function f=getFunctionAt(a);c.println("\n===== "+addr+" "+(f==null?"UNDEFINED":f.getName())+" =====");if(f==null){fail++;continue;}
        DecompileResults r=d.decompileFunction(f,22,monitor);if(r!=null&&r.decompileCompleted()&&r.getDecompiledFunction()!=null){c.println(r.getDecompiledFunction().getC());ok++;}else{c.println("DECOMP_ERROR "+(r==null?"null":r.getErrorMessage()));fail++;}
        InstructionIterator it=currentProgram.getListing().getInstructions(f.getBody(),true);while(it.hasNext()){
          Instruction i=it.next();asm.printf("%s\t%s\t%s%n",addr,i.getAddress(),clean(i.toString()));
          for(Reference ref:i.getReferencesFrom())if(ref.getReferenceType().isCall()){
            Function target=getFunctionContaining(ref.getToAddress());calls.printf("%s\t%s\t%s\t%s%n",addr,i.getAddress(),ref.getToAddress(),target==null?"UNDEFINED":clean(target.getName()));
          }
        }
        for(Reference ref:currentProgram.getReferenceManager().getReferencesTo(a)){
          Function source=getFunctionContaining(ref.getFromAddress());incoming.printf("%s\t%s\t%s\t%s%n",addr,ref.getFromAddress(),source==null?"UNDEFINED":clean(source.getName()),ref.getReferenceType());
        }
      }
    }
    d.dispose();
    try(PrintWriter ds=new PrintWriter(new File(out,"v99_selected_bwd2_descriptors.tsv"),"UTF-8")){
      ds.println("address\ttag\taux\tcallback\tflags");Memory mem=currentProgram.getMemory();String[] addrs={"00500328","00500338","00500348","00500358","00500368","00500378","00500388","00500398","005003a8","00500d20","00500d30","00500d40"};
      for(String s:addrs){Address a=toAddr(s);byte[] b=new byte[4];mem.getBytes(a,b);StringBuilder tag=new StringBuilder();for(byte t:b)tag.append(t==0?'_':(char)(t&0xff));ds.printf("%s\t%s\t0x%08X\t0x%08X\t0x%08X%n",s,tag,mem.getInt(a.add(4)),mem.getInt(a.add(8)),mem.getInt(a.add(12)));}
    }
    println("V99_LOADER_READONLY_OK decompiled="+ok+" failures="+fail+" md5="+currentProgram.getExecutableMD5());
    if(fail>0)throw new Exception("Missing or uncompiled functions: "+fail);
  }
}
