// Disposable-project-only negative fixtures. Never install in a live database.
//@category Interstate76
import ghidra.program.model.data.*;
import ghidra.program.model.symbol.*;
public class RestorationSafety extends I76_Reconcile_v100_v102_20261103 {
 boolean inject;
 @Override protected void checkpoint()throws Exception{if(inject)throw new Exception("INJECTED_ROLLBACK");}
 void rejected(String mode,String phase,String expected)throws Exception{
  setScriptArgs(new String[]{"APPLY",phase});try{super.run();throw new AssertionError("Fixture accepted "+mode);}catch(Exception e){String all=e.toString();for(Throwable t=e.getCause();t!=null;t=t.getCause())all+=" "+t;if(!all.contains(expected))throw e;println("NEGATIVE PASS "+mode+" "+expected);}
 }
 @Override public void run()throws Exception{
 String mode=getScriptArgs()[0];if(mode.equals("rollback")){inject=true;rejected(mode,"ALL","INJECTED_ROLLBACK");return;}int tx=currentProgram.startTransaction("Disposable negative fixture "+mode);
 try{
  if(mode.equals("type")){var s=new StructureDataType(new CategoryPath("/Interstate76/Research-v100"),"I76_Class1Descriptor_0x34",0x34);s.replaceAtOffset(8,IntegerDataType.dataType,4,"analyst_field",null);currentProgram.getDataTypeManager().addDataType(s,DataTypeConflictHandler.REPLACE_HANDLER);rejected(mode,"V100","incompatible descriptor");}
  else if(mode.equals("prerequisite")){var s=(Structure)currentProgram.getDataTypeManager().getDataType("/Interstate76/Research-v99/I76_CameraView_0x1D8");s.replaceAtOffset(0x2c,IntegerDataType.dataType,4,"analyst_field",null);rejected(mode,"V100","baseline fields differ");}
  else if(mode.equals("bytes")){var a=toAddr(0x490a00);clearListing(a,getInstructionAt(a).getMaxAddress());setByte(a,(byte)0x90);rejected(mode,"ALL","original byte mismatch");}
  else if(mode.equals("boundary")){var f=getFunctionAt(toAddr(0x49c320));var body=new ghidra.program.model.address.AddressSet(f.getBody());body.delete(toAddr(0x49c357),toAddr(0x49c357));f.setBody(body);rejected(mode,"ALL","function boundary");}
  else if(mode.equals("identity")){currentProgram.setExecutableMD5("00000000000000000000000000000000");rejected(mode,"ALL","retail image mismatch");}
  else if(mode.equals("tablebytes")){setInt(toAddr(0x4f7784),0x463121);rejected(mode,"ALL","original 27 rows differ");}
  else if(mode.equals("overlap")){clearListing(toAddr(0x4f76e0),toAddr(0x4f76e7));createData(toAddr(0x4f76e0),DoubleDataType.dataType);rejected(mode,"ALL","non-scalar original data");}
  else if(mode.equals("signature")){getFunctionAt(toAddr(0x490a00)).getParameter(0).setDataType(DoubleDataType.dataType,SourceType.USER_DEFINED);rejected(mode,"V100","parameter");}
  else if(mode.equals("label")){createLabel(toAddr(0x4f7785),"AnalystInteriorFixture",true,SourceType.USER_DEFINED);rejected(mode,"ALL","analyst");}
  else if(mode.equals("rollback")){inject=true;rejected(mode,"ALL","INJECTED_ROLLBACK");}
  else throw new Exception("Unknown fixture");
 }finally{currentProgram.endTransaction(tx,false);}
 }
}
