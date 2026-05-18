/*
 * Program: i76.exe
 * Function: render_game_frame_software_pipeline_debug_timed
 * Entry: 00401cc0
 * Signature: undefined __cdecl render_game_frame_software_pipeline_debug_timed(float * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: High-level frame render pipeline with timing labels such as
   Mirr/Terr/Road/Skid/Sky/Sort/Span/Final; software-style path. */

void __cdecl render_game_frame_software_pipeline_debug_timed(float *param_1)

{
  double dVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  int iVar5;
  undefined3 extraout_var;
  float10 fVar6;
  float10 fVar7;
  float local_24;
  void *local_14;
  undefined *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
                    /* I76 semantic baseline: render_game_frame_software_pipeline_debug_timed
                       High-level software frame render pipeline with timing/debug labels. */
  iVar5 = DAT_004c2724;
  local_8 = 0xffffffff;
  puStack_c = &DAT_004bc460;
  puStack_10 = &DAT_004ba0d0;
  local_14 = ExceptionList;
  ExceptionList = &local_14;
  update_flamer_effect_state();
  if (iVar5 != 0) {
    force_feedback_effect_stop_helper_00445750();
  }
  mark_frame_timing_interval(s_Mirr_004c2120);
  if (DAT_00654b86 != '\0') {
    fill_bitmap_surface_context((int *)&DAT_005dcef4,0);
  }
  local_24 = -param_1[0x12];
  fVar2 = -param_1[0x18];
  fVar3 = local_24 * local_24 + fVar2 * fVar2;
  if (_DAT_004bc44c <= fVar3) {
    dVar1 = (double)fVar3;
    fVar7 = zone_satellite_map_context_helper_00495000
                      (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
    fVar6 = fVar7 * (float10)fVar2;
    local_24 = (float)fVar7 * local_24;
  }
  else {
    local_24 = 0.0;
    fVar6 = (float10)_DAT_004bc454;
  }
  DAT_005dd380 = (float)fVar6;
  DAT_005dd384 = 0;
  _DAT_005dd388 = -local_24;
  _DAT_005dd38c = 0;
  _DAT_005dd390 = 0x3f800000;
  _DAT_005dd394 = 0;
  _DAT_005dd398 = local_24;
  _DAT_005dd39c = 0;
  _DAT_005dd3a0 = (float)fVar6;
  local_8 = 0;
  raster_span_builder_context_helper_00473630();
  i76_runtime_build_visible_adaptive_terrain_mesh((int)param_1);
  mark_frame_timing_interval(s_Terr_004c2118);
  render_dynamic_or_track_geometry_pass_candidate((int)param_1);
  mark_frame_timing_interval(s_Road_004c2110);
  force_feedback_user_entity_lookup_context_helper_00445060((int)param_1);
  mark_frame_timing_interval(s_Skid_004c2108);
  shutdown_flamer_effect_state((int)param_1);
  world_object_geometry_context_helper_00457ff0((int *)param_1);
  load_dust_texture_resource((int)param_1);
  render_projectile_tracer_quads_variant_b((int)param_1);
  hud_bitmap_render_context_helper_0045c380((int)param_1);
  update_world_object_smoke_emitters_and_spawn_particles(param_1);
  (*DAT_005dd2bc)();
  submit_far_scene_horizon_polygon_batch();
  submit_dynamic_geometry_aux_view_polygons();
  mark_frame_timing_interval(s_Sky_004c2100);
  merge_world_object_or_geometry_state(param_1,1);
  mark_frame_timing_interval(s_Sort_004c20f8);
  if ((iVar5 != 0) && (DAT_00654b88 != '\0')) {
    load_gear_indicator_texture(param_1);
  }
  mark_frame_timing_interval(s_Ckpt3_004c20f0);
  raster_span_builder_context_helper_00473640(param_1[0xf]);
  mark_frame_timing_interval(s_Span_004c20e8);
  if (iVar5 == 0) {
    if (DAT_00654b8c._2_1_ == '\0') goto LAB_00401f01;
  }
  else if (DAT_00654b88 != '\0') goto LAB_00401f01;
  load_speedometer_textures(param_1);
LAB_00401f01:
  mark_frame_timing_interval(s_Ckpt2_004c20e0);
  cockpit_gauge_context_helper_0045af10(param_1,0);
  iVar5 = is_damage_side_effects_suppressed();
  if (iVar5 != 0) {
    cockpit_gauge_context_helper_0045bb80((int)param_1);
  }
  local_8 = 0xffffffff;
  bVar4 = system_cutscene_memory_context_helper_00498720();
  if (CONCAT31(extraout_var,bVar4) != 0) {
    system_cutscene_memory_context_helper_00498730((int)param_1);
  }
  mark_frame_timing_interval(s_Final_004c20d8);
  (*DAT_005dd2c0)();
  ExceptionList = local_14;
  return;
}


