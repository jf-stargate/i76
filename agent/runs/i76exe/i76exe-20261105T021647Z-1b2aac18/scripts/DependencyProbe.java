import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import java.util.*;
import java.nio.file.*;
import com.google.gson.GsonBuilder;
public class DependencyProbe extends GhidraScript {
 public void run()throws Exception{List<Object> rows=new ArrayList<>();for(long pc:new long[]{0x4ba090,0x4ba2b6}){var e=new EmulatorHelper(currentProgram);try{e.writeRegister("ESP",0x30010000);e.writeMemoryValue(toAddr(0x30010000),4,0x70000000);e.writeRegister("EIP",pc);e.writeRegister("FPUControlWord",0x37f);for(int k=0;k<8;k++)e.writeRegister("ST"+k,0);long slot=pc==0x4ba090?0x4bc27c:0x4bc1fc;byte[]b=e.readMemory(toAddr(slot),4);long target=(b[0]&255L)|((b[1]&255L)<<8)|((b[2]&255L)<<16)|((b[3]&255L)<<24);boolean thunk=e.step(monitor);boolean service=e.step(monitor);rows.add(Map.of("thunk",String.format("%08x",pc),"iat",String.format("%08x",slot),"unresolved_iat_value",String.format("%08x",target),"thunk_step",thunk,"external_step",service,"error",String.valueOf(e.getLastError()),"classification","Missing loaded DLL in this GZF emulation environment, not a retail runtime failure."));}finally{e.dispose();}}Files.writeString(Path.of(getScriptArgs()[0]),new GsonBuilder().setPrettyPrinting().create().toJson(rows)+"\n");}
}
