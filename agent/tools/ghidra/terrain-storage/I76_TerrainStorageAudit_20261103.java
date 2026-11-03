// Standalone guarded data correction for the verified private v99 export.
// Research aliases are not recovered developer identifiers. No code/ABI changes.
//@category Interstate76
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import java.security.*;
import java.util.*;
public class I76_TerrainStorageAudit_20261103 extends GhidraScript {
 static final String SHA="bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3";
 static final String[][] GUARDS={
  {"00421400","[[00421400, 004216d6]]","8e810fb092f98aa967a8bfc8fb474b67e9e2f6c29b55efc2ac53edbfcba40ce2"},
  {"004217e0","[[004217e0, 004218f9]]","56b11639582d9607d1abfb671e3acbbdb30dfa6729eebd543e2f43baee871ae9"},
  {"00422540","[[00422540, 004226db]]","9aede4046294a15feb0d9afd544f51a34bb1c0b7d4c91cc558523be9f91be55a"},
  {"00425130","[[00425130, 00425c03]]","f92cfdcc9a3d34eeab9a9f79373938870b0a4ba5176bff6079e75fc3de314a93"},
  {"00425e60","[[00425e60, 00425ee9]]","82a8a9fd0d170ba9fa4e4ce029c64bcfb688c1228ffaa4cdec021349cfc451e0"},
  {"00425ef0","[[00425ef0, 00426042]]","137c4b3c5b9af3b20c2b812813364cf7f28259a5058c83f8691353c2d2c21031"},
  {"00440740","[[00440740, 00440d8e]]","f38c02a94d6a85e669c2a59fe967a048dd7b350c017cb20394f55c8d2a8c0e7f"},
  {"0045ef70","[[0045ef70, 0045f0bd]]","b87522b529960811de327c210414825d397f33308e15a84f494ce31de781a67d"},
  {"0045f0f0","[[0045f0f0, 0045f254]]","6f03da306974b65a2a6dbbd400556dfff09e316aeefb11802684238e0e1a2dea"},
  {"00490a00","[[00490a00, 00490fa9]]","7eafa1a3103d0e6ecc30234587b513e2e57e744b5e6db242e72982d475a05e73"},
  {"00490fb0","[[00490fb0, 004911d2]]","5549d8a0f6a1977c5c46f3a70ee0eb8a9c598aac2f3d5870fe84214e3e3e2612"},
  {"004911e0","[[004911e0, 00491808]]","7905a99c982dc54454f5ff3e8b6d1667741fed0775410c874e49203baf30d361"},
  {"004926f0","[[004926f0, 0049276f]]","67424c359eb3f47e37c40be0cfbbdf9f8121d24e3901743ccc14b3171217269a"},
  {"004927b0","[[004927b0, 0049288f]]","1091c440f47c4cda959fb3aea82892a61757c20a1da51f95c4f9e8bfdfb24d74"},
  {"004929b0","[[004929b0, 00493079]]","6f31dd9645702010d958a7b5e61486305419b70f2db29b97a19eb0fb81131a17"},
  {"00493080","[[00493080, 0049314c]]","e502bc5d513534d65743a441a6d145cbffe40b3f8dca15e923c5f56cc362bfd1"},
  {"00493160","[[00493160, 004931b2]]","5fbed866b12508c94bf62e0923318d4a833da3c1208b4b4242b70a4e9daf7c64"},
  {"004931c0","[[004931c0, 00493542]]","c5c418c9f40a521f8b7f16068063b0f765695db60c3732fc16c48bd77e799b0c"},
  {"00493550","[[00493550, 004937b2]]","dd3171475a30de903df9b35f8e486fd5f6b393add7d27a67d88a41f0ff763613"},
  {"004937c0","[[004937c0, 00493908]]","094bf497e3f57ecfc175e78b07c04c48e2d4149024e80d5dc4b8d61a1ec9bb64"},
  {"00493bd0","[[00493bd0, 00493be7]]","5ed8a32b9314385b1a2698eb9a041d2cc0cfac0282229f4a2b3d9d905b25a8f9"},
  {"004a2070","[[004a2070, 004a2431]]","07c565de62166107804f454605d1ac28dbe9b7f13a3895776eebdf92dd31a41c"},
  {"004a7800","[[004a7800, 004a7ba6]]","d79da4155f47a086e92251d744229b07edd5404627b0f5d3c867eb12dec4551a"},
  {"004a8690","[[004a8690, 004a8921]]","82d94f17599d44604fedba25dac6648a8142c6a21dab09f6226f1693653d1f3b"},
  {"004aa0f0","[[004aa0f0, 004aa146]]","9d79188666acd890735500f85290914aff41b57a9ed9e5123153fb2d7330185f"},
  {"004aa9f0","[[004aa9f0, 004ab1b9]]","248dadd5a926225d13f2ca18bec038ec68d5722bb24a5b1d73310ed6d3a8502d"},
  {"004ab1c0","[[004ab1c0, 004ab915]]","72a8eb6483419eaf10949fe5a59e5168ed28b498ea4785e029ebe736abe1838e"},
  {"004b8a10","[[004b8a10, 004b8c37]]","3819088f857ee2f45b1d73735e18129131902f797c0878dd5ddb488ea8360a64"},
 };
 protected void checkpoint() throws Exception {} // Empty; tests may override only in disposable projects.
 String digest(Function f)throws Exception{var md=MessageDigest.getInstance("SHA-256");var it=f.getBody().getAddressRanges();while(it.hasNext()){var r=it.next();byte[] b=new byte[(int)r.getLength()];currentProgram.getMemory().getBytes(r.getMinAddress(),b);md.update(b);}return HexFormat.of().formatHex(md.digest());}
 void identity()throws Exception{
  if(!SHA.equals(currentProgram.getExecutableSHA256())||!"a640ea0097dbb62e0c77b7f2847c7161".equals(currentProgram.getExecutableMD5())||!"x86:LE:32:default".equals(currentProgram.getLanguageID().toString())||currentProgram.getDefaultPointerSize()!=4||currentProgram.getImageBase().getOffset()!=0x400000||!"12.1.4".equals(ghidra.framework.Application.getApplicationVersion()))throw new Exception("CONFLICT program identity/toolchain; no changes");
  for(var g:GUARDS){var f=getFunctionAt(toAddr(g[0]));if(f==null||!g[1].equals(f.getBody().toString())||!g[2].equals(digest(f)))throw new Exception("CONFLICT original function guard "+g[0]+"; no changes");}
  if(getInt(toAddr(0x4ed7ec))!=0x00647561)throw new Exception("CONFLICT original aud literal bytes");
 }
 String allFunctions()throws Exception{StringBuilder b=new StringBuilder();var it=currentProgram.getFunctionManager().getFunctions(true);while(it.hasNext()){var f=it.next();b.append(f.getEntryPoint()).append('|').append(f.getBody()).append('|').append(digest(f)).append('|').append(f.getPrototypeString(false,false)).append('|').append(f.getReturn().getVariableStorage());for(var p:f.getParameters())b.append('|').append(p.getName()).append(':').append(p.getDataType().getPathName()).append(':').append(p.getVariableStorage()).append(':').append(p.getSource());b.append('\n');}return b.toString();}
 Map<String,String> annotations(){Map<String,String> m=new TreeMap<>();var it=currentProgram.getSymbolTable().getAllSymbols(true);while(it.hasNext()){var s=it.next();if(s.getSource()==SourceType.USER_DEFINED)m.put("symbol:"+s.getID(),s.getAddress()+"|"+s.getName(true)+"|"+s.getSymbolType());}for(int k=0;k<=4;k++){var ci=currentProgram.getListing().getCommentAddressIterator(k,currentProgram.getMemory(),true);while(ci.hasNext()){var a=ci.next();m.put("comment:"+a+":"+k,currentProgram.getListing().getComment(k,a));}}return m;}
 void footprint(long va)throws Exception{var a=toAddr(va);var d=getDataAt(a);if(d==null||d.getLength()!=4||!d.getMaxAddress().equals(a.add(3)))throw new Exception("Unrecognized four-byte definition "+a);for(int j=0;j<4;j++){if(getInstructionContaining(a.add(j))!=null)throw new Exception("Instruction overlap "+a);if(j>0)for(var s:currentProgram.getSymbolTable().getSymbols(a.add(j)))if(s.getSource()!=SourceType.DEFAULT)throw new Exception("Interior analyst symbol "+s.getAddress());}}
 boolean spacing()throws Exception{footprint(0x6442c0);var a=toAddr(0x6442c0);var s=currentProgram.getSymbolTable().getPrimarySymbol(a);if(s==null||!s.getName().equals("g_TER_GridStep")||s.getSource()!=SourceType.USER_DEFINED)throw new Exception("Spacing alias differs; preserve");var t=getDataAt(a).getDataType();if(t.isEquivalent(FloatDataType.dataType)){println("ALREADY 006442C0 float");return false;}if(!t.getPathName().equals("/int"))throw new Exception("Spacing type differs; preserve "+t.getPathName());println("PROPOSE 006442C0 int -> float: setup copies float bits; FMUL/FDIV float and matrix float copies");return true;}
 boolean literal()throws Exception{footprint(0x4ed7ec);var a=toAddr(0x4ed7ec);var t=getDataAt(a).getDataType();if(t.isEquivalent(TerminatedStringDataType.dataType)){println("ALREADY 004ED7EC terminated aud string");return false;}if(!t.getPathName().equals("/pointer"))throw new Exception("Literal type differs; preserve "+t.getPathName());for(var s:currentProgram.getSymbolTable().getSymbols(a))if(s.getSource()!=SourceType.DEFAULT&&s.getSource()!=SourceType.ANALYSIS)throw new Exception("Analyst literal label; preserve");println("PROPOSE 004ED7EC pointer -> terminated string: aud plus NUL; generated grid relationship is numeric coincidence");return true;}
 public void run()throws Exception{
  String[] args=getScriptArgs();String mode=args.length==0?askChoice("Terrain storage correction","Preview or apply on a backed-up program?",List.of("PREVIEW","APPLY"),"PREVIEW"):args.length==1?args[0]:"INVALID";
  if(!mode.equals("PREVIEW")&&!mode.equals("APPLY"))throw new Exception("Use PREVIEW or APPLY only");identity();
  boolean sp=false,lit=false;int conflicts=0;try{sp=spacing();}catch(Exception e){println("CONFLICT 006442C0 "+e.getMessage());conflicts++;}try{lit=literal();}catch(Exception e){println("CONFLICT 004ED7EC "+e.getMessage());conflicts++;}
  if(conflicts>0)throw new Exception("Preflight conflicts="+conflicts+"; entire application preserved");
  if(mode.equals("PREVIEW")){println("SUMMARY PREVIEW eligible="+((sp?1:0)+(lit?1:0))+"; no edits");return;}
  String functions=allFunctions();var old=annotations();int tx=currentProgram.startTransaction("Verified terrain float spacing and aud literal");boolean commit=false;
  try{if(sp){clearListing(toAddr(0x6442c0),toAddr(0x6442c3));createData(toAddr(0x6442c0),FloatDataType.dataType);println("APPLY 006442C0 float");}checkpoint();if(lit){clearListing(toAddr(0x4ed7ec),toAddr(0x4ed7ef));currentProgram.getListing().createData(toAddr(0x4ed7ec),TerminatedStringDataType.dataType,4);println("APPLY 004ED7EC string");}
   if(!functions.equals(allFunctions())||!old.equals(annotations()))throw new Exception("Function/analyst annotation invariance failed");identity();commit=true;
  }finally{currentProgram.endTransaction(tx,commit);println("SUMMARY APPLY changed="+(commit?((sp?1:0)+(lit?1:0)):0)+" committed="+commit);}
 }
}
