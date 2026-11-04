// @category I76
// Compare selected Ghidra instruction bytes with authenticated executable, read-only.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.file.*;
import java.security.*;
public class WrldVerify extends GhidraScript {
 private int u16(byte[] b,int p){return (b[p]&255)|((b[p+1]&255)<<8);}
 private int u32(byte[] b,int p){return u16(b,p)|(u16(b,p+2)<<16);}
 public void run() throws Exception {
  String[] args=getScriptArgs();byte[] b=Files.readAllBytes(Path.of(args[0]));StringBuilder hash=new StringBuilder();for(byte v:MessageDigest.getInstance("SHA-256").digest(b))hash.append(String.format("%02x",v&255));
  if(!hash.toString().equals("bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3"))throw new Exception("executable hash mismatch");
  int pe=u32(b,60), count=u16(b,pe+6), table=pe+24+u16(b,pe+20),total=0,mismatches=0;
  try(PrintWriter out=new PrintWriter(args[1])){
   out.println("function\tinstruction_count\tcompared_bytes\tmismatches");
   for(int n=2;n<args.length;n++){
    Function f=getFunctionContaining(toAddr(args[n]));if(f==null)throw new Exception("missing function "+args[n]);int inscount=0,compared=0,bad=0;
    InstructionIterator it=currentProgram.getListing().getInstructions(f.getBody(),true);
    while(it.hasNext()){
     Instruction ins=it.next();byte[] bytes=ins.getBytes();long rva=ins.getAddress().getOffset()-0x400000;int raw=-1;
     for(int s=0;s<count;s++){int p=table+40*s;long va=Integer.toUnsignedLong(u32(b,p+12)),size=Integer.toUnsignedLong(u32(b,p+16));if(rva>=va&&rva+bytes.length<=va+size)raw=(int)(rva-va+Integer.toUnsignedLong(u32(b,p+20)));}
     if(raw<0)throw new Exception("unmapped instruction "+ins.getAddress());
     for(int k=0;k<bytes.length;k++){if(bytes[k]!=b[raw+k])bad++;compared++;}inscount++;
    }
    out.println(f.getEntryPoint()+"\t"+inscount+"\t"+compared+"\t"+bad);total+=compared;mismatches+=bad;
   }
   out.println("# compared_bytes="+total+" mismatches="+mismatches);
  }
  if(mismatches!=0)throw new Exception("Ghidra instruction bytes differ from retail");println("WRLD_RETAIL_BYTES_MATCH "+total);
 }
}
