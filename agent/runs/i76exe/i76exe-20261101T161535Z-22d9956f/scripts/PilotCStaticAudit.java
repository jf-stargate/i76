import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import java.io.*;
import java.security.MessageDigest;
public class PilotCStaticAudit extends GhidraScript {
 public void run() throws Exception {
  if (!"bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3".equals(currentProgram.getExecutableSHA256())) throw new Exception("identity");
  try(PrintWriter out=new PrintWriter(getScriptArgs()[0]); PrintWriter dec=new PrintWriter(getScriptArgs()[1])) {
   out.println("kind\taddress\tdetail\tvalue");
   out.println("program\t-\tsha256\t"+currentProgram.getExecutableSHA256());
   DecompInterface d=new DecompInterface(); d.openProgram(currentProgram);
   for(String s:("46ffc0,470070,470340,470b20,4b2e00,4b3030,470660,4ad640,46fd40,46fee0,46fe30,46fbe0,470bc0,470c40,470c70,470ca0,4b3000,4b3310,4b34f0,4b2b30,4702d0,4b41e0,4469a0,44ab90").split(",")) {
    var f=getFunctionAt(toAddr(Long.parseLong(s,16))); if(f==null)throw new Exception(s);
    out.println("function\t"+f.getEntryPoint()+"\tprototype\t"+f.getPrototypeString(false,false));
    for(var p:f.getParameters())out.println("parameter\t"+f.getEntryPoint()+"\t"+p.getName()+"\t"+p.getSource()+":"+p.getDataType().getPathName());
    var ranges=f.getBody().getAddressRanges(); while(ranges.hasNext()) {var r=ranges.next(); byte[] b=new byte[(int)r.getLength()]; currentProgram.getMemory().getBytes(r.getMinAddress(),b); var md=MessageDigest.getInstance("SHA-256"); byte[] h=md.digest(b); StringBuilder hs=new StringBuilder();for(byte x:h)hs.append(String.format("%02x",x&255));out.println("range\t"+r.getMinAddress()+"\t"+b.length+"\t"+hs);}
    var refs=getReferencesTo(f.getEntryPoint()); for(var ref:refs)out.println("xref\t"+f.getEntryPoint()+"\t"+ref.getFromAddress()+"\t"+ref.getReferenceType());
    var ins=currentProgram.getListing().getInstructions(f.getBody(),true);while(ins.hasNext()){var i=ins.next();if(i.getFlowType().isCall())for(var dest:i.getFlows())out.println("call\t"+i.getAddress()+"\t"+f.getEntryPoint()+"\t"+dest);}
    var result=d.decompileFunction(f,60,monitor);dec.println("ENTRY "+s+" "+f);dec.println(result.getDecompiledFunction().getC());
    var it=currentProgram.getListing().getInstructions(f.getBody(),true);while(it.hasNext()){var i=it.next();dec.println(i.getAddress()+" "+i);}
   } d.dispose();
  }
 }
}
