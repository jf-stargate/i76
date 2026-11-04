import ghidra.app.script.GhidraScript;
import java.nio.file.*;
public class ZfsRefs extends GhidraScript {
 public void run() throws Exception {
 var b=new StringBuilder();
 for(String s:getScriptArgs()[1].split(",")) {
  var a=toAddr(s);b.append("TARGET "+s+"\n");
  var d=getDataContaining(a);if(d!=null)b.append(d+"\n");
  for(var r:getReferencesTo(a)){var f=getFunctionContaining(r.getFromAddress());b.append(r+" FUNCTION "+(f==null?"none":f.getEntryPoint()+" "+f.getName())+"\n");}
 }
 Files.writeString(Path.of(getScriptArgs()[0]),b.toString());
 }
}
