// Private capture: never commit the output directory or C exports.
//@category i76
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import java.nio.file.*;
import java.security.*;
import java.util.*;
public class ConsolidationAudit extends GhidraScript {
 static final long[] TARGETS={0x493080,0x493160,0x4927b0,0x4931c0,0x493550,0x410490,0x412500,0x414670,0x4149f0,0x412ce0,0x46ffc0,0x470070,0x470340,0x470b20,0x4b2e00,0x4b3030,0x461970,0x461b80,0x461c80,0x461d50,0x42d5d0};
 static String clean(Object o){return String.valueOf(o).replace('\t',' ').replace('\n',' ').replace('\r',' ');}
 static String hash(byte[] b)throws Exception{return HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(b));}
 static String signature(Function f){StringBuilder b=new StringBuilder(f.getName()+"|"+f.getSymbol().getSource()+"|"+f.getCallingConventionName()+"|"+f.hasCustomVariableStorage()+"|"+f.getSignatureSource()+"|"+f.getReturnType().getPathName()+"|"+f.getReturn().getVariableStorage());for(var p:f.getParameters())b.append("|").append(p.getName()).append(":").append(p.getDataType().getPathName()).append(":").append(p.getVariableStorage()).append(":").append(p.getSource());return b.toString();}
 public void run()throws Exception{
  Path out=Paths.get(getScriptArgs()[0]);Files.createDirectories(out);
  int defined=0,external=0;var di=currentProgram.getFunctionManager().getFunctions(true);while(di.hasNext()){di.next();defined++;}var ei=currentProgram.getFunctionManager().getExternalFunctions();while(ei.hasNext()){ei.next();external++;}
  Files.writeString(out.resolve("identity.tsv"),"program\t"+currentProgram.getName()+"\nsha256\t"+currentProgram.getExecutableSHA256()+"\nmd5\t"+currentProgram.getExecutableMD5()+"\nlanguage\t"+currentProgram.getLanguageID()+"\nimage_base\t"+currentProgram.getImageBase()+"\nfunctions\t"+currentProgram.getFunctionManager().getFunctionCount()+"\ndefined_functions\t"+defined+"\nexternal_functions\t"+external+"\nghidra\t"+ghidra.framework.Application.getApplicationVersion()+"\n");
  StringBuilder funcs=new StringBuilder("address\tbody\tbytes_sha256\tsignature\n"),ins=new StringBuilder("address\tbytes\n");
  var fi=currentProgram.getFunctionManager().getFunctions(true);while(fi.hasNext()){var f=fi.next();MessageDigest md=MessageDigest.getInstance("SHA-256");var ranges=f.getBody().getAddressRanges();while(ranges.hasNext()){var r=ranges.next();byte[] bytes=new byte[(int)r.getLength()];currentProgram.getMemory().getBytes(r.getMinAddress(),bytes);md.update(bytes);}funcs.append(f.getEntryPoint()+"\t"+f.getBody()+"\t"+HexFormat.of().formatHex(md.digest())+"\t"+clean(signature(f))+"\n");}
  Files.writeString(out.resolve("functions.tsv"),funcs);
  StringBuilder syms=new StringBuilder();var si=currentProgram.getSymbolTable().getAllSymbols(true);while(si.hasNext()){var s=si.next();syms.append(s.getAddress()+"\t"+s.getName(true)+"\t"+s.getSymbolType()+"\t"+s.getSource()+"\t"+s.isPrimary()+"\n");}Files.writeString(out.resolve("symbols.tsv"),syms);
  StringBuilder types=new StringBuilder();var ti=currentProgram.getDataTypeManager().getAllDataTypes();while(ti.hasNext()){var t=ti.next();types.append(clean(t.getPathName())+"\t"+t.getLength()+"\t"+clean(t)+"\n");}Files.writeString(out.resolve("types.tsv"),types);
  StringBuilder comments=new StringBuilder();for(int kind=0;kind<=4;kind++){var it=currentProgram.getListing().getCommentAddressIterator(kind,currentProgram.getMemory(),true);while(it.hasNext()){var a=it.next();comments.append(a+"\t"+kind+"\t"+clean(currentProgram.getListing().getComment(kind,a))+"\n");}}Files.writeString(out.resolve("comments.tsv"),comments);
  TreeSet<Address> sample=new TreeSet<>();for(long va:TARGETS){var f=getFunctionAt(toAddr(va));if(f==null)throw new Exception("Missing target "+Long.toHexString(va));sample.add(f.getEntryPoint());var refs=currentProgram.getReferenceManager().getReferencesTo(f.getEntryPoint());while(refs.hasNext()){var r=refs.next();var caller=getFunctionContaining(r.getFromAddress());if(caller!=null)sample.add(caller.getEntryPoint());}}
  DecompInterface dc=new DecompInterface();dc.openProgram(currentProgram);StringBuilder metrics=new StringBuilder("address\tbytes\tsha256\tprototype\n");
  for(var a:sample){var f=getFunctionAt(a);var r=dc.decompileFunction(f,120,monitor);if(!r.decompileCompleted())throw new Exception("Decompile "+a+": "+r.getErrorMessage());String c=r.getDecompiledFunction().getC();Files.writeString(out.resolve(a+".c"),c);metrics.append(a+"\t"+c.getBytes(java.nio.charset.StandardCharsets.UTF_8).length+"\t"+hash(c.getBytes(java.nio.charset.StandardCharsets.UTF_8))+"\t"+clean(f.getPrototypeString(false,false))+"\n");var it=currentProgram.getListing().getInstructions(f.getBody(),true);while(it.hasNext()){var i=it.next();ins.append(i.getAddress()+"\t"+HexFormat.of().formatHex(i.getBytes())+"\n");}}
  dc.dispose();Files.writeString(out.resolve("decompilations.tsv"),metrics);Files.writeString(out.resolve("instructions.tsv"),ins);
  println("AUDIT functions="+currentProgram.getFunctionManager().getFunctionCount()+" sample="+sample.size());
 }
}
