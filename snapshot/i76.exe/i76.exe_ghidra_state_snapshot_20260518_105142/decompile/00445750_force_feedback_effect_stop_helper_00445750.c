/*
 * Program: i76.exe
 * Function: force_feedback_effect_stop_helper_00445750
 * Entry: 00445750
 * Signature: undefined __stdcall force_feedback_effect_stop_helper_00445750(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: force feedback effect stop helper
   based on prior focused closure context. */

void force_feedback_effect_stop_helper_00445750(void)

{
  int *piVar1;
  int iVar2;
  float *pfVar3;
  int unaff_EBX;
  float unaff_ESI;
  float unaff_EDI;
  float *pfVar4;
  int in_stack_fffffecc;
  float in_stack_fffffed0;
  float *in_stack_fffffed4;
  float *in_stack_fffffed8;
  undefined4 in_stack_fffffedc;
  undefined4 in_stack_fffffee0;
  undefined4 in_stack_fffffee4;
  undefined4 in_stack_fffffee8;
  undefined4 in_stack_fffffeec;
  undefined4 in_stack_fffffef0;
  float local_ec [6];
  float local_d4;
  float local_d0;
  float local_cc;
  float local_64 [16];
  int *local_24;
  uint local_20;
  undefined1 *local_1c;
  void *local_14;
  undefined *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  piVar1 = DAT_00608cbc;
  local_8 = 0xffffffff;
  puStack_c = &DAT_004bd368;
  puStack_10 = &DAT_004ba0d0;
  local_14 = ExceptionList;
  local_1c = &stack0xfffffec0;
  local_20 = (uint)DAT_00654b8c._1_1_;
  if ((local_20 != 0) && (DAT_004f22f8 != 0)) {
    local_24 = DAT_00608cbc;
    if ((DAT_00608cbc != (int *)0x0) && (DAT_00608cbc[0xb] != 0)) {
      ExceptionList = &local_14;
      iVar2 = get_current_texture_cache_generation();
      if (DAT_0052bbc8 <= iVar2) {
        DAT_0052bbc8 = iVar2 + 2;
        if (DAT_004c2908 == (int *)0x0) {
          DAT_004c2908 = (int *)get_active_player_or_camera_world_object_entry();
          if (DAT_004c2908 == (int *)0x0) {
            DAT_004c2908 = (int *)get_active_player_or_camera_world_object_entry();
          }
        }
        iVar2 = get_vehicle_runtime_context(*DAT_004c2908);
        pfVar3 = (float *)compute_transform_relative_to_ancestor
                                    ((float *)&stack0xfffffed0,*(int *)(iVar2 + 0x398),0);
        pfVar4 = local_ec;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *pfVar4 = *pfVar3;
          pfVar3 = pfVar3 + 1;
          pfVar4 = pfVar4 + 1;
        }
        local_ec[0] = -local_ec[0];
        local_ec[1] = -local_ec[1];
        local_ec[2] = -local_ec[2];
        local_d4 = -local_d4;
        local_d0 = -local_d0;
        local_cc = -local_cc;
        pfVar3 = local_ec;
        pfVar4 = local_64;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *pfVar4 = *pfVar3;
          pfVar3 = pfVar3 + 1;
          pfVar4 = pfVar4 + 1;
        }
        software_raster_queue_context_helper_00472990(0x608c80,local_64);
        fill_bitmap_surface_context(piVar1,0xea);
        if (local_20 == 1) {
          raster_span_builder_context_helper_00473630();
          g_runtime_terrain_render_min_or_near_bound = 0xc1200000;
          _g_runtime_terrain_render_max_or_far_bound = 0x43fa0000;
          local_8 = 0;
          entity_instance_table_context_helper_00457a90
                    (8.86661e-39,unaff_EDI,unaff_ESI,unaff_EBX,in_stack_fffffecc,in_stack_fffffed0,
                     in_stack_fffffed4,in_stack_fffffed8,in_stack_fffffedc,in_stack_fffffee0,
                     in_stack_fffffee4,in_stack_fffffee8,in_stack_fffffeec,in_stack_fffffef0);
          render_projectile_tracer_quads_variant_a(0x608c80);
          render_active_smoke_particle_emitters((float *)&DAT_00608c80);
          shutdown_flamer_effect_state(0x608c80);
          merge_world_object_or_geometry_state((float *)&DAT_00608c80,0);
        }
        else {
          build_camera_forward_basis_from_active_transform(8.86661e-39);
          local_8 = 1;
          raster_span_builder_context_helper_00473630();
          i76_runtime_build_visible_adaptive_terrain_mesh(0x608c80);
          render_dynamic_or_track_geometry_pass_candidate(0x608c80);
          shutdown_flamer_effect_state(0x608c80);
          entity_instance_table_context_helper_00457a90
                    (8.86661e-39,unaff_EDI,unaff_ESI,unaff_EBX,in_stack_fffffecc,in_stack_fffffed0,
                     in_stack_fffffed4,in_stack_fffffed8,in_stack_fffffedc,in_stack_fffffee0,
                     in_stack_fffffee4,in_stack_fffffee8,in_stack_fffffeec,in_stack_fffffef0);
          render_projectile_tracer_quads_variant_a(0x608c80);
          render_active_smoke_particle_emitters((float *)&DAT_00608c80);
          submit_far_scene_horizon_polygon_batch();
          merge_world_object_or_geometry_state((float *)&DAT_00608c80,1);
        }
        raster_span_builder_context_helper_00473640(DAT_00608cbc);
        cockpit_gauge_context_helper_0045af10((float *)&DAT_00608c80,1);
        local_8 = 0xffffffff;
        matrix_identity_or_copy_context_helper_00479740(1,0xff);
        DAT_0063b2bf = DAT_005dd328;
        blit_bitmap_surface_context_clipped_with_palette_blend
                  (local_24,&DAT_00608c40,0,(uint *)0x0,(uint *)0x1);
        DAT_0063b2bf = 0xff;
        matrix_identity_or_copy_context_helper_00479740(1,1);
        mark_texture_set_binding_dirty_or_track_special_view(DAT_0052bbc4,s_RearView_004edf74);
      }
    }
  }
  ExceptionList = local_14;
  return;
}


