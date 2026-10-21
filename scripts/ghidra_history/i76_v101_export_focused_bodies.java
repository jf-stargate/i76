//@category I76
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import java.io.*;

public class i76_v101_export_focused_bodies extends GhidraScript {
    private static final String MD5="a640ea0097dbb62e0c77b7f2847c7161";
    private static final long[] TARGETS={
        0x00402620L,0x00402B30L,0x00409740L,0x00409850L,0x00409980L,
        0x0040A320L,0x0040AEB0L,0x0040AEC0L,0x0040B320L,0x0040BDF0L,
        0x00410490L,0x00410720L,0x00410A10L,0x00412400L,0x00412500L,
        0x004125C0L,0x00412830L,0x00412CE0L,0x00414670L,0x004149F0L,
        0x00414BC0L,0x00415020L,0x004157A0L,0x0041F8E0L,0x0041F9C0L,
        0x0041FC40L,0x0041FCE0L,0x00420A20L,0x00420AA0L,0x00421730L,
        0x00423620L,0x004238E0L,0x00423A10L,0x0042D5D0L,0x00457100L,
        0x004571A0L,0x00457420L,0x00457610L,0x00457630L,0x0045E960L,
        0x0045E9E0L,0x0045EA90L,0x004AD410L,0x004AD450L,0x004AD5B0L,
        0x004AD600L,0x004B3DB0L,0x004B41E0L,0x004B42B0L,0x004B45F0L,
        0x004B4610L,0x004B7AC0L,0x004B84E0L,0x004B8960L,0x004B89B0L
    };
    private String clean(String s){ return s==null?"":s.replace('\t',' ').replace('\n',' ').replace('\r',' '); }
    @Override public void run() throws Exception {
        if(!MD5.equalsIgnoreCase(currentProgram.getExecutableMD5())) throw new IllegalStateException("retail MD5 mismatch");
        String[] args=getScriptArgs();
        if(args.length<3) throw new IllegalArgumentException("output_dir start_index count [decomp=0|1]");
        File root=new File(args[0]); int start=Integer.parseInt(args[1]);int count=Integer.parseInt(args[2]);
        boolean decomp=args.length>3 && args[3].equals("1");
        File asm=new File(root,"disassembly"); File dec=new File(root,"decompile"); asm.mkdirs();dec.mkdirs();
        DecompInterface ifc=null;
        if(decomp){ifc=new DecompInterface();ifc.openProgram(currentProgram);}
        File indexfile=new File(root,"focused_body_index.tsv");
        try(PrintWriter index=new PrintWriter(new BufferedWriter(new FileWriter(indexfile,true)))){
            for(int i=start;i<Math.min(start+count,TARGETS.length);i++){
                Address a=toAddr(TARGETS[i]);Function f=currentProgram.getFunctionManager().getFunctionAt(a);
                if(f==null){index.printf("%08X\tMISSING\t\t\t\n",TARGETS[i]);continue;}
                String basename=String.format("%08X",TARGETS[i])+"_"+f.getName().replaceAll("[^A-Za-z0-9_.-]","_");
                int inscount=0;
                try(PrintWriter pw=new PrintWriter(new BufferedWriter(new FileWriter(new File(asm,basename+".asm.tsv"))))) {
                    pw.println("address\tbytes\tmnemonic\toperands\tinstruction");
                    InstructionIterator it=currentProgram.getListing().getInstructions(f.getBody(),true);
                    while(it.hasNext()){
                        Instruction ins=it.next();StringBuilder b=new StringBuilder(),o=new StringBuilder();
                        for(byte v:ins.getBytes()) b.append(String.format("%02X",v&255));
                        for(int p=0;p<ins.getNumOperands();p++){if(p>0)o.append(", ");o.append(ins.getDefaultOperandRepresentation(p));}
                        pw.println(ins.getAddress()+"\t"+b+"\t"+clean(ins.getMnemonicString())+"\t"+clean(o.toString())+"\t"+clean(ins.toString()));
                        inscount++;
                    }
                }
                String status="not_requested";
                if(decomp){
                    try(PrintWriter pw=new PrintWriter(new BufferedWriter(new FileWriter(new File(dec,basename+".c"))))) {
                        pw.println("/* Decompiled retail i76.exe, Ghidra v97; " + a + " " + f.getName()+" */");
                        DecompileResults r=ifc.decompileFunction(f,60,monitor);
                        if(r!=null&&r.decompileCompleted()&&r.getDecompiledFunction()!=null){pw.println(r.getDecompiledFunction().getC());status="ok";}
                        else {status="failed";pw.println("/* " +clean(r==null?"null":r.getErrorMessage())+" */");}
                    } catch(Exception ex){status="error";}
                }
                index.println(String.format("%08X",TARGETS[i])+"\t"+f.getName()+"\t"+inscount+"\t"+status+"\t"+basename);
                index.flush();println("exported "+basename+" instructions="+inscount+" decomp="+status);
            }
        }
        if(ifc!=null)ifc.dispose();
    }
}
