// I76_ObjectDispatch_v101.java
// @category Interstate76
// Ghidra 12.1.4. C-source readability / object and class-list semantics.
// Baseline: verified v98 + applied v99 and v100. Research aliases, NOT original developer symbols.
// Default is preview only. Use a copy and inspect the decompiler before exporting a new GZF.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.data.*;
import ghidra.program.model.symbol.*;
import java.util.*;

public class I76_ObjectDispatch_v101 extends GhidraScript {
    private static final boolean APPLY = false;
    private static final String MD5="a640ea0097dbb62e0c77b7f2847c7161";
    private static final String SHA256="bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3";
    private static final CategoryPath TYPES=new CategoryPath("/Interstate76/Research-v101");
    private int changed=0,already=0,skipped=0,errors=0;
    private final List<String> failures=new ArrayList<>();
    private void propose(String kind,String key,String why){changed++;println("V101 CHANGE\t"+kind+"\t"+key+"\t"+why);}
    private void done(String key){already++;println("V101 ALREADY\t"+key);}
    private void keep(String key,String why){skipped++;println("V101 PRESERVE\t"+key+"\t"+why);}
    private void fail(String key,Exception e){errors++;failures.add(key+":"+e);println("V101 ERROR\t"+key+"\t"+e);}
    private void identity(){boolean yes=MD5.equalsIgnoreCase(currentProgram.getExecutableMD5())&&SHA256.equalsIgnoreCase(currentProgram.getExecutableSHA256())&&currentProgram.getImageBase().toString().equalsIgnoreCase("00400000")&&currentProgram.getLanguage().getLanguageID().toString().startsWith("x86:LE:32"); if(!yes)throw new IllegalStateException("wrong retail executable/architecture/image base");}
    private DataType ptr(DataType v){return new PointerDataType(v,currentProgram.getDataTypeManager());}
    private StructureDataType struct(String name,int size,String note){StructureDataType x=new StructureDataType(TYPES,name,size);x.setDescription(note);return x;}
    private void fld(Structure s,int off,DataType dt,String name,String evidence){s.replaceAtOffset(off,dt,dt.getLength(),name,evidence);}
    private void u16(Structure s,int off,String n,String e){fld(s,off,UnsignedShortDataType.dataType,n,e);}
    private void u32(Structure s,int off,String n,String e){fld(s,off,UnsignedIntegerDataType.dataType,n,e);}
    private void f64(Structure s,int off,String n,String e){fld(s,off,DoubleDataType.dataType,n,e);}
    private void p(Structure s,int off,String n,String e){fld(s,off,PointerDataType.dataType,n,e);}
    private List<Structure> candidates(){List<Structure> a=new ArrayList<>();
        Structure w=struct("I76_WorldNode_0xB0",0xb0,"Partial retail world node. Allocation/initial stores at 0045EBD0; OBJ index / v100. +68 is MUTABLE contextual link, not invariant parent.");
        u16(w,0x08,"logical_removal_state","0045F0F0 removal branch, original 0045EBD0 zero-init");
        u32(w,0x0c,"reference_count","0045F0F0/0045EF70 release; reference lifetime conditional");
        u32(w,0x10,"status_flags","0045EBD0 init, 004572B0 tests selected bits");
        fld(w,0x18,new ArrayDataType(FloatDataType.dataType,9,4),"orientation_basis_3x3","accepted #49/#67 and v99 partial prefix");
        f64(w,0x40,"position_x","original root world pose");f64(w,0x48,"position_y","original root world pose");f64(w,0x50,"position_z","original root world pose");
        fld(w,0x60,ptr(w),"sibling_or_preceding_link","0045EBD0 child insertion / 0045F0F0 removal; same world node type");
        fld(w,0x64,ptr(w),"last_child","0045EBD0 writes current newest child; not first child");
        p(w,0x68,"context_link_mutable","0045EBD0 parent on insertion, may later become sibling backlink; do not infer stable parent");
        u32(w,0x6c,"class_id","00461970 writes class discriminator");p(w,0x70,"class_runtime","004AD6F0 creates VCF runtime, class-specific and opaque");a.add(w);
        Structure l=struct("I76_ClassLinkNode_0x0C",0x0c,"0049C320 generic 12-byte list node; prev/next/data; same shape for class enrolled and pending lists, DIFFERENT payloads.");
        fld(l,0x00,ptr(l),"previous","0049C320 initial param_1");fld(l,0x04,ptr(l),"next","0049C320 initial param_2");p(l,0x08,"payload","Enrolled node => world handle; pending node => enrolled node pointer. Avoid one payload type for both.");a.add(l);
        Structure r=struct("I76_ActiveWorldEntry_0x78",0x78,"004572B0 / 00457420, 30-DWORD active-world entry; only safe fields included; do NOT use class-collection node type.");
        fld(r,0,ptr(w),"world_object","004572B0 stores node pointer, 00409850/00409980 deref");
        u32(r,0x14,"active_state","004572B0 selection branch writes one");
        u32(r,0x18,"registration_tag","004572B0 stores external parameter when active");
        u32(r,0x30,"has_supplied_bounds_payload","004572B0 marks caller payload copying; other extent semantics unresolved");a.add(r);
        return a;
    }
    private void createTypes(){for(Structure s:candidates()){String key=TYPES+"/"+s.getName();try{DataType old=currentProgram.getDataTypeManager().getDataType(TYPES,s.getName());if(old!=null){if(old.isEquivalent(s)){done(key);}else{keep(key,"existing type differs; no replacement");}continue;}if(APPLY)currentProgram.getDataTypeManager().addDataType(s,DataTypeConflictHandler.DEFAULT_HANDLER);propose("TYPE",key,"partial, original code and accepted research");}catch(Exception e){fail(key,e);}}}
    private DataType type(String name){DataType d=currentProgram.getDataTypeManager().getDataType(TYPES,name);if(d==null&&!APPLY){for(Structure s:candidates())if(s.getName().equals(name))return s;}return d;}
    private static final class PRule {String a,n,old,t,ev;int i,depth;PRule(String a,int i,String n,String old,String t,int depth,String ev){this.a=a;this.i=i;this.n=n;this.old=old;this.t=t;this.depth=depth;this.ev=ev;}}
    // Type only parameters with direct original code evidence; leave runtime-specific and mixed records opaque.
    private static final PRule[] PARAMS={
      new PRule("0045EBD0",0,"parent_world_node","int","I76_WorldNode_0xB0",1,"allocates child under parent +0x64; #OBJ and original decompile"),
      new PRule("00461970",0,"world_node","int","I76_WorldNode_0xB0",1,"writes class +0x6c and runtime +0x70"),
      new PRule("00463120",0,"vehicle_root","pointer","I76_WorldNode_0xB0",1,"class-1 init uses +0x6c,+0x70; opaque runtime pointer"),
      new PRule("00463800",0,"vehicle_root","float *","I76_WorldNode_0xB0",1,"class-1 pre uses runtime +0x70 and status +0x10"),
      new PRule("00463950",0,"vehicle_root","pointer","I76_WorldNode_0xB0",1,"class-1 post callback receives same world node"),
      new PRule("0045F0F0",0,"world_node","LPVOID","I76_WorldNode_0xB0",1,"conditional resolver/removal; original branch +08,+0c,+60,+64,+68"),
      new PRule("0045EF70",0,"world_node","LPVOID","I76_WorldNode_0xB0",1,"conditional reference cleanup"),
      new PRule("004572B0",0,"world_node","int","I76_WorldNode_0xB0",1,"active registry captures world node"),
      new PRule("0049C320",0,"previous_node","int","I76_ClassLinkNode_0x0C",1,"generic list allocator previous link"),
      new PRule("0049C320",1,"next_node","undefined4 *","I76_ClassLinkNode_0x0C",1,"generic list allocator next link"),
      new PRule("0049C360",0,"head_pointer","int *","I76_ClassLinkNode_0x0C",2,"unlink routine writes caller head; pointer-to-pointer"),
      new PRule("0049C360",1,"node","int *","I76_ClassLinkNode_0x0C",1,"unlink 0x0c-byte entry"),
      new PRule("00457420",0,"registered_entry","int *","I76_ActiveWorldEntry_0x78",1,"unregister entry pointer"),
      new PRule("00409850",0,"registered_entry","int *","I76_ActiveWorldEntry_0x78",1,"FSM registration callback receives active entry"),
      new PRule("00409980",0,"registered_entry","int *","I76_ActiveWorldEntry_0x78",1,"FSM unregistration callback receives active entry")
    };
    private void params(){for(PRule r:PARAMS){String key=r.a+" arg["+r.i+"] "+r.n;try{Function f=getFunctionAt(toAddr(r.a));if(f==null||f.getParameterCount()<=r.i){keep(key,"function/argument unavailable");continue;}Parameter x=f.getParameter(r.i);DataType s=type(r.t);if(s==null){keep(key,"type missing; apply v101 types first");continue;}DataType want=ptr(s);if(r.depth==2)want=ptr(want);if(x.getDataType().isEquivalent(want)){done(key);continue;}if(!x.getName().equals(r.n)&&!(r.n.equals("world_node")&&x.getName().equals("param_1"))&&!(r.n.equals("parent_world_node")&&x.getName().equals("param_1"))&&!(r.n.equals("previous_node")&&x.getName().equals("param_1"))&&!(r.n.equals("next_node")&&x.getName().equals("param_2"))&&!(r.n.equals("head_pointer")&&x.getName().equals("param_1"))&&!(r.n.equals("node")&&x.getName().equals("param_2"))&&!(r.n.equals("registered_entry")&&x.getName().equals("param_1"))){keep(key,"analyst name conflict: "+x.getName());continue;}
       if(!x.getDataType().getName().equals(r.old)){keep(key,"type not expected baseline: "+x.getDataType().getName());continue;}
       if(APPLY){x.setDataType(want,SourceType.USER_DEFINED);if(x.getName().startsWith("param_"))x.setName(r.n,SourceType.USER_DEFINED);}propose("PARAM",key,r.old+" -> "+r.t+"*; "+r.ev);
    }catch(Exception e){fail(key,e);}}}
    private void returns(){String[][] rs={{"0045EBD0","LPVOID","I76_WorldNode_0xB0","constructor allocation returns newly created node"},{"0045F0F0","LPVOID","I76_WorldNode_0xB0","live resolve returns same world node, removal branch may mutate"},{"004572B0","int *","I76_ActiveWorldEntry_0x78","active registry entry returned after insert"},{"0049C320","undefined","I76_ClassLinkNode_0x0C","0049C320 original 0049C331..0049C357 keeps HeapAlloc EAX intact across successful/failed allocation; enrolled/pending callers use EAX as node"}};
      for(String[] r:rs){String key=r[0]+" return "+r[2]+"*";try{Function f=getFunctionAt(toAddr(r[0]));DataType s=type(r[2]);if(f==null||s==null){keep(key,"function/type missing");continue;}DataType want=ptr(s);if(f.getReturnType().isEquivalent(want)){done(key);continue;}if(!f.getReturnType().getName().equals(r[1])){keep(key,"unexpected current return "+f.getReturnType().getName());continue;}if(APPLY)f.setReturnType(want,SourceType.USER_DEFINED);propose("RETURN",key,r[3]);}catch(Exception e){fail(key,e);}}}
    private void globalHeads(){String[][] rr={{"0054B204","g_queued_world_object_class_callback_list","enrolled class node head"},{"0054B208","g_ENG_ClassPendingListHead","pending init node head"}};
      for(String[] x:rr){String key=x[0]+" "+x[1];try{Address a=toAddr(x[0]);Symbol sym=currentProgram.getSymbolTable().getPrimarySymbol(a);Data d=currentProgram.getListing().getDataAt(a);DataType t=type("I76_ClassLinkNode_0x0C");if(sym==null||!sym.getName().equals(x[1])||d==null||t==null){keep(key,"baseline symbol/type missing");continue;}DataType want=ptr(t);if(d.getDataType().isEquivalent(want)){done(key);continue;}if(!"undefined4".equals(d.getDataType().getName())||d.getLength()!=4){keep(key,"existing data definition differs: "+d.getDataType());continue;}if(APPLY){clearListing(a,a.add(3));createData(a,want);}propose("GLOBAL",key,"typed list head: "+x[2]);}catch(Exception e){fail(key,e);}}}
    private void guardedLabel(){String a="0045F0F0",prev="release_world_object_tree_reference",next="OBJ_ResolveLiveOrReleaseWorldReference";try{Function f=getFunctionAt(toAddr(a));if(f==null){keep(a,"function missing");return;}if(f.getName().equals(next)){done(a+" alias");return;}if(!f.getName().equals(prev)||f.getSymbol().getSource()!=SourceType.USER_DEFINED&&f.getSymbol().getSource()!=SourceType.ANALYSIS){keep(a,"analyst name differs: "+f.getName());return;}if(APPLY)f.setName(next,SourceType.USER_DEFINED);propose("NAME",a+" "+prev+" -> "+next,"resolver on live inputs, conditional removal on logically removed; OBJ #95 and direct Ghidra decompile");}catch(Exception e){fail(a,e);}}
    private void evidenceComment(){String a="0045F0F0",key=a+" lifecycle note";try{Address at=toAddr(a);CodeUnit cu=currentProgram.getListing().getCodeUnitAt(at);String old=cu.getComment(CodeUnit.PLATE_COMMENT);String note="I76-v101: Live world-object resolution occurs during original ENG dispatch (accepted M-ENG-01); logically removed object can enter conditional unlink/refcount release. Not an unconditional live-object decref. +0x68 link is contextual, not an immutable parent. See merged #95 OBJ index and promoted class schedule. Research-derived C semantics.";if(old!=null&&old.contains(note)){done(key);return;}if(APPLY)cu.setComment(CodeUnit.PLATE_COMMENT,(old==null?"":old+"\n")+note);propose("COMMENT",key,"preserve earlier comments");}catch(Exception e){fail(key,e);}}
    public void run()throws Exception{identity();int tx=-1;boolean commit=false;try{if(APPLY)tx=currentProgram.startTransaction("I76 v101 world-object and class-dispatch semantics");createTypes();params();returns();globalHeads();guardedLabel();evidenceComment();commit=errors==0;}finally{if(tx>=0)currentProgram.endTransaction(tx,commit);}println("I76_V101_SUMMARY APPLY="+APPLY+" changed="+changed+" already="+already+" skipped="+skipped+" errors="+errors+" committed="+(APPLY&&commit));if(errors>0)throw new IllegalStateException("v101 rolled back: "+failures);}
}