// Guarded integration, not recovered developer source. Ghidra 12.1.4.
//@category i76
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.data.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.nio.*;
import java.security.*;
import java.util.*;
public class ConsolidateSemantics extends GhidraScript {
 static final String SHA="bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3";
 static final CategoryPath CAT=new CategoryPath("/Interstate76/SemanticConsolidation");
 boolean apply; Path bundle; List<String> log=new ArrayList<>();Map<String,String> expected=new TreeMap<>();Map<String,DataType> types=new HashMap<>();int changed,already,preserved,conflicts;
 DataType u=UnsignedIntegerDataType.dataType,f32=FloatDataType.dataType,f64=DoubleDataType.dataType,i32=IntegerDataType.dataType,u16=UnsignedShortDataType.dataType;
 String hash(byte[] b)throws Exception{return HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(b));}
 String sig(Function f){StringBuilder b=new StringBuilder(f.getName()+"|"+f.getSymbol().getSource()+"|"+f.getCallingConventionName()+"|"+f.hasCustomVariableStorage()+"|"+f.getSignatureSource()+"|"+f.getReturnType().getPathName()+"|"+f.getReturn().getVariableStorage());for(var p:f.getParameters())b.append("|").append(p.getName()).append(":").append(p.getDataType().getPathName()).append(":").append(p.getVariableStorage()).append(":").append(p.getSource());return b.toString();}
 void record(String status,String id,String reason){log.add(status+"\t"+id+"\t"+reason.replace('\n',' '));if(status.equals("APPLY"))changed++;if(status.equals("ALREADY"))already++;if(status.equals("PRESERVE"))preserved++;if(status.equals("CONFLICT"))conflicts++;}
 DataType ptr(DataType t){return new PointerDataType(t,4);}
 // Exact original body/layout + original PE bytes; metadata alone is insufficient.
 void identity(Path pePath)throws Exception{
  if(!SHA.equals(currentProgram.getExecutableSHA256())||!"a640ea0097dbb62e0c77b7f2847c7161".equals(currentProgram.getExecutableMD5())||!currentProgram.getLanguageID().toString().equals("x86:LE:32:default")||currentProgram.getDefaultPointerSize()!=4||currentProgram.getImageBase().getOffset()!=0x400000||!ghidra.framework.Application.getApplicationVersion().equals("12.1.4"))throw new Exception("Identity/version mismatch");
  byte[] pe=Files.readAllBytes(pePath);if(!hash(pe).equals(SHA))throw new Exception("Wrong retail PE");ByteBuffer b=ByteBuffer.wrap(pe).order(ByteOrder.LITTLE_ENDIAN);int ph=b.getInt(0x3c),n=Short.toUnsignedInt(b.getShort(ph+6)),opt=Short.toUnsignedInt(b.getShort(ph+20));if(b.getInt(ph)!=0x4550||b.getShort(ph+4)!=0x14c||b.getShort(ph+24)!=0x10b||b.getInt(ph+52)!=0x400000)throw new Exception("PE layout mismatch");
  for(String line:Files.readAllLines(bundle.resolve("code_guards.tsv"))){String[] row=line.split("\t");if(row[0].equals("address"))continue;Function fn=getFunctionAt(toAddr(row[0]));if(fn==null||!fn.getBody().toString().equals(row[1]))throw new Exception("Body mismatch "+row[0]);MessageDigest md=MessageDigest.getInstance("SHA-256");var it=fn.getBody().getAddressRanges();while(it.hasNext()){var r=it.next();byte[] bytes=new byte[(int)r.getLength()];currentProgram.getMemory().getBytes(r.getMinAddress(),bytes);md.update(bytes);long rva=r.getMinAddress().getOffset()-0x400000L;boolean found=false;for(int j=0;j<n;j++){int sh=ph+24+opt+j*40;long start=Integer.toUnsignedLong(b.getInt(sh+12)),size=Integer.toUnsignedLong(b.getInt(sh+16));if(rva>=start&&rva+bytes.length<=start+size){int off=(int)(Integer.toUnsignedLong(b.getInt(sh+20))+rva-start);if(!Arrays.equals(bytes,Arrays.copyOfRange(pe,off,off+bytes.length)))throw new Exception("PE bytes differ "+r);found=true;break;}}if(!found)throw new Exception("Unmapped PE range "+r);}
   if(!HexFormat.of().formatHex(md.digest()).equals(row[2]))throw new Exception("Body digest mismatch "+row[0]);
  }
  // Constants and live/wire distinction anchors, checked even on repeat.
  if(getInt(toAddr(0x4104cd))!=0x10bc||getInt(toAddr(0x4146ac))!=800||getInt(toAddr(0x414966))!=1000||getByte(toAddr(0x42d5d0))!=(byte)0xc3||getLong(toAddr(0x4faf18))!=0x4338000000000000L||getInt(toAddr(0x4be8a8))!=0x3dcccccd||getInt(toAddr(0x4be8ac))!=0xbf800000)throw new Exception("Semantic layout anchors differ");
 }
 String bodies()throws Exception{StringBuilder b=new StringBuilder();var it=currentProgram.getFunctionManager().getFunctions(true);while(it.hasNext()){var fn=it.next();MessageDigest md=MessageDigest.getInstance("SHA-256");var rs=fn.getBody().getAddressRanges();while(rs.hasNext()){var r=rs.next();byte[] bytes=new byte[(int)r.getLength()];currentProgram.getMemory().getBytes(r.getMinAddress(),bytes);md.update(bytes);}b.append(fn.getEntryPoint()+"|"+fn.getBody()+"|"+HexFormat.of().formatHex(md.digest())+"\n");}return b.toString();}
 Set<String> analyst(){Set<String> s=new TreeSet<>();var it=currentProgram.getSymbolTable().getAllSymbols(true);while(it.hasNext()){var v=it.next();if(v.getSource()==SourceType.USER_DEFINED)s.add(v.getAddress()+"|"+v.getSymbolType()+"|"+v.getName(true));}return s;}
 Map<String,String> comments(){Map<String,String> out=new TreeMap<>();for(int k=0;k<=4;k++){var it=currentProgram.getListing().getCommentAddressIterator(k,currentProgram.getMemory(),true);while(it.hasNext()){var a=it.next();out.put(a+"|"+k,currentProgram.getListing().getComment(k,a));}}return out;}
 void type(StructureDataType t)throws Exception{
  var old=currentProgram.getDataTypeManager().getDataType(CAT,t.getName());
  if(old!=null&&!old.isEquivalent(t)){record("CONFLICT","type:"+t.getName(),"Existing definition differs; dependent signatures skipped");return;}
  if(old!=null){record("ALREADY","type:"+t.getName(),"Equivalent layout");types.put(t.getName(),old);return;}
  record("APPLY","type:"+t.getName(),"New reference layout; no mapped instances");types.put(t.getName(),apply?currentProgram.getDataTypeManager().addDataType(t,DataTypeConflictHandler.KEEP_HANDLER):t);
 }
 void types()throws Exception{
  var normal=new StructureDataType(CAT,"TER_Normal3f",0);normal.add(f32,"x",null);normal.add(f32,"y",null);normal.add(f32,"z",null);type(normal);
  var page=new StructureDataType(CAT,"TER_Page",0);page.add(new ArrayDataType(new ArrayDataType(u16,128,2),128,256),"samples","low12 height, bit12 unknown, high3 material");type(page);
  var token=new StructureDataType(CAT,"VmToken",0);token.add(u,"kind",null);token.add(u,"payload",null);type(token);if(!types.containsKey("VmToken"))return;
  var node=new StructureDataType(CAT,"VmNode",0);node.add(new ArrayDataType(u,1024,4),"workspace_words","Mixed values/addresses; not pointer array");node.add(new ArrayDataType(u,40,4),"host_words","Separate host argument storage");node.add(u,"condition",null);node.add(ptr(types.get("VmToken")),"token_base",null);node.add(ptr(types.get("VmToken")),"ip","LIVE only: scalar entry index before relocation");node.add(ptr(u),"frame",null);node.add(ptr(u),"operand_cursor",null);node.add(ptr(u),"host_cursor",null);node.add(ptr(node),"next",null);
  if(node.getLength()!=0x10bc||node.getComponentAt(0x1000).getOffset()!=0x1000||node.getComponentAt(0x10a8).getOffset()!=0x10a8||node.getComponentAt(0x10b8).getOffset()!=0x10b8)throw new Exception("VM layout mismatch");type(node);
 }
 // Atomic signature replacement only on a fully recognized signature, including sources/storage.
 void signature(String va,DataType ret,String[] names,DataType[] ts,boolean packed)throws Exception{
  Function fn=getFunctionAt(toAddr(va));boolean same=fn.getParameterCount()==names.length&&fn.getReturnType().isEquivalent(ret)&&"__cdecl".equals(fn.getCallingConventionName())&&(!packed||fn.getReturn().getVariableStorage().toString().equals("EAX:4"));int off=4;
  for(int j=0;j<names.length&&same;j++){var p=fn.getParameter(j);same=p.getName().equals(names[j])&&p.getDataType().isEquivalent(ts[j])&&p.isStackVariable()&&p.getStackOffset()==off;off+=ts[j].getLength();}
  if(same){record("ALREADY",va+":signature","Equivalent parameters, return and storage");return;}
  if(!sig(fn).equals(expected.get(va))){record("PRESERVE",va+":signature","Unrecognized signature/name/source/storage; no replacement");return;}
  record("APPLY",va+":signature","Exact measured baseline matched");if(!apply)return;
  Parameter[] ps=new Parameter[names.length];off=4;for(int j=0;j<ps.length;j++){ps[j]=packed?new ParameterImpl(names[j],ts[j],new VariableStorage(currentProgram,currentProgram.getAddressFactory().getStackSpace().getAddress(off),ts[j].getLength()),currentProgram):new ParameterImpl(names[j],ts[j],currentProgram);off+=ts[j].getLength();}
  fn.updateFunction("__cdecl",packed?new ReturnParameterImpl(ret,new VariableStorage(currentProgram,currentProgram.getRegister("EAX")),currentProgram):new ReturnParameterImpl(ret,currentProgram),packed?Function.FunctionUpdateType.CUSTOM_STORAGE:Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS,true,SourceType.USER_DEFINED,ps);
  off=4;for(var p:fn.getParameters()){if(!p.isStackVariable()||p.getStackOffset()!=off||p.isAutoParameter())throw new Exception("Unexpected stack/hidden parameter "+va);off+=p.getLength();}
 }
 void vm(String va)throws Exception{
  if(!types.containsKey("VmNode")){record("CONFLICT",va+":signature","VM type conflict");return;}
  var fn=getFunctionAt(toAddr(va));String original=expected.get(va);String[] parts=original.split("\\|");int count=parts.length-7;String[] names=new String[count+(va.equals("004149f0")?1:2)];DataType[] ts=new DataType[names.length];
  // Preserve original first 10/15 parameter types, even on idempotent repeat.
  for(int j=0;j<count;j++){String[] p=parts[j+7].split(":",4);names[j]=p[0];ts[j]=currentProgram.getDataTypeManager().getDataType(p[1]);if(ts[j]==null)throw new Exception("Baseline type absent "+p[1]);}
  if(va.equals("004149f0")){names[10]="head";ts[10]=ptr(ptr(types.get("VmNode")));names[11]="pending_count";ts[11]=ptr(i32);names[count]="forwarded_unknown";ts[count]=u;}
  else{names[0]="node";ts[0]=ptr(types.get("VmNode"));names[count]="forwarded_unknown";ts[count]=u;names[count+1]=va.equals("00414670")?"visit_ordinal_unused":"invocation_scratch_unused";ts[count+1]=va.equals("00414670")?u:ptr(VoidDataType.dataType);}
  String retPath=parts[5];if(!fn.getReturnType().getPathName().equals(retPath)){record("PRESERVE",va+":signature","Return type differs from baseline");return;}signature(va,fn.getReturnType(),names,ts,false);
 }
 void data(String va,DataType t)throws Exception{
  var a=toAddr(va);var existing=getDataAt(a);if(va.equals("006442c0")&&existing!=null&&existing.getDataType().getName().equals("int")){record("CONFLICT",va+":data","Known v99 int conflicts with original float spacing; preserved pending analyst decision");return;}if(existing!=null&&existing.getDataType().isEquivalent(t)){record("ALREADY",va+":data","Equivalent mapped type");return;}
  for(int j=0;j<t.getLength();j++){var at=a.add(j);var old=getDataContaining(at);if(getInstructionContaining(at)!=null||(old!=null&&(!Undefined.isUndefined(old.getDataType())||old.getMinAddress().compareTo(a)<0||old.getMaxAddress().compareTo(a.add(t.getLength()-1))>0))){record("PRESERVE",va+":data","Defined data/instruction overlaps footprint at "+at);return;}if(j>0)for(var s:currentProgram.getSymbolTable().getSymbols(at))if(s.getSource()==SourceType.USER_DEFINED){record("PRESERVE",va+":data","Interior analyst label at "+at);return;}}
  record("APPLY",va+":data","Whole undefined footprint; labels/comments retained");if(apply){clearListing(a,a.add(t.getLength()-1));createData(a,t);}
 }
 void note(String va,String text){String marker="Semantic consolidation: "+text;var a=toAddr(va);String old=currentProgram.getListing().getComment(CodeUnit.REPEATABLE_COMMENT,a);if(old!=null&&old.contains(marker)){record("ALREADY",va+":comment","Semantic qualification already present");return;}record("APPLY",va+":comment","Append evidence qualification, retain prior text");if(apply)currentProgram.getListing().setComment(a,CodeUnit.REPEATABLE_COMMENT,(old==null?"":old+"\n")+marker);}
 public void run()throws Exception{
  log.clear();expected.clear();types.clear();changed=already=preserved=conflicts=0;String[] args=getScriptArgs();if(args.length<3||args.length>4)throw new Exception("bundle-directory private-retail-PE action-log [APPLY]");if(args.length==4&&!args[3].equals("APPLY"))throw new Exception("Only explicit APPLY authorizes changes");apply=args.length==4;bundle=Paths.get(args[0]);identity(Paths.get(args[1]));
  for(String line:Files.readAllLines(bundle.resolve("expected_signatures.tsv"))){String[] r=line.split("\t",2);if(!r[0].equals("address"))expected.put(r[0],r[1]);}
  String bodies=bodies();Set<String> analyst=analyst();Map<String,String> comments=comments();int count=currentProgram.getFunctionManager().getFunctionCount();int tx=currentProgram.startTransaction("Semantic consolidation guarded integration");boolean commit=false;
  try{
   types();signature("00493080",i32,new String[]{"setup_value","mode","sample_spacing"},new DataType[]{u,i32,f32},false);
   if(types.containsKey("TER_Normal3f"))signature("004931c0",ptr(types.get("TER_Normal3f")),new String[]{"out_normal","world_x","world_z"},new DataType[]{ptr(types.get("TER_Normal3f")),f64,f64},true);else record("CONFLICT","004931c0:signature","Normal type conflict");
   for(String va:new String[]{"00414670","004149f0","00412ce0"})vm(va);
   String[][] resources={{"0046ffc0","logical_name"},{"00470070","logical_name"},{"00470340","logical_name"},{"00470b20","logical_name"},{"004b2e00","key16"},{"004b3030","logical_name","out_size","destination","destination_capacity"}};
   for(String[] row:resources){var fn=getFunctionAt(toAddr(row[0]));var ps=fn.getParameters();if(ps.length!=row.length-1){record("PRESERVE",row[0]+":signature","Unexpected parameter count");continue;}DataType[] ts=new DataType[ps.length];for(int j=0;j<ts.length;j++)ts[j]=ps[j].getDataType();signature(row[0],fn.getReturnType(),Arrays.copyOfRange(row,1,row.length),ts,false);}
   data("006442c0",f32);data("006442c4",f32);data("004faf18",f64);data("004be8a0",f32);data("004be8a8",f32);data("004be8ac",f32);data("00644380",new ArrayDataType(ptr(u16),16384,4));
   note("00493160","height12 return (&0xfff), not packed material word. Alias retained. 004931A4 is interior. Pilot A A5-A7.");
   note("00493550","numeric ST0 return, no hidden result pointer; existing v99 float ABI presentation retained. No final float store proved. RC-down FISTP, float X rows before RC restore; Ghidra ROUND/casts are not exact arithmetic. Pilot A A8-A12.");
   note("004931c0","returns caller output in EAX; output +4, packed X double +8, Z double +16; triangle normal differs from bilinear height, literal world-minus-index selector and slope signs. Pilot A A15-A21.");
   note("00414670","live-node only; serialized +10A8 is an index before relocation. Completion is restored operand_cursor == node base. Host dispatcher advances IP synchronously; trailing argument roles remain unresolved. Pilot B FSM-B-control/abi-envelope.");
   note("0046ffc0","returns retained bytes; conditional PIX-first vs loaded-file-first at 00609564. Size and release stay PIX-first independently; collision lifetime not established. Pilot C C1/C2/C10.");
   note("00470340","index/registered membership only; not cache residency or loadability. Analyst alias retained. Pilot C C9.");
   note("00609584","record count (+1/-1 per allocation), despite historical used_bytes alias. Alias retained. Pilot C C5.");
   note("004702d0","hash lookup then eviction, not key canonicalization; retained references/invalidation safety unresolved. Alias retained. Pilot C C10.");
   note("0042d5d0","tested authenticated retail reporter body is a single RET (Pilot B). Narrows Pilot C reporter uncertainty for this PE only; does not prove safe resource failure handling or other configurations.");
   if(count!=currentProgram.getFunctionManager().getFunctionCount()||!bodies.equals(bodies()))throw new Exception("Function boundaries/bytes changed");if(!analyst().containsAll(analyst))throw new Exception("Analyst symbol lost");var after=comments();for(var e:comments.entrySet())if(!after.containsKey(e.getKey())||!after.get(e.getKey()).startsWith(e.getValue()))throw new Exception("Analyst comment lost "+e.getKey());
   commit=apply;
  }finally{currentProgram.endTransaction(tx,commit);Files.writeString(Paths.get(args[2]),"disposition\tentity\treason\n"+String.join("\n",log)+"\nSUMMARY\tAPPLY="+apply+" committed="+commit+"\tapply="+changed+" already="+already+" preserve="+preserved+" conflict="+conflicts+"\n");println("CONSOLIDATION apply="+apply+" committed="+commit+" eligible="+changed+" already="+already+" preserve="+preserved+" conflict="+conflicts);}
 }
}
