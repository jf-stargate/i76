// @category I76.Research
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import com.google.gson.Gson;
import java.io.*;
import java.util.*;
import java.security.MessageDigest;
public class TUValidate extends GhidraScript {
 public void run() throws Exception {
  long before=currentProgram.getModificationNumber();
  long[][] spans={{0x4927b0L,0x493be7L},{0x410490L,0x414b42L},{0x46fee0L,0x470bb5L},{0x4b2e00L,0x4b32eaL}};
  List<Object> out=new ArrayList<>();
  for(long[] s:spans){byte[] b=new byte[(int)(s[1]-s[0]+1)];currentProgram.getMemory().getBytes(toAddr(s[0]),b);StringBuilder h=new StringBuilder();for(byte x:MessageDigest.getInstance("SHA-256").digest(b))h.append(String.format("%02x",x&255));Map<String,Object> m=new LinkedHashMap<>();m.put("start",toAddr(s[0]).toString());m.put("end",toAddr(s[1]).toString());m.put("sha256",h.toString());out.add(m);}
  Map<String,Object> m=new LinkedHashMap<>();m.put("envelopes",out);m.put("modification_before",before);m.put("modification_after",currentProgram.getModificationNumber());
  try(PrintWriter p=new PrintWriter(getScriptArgs()[0],"UTF-8")){p.println(new Gson().toJson(m));}println(new Gson().toJson(m));
 }
}
