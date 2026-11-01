import ghidra.app.script.GhidraScript;
import ghidra.program.model.symbol.SourceType;
import java.io.*;
import java.security.MessageDigest;
public class PilotCParameterNames extends GhidraScript {
 // Only default parameter names are eligible. No function/type/global/comment changes.
 public void run() throws Exception {
  if (!"bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3".equals(currentProgram.getExecutableSHA256())) throw new Exception("wrong retail identity");
  if(currentProgram.getDefaultPointerSize()!=4)throw new Exception("not PE32");
  boolean apply=getScriptArgs().length>1 && getScriptArgs()[1].equals("APPLY");
  String[][] rows={{"46ffc0","open_resource_file_into_memory","logical_name"},{"470070","load_resource_stream_into_loaded_cache","logical_name"},{"470340","resource_exists_in_cache_or_search_paths","logical_name"},{"470b20","load_indexed_resource_record_payload","logical_name"},{"4b2e00","resolve_virtual_filename_to_mounted_source","key16"},{"4b3030","load_registered_resource_payload","logical_name","out_size","destination","destination_capacity"}};
  // Preflight every operation before mutation, including all audited code hashes.
  try(var in=new BufferedReader(new FileReader(getScriptArgs()[0]))) {String line;while((line=in.readLine())!=null){var v=line.split("\t");if(!v[0].equals("range"))continue;byte[] b=new byte[Integer.parseInt(v[2])];currentProgram.getMemory().getBytes(toAddr(Long.parseLong(v[1],16)),b);StringBuilder hs=new StringBuilder();for(byte x:MessageDigest.getInstance("SHA-256").digest(b))hs.append(String.format("%02x",x&255));if(!hs.toString().equals(v[3]))throw new Exception("code changed: "+v[1]);}}
  for(var row:rows){var f=getFunctionAt(toAddr(Long.parseLong(row[0],16)));if(f==null||!f.getName().equals(row[1])||f.getParameterCount()!=row.length-2)throw new Exception("function guard "+row[0]);for(int i=2;i<row.length;i++){var p=f.getParameter(i-2);if(!p.getName().equals(row[i]) && !(p.getSource()==SourceType.DEFAULT && p.getName().equals("param_"+(i-1))))throw new Exception("preserving analyst parameter "+row[0]+":"+p.getName());}}
  int count=currentProgram.getFunctionManager().getFunctionCount(), changed=0,already=0;
  int tx=currentProgram.startTransaction("Pilot C default parameter names");boolean commit=false;
  try{for(var row:rows){var f=getFunctionAt(toAddr(Long.parseLong(row[0],16)));println("BEFORE "+f.getPrototypeString(false,false));for(int i=2;i<row.length;i++){var p=f.getParameter(i-2);if(p.getName().equals(row[i])){already++;continue;}changed++;if(apply)p.setName(row[i],SourceType.USER_DEFINED);}println("AFTER "+f.getPrototypeString(false,false));}if(currentProgram.getFunctionManager().getFunctionCount()!=count)throw new Exception("function count changed");commit=apply;}finally{currentProgram.endTransaction(tx,commit);}
  println("PILOT_C apply="+apply+" eligible="+changed+" already="+already+" functions="+count+" errors=0");
 }
}
