// I76_SemanticTypes_v100.java
// @category Interstate76
// Ghidra 12.1.4: verified v99 -> v100, C-source-oriented type propagation.
// Source: jf-stargate/i76 accepted main through 71da0efa1ec4c92fa939f499683611a1ae647406; original opcode evidence #58/#62/#66-#84.
// This is not original recovered source. Preview by default. Work on a COPY of the Ghidra program.

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.data.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.*;
import java.util.*;

public class I76_SemanticTypes_v100 extends GhidraScript {
    private static final boolean APPLY = false; // change to true after reviewing dry-run and backing up
    private static final boolean INSTALL_CLASS1_DESCRIPTOR = true;
    private static final String MD5 = "a640ea0097dbb62e0c77b7f2847c7161";
    private static final String SHA256 = "bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3";
    private static final CategoryPath V99 = new CategoryPath("/Interstate76/Research-v99");
    private static final CategoryPath V100 = new CategoryPath("/Interstate76/Research-v100");
    private int changed=0, already=0, skipped=0, errors=0;
    private final ArrayList<String> failures=new ArrayList<>();

    private static class ParamRule {
        final String va; final int ordinal; final String name; final String oldType; final String structName; final String evidence;
        ParamRule(String a,int n,String s,String from,String target,String ev) {
            va=a;ordinal=n;name=s;oldType=from;structName=target;evidence=ev;
        }
    }
    // Require exact v99 name and one of its observed Ghidra types; refuse unrecognized analyst edits.
    private static final ParamRule[] PARAMS={
        new ParamRule("00490A00",0,"camera_view","int","I76_CameraView_0x1D8","#69/#76/#78 original camera pointer to M06 adaptive builder"),
        new ParamRule("004929B0",0,"camera_view","int","I76_CameraView_0x1D8","#76/#78 original camera pointer to terrain visible bounds"),
        new ParamRule("00457FF0",0,"camera_view","int *","I76_CameraView_0x1D8","#66/#70 original visibility producer receives retained camera"),
        new ParamRule("0048FAC0",0,"camera_view","float *","I76_CameraView_0x1D8","#70/#80 typed original bucket queue consumer camera"),
        new ParamRule("00472C10",0,"camera_view","int","I76_CameraView_0x1D8","#67/#76 original frustum classification view"),
        new ParamRule("0047CB00",0,"draw_command","byte *","I76_SoftwareDrawCommand_0x60","#75/#77/#79 original indexed software span callback first argument"),
        new ParamRule("0047CB00",1,"surface_descriptor","int *","I76_SoftwareSurface_0x34","#77/#81 original span callback second argument"),
        new ParamRule("00474C60",0,"surface_descriptor","int *","I76_SoftwareSurface_0x34","#77/#79 13-DWORD output surface descriptor")
    };

    private void proposal(String type,String id,String details){
        changed++;println("V100 CHANGE " + type + "\t"+id+"\t"+details);
    }
    private void done(String id){already++;println("V100 ALREADY\t"+id);}
    private void keep(String id,String reason){skipped++;println("V100 PRESERVE\t"+id+"\t"+reason);}
    private void fail(String id, Exception e){errors++;failures.add(id+": "+e);println("V100 ERROR\t"+id+"\t"+e);}

    private void identity(){
        boolean ok=MD5.equalsIgnoreCase(currentProgram.getExecutableMD5()) &&
            SHA256.equalsIgnoreCase(currentProgram.getExecutableSHA256()) &&
            "00400000".equalsIgnoreCase(currentProgram.getImageBase().toString()) &&
            currentProgram.getLanguage().getLanguageID().toString().startsWith("x86:LE:32");
        if(!ok)throw new IllegalStateException("Unexpected image; refusing v100 modifications");
        println("V100 VERIFIED retail i76.exe MD5/SHA256/32-bit/image-base");
    }

    private DataType known(String name){return currentProgram.getDataTypeManager().getDataType(V99,name);}
    private DataType pointerTo(DataType dt){return new PointerDataType(dt,currentProgram.getDataTypeManager());}
    private void typeParams(){
        for(ParamRule r:PARAMS){
            String key=r.va+" parameter["+r.ordinal+"] "+r.name;
            try {
                Function f=getFunctionAt(toAddr(r.va));
                if(f==null){keep(key,"no function at entry");continue;}
                Parameter[] p=f.getParameters();
                if(r.ordinal>=p.length){keep(key,"missing argument; preserve ABI");continue;}
                Parameter arg=p[r.ordinal];
                DataType target=known(r.structName);
                if(!(target instanceof Structure)){keep(key,"required verified v99 type missing; apply v99 first");continue;}
                DataType want=pointerTo(target);
                if(arg.getDataType().isEquivalent(want)){done(key);continue;}
                if(!r.name.equals(arg.getName())||!r.oldType.equals(arg.getDataType().getName())){
                    keep(key,"existing name/type conflict: "+arg.getName()+"/"+arg.getDataType().getName());continue;
                }
                if(APPLY)arg.setDataType(want,SourceType.USER_DEFINED);
                proposal("PARAM",key,r.oldType+" -> "+r.structName+"*; "+r.evidence);
            }catch(Exception e){fail(key,e);}
        }
    }

    private void leafReturn(){
        String key="00491810 return I76_TerrainAdaptiveLeaf_0x1C *";
        try {
            Function f=getFunctionAt(toAddr("00491810"));
            if(f==null){keep(key,"missing function");return;}
            DataType s=known("I76_TerrainAdaptiveLeaf_0x1C");
            if(s==null){keep(key,"missing v99 leaf structure");return;}
            DataType want=pointerTo(s);
            if(f.getReturnType().isEquivalent(want)){done(key);return;}
            if(!"short *".equals(f.getReturnType().getName())){keep(key,"current return type not verified v99 short*: "+f.getReturnType().getName());return;}
            if(APPLY)f.setReturnType(want,SourceType.USER_DEFINED);
            proposal("RETURN",key,"short* -> typed leaf*; #69/#78 original 0x1C linked leaf allocation");
        }catch(Exception e){fail(key,e);}
    }

    private DataType callbackType(DataType root){
        FunctionDefinitionDataType cb=new FunctionDefinitionDataType(V100,"I76_Class1Callback");
        cb.setReturnType(VoidDataType.dataType);
        cb.setArguments(new ParameterDefinition[]{
            new ParameterDefinitionImpl("vehicle_root",PointerDataType.dataType,"opaque original class-1 callback receiver; full runtime object layout not yet established")
        });
        cb.setComment("Callable class-1 descriptor slot at +0x08/+0x0c/+0x10; original 00463120/00463800/00463950; receiver is opaque because v99 world-root prefix is incomplete; no C++ vtable claim.");
        return cb;
    }

    private void defineCallbacksAndDescriptor(){
        String key="Class1 callback and descriptor typed declaration";
        try {
            DataType root=known("I76_WorldObjectPosePrefix_0x58");
            if(root==null){keep(key,"missing v99 root type");return;}
            DataTypeManager dtm=currentProgram.getDataTypeManager();
            DataType cbExisting=dtm.getDataType(V100,"I76_Class1Callback");
            DataType cb=cbExisting;
            if(cb==null){
                if(APPLY)cb=dtm.addDataType(callbackType(root),DataTypeConflictHandler.DEFAULT_HANDLER);
                proposal("CALLBACK_TYPE",V100+"/I76_Class1Callback","void callback(void *); return unused in observed dispatch; #58/#62");
            }else done("I76_Class1Callback");
            DataType stExisting=dtm.getDataType(V100,"I76_Class1Descriptor_0x34");
            if(stExisting==null){
                StructureDataType desc=new StructureDataType(V100,"I76_Class1Descriptor_0x34",0x34);
                desc.setDescription("Class-1 0x34-byte descriptor. Untyped/unknown members preserved. #58/#62; not a C++ vtable.");
                // Build candidate in preview using unsaved callback type; install with registered callback when applying.
                DataType entry=pointerTo(cb==null?callbackType(root):cb);
                desc.replaceAtOffset(0x08,entry,4,"initialize","004F7784 points to 00463120");
                desc.replaceAtOffset(0x0c,entry,4,"pre_update","004F7788 points to 00463800");
                desc.replaceAtOffset(0x10,entry,4,"post_update","004F778C points to 00463950; NOT 004639A0");
                if(APPLY)dtm.addDataType(desc,DataTypeConflictHandler.DEFAULT_HANDLER);
                proposal("DESCRIPTOR_TYPE",V100+"/I76_Class1Descriptor_0x34","0x34 stride, typed +8/+c/+10 callbacks; #58/#62");
            }else if(stExisting instanceof Structure && stExisting.getLength()==0x34)done("I76_Class1Descriptor_0x34");
            else keep(key,"existing incompatible descriptor type; preserved");
        }catch(Exception e){fail(key,e);}
    }

    private void installDescriptor(){
        if(!INSTALL_CLASS1_DESCRIPTOR)return;
        String key="004F777C class-1 callable slots +8/+c/+10";
        try {
            // The descriptor already contains typed Ghidra pointer data at several offsets.
            // Preserve that existing representation. Retype ONLY three independently confirmed callbacks.
            Address base=toAddr("004F777C");
            DataType cb=currentProgram.getDataTypeManager().getDataType(V100,"I76_Class1Callback");
            DataType want=pointerTo(cb==null?callbackType(known("I76_WorldObjectPosePrefix_0x58")):cb);
            String[] expected={"00463120","00463800","00463950"};
            for(int i=0;i<3;i++){
                int off=8+4*i;
                Address a=base.add(off);
                String id=key+" slot +"+Integer.toHexString(off);
                Data old=currentProgram.getListing().getDataAt(a);
                long addr=currentProgram.getMemory().getInt(a)&0xffffffffL;
                if(addr!=Long.parseLong(expected[i],16)){
                    keep(id,"original callback address mismatch: "+Long.toHexString(addr));continue;
                }
                if(old!=null&&old.getDataType().isEquivalent(want)){done(id);continue;}
                if(old==null||old.getLength()!=4 || !"undefined *".equals(old.getDataType().getName())){
                    keep(id,"preserve existing pointer/data type: "+(old==null?"none":old.getDataType().getName()));continue;
                }
                boolean conflict=false;
                for(int j=0;j<4;j++){
                    for(Symbol sym:currentProgram.getSymbolTable().getSymbols(a.add(j))){
                        if(sym.getSource()==SourceType.USER_DEFINED){conflict=true;break;}
                    }
                }
                if(conflict){keep(id,"analyst symbol overlaps pointer bytes");continue;}
                if(APPLY){
                    if(cb==null){keep(id,"callback type missing after creation");continue;}
                    clearListing(a,a.add(3));
                    createData(a,want);
                }
                proposal("CALLBACK_SLOT",id,expected[i]+" original class-1 callable; #58/#62");
            }
        }catch(Exception e){fail(key,e);}
    }

    public void run() throws Exception {
        identity();
        int tx=-1; boolean commit=false;
        try {
            if(APPLY)tx=currentProgram.startTransaction("I76 v100 C readability type propagation");
            // All newly created types are confined to Research-v100 and existing analyst data is protected.
            defineCallbacksAndDescriptor();
            typeParams();
            leafReturn();
            installDescriptor();
            commit=errors==0;
        }finally {if(tx>=0)currentProgram.endTransaction(tx,commit);}
        println("I76_V100_SUMMARY APPLY="+APPLY+" changed="+changed+" already="+already+
            " skipped="+skipped+" errors="+errors+" committed="+(APPLY&&commit));
        if(errors!=0)throw new IllegalStateException("v100 migration rolled back: "+failures);
    }
}
