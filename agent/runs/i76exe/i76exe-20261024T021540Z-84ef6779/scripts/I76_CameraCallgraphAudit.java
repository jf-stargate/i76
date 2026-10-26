import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
public class I76_CameraCallgraphAudit extends GhidraScript {
 public void run()throws Exception { PrintWriter out=new PrintWriter(new FileWriter(getScriptArgs()[0])); DecompInterface de=new DecompInterface();de.openProgram(currentProgram);
 long[] addresses={0x00403e64L,0x00405970L,0x00405b90L,0x004061b0L,0x00406ab0L,0x004071a0L,0x00407680L,0x00472990L,0x0049d400L,0x004942f0L,0x0049944dL};
 for(long addr:addresses){ Function f=getFunctionContaining(toAddr(addr));out.printf("\nADDRESS %08X FUNCTION %s ENTRY %s\n",addr,f==null?"null":f.getName(),f==null?"null":f.getEntryPoint());if(f!=null){DecompileResults rr=de.decompileFunction(f,40,monitor);if(rr.decompileCompleted()){String code=rr.getDecompiledFunction().getC();if(code.length()>30000)code=code.substring(0,30000);out.println(code);}}}
 long[] globals={0x004c2908L,0x004c2724L,0x004c2730L,0x004c2918L,0x004c2954L,0x0053678cL,0x00536794L,0x0053679cL,0x005367a4L};
 for(long g:globals){out.printf("\nGLOBAL %08X\n",g);for(int off=0;off<4;off++)for(Reference r:getReferencesTo(toAddr(g+off))){Function f=getFunctionContaining(r.getFromAddress());out.printf("%s %s %s %s\n",r.getFromAddress(),r.getReferenceType(),f==null?"?":f.getName(),getInstructionAt(r.getFromAddress()));}}
 de.dispose();out.close();
 }
}
