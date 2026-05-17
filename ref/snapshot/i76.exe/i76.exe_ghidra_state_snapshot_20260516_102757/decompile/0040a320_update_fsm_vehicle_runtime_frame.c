/*
 * Program: i76.exe
 * Function: update_fsm_vehicle_runtime_frame
 * Entry: 0040a320
 * Signature: undefined __stdcall update_fsm_vehicle_runtime_frame(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v10 fsm/ai runtime core cluster: Per-frame FSM/vehicle runtime update: updates
   aim/terrain bounds, processes FSM instructions, updates AI targets, and clears one-frame globals.
    */

void update_fsm_vehicle_runtime_frame(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  bool bVar10;
  int iVar11;
  float *pfVar12;
  int iVar13;
  int *piVar14;
  undefined3 extraout_var;
  float10 fVar15;
  undefined4 *local_94;
  undefined4 *local_90;
  int local_80;
  int *local_7c;
  float local_38 [3];
  float local_2c [3];
  undefined4 local_20 [4];
  float local_10;
  
                    /* I76 semantic baseline: update_fsm_vehicle_runtime_frame
                       Frame-level AI/FSM vehicle orchestrator: registry precompute, instruction
                       processing/active-player targeting. */
  if (DAT_0051f640 == 0) {
    commit_active_player_ai_control_change_state();
    clear_fsm_runtime_secondary_progress_state();
    reset_fsm_runtime_progress_counter();
    local_94 = &DAT_00507da0;
    local_7c = &DAT_0051f5d0;
    do {
      local_80 = *local_7c;
      if (0 < local_80) {
        local_90 = local_94;
        do {
          iVar13 = *(int *)*local_90;
          iVar11 = get_vehicle_runtime_context(iVar13);
          pfVar12 = (float *)get_cached_world_object_aim_position(local_20,iVar13);
          fVar1 = *pfVar12;
          fVar2 = pfVar12[1];
          fVar3 = pfVar12[2];
          pfVar12 = (float *)terrain_map_context_helper_004931c0
                                       (local_38,(double)fVar1,SUB84((double)fVar3,0),
                                        (int)((ulonglong)(double)fVar3 >> 0x20));
          fVar4 = *pfVar12;
          fVar5 = pfVar12[1];
          fVar6 = pfVar12[2];
          fVar8 = (*(float *)(iVar13 + 0x30) * fVar6 - *(float *)(iVar13 + 0x38) * fVar4) *
                  _DAT_004bc600;
          fVar9 = (*(float *)(iVar13 + 0x34) * fVar4 - *(float *)(iVar13 + 0x30) * fVar5) *
                  _DAT_004bc600;
          fVar7 = (*(float *)(iVar13 + 0x38) * fVar5 - *(float *)(iVar13 + 0x34) * fVar6) *
                  _DAT_004bc600;
          fVar15 = mission_flow_map_context_helper_0049c7b0();
          if (fVar15 <= (float10)_DAT_004bc604) {
            fVar15 = mission_flow_map_context_helper_0049c7b0();
          }
          else {
            fVar15 = (float10)_DAT_004bc604;
          }
          fVar15 = fVar15 * (float10)_DAT_004bc608 * (float10)*(float *)(iVar11 + 0xe8);
          pfVar12 = (float *)add_vec3_components(local_2c,fVar1,fVar2,fVar3,
                                                 (float)((float10)(fVar5 * fVar9 - fVar6 * fVar8) *
                                                        fVar15),
                                                 (float)((float10)(fVar6 * fVar7 - fVar4 * fVar9) *
                                                        fVar15),
                                                 (float)((float10)(fVar4 * fVar8 - fVar5 * fVar7) *
                                                        fVar15));
          local_10 = pfVar12[1];
          set_ai_behavior_xy_bounds_from_segment(iVar13,fVar1,fVar3,*pfVar12,pfVar12[2]);
          local_90 = local_90 + 1;
          local_80 = local_80 + -1;
        } while (local_80 != 0);
      }
      local_7c = local_7c + 1;
      local_94 = local_94 + 0x40;
    } while ((int)local_7c < 0x51f5f0);
    iVar13 = is_network_or_trip_runtime_mode();
    if ((iVar13 == 0) && (DAT_0051f5c0 == 0)) {
      process_pending_fsm_instruction_list
                (DAT_0051f63c,DAT_0051f638,DAT_0051f608,DAT_0051f60c,DAT_0051f610,DAT_0051f614,
                 DAT_0051f618,DAT_0051f61c,DAT_0051f620,&DAT_0051f624,&DAT_0051f628,&DAT_0051f62c,
                 DAT_0051f630,DAT_0051f634,DAT_0051f5b4);
    }
    else {
      update_all_ai_vehicles_against_active_player();
    }
    update_fsm_runtime_progress_compare_state();
    increment_vehicle_damage_source_event_state();
    iVar13 = is_damage_side_effects_suppressed();
    if (iVar13 == 0) {
      piVar14 = (int *)get_active_player_or_camera_world_object_entry();
      if (piVar14 == (int *)0x0) {
        DAT_0051f5c8 = 0;
      }
      else {
        bVar10 = radar_render_context_helper_00461680(*piVar14);
        DAT_0051f5c8 = CONCAT31(extraout_var,bVar10);
      }
    }
    if (DAT_0051f5c8 != 0) {
      if (DAT_0051f5cc == 0) {
        DAT_0051f5bc = 0;
      }
      DAT_0051f5cc = 0;
      DAT_0051f5b8 = 0;
    }
    DAT_0051f604 = 0;
    if ((DAT_00508da0 == 0) && (DAT_0051f5b0 != 0)) {
      reset_bridge_validation_runtime_state(*(int *)(*(int *)(DAT_0051f5b0 + 0x70) + 0x108));
      DAT_0051f5b0 = 0;
    }
    DAT_00508da0 = 0;
  }
  return;
}


