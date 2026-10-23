import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;
public class I76_FrameCameraDataflow extends GhidraScript{
 @Override public void run()throws Exception{
 PrintWriter o=new PrintWriter(new FileWriter(getScriptArgs()[0]));Map<String,ArrayList<String>> by=new TreeMap<>();
 for(long addr=0x004c2730L;addr<0x004c2970L;addr++){
  for(Reference r:getReferencesTo(toAddr(addr))){Function f=getFunctionContaining(r.getFromAddress());String key=f==null?"NO_FUNCTION":f.getEntryPoint().toString()+" "+f.getName();Instruction ins=getInstructionAt(r.getFromAddress());String v=String.format("%08X %s <- %s %s",addr,r.getReferenceType(),r.getFromAddress(),ins==null?"":ins.toString());by.computeIfAbsent(key,k->new ArrayList<>()).add(v);}
 }
 for(Map.Entry<String,ArrayList<String>> e:by.entrySet()){o.println("\n==="+e.getKey()+" count="+e.getValue().size());for(String v:e.getValue())o.println(v);}
 o.close();
 }
}
