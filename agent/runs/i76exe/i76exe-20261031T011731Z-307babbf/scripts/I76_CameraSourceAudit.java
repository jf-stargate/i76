// Private read-only source audit. Full output is not a public artifact.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import java.io.*;import java.util.*;
public class I76_CameraSourceAudit extends GhidraScript {
 void instruction(PrintWriter o,Instruction in)throws Exception{StringBuilder h=new StringBuilder();for(byte b:in.getBytes())h.append(String.format("%02x",b&255));o.println(in.getAddress()+"\t"+h+"\t"+in.toString());}
 public void run()throws Exception{
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("retail identity");
  try(PrintWriter o=new PrintWriter(getScriptArgs()[0])){
   // Callback lacks a function definition in the annotated baseline. Inspect existing
   // instructions without creating one or mutating symbols.
   for(long[] range:new long[][]{{0x406ab0L,0x406dffL},{0x472530L,0x472990L}})
    for(long pc=range[0];pc<range[1];){Instruction in=getInstructionAt(toAddr(pc));if(in==null){o.println("UNDEFINED "+Long.toHexString(pc++));continue;}instruction(o,in);pc+=in.getLength();}
   for(long pc:new long[]{0x458cb0L,0x494e20L,0x471fd0L,0x472400L})instruction(o,getInstructionAt(toAddr(pc)));
   for(long v:new long[]{0x58da68L,0x58da98L,0x58da70L,0x4fa48cL,0x4f9d80L})for(var ref:getReferencesTo(toAddr(v))){Function own=getFunctionContaining(ref.getFromAddress());o.println("XREF "+Long.toHexString(v)+" "+ref.getFromAddress()+" "+(own==null?"none":own.getEntryPoint()+" "+own.getName()));}
   DecompInterface di=new DecompInterface();di.openProgram(currentProgram);
   for(int i=1;i<getScriptArgs().length;i++){
    Function f=getFunctionAt(toAddr(Long.parseLong(getScriptArgs()[i],16)));
    if(f==null){long start=Long.parseLong(getScriptArgs()[i],16);for(long pc=start;pc<start+0x500;){Instruction in=getInstructionAt(toAddr(pc));if(in==null){pc++;continue;}instruction(o,in);pc+=in.getLength();}continue;}
    o.println("FUNCTION "+f.getEntryPoint()+" "+f.getName());
    DecompileResults d=di.decompileFunction(f,60,monitor);o.println(d.decompileCompleted()?d.getDecompiledFunction().getC():d.getErrorMessage());
    InstructionIterator ii=currentProgram.getListing().getInstructions(f.getBody(),true);while(ii.hasNext())instruction(o,ii.next());
   }di.dispose();
  }
 }
}
