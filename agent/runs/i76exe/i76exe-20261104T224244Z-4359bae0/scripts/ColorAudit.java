// Read-only audit. Full instructions/decompilation go to a private output path.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import com.google.gson.GsonBuilder;
import java.util.*;
import java.nio.file.*;
import java.security.*;
public class ColorAudit extends GhidraScript {
 Map<String,Object> m(Object... a){var r=new LinkedHashMap<String,Object>();for(int i=0;i<a.length;i+=2)r.put((String)a[i],a[i+1]);return r;}
 public void run() throws Exception {
 long before=currentProgram.getModificationNumber(); var out=new ArrayList<Object>(); var dec=new DecompInterface();dec.openProgram(currentProgram);
 String[] addrs=Arrays.copyOfRange(getScriptArgs(),1,getScriptArgs().length);
 var xr=new ArrayList<Object>();
 for(long[] range:new long[][]{{0x5dcec0,0x5dd300},{0x6094a0,0x60afa0},{0x61afa0,0x63b2c0},{0x4f9dc0,0x4f9e08},{0x4fa498,0x4fa4e0},{0x4ede98,0x4edee0},{0x4f0050,0x4f0098},{0x4f1520,0x4f1568},{0x60afa0,0x61afa0},{0x4fa170,0x4fa470}}){
 for(long p=range[0];p<range[1];p++)for(var r:currentProgram.getReferenceManager().getReferencesTo(toAddr(p))){var f=getFunctionContaining(r.getFromAddress());xr.add(m("target",Long.toHexString(p),"from",r.getFromAddress().toString(),"type",r.getReferenceType().toString(),"function",f==null?null:f.getEntryPoint().toString(),"instruction",String.valueOf(currentProgram.getListing().getInstructionAt(r.getFromAddress()))));}}
 Files.writeString(Path.of(getScriptArgs()[0]+".refs.json"),new GsonBuilder().setPrettyPrinting().create().toJson(xr));

 for(String s:addrs){if(s.contains(":")){String[] ab=s.split(":");var start=toAddr(ab[0]);var end=toAddr(ab[1]);var set=new ghidra.program.model.address.AddressSet(start,end);var ins=new ArrayList<Object>();for(var i:currentProgram.getListing().getInstructions(set,true))ins.add(m("va",i.getAddress().toString(),"bytes",HexFormat.of().formatHex(i.getBytes()),"asm",i.toString()));out.add(m("entry",s,"instructions",ins));continue;}var f=getFunctionContaining(toAddr(s));if(f==null){out.add(m("entry",s,"error","no defined function"));continue;}var ins=new ArrayList<Object>();var ranges=new ArrayList<Object>();
 for(var r:f.getBody().getAddressRanges()){byte[] b=new byte[(int)r.getLength()];currentProgram.getMemory().getBytes(r.getMinAddress(),b);ranges.add(m("start",r.getMinAddress().toString(),"length",b.length,"sha256",HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(b))));}
 for(var i:currentProgram.getListing().getInstructions(f.getBody(),true)){var refs=new ArrayList<Object>();for(var r:i.getReferencesFrom()){var d=getDataContaining(r.getToAddress());refs.add(m("to",r.getToAddress().toString(),"type",r.getReferenceType().toString(),"data",d==null?null:d.toString()));}ins.add(m("va",i.getAddress().toString(),"bytes",HexFormat.of().formatHex(i.getBytes()),"asm",i.toString(),"refs",refs));}
 var d=dec.decompileFunction(f,60,monitor);out.add(m("entry",s,"ranges",ranges,"instructions",ins,"decompilation",d.decompileCompleted()?d.getDecompiledFunction().getC():d.getErrorMessage()));}
 dec.dispose();Files.writeString(Path.of(getScriptArgs()[0]),new GsonBuilder().setPrettyPrinting().create().toJson(m("program",currentProgram.getName(),"executable_sha256",currentProgram.getExecutableSHA256(),"ghidra",getGhidraVersion(),"modification_before",before,"modification_after",currentProgram.getModificationNumber(),"functions",out)));
 }
}
