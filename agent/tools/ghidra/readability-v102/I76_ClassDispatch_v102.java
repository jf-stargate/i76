// I76_ClassDispatch_v102.java
// @category Interstate76
// Retail Interstate '76 Ghidra 12.1.4. C-readability pass; NOT original source symbols.
// Based on verified v98 GZF with v99, v100 and v101 applied; default PREVIEW.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.util.*;
public class I76_ClassDispatch_v102 extends GhidraScript {
    private static final boolean APPLY=false;
    private static final String MD5="a640ea0097dbb62e0c77b7f2847c7161";
    private static final String SHA256="bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3";
    private static final CategoryPath CAT=new CategoryPath("/Interstate76/Research-v102");
    private static final int ROWS=27, STRIDE=0x34;
    private int changed=0,already=0,skipped=0,errors=0;
    private final List<String> failures=new ArrayList<>();
    private void change(String group,String what,String why){changed++;println("V102 CHANGE\t"+group+"\t"+what+"\t"+why);}
    private void done(String x){already++;println("V102 ALREADY\t"+x);}
    private void preserve(String x,String why){skipped++;println("V102 PRESERVE\t"+x+"\t"+why);}
    private void fail(String x,Exception e){errors++;failures.add(x+": "+e);println("V102 ERROR\t"+x+"\t"+e);}
    private void identity(){if(!MD5.equalsIgnoreCase(currentProgram.getExecutableMD5())||!SHA256.equalsIgnoreCase(currentProgram.getExecutableSHA256())||!"00400000".equalsIgnoreCase(currentProgram.getImageBase().toString())||!currentProgram.getLanguage().getLanguageID().toString().startsWith("x86:LE:32")) throw new IllegalStateException("Not the verified retail i76.exe x86/32 baseline");}
    private DataType world(){return currentProgram.getDataTypeManager().getDataType(new CategoryPath("/Interstate76/Research-v101"),"I76_WorldNode_0xB0");}
    private DataType ptr(DataType t){return new PointerDataType(t,currentProgram.getDataTypeManager());}
    private FunctionDefinitionDataType callback(String name,DataType ret,DataType[] args,String[] names,String note){
        FunctionDefinitionDataType f=new FunctionDefinitionDataType(CAT,name);
        f.setReturnType(ret);ParameterDefinition[] ps=new ParameterDefinition[args.length];
        for(int i=0;i<ps.length;i++) ps[i]=new ParameterDefinitionImpl(names[i],args[i],"original retail indirect call boundary");
        f.setArguments(ps);f.setComment(note);return f;
    }
    private final String[] fNames={"I76_ClassRuntimeFactory","I76_ClassPhaseCallback","I76_ClassDamageCallback"};
    private List<FunctionDefinitionDataType> callbackCandidates(){
        DataType w=world(); if(w==null)throw new IllegalStateException("v101 world-node datatype missing");
        List<FunctionDefinitionDataType> defs=new ArrayList<>();
        defs.add(callback(fNames[0],PointerDataType.dataType,new DataType[]{},new String[]{},"Class descriptor +04; original 00461970 calls with zero args and stores EAX at world+70. Other ownership unresolved."));
        defs.add(callback(fNames[1],VoidDataType.dataType,new DataType[]{ptr(w)},new String[]{"world_node"},"Descriptor +08/+0C/+10 init/pre/post. Original ENG 00461B80/1C80/1D50 passes world node; return unused."));
        defs.add(callback(fNames[2],UnsignedIntegerDataType.dataType,new DataType[]{ptr(w),PointerDataType.dataType,PointerDataType.dataType},new String[]{"world_node","damage_context","vector_context"},"Descriptor +28. 00462040 passes world pointer and two opaque 32-bit arguments, reads return EAX. Not proven for other callback slots."));
        return defs;
    }
    private void callbackTypes(){String[] note={"class runtime factory +04","class init/pre/post +08/+0C/+10","class damage +28"};int i=0;
        for(FunctionDefinitionDataType f:callbackCandidates()){String id=CAT+"/"+f.getName();try{DataType existing=currentProgram.getDataTypeManager().getDataType(CAT,f.getName());if(existing!=null){if(existing.isEquivalent(f))done(id);else preserve(id,"existing type conflicts; leave untouched");}else{if(APPLY)currentProgram.getDataTypeManager().addDataType(f,DataTypeConflictHandler.DEFAULT_HANDLER);change("FUNCDEF",id,note[i]);}}catch(Exception e){fail(id,e);}i++;}
    }
    private DataType cb(String name){DataType dt=currentProgram.getDataTypeManager().getDataType(CAT,name);if(dt!=null)return dt;if(!APPLY){for(FunctionDefinitionDataType f:callbackCandidates())if(f.getName().equals(name))return f;}return null;}
    private StructureDataType classDesc(){StructureDataType d=new StructureDataType(CAT,"I76_ClassDescriptor_0x34",STRIDE);
        d.setDescription("Original 27-row/52-byte world-class dispatch table. 00461970/00461B80/00461C80/00461D50/00462040. Unknown slots explicitly opaque; not a C++ vtable.");
        d.replaceAtOffset(0,UnsignedIntegerDataType.dataType,4,"class_id","Discriminator; special values normalized to class 2 in caller");
        for(int off=4;off<STRIDE;off+=4){String name=String.format("slot_%02x",off);DataType type=PointerDataType.dataType;
          if(off==4){name="runtime_factory";type=ptr(cb(fNames[0]));}
          if(off==8){name="initialize";type=ptr(cb(fNames[1]));}
          if(off==0x0c){name="pre_update";type=ptr(cb(fNames[1]));}
          if(off==0x10){name="post_update";type=ptr(cb(fNames[1]));}
          if(off==0x28){name="damage";type=ptr(cb(fNames[2]));}
          d.replaceAtOffset(off,type,4,name,(off==4||off==8||off==0xc||off==0x10||off==0x28)?"Verified original dispatcher callsite":"Opaque callback or reserved zero; no ABI inferred");
        }
        return d;
    }
    private void descriptorType(){String id=CAT+"/I76_ClassDescriptor_0x34";try{StructureDataType d=classDesc();DataType old=currentProgram.getDataTypeManager().getDataType(CAT,d.getName());if(old!=null){if(old.isEquivalent(d))done(id);else preserve(id,"existing structural definition differs");return;}if(APPLY)currentProgram.getDataTypeManager().addDataType(d,DataTypeConflictHandler.DEFAULT_HANDLER);change("STRUCT",id,"original class-table stride 0x34; indexed dispatch and distinct callback signatures");}catch(Exception e){fail(id,e);}}
    private void partialRuntimeTypes(){
        // These describe only directly accessed prefixes, NOT complete allocations.
        // Do NOT cast world_node->class_runtime globally: its layout depends on class_id.
        DataType w=world(); if(w==null){preserve("runtime prefix types","v101 world-node type missing");return;}
        List<StructureDataType> candidates=new ArrayList<>();
        StructureDataType c31=new StructureDataType(CAT,"I76_Class31RuntimeObserved_0x04",4);
        c31.setDescription("Observed class-31 runtime prefix ONLY; exact allocation size and ownership unresolved. 0046F2B0.");
        c31.replaceAtOffset(0,PointerDataType.dataType,4,"animation_context","0046F2B0 stores generated animation context at runtime+0");candidates.add(c31);
        StructureDataType c34=new StructureDataType(CAT,"I76_Class34RuntimeObserved_0x80",0x80);
        c34.setDescription("Observed class-34 runtime offsets ONLY; 0x80 is minimum accessed extent, not established allocation size. 0045F810.");
        c34.replaceAtOffset(8,PointerDataType.dataType,4,"animation_context","0045F810 runtime+8 write");
        c34.replaceAtOffset(0x78,ptr(w),4,"root_world_node","0045F810 stores get_root_ancestor_world_object return");
        c34.replaceAtOffset(0x7c,ptr(w),4,"self_world_node","0045F810 stores callback world node");candidates.add(c34);
        StructureDataType c3233=new StructureDataType(CAT,"I76_Class32_33VisualRuntimeObserved_0x10",0x10);
        c3233.setDescription("Observed class 0x20/0x21 damage-visual runtime prefix ONLY, NOT a complete constructor contract. 0046DFE0.");
        c3233.replaceAtOffset(4,UnsignedIntegerDataType.dataType,4,"local_visual_state","0046DFE0 sets one for local-player root");
        c3233.replaceAtOffset(8,ptr(w),4,"self_world_node","0046DFE0 stores own callback world node");
        c3233.replaceAtOffset(12,UnsignedIntegerDataType.dataType,4,"damage_visual_selector","0046DFE0 sets one for 0x20, two for 0x21");candidates.add(c3233);
        for(StructureDataType cand:candidates){String key=CAT+"/"+cand.getName();try{DataType old=currentProgram.getDataTypeManager().getDataType(CAT,cand.getName());
            if(old!=null){if(old.isEquivalent(cand))done(key);else preserve(key,"existing partial layout disagrees; no replacement");continue;}
            if(APPLY)currentProgram.getDataTypeManager().addDataType(cand,DataTypeConflictHandler.DEFAULT_HANDLER);
            change("RUNTIME_PREFIX",key,"original decompiled field stores; class-specific, not installed at world+0x70");
        }catch(Exception e){fail(key,e);}}
    }
    private int outbound(Address at){int n=0;for(Reference r:currentProgram.getReferenceManager().getReferencesFrom(at))n++;return n;}
    private void mapClassTable(){final String id="004F76E0 class descriptor table[27]";try{
        Address begin=toAddr("004F76E0"),end=begin.add(ROWS*STRIDE-1);DataType ds=currentProgram.getDataTypeManager().getDataType(CAT,"I76_ClassDescriptor_0x34");if(ds==null&&!APPLY)ds=classDesc();if(ds==null){preserve(id,"descriptor type unavailable");return;}
        if(!ds.isEquivalent(classDesc())){preserve(id,"descriptor type differs from v102 verified layout");return;}
        ArrayDataType desired=new ArrayDataType(ds,ROWS,STRIDE);Data existing=currentProgram.getListing().getDataAt(begin);
        if(existing!=null && existing.getDataType().isEquivalent(desired)){done(id);return;}
        if(existing==null){preserve(id,"missing original row-zero data");return;}
        // Guard original binary values for the exact 27-entry table and class-1 pointers.
        if(currentProgram.getMemory().getInt(begin.add(3*STRIDE))!=1 ||
            currentProgram.getMemory().getInt(toAddr("004F7784"))!=0x00463120 ||
            currentProgram.getMemory().getInt(toAddr("004F7788"))!=0x00463800 ||
            currentProgram.getMemory().getInt(toAddr("004F778C"))!=0x00463950 ||
            currentProgram.getMemory().getInt(toAddr("004F77A4"))!=0x00463a80){preserve(id,"immutable class-1 sample values mismatch");return;}
        int oldOutbound=0,oldPointerFields=0,codePtrs=0;
        List<Object[]> preservedComments=new ArrayList<>();
        for(int i=0;i<ROWS*STRIDE;i+=4){Address here=begin.add(i);CodeUnit unit=currentProgram.getListing().getCodeUnitContaining(here);
            if(unit==null||!(unit instanceof Data) || currentProgram.getListing().getInstructionContaining(here)!=null){preserve(id,"instruction/non-data overlaps at "+here);return;}
            Data data=currentProgram.getListing().getDataAt(here);
            if(data==null){preserve(id,"cross-boundary scalar at "+here);return;}
            if(data.getLength()!=4 && !ghidra.program.model.data.Undefined.isUndefined(data.getDataType())){preserve(id,"non-scalar original data at "+here);return;}
            if(data.getDataType() instanceof Pointer)oldPointerFields++;
            oldOutbound+=outbound(here);
            long val=Integer.toUnsignedLong(currentProgram.getMemory().getInt(here));
            if(i%STRIDE!=0&&val!=0){if(val<0x00400000L||val>=0x004C0000L){preserve(id,"non-code-pointer nonzero field at "+here);return;}codePtrs++;}
            for(Symbol symbol:currentProgram.getSymbolTable().getSymbols(here))if(symbol.getSource()==SourceType.USER_DEFINED && !here.equals(begin) && !here.equals(toAddr("004F777C"))){preserve(id,"additional analyst label "+symbol.getName()+" at "+here);return;}
            for(int c:new int[]{CodeUnit.PLATE_COMMENT,CodeUnit.PRE_COMMENT,CodeUnit.POST_COMMENT,CodeUnit.EOL_COMMENT,CodeUnit.REPEATABLE_COMMENT})
                if(unit.getComment(c)!=null) preservedComments.add(new Object[]{here,c,unit.getComment(c)});
        }
        if(codePtrs<60||oldPointerFields<40||oldOutbound<40){preserve(id,"unexpected pointer census: code="+codePtrs+" typed="+oldPointerFields+" refs="+oldOutbound);return;}
        if(APPLY){
            clearListing(begin,end);createData(begin,desired);
            for(Object[] note:preservedComments)currentProgram.getListing().setComment((Address)note[0],((Integer)note[1]).intValue(),(String)note[2]);
            for(Object[] note:preservedComments)if(!((String)note[2]).equals(currentProgram.getListing().getComment(((Integer)note[1]).intValue(),(Address)note[0])))throw new IllegalStateException("Preserved comment lost at "+note[0]);
            // Transaction is rolled back automatically if the converted records lose primary analyst symbols or pointer links.
            Symbol root=currentProgram.getSymbolTable().getPrimarySymbol(begin),veh=currentProgram.getSymbolTable().getPrimarySymbol(toAddr("004F777C"));
            if(root==null||!root.getName().equals("g_world_object_class_callback_table")||veh==null||!veh.getName().equals("g_vehicle_class_callback_table"))throw new IllegalStateException("Analyst entrypoint labels were lost");
            int afterRefs=0;for(int i=0;i<ROWS*STRIDE;i+=4)afterRefs+=outbound(begin.add(i));
            if(afterRefs<oldOutbound)throw new IllegalStateException("Pointer references lost: "+oldOutbound+" -> "+afterRefs);
        }
        change("TABLE",id,"27x52 typed dispatch; verified original code targets="+codePtrs+", source pointer xrefs="+oldOutbound+"; preserved two internal labels and "+preservedComments.size()+" comments");
    }catch(Exception e){fail(id,e);}}
    private void typedParams(){DataType w=world();if(w==null){preserve("PARAMS","missing v101 world type");return;}
       String[][] entries={{"00462040","0","world_node","int","damage dispatcher dereferences world+6C before indexing +28"},
         {"00463A80","0","vehicle_root","int","class-1 damage callback reads world+10/+70"},
         {"0046F2B0","0","world_node","uint","class31 initializer dereferences world+70/+5C"},
         {"0045F810","0","world_node","uint","class34 initializer dereferences world+70"},
         {"0046DFE0","0","world_node","uint","class32/33 visual initializer dereferences world+6C/+70"}};
       for(String[] e:entries){String key=e[0]+" arg"+e[1]+" -> "+e[2];try{Function f=getFunctionAt(toAddr(e[0]));int pos=Integer.parseInt(e[1]);if(f==null||f.getParameterCount()<=pos){preserve(key,"missing function/param");continue;}Parameter p=f.getParameter(pos);DataType target=ptr(w);if(p.getDataType().isEquivalent(target)){done(key);continue;}if(!p.getDataType().getName().equals(e[3])||!p.getName().equals("param_1")){preserve(key,"existing signature differs "+p.getName()+" "+p.getDataType().getName());continue;}if(APPLY){p.setDataType(target,SourceType.USER_DEFINED);p.setName(e[2],SourceType.USER_DEFINED);}change("PARAM",key,e[4]);}catch(Exception x){fail(key,x);}}
       String key="00461970 class_id argument";try{Function f=getFunctionAt(toAddr("00461970"));Parameter p=f.getParameter(1);if(p.getName().equals("class_id")){done(key);}else if(!p.getName().equals("param_2")){preserve(key,"analyst label exists");}else{if(APPLY)p.setName("class_id",SourceType.USER_DEFINED);change("PARAM",key,"original 00461970 stores discriminator at world+6C");}}catch(Exception e){fail(key,e);}
    }
    private void classCounters(){String[][] entries={{"0054B20C","g_ENG_PendingClassNodeCount","pending insert +1 at 00461970 and unlink -1 in 00461B80"},{"0054B210","g_ENG_RegisteredClassNodeCount","enrolled list insert +1 at 00461970 and unlink -1 in 00461C80/1D50"}};
      for(String[] row:entries){String key=row[0]+" "+row[1];try{Address ad=toAddr(row[0]);Data data=currentProgram.getListing().getDataAt(ad);Symbol label=currentProgram.getSymbolTable().getPrimarySymbol(ad);if(label==null||data==null){preserve(key,"missing data");continue;}if(label.getName().equals(row[1])){done(key);continue;}if(label.getSource()!=SourceType.DEFAULT||!ghidra.program.model.data.Undefined.isUndefined(data.getDataType())){preserve(key,"existing analyst name or type");continue;}if(APPLY){label.setName(row[1],SourceType.USER_DEFINED);clearListing(ad,ad.add(3));createData(ad,UnsignedIntegerDataType.dataType);}change("GLOBAL",key,row[2]);}catch(Exception e){fail(key,e);}}
    }
    public void run()throws Exception{identity();int tx=-1;boolean commit=false;try{if(APPLY)tx=currentProgram.startTransaction("I76 v102 C-readable class-dispatch table/ABI");callbackTypes();descriptorType();partialRuntimeTypes();mapClassTable();typedParams();classCounters();commit=errors==0;}finally{if(tx>=0)currentProgram.endTransaction(tx,commit);}println("I76_V102_SUMMARY APPLY="+APPLY+" changed="+changed+" already="+already+" skipped="+skipped+" errors="+errors+" committed="+(APPLY&&commit));if(errors>0)throw new IllegalStateException("v102 migration rolled back: "+failures);}
}
