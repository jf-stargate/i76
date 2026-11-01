// Private bounded decompiler/disassembly capture; do not publish its full output.
//@category i76
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import java.io.*;
public class TerrainInspect extends GhidraScript {
 public void run() throws Exception {
  try(PrintWriter o=new PrintWriter(getScriptArgs()[0])) {
   o.println("PROGRAM "+currentProgram.getName()+" SHA256 "+currentProgram.getExecutableSHA256());
   o.println("FUNCTION_COUNT "+currentProgram.getFunctionManager().getFunctionCount());
   var ti=currentProgram.getDataTypeManager().getAllDataTypes();while(ti.hasNext()){var t=ti.next();if(t.getPathName().contains("I76_"))o.println("TYPE "+t.getPathName()+" "+t.getLength());}
   for(String s:new String[]{"006442c0","006442c4","006442d0","00644380","0059c588","004faf18","004be8a0","004be8a8","004be8ac"}) {
    var a=toAddr(s);o.println("GLOBAL "+s+" "+getDataAt(a));for(var sym:currentProgram.getSymbolTable().getSymbols(a))o.println("SYMBOL "+sym+" "+sym.getSource());
    o.println("RAW64 "+Long.toHexString(getLong(a)));
   }
   var d=new DecompInterface();d.openProgram(currentProgram);
   for(String s:new String[]{"00493080","00493160","004931c0","00493550","004927b0","00493bf0","00493c00","004ba090","00495000","00440870"}) {
    var f=getFunctionContaining(toAddr(s));if(f==null)continue;o.println("FUNCTION "+f.getEntryPoint()+" "+f.getSignature()+" BODY "+f.getBody());
    for(var p:f.getParameters())o.println("PARAM "+p.getName()+" "+p.getDataType()+" "+p.getVariableStorage()+" "+p.getSource());
    o.println("RETURN "+f.getReturn().getVariableStorage());
    var r=d.decompileFunction(f,60,monitor);o.println(r.decompileCompleted()?r.getDecompiledFunction().getC():r.getErrorMessage());
    var it=currentProgram.getListing().getInstructions(f.getBody(),true);while(it.hasNext()){var i=it.next();o.println(i.getAddress()+" "+i);}
   } d.dispose();
  }
 }
}
