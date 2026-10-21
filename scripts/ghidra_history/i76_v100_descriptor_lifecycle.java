// @category I76
// I76 v100: read-only descriptor lifetime and repeated-load control flow audit.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;

public class i76_v100_descriptor_lifecycle extends GhidraScript {
 private Address A(long x){return toAddr(Long.toHexString(x));}
 private void instructionWindow(PrintWriter out, Address at, int before, int after) {
  Instruction i=currentProgram.getListing().getInstructionContaining(at);
  if(i==null) {out.println("MISSING "+at);return;}
  for(int j=0;j<before && i!=null;j++)i=i.getPrevious();
  for(int j=0;j<before+after+1 && i!=null;j++,i=i.getNext())out.println(i.getAddress()+"\t"+i.toString());
 }
 public void run() throws Exception {
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("Wrong binary MD5");
  File o=new File(getScriptArgs()[0]);o.mkdirs();
  Listing l=currentProgram.getListing(); ReferenceManager rm=currentProgram.getReferenceManager(); Memory mem=currentProgram.getMemory();
  try(PrintWriter out=new PrintWriter(new File(o,"v100_descriptor_references.tsv"),"UTF-8")){
   out.println("target\tbase\toffset\tref_source\ttype\tsource_function\tsource_instruction");
   for(long[] range:new long[][]{{0x500328,0x5003b8},{0x500d20,0x500d50}}) {
    for(long p=range[0];p<range[1];p++){
     for(Reference r:rm.getReferencesTo(A(p))){
      Function f=getFunctionContaining(r.getFromAddress());Instruction i=l.getInstructionContaining(r.getFromAddress());
      out.printf("%08X\t%08X\t%d\t%s\t%s\t%s\t%s%n",p,range[0],p-range[0],r.getFromAddress(),r.getReferenceType(),f==null?"NONE":f.getEntryPoint(),i==null?"DATA":i.toString().replace('\t',' '));
     }
    }
   }
  }
  try(PrintWriter out=new PrintWriter(new File(o,"v100_descriptor_initial_values.tsv"),"UTF-8")){
   out.println("table\taddress\ttag\targ\tcallback\tinitial_flags\tseen_in_file\trequired");
   for(long[] range:new long[][]{{0x500328,0x5003b8},{0x500d20,0x500d50}}){
    for(long p=range[0];p+16<=range[1];p+=16){
     byte[] bytes=new byte[4];mem.getBytes(A(p),bytes);StringBuilder tag=new StringBuilder();for(byte b:bytes)tag.append(b>=32&&b<=126?(char)b:'_');
     int flags=mem.getInt(A(p+12));out.printf("%08X\t%08X\t%s\t%08X\t%08X\t%08X\t%d\t%d%n",range[0],p,tag,mem.getInt(A(p+4)),mem.getInt(A(p+8)),flags,(flags&0x80)==0?0:1,(flags&0x40)==0?0:1);
    }
   }
  }
  try(PrintWriter out=new PrintWriter(new File(o,"v100_parser_call_sites.txt"),"UTF-8")){
   long[] targets={0x4b3db0,0x4b42b0,0x4b41e0,0x4b89b0,0x4b84e0,0x4b4550,0x4b4610};
   for(long target:targets){out.println("\n## Incoming refs "+String.format("%08X",target));
    int n=0;
    for(Reference r:rm.getReferencesTo(A(target))){
     out.println("== REF "+r.getFromAddress()+" type "+r.getReferenceType()+" ==");
     if(r.getReferenceType().isCall()||r.getReferenceType().isJump())instructionWindow(out,r.getFromAddress(),20,7);
     else out.println("NONCALL/DATA REF");
     if(++n>=90){out.println("TRUNCATED");break;}
    }
   }
  }
  DecompInterface d=new DecompInterface();d.openProgram(currentProgram);
  try(PrintWriter out=new PrintWriter(new File(o,"v100_targeted_decompilation.txt"),"UTF-8")){
   long[] targets={0x4b3db0,0x4b42b0,0x4b41e0,0x4b89b0,0x4b84e0,0x4b4550,0x4b4610,0x4b5710,0x4b7ac0,0x4b4790,0x402b30,0x4571a0};
   for(long x:targets){Function f=getFunctionAt(A(x));out.println("\n======= "+String.format("%08X",x)+" "+(f==null?"NONE":f.getName())+" =======");if(f==null)continue;
    if(x==0x402b30){out.println("OMITTED LARGE LOOP; see callsite audit");continue;}
    DecompileResults r=d.decompileFunction(f,17,monitor);out.println(r.decompileCompleted()?r.getDecompiledFunction().getC():"FAILED "+r.getErrorMessage());
   }
  }
  d.dispose();
  try(PrintWriter out=new PrintWriter(new File(o,"v100_seen_mutation_instruction_audit.tsv"),"UTF-8")){
   out.println("address\tfunction\tinstruction\tscope");
   // Parser body exact instruction window, plus suspicious flag bit operations in all executable code.
   InstructionIterator it=l.getInstructions(true);int seen=0;int all=0;
   while(it.hasNext()){
    Instruction i=it.next(); all++;
    if(i.getAddress().getOffset()<0x400000||i.getAddress().getOffset()>0x4c1000)continue;
    String s=i.toString().toUpperCase(Locale.ROOT);
    if ((i.getAddress().getOffset()==0x4b3f2c || i.getAddress().getOffset()==0x4b3f2f || i.getAddress().getOffset()==0x4b3f31 || i.getAddress().getOffset()==0x4b4163 || i.getAddress().getOffset()==0x4b4168) || ((s.startsWith("OR ")||s.startsWith("AND ")||s.startsWith("MOV ")||s.startsWith("XOR "))
       && (s.contains("0X80")||s.contains("0XFFFFFF7F")||s.contains("0X7F")||s.contains("0XFFFFFEFF"))
       && (s.contains("+ 0XC")||s.contains("+0XC")||s.contains("0X5003")||s.contains("0X500D")))) {
     Function f=getFunctionContaining(i.getAddress());out.println(i.getAddress()+"\t"+(f==null?"NONE":f.getEntryPoint())+"\t"+s+"\tFLAG_CANDIDATE");seen++;
    }
   }
   out.println("# instructions="+all+" candidates="+seen);
  }
  println("V100_DESCRIPTOR_READONLY_OK");
 }
}
