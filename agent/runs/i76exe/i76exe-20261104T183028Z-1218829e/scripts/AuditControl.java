// Post-freeze original switch-table negative control, outside the ranked range.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import com.google.gson.GsonBuilder;
import java.util.*;
import java.nio.file.*;
public class AuditControl extends GhidraScript {
 Map<String,Object> m(Object... v){Map<String,Object> r=new LinkedHashMap<>();for(int i=0;i<v.length;i+=2)r.put((String)v[i],v[i+1]);return r;}
 public void run()throws Exception{
 long n=currentProgram.getModificationNumber();var li=currentProgram.getListing();var rm=currentProgram.getReferenceManager();List<Object> rows=new ArrayList<>();
 for(long x=0x412c30L;x<0x412cc0L;){Address p=toAddr(x);CodeUnit u=li.getCodeUnitContaining(p);long end=u==null?x:u.getMaxAddress().getOffset();List<Object> refs=new ArrayList<>();for(long y=x;y<=end;y++){for(Reference r:rm.getReferencesTo(toAddr(y)))refs.add(m("from",r.getFromAddress().toString(),"to",r.getToAddress().toString(),"type",r.getReferenceType().toString()));}rows.add(m("start",p.toString(),"end",toAddr(end).toString(),"text",u==null?"undefined":u.toString(),"references",refs));x=end+1;}
 List<Object> ins=new ArrayList<>();for(Instruction i:li.getInstructions(new AddressSet(toAddr(0x412830L),toAddr(0x412c2fL)),true)){if(i.getFlowType().isComputed()||i.getAddress().getOffset()==0x412916L){List<Object> refs=new ArrayList<>();for(Reference r:i.getReferencesFrom())refs.add(m("from",r.getFromAddress().toString(),"to",r.getToAddress().toString(),"type",r.getReferenceType().toString()));ins.add(m("address",i.getAddress().toString(),"text",i.toString(),"references",refs));}}
 var out=m("rows",rows,"computed_instructions",ins,"modification_before",n,"modification_after",currentProgram.getModificationNumber());Files.writeString(Path.of(getScriptArgs()[0]),new GsonBuilder().setPrettyPrinting().create().toJson(out));
 }
}
