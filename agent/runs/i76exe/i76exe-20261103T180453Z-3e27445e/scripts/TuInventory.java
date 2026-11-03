// Read-only inventory. Run with -readOnly -noanalysis; output is private.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import java.io.*;
public class TuInventory extends GhidraScript {
 public void run() throws Exception {
  PrintWriter w=new PrintWriter(getScriptArgs()[0]);
  w.println("entry\tname\tsize\tranges\treferences"); int defined=0,external=0;
  FunctionIterator fs=currentProgram.getFunctionManager().getFunctions(true);
  while(fs.hasNext()) { Function f=fs.next(); if(f.isExternal()){external++;continue;} defined++;
   StringBuilder refs=new StringBuilder(); AddressIterator ai=f.getBody().getAddresses(true);
   while(ai.hasNext()){Address a=ai.next(); for(Reference r:currentProgram.getReferenceManager().getReferencesFrom(a)) {
    if(r.getReferenceType().isFlow()&&!r.getReferenceType().isCall())continue;
    Data d=currentProgram.getListing().getDefinedDataContaining(r.getToAddress());
    String val=d!=null&&d.hasStringValue()?String.valueOf(d.getValue()).replace('\t',' ').replace('\n',' ').replace('\r',' '):"";
    refs.append(a+":"+r.getReferenceType()+":"+r.getToAddress()+":"+val.replace("|"," ")+"|");
   }}
   w.println(f.getEntryPoint()+"\t"+f.getName()+"\t"+f.getBody().getNumAddresses()+"\t"+f.getBody().toString().replace('\n',' ').replace('\r',' ')+"\t"+refs);
  }
  w.close(); int ec=0; FunctionIterator ei=currentProgram.getFunctionManager().getExternalFunctions(); while(ei.hasNext()){ei.next();ec++;} println("EXTERNAL_COUNT="+ec); println("DEFINED="+defined+" EXTERNAL_ITERATOR="+external+" EXTERNAL_FUNCTIONS="+currentProgram.getFunctionManager().getExternalFunctions().hasNext());
 }
}
