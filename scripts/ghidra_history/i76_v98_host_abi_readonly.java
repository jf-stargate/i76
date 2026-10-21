// @category I76
// Research-only host ABI extraction; no program mutations.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;
public class i76_v98_host_abi_readonly extends GhidraScript {
  String clean(String s){return s==null?"":s.replace('\t',' ').replace('\r',' ').replace('\n',' ');}
  public void run() throws Exception {
    if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("Retail PE preflight failed");
    File dir=new File(getScriptArgs()[0]);dir.mkdirs();
    Function f=getFunctionAt(toAddr("00412ce0"));if(f==null||f.getBody().getNumAddresses()!=6146)throw new Exception("Dispatcher boundary mismatch");
    try(PrintWriter out=new PrintWriter(new File(dir,"v98_jump_targets.tsv"),"UTF-8")) {
      out.println("opcode\tentry\tsymbol\tbytes");Memory m=currentProgram.getMemory();
      for(int i=0;i<96;i++){Address slot=toAddr("004144e4").add(i*4L);Address addr=toAddr(Integer.toUnsignedString(m.getInt(slot),16));Instruction inst=getInstructionAt(addr);Function owner=getFunctionContaining(addr);out.printf("0x%02X\t%s\t%s\t%s%n",i,addr,owner==null?"UNDEFINED":clean(owner.getName()),inst==null?"NO_INSTRUCTION":clean(inst.toString()));}
    }
    String[] funcs={"00412ce0","00414670","0040b7d0","0040be60","0040b360","0040b8e0","0040b940","0040ab30","0040bd90","0040bdf0","0040bf50","0040bf60","0040bf90","0040c040","0040c060","0040c0e0","0049d420","0049d470","0049d740","0049d4a0","0049d5f0","0049dac0","0049dda0","0041fce0","0040b2f0","0040b8b0","0040aed0","0040afc0","0049aec0","0040ba60","0040a8a0","0040b9e0"};
    DecompInterface decomp=new DecompInterface();decomp.openProgram(currentProgram);
    int ok=0,fail=0;
    try(PrintWriter out=new PrintWriter(new File(dir,"v98_native_selected.txt"),"UTF-8")){
      for(String a:funcs){Function fn=getFunctionAt(toAddr(a));out.println("\n===== "+a+" "+(fn==null?"MISSING":fn.getName())+" =====");if(fn==null){fail++;continue;}
        DecompileResults r=decomp.decompileFunction(fn,22,monitor);
        if(r!=null&&r.decompileCompleted()&&r.getDecompiledFunction()!=null){out.println(r.getDecompiledFunction().getC());ok++;}else{out.println("FAIL "+(r==null?"null":r.getErrorMessage()));fail++;}
      }
    }
    decomp.dispose();println("V98_ABI_READONLY_OK functions="+ok+" failures="+fail+" md5="+currentProgram.getExecutableMD5());
  }
}
