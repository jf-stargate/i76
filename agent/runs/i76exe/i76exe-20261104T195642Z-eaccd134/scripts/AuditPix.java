// Read-only audit. Full instructions/decompilation go to a private output path.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import com.google.gson.GsonBuilder;
import java.util.*;
import java.nio.file.*;
import java.security.*;
public class AuditPix extends GhidraScript {
 Map<String,Object> m(Object... a){var r=new LinkedHashMap<String,Object>();for(int i=0;i<a.length;i+=2)r.put((String)a[i],a[i+1]);return r;}
 public void run() throws Exception {
 long before=currentProgram.getModificationNumber(); var out=new ArrayList<Object>(); var dec=new DecompInterface();dec.openProgram(currentProgram);
 String[] addrs={"00470660","00470ac0","00470b20","00470bc0","00470c40","00470c70","00470ca0","0046ffc0","0046fd40","0046fee0","00470070","004b2e00","004b3030","0042d5d0","004b34f0","004b2ac0","004b32f0","004b3550","0046fe30","00404d80"};
 for(String s:addrs){var f=getFunctionAt(toAddr(s));if(f==null)throw new Exception("missing "+s);var ins=new ArrayList<Object>();var ranges=new ArrayList<Object>();
 for(var r:f.getBody().getAddressRanges()){byte[] b=new byte[(int)r.getLength()];currentProgram.getMemory().getBytes(r.getMinAddress(),b);ranges.add(m("start",r.getMinAddress().toString(),"length",b.length,"sha256",HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(b))));}
 for(var i:currentProgram.getListing().getInstructions(f.getBody(),true)){var refs=new ArrayList<Object>();for(var r:i.getReferencesFrom()){var d=getDataContaining(r.getToAddress());refs.add(m("to",r.getToAddress().toString(),"type",r.getReferenceType().toString(),"data",d==null?null:d.toString()));}ins.add(m("va",i.getAddress().toString(),"bytes",HexFormat.of().formatHex(i.getBytes()),"asm",i.toString(),"refs",refs));}
 var d=dec.decompileFunction(f,60,monitor);out.add(m("entry",s,"ranges",ranges,"instructions",ins,"decompilation",d.decompileCompleted()?d.getDecompiledFunction().getC():d.getErrorMessage()));}
 dec.dispose();Files.writeString(Path.of(getScriptArgs()[0]),new GsonBuilder().setPrettyPrinting().create().toJson(m("program",currentProgram.getName(),"executable_sha256",currentProgram.getExecutableSHA256(),"ghidra",getGhidraVersion(),"modification_before",before,"modification_after",currentProgram.getModificationNumber(),"functions",out)));
 }
}
