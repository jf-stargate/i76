import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.*;
import java.io.*;import java.security.*;
//@category i76
public class CoordinateAudit extends GhidraScript {
 public void run() throws Exception {
  try(PrintWriter o=new PrintWriter(getScriptArgs()[0])) {
   for(MemoryBlock b:currentProgram.getMemory().getBlocks())if(b.isExecute()){
    byte[] v=new byte[(int)b.getSize()];currentProgram.getMemory().getBytes(b.getStart(),v);
    o.println("CODE_SHA256\t"+b.getStart()+"\t"+b.getSize()+"\t"+java.util.HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(v)));
   }
   for(String s:new String[]{"0059c588","00493160","004931c0","00490fb0"})for(Reference x:getReferencesTo(toAddr(Long.parseLong(s,16))))o.println("XREF\t"+s+"\t"+x.getFromAddress()+"\t"+x.getReferenceType());
   for(String s:new String[]{"00493080","00493160","00493550","004927b0","004931c0","00490fb0","004937c0","00493c50"}){
    Function f=getFunctionAt(toAddr(Long.parseLong(s,16)));o.println("FUNCTION\t"+s);
    InstructionIterator ii=currentProgram.getListing().getInstructions(f.getBody(),true);
    while(ii.hasNext()){Instruction in=ii.next();o.println(in.getAddress()+"\t"+java.util.HexFormat.of().formatHex(in.getBytes())+"\t"+in);}
   }
  }
 }
}
