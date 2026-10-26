import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;
public class I76_RenderProducerAudit extends GhidraScript {
  String h(Address a){return a==null?"NULL":a.toString();}
  @Override public void run()throws Exception {
    String[] a=getScriptArgs(); PrintWriter out=new PrintWriter(new FileWriter(a[0]));
    DecompInterface ifc=new DecompInterface();ifc.openProgram(currentProgram);
    long[] targets={0x457ff0,0x472c10,0x472d30,0x494be0,0x490590,0x48fe10,0x48fac0,0x48f4c0,0x45d530,0x4572b0,0x48f9b0};
    for(long pc:targets){Address ad=toAddr(pc); Function f=getFunctionAt(ad);out.println("\n################## TARGET "+h(ad)+" "+(f==null?"GLOBAL":f.getName())+" ###################");
      if(f!=null){out.println("FUNC "+f.getEntryPoint()+" to "+f.getBody().getMaxAddress()+" signature="+f.getSignature());
        DecompileResults dr=ifc.decompileFunction(f,60,monitor);out.println("DECOMP_STATUS "+dr.getErrorMessage());
        if(dr.decompileCompleted())out.println(dr.getDecompiledFunction().getC());
        InstructionIterator ii=currentProgram.getListing().getInstructions(f.getBody(),true);int c=0;
        out.println("ASM_START");while(ii.hasNext()&&c++<700){Instruction inst=ii.next();StringBuilder sb=new StringBuilder();sb.append(inst.getAddress()).append(' ').append(inst.toString());
        for(Reference r:inst.getReferencesFrom()){if(r.getReferenceType().isCall()||r.getReferenceType().isJump())sb.append(" => ").append(r.getToAddress());}
        out.println(sb);
        }out.println("ASM_END");}
      out.println("INCOMING");Reference[] refs=getReferencesTo(ad);int n=0;for(Reference ref:refs){if(n++>=250)break;Function caller=getFunctionContaining(ref.getFromAddress());out.println(ref.getFromAddress()+" "+ref.getReferenceType()+" "+(caller==null?"no_func":caller.getName()+"@"+caller.getEntryPoint()));}
      out.println("INCOMING_COUNT_SHOWN="+n);
    }
    ifc.dispose();out.close();
  }
}
