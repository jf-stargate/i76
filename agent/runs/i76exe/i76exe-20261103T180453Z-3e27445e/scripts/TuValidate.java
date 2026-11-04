// Read-only retail code comparison and pilot function-entry checks.
import ghidra.app.script.GhidraScript;
import java.nio.file.*;
import java.io.*;
public class TuValidate extends GhidraScript {
 public void run() throws Exception {
 byte[] exe=Files.readAllBytes(Paths.get(getScriptArgs()[0])); byte[] code=new byte[765525];
 currentProgram.getMemory().getBytes(toAddr(0x401000L),code);
 int mismatch=0;for(int i=0;i<code.length;i++)if(code[i]!=exe[1024+i])mismatch++;
 PrintWriter w=new PrintWriter(getScriptArgs()[1]); w.println("retail_text_bytes_checked="+code.length+" mismatches="+mismatch);
 long[][] ranges={{0x4927b0,0x493bd0},{0x410490,0x4149f0},{0x46fee0,0x470b20},{0x4b2e00,0x4b3030}};
 int n=0; for(long[] r:ranges){var fs=currentProgram.getFunctionManager().getFunctions(toAddr(r[0]),true);while(fs.hasNext()){var f=fs.next();if(f.getEntryPoint().getOffset()>r[1])break;n++;if(currentProgram.getFunctionManager().getFunctionAt(f.getEntryPoint())!=f)throw new Exception("entry mismatch");}}
 w.println("bounded_function_entries="+n);w.close();
 }
}
