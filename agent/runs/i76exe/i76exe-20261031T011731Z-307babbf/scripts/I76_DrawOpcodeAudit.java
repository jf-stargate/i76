import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.nio.file.*;import java.io.*;import java.util.*;
public class I76_DrawOpcodeAudit extends GhidraScript {
 public void run()throws Exception{
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("retail MD5");
  String[] args=getScriptArgs();TreeSet<Long> pcs=new TreeSet<>();
  for(int i=1;i<args.length;i++)for(String line:Files.readAllLines(Paths.get(args[i]))){String[] x=line.split("\t",4);if(x.length==4&&(x[1].equals("DRAW_INSTRUCTION")||x[1].equals("DRAW_STORE_BYTE"))){long pc=Long.parseLong(x[2],16);if(pc>=0x400000L&&pc<0x4bc000L)pcs.add(pc);}}
  for(long[] range:new long[][]{{0x47ce40L,0x47cfb4L},{0x47cb00L,0x47ce40L},{0x473620L,0x473630L},{0x4ba2f8L,0x4ba304L},{0x473640L,0x473663L}})for(long pc=range[0];pc<range[1];){Instruction in=getInstructionAt(toAddr(pc));if(in==null){pc++;continue;}pcs.add(pc);pc+=in.getLength();}
  try(PrintWriter o=new PrintWriter(args[0])){o.println("va\thex\tassembly\tannotated_function");for(long pc:pcs){Instruction in=getInstructionAt(toAddr(pc));if(in==null)throw new Exception("missing instruction "+Long.toHexString(pc));StringBuilder h=new StringBuilder();for(byte b:in.getBytes())h.append(String.format("%02x",b&255));Function f=getFunctionContaining(in.getAddress());o.println(String.format("%08X",pc)+"\t"+h+"\t"+in+"\t"+(f==null?"undefined":f.getEntryPoint()+" "+f.getName()));}}
 }
}
