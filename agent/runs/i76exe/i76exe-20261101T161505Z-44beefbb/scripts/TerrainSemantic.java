// Evidence: SEMANTIC_RECONSTRUCTION.md and original anchors in this run.
// Default is dry-run. Explicit argument 'apply' mutates only the opened working copy.
//@category i76
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.data.*;
import ghidra.program.model.symbol.*;
import java.security.MessageDigest;
import java.util.*;
public class TerrainSemantic extends GhidraScript {
 boolean apply; int changed,already,skipped;
 CategoryPath cat=new CategoryPath("/I76_TerrainPilotA");
 DataType f=FloatDataType.dataType,d=DoubleDataType.dataType,i=IntegerDataType.dataType,u=UnsignedIntegerDataType.dataType,h=UnsignedShortDataType.dataType;
 void act(String s)throws Exception { changed++;println((apply?"APPLY ":"PLAN ")+s); }
 void skip(String s){skipped++;println("PRESERVE "+s);}
 DataType type(DataType t)throws Exception {
  DataType old=currentProgram.getDataTypeManager().getDataType(cat,t.getName());
  if(old!=null){if(!old.isEquivalent(t))throw new Exception("Conflicting type "+t.getName());already++;return old;}
  act("type "+t.getName());return apply?currentProgram.getDataTypeManager().addDataType(t,DataTypeConflictHandler.KEEP_HANDLER):t;
 }
 void sig(String va,String expected,DataType ret,String[] names,DataType... types)throws Exception {
  Function fn=getFunctionAt(toAddr(va));if(fn==null||!fn.getName().equals(expected)){skip(va+" function name");return;}
  Parameter[] ps=fn.getParameters();
  boolean match=ps.length==names.length;
  if(match){for(int n=0;n<ps.length;n++)match &= ps[n].getName().equals(names[n])&&ps[n].getDataType().isEquivalent(types[n]);}
  if(match && fn.getReturnType().isEquivalent(ret)){already++;return;}
  // Only accept the actual v98 default parameters, or an already completed application.
  if(ps.length!=names.length && !(va.equals("004931c0")&&ps.length==4)){skip(va+" parameter count");return;}
  for(Parameter p:ps)if(p.getSource()==SourceType.USER_DEFINED){skip(va+" analyst parameter "+p.getName());return;}
  int offExpected=4;
  int[] lengths=va.equals("004931c0")?new int[]{4,8,4,4}:va.equals("00493080")?new int[]{4,4,4}:va.equals("00493160")?new int[]{4,4}:new int[]{8,8};
  for(int n=0;n<ps.length;n++){
   if(!ps[n].getName().equals("param_"+(n+1)) || !ps[n].isStackVariable() || ps[n].getStackOffset()!=offExpected || ps[n].getLength()!=lengths[n]){skip(va+" unexpected original parameter/storage");return;}
   offExpected+=lengths[n];
  }
  String rt=fn.getReturnType().getName();
  String allowed=va.equals("00493550")?"uint":va.equals("00493080")?"undefined4":va.equals("004931c0")?"undefined":"ushort";
  if(!rt.equals(allowed)){skip(va+" return "+rt);return;}
  act(va+" signature "+ret+" "+Arrays.toString(names));
  if(apply){Parameter[] out=new Parameter[names.length];
   boolean packedStack=va.equals("004931c0");int off=4;
   for(int n=0;n<out.length;n++){
    out[n]=packedStack?new ParameterImpl(names[n],types[n],new VariableStorage(currentProgram,currentProgram.getAddressFactory().getStackSpace().getAddress(off),types[n].getLength()),currentProgram):new ParameterImpl(names[n],types[n],currentProgram);
    off+=types[n].getLength();
   }
   fn.updateFunction("__cdecl",new ReturnParameterImpl(ret,currentProgram),packedStack?Function.FunctionUpdateType.CUSTOM_STORAGE:Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS,true,SourceType.USER_DEFINED,out);
  }
 }
 void data(String va,DataType t)throws Exception {
  var a=toAddr(va);var end=a.add(t.getLength()-1);
  var old=getDataAt(a);if(old!=null&&old.getDataType().isEquivalent(t)){already++;return;}
  for(long off=0;off<t.getLength();off++){
   var p=a.add(off);if(getInstructionContaining(p)!=null){skip(va+" instruction");return;}
   var x=getDataContaining(p);if(x!=null&&!Undefined.isUndefined(x.getDataType())){skip(va+" existing data "+x);return;}
   if(off>0)for(var sym:currentProgram.getSymbolTable().getSymbols(p))if(sym.getSource()==SourceType.USER_DEFINED){skip(va+" interior symbol "+sym);return;}
  }
  act(va+" data "+t.getName());if(apply){clearListing(a,end);createData(a,t);}
 }
 void comment(String va,String text)throws Exception {
  var a=toAddr(va);String old=currentProgram.getListing().getComment(CodeUnit.REPEATABLE_COMMENT,a);
  if(old!=null&&old.contains(text)){already++;return;}
  act(va+" additive comment");if(apply)currentProgram.getListing().setComment(a,CodeUnit.REPEATABLE_COMMENT,(old==null?"":old+"\n")+text);
 }
 public void run()throws Exception {
  apply=getScriptArgs().length>0&&getScriptArgs()[0].equals("apply");
  if(!currentProgram.getExecutableSHA256().equalsIgnoreCase("bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3")||!currentProgram.getExecutableMD5().equalsIgnoreCase("a640ea0097dbb62e0c77b7f2847c7161")||!currentProgram.getLanguageID().toString().equals("x86:LE:32:default")||currentProgram.getImageBase().getOffset()!=0x400000)throw new Exception("Retail identity/architecture mismatch");
  // Compare actual database instruction bytes to the privately measured original PE ranges.
  for(String[] row:CODE_HASHES){byte[] b=new byte[Integer.parseInt(row[1])];currentProgram.getMemory().getBytes(toAddr(row[0]),b);String hex=HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(b));if(!hex.equals(row[2]))throw new Exception("Code mismatch "+row[0]);}
  int tx=currentProgram.startTransaction("Terrain semantic pilot");boolean ok=false;
  try{
   StructureDataType vec=new StructureDataType(cat,"TER_Normal3f",0);vec.add(f,"x",null);vec.add(f,"y",null);vec.add(f,"z",null);DataType v=type(vec);
   StructureDataType page=new StructureDataType(cat,"TER_Page",0);page.add(new ArrayDataType(new ArrayDataType(h,128,2),128,256),"samples", "[z][x], packed low12 height, bit12 unknown, high3 class");type(page);
   sig("00493080","build_runtime_terrain_page_grid_from_zmap",i,new String[]{"setup_value","mode","sample_spacing"},u,i,f);
   sig("00493160","TER_ReadPackedTerrainGridWord",h,new String[]{"sample_x","sample_z"},i,i);
   sig("00493550","TER_SampleBilinearHeightXZ",d,new String[]{"world_x","world_z"},d,d);
   sig("004927b0","lookup_terrain_material_index_at_world_xz",h,new String[]{"world_x","world_z"},d,d);
   sig("004931c0","TER_SampleSurfaceNormalXZ",VoidDataType.dataType,new String[]{"out_normal","world_x","world_z"},new PointerDataType(v,4),d,d);
   data("006442c0",f);data("006442c4",f);data("004faf18",d);data("004be8a0",f);data("004be8a8",f);data("004be8ac",f);
   // Whole grid only if undefined with no interior user labels; element type keeps literal offsets readable.
   data("00644380",new ArrayDataType(new PointerDataType(h,4),16384,4));
   comment("00493160","TER Pilot A: returns height12, not packed word; 004931A4 is an interior word load, not a function. Signed page upper-bound only; no negative-page guard. Research alias retained to preserve analyst symbol.");
   comment("00493550","TER Pilot A: bilinear height, double X/Z stack inputs, x87 ST0 numeric return; double is a C ABI presentation, no final double/float store. No hidden result pointer. Floor FISTP at 4935EE/493608 requires hardware rounding qualification. Float X intermediates; restore RC before final Z interpolation. Supersedes obsolete bounds comment above.");
   comment("004931c0","TER Pilot A: void(out float[3], double X, double Z). Rounded admission test; ftol truncates lattice coordinates. Triangle decision compares unscaled world coordinates minus lattice indices, as encoded. Output +X slope sign is positive in first triangle branch. Old raw-word comment is obsolete.");
   comment("00493080","TER Pilot A: initializes 16384 borrowed page pointers to 0059C588; overlays 80x80 byte ZMAP at +24/+24; FF retains default. Stores setup_value at 6442D0, mode constants at 4FAD20/24, spacing and reciprocal at 6442C0/C4; no allocation here.");
   comment("004927b0","TER Pilot A: rounded bias-based coordinate admission; outside returns class 5; invalid page index returns 0; selected packed sample >>13. Bit12 unresolved.");
   ok=true;
  }finally{currentProgram.endTransaction(tx,apply&&ok);println("SUMMARY apply="+apply+" changed="+changed+" already="+already+" skipped="+skipped+" committed="+(apply&&ok));}
 }
 static final String[][] CODE_HASHES={{"00493080","205","e502bc5d513534d65743a441a6d145cbffe40b3f8dca15e923c5f56cc362bfd1"},{"00493160","83","5fbed866b12508c94bf62e0923318d4a833da3c1208b4b4242b70a4e9daf7c64"},{"004931c0","899","c5c418c9f40a521f8b7f16068063b0f765695db60c3732fc16c48bd77e799b0c"},{"00493550","611","dd3171475a30de903df9b35f8e486fd5f6b393add7d27a67d88a41f0ff763613"},{"004927b0","224","1091c440f47c4cda959fb3aea82892a61757c20a1da51f95c4f9e8bfdfb24d74"}};
}
