// I76_SemanticPass_v99.java
// @category Interstate76
// Retail i76.exe; Ghidra 12.1.4; semantic pass on verified v98 GZF.
// Research aliases, NOT recovered original developer identifiers.
// Default dry run. Preserve user-authored names/types and existing code/data.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.util.*;

public class I76_SemanticPass_v99 extends GhidraScript {
    private static final boolean APPLY = false;
    // Structure types are registered, not imposed on the original .data blocks.
    private static final boolean DEFINE_PARTIAL_STRUCTURES = true;
    private static final boolean RENAME_DEFAULT_PARAMETERS = true;
    private static final boolean APPLY_CONFIRMED_SCALAR_TYPES = true;
    private static final boolean CORRECT_BILINEAR_X87_RETURN = true;
    private static final boolean ADD_EVIDENCE_COMMENTS = true;
    // Only install concrete data where EVERY original byte is undefined and there are no interior user symbols.
    private static final boolean INSTALL_SAFE_CAMERA_AND_SHADE_LAYOUTS = true;
    private static final String PE_MD5 = "a640ea0097dbb62e0c77b7f2847c7161";
    private static final String PE_SHA256 = "bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3";
    private static final CategoryPath TYPES = new CategoryPath("/Interstate76/Research-v99");

    private int changed=0, already=0, skipped=0, errors=0;
    private final List<String> failures=new ArrayList<>();
    private static final class Param {
        String addr; int index; String name; String type; String evidence;
        Param(String a,int i,String n,String t,String e) { addr=a;index=i;name=n;type=t;evidence=e; }
    }
    private static final Param[] PARAMS = {
        new Param("00493550",0,"world_x","","TER sampler; M06 physics evidence #51"),
        new Param("00493550",1,"world_z","","TER sampler; M06 physics evidence #51"),
        new Param("004927B0",0,"world_x","","packed material sampler; #51"),
        new Param("004927B0",1,"world_z","","packed material sampler; #51"),
        new Param("00493160",0,"sample_x","","source pointer-grid sampler; #69/#78"),
        new Param("00493160",1,"sample_z","","source pointer-grid sampler; #69/#78"),
        new Param("00490A00",0,"camera_view","","original visual terrain builder #69/#76"),
        new Param("004929B0",0,"camera_view","","original terrain visible-bounds selection #76"),
        new Param("00457FF0",0,"camera_view","","original visibility producer #66/#70"),
        new Param("0048FE10",0,"view_depth","","depth-based original bucket insert #66/#70"),
        new Param("0048FAC0",0,"camera_view","","original bucket consumer #70/#80"),
        new Param("00472C10",0,"camera_view","","original view classification #67/#70"),
        new Param("00472C10",1,"sphere_center_xyz","","original frustum sphere classifier #66/#70"),
        new Param("00472C10",2,"sphere_radius","","original frustum sphere classifier #66/#70"),
        new Param("004918F0",0,"shared_edge","","original edge splitting #69"),
        new Param("004791E0",0,"palette_context","","shade-column producer #81/#84"),
        new Param("004791E0",1,"optional_luminance_table","","nullable copy branch #81/#84"),
        new Param("004796A0",0,"red","","nearest ACT color lookup #81/#84"),
        new Param("004796A0",1,"green","","nearest ACT color lookup #81/#84"),
        new Param("004796A0",2,"blue","","nearest ACT color lookup #81/#84"),
        new Param("00474C60",0,"surface_descriptor","","13-dword software surface constructor #77/#79"),
        new Param("00474C60",1,"byte_pitch","","original constructor writes field +0 #77/#79"),
        new Param("00474C60",2,"height_rows","","original constructor derives width*height and max Y #77/#79"),
        new Param("00474C60",3,"optional_backing_pixels","","original constructor uses caller buffer or HeapAlloc #77/#79"),
        new Param("00474C60",4,"pixel_format_mode","","source mode==1 doubles allocation; exact format unresolved #77/#79"),
        new Param("0047CB00",0,"draw_command","","source reads +0x18,+0x30,+0x58 from 0x60-byte draw command #75/#79"),
        new Param("0047CB00",1,"surface_descriptor","","source reads byte pitch +0 and offsets +0x14/+0x1C from caller surface #77/#81"),
        new Param("00463120",0,"vehicle_root","ptr-from-float","class-1 selected init owns original world object #64"),
        new Param("00463800",0,"vehicle_root","","descriptor class-1 pre callback #58/#62"),
        new Param("00463950",0,"vehicle_root","ptr-from-int","descriptor class-1 post callback #58/#64"),
        new Param("004AD6F0",0,"world_object","","original top-level VCF construction #16"),
        new Param("00449680",0,"world_object_identity","","original per-owner TMT registration #16"),
        new Param("00491810",0,"edge_ref_0","","four source edge references; #69/#78"),
        new Param("00491810",1,"edge_ref_1","","four source edge references; #69/#78"),
        new Param("00491810",2,"edge_ref_2","","four source edge references; #69/#78"),
        new Param("00491810",3,"edge_ref_3","","four source edge references; #69/#78")
    };
    private static final String[][] GLOBALS = {
        {"0061B2A0","g_RND_ShadeLookup256x256","#81/#84; static 65536-byte shade-row by palette-index table"},
        {"0059B388","g_RND_PaletteSquaredDifferenceTable","#81/#84; 512 dword signed-square entries -256..255"},
        {"00654398","g_RND_PolygonRecordArenaBase","#76/#80; original renderer polygon allocation base"}
    };
    // Fix only exact verified v98 aliases that conflict with later original-source ownership.
    private static final String[][] GUARDED_CORRECTIONS = {
        {"00654380","g_RND_WorkRecordArenaCursor","g_TER_AdaptiveEdgeLeafArenaCursor","#69/#80: source edge/leaf allocations use this cursor, distinct from polygon record cursor 006543C0"},
        {"005DD324","g_RND_WorkArenaBase","g_RND_SharedTerrainVehicleScratchBase","#80: terrain edge/leaf arena reused for stock GEO scratch"},
        {"005DD2EC","g_runtime_terrain_vertex_aux_projected_lighting_buffer","g_TER_SourceVertexAuxAlias","#80: pointer aliases upper half of the same 108000-byte XYZ allocation"}
    };
    private static final String[][] LOCALS = {
        {"00493550","local_18","sample_x_index","verified bilinear X lattice integer in decompiled original sampler #51"},
        {"00493550","local_10","sample_z_index","verified bilinear Z lattice integer in decompiled original sampler #51"},
        {"004796A0","local_4","best_palette_index","lowest squared RGB distance candidate cached by original #81"},
        {"0047CB00","local_8","pixel_cursor","original writes indexed shade bytes through this advancing pointer #77/#81"},
        {"0047CB00","local_14","span_blocks_remaining","decrements per 16-pixel unrolled group in original raster #77"},
        {"00474C60","local_1c","raw_allocation","actual HeapAlloc pointer or NULL for caller-owned backing #77"},
        {"00474C60","local_20","aligned_pixel_base","original masks byte pointer to 32-byte alignment #77"},
        {"00474C60","local_10","max_x_inclusive","constructed from byte pitch minus one #77"},
        {"00474C60","local_c","max_y_inclusive","constructed from height minus one #77"}
    };
    private static final String[][] SCALARS = {
        {"004FE420","float","frame delta seconds; #50/#62"},
        {"006442C0","int","M06 source grid step 5; #51/#78"},
        {"006442C4","float","M06 reciprocal grid step 0.2; #51/#78"},
        {"006543A4","float","frame work queue maximum depth bound; #76/#78"},
        {"006543AC","float","frame work queue minimum depth bound; #76/#78"}
    };
    private static final String[][] COMMENTS = {
        {"00493550","#51 original bilinear packed low12 height sampler (X/Z doubles, ST0 result). This is NOT a world transform/bounds helper."},
        {"004931C0","#51 original terrain normal calculation, NOT the packed material word sampler. Packed bit12 remains unresolved."},
        {"00463120","#64 direct selected class-1 init returns; full pending-list selected initialization/input delivery remains unresolved."},
        {"00457FF0","#66/#70 produces original kind-6/10 work records from registered objects. Do not equate active world registry with class callback list."},
        {"00490A00","#69/#74/#76 original adaptive terrain produces source primitives and then emits bin candidates. Rendering/pixels require distinct stages."},
        {"004937C0","#74/#76 original terrain source-to-view transform; a #69 diagnostic stopped BEFORE its entry."},
        {"0048FAC0","#70/#80 consumes original typed work queue and clears buckets; does not prove native terrain pixels."},
        {"0047C8D0","#73 confirmed untextured kind-6 projected polygon path, flag 0x101. Not the old assumed mode-0x15 path."},
        {"0047CE40","#75 confirmed original untextured draw submission, flag 0x01, 0x60-byte command/0x20-byte edges."},
        {"0047CB00","#77/#81 original software 8-bit indexed raster span writer; returned bytes require authenticated palette and materials for color fidelity."},
        {"004791E0","#81/#84 original palette shade table producer for ONE fully observed 256-byte color column; full return not observed."},
        {"004796A0","#81/#84 original nearest-color palette cache indexed by quantized RGB; searches palette entries 0..254."},
        {"004C2730","#67/#76 original retained 0x1D8-byte camera view. Near/far are +0x108/+0x138, not depth bucket bounds."},
        {"00654380","#69/#80 visual terrain leaf/edge arena cursor; distinct from polygon queue cursor 006543C0. Earlier v98 label may conflate them."},
        {"006543A4","#76/#78 terrain-derived depth-bucket maximum, not camera far clipping plane. Some earlier harness values were supplied."},
        {"006543AC","#76/#78 terrain-derived depth-bucket minimum, not camera near clipping plane."},
        {"0061B2A0","#81/#84 0x10000-byte shade lookup table indexed shade*256 + palette index; only one native-produced column proven."},
        {"005DD2EC","#80 original scratch pointer aliases upper half of one 108000-byte source buffer, not an independent allocation."},
        {"005DD324","#80 terrain leaf/edge scratch later reused by vehicle GEO traversal; external backing not retail allocation evidence."}
    };

    private void note(String action,String what,String more) {
        println(String.format("V99 %-12s %-42s %s",action,what,more));
    }
    private void update(String action,String what,String more) { changed++;note(action,what,more); }
    private void keep(String what,String reason){skipped++;note("SKIP",what,reason);}
    private void done(String what){already++;note("ALREADY",what,"");}
    private void fail(String what,Exception e){errors++; failures.add(what+": "+e);note("ERROR",what,e.toString());}
    private boolean identity() {
        boolean ok=PE_MD5.equalsIgnoreCase(currentProgram.getExecutableMD5()) &&
            PE_SHA256.equalsIgnoreCase(currentProgram.getExecutableSHA256()) &&
            "00400000".equalsIgnoreCase(currentProgram.getImageBase().toString()) &&
            "x86:LE:32:default".equals(currentProgram.getLanguageID().getIdAsString());
        note(ok?"VERIFIED":"REJECT","retail executable",currentProgram.getName());
        return ok;
    }
    private void params() {
        if(!RENAME_DEFAULT_PARAMETERS) return;
        for(Param x: PARAMS){String key=x.addr+" arg"+x.index+" -> "+x.name;
            try { Function f=getFunctionAt(toAddr(x.addr)); if(f==null){keep(key,"not a defined function");continue;}
                Parameter[] p=f.getParameters();if(p.length<=x.index){keep(key,"parameter missing");continue;}
                Parameter v=p[x.index]; String old=v.getName();
                if(old.equals(x.name)){
                    if(!x.type.isEmpty() && v.getDataType().getName().equals("float") && x.type.equals("ptr-from-float")){
                        // Handle a partial prior application: do not auto-modify without the expected default name.
                        keep(key,"name already set but type still ambiguous; review manually");
                    } else done(key);
                    continue;
                }
                if(!(old.equals("param_"+(x.index+1)) && v.getSource()==SourceType.DEFAULT)) {keep(key,"preserve analyst parameter '"+old+"'");continue;}
                if(!x.type.isEmpty()) {
                    String required = x.type.equals("ptr-from-float")?"float":"int";
                    if(!v.getDataType().getName().equals(required)){keep(key,"expected "+required+" but found "+v.getDataType().getName());continue;}
                }
                if(APPLY){
                    if(!x.type.isEmpty()) v.setDataType(PointerDataType.dataType,SourceType.USER_DEFINED);
                    v.setName(x.name,SourceType.USER_DEFINED);
                }
                update("PARAM",key,x.evidence);
            }catch(Exception e){fail(key,e);}
        }
    }
    private void guardedCorrections(){
        SymbolTable table=currentProgram.getSymbolTable();
        for(String[] x:GUARDED_CORRECTIONS){String key=x[0]+" "+x[1]+" -> "+x[2];
            try {Symbol sym=table.getPrimarySymbol(toAddr(x[0]));
                if(sym==null){keep(key,"no symbol");continue;}
                if(sym.getName().equals(x[2])){done(key);continue;}
                if(!sym.getName().equals(x[1]) || sym.getSource()!=SourceType.USER_DEFINED){keep(key,"name/source not verified v98; preserve "+sym.getName());continue;}
                if(APPLY)sym.setName(x[2],SourceType.USER_DEFINED);
                update("CORRECTION",key,x[3]);
            }catch(Exception e){fail(key,e);}
        }
    }
    private void renameLocals(){
        for(String[] x:LOCALS){String key=x[0]+" "+x[1]+" -> "+x[2];
            try{Function f=getFunctionAt(toAddr(x[0]));if(f==null){keep(key,"missing function");continue;}
                Variable target=null;boolean alreadyPresent=false;
                for(Variable v:f.getLocalVariables()){
                    if(v.getName().equals(x[2]))alreadyPresent=true;
                    if(v.getName().equals(x[1]))target=v;
                }
                if(alreadyPresent){done(key);continue;}
                if(target==null){keep(key,"existing local not present");continue;}
                if(target.getSource()!=SourceType.DEFAULT){keep(key,"analyst local preserved");continue;}
                if(APPLY)target.setName(x[2],SourceType.USER_DEFINED);
                update("LOCAL",key,x[3]);
            }catch(Exception e){fail(key,e);}
        }
    }
    private void globalNames(){
        SymbolTable syms=currentProgram.getSymbolTable();
        for(String[] x: GLOBALS){String key=x[0]+" -> "+x[1];try{
            Address a=toAddr(x[0]);Symbol s=syms.getPrimarySymbol(a);
            if(s!=null && x[1].equals(s.getName())){done(key);continue;}
            if(s!=null && s.getSource()==SourceType.USER_DEFINED){keep(key,"existing user symbol "+s.getName());continue;}
            if(currentProgram.getListing().getInstructionContaining(a)!=null){keep(key,"code/instruction overlap");continue;}
            if(APPLY)createLabel(a,x[1],true);
            update("GLOBAL",key,x[2]);
        }catch(Exception e){fail(key,e);}}
    }
    private DataType scalarType(String name){return "float".equals(name)?FloatDataType.dataType:IntegerDataType.dataType;}
    private void scalarData(){if(!APPLY_CONFIRMED_SCALAR_TYPES)return;
        for(String[] x:SCALARS){String key=x[0]+" as "+x[1];try{
            Address a=toAddr(x[0]);Data d=currentProgram.getListing().getDataAt(a);DataType want=scalarType(x[1]);
            if(d==null){keep(key,"not a data-start address");continue;}
            if(d.getDataType().isEquivalent(want)){done(key);continue;}
            if(!Undefined.isUndefined(d.getDataType())){keep(key,"preserve pre-existing defined type "+d.getDataType().getName());continue;}
            if(currentProgram.getListing().getInstructionContaining(a)!=null){keep(key,"instruction overlap");continue;}
            boolean safe=true;for(int i=0;i<4;i++){
                Address z=a.add(i);CodeUnit c=currentProgram.getListing().getCodeUnitContaining(z);
                if(!(c instanceof Data) || !Undefined.isUndefined(((Data)c).getDataType())){safe=false;break;}
            }
            if(!safe){keep(key,"4-byte region contains non-undefined data");continue;}
            if(APPLY){clearListing(a,a.add(3));createData(a,want);}
            update("TYPE",key,x[2]);
        }catch(Exception e){fail(key,e);}}
    }
    private void x87Return(){if(!CORRECT_BILINEAR_X87_RETURN)return;
        String key="00493550 bilinear sampler -> float ST0";
        try{Function f=getFunctionAt(toAddr("00493550"));
            if(f==null){keep(key,"not function");return;}
            String old=f.getReturnType().getName();
            if("float".equals(old)){done(key);return;}
            if(!"uint".equals(old) || f.getSignatureSource()==SourceType.USER_DEFINED){keep(key,"existing return "+old+" or analyst signature");return;}
            if(APPLY) f.setReturnType(FloatDataType.dataType,SourceType.USER_DEFINED);
            update("RETURN",key,"#51 executed x87 FPU returns packed terrain height in ST0; decompiler uint was misleading");
        }catch(Exception e){fail(key,e);}
    }
    private void comments(){if(!ADD_EVIDENCE_COMMENTS)return;
        for(String[] x: COMMENTS){String key=x[0]+" evidence";
            try{CodeUnit unit=currentProgram.getListing().getCodeUnitAt(toAddr(x[0]));
                if(unit==null){keep(key,"no code unit");continue;}
                String c=unit.getComment(CodeUnit.REPEATABLE_COMMENT);
                if(c!=null && c.contains(x[1])){done(key);continue;}
                if(c!=null && !c.isEmpty()) {keep(key,"preserve existing repeatable comment");continue;}
                if(APPLY)unit.setComment(CodeUnit.REPEATABLE_COMMENT,"I76 v99: "+x[1]);
                update("COMMENT",key,x[1]);
            }catch(Exception e){fail(key,e);}
        }
    }

    private Structure st(String name,int len,String descr) {
        StructureDataType s=new StructureDataType(TYPES,name,len);
        s.setDescription("I76 original-instruction evidence. Bounded/partial layout; unknown bytes remain undefined. "+descr);
        return s;
    }
    private void fld(Structure s,int off,DataType type,String field,String why){
        s.replaceAtOffset(off,type,type.getLength(),field,why);
    }
    private void ptr(Structure s,int off,String name,String why){fld(s,off,PointerDataType.dataType,name,why);}
    private void u32(Structure s,int off,String name,String why){fld(s,off,UnsignedIntegerDataType.dataType,name,why);}
    private void f32(Structure s,int off,String name,String why){fld(s,off,FloatDataType.dataType,name,why);}
    private void f64(Structure s,int off,String name,String why){fld(s,off,DoubleDataType.dataType,name,why);}
    private void fieldArray(Structure s,int off,DataType el,int count,String name,String why){
        DataType arr=new ArrayDataType(el,count,el.getLength());s.replaceAtOffset(off,arr,arr.getLength(),name,why);
    }
    private List<Structure> makeStructures(){List<Structure> out=new ArrayList<>();
        Structure camera=st("I76_CameraView_0x1D8",0x1d8,"#67/#76; retained 472-byte original view record. Not a full replacement class layout.");
        f32(camera,0x00,"viewport_center_x","#76 original viewport builder 320");
        f32(camera,0x04,"viewport_center_y","#76 original viewport builder 240");
        f32(camera,0x08,"projection_scale_x","#76 original scale +320");
        f32(camera,0x0c,"projection_scale_y","#76 original scale -320");
        f32(camera,0x1c,"viewport_min_x","#76 screen inclusive minimum");
        f32(camera,0x20,"viewport_min_y","#76 screen inclusive minimum");
        f32(camera,0x24,"viewport_max_x","#76 639");
        f32(camera,0x28,"viewport_max_y","#76 479");
        f32(camera,0x2c,"fov_tangent","#76 measured field");
        f32(camera,0x30,"aspect","#76 measured field");
        f32(camera,0x34,"zoom","#67/#76 measured field");
        ptr(camera,0x3c,"viewport_context_ptr","#67 measured original read");
        fieldArray(camera,0x40,FloatDataType.dataType,9,"inverse_orientation_3x3","#67/#76 row/column order documented in reference");
        f64(camera,0x68,"inverse_translation_x","#67 -transpose(R)*position");
        f64(camera,0x70,"inverse_translation_y","#67 -transpose(R)*position");
        f64(camera,0x78,"inverse_translation_z","#67 -transpose(R)*position");
        f64(camera,0x80,"world_frustum_aabb_center_x","#67 independently checked");
        f64(camera,0x88,"world_frustum_aabb_center_y","#67 independently checked");
        f64(camera,0x90,"world_frustum_aabb_center_z","#67 independently checked");
        f64(camera,0x98,"world_frustum_bounding_radius","#67 independently checked");
        fieldArray(camera,0xa0,ByteDataType.dataType,0x60,"frustum_plane_raw","#76 six planes; individual plane fields not yet fully typed");
        f32(camera,0x108,"near_clip_z","#76 0.1 original-projection local corner, NOT depth bucket min");
        f32(camera,0x138,"far_clip_z","#76 150 original-projection local corner, NOT depth bucket max");
        f64(camera,0x160,"source_camera_x","#67/#76 original source world position");
        f64(camera,0x168,"source_camera_y","#67/#76 original source world position");
        f64(camera,0x170,"source_camera_z","#67/#76 original source world position");
        fieldArray(camera,0x178,DoubleDataType.dataType,12,"world_frustum_corners_4x3","#67/#76 four triples of transformed world coordinates");
        out.add(camera);
        Structure work=st("I76_RenderWorkKind6_0x44",0x44,"#66/#70 original kind-6 record; kind-10 has DIFFERENT field meanings.");
        u32(work,0x0c,"record_kind","original store 6");ptr(work,0x14,"next_record","original bucket insertion link");
        ptr(work,0x1c,"world_object_owner","original registered target root");
        f32(work,0x20,"camera_classified_x","#66/#70 cull point");f32(work,0x24,"camera_classified_y","#66/#70 cull point");f32(work,0x28,"camera_classified_z","#66/#70 cull point");
        f32(work,0x2c,"bounding_radius","original source radius");u32(work,0x30,"mode_selector","NOT the bucket index");
        u32(work,0x34,"flags","sampled 0x100");u32(work,0x38,"pass_selector","sampled zero");
        u32(work,0x3c,"cache_state","sampled zero");ptr(work,0x40,"active_world_entry","ONLY kind-6; kind-10 has matrix data here");out.add(work);
        Structure surf=st("I76_SoftwareSurface_0x34",0x34,"#77/#79 original 13-dword software surface descriptor. Raw allocation is provided in tested harness.");
        u32(surf,0,"byte_pitch","#77 observed 640");u32(surf,4,"flags","bit meanings unresolved");
        u32(surf,8,"caller_mode","#77 supplied zero");u32(surf,0xc,"pixel_count_div_4","width*height/4 in tested fixture");
        u32(surf,0x10,"pixel_count_mod_32","#77 measured zero");ptr(surf,0x14,"aligned_pixel_base","#77");ptr(surf,0x18,"backing_allocation","#77");
        u32(surf,0x1c,"x_offset_bytes","#77");u32(surf,0x20,"y_row_offset","#77");
        u32(surf,0x24,"max_x_inclusive","#77 observed 639");u32(surf,0x28,"max_y_inclusive","#77 observed 479");
        u32(surf,0x2c,"owns_backing","#77 measured 1; release details unresolved");out.add(surf);
        Structure draw=st("I76_SoftwareDrawCommand_0x60",0x60,"#75/#79 original 96-byte untextured deferred draw command. Some fields are phase-dependent.");
        u32(draw,0,"call_color_control","sampled zero; exact global meaning not proven");ptr(draw,4,"next_command","deferred list link");
        ptr(draw,8,"span_callback","original 0047CB00");f32(draw,0x18,"shade_plane_constant","original store");u32(draw,0x1c,"control_word","sampled zero");
        ptr(draw,0x20,"left_edge_head","native edge-list chain");ptr(draw,0x24,"right_edge_head","native edge-list chain");
        u32(draw,0x28,"pending_packed_span","signed initial -1; phase-dependent");
        u32(draw,0x30,"extent_or_span_slot","preliminary Y extent becomes pointer later; phase-dependent");
        u32(draw,0x34,"sequence_serial","observed 4/8");f32(draw,0x58,"shade_gradient_x","#75/#79");f32(draw,0x5c,"shade_gradient_y","#75/#79");out.add(draw);
        Structure leaf=st("I76_TerrainAdaptiveLeaf_0x1C",0x1c,"#69/#78 original 28-byte linked adaptive terrain leaf; edge order follows native walker.");
        ptr(leaf,0x08,"next_leaf","original zeroed next on allocation");
        ptr(leaf,0x0c,"edge_walk_reverse_last","#69 walker +0C reverse");
        ptr(leaf,0x10,"edge_walk_forward_second","#69 walker +10 forward");
        ptr(leaf,0x14,"edge_walk_forward_first","#69 walker +14 forward");
        ptr(leaf,0x18,"edge_walk_reverse_third","#69 walker +18 reverse");out.add(leaf);
        Structure proj=st("I76_ProjectVertex_0x18",0x18,"#73/#79 projected software vertex. Unproven UV fields remain undefined.");
        f32(proj,0,"screen_x","original projection");f32(proj,4,"screen_y","original projection");
        f32(proj,8,"reciprocal_z","original projection");u32(proj,0x14,"copied_attribute","original copy; meaning not conclusively UV");out.add(proj);
        Structure root=st("I76_WorldObjectPosePrefix_0x58",0x58,"#49/#67 original world object root pose offsets. This is ONLY an incomplete prefix, not the full object/runtime.");
        fieldArray(root,0x18,FloatDataType.dataType,9,"orientation_basis_3x3","#49/#67 measured 9 float basis entries");
        f64(root,0x40,"position_x","original double world position");f64(root,0x48,"position_y","original double world position");
        f64(root,0x50,"position_z","original double world position");out.add(root);
        Structure desc=st("I76_ClassDescriptor_0x34",0x34,"#58/#62 descriptor table stride 0x34; only callback slots at +8..+10 assigned.");
        ptr(desc,8,"initialize_callback","class-1 original 00463120");ptr(desc,0xc,"pre_callback","class-1 original 00463800");
        ptr(desc,0x10,"post_callback","class-1 original 00463950 NOT 004639A0");out.add(desc);
        return out;
    }
    private void mapSafeGlobals(){
        if(!INSTALL_SAFE_CAMERA_AND_SHADE_LAYOUTS)return;
        String[][] targets={{"004C2730","472","camera"},{"0061B2A0","65536","shade"}};
        for(String[] t:targets){String key=t[0]+" installed "+t[2];try{
            Address a=toAddr(t[0]);int len=Integer.parseInt(t[1]);Data start=currentProgram.getListing().getDataAt(a);
            boolean isCamera=t[2].equals("camera");
            DataType type=isCamera?currentProgram.getDataTypeManager().getDataType(TYPES,"I76_CameraView_0x1D8"):
                new ArrayDataType(ByteDataType.dataType,65536,1);
            if(type==null){if(APPLY){keep(key,"camera type unavailable");continue;}
                type=makeStructures().get(0);
            }
            if(start!=null && !Undefined.isUndefined(start.getDataType()) && start.getDataType().isEquivalent(type)){
                done(key);continue;
            }
            if(start==null || !Undefined.isUndefined(start.getDataType())){keep(key,"preserve existing defined data at start");continue;}
            boolean safe=true;
            for(int i=0;i<len;i++){
                Address b=a.add(i);CodeUnit c=currentProgram.getListing().getCodeUnitContaining(b);
                if(!(c instanceof Data) || !Undefined.isUndefined(((Data)c).getDataType())){safe=false;break;}
                if(i>0)for(Symbol sym:currentProgram.getSymbolTable().getSymbols(b)){
                    if(sym.getSource()!=SourceType.DEFAULT){safe=false;break;}
                }
                if(!safe)break;
            }
            if(!safe){keep(key,"existing defined data, code or interior analyst labels; no action");continue;}
            if(APPLY){
                // Only undefined data can be cleared; all labels at the start remain intact.
                clearListing(a,a.add(len-1));
                createData(a,type);
            }
            update("MAP",key,isCamera?"#67/#76 472-byte persistent camera":"#81/#84 original static 65536-byte shade lookup table");
        }catch(Exception e){fail(key,e);}}
    }
    private void types(){if(!DEFINE_PARTIAL_STRUCTURES)return;
        try{for(Structure s:makeStructures()){
            String key=TYPES+"/"+s.getName();DataType d=currentProgram.getDataTypeManager().getDataType(TYPES,s.getName());
            if(d!=null){if(d instanceof Structure && d.getLength()==s.getLength()){done(key);continue;}
                keep(key,"existing data type mismatch; do not overwrite");continue;}
            if(APPLY)currentProgram.getDataTypeManager().addDataType(s,DataTypeConflictHandler.DEFAULT_HANDLER);
            update("STRUCT",key,"size="+s.getLength()+"; partial fields only, not automatically applied to memory");
        }}catch(Exception e){fail("build structures",e);}
    }
    public void run() throws Exception {
        if(!identity())throw new IllegalStateException("Unsupported executable/GZF; no annotations performed");
        int tx=-1;boolean commit=false;
        try{
            if(APPLY)tx=currentProgram.startTransaction("I76 v99 evidence-backed semantic annotation");
            types();globalNames();guardedCorrections();scalarData();params();x87Return();renameLocals();mapSafeGlobals();comments();
            commit=errors==0;
        }finally{
            if(tx>=0)currentProgram.endTransaction(tx,commit);
        }
        println("I76_V99_SUMMARY APPLY="+APPLY+" changed="+changed+" already="+already+" skipped="+skipped+" errors="+errors+" committed="+(APPLY&&commit));
        if(errors>0)throw new IllegalStateException("Semantic migration failed and rolled back: "+failures);
    }
}
