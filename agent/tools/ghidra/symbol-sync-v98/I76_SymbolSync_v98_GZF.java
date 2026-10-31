// I76_SymbolSync_v98_GZF.java
// @category Interstate76
// Ghidra 12.1.4 / retail i76.exe. Names are research aliases, NOT recovered original symbols.
// v98 GZF-aware reconciliation, 2026-10-31; verified against two imported GZF archives with Ghidra 12.1.4.
// Uses address-level accepted research; only explicitly reviewed outdated v97 names are overridden.
// Default dry-run, fail-closed executable identity, preserve existing user annotations.
// Review accompanying TSV and README before enabling APPLY.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;
import ghidra.program.model.symbol.SymbolType;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class I76_SymbolSync_v98_GZF extends GhidraScript {
    // Controls: review dry-run output before changing anything.
    private static final boolean APPLY = false;
    private static final boolean INCLUDE_ACCEPTED_RESEARCH = true;
    private static final boolean INCLUDE_HISTORICAL_REVIEW = false;
    // v98 never globally replaces USER_DEFINED symbols; overrides are exact-name allowlisted.
    private static final boolean REPLACE_USER_DEFINED_NAMES = false;
    // Correct four specifically documented obsolete/misleading function labels even if user-defined.
    private static final boolean CORRECT_DOCUMENTED_MISLABELS = true;
    private static final boolean ADD_PROVENANCE_COMMENTS = true;
    private static final boolean CREATE_MISSING_PROVEN_FUNCTIONS = true; // only two exact verified VAs with disassembled prologues
    // Exact previous symbols from the verified v97 GZF, SHA256 b2f76177...
    // These are the only USER_DEFINED names this migration may replace.
    // A changed existing name is PRESERVED, never forced.
    private static final java.util.Map<String,String> EXPECTED_V97_OVERRIDES = new java.util.HashMap<>();
    static {
        EXPECTED_V97_OVERRIDES.put("00437F90", "effect_target_bounds_query_helper_00437f90");
        EXPECTED_V97_OVERRIDES.put("00457FF0", "world_object_geometry_context_helper_00457ff0");
        EXPECTED_V97_OVERRIDES.put("0045F810", "radar_bitmap_context_helper_0045f810");
        EXPECTED_V97_OVERRIDES.put("0045FAF0", "release_radar_context");
        EXPECTED_V97_OVERRIDES.put("00461B80", "dispatch_queued_world_object_class_callbacks");
        EXPECTED_V97_OVERRIDES.put("00463950", "update_optional_vehicle_runtime_visual_state");
        EXPECTED_V97_OVERRIDES.put("00469B00", "parse_world_object_placement_record");
        EXPECTED_V97_OVERRIDES.put("00469F10", "parse_world_object_placement_field_helper_00469f10");
        EXPECTED_V97_OVERRIDES.put("0046D760", "world_object_texture_animation_state_setter_0046d760");
        EXPECTED_V97_OVERRIDES.put("0046F2B0", "initialize_vehicle_suspension_or_wheel_damage_visual");
        EXPECTED_V97_OVERRIDES.put("0046F420", "loaded_resource_cache_release_record_helper_0046f420");
        EXPECTED_V97_OVERRIDES.put("00471400", "graphics_error_ui_graphics_error_dialog_helper_00471400");
        EXPECTED_V97_OVERRIDES.put("00471FD0", "submit_lit_textured_polygon_to_renderer");
        EXPECTED_V97_OVERRIDES.put("00472400", "software_raster_command_context_helper_00472400");
        EXPECTED_V97_OVERRIDES.put("00472990", "software_raster_queue_context_helper_00472990");
        EXPECTED_V97_OVERRIDES.put("00472C10", "visibility_or_raster_queue_test_for_polygon");
        EXPECTED_V97_OVERRIDES.put("00472D30", "raster_scratch_arena_context_helper_00472d30");
        EXPECTED_V97_OVERRIDES.put("0048FAC0", "merge_world_object_or_geometry_state");
        EXPECTED_V97_OVERRIDES.put("0048FE10", "i76_runtime_bin_terrain_polygon_work_record");
        EXPECTED_V97_OVERRIDES.put("00490590", "i76_runtime_alloc_prepare_terrain_polygon_work_record");
        EXPECTED_V97_OVERRIDES.put("004929B0", "terrain_runtime_lookup_context_helper");
        EXPECTED_V97_OVERRIDES.put("00493160", "sample_runtime_terrain_height");
        EXPECTED_V97_OVERRIDES.put("004931C0", "sample_runtime_terrain_packed_word");
        EXPECTED_V97_OVERRIDES.put("00493550", "apply_world_object_transform_to_bounds_or_geometry");
        EXPECTED_V97_OVERRIDES.put("00493C50", "zone_satellite_map_context_helper_00493c50");
        EXPECTED_V97_OVERRIDES.put("00494710", "zone_satellite_map_context_helper_00494710");
        EXPECTED_V97_OVERRIDES.put("00495000", "zone_satellite_map_context_helper_00495000");
        EXPECTED_V97_OVERRIDES.put("0049C7F0", "initialize_runtime_clock_state");
        EXPECTED_V97_OVERRIDES.put("0049CBE0", "initialize_fixedstep_accumulator_interval");
        EXPECTED_V97_OVERRIDES.put("0049CC20", "reset_fixedstep_accumulator_timer");
        EXPECTED_V97_OVERRIDES.put("0049CCA0", "get_fixedstep_accumulator_seconds");
        EXPECTED_V97_OVERRIDES.put("0049D400", "mission_flow_map_context_helper_0049d400");
        EXPECTED_V97_OVERRIDES.put("0049E0F0", "mission_flow_map_context_helper_0049e0f0");
        EXPECTED_V97_OVERRIDES.put("0049E1B0", "mission_flow_map_context_helper_0049e1b0");
        EXPECTED_V97_OVERRIDES.put("004B75A0", "instantiate_part_record_array_with_geo_cache");
        EXPECTED_V97_OVERRIDES.put("004B8A10", "load_palette_luminance_translucency_tables");
        EXPECTED_V97_OVERRIDES.put("00654380", "g_runtime_terrain_arena_cursor");
        EXPECTED_V97_OVERRIDES.put("006543A4", "g_runtime_terrain_render_max_or_far_bound");
        EXPECTED_V97_OVERRIDES.put("006543AC", "g_runtime_terrain_render_min_or_near_bound");
    }

    // If imported executable fingerprint is missing/mismatched, stop instead of guessing.
    private static final String MD5 = "a640ea0097dbb62e0c77b7f2847c7161";
    private static final String SHA256 = "bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3";

    private static class Entry {
        final String kind, va, name, tier, source, note;
        Entry(String kind, String va, String name, String tier, String source, String note) {
            this.kind=kind; this.va=va; this.name=name; this.tier=tier;
            this.source=source; this.note=note;
        }
    }
    private static final Entry[] SYMBOLS = new Entry[] {
        new Entry("F", "004AD6F0", "VEH_ConstructFromVCF", "P", "P-VEH", "Original top-level VCF construction; tested bus and GTSi"),
        new Entry("F", "004B75A0", "VEH_InstantiateVGEO100ByteBodyPart", "P", "P-VEH", "100-byte VGEO body-part path (not 120-byte)"),
        new Entry("F", "004B7800", "VEH_InstantiateVGEO120BytePath", "P", "P-VEH", "Distinct 120-byte instantiation path, not 100-byte body-part path"),
        new Entry("F", "00449680", "GEO_RegisterObjectTextureSlot", "P", "P-VEH", "Owner-specific TMT keyed registration"),
        new Entry("F", "0044AB90", "GEO_DecodeTMTDescriptor", "P", "P-VEH", "Parse/copy TMT descriptor header and frame names"),
        new Entry("F", "0044AC80", "GEO_CreateOwnerTMTSlotRecord", "P", "P-VEH", "Create owner-to-cached-TMT record"),
        new Entry("F", "004469A0", "GEO_LookupOrLoadGeometry", "P", "P-VEH", "Resource lookup and GEO handle creation"),
        new Entry("F", "00446C90", "GEO_ConstructGeometryFromBytes", "P", "P-VEH", "Construct runtime GEO representation from retail data"),
        new Entry("F", "004466C0", "GEO_SelectBodyGeometryGroup", "P", "P-VEH", "Group 0/4/0 caching transition tested on one node"),
        new Entry("F", "00461970", "ENG_RegisterClassNode", "P", "P-ENG", "Original class-node registration"),
        new Entry("F", "0049C320", "ENG_InsertClassListNode", "P", "P-ENG", "Original class-list insertion"),
        new Entry("F", "00461C80", "ENG_DispatchClassPreCallbacks", "P", "P-ENG", "Original descriptor-driven pre traversal"),
        new Entry("F", "00461D50", "ENG_DispatchClassPostCallbacks", "P", "P-ENG", "Original descriptor-driven post traversal"),
        new Entry("F", "0045F0F0", "OBJ_ResolveClassObjectForDispatch", "P", "P-ENG", "Original class-collection object resolver"),
        new Entry("F", "00463120", "VEH_Class1Initialize", "P", "P-ENG", "Class-1 descriptor initializer; selected direct control later confirmed"),
        new Entry("F", "00463800", "VEH_Class1PreUpdate", "P", "P-ENG", "Class-1 descriptor pre callback"),
        new Entry("F", "00463950", "VEH_Class1PostUpdate", "P", "P-ENG", "Correct descriptor post entry, not internal 004639A0"),
        new Entry("F", "0049C920", "ENG_UpdateClockFromTicks", "P", "P-ENG", "Original clock update with supplied GetTickCount"),
        new Entry("D", "004F777C", "g_ENG_Class1Descriptor", "P", "P-ENG", "Original class-1 descriptor row; slots at +8/+C/+10"),
        new Entry("D", "0054B204", "g_ENG_ClassListHead", "P", "P-ENG", "Original class collection head, NOT active world registry"),
        new Entry("D", "0054B208", "g_ENG_ClassPendingListHead", "P", "P-ENG", "Pending entries refer to class nodes, not owners directly"),
        new Entry("F", "00493C50", "MATH_InitializeApproxInvSqrtSeeds", "A", "A-ENG", "Initializes 256-byte reciprocal-sqrt seed table"),
        new Entry("F", "0049C7F0", "ENG_InitializeFrameReciprocals", "A", "A-ENG", "Initializes 20 float reciprocals and clock context"),
        new Entry("F", "0049CBE0", "ENG_InitializeFrameSubdivision", "A", "A-ENG", "Initializes current-frame subdivision rate"),
        new Entry("F", "0049CC20", "ENG_ComputeCurrentFrameSubsteps", "A", "A-ENG", "Bounded current-frame subdivision, not persistent accumulator"),
        new Entry("F", "0049CCA0", "ENG_ConsumeFrameSubstepDuration", "A", "A-ENG", "Current-frame substep duration consumer"),
        new Entry("F", "00494710", "MATH_ApplyVehicleBasisNormalization", "A", "A-ENG", "Observed basis normalization chain"),
        new Entry("F", "00495000", "MATH_ApproxInverseSquareRoot", "A", "A-ENG", "Seed-table inverse-sqrt consumer"),
        new Entry("F", "00461B80", "ENG_InitializePendingClassNodes", "A", "A-ENG", "Pending descriptor-init dispatcher; can stop on STRLKUP"),
        new Entry("F", "0045EBD0", "OBJ_CreateRootWorldObject", "A", "A-VEH", "Original root/world-object creation"),
        new Entry("F", "00465370", "VEH_PreUpdateControllerStage", "A", "A-VEH", "Observed class-1 active-branch controller stage"),
        new Entry("F", "0043A3C0", "VEH_IntegrateRootMotionStage", "A", "A-VEH", "Observed original root-integrator call chain"),
        new Entry("F", "0043BDF0", "VEH_UpdateRootBasisAndVelocity", "A", "A-VEH", "Integrator with vehicle root basis/velocity updates"),
        new Entry("F", "00438FD0", "VEH_RunWheelSuspensionPath", "A", "A-VEH", "Original wheel/suspension path in authentic M06"),
        new Entry("F", "0043A5D0", "VEH_UpdateSuspensionContact", "A", "A-VEH", "Original contact/suspension descendant"),
        new Entry("F", "0046DC10", "VEH_ComputeTireContactMode0", "A", "A-VEH", "Mode-0 tire contact in sampled M06 scenarios"),
        new Entry("F", "00437230", "VEH_ComputeContactNormalBranch", "A", "A-VEH", "Original normal branch reached during tire contact"),
        new Entry("F", "0046D760", "VEH_InitializeSuspensionFilter", "A", "A-VEH", "Filter coefficient warm-up path"),
        new Entry("F", "0049E0F0", "VEH_ComputeSuspensionFilterCoefficient", "A", "A-VEH", "X87 COS-dependent coefficient helper"),
        new Entry("F", "0049E1B0", "VEH_ApplySuspensionFilterRecurrence", "A", "A-VEH", "Filter recurrence for sampled tire states"),
        new Entry("F", "00469B00", "VEH_LoadEngineSoundRegistry", "A", "A-VEH", "engsnd.dat engine-component registry startup"),
        new Entry("F", "00469F10", "VEH_LookupEngineComponentRegistry", "A", "A-VEH", "Engine component ID selection during CDF"),
        new Entry("F", "004B42B0", "MLD_LoadMissionDescriptorBWD2", "A", "A-TER", "Original outer mission descriptor loader"),
        new Entry("F", "004B3DB0", "MLD_DispatchTaggedChunkDescriptors", "A", "A-TER", "Generic 16-byte tagged descriptor parser"),
        new Entry("F", "004B8A10", "TER_LoadWRLDMaterialProperties", "A", "A-TER", "WREV-9 material-record loader"),
        new Entry("F", "00493910", "TER_InitializeTerrainFromTDEF", "A", "A-TER", "Original terrain/TDEF startup entry"),
        new Entry("F", "00471400", "TER_OpenOrMapTerrainResource", "A", "A-TER", "Original mapped terrain-file wrapper; Win32 supplied"),
        new Entry("F", "00493080", "TER_InitializeTerrainPageGrid", "A", "A-TER", "Installs step reciprocal and TER page pointer grid"),
        new Entry("F", "00493550", "TER_SampleBilinearHeightXZ", "A", "A-TER", "CORRECTION: bilinear low12 height (x87 ST0), NOT transform/bounds"),
        new Entry("F", "004927B0", "TER_SamplePackedMaterialXZ", "A", "A-TER", "Sample material bits15..13; bit12 unresolved"),
        new Entry("F", "004931C0", "TER_SampleSurfaceNormalXZ", "A", "A-TER", "CORRECTION: computed normal, NOT material word"),
        new Entry("F", "00440740", "TER_ProbeSpecialFourPointSurface", "A", "A-TER", "Tested zero for upright cases, not general polygon contact"),
        new Entry("F", "0043E530", "TER_QueryGeneralSurface", "A", "A-TER", "Static polygon-candidate versus heightfield fallthrough; ownership unproved"),
        new Entry("D", "00655180", "g_MATH_ApproxInvSqrtSeedTable", "A", "A-ENG", "256-byte seed table initialized by 00493C50"),
        new Entry("D", "005A7E20", "g_ENG_FrameReciprocalTable", "A", "A-ENG", "Twenty reciprocal float entries"),
        new Entry("D", "005A7E1C", "g_ENG_FrameReciprocalContext", "A", "A-ENG", "Adjacent time counter context"),
        new Entry("D", "004FE420", "g_ENG_FrameDeltaSeconds", "A", "A-ENG", "Delta used by vehicle and camera"),
        new Entry("D", "00644220", "g_TER_WorldMaterialProperties", "A", "A-TER", "WRLD WREV-9 material table, not page data"),
        new Entry("D", "006442C0", "g_TER_GridStep", "A", "A-TER", "Original grid step 5"),
        new Entry("D", "006442C4", "g_TER_GridStepReciprocal", "A", "A-TER", "Original step reciprocal float 0.2"),
        new Entry("D", "00644380", "g_TER_TerrainPagePointerGrid", "A", "A-TER", "16384 terrain pointer-grid entries; 16 backed TER pages in M06"),
        new Entry("F", "0049C360", "ENG_RemovePendingClassListNode", "A", "A-SELECT", "Original pending-node unlink after completed init"),
        new Entry("F", "0046D820", "VEH_ClassTireInitialize", "A", "A-SELECT", "Class tire descriptor initializer"),
        new Entry("F", "0046F2B0", "VEH_Class31InitializeAnimation", "A", "A-SELECT", "Initializes animation consumed by class31 post"),
        new Entry("F", "0046F420", "VEH_Class31PostUpdateAnimation", "A", "A-SELECT", "CORRECTION: consumes initialized animation; not resource release"),
        new Entry("F", "0045F810", "VEH_Class34InitializeRootLink", "A", "A-SELECT", "Initializes root/self linkage consumed by class34 post"),
        new Entry("F", "0045FAF0", "VEH_Class34PostUpdate", "A", "A-SELECT", "Post callback consumes class34 root/self linkage"),
        new Entry("F", "0046DFE0", "VEH_Class32InitializeDamageChild", "A", "A-SELECT", "Pending initialization stops at unresolved localization dependency"),
        new Entry("F", "0049D400", "MATH_ComputeSineCosineX87Helper", "A", "A-SELECT", "Original trig helper containing FSINCOS at 0049D409"),
        new Entry("F", "00405970", "RND_InitializeCameraProjection", "A", "A-RND02", "Original viewport/camera setup, copies 118 dwords"),
        new Entry("F", "00406AB0", "RND_UpdateSelectedVehicleCamera", "A", "A-RND02", "Original selected vehicle camera callback; controlled direct invokes"),
        new Entry("F", "00437F90", "RND_BuildVehicleCameraBasis", "A", "A-RND02", "Original camera basis/smoothing computation"),
        new Entry("F", "00472400", "RND_BuildProjectionState", "A", "A-RND02", "Projection builder used by camera callbacks"),
        new Entry("F", "00472990", "RND_ApplyCameraViewTransform", "A", "A-RND02", "Original persistent view record writer"),
        new Entry("F", "00472D30", "RND_TransformPointUsingInverseView", "A", "A-RND02", "Bounded inverse-view point outputs from original record"),
        new Entry("D", "004C2730", "g_RND_PersistentCameraView", "A", "A-RND02", "Full 472-byte camera record, not 432"),
        new Entry("D", "004C2908", "g_RND_SelectedCameraActiveWorldEntry", "A", "A-RND02", "Adjacent active-entry pointer outside view record"),
        new Entry("D", "004C2964", "g_RND_CameraAngularHistory", "A", "A-RND02", "Camera history outside persistent view record"),
        new Entry("D", "0052B93C", "g_RND_CameraSmoothingHistory", "A", "A-RND02", "Smoothing history outside view record"),
        new Entry("D", "004FE428", "g_RND_CameraTimeScaleConstant", "A", "A-RND02", "Retail mapped .06 in controlled camera sequence"),
        new Entry("D", "004C2728", "g_RND_CameraMode", "A", "A-RND02", "Controlled mapped zero in selected callback sequence"),
        new Entry("D", "00536770", "g_RND_CameraAngleInput0", "A", "A-RND02", "Supplied integer angle input 0, positional semantics unverified"),
        new Entry("D", "00536778", "g_RND_CameraAngleInput1", "A", "A-RND02", "Supplied integer angle input 1, positional semantics unverified"),
        new Entry("D", "00536780", "g_RND_CameraAngleInput2", "A", "A-RND02", "Supplied integer angle input 2, positional semantics unverified"),
        new Entry("F", "00457FF0", "RND_ProduceVisibleWorldWorkRecords", "A", "A-RND01", "Original registered-world producer with positive kind-6 record"),
        new Entry("F", "00472C10", "RND_ClassifyObjectAgainstView", "A", "A-RND01", "Observed visible/behind classifier, result zero accepts"),
        new Entry("F", "0048FE10", "RND_InsertDepthBucketWorkRecord", "A", "A-RND01", "Original work arena/bucket insertion"),
        new Entry("F", "00490590", "RND_AllocateWorkRecordFromArena", "A", "A-RND01", "Original record arena allocation/initialization"),
        new Entry("F", "0048F9B0", "RND_InitializeWorkArenas", "A", "A-RND03", "Five original allocation requests and bucket tables"),
        new Entry("F", "0048FAC0", "RND_ConsumeDepthBucketQueue", "A", "A-RND03", "Original queue consumption from same producer-emulator state"),
        new Entry("F", "0048F4C0", "RND_ConsumeKind6Record", "A", "A-RND03", "Kind-6 dispatch to geometry traversal"),
        new Entry("F", "00490640", "RND_ConsumeKind10Record", "A", "A-RND03", "Kind-10 dispatch/face path in bounded integrated scene"),
        new Entry("F", "0045D530", "GEO_TraverseSecondaryRenderGeometry", "A", "A-RND03", "Consumes original kind-6 subrecord to geometry traversal"),
        new Entry("F", "0045CBE0", "GEO_BuildRenderPolygonFromGeometry", "A", "A-RND03", "Observed retail GEO construction and polygon wrapper path"),
        new Entry("F", "00471FD0", "RND_EmitPolygonWrapper", "A", "A-RND03", "Actual polygon wrapper invoked; clipping/draw intercepted"),
        new Entry("D", "00542830", "g_OBJ_ActiveWorldRegistry", "A", "A-RND03", "First active-world entry; not class callback list"),
        new Entry("D", "0054A25C", "g_OBJ_ActiveWorldEntryCount", "A", "A-RND03", "Active-world entry count distinct from class list"),
        new Entry("D", "00654380", "g_RND_WorkRecordArenaCursor", "A", "A-RND03", "Original work-record arena cursor/bucket state region"),
        new Entry("D", "006543A4", "g_RND_FrameFarDepthBound", "A", "A-RND03", "Supplied 4095 for integrated bucket scanning; original scheduler unknown"),
        new Entry("D", "006543AC", "g_RND_FrameNearDepthBound", "A", "A-RND03", "Observed near bound; full frame initialization not proved"),
        new Entry("F", "00490A00", "TER_BuildAdaptiveVisibleTerrain", "A", "A-RND05", "Original adaptive M06 visual primitive producer, not contact/triangles"),
        new Entry("F", "004929B0", "TER_ComputeVisibleTerrainBounds", "A", "A-RND05", "Original visible terrain bounds/height guard"),
        new Entry("F", "004911E0", "TER_SubdivideVisibleTerrainQuads", "A", "A-RND05", "Adaptive plane/material/error subdivision"),
        new Entry("F", "00491810", "TER_AllocateVisibleTerrainLeaf", "A", "A-RND05", "Original 0x1C-byte leaf primitive alloc/init"),
        new Entry("F", "004918B0", "TER_AllocateVisibleTerrainEdge", "A", "A-RND05", "Original edge allocation in adaptive builder"),
        new Entry("F", "004918F0", "TER_SplitVisibleTerrainEdge", "A", "A-RND05", "Shared edge midpoint splitter"),
        new Entry("F", "00493160", "TER_ReadPackedTerrainGridWord", "A", "A-RND05", "Original page grid lookup/low12 word for visible heights"),
        new Entry("D", "005DD320", "g_RND_VertexScratchBuffer", "A", "A-RND05", "Source-coordinate vertex-buffer pointer in terrain run"),
        new Entry("D", "005DD324", "g_RND_WorkArenaBase", "A", "A-RND05", "Companion work/terrain arena base pointer in terrain run"),
        new Entry("D", "005DD2EC", "g_TER_VisibleTerrainAuxXZBuffer", "A", "A-RND05", "Auxiliary source XZ buffer pointer"),
        new Entry("D", "0059C560", "g_TER_VisibleTerrainFirstLeaf", "A", "A-RND05", "First leaf linked list pointer"),
        new Entry("D", "0059C574", "g_TER_VisibleTerrainLastLeaf", "A", "A-RND05", "Last leaf linked list pointer"),
        new Entry("F", "0040A320", "FSM_RunMissionFrameIfEnabled", "H", "H-FSM", "Historical static mission frame/gates"),
        new Entry("F", "004149F0", "FSM_UpdateCooperativeScriptScheduler", "H", "H-FSM", "Historical mission VM cooperative scheduler"),
        new Entry("F", "00414670", "FSM_DispatchScriptInterpreter", "H", "H-FSM", "Historical interpreter/host ABI"),
        new Entry("F", "00412CE0", "FSM_DispatchScriptHostCommand", "H", "H-FSM", "Historical host handler"),
        new Entry("F", "00412830", "AI_EvaluateBehaviorTransition", "H", "H-FSM", "Historical AI behavior transition evaluator"),
        new Entry("F", "00412680", "AI_SelectWeightedBehavior", "H", "H-FSM", "Historical weighted selector"),
        new Entry("F", "0041FC40", "AI_ConsumeDriveControlQueue", "H", "H-FSM", "Historical drive-control queue consumption"),
        new Entry("F", "0041F8E0", "AI_ApplyQueuedDriveControl", "H", "H-FSM", "Historical queue-to-control conversion"),
        new Entry("F", "0041FCE0", "AI_CheckDriveControlDone", "H", "H-FSM", "Historical non-consuming drained flag reader"),
        new Entry("F", "004155F0", "AI_AdvanceDamageEpoch", "H", "H-FSM", "Historical damage epoch advance"),
        new Entry("F", "00409980", "OBJ_OnWorldObjectUnregister", "H", "H-FSM", "Historical FSM invalidation callback"),
        new Entry("F", "00409BD0", "OBJ_RegisterUnregisterCallback", "H", "H-FSM", "Historical world callback registration"),
        new Entry("F", "004572B0", "OBJ_RegisterActiveWorldEntry", "H", "H-OBJ", "Original active-world registry; multiple accepted investigations"),
        new Entry("F", "00457420", "OBJ_UnregisterActiveWorldEntryAndRelease", "H", "H-OBJ", "Historical counted release after callbacks"),
        new Entry("F", "00462040", "VEH_DispatchClassDamage", "H", "H-OBJ", "Historical 13-slot class damage dispatcher"),
        new Entry("F", "00463A80", "VEH_HandleClass1VehicleDamage", "H", "H-OBJ", "Historical class-1 damage callback"),
        new Entry("F", "00465AF0", "VEH_ApplyPartDamage", "H", "H-OBJ", "Historical part damage/death flag update"),
        new Entry("F", "00466180", "VEH_PropagateCatastrophicWorldDeath", "H", "H-OBJ", "Historical catastrophic damage death propagation"),
        new Entry("D", "0054A178", "g_OBJ_NameRegistryContext", "H", "H-FSM", "Historical 16-byte registry context initialized by 004AD410"),
        new Entry("D", "004C3E50", "g_AI_BehaviorDescriptorTable", "H", "H-FSM", "Historical 34 rows stride 0x1354"),
        new Entry("D", "00524550", "g_AI_DamageEpoch", "H", "H-FSM", "Historical mission-frame damage epoch"),
        new Entry("D", "005A7E14", "g_FSM_ElapsedMissionClock", "H", "H-FSM", "Historical mission deadline accumulator"),
        new Entry("D", "0051F640", "g_FSM_MissionFrameGate", "H", "H-FSM", "Historical mission update gate"),
        new Entry("D", "0051F5C0", "g_FSM_SecondaryMissionFrameGate", "H", "H-FSM", "Historical mission update gate"),
        new Entry("F", "004937C0", "TER_TransformVisibleTerrainPrimitives", "H", "H-TER", "Static downstream transform entry; M-RND-05 stopped before execution"),
        new Entry("F", "00472220", "RND_BuildCameraProjectionMatrix", "H", "H-RND", "Older camera/type-10 evidence; defer corroboration"),
        new Entry("F", "0045D100", "GEO_TraversePrimaryRenderGeometry", "H", "H-RND", "Historical traversal entry; kind-6 subrecord uses secondary"),
        new Entry("F", "0048F2B0", "RND_ProduceKind10FaceRecord", "H", "H-RND", "Older type-10 route; precise semantics bounded"),
        new Entry("F", "00491A30", "TER_WalkAdaptivePrimitiveLeafList", "H", "H-RND", "Static visible terrain leaf walker, not executed by M-RND-05"),
        new Entry("F", "004922F0", "TER_EmitSoftwareTerrainPolygonWork", "H", "H-RND", "Static callback-controlled terrain polygon path"),
        new Entry("F", "004923F0", "TER_PrepareAlternateTerrainPolygon", "H", "H-RND", "Static alternate polygon path"),
        new Entry("F", "004924B0", "TER_EmitAlternateTerrainPolygonWork", "H", "H-RND", "Static alternate polygon emitter"),
        new Entry("D", "00654B8B", "g_TER_VisibleTerrainOutputModeByte", "H", "A-RND05", "Static output-mode selector; downstream paths unexecuted"),
        new Entry("D", "004FACA8", "g_RND_WorkRecordKindDispatchTable", "H", "H-RND", "Kind-specific consumer dispatch"),
        new Entry("D", "004FACF8", "g_RND_WorkRecordKindSizeTable", "H", "H-RND", "Kind-6 size 0x28 + 0x1C header"),
        new Entry("D", "0052B94C", "g_TER_CollisionCandidateList", "H", "A-TER", "Historical candidate list; population bridge unresolved"),
        new Entry("D", "00644200", "g_TER_SceneRegisteredPolygonList", "H", "A-TER", "Historical separate list; population bridge unresolved"),
        new Entry("D", "005DB988", "g_TER_RoadSegmentListHead", "H", "A-TER", "Historical RSEG road-strip list"),
        new Entry("D", "005DB98C", "g_TER_RoadSegmentListTail", "H", "A-TER", "Historical RSEG road-strip list tail"),
    };

    private int changed=0, same=0, proposed=0, skipped=0, errors=0;

    private boolean enabled(Entry e) {
        return "P".equals(e.tier) || ("A".equals(e.tier) && INCLUDE_ACCEPTED_RESEARCH)
            || ("H".equals(e.tier) && INCLUDE_HISTORICAL_REVIEW);
    }
    private void line(String result, Entry e, String detail) {
        printf("%-12s %s %-10s %-46s old/result=%s  source=%s\n",
            result, e.va, e.kind + ":" + e.tier, e.name, detail, e.source);
    }
    private void verifyProgram() throws Exception {
        if (currentProgram == null) throw new Exception("No active Ghidra program");
        String md5 = currentProgram.getExecutableMD5();
        String sha = currentProgram.getExecutableSHA256();
        if (md5 == null || !MD5.equalsIgnoreCase(md5.trim()))
            throw new Exception("Retail i76.exe MD5 missing or unexpected: " + md5);
        if (sha != null && !sha.trim().isEmpty() && !SHA256.equalsIgnoreCase(sha.trim()))
            throw new Exception("Retail i76.exe SHA256 mismatch: " + sha);
        if (currentProgram.getImageBase().getOffset() != 0x00400000L)
            throw new Exception("Image base must be 00400000; current=" + currentProgram.getImageBase());
        if (currentProgram.getDefaultPointerSize() != 4 ||
            !currentProgram.getLanguageID().toString().toLowerCase(Locale.ROOT).contains("x86"))
            throw new Exception("This script applies only to the retail x86 32-bit game");
        println("Program identity verified: " + currentProgram.getName() +
            " MD5=" + md5 + " imageBase=" + currentProgram.getImageBase());
    }
    private boolean documentedCorrection(Entry e) {
        return e.va.equals("00493550") || e.va.equals("004931C0") ||
            e.va.equals("00463950") || e.va.equals("0046F420");
    }
    private boolean okayToReplace(Symbol sym, Entry e) {
        if (sym == null) return true;
        SourceType source = sym.getSource();
        if (source == SourceType.DEFAULT || source == SourceType.ANALYSIS) return true;
        // No blanket renaming of existing analyst conclusions; fail closed on drift.
        if (source != SourceType.USER_DEFINED) return false;
        String expected = EXPECTED_V97_OVERRIDES.get(e.va);
        return expected != null && expected.equals(sym.getName());
    }
    private Address address(String va) {
        return currentProgram.getAddressFactory().getDefaultAddressSpace()
            .getAddress(Long.parseLong(va,16));
    }
    private void commentProvenance(Address a, Entry e) {
        if (!ADD_PROVENANCE_COMMENTS) return;
        CodeUnit cu = currentProgram.getListing().getCodeUnitContaining(a);
        if (cu == null) return;
        String tag = "I76_SYMBOL_SYNC " + e.kind + " tier=" + e.tier +
            " evidence=" + e.source + " (research alias, not original symbol)";
        String prior = cu.getComment(CodeUnit.PLATE_COMMENT);
        if (prior != null && prior.contains(tag)) return;
        cu.setComment(CodeUnit.PLATE_COMMENT,
            (prior == null || prior.isEmpty() ? "" : prior + "\n") + tag);
    }
    private void process(Entry e) {
        if (!enabled(e)) { skipped++; return; }
        Address a = address(e.va);
        if (!currentProgram.getMemory().contains(a)) {
            line("NO_MEMORY", e, "address missing"); skipped++; return;
        }
        Symbol target;
        try {
            if ("F".equals(e.kind)) {
                Function f = currentProgram.getFunctionManager().getFunctionAt(a);
                if (f == null) {
                    // Two original-instruction entry points are disassembled, but missing
                    // function definitions in the verified v97 GZF. Do not force a body.
                    if (CREATE_MISSING_PROVEN_FUNCTIONS &&
                        (e.va.equals("00406AB0") || e.va.equals("00490640")) &&
                        currentProgram.getFunctionManager().getFunctionContaining(a) == null) {
                        Instruction first = currentProgram.getListing().getInstructionAt(a);
                        String expectedPrologue = e.va.equals("00406AB0") ? "SUB ESP,0xd4" : "SUB ESP,0x32c";
                        if (first != null && first.toString().equalsIgnoreCase(expectedPrologue)) {
                            if (!APPLY) {
                                line("PROPOSE_CREATE", e, "disassembled verified entry, no function containing");
                                proposed++; return;
                            }
                            Function created = createFunction(a, e.name);
                            if (created == null || !created.getEntryPoint().equals(a)) {
                                line("ERROR", e, "function creation failed, no code deleted");
                                errors++; return;
                            }
                            commentProvenance(a,e);
                            line("CREATED", e, "new function definition");
                            changed++; return;
                        }
                    }
                    line("NOT_FUNCTION", e, "no verified function START at VA; preserved"); skipped++; return;
                }
                target = f.getSymbol();
            } else {
                if (currentProgram.getListing().getInstructionContaining(a) != null) {
                    line("CODE_AT_DATA", e, "would label instruction"); skipped++; return;
                }
                Data d = currentProgram.getListing().getDataContaining(a);
                if (d != null && !a.equals(d.getMinAddress())) {
                    line("DATA_INTERIOR", e, "inside existing defined data"); skipped++; return;
                }
                target = currentProgram.getSymbolTable().getPrimarySymbol(a);
                if (target != null && target.getSymbolType() == SymbolType.FUNCTION) {
                    line("FUNCTION_AT_DATA", e, target.getName()); skipped++; return;
                }
            }
            String old = target == null ? "<none>" : target.getName();
            if (e.name.equals(old)) {
                line("ALREADY", e, old); same++; return;
            }
            if (!okayToReplace(target, e)) {
                line("PRESERVED", e, old + " [source=" + target.getSource() + "]");
                skipped++; return;
            }
            if (!APPLY) {
                line("PROPOSED", e, old); proposed++; return;
            }
            if ("F".equals(e.kind)) {
                Function f = currentProgram.getFunctionManager().getFunctionAt(a);
                f.setName(e.name, SourceType.USER_DEFINED);
            } else if (target != null) {
                target.setName(e.name, SourceType.USER_DEFINED);
            } else {
                Symbol s = currentProgram.getSymbolTable().createLabel(a, e.name,
                    SourceType.USER_DEFINED);
                s.setPrimary();
            }
            commentProvenance(a,e);
            line("RENAMED", e, old); changed++;
        } catch (Exception ex) {
            line("ERROR", e, ex.getClass().getSimpleName() + ": " + ex.getMessage());
            errors++;
        }
    }
    @Override
    protected void run() throws Exception {
        verifyProgram();
        println("Review 004639A0 separately: it is NOT the class-1 post callback entry; 00463950 is.");
        println("I76 Symbol Sync: APPLY="+APPLY+", accepted="+INCLUDE_ACCEPTED_RESEARCH+
            ", historical="+INCLUDE_HISTORICAL_REVIEW+
            ", guarded-v97-overrides="+EXPECTED_V97_OVERRIDES.size()+
            ", documented-corrections="+CORRECT_DOCUMENTED_MISLABELS);
        if (!APPLY) {
            for (Entry e: SYMBOLS) { monitor.checkCancelled(); process(e); }
        } else {
            int transaction = currentProgram.startTransaction("I76 evidence-backed symbol synchronization");
            boolean commit = false;
            try {
                for (Entry e: SYMBOLS) { monitor.checkCancelled(); process(e); }
                commit = errors == 0;
            } finally {
                currentProgram.endTransaction(transaction, commit);
                if (!commit) println("Apply rolled back: errors or cancellation");
            }
        }
        printf("I76 Symbol Sync summary: total=%d changed=%d proposed=%d already=%d skipped=%d errors=%d\n",
            SYMBOLS.length, changed, proposed, same, skipped, errors);
        if (errors > 0) println("Errors occurred. Review output and undo/restore as needed.");
    }
}
