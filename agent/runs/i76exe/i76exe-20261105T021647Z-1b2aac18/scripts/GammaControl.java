import java.nio.file.*;
/* Fixed replay: same PC64 service outputs for two Ghidra CW settings.
 * Deliberately controlled replay, not a valid PC24 CRT replacement. */
public class GammaControl extends NumericProbe {
 public void run()throws Exception{String[]z=getScriptArgs();power=Files.readAllBytes(Path.of(z[0]));StringBuilder out=new StringBuilder("[");for(int cw:new int[]{0x37f,0x7f}){reset(cw);pows=0;ftols=0;replayMismatch=0;call(0x479860);byte[]b=e.readMemory(a(0x6095a0),2560);Files.write(Path.of(z[1]+"."+cw+".gamma"),b);if(cw!=0x37f)out.append(',');out.append("{\"cw\":"+cw+",\"gamma_sha256\":\""+sha(b)+"\",\"power_operand_mismatches\":"+replayMismatch+",\"pows\":"+pows+",\"ftols\":"+ftols+"}");e.dispose();}out.append("]\n");Files.writeString(Path.of(z[1]+".json"),out.toString());println(out.toString());}
}
