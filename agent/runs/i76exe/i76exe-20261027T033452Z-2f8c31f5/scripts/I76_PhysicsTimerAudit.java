import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import java.io.*;import java.util.*;
public class I76_PhysicsTimerAudit extends GhidraScript {
 public void run()throws Exception {
 String[] targets={"00438630","00438680","00438FD0","0043A3C0","0043A560","0043A5D0","0043BDF0","0043D070","00463800","004639A0","00464360","004643A0","0045EBD0","004572B0","00406AB0","00463120","0043BCF0","0043A320","0049CBE0","0049CC20","0049CCA0","0049C7A0","00406840","0044E010","0043A300"};
 try(PrintWriter o=new PrintWriter(new FileWriter(getScriptArgs()[0]))) {
  DecompInterface di=new DecompInterface();di.openProgram(currentProgram);
  for(String loc:targets){Address addr=toAddr(Long.parseLong(loc,16));Function f=getFunctionContaining(addr);if(f==null){o.println("MISSING "+loc);continue;}
   o.println("\n====== " + f.getName()+" "+f.getEntryPoint()+" BYTES "+f.getBody().getNumAddresses()+" ======");
   o.println("CALLERS:");for(Reference ref:getReferencesTo(f.getEntryPoint())){Function owner=getFunctionContaining(ref.getFromAddress());o.println(ref.getFromAddress()+" "+ref.getReferenceType()+" owner="+(owner==null?"?":owner.getEntryPoint()+" "+owner.getName()));}
   o.println("CALLEES:");for(Function callee:f.getCalledFunctions(monitor))o.println(callee.getEntryPoint()+" "+callee.getName());
   DecompileResults d=di.decompileFunction(f,30,monitor);o.println("C:\n"+(d.decompileCompleted()?d.getDecompiledFunction().getC():"ERROR "+d.getErrorMessage()));
  }di.dispose();
 }
 }
}
