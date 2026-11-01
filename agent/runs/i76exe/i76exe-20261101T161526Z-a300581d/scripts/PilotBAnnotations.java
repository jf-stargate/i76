// Disposable-project experiment; semantic aliases are not original developer symbols.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.nio.file.*;
import java.security.*;
import java.util.*;
public class PilotBAnnotations extends GhidraScript {
 private final long[] functions={0x410490,0x412500,0x414670,0x4149f0,0x40a320,0x412ce0};
 private Path out;
 private String digest(byte[] b)throws Exception {return HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(b));}
 private void export(String phase)throws Exception {
  DecompInterface d=new DecompInterface();d.openProgram(currentProgram);
  StringBuilder metrics=new StringBuilder("address\tphase\tparameters\tbytes\tsha256\tnode_fields\n");
  for(long va:functions){Function f=getFunctionAt(toAddr(va));var r=d.decompileFunction(f,120,monitor);
   if(!r.decompileCompleted())throw new Exception(r.getErrorMessage());String c=r.getDecompiledFunction().getC();
   Files.writeString(out.resolve(phase+"-"+Long.toHexString(va)+".c"),c);
   StringBuilder ins=new StringBuilder("address\tbytes\n");var it=currentProgram.getListing().getInstructions(f.getBody(),true);
   while(it.hasNext()){var i=it.next();ins.append(i.getAddress()).append("\t").append(HexFormat.of().formatHex(i.getBytes())).append("\n");}
   Files.writeString(out.resolve(phase+"-"+Long.toHexString(va)+"-instructions.tsv"),ins);
   metrics.append(String.format("%08x\t%s\t%d\t%d\t%s\t%d\n",va,phase,f.getParameterCount(),c.length(),digest(c.getBytes(java.nio.charset.StandardCharsets.UTF_8)),c.split("(->ip|->operand_cursor|->next|->frame|->host_cursor)",-1).length-1));
  }Files.writeString(out.resolve(phase+"-metrics.tsv"),metrics);d.dispose();
 }
 private void envelope(long va,String[] names,DataType[] types)throws Exception {
  Function f=getFunctionAt(toAddr(va));java.util.List<Parameter> ps=new java.util.ArrayList<>();
  for(Parameter p:f.getParameters())ps.add(new ParameterImpl(p.getName(),p.getDataType(),currentProgram));
  for(int i=0;i<names.length;i++)ps.add(new ParameterImpl(names[i],types[i],currentProgram));
  f.replaceParameters(ps,Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS,true,SourceType.USER_DEFINED);
 }
 private void parameter(long va,int index,String name,DataType type)throws Exception {
  Function f=getFunctionAt(toAddr(va));Parameter p=f.getParameter(index);
  if(p==null||p.getLength()!=4)throw new Exception("Unexpected parameter "+f+" "+index);
  p.setDataType(type,SourceType.USER_DEFINED);p.setName(name,SourceType.USER_DEFINED);
 }
 public void run()throws Exception {
  String[] a=getScriptArgs();if(a.length!=3)throw new Exception("output-directory APPLY|DRY retail-PE-path");out=Paths.get(a[0]);Files.createDirectories(out);
  if(currentProgram.getDefaultPointerSize()!=4||!currentProgram.getLanguageID().toString().equals("x86:LE:32:default")||!currentProgram.getExecutableMD5().equals("a640ea0097dbb62e0c77b7f2847c7161"))throw new Exception("Retail identity/architecture mismatch");
  int[] expectedParameters={3,4,10,15,0,10};
  for(int i=0;i<functions.length;i++)if(getFunctionAt(toAddr(functions[i])).getParameterCount()!=expectedParameters[i])throw new Exception("Unexpected baseline signature at "+Long.toHexString(functions[i]));
  // Expected instruction fingerprints, independent of historical labels.
  if(getInt(toAddr(0x4146ac))!=0x00000320||getInt(toAddr(0x414966))!=1000||getInt(toAddr(0x4104cd))!=0x10bc)throw new Exception("Instruction guard mismatch");
  byte[] pe=Files.readAllBytes(Paths.get(a[2]));
  if(!digest(pe).equals("bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3"))throw new Exception("Retail PE SHA256 mismatch");
  java.nio.ByteBuffer bb=java.nio.ByteBuffer.wrap(pe).order(java.nio.ByteOrder.LITTLE_ENDIAN);
  int ph=bb.getInt(0x3c), sections=Short.toUnsignedInt(bb.getShort(ph+6));
  int opt=Short.toUnsignedInt(bb.getShort(ph+20));long base=Integer.toUnsignedLong(bb.getInt(ph+52));
  int verified=0;
  for(long va:functions){var it=currentProgram.getListing().getInstructions(getFunctionAt(toAddr(va)).getBody(),true);
   while(it.hasNext()){var ins=it.next();byte[] expected=ins.getBytes();long rva=ins.getAddress().getOffset()-base;boolean matched=false;
    for(int j=0;j<sections;j++){int sh=ph+24+opt+40*j;long rv=Integer.toUnsignedLong(bb.getInt(sh+12));long size=Integer.toUnsignedLong(bb.getInt(sh+16));
     if(rva>=rv&&rva+expected.length<=rv+size){int off=(int)(Integer.toUnsignedLong(bb.getInt(sh+20))+rva-rv);
      if(!Arrays.equals(expected,Arrays.copyOfRange(pe,off,off+expected.length)))throw new Exception("PE instruction mismatch at "+ins.getAddress());matched=true;break;}}
    if(!matched)throw new Exception("Unmapped instruction");verified++;
   }
  }
  println("Verified "+verified+" original instructions against SHA256-authenticated retail PE");
  export("before");
  if(!a[1].equals("APPLY")){println("DRY: guards passed; no annotations applied");return;}
  int tx=currentProgram.startTransaction("Pilot B VM readability experiment");boolean commit=false;
  try {
   DataTypeManager m=currentProgram.getDataTypeManager();CategoryPath cat=new CategoryPath("/PilotB");
   if(m.getDataType(cat,"VmNode")!=null)throw new Exception("Fresh disposable baseline required");
   DataType word=UnsignedIntegerDataType.dataType;
   StructureDataType token=new StructureDataType(cat,"VmToken",0);token.add(word,"kind",null);token.add(word,"payload",null);
   DataType t=m.addDataType(token,DataTypeConflictHandler.DEFAULT_HANDLER);
   StructureDataType node=new StructureDataType(cat,"VmNode",0);
   node.add(new ArrayDataType(word,1024,4),"workspace_words","Mixed scalar/address/frame storage; no universal pointer element type");
   node.add(new ArrayDataType(word,40,4),"host_words","Mixed scalar/address host slots, separate from workspace");
   node.add(word,"condition","Truth is nonzero; predicates need not return canonical one");
   node.add(new PointerDataType(t,4),"token_base",null);node.add(new PointerDataType(t,4),"ip",null);
   node.add(new PointerDataType(word,4),"frame","Points to saved return IP; previous frame is frame[-1]");
   node.add(new PointerDataType(word,4),"operand_cursor",null);node.add(new PointerDataType(word,4),"host_cursor",null);
   node.add(new PointerDataType(node,4),"next",null);
   DataType n=m.addDataType(node,DataTypeConflictHandler.DEFAULT_HANDLER);if(n.getLength()!=0x10bc)throw new Exception("Layout mismatch");
   DataType np=new PointerDataType(n,4), npp=new PointerDataType(np,4);
   parameter(0x414670,0,"node",np);parameter(0x412ce0,0,"node",np);
   parameter(0x4149f0,10,"head",npp);
   // Import and relocation signatures stay untyped: +10A8 is an index before relocation.
   // Count remains scalar; do not type the serialized entry index as a token pointer in the loader.
   parameter(0x4149f0,11,"pending_count",new PointerDataType(IntegerDataType.dataType,4));
   // Call envelopes are proved by push sequences and caller cleanup. Trailing roles remain qualified.
   envelope(0x414670,new String[]{"forwarded_unknown","visit_ordinal_unused"},new DataType[]{word,word});
   envelope(0x412ce0,new String[]{"forwarded_unknown","invocation_scratch_unused"},new DataType[]{word,new PointerDataType(VoidDataType.dataType,4)});
   envelope(0x4149f0,new String[]{"forwarded_unknown"},new DataType[]{word});
   commit=true;
  } finally {currentProgram.endTransaction(tx,commit);}
  export("after");println("APPLY complete; 2 types, 4 parameter annotations and 3 call envelopes; existing names/comments retained");
 }
}
