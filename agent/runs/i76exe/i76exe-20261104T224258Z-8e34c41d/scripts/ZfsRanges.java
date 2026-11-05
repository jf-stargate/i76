import ghidra.app.script.GhidraScript;
import com.google.gson.GsonBuilder;
import java.util.*;
import java.nio.file.*;
public class ZfsRanges extends GhidraScript {
 Map<String,Object> m(Object... a){var r=new LinkedHashMap<String,Object>();for(int i=0;i<a.length;i+=2)r.put((String)a[i],a[i+1]);return r;}
 public void run() throws Exception {
 var out=new ArrayList<Object>();
 for(String pair:getScriptArgs()[1].split(",")) {
 var parts=pair.split(":");var start=toAddr(parts[0]);var end=toAddr(parts[1]);
 var rows=new ArrayList<Object>();
 for(var i:currentProgram.getListing().getInstructions(start,true)){if(i.getAddress().compareTo(end)>0)break;rows.add(m("va",i.getAddress().toString(),"bytes",HexFormat.of().formatHex(i.getBytes()),"asm",i.toString()));}
 out.add(m("start",parts[0],"end",parts[1],"instructions",rows));
 }
 var strings=new ArrayList<Object>();
 for(String s:getScriptArgs()[2].split(",")){byte[] b=new byte[40];currentProgram.getMemory().getBytes(toAddr(s),b);strings.add(m("va",s,"hex",HexFormat.of().formatHex(b)));}
 Files.writeString(Path.of(getScriptArgs()[0]),new GsonBuilder().setPrettyPrinting().create().toJson(m("ranges",out,"data",strings)));
 }
}
