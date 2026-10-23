import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
public class I76_RenderDispatchTableAudit extends GhidraScript {
 @Override public void run() throws Exception {
 String[] args=getScriptArgs();PrintWriter out=new PrintWriter(new FileWriter(args[0]));
 for(long base:new long[]{0x4faca8,0x4facc0,0x4fac98}){out.printf("TABLE %08X\n",base);for(int i=0;i<14;i++){Address a=toAddr(base+4*i);int v=currentProgram.getMemory().getInt(a);Function f=getFunctionContaining(toAddr(v&0xffffffffL));out.printf("%d: %08X target=%08X function=%s\n",i,base+i*4,v,f==null?"none":f.getName()+"@"+f.getEntryPoint());}}
 for(long pc:new long[]{0x48f2b0,0x401cc0,0x401fa0,0x472c10,0x48f750,0x457ff0,0x48fac0,0x48fe10,0x490590}){
  out.printf("\nREFERENCES TO %08X\n",pc);int n=0;for(Reference ref:getReferencesTo(toAddr(pc))){Function f=getFunctionContaining(ref.getFromAddress());out.printf("%s %s %s\n",ref.getFromAddress(),ref.getReferenceType(),f==null?"none":f.getEntryPoint()+" "+f.getName());if(++n>100)break;}
 }
 for(long pc:new long[]{0x006543a4,0x006543a8,0x006543b0,0x006543bc,0x004bdf94,0x004bdfbc,0x004bdfa0}){
  out.printf("\nGLOBAL %08X\n",pc);int n=0;for(Reference ref:getReferencesTo(toAddr(pc))){Function f=getFunctionContaining(ref.getFromAddress());out.printf("%s %s %s\n",ref.getFromAddress(),ref.getReferenceType(),f==null?"none":f.getEntryPoint()+" "+f.getName());if(++n>150)break;}
 }
 DecompInterface dec=new DecompInterface();dec.openProgram(currentProgram);
 for(long pc:new long[]{0x48f750,0x458bf0,0x49f240}){Function f=getFunctionContaining(toAddr(pc));out.printf("\nFUNC %08X actual %s\n",pc,f==null?"none":f.getEntryPoint());if(f!=null){DecompileResults r=dec.decompileFunction(f,40,monitor);if(r.decompileCompleted())out.println(r.getDecompiledFunction().getC());}}
 dec.dispose();out.close();
 }
}
