import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.TaskMonitor;
import java.nio.file.*;
import java.util.*;
public class I76_Flag10CallgraphAudit extends GhidraScript {
  Address a(long n){return toAddr(n);}
  public void run()throws Exception {
   StringBuilder b=new StringBuilder();
   b.append("program="+currentProgram.getName()+"\nmd5="+currentProgram.getExecutableMD5()+"\n");
   long[] targets={0x451180L,0x4513c0L,0x4512a1L,0x45146eL,0x4ad6f0L,0x454e30L,0x541028L,0x458bf0L,0x4ae000L,0x4b7ac0L};
   for(long target:targets){
      Address addr=a(target); Function fun=currentProgram.getFunctionManager().getFunctionContaining(addr);
      b.append("\nTARGET "+String.format("%08X",target)+" owner="+(fun!=null?fun.getName()+" "+fun.getEntryPoint():"UNDEFINED")+"\n");
      for(Reference ref:currentProgram.getReferenceManager().getReferencesTo(addr)){
       Function caller=currentProgram.getFunctionManager().getFunctionContaining(ref.getFromAddress()); b.append("  REF "+ref.getFromAddress()+" "+ref.getReferenceType()+" caller="+(caller==null?"UNDEFINED":caller.getName()+"@"+caller.getEntryPoint())+"\n");
      }
      if(target==0x451180L||target==0x4513c0L){
       if(fun!=null){DecompInterface decomp=new DecompInterface(); decomp.openProgram(currentProgram);
         DecompileResults res=decomp.decompileFunction(fun,45,monitor);
         b.append("  DECOMP\n"+(res.decompileCompleted()?res.getDecompiledFunction().getC():res.getErrorMessage())+"\n");decomp.dispose();}
      }
   }
   Files.write(Paths.get(getScriptArgs()[0]),b.toString().getBytes(java.nio.charset.StandardCharsets.UTF_8));
  }
}
