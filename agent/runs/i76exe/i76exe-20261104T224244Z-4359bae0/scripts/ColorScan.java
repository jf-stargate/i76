// Read-only whole-program immediate/displacement survey; no annotations.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import com.google.gson.GsonBuilder;
import java.util.*;import java.nio.file.*;
public class ColorScan extends GhidraScript {
 public void run() throws Exception {
  var rows=new ArrayList<Object>();long before=currentProgram.getModificationNumber();
  for(var i:currentProgram.getListing().getInstructions(true)){
   boolean hit=false;
   for(int k=0;k<i.getNumOperands();k++)for(Object o:i.getOpObjects(k)){
    long v=o instanceof Scalar?((Scalar)o).getUnsignedValue():o instanceof Address?((Address)o).getOffset():-1;
    if(v==0x404||(v>=0x60afa0&&v<0x61afa0)||v==0x5dd2c4)hit=true;
   }
   if(hit){var f=getFunctionContaining(i.getAddress());rows.add(Map.of("va",i.getAddress().toString(),"asm",i.toString(),"function",f==null?"undefined":f.getEntryPoint().toString()));}
  }
  Files.writeString(Path.of(getScriptArgs()[0]),new GsonBuilder().setPrettyPrinting().create().toJson(Map.of("modification_before",before,"modification_after",currentProgram.getModificationNumber(),"instructions",rows)));
 }
}
