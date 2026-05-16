/*
 * Program: i76.exe
 * Function: render_game_frame_d3d_pipeline_debug_timed
 * Entry: 00401fa0
 * Signature: undefined __cdecl render_game_frame_d3d_pipeline_debug_timed(float * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: High-level frame render pipeline with timing labels and
   DirectDraw/D3D surface restore/scene flush calls. */

void __cdecl render_game_frame_d3d_pipeline_debug_timed(float *param_1)

{
  double dVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float local_24;
  void *local_14;
  undefined *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
                    /* I76 semantic baseline: render_game_frame_d3d_pipeline_debug_timed
                       High-level D3D frame render pipeline with timing/debug labels. */
  iVar4 = DAT_004c2724;
  local_8 = 0xffffffff;
  puStack_c = &DAT_004bc470;
  puStack_10 = &DAT_004ba0d0;
  local_14 = ExceptionList;
  ExceptionList = &local_14;
  update_flamer_effect_state();
  if (iVar4 != 0) {
    force_feedback_effect_stop_helper_00445750();
  }
  mark_frame_timing_interval(s_Mirr_004c2120);
  local_24 = -param_1[0x12];
  fVar2 = -param_1[0x18];
  fVar3 = local_24 * local_24 + fVar2 * fVar2;
  if (_DAT_004bc44c <= fVar3) {
    dVar1 = (double)fVar3;
    fVar6 = zone_satellite_map_context_helper_00495000
                      (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
    fVar5 = fVar6 * (float10)fVar2;
    local_24 = (float)fVar6 * local_24;
  }
  else {
    local_24 = 0.0;
    fVar5 = (float10)_DAT_004bc454;
  }
  DAT_005dd380 = (float)fVar5;
  DAT_005dd384 = 0;
  _DAT_005dd388 = -local_24;
  _DAT_005dd38c = 0;
  _DAT_005dd390 = 0x3f800000;
  _DAT_005dd394 = 0;
  _DAT_005dd398 = local_24;
  _DAT_005dd39c = 0;
  _DAT_005dd3a0 = (float)fVar5;
  local_8 = 0;
  terrain_map_context_helper_00490a00((int)param_1);
  mark_frame_timing_interval(s_Terr_004c2118);
  restore_or_acquire_directdraw_surface_if_needed();
  render_dynamic_or_track_geometry_pass_candidate((int)param_1);
  mark_frame_timing_interval(s_Road_004c2110);
  restore_or_acquire_directdraw_surface_if_needed();
  force_feedback_user_entity_lookup_context_helper_00445060((int)param_1);
  restore_or_acquire_directdraw_surface_if_needed();
  shutdown_flamer_effect_state((int)param_1);
  world_object_geometry_context_helper_00457ff0((int *)param_1);
  restore_or_acquire_directdraw_surface_if_needed();
  load_dust_texture_resource((int)param_1);
  render_projectile_tracer_quads_variant_b((int)param_1);
  hud_bitmap_render_context_helper_0045c380((int)param_1);
  update_world_object_smoke_emitters_and_spawn_particles(param_1);
  submit_far_scene_horizon_polygon_batch();
  submit_dynamic_geometry_aux_view_polygons();
  mark_frame_timing_interval(s_Sky_004c2100);
  restore_or_acquire_directdraw_surface_if_needed();
  if ((DAT_00504be8 == 0) && (DAT_005dd2a8 == 1)) {
    submit_display_backend_screen_edge_quads();
  }
  merge_world_object_or_geometry_state(param_1,1);
  mark_frame_timing_interval(s_Sort_004c20f8);
  if ((iVar4 != 0) && (DAT_00654b88 != '\0')) {
    load_gear_indicator_texture(param_1);
  }
  mark_frame_timing_interval(s_Ckpt3_004c20f0);
  if (iVar4 == 0) {
    if (DAT_00654b8c._2_1_ == '\0') goto LAB_004021c8;
  }
  else if (DAT_00654b88 != '\0') goto LAB_004021c8;
  load_speedometer_textures(param_1);
LAB_004021c8:
  mark_frame_timing_interval(s_Ckpt2_004c20e0);
  cockpit_gauge_context_helper_0045af10(param_1,0);
  mark_frame_timing_interval(s_tgtr_004c2128);
  local_8 = 0xffffffff;
  if ((DAT_00504be8 == 0) && (DAT_005dd2a8 == 1)) {
    end_d3d_scene_and_flush_execute_buffer();
  }
  iVar4 = is_damage_side_effects_suppressed();
  if (iVar4 != 0) {
    (*DAT_005dd2bc)();
    cockpit_gauge_context_helper_0045bb80((int)param_1);
    (*DAT_005dd2c0)();
  }
  if (DAT_00504be8 != 0) {
    submit_display_backend_white_edge_test_quads();
    (*DAT_00608bb4)();
  }
  mark_frame_timing_interval(s_Final_004c20d8);
  ExceptionList = local_14;
  return;
}


