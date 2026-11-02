// Disposable-project negative tests. Each mode is a separate Ghidra script invocation.
// Verify saved rollback with ConsolidationAudit in a subsequent invocation.
//@category i76
import ghidra.program.model.data.*;
import ghidra.program.model.symbol.SourceType;
import java.nio.file.*;
import java.util.*;
public class ConsolidationSafetyProbe extends ConsolidateSemantics {
 boolean inject;
 @Override void types()throws Exception{super.types();if(inject){currentProgram.getDataTypeManager().addDataType(new StructureDataType(CAT,"RollbackSentinel",4),DataTypeConflictHandler.KEEP_HANDLER);throw new Exception("INJECTED_FAILURE");}}
 @Override public void run()throws Exception{
  String[] args=getScriptArgs();if(args.length!=5||!args[3].equals("APPLY"))throw new Exception("bundle PE private-log APPLY parameter|type|guard|pe|rollback");String mode=args[4];String[] original=Arrays.copyOf(args,4);setScriptArgs(original);Path report=Paths.get(args[2]);
  if(mode.equals("parameter")){
   int tx=currentProgram.startTransaction("Analyst parameter fixture");try{getFunctionAt(toAddr(0x46ffc0)).getParameter(0).setName("analyst_private_parameter",SourceType.USER_DEFINED);super.run();if(!getFunctionAt(toAddr(0x46ffc0)).getParameter(0).getName().equals("analyst_private_parameter")||log.stream().noneMatch(x->x.startsWith("PRESERVE\t0046ffc0:signature")))throw new Exception("Analyst annotation lost");}finally{currentProgram.endTransaction(tx,false);}
  }else if(mode.equals("type")){
   int tx=currentProgram.startTransaction("VM type conflict fixture");try{((ghidra.program.model.data.Structure)currentProgram.getDataTypeManager().getDataType(CAT,"VmNode")).growStructure(4);super.run();if(log.stream().noneMatch(x->x.startsWith("CONFLICT\ttype:VmNode"))||log.stream().noneMatch(x->x.startsWith("CONFLICT\t00414670:signature")))throw new Exception("Conflict/dependent skip absent");}finally{currentProgram.endTransaction(tx,false);}
  }else if(mode.equals("rollback")){
   if(currentProgram.getDataTypeManager().getDataType(CAT,"RollbackSentinel")!=null)throw new Exception("Dirty test baseline");inject=true;try{super.run();throw new AssertionError("Injected failure swallowed");}catch(Exception e){if(!e.getMessage().equals("INJECTED_FAILURE"))throw e;}finally{inject=false;}
  }else if(mode.equals("guard")||mode.equals("pe")){
   Path temp=Files.createTempDirectory(report.toAbsolutePath().getParent(),"negative-");
   if(mode.equals("guard")){Files.copy(Paths.get(original[0]).resolve("expected_signatures.tsv"),temp.resolve("expected_signatures.tsv"));String guards=Files.readString(Paths.get(original[0]).resolve("code_guards.tsv"));String[] lines=guards.split("\n");String[] r=lines[1].split("\t");lines[1]=r[0]+"\t"+r[1]+"\t"+"0".repeat(64);Files.writeString(temp.resolve("code_guards.tsv"),String.join("\n",lines)+"\n");setScriptArgs(new String[]{temp.toString(),original[1],original[2],"APPLY"});}
   else{Path wrong=temp.resolve("wrong-pe");Files.writeString(wrong,"not the retail PE");setScriptArgs(new String[]{original[0],wrong.toString(),original[2],"APPLY"});}
   try{super.run();throw new AssertionError("Invalid input accepted");}catch(Exception e){if(!e.getMessage().contains(mode.equals("guard")?"digest mismatch":"Wrong retail PE"))throw e;}
  }else throw new Exception("Unknown test mode");
  Files.writeString(report,"PASS "+mode+" fixture; saved rollback must be verified by separate audit\n");println("SAFETY PASS "+mode);
 }
}
