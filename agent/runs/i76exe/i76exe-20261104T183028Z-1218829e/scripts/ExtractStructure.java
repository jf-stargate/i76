// Read-only bounded extraction; full output is private. No semantic names exported.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.*;
import com.google.gson.GsonBuilder;
import java.util.*;
import java.nio.file.*;
import java.security.*;
public class ExtractStructure extends GhidraScript {
 String a(Address a) {return a==null?null:a.toString();}
 Map<String,Object> m(Object... v){Map<String,Object> r=new LinkedHashMap<>();for(int i=0;i<v.length;i+=2)r.put((String)v[i],v[i+1]);return r;}
 String hash(byte[] b)throws Exception{ return HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(b)); }
 public void run() throws Exception {
  long before=currentProgram.getModificationNumber();
  var fm=currentProgram.getFunctionManager();var li=currentProgram.getListing();var rm=currentProgram.getReferenceManager();
  List<Function> all=new ArrayList<>();for(Function f:fm.getFunctions(true))all.add(f);
  int first=0,last=0;for(int i=0;i<all.size();i++){long x=all.get(i).getEntryPoint().getOffset();if(x<0x46fa00L)first=i+1;if(x<=0x470d20L)last=i;}
  List<Object> fs=new ArrayList<>();Set<Address> objects=new TreeSet<>();
  for(int j=first-1;j<=last+1;j++){
   Function f=all.get(j);List<Object> ranges=new ArrayList<>(),ins=new ArrayList<>(),refs=new ArrayList<>(),incoming=new ArrayList<>();Set<String> calls=new TreeSet<>();
   for(AddressRange r:f.getBody().getAddressRanges()){byte[] b=new byte[(int)r.getLength()];currentProgram.getMemory().getBytes(r.getMinAddress(),b);ranges.add(m("start",a(r.getMinAddress()),"end",a(r.getMaxAddress()),"sha256",hash(b)));}
   for(Instruction i:li.getInstructions(f.getBody(),true)){
    List<Object> rr=new ArrayList<>();
    for(Reference r:i.getReferencesFrom()){
     Address dest=r.getToAddress();String type=r.getReferenceType().toString();Function target=fm.getFunctionContaining(dest);
     Address obj=dest;Data d=li.getDataContaining(dest);if(d!=null)obj=d.getMinAddress();
     if(r.getReferenceType().isData() && dest.isMemoryAddress())objects.add(obj);
     Map<String,Object> row=m("from",a(i.getAddress()),"to",a(dest),"object",a(obj),"type",type,"operand",r.getOperandIndex(),"function",target==null?null:a(target.getEntryPoint()));
     rr.add(row);refs.add(row);
     if(r.getReferenceType().isCall() && target!=null)calls.add(a(target.getEntryPoint()));
    }
    ins.add(m("address",a(i.getAddress()),"length",i.getLength(),"text",i.toString(),"flow",i.getFlowType().toString(),"refs",rr));
   }
   for(Reference r:rm.getReferencesTo(f.getEntryPoint())){Function src=fm.getFunctionContaining(r.getFromAddress());incoming.add(m("from",a(r.getFromAddress()),"type",r.getReferenceType().toString(),"function",src==null?null:a(src.getEntryPoint())));}
   Address end=f.getBody().getMaxAddress(),next=all.get(j+1).getEntryPoint();List<Object> gap=new ArrayList<>();
   for(Address p=end.add(1);p.compareTo(next)<0;){CodeUnit u=li.getCodeUnitContaining(p);Address q=u==null?p:u.getMaxAddress();if(q.compareTo(next)>=0)q=next.subtract(1);byte[] b=new byte[(int)(q.subtract(p)+1)];currentProgram.getMemory().getBytes(p,b);gap.add(m("start",a(p),"end",a(q),"kind",u==null?"undefined":u instanceof Data?"data":"instruction","text",u==null?"":u.toString(),"hex",HexFormat.of().formatHex(b)));p=q.add(1);}
   fs.add(m("entry",a(f.getEntryPoint()),"context",j<first||j>last,"ranges",ranges,"size",f.getBody().getNumAddresses(),"calls",calls,"incoming",incoming,"refs",refs,"instructions",ins,"gap",gap,"next",a(next),"thunk",f.isThunk()));
  }
  List<Object> ds=new ArrayList<>();
  for(Address obj:objects){Data d=li.getDataContaining(obj);MemoryBlock block=currentProgram.getMemory().getBlock(obj);List<Object> users=new ArrayList<>();int length=d==null?1:d.getLength();
   // Include references to interior addresses, not only object starts.
   for(Address p=obj;p.compareTo(obj.add(length))<0;p=p.add(1))for(Reference r:rm.getReferencesTo(p)){Function f=fm.getFunctionContaining(r.getFromAddress());users.add(m("from",a(r.getFromAddress()),"to",a(p),"type",r.getReferenceType().toString(),"function",f==null?null:a(f.getEntryPoint())));}
   ds.add(m("address",a(obj),"length",length,"type",d==null?"undefined":d.getDataType().getName(),"value",d==null?null:d.getDefaultValueRepresentation(),"writable",block!=null&&block.isWrite(),"executable",block!=null&&block.isExecute(),"users",users));
  }
  var out=m("program",currentProgram.getName(),"language",currentProgram.getLanguageID().toString(),"image_base",a(currentProgram.getImageBase()),"executable_sha256",currentProgram.getExecutableSHA256(),"ghidra",getGhidraVersion(),"defined_functions",all.size(),"modification_before",before,"modification_after",currentProgram.getModificationNumber(),"functions",fs,"objects",ds);
  Files.writeString(Path.of(getScriptArgs()[0]),new GsonBuilder().setPrettyPrinting().create().toJson(out));
 }
}
