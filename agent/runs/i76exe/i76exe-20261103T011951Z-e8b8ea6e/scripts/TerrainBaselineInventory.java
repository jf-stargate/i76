// Private-only captures; run with output directory.
//@category i76
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.data.*;
import ghidra.program.model.address.*;
import java.nio.file.*;
import java.util.*;
public class TerrainBaselineInventory extends GhidraScript {
 String clean(Object o){return String.valueOf(o).replace('\t',' ').replace('\n',' ').replace('\r',' ');}
 public void run()throws Exception{
 Path out=Paths.get(getScriptArgs()[0]);Files.createDirectories(out);
 StringBuilder data=new StringBuilder("address\tlength\ttype\tvalue\n");var ds=currentProgram.getListing().getDefinedData(true);while(ds.hasNext()){var d=ds.next();data.append(d.getAddress()+"\t"+d.getLength()+"\t"+d.getDataType().getPathName()+"\t"+clean(d.getDefaultValueRepresentation())+"\n");}Files.writeString(out.resolve("data.tsv"),data);
 StringBuilder comps=new StringBuilder("type\tlength\toffset\tfield\tcomponent_type\tcomment\n");var ts=currentProgram.getDataTypeManager().getAllDataTypes();while(ts.hasNext()){var t=ts.next();if(t instanceof Structure s)for(var c:s.getDefinedComponents())comps.append(s.getPathName()+"\t"+s.getLength()+"\t"+c.getOffset()+"\t"+clean(c.getFieldName())+"\t"+c.getDataType().getPathName()+"\t"+clean(c.getComment())+"\n");}Files.writeString(out.resolve("components.tsv"),comps);
 StringBuilder ex=new StringBuilder();var es=currentProgram.getFunctionManager().getExternalFunctions();while(es.hasNext()){var f=es.next();ex.append(f.getEntryPoint()+"\t"+ConsolidationAudit.signature(f)+"\n");}Files.writeString(out.resolve("external_functions.tsv"),ex);
 TreeSet<Address> selected=new TreeSet<>();for(long a:new long[]{0x493080,0x493160,0x4931c0,0x493550,0x4927b0,0x425130,0x425ef0,0x440740,0x493bd0,0x45f0f0,0x0045ef70})selected.add(toAddr(a));
 StringBuilder refs=new StringBuilder("target\tfrom\tkind\tinstruction\tpcode\n");
 for(long va:new long[]{0x6442c0,0x6442c4,0x644380,0x4ed7ec}){var ri=currentProgram.getReferenceManager().getReferencesTo(toAddr(va));while(ri.hasNext()){var r=ri.next();var i=getInstructionAt(r.getFromAddress());refs.append(toAddr(va)+"\t"+r.getFromAddress()+"\t"+r.getReferenceType()+"\t"+clean(i)+"\t"+(i==null?"":clean(Arrays.toString(i.getPcode())))+"\n");var f=getFunctionContaining(r.getFromAddress());if(f!=null)selected.add(f.getEntryPoint());}}
 Files.writeString(out.resolve("terrain_refs.tsv"),refs);
 StringBuilder ins=new StringBuilder("function\taddress\tbytes\tinstruction\tpcode\n");DecompInterface dc=new DecompInterface();dc.openProgram(currentProgram);
 for(var a:selected){var f=getFunctionAt(a);var it=currentProgram.getListing().getInstructions(f.getBody(),true);while(it.hasNext()){var i=it.next();ins.append(a+"\t"+i.getAddress()+"\t"+HexFormat.of().formatHex(i.getBytes())+"\t"+i+"\t"+clean(Arrays.toString(i.getPcode()))+"\n");}var d=dc.decompileFunction(f,120,monitor);if(!d.decompileCompleted())throw new Exception(d.getErrorMessage());Files.writeString(out.resolve(a+".c"),d.getDecompiledFunction().getC());}dc.dispose();Files.writeString(out.resolve("terrain_instructions.tsv"),ins);
 println("TERRAIN_INVENTORY selected="+selected.size());
 }
}
