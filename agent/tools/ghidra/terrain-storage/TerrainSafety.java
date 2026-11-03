// Disposable-project fixture, never run in a live database.
//@category i76
import ghidra.program.model.data.*;
import ghidra.program.model.symbol.*;
public class TerrainSafety extends I76_TerrainStorageAudit_20261103 {
 boolean inject;
 @Override protected void checkpoint()throws Exception{if(inject)throw new Exception("INJECTED_ROLLBACK");}
 void reject(String mode,String expected)throws Exception{try{super.run();throw new AssertionError("Accepted "+mode);}catch(Exception e){if(!e.getMessage().contains(expected))throw e;println("SAFETY PASS "+mode+" "+e.getMessage());}}
 @Override public void run()throws Exception{String mode=getScriptArgs()[0];setScriptArgs(new String[]{"APPLY"});
 int tx=currentProgram.startTransaction("Disposable negative fixture "+mode);try{
 if(mode.equals("type")){clearListing(toAddr(0x6442c0),toAddr(0x6442c3));createData(toAddr(0x6442c0),UnsignedIntegerDataType.dataType);reject(mode,"Preflight conflicts");}
 else if(mode.equals("label")){createLabel(toAddr(0x4ed7ec),"AnalystLiteralFixture",true,SourceType.USER_DEFINED);reject(mode,"Preflight conflicts");}
 else if(mode.equals("boundary")){clearListing(toAddr(0x6442c0),toAddr(0x6442c7));createData(toAddr(0x6442c0),DoubleDataType.dataType);reject(mode,"Preflight conflicts");}
 else if(mode.equals("guard")){clearListing(toAddr(0x493080),getInstructionAt(toAddr(0x493080)).getMaxAddress());setByte(toAddr(0x493080),(byte)0x90);reject(mode,"original function guard");}
 else if(mode.equals("identity")){currentProgram.setExecutableMD5("00000000000000000000000000000000");reject(mode,"program identity");}
 else if(mode.equals("rollback")){inject=true;reject(mode,"INJECTED_ROLLBACK");}
 else if(mode.equals("arguments")){setScriptArgs(new String[]{"yes"});reject(mode,"Use PREVIEW or APPLY");}
 else throw new Exception("Unknown mode");
 }finally{currentProgram.endTransaction(tx,false);}}
}
