// Standalone reconciliation of accepted v100-v102 annotations on verified v99.
// Research aliases; not recovered original identifiers. Preview is the default.
//@category Interstate76
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.data.*;
import ghidra.program.model.symbol.*;
import java.util.*;
import java.security.*;
public class I76_Reconcile_v100_v102_20261103 extends GhidraScript {
 boolean APPLY=false;
 String phase="ALL";
 int proposed,already,preserved,conflicted,deferred;
 protected void checkpoint() throws Exception {} // Empty hook; disposable tests may override.
 void report(String status,String id,String why){println(status+"\t"+id+"\t"+why);switch(status){case "APPLY":proposed++;break;case "ALREADY":already++;break;case "PRESERVE":preserved++;break;case "CONFLICT":conflicted++;break;case "DEFER":deferred++;break;}}
 void conflict(String id,String why){report("CONFLICT",id,why);throw new IllegalStateException("CONFLICT "+id+": "+why);}
 String sha(byte[] b)throws Exception{return HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(b));}
 String bodyDigest(Function f)throws Exception{var md=MessageDigest.getInstance("SHA-256");var rs=f.getBody().getAddressRanges();while(rs.hasNext()){var r=rs.next();byte[] b=new byte[(int)r.getLength()];currentProgram.getMemory().getBytes(r.getMinAddress(),b);md.update(b);}return HexFormat.of().formatHex(md.digest());}
 String originalFunctions()throws Exception{StringBuilder b=new StringBuilder();var fs=currentProgram.getFunctionManager().getFunctions(true);while(fs.hasNext()){var f=fs.next();b.append(f.getEntryPoint()+"\t"+f.getBody()+"\t"+bodyDigest(f)+"\n");}return sha(b.toString().getBytes(java.nio.charset.StandardCharsets.UTF_8));}
 boolean equivalent(DataType a,DataType b){return eq(a,b,new HashSet<>());}
 boolean eq(DataType a,DataType b,Set<String> seen){
 if(a==null||b==null)return a==b;
 if(a.getLength()!=b.getLength())return false;
 if(!(a instanceof Pointer)&&!(a instanceof Array)&&!a.getName().equals(b.getName()))return false;
 String key=a.getPathName()+"|"+b.getPathName();if(!seen.add(key))return true;
 if(a instanceof Pointer x && b instanceof Pointer y)return eq(x.getDataType(),y.getDataType(),seen);
 if(a instanceof Array x && b instanceof Array y)return x.getNumElements()==y.getNumElements()&&x.getElementLength()==y.getElementLength()&&eq(x.getDataType(),y.getDataType(),seen);
 if(a instanceof Structure x && b instanceof Structure y){var xs=x.getDefinedComponents();var ys=y.getDefinedComponents();if(xs.length!=ys.length)return false;for(int i=0;i<xs.length;i++)if(xs[i].getOffset()!=ys[i].getOffset()||xs[i].getLength()!=ys[i].getLength()||!Objects.equals(xs[i].getFieldName(),ys[i].getFieldName())||!eq(xs[i].getDataType(),ys[i].getDataType(),seen))return false;return true;}
 if(a instanceof FunctionDefinition x && b instanceof FunctionDefinition y){if(!eq(x.getReturnType(),y.getReturnType(),seen)||x.hasVarArgs()!=y.hasVarArgs()||!Objects.equals(x.getCallingConventionName(),y.getCallingConventionName()))return false;var xs=x.getArguments();var ys=y.getArguments();if(xs.length!=ys.length)return false;for(int i=0;i<xs.length;i++)if(!Objects.equals(xs[i].getName(),ys[i].getName())||!eq(xs[i].getDataType(),ys[i].getDataType(),seen))return false;return true;}
 return a.isEquivalent(b);
 }
 static final String BODY_SHA="f852f23a1ea3d9cfaefd9187a0dc16dc0ec8420f158c27d3bee7c7045bc805ab";
 static final String TABLE_SHA="2f233daf86fb10ed5a7d6eb11c7936214c0cd99bf46866a2b863c8741f98865c";
 static final String[][] SHAPES={
{"/Interstate76/Research-v99/I76_CameraView_0x1D8","472","0:viewport_center_x:/float;4:viewport_center_y:/float;8:projection_scale_x:/float;12:projection_scale_y:/float;28:viewport_min_x:/float;32:viewport_min_y:/float;36:viewport_max_x:/float;40:viewport_max_y:/float;44:fov_tangent:/float;48:aspect:/float;52:zoom:/float;60:viewport_context_ptr:/pointer;64:inverse_orientation_3x3:/float[9];104:inverse_translation_x:/double;112:inverse_translation_y:/double;120:inverse_translation_z:/double;128:world_frustum_aabb_center_x:/double;136:world_frustum_aabb_center_y:/double;144:world_frustum_aabb_center_z:/double;152:world_frustum_bounding_radius:/double;160:frustum_plane_raw:/byte[96];264:near_clip_z:/float;312:far_clip_z:/float;352:source_camera_x:/double;360:source_camera_y:/double;368:source_camera_z:/double;376:world_frustum_corners_4x3:/double[12]"},
{"/Interstate76/Research-v99/I76_ClassDescriptor_0x34","52","8:initialize_callback:/pointer;12:pre_callback:/pointer;16:post_callback:/pointer"},
{"/Interstate76/Research-v99/I76_ProjectVertex_0x18","24","0:screen_x:/float;4:screen_y:/float;8:reciprocal_z:/float;20:copied_attribute:/uint"},
{"/Interstate76/Research-v99/I76_RenderWorkKind6_0x44","68","12:record_kind:/uint;20:next_record:/pointer;28:world_object_owner:/pointer;32:camera_classified_x:/float;36:camera_classified_y:/float;40:camera_classified_z:/float;44:bounding_radius:/float;48:mode_selector:/uint;52:flags:/uint;56:pass_selector:/uint;60:cache_state:/uint;64:active_world_entry:/pointer"},
{"/Interstate76/Research-v99/I76_SoftwareDrawCommand_0x60","96","0:call_color_control:/uint;4:next_command:/pointer;8:span_callback:/pointer;24:shade_plane_constant:/float;28:control_word:/uint;32:left_edge_head:/pointer;36:right_edge_head:/pointer;40:pending_packed_span:/uint;48:extent_or_span_slot:/uint;52:sequence_serial:/uint;88:shade_gradient_x:/float;92:shade_gradient_y:/float"},
{"/Interstate76/Research-v99/I76_SoftwareSurface_0x34","52","0:byte_pitch:/uint;4:flags:/uint;8:caller_mode:/uint;12:pixel_count_div_4:/uint;16:pixel_count_mod_32:/uint;20:aligned_pixel_base:/pointer;24:backing_allocation:/pointer;28:x_offset_bytes:/uint;32:y_row_offset:/uint;36:max_x_inclusive:/uint;40:max_y_inclusive:/uint;44:owns_backing:/uint"},
{"/Interstate76/Research-v99/I76_TerrainAdaptiveLeaf_0x1C","28","8:next_leaf:/pointer;12:edge_walk_reverse_last:/pointer;16:edge_walk_forward_second:/pointer;20:edge_walk_forward_first:/pointer;24:edge_walk_reverse_third:/pointer"},
{"/Interstate76/Research-v99/I76_WorldObjectPosePrefix_0x58","88","24:orientation_basis_3x3:/float[9];64:position_x:/double;72:position_y:/double;80:position_z:/double"},
{"/Interstate76/SemanticConsolidation/TER_Normal3f","12","0:x:/float;4:y:/float;8:z:/float"},
{"/Interstate76/SemanticConsolidation/TER_Page","32768","0:samples:/ushort[128][128]"},
{"/Interstate76/SemanticConsolidation/VmNode","4284","0:workspace_words:/uint[1024];4096:host_words:/uint[40];4256:condition:/uint;4260:token_base:/Interstate76/SemanticConsolidation/VmToken *32;4264:ip:/Interstate76/SemanticConsolidation/VmToken *32;4268:frame:/uint *32;4272:operand_cursor:/uint *32;4276:host_cursor:/uint *32;4280:next:/Interstate76/SemanticConsolidation/VmNode *32"},
{"/Interstate76/SemanticConsolidation/VmToken","8","0:kind:/uint;4:payload:/uint"},
 };
 static final String[][] SIGNATURES={
{"00409850","fsm_on_world_object_registered|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|param_1:/int *:Stack[0x4]:4:DEFAULT"},
{"00409980","fsm_on_world_object_unregistered|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|param_1:/int *:Stack[0x4]:4:DEFAULT"},
{"004572b0","register_active_world_object_entry|USER_DEFINED|__cdecl|false|ANALYSIS|/int *|EAX:4|param_1:/int:Stack[0x4]:4:DEFAULT|param_2:/int:Stack[0x8]:4:DEFAULT|param_3:/int *:Stack[0xc]:4:DEFAULT"},
{"00457420","unregister_active_world_object_entry_and_release|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|param_1:/int *:Stack[0x4]:4:DEFAULT"},
{"00457ff0","RND_ProduceVisibleWorldWorkRecords|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|camera_view:/int *:Stack[0x4]:4:USER_DEFINED"},
{"0045ebd0","allocate_world_object_node|USER_DEFINED|__cdecl|false|ANALYSIS|/WinDef.h/LPVOID|EAX:4|param_1:/int:Stack[0x4]:4:DEFAULT"},
{"0045ef70","finalize_released_world_object_after_damage|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|param_1:/WinDef.h/LPVOID:Stack[0x4]:4:DEFAULT|param_2:/undefined4:Stack[0x8]:4:DEFAULT"},
{"0045f0f0","release_world_object_tree_reference|USER_DEFINED|__cdecl|false|ANALYSIS|/WinDef.h/LPVOID|EAX:4|param_1:/WinDef.h/LPVOID:Stack[0x4]:4:DEFAULT|param_2:/undefined4:Stack[0x8]:4:DEFAULT"},
{"0045f810","VEH_Class34InitializeRootLink|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|param_1:/uint:Stack[0x4]:4:DEFAULT"},
{"00461970","set_world_object_class_and_register_runtime|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|param_1:/int:Stack[0x4]:4:DEFAULT|param_2:/int:Stack[0x8]:4:DEFAULT"},
{"00462040","dispatch_damage_context_to_world_object_class_handler|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined4|EAX:4|param_1:/int:Stack[0x4]:4:DEFAULT|param_2:/undefined4:Stack[0x8]:4:DEFAULT|param_3:/undefined4:Stack[0xc]:4:DEFAULT"},
{"00463120","initialize_vehicle_runtime_context_and_cockpit_state|USER_DEFINED|__cdecl|false|USER_DEFINED|/undefined|<UNASSIGNED>|vehicle_root:/pointer:Stack[0x4]:4:USER_DEFINED"},
{"00463800","vehicle_class_pre_update_callback|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|vehicle_root:/float *:Stack[0x4]:4:USER_DEFINED"},
{"00463950","VEH_Class1PostUpdate|USER_DEFINED|__cdecl|false|USER_DEFINED|/undefined|<UNASSIGNED>|vehicle_root:/pointer:Stack[0x4]:4:USER_DEFINED"},
{"00463a80","apply_vehicle_class_damage_and_destruction|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined4|EAX:4|param_1:/int:Stack[0x4]:4:DEFAULT|param_2:/int *:Stack[0x8]:4:DEFAULT|param_3:/float *:Stack[0xc]:4:DEFAULT"},
{"0046dfe0","initialize_vehicle_door_or_hood_damage_visual|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|param_1:/uint:Stack[0x4]:4:DEFAULT"},
{"0046f2b0","VEH_Class31InitializeAnimation|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|param_1:/uint:Stack[0x4]:4:DEFAULT"},
{"00472c10","RND_ClassifyObjectAgainstView|USER_DEFINED|__cdecl|false|ANALYSIS|/int|EAX:4|camera_view:/int:Stack[0x4]:4:USER_DEFINED|sphere_center_xyz:/float *:Stack[0x8]:4:USER_DEFINED|sphere_radius:/float:Stack[0xc]:4:USER_DEFINED"},
{"00474c60","construct_bitmap_surface_context|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|surface_descriptor:/int *:Stack[0x4]:4:USER_DEFINED|byte_pitch:/int:Stack[0x8]:4:USER_DEFINED|height_rows:/uint:Stack[0xc]:4:USER_DEFINED|optional_backing_pixels:/int:Stack[0x10]:4:USER_DEFINED|pixel_format_mode:/int:Stack[0x14]:4:USER_DEFINED"},
{"0047cb00","raster_emit_flat_shaded_gradient_spans|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|draw_command:/byte *:Stack[0x4]:4:USER_DEFINED|surface_descriptor:/int *:Stack[0x8]:4:USER_DEFINED"},
{"0048fac0","RND_ConsumeDepthBucketQueue|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|camera_view:/float *:Stack[0x4]:4:USER_DEFINED|param_2:/int:Stack[0x8]:4:DEFAULT"},
{"00490a00","build_adaptive_terrain_root_primitives|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|camera_view:/int:Stack[0x4]:4:USER_DEFINED"},
{"00491810","allocate_terrain_leaf_primitive_node|USER_DEFINED|__cdecl|false|ANALYSIS|/short *|EAX:4|edge_ref_0:/undefined4:Stack[0x4]:4:USER_DEFINED|edge_ref_1:/undefined4:Stack[0x8]:4:USER_DEFINED|edge_ref_2:/undefined4:Stack[0xc]:4:USER_DEFINED|edge_ref_3:/undefined4:Stack[0x10]:4:USER_DEFINED"},
{"004929b0","TER_ComputeVisibleTerrainBounds|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined4|EAX:4|camera_view:/int:Stack[0x4]:4:USER_DEFINED"},
{"0049c320","allocate_linked_list_node_3field|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|param_1:/int:Stack[0x4]:4:DEFAULT|param_2:/undefined4 *:Stack[0x8]:4:DEFAULT|param_3:/int:Stack[0xc]:4:DEFAULT"},
{"0049c360","unlink_and_free_linked_list_node_3field|USER_DEFINED|__cdecl|false|ANALYSIS|/undefined|<UNASSIGNED>|param_1:/int *:Stack[0x4]:4:DEFAULT|param_2:/int *:Stack[0x8]:4:DEFAULT"},
 };
 class V100 {

    private static final boolean INSTALL_CLASS1_DESCRIPTOR = true;
    private static final String MD5 = "a640ea0097dbb62e0c77b7f2847c7161";
    private static final String SHA256 = "bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3";
    private static final CategoryPath V99 = new CategoryPath("/Interstate76/Research-v99");
    private static final CategoryPath V100 = new CategoryPath("/Interstate76/Research-v100");

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

    private void proposal(String type,String id,String details){report("APPLY","v100 "+type+" "+id,details);}
    private void done(String id){report("ALREADY","v100 "+id,"");}
    private void keep(String id,String reason){conflict("v100 "+id,reason);}
    private void fail(String id,Exception e){throw new IllegalStateException("v100 "+id,e);}
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
            if(Set.of("00457FF0","00474C60","00472C10").contains(r.va)){
                report("DEFER","v100 PARAM "+key,
                    r.va.equals("00457FF0")?"trial conflates active-world/scratch pointers with camera fields; original-pointer typing alone insufficient":
                    r.va.equals("00474C60")?"trial gives DWORD copy loops misleading repeated byte_pitch/flags access; retain original array semantics":
                    "trial replaces float plane traversal with byte-array casts; retain numeric traversal pending plane-layout research");continue;
            }
            try {
                Function f=getFunctionAt(toAddr(r.va));
                if(f==null){keep(key,"no function at entry");continue;}
                Parameter[] p=f.getParameters();
                if(r.ordinal>=p.length){keep(key,"missing argument; preserve ABI");continue;}
                Parameter arg=p[r.ordinal];
                DataType target=known(r.structName);
                if(!(target instanceof Structure)){keep(key,"required verified v99 type missing; apply v99 first");continue;}
                DataType want=pointerTo(target);
                if(equivalent(arg.getDataType(),want)){done(key);continue;}
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
            if(equivalent(f.getReturnType(),want)){done(key);return;}
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
            }else {if(!equivalent(cb,callbackType(root)))keep(key,"incompatible callback definition");done("I76_Class1Callback");}
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
            }else if(stExisting instanceof Structure && validV100Descriptor((Structure)stExisting,cb))done("I76_Class1Descriptor_0x34");
            else keep(key,"existing incompatible descriptor type; preserved");
        }catch(Exception e){fail(key,e);}
    }

    private void installDescriptor(){
        if(!INSTALL_CLASS1_DESCRIPTOR)return; if(finalTable()){for(int off:new int[]{8,12,16})done("004F777C slot +"+Integer.toHexString(off)+" (subsumed by verified v102 array)");return;}
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
                if(old!=null&&equivalent(old.getDataType(),want)){done(id);continue;}
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


 }
 class V101 {

    private static final String MD5="a640ea0097dbb62e0c77b7f2847c7161";
    private static final String SHA256="bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3";
    private static final CategoryPath TYPES=new CategoryPath("/Interstate76/Research-v101");
    private void propose(String kind,String key,String why){report("APPLY","v101 "+kind+" "+key,why);}
    private void done(String key){report("ALREADY","v101 "+key,"");}
    private void keep(String key,String why){conflict("v101 "+key,why);}
    private void fail(String key,Exception e){throw new IllegalStateException("v101 "+key,e);}
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
    private void createTypes(){for(Structure s:candidates()){String key=TYPES+"/"+s.getName();try{DataType old=currentProgram.getDataTypeManager().getDataType(TYPES,s.getName());if(old!=null){if(equivalent(old,s)){done(key);}else{keep(key,"existing type differs; no replacement");}continue;}if(APPLY)currentProgram.getDataTypeManager().addDataType(s,DataTypeConflictHandler.DEFAULT_HANDLER);propose("TYPE",key,"partial, original code and accepted research");}catch(Exception e){fail(key,e);}}}
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
    private void params(){for(PRule r:PARAMS){String key=r.a+" arg["+r.i+"] "+r.n;if(r.a.equals("00409980")){report("DEFER","v101 PARAM "+key,"trial reuses active-entry pointer as integer bucket index and fabricates world_object field arithmetic; needs local-variable separation");continue;}try{Function f=getFunctionAt(toAddr(r.a));if(f==null||f.getParameterCount()<=r.i){keep(key,"function/argument unavailable");continue;}Parameter x=f.getParameter(r.i);DataType s=type(r.t);if(s==null){keep(key,"type missing; apply v101 types first");continue;}DataType want=ptr(s);if(r.depth==2)want=ptr(want);if(equivalent(x.getDataType(),want)){done(key);continue;}if(!x.getName().equals(r.n)&&!(r.n.equals("world_node")&&x.getName().equals("param_1"))&&!(r.n.equals("parent_world_node")&&x.getName().equals("param_1"))&&!(r.n.equals("previous_node")&&x.getName().equals("param_1"))&&!(r.n.equals("next_node")&&x.getName().equals("param_2"))&&!(r.n.equals("head_pointer")&&x.getName().equals("param_1"))&&!(r.n.equals("node")&&x.getName().equals("param_2"))&&!(r.n.equals("registered_entry")&&x.getName().equals("param_1"))){keep(key,"analyst name conflict: "+x.getName());continue;}
       if(!x.getDataType().getName().equals(r.old)){keep(key,"type not expected baseline: "+x.getDataType().getName());continue;}
       if(APPLY){x.setDataType(want,SourceType.USER_DEFINED);if(x.getName().startsWith("param_"))x.setName(r.n,SourceType.USER_DEFINED);}propose("PARAM",key,r.old+" -> "+r.t+"*; "+r.ev);
    }catch(Exception e){fail(key,e);}}}
    private void returns(){String[][] rs={{"0045EBD0","LPVOID","I76_WorldNode_0xB0","constructor allocation returns newly created node"},{"0045F0F0","LPVOID","I76_WorldNode_0xB0","live resolve returns same world node, removal branch may mutate"},{"004572B0","int *","I76_ActiveWorldEntry_0x78","active registry entry returned after insert"},{"0049C320","undefined","I76_ClassLinkNode_0x0C","0049C320 original 0049C331..0049C357 keeps HeapAlloc EAX intact across successful/failed allocation; enrolled/pending callers use EAX as node"}};
      for(String[] r:rs){String key=r[0]+" return "+r[2]+"*";try{Function f=getFunctionAt(toAddr(r[0]));DataType s=type(r[2]);if(f==null||s==null){keep(key,"function/type missing");continue;}DataType want=ptr(s);if(equivalent(f.getReturnType(),want)){done(key);continue;}if(!f.getReturnType().getName().equals(r[1])){keep(key,"unexpected current return "+f.getReturnType().getName());continue;}if(APPLY)f.setReturnType(want,SourceType.USER_DEFINED);propose("RETURN",key,r[3]);}catch(Exception e){fail(key,e);}}}
    private void globalHeads(){String[][] rr={{"0054B204","g_queued_world_object_class_callback_list","enrolled class node head"},{"0054B208","g_ENG_ClassPendingListHead","pending init node head"}};
      for(String[] x:rr){String key=x[0]+" "+x[1];try{Address a=toAddr(x[0]);footprint(Long.parseLong(x[0],16));Symbol sym=currentProgram.getSymbolTable().getPrimarySymbol(a);Data d=currentProgram.getListing().getDataAt(a);DataType t=type("I76_ClassLinkNode_0x0C");if(sym==null||!sym.getName().equals(x[1])||d==null||t==null){keep(key,"baseline symbol/type missing");continue;}DataType want=ptr(t);if(equivalent(d.getDataType(),want)){done(key);continue;}if(!"undefined4".equals(d.getDataType().getName())||d.getLength()!=4){keep(key,"existing data definition differs: "+d.getDataType());continue;}if(APPLY){clearListing(a,a.add(3));createData(a,want);}propose("GLOBAL",key,"typed list head: "+x[2]);}catch(Exception e){fail(key,e);}}}
    private void guardedLabel(){String a="0045F0F0",prev="release_world_object_tree_reference",next="OBJ_ResolveLiveOrReleaseWorldReference";try{Function f=getFunctionAt(toAddr(a));if(f==null){keep(a,"function missing");return;}if(f.getName().equals(next)){done(a+" alias");return;}if(!f.getName().equals(prev)||f.getSymbol().getSource()!=SourceType.USER_DEFINED&&f.getSymbol().getSource()!=SourceType.ANALYSIS){keep(a,"analyst name differs: "+f.getName());return;}if(APPLY)f.setName(next,SourceType.USER_DEFINED);propose("NAME",a+" "+prev+" -> "+next,"resolver on live inputs, conditional removal on logically removed; OBJ #95 and direct Ghidra decompile");}catch(Exception e){fail(a,e);}}
    private void evidenceComment(){String a="0045F0F0",key=a+" lifecycle note";try{Address at=toAddr(a);CodeUnit cu=currentProgram.getListing().getCodeUnitAt(at);String old=cu.getComment(CodeUnit.PLATE_COMMENT);String note="I76-v101: Live world-object resolution occurs during original ENG dispatch (accepted M-ENG-01); logically removed object can enter conditional unlink/refcount release. Not an unconditional live-object decref. +0x68 link is contextual, not an immutable parent. See merged #95 OBJ index and promoted class schedule. Research-derived C semantics.";if(old!=null&&old.contains(note)){done(key);return;}if(APPLY)cu.setComment(CodeUnit.PLATE_COMMENT,(old==null?"":old+"\n")+note);propose("COMMENT",key,"preserve earlier comments");}catch(Exception e){fail(key,e);}}

 }
 class V102 {

    private static final String MD5="a640ea0097dbb62e0c77b7f2847c7161";
    private static final String SHA256="bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3";
    private static final CategoryPath CAT=new CategoryPath("/Interstate76/Research-v102");
    private static final int ROWS=27, STRIDE=0x34;
    private void change(String group,String what,String why){report("APPLY","v102 "+group+" "+what,why);}
    private void done(String x){report("ALREADY","v102 "+x,"");}
    private void preserve(String x,String why){conflict("v102 "+x,why);}
    private void fail(String x,Exception e){throw new IllegalStateException("v102 "+x,e);}
    private void identity(){if(!MD5.equalsIgnoreCase(currentProgram.getExecutableMD5())||!SHA256.equalsIgnoreCase(currentProgram.getExecutableSHA256())||!"00400000".equalsIgnoreCase(currentProgram.getImageBase().toString())||!currentProgram.getLanguage().getLanguageID().toString().startsWith("x86:LE:32")) throw new IllegalStateException("Not the verified retail i76.exe x86/32 baseline");}
    private DataType world(){return v101.type("I76_WorldNode_0xB0");}
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
        for(FunctionDefinitionDataType f:callbackCandidates()){String id=CAT+"/"+f.getName();try{DataType existing=currentProgram.getDataTypeManager().getDataType(CAT,f.getName());if(existing!=null){if(equivalent(existing,f))done(id);else preserve(id,"existing type conflicts; leave untouched");}else{if(APPLY)currentProgram.getDataTypeManager().addDataType(f,DataTypeConflictHandler.DEFAULT_HANDLER);change("FUNCDEF",id,note[i]);}}catch(Exception e){fail(id,e);}i++;}
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
    private void descriptorType(){String id=CAT+"/I76_ClassDescriptor_0x34";try{StructureDataType d=classDesc();DataType old=currentProgram.getDataTypeManager().getDataType(CAT,d.getName());if(old!=null){if(equivalent(old,d))done(id);else preserve(id,"existing structural definition differs");return;}if(APPLY)currentProgram.getDataTypeManager().addDataType(d,DataTypeConflictHandler.DEFAULT_HANDLER);change("STRUCT",id,"original class-table stride 0x34; indexed dispatch and distinct callback signatures");}catch(Exception e){fail(id,e);}}
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
            if(old!=null){if(equivalent(old,cand))done(key);else preserve(key,"existing partial layout disagrees; no replacement");continue;}
            if(APPLY)currentProgram.getDataTypeManager().addDataType(cand,DataTypeConflictHandler.DEFAULT_HANDLER);
            change("RUNTIME_PREFIX",key,"original decompiled field stores; class-specific, not installed at world+0x70");
        }catch(Exception e){fail(key,e);}}
    }
    private int outbound(Address at){int n=0;for(Reference r:currentProgram.getReferenceManager().getReferencesFrom(at))n++;return n;}
    private void mapClassTable(){final String id="004F76E0 class descriptor table[27]";try{
        Address begin=toAddr("004F76E0"),end=begin.add(ROWS*STRIDE-1);DataType ds=currentProgram.getDataTypeManager().getDataType(CAT,"I76_ClassDescriptor_0x34");if(ds==null&&!APPLY)ds=classDesc();if(ds==null){preserve(id,"descriptor type unavailable");return;}
        if(!equivalent(ds,classDesc())){preserve(id,"descriptor type differs from v102 verified layout");return;}
        ArrayDataType desired=new ArrayDataType(ds,ROWS,STRIDE);Data existing=currentProgram.getListing().getDataAt(begin);
        if(existing!=null && equivalent(existing.getDataType(),desired)){done(id);return;}
        if(existing==null){preserve(id,"missing original row-zero data");return;}
        // Guard original binary values for the exact 27-entry table and class-1 pointers.
        if(currentProgram.getMemory().getInt(begin.add(3*STRIDE))!=1 ||
            currentProgram.getMemory().getInt(toAddr("004F7784"))!=0x00463120 ||
            currentProgram.getMemory().getInt(toAddr("004F7788"))!=0x00463800 ||
            currentProgram.getMemory().getInt(toAddr("004F778C"))!=0x00463950 ||
            currentProgram.getMemory().getInt(toAddr("004F77A4"))!=0x00463a80){preserve(id,"immutable class-1 sample values mismatch");return;}
        guardTableAnnotations(); Set<String> originalRefs=tableReferences(); int oldOutbound=0,oldPointerFields=0,codePtrs=0;
        List<Object[]> preservedComments=new ArrayList<>();
        for(int i=0;i<ROWS*STRIDE;i+=4){Address here=begin.add(i);CodeUnit unit=currentProgram.getListing().getCodeUnitContaining(here);
            if(unit==null||!(unit instanceof Data) || currentProgram.getListing().getInstructionContaining(here)!=null){preserve(id,"instruction/non-data overlaps at "+here);return;}
            Data data=currentProgram.getListing().getDataAt(here);
            if(data==null){preserve(id,"cross-boundary scalar at "+here);return;}
            if(!eligibleTableScalar(data,i%STRIDE)){preserve(id,"non-scalar original data at "+here);return;}
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
            if(!tableReferences().containsAll(originalRefs))throw new IllegalStateException("Original outgoing table references lost");
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
       for(String[] e:entries){String key=e[0]+" arg"+e[1]+" -> "+e[2];try{Function f=getFunctionAt(toAddr(e[0]));int pos=Integer.parseInt(e[1]);if(f==null||f.getParameterCount()<=pos){preserve(key,"missing function/param");continue;}Parameter p=f.getParameter(pos);DataType target=ptr(w);if(equivalent(p.getDataType(),target)){done(key);continue;}if(!p.getDataType().getName().equals(e[3])||!p.getName().equals("param_1")){preserve(key,"existing signature differs "+p.getName()+" "+p.getDataType().getName());continue;}if(APPLY){p.setDataType(target,SourceType.USER_DEFINED);p.setName(e[2],SourceType.USER_DEFINED);}change("PARAM",key,e[4]);}catch(Exception x){fail(key,x);}}
       String key="00461970 class_id argument";try{Function f=getFunctionAt(toAddr("00461970"));Parameter p=f.getParameter(1);if(p.getName().equals("class_id")){done(key);}else if(!p.getName().equals("param_2")){preserve(key,"analyst label exists");}else{if(APPLY)p.setName("class_id",SourceType.USER_DEFINED);change("PARAM",key,"original 00461970 stores discriminator at world+6C");}}catch(Exception e){fail(key,e);}
    }
    private void classCounters(){String[][] entries={{"0054B20C","g_ENG_PendingClassNodeCount","pending insert +1 at 00461970 and unlink -1 in 00461B80"},{"0054B210","g_ENG_RegisteredClassNodeCount","enrolled list insert +1 at 00461970 and unlink -1 in 00461C80/1D50"}};
      for(String[] row:entries){String key=row[0]+" "+row[1];try{Address ad=toAddr(row[0]);counterFootprint(ad);Data data=currentProgram.getListing().getDataAt(ad);Symbol label=currentProgram.getSymbolTable().getPrimarySymbol(ad);if(label==null||data==null){preserve(key,"missing data");continue;}if(label.getName().equals(row[1])){if(!equivalent(data.getDataType(),UnsignedIntegerDataType.dataType)||data.getLength()!=4)preserve(key,"counter name exists with incompatible type");done(key);continue;}if(label.getSource()!=SourceType.DEFAULT||!ghidra.program.model.data.Undefined.isUndefined(data.getDataType())){preserve(key,"existing analyst name or type");continue;}if(APPLY){label.setName(row[1],SourceType.USER_DEFINED);clearListing(ad,ad.add(3));createData(ad,UnsignedIntegerDataType.dataType);}change("GLOBAL",key,row[2]);}catch(Exception e){fail(key,e);}}
    }

 }
 V100 v100=new V100(); V101 v101=new V101(); V102 v102=new V102();
 boolean validV100Descriptor(Structure s,DataType cb){
  if(s.getLength()!=0x34||s.getDefinedComponents().length!=3)return false;
  String[] names={"initialize","pre_update","post_update"};
  for(int i=0;i<3;i++){var c=s.getComponentAt(8+i*4);if(c==null||!names[i].equals(c.getFieldName())||!equivalent(c.getDataType(),new PointerDataType(cb,currentProgram.getDataTypeManager())))return false;}return true;
 }
 boolean finalTable(){var d=getDataAt(toAddr(0x4f76e0));return d!=null&&d.getDataType() instanceof Array&&equivalent(d.getDataType(),new ArrayDataType(v102.classDesc(),27,0x34));}
 boolean eligibleTableScalar(Data data,int offset){
  DataType dt=data.getDataType();if(data.getLength()==1&&Undefined.isUndefined(dt))return true;
  if(data.getLength()!=4)return false;
  if(Undefined.isUndefined(dt))return true;
  if(offset==0)return dt.getPathName().equals("/int")||dt.getPathName().equals("/uint");
  if(!(dt instanceof Pointer q))return false;
  if(q.getDataType()==null||Undefined.isUndefined(q.getDataType()))return true;
  return equivalent(dt,new PointerDataType(v100.callbackType(null),currentProgram.getDataTypeManager()));
 }
 void guardTableAnnotations(){
  var begin=toAddr(0x4f76e0);var end=toAddr(0x4f7c5b);
  for(var a=begin;a.compareTo(end)<=0;a=a.add(1)){
   if(getInstructionContaining(a)!=null)conflict("TABLE "+a,"instruction overlap");
   for(var s:currentProgram.getSymbolTable().getSymbols(a))if(s.getSource()!=SourceType.DEFAULT&&s.getSource()!=SourceType.ANALYSIS&&!a.equals(begin)&&!a.equals(toAddr(0x4f777c)))conflict("TABLE "+a,"interior analyst label "+s.getName());
  }
 }
 Set<String> tableReferences(){Set<String> refs=new TreeSet<>();for(long va=0x4f76e0;va<=0x4f7c5b;va++)for(var r:currentProgram.getReferenceManager().getReferencesFrom(toAddr(va)))refs.add(r.getFromAddress()+"|"+r.getToAddress()+"|"+r.getReferenceType()+"|"+r.getOperandIndex()+"|"+r.getSource());return refs;}
 String unchangedFunctions(){Set<String> affected=new HashSet<>();for(var r:SIGNATURES)affected.add(r[0]);StringBuilder b=new StringBuilder();var it=currentProgram.getFunctionManager().getFunctions(true);while(it.hasNext()){var f=it.next();if(affected.contains(f.getEntryPoint().toString()))continue;b.append(f.getEntryPoint()+"|"+f.getPrototypeString(false,false)+"|"+f.getCallingConventionName()+"|"+f.hasCustomVariableStorage()+"|"+f.getReturn().getVariableStorage()+"|"+f.getSignatureSource());for(var x:f.getParameters())b.append("|"+x.getName()+":"+x.getDataType().getPathName()+":"+x.getVariableStorage()+":"+x.getSource());b.append("\n");}return b.toString();}
 void counterFootprint(Address a){for(int i=0;i<4;i++){var d=getDataContaining(a.add(i));if(d==null||getInstructionContaining(a.add(i))!=null||d.getMinAddress().compareTo(a)<0||d.getMaxAddress().compareTo(a.add(3))>0)conflict(a.toString(),"counter overlapping data");if(i>0)for(var sym:currentProgram.getSymbolTable().getSymbols(a.add(i)))if(sym.getSource()!=SourceType.DEFAULT)conflict(a.toString(),"counter interior analyst label");}}
 void checkShapes(){for(var row:SHAPES){var t=currentProgram.getDataTypeManager().getDataType(row[0]);if(!(t instanceof Structure s)||t.getLength()!=Integer.parseInt(row[1])){conflict(row[0],"baseline structure missing/extent differs");return;}StringJoiner b=new StringJoiner(";");for(var c:s.getDefinedComponents())b.add(c.getOffset()+":"+c.getFieldName()+":"+c.getDataType().getPathName());if(!row[2].equals(b.toString()))conflict(row[0],"baseline fields differ; preserve analyst layout");}}
 String ruleType(String va,int i){
  for(var r:V100.PARAMS)if(r.va.equalsIgnoreCase(va)&&r.ordinal==i)return "/Interstate76/Research-v99/"+r.structName+" *";
  for(var r:V101.PARAMS)if(r.a.equalsIgnoreCase(va)&&r.i==i)return "/Interstate76/Research-v101/"+r.t+(r.depth==2?" * *":" *");
  if(i==0&&Set.of("00462040","00463a80","0046f2b0","0045f810","0046dfe0").contains(va.toLowerCase()))return "/Interstate76/Research-v101/I76_WorldNode_0xB0 *";
  return null;
 }
 String ruleName(String va,int i){
  for(var r:V100.PARAMS)if(r.va.equalsIgnoreCase(va)&&r.ordinal==i)return r.name;
  for(var r:V101.PARAMS)if(r.a.equalsIgnoreCase(va)&&r.i==i)return r.n;
  if(i==1&&va.equalsIgnoreCase("00461970"))return "class_id";
  if(i==0&&va.equalsIgnoreCase("00463a80"))return "vehicle_root";
  if(i==0&&Set.of("00462040","0046f2b0","0045f810","0046dfe0").contains(va.toLowerCase()))return "world_node";
  return null;
 }
 String returnType(String va){switch(va.toLowerCase()){
  case "00491810":return "/Interstate76/Research-v99/I76_TerrainAdaptiveLeaf_0x1C *";
  case "0045ebd0":case "0045f0f0":return "/Interstate76/Research-v101/I76_WorldNode_0xB0 *";
  case "004572b0":return "/Interstate76/Research-v101/I76_ActiveWorldEntry_0x78 *";
  case "0049c320":return "/Interstate76/Research-v101/I76_ClassLinkNode_0x0C *";
  default:return null;}}
 void checkSignatures(){for(var row:SIGNATURES){String va=row[0];var f=getFunctionAt(toAddr(va));String[] old=row[1].split("\\|",-1);if(f==null)conflict(va,"missing function");
  if(!f.getName().equals(old[0])&&!(va.equals("0045f0f0")&&f.getName().equals("OBJ_ResolveLiveOrReleaseWorldReference")))conflict(va,"analyst function alias differs");
  if(!Objects.equals(f.getCallingConventionName(),old[2])||f.hasCustomVariableStorage()!=Boolean.parseBoolean(old[3])||f.getParameterCount()!=old.length-7)conflict(va,"calling convention/storage/arity conflict");
  String rt=f.getReturnType().getPathName(),want=returnType(va);if(!rt.equals(old[5])&&!rt.equals(want))conflict(va,"return type conflict "+rt);
  String storage=f.getReturn().getVariableStorage().toString();if(!storage.equals(old[6])&&!(want!=null&&rt.equals(want)&&storage.equals("EAX:4")))conflict(va,"return storage conflict "+storage);
  for(int i=0;i<f.getParameterCount();i++){var x=f.getParameter(i);String[] o=old[i+7].split(":",-1);String expectedStorage=String.join(":",Arrays.copyOfRange(o,2,o.length-1));String w=ruleType(va,i),n=ruleName(va,i);
   if(!x.getDataType().getPathName().equals(o[1])&&!x.getDataType().getPathName().equals(w))conflict(va+" arg"+i,"analyst parameter type "+x.getDataType().getPathName());
   if(!x.getName().equals(o[0])&&!x.getName().equals(n))conflict(va+" arg"+i,"analyst parameter name "+x.getName());
   if(!x.getVariableStorage().toString().equals(expectedStorage))conflict(va+" arg"+i,"parameter storage differs "+x.getVariableStorage());
  }
 }}
 void identity()throws Exception{
  if(!"12.1.4".equals(ghidra.framework.Application.getApplicationVersion())||!V100.SHA256.equals(currentProgram.getExecutableSHA256())||!V100.MD5.equals(currentProgram.getExecutableMD5())||currentProgram.getImageBase().getOffset()!=0x400000||currentProgram.getDefaultPointerSize()!=4||!"x86:LE:32:default".equals(currentProgram.getLanguageID().toString()))conflict("IDENTITY","toolchain or retail image mismatch");
  if(!BODY_SHA.equals(originalFunctions()))conflict("ORIGINAL_BODIES","function boundary or original byte mismatch");
  byte[] table=new byte[0x57c];currentProgram.getMemory().getBytes(toAddr(0x4f76e0),table);if(!TABLE_SHA.equals(sha(table)))conflict("TABLE_BYTES","original 27 rows differ");
  if(getInt(toAddr(0x4ed7ec))!=0x00647561)conflict("AUD_BYTES","original literal differs");
 }
 boolean footprint(long va){var a=toAddr(va);var d=getDataAt(a);if(d==null||d.getLength()!=4){conflict(a.toString(),"four-byte definition differs");return false;}for(int j=0;j<4;j++){if(getInstructionContaining(a.add(j))!=null)conflict(a.toString(),"instruction overlap");if(j>0)for(var s:currentProgram.getSymbolTable().getSymbols(a.add(j)))if(s.getSource()!=SourceType.DEFAULT)conflict(a.toString(),"interior annotation");}return true;}
 void terrain()throws Exception{
  footprint(0x6442c0);footprint(0x4ed7ec);
  var a=toAddr(0x6442c0);var sym=currentProgram.getSymbolTable().getPrimarySymbol(a);if(sym==null||!sym.getName().equals("g_TER_GridStep"))conflict("006442C0","spacing alias differs");
  var dt=getDataAt(a).getDataType();if(equivalent(dt,FloatDataType.dataType))report("ALREADY","terrain 006442C0","float");else{if(!dt.getPathName().equals("/int"))conflict("006442C0","incompatible analyst type");report("APPLY","terrain 006442C0","int -> float; original floating consumers");if(APPLY){clearListing(a,a.add(3));createData(a,FloatDataType.dataType);}}
  a=toAddr(0x4ed7ec);dt=getDataAt(a).getDataType();if(equivalent(dt,TerminatedStringDataType.dataType))report("ALREADY","terrain 004ED7EC","terminated aud string");else{if(!dt.getPathName().equals("/pointer"))conflict("004ED7EC","incompatible analyst type");for(var s:currentProgram.getSymbolTable().getSymbols(a))if(s.getSource()!=SourceType.DEFAULT&&s.getSource()!=SourceType.ANALYSIS)conflict("004ED7EC","analyst label");report("APPLY","terrain 004ED7EC","generic pointer -> terminated aud string");if(APPLY){clearListing(a,a.add(3));currentProgram.getListing().createData(a,TerminatedStringDataType.dataType,4);}}
 }
 void stages()throws Exception{
  if(phase.equals("ALL")||phase.equals("TERRAIN"))terrain();
  if(phase.equals("ALL")||phase.equals("V100")){v100.defineCallbacksAndDescriptor();v100.typeParams();v100.leafReturn();v100.installDescriptor();}
  if(phase.equals("ALL")||phase.equals("V101")){v101.createTypes();v101.params();v101.returns();v101.globalHeads();v101.guardedLabel();v101.evidenceComment();}
  if(phase.equals("ALL")||phase.equals("V102")){v102.callbackTypes();v102.descriptorType();v102.partialRuntimeTypes();v102.mapClassTable();v102.typedParams();v102.classCounters();}
 }
 Map<String,String> annotations(){Map<String,String> m=new TreeMap<>();var it=currentProgram.getSymbolTable().getAllSymbols(true);while(it.hasNext()){var s=it.next();if(s.getSource()==SourceType.USER_DEFINED)m.put("S"+s.getID(),s.getAddress()+"|"+s.getName(true)+"|"+s.getSymbolType());}for(int k=0;k<=4;k++){var ci=currentProgram.getListing().getCommentAddressIterator(k,currentProgram.getMemory(),true);while(ci.hasNext()){var a=ci.next();m.put("C"+a+":"+k,currentProgram.getListing().getComment(k,a));}}return m;}
 void preserveAnnotations(Map<String,String> before){var after=annotations();for(var e:before.entrySet()){var v=after.get(e.getKey());if(e.getKey().startsWith("C")){if(v==null||!v.contains(e.getValue()))conflict(e.getKey(),"analyst comment lost");}else if(!Objects.equals(v,e.getValue())){
  if(e.getValue().startsWith("0045f0f0|release_world_object_tree_reference|")&&v!=null&&v.startsWith("0045f0f0|OBJ_ResolveLiveOrReleaseWorldReference|"))continue;
  // Only reviewed parameter renames are permitted by checkSignatures.
  if(v!=null&&e.getValue().endsWith("|Parameter")&&v.endsWith("|Parameter"))continue;
  conflict(e.getKey(),"analyst symbol lost/changed "+e.getValue());
 }}}
 @Override public void run()throws Exception{
  var args=getScriptArgs();String mode=args.length==0?(isRunningHeadless()?"PREVIEW":askChoice("Semantic reconciliation","Preview or explicitly apply on a backed-up program?",List.of("PREVIEW","APPLY"),"PREVIEW")):args[0];phase=args.length<2?"ALL":args[1];
  if(args.length>2||!Set.of("PREVIEW","APPLY").contains(mode)||!Set.of("ALL","TERRAIN","V100","V101","V102").contains(phase))throw new IllegalArgumentException("Use PREVIEW|APPLY [ALL|TERRAIN|V100|V101|V102]");
  APPLY=mode.equals("APPLY");identity();checkShapes();checkSignatures();var before=annotations();String unaffected=unchangedFunctions();
  int tx=-1;boolean committed=false;
  try{if(APPLY)tx=currentProgram.startTransaction("Verified v100-v102 semantic reconciliation");stages();checkpoint();if(APPLY){identity();checkShapes();checkSignatures();preserveAnnotations(before);if(!unaffected.equals(unchangedFunctions()))conflict("UNAFFECTED_SIGNATURES","unrelated signature/storage changed");}committed=true;
  }catch(Exception e){println("CONFLICT/PRESERVE transaction: "+e);throw e;
  }finally{if(tx>=0)currentProgram.endTransaction(tx,committed);println("SUMMARY mode="+mode+" phase="+phase+" eligible="+proposed+" applied="+(APPLY&&committed?proposed:0)+" already="+already+" preserved="+preserved+" conflicted="+conflicted+" deferred="+deferred+" committed="+(APPLY&&committed));}
 }
}
