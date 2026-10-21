// @category I76
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import java.util.*;
import java.io.*;
public class i76_v98_host_deep_helpers_readonly extends GhidraScript {
 public void run() throws Exception {
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("MD5");
  File dir=new File(getScriptArgs()[0]);dir.mkdirs();DecompInterface dec=new DecompInterface();dec.openProgram(currentProgram);
  String[] names={"append_salvage_resource_reference_for_mission","play_or_stop_vehicle_engine_event_sound","set_vehicle_current_damage_or_effect_object","keyboard_joystick_input_binding_context_helper_0044eca0"};
  int count=0; try(PrintWriter out=new PrintWriter(new File(dir,"v98_secondary_callees_native.txt"),"UTF-8")){
   FunctionIterator it=currentProgram.getFunctionManager().getFunctions(true);
   while(it.hasNext()){Function f=it.next();for(String n:names){if(!f.getName().equals(n))continue;
    count++;out.println("===== "+f.getEntryPoint()+" "+f.getName()+" len="+f.getBody().getNumAddresses()+" =====");
    DecompileResults r=dec.decompileFunction(f,25,monitor);out.println(r!=null&&r.decompileCompleted()?r.getDecompiledFunction().getC():"DECOMPILE FAILED");
   }}
  }dec.dispose();println("V98_SECONDARY_HELPERS "+count);
 }
}
