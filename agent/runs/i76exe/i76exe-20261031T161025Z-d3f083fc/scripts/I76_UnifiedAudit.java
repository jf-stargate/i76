// Read-only retail section equality, original instructions, xrefs and private decompilation.
//@category i76
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;import java.nio.*;import java.nio.file.*;import java.util.*;
public class I76_UnifiedAudit extends GhidraScript{
 public void run()throws Exception{
  String[] args=getScriptArgs();byte[] pe=Files.readAllBytes(Paths.get(args[0]));ByteBuffer b=ByteBuffer.wrap(pe).order(ByteOrder.LITTLE_ENDIAN);int h=b.getInt(60),n=b.getShort(h+6)&65535,s=h+24+(b.getShort(h+20)&65535);
  try(PrintWriter o=new PrintWriter(args[1])){
   for(int j=0;j<n;j++){int p=s+j*40,size=b.getInt(p+16),rva=b.getInt(p+12),offset=b.getInt(p+20);if((b.getInt(p+36)&0x20000000)!=0){byte[] raw=Arrays.copyOfRange(pe,offset,offset+size),mapped=new byte[size];currentProgram.getMemory().getBytes(toAddr(0x400000L+rva),mapped);if(!Arrays.equals(raw,mapped))throw new Exception("retail executable section mismatch");o.println("CODE_EQUAL\t"+Integer.toHexString(rva)+"\t"+size+"\t"+java.util.HexFormat.of().formatHex(java.security.MessageDigest.getInstance("SHA-256").digest(raw)));}}
   DecompInterface di=new DecompInterface();di.openProgram(currentProgram);
   for(String va:new String[]{"00402f70","00451452","0045ebd0","004572b0","00490590","00494e20","00471fd0","00457ff0","0045cbe0","0045d530","0048f4c0","00490640","0048e190","004923f0","004937c0","00490a00","00403e64","00401c90","00401cc0","00401fa0","0048fac0","00474b00","00498940","00499ce0","00472220","00472400","00472530","00472990","00472c10","00494f70","00406ab0","00437f90","00405970","004937c0","00494e20","00491a30","004922f0","004924b0","00490590","0047bf00","0048fe10","0048f9b0","00471f00"}){
    Address a=toAddr(Long.parseLong(va,16));o.println("XREF "+va);for(Reference ref:getReferencesTo(a))o.println(ref.getFromAddress()+" "+ref.getReferenceType());Function f=getFunctionAt(a);if(f==null)f=getFunctionContaining(a);if(f==null){o.println("NO_FUNCTION_BOUNDARY "+va);InstructionIterator q=currentProgram.getListing().getInstructions(a,true);for(int k=0;k<400&&q.hasNext();k++){Instruction in=q.next();o.println(in.getAddress()+"\t"+java.util.HexFormat.of().formatHex(in.getBytes())+"\t"+in);}continue;}
    o.println("FUNCTION "+va);DecompileResults d=di.decompileFunction(f,60,monitor);o.println(d.decompileCompleted()?d.getDecompiledFunction().getC():d.getErrorMessage());
    InstructionIterator it=currentProgram.getListing().getInstructions(f.getBody(),true);while(it.hasNext()){Instruction in=it.next();o.println(in.getAddress()+"\t"+java.util.HexFormat.of().formatHex(in.getBytes())+"\t"+in);}
   }
   // Callback labels are not recovered function boundaries. Inspect bounded listing only.
   for(long[] range:new long[][]{{0x48e190L,0x48e2c0L},{0x4923f0L,0x4924b0L}}){InstructionIterator it=currentProgram.getListing().getInstructions(toAddr(range[0]),true);while(it.hasNext()){Instruction in=it.next();if(in.getAddress().getOffset()>=range[1])break;o.println(in.getAddress()+"\t"+java.util.HexFormat.of().formatHex(in.getBytes())+"\t"+in);}}
   di.dispose();
  }
 }
}
