// Read-only original-instruction audit and exact function reference classification.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import java.io.*;
public class TuAudit extends GhidraScript {
 public void run() throws Exception {
 PrintWriter w=new PrintWriter(getScriptArgs()[0]);
 FunctionIterator fi=currentProgram.getFunctionManager().getFunctions(true);
 while(fi.hasNext()) {Function f=fi.next(); long a=f.getEntryPoint().getOffset();
 if(!((a>=0x492700L&&a<=0x493d00L)||(a>=0x410200L&&a<=0x414c00L)||(a>=0x46fb00L&&a<=0x470e00L)||(a>=0x4b2a00L&&a<=0x4b3600L))) continue;
 w.println("FUNCTION "+f.getEntryPoint()+" "+f.getName()+" "+f.getBody());
 ReferenceIterator incoming=currentProgram.getReferenceManager().getReferencesTo(f.getEntryPoint());
 while(incoming.hasNext()){Reference r=incoming.next(); Function caller=currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());w.println("IN "+r+" owner="+(caller==null?"none":caller.getEntryPoint()));}
 InstructionIterator ii=currentProgram.getListing().getInstructions(f.getBody(),true);
 while(ii.hasNext()){Instruction i=ii.next(); w.println(i.getAddress()+" "+i);for(Reference r:i.getReferencesFrom()) {
 Function target=currentProgram.getFunctionManager().getFunctionAt(r.getToAddress());
 Symbol sym=currentProgram.getSymbolTable().getPrimarySymbol(r.getToAddress());
 w.println("REF "+r+" target="+(target==null?"none":target.getEntryPoint()+" "+target.getName())+" symbol="+sym);
 }}
 }
 w.close();
 }
}
