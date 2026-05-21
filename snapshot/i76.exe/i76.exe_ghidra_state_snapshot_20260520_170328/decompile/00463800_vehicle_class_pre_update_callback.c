/*
 * Program: i76.exe
 * Function: vehicle_class_pre_update_callback
 * Entry: 00463800
 * Signature: undefined __cdecl vehicle_class_pre_update_callback(float * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=high] Class-id 1 frame callback.
   Gates update by object state, accumulates fixed-step time at vehicle runtime +0x444, calls
   vehicle state/lifecycle update and the lower-level vehicle physics integrator. */

void __cdecl vehicle_class_pre_update_callback(float *param_1)

{
  float fVar1;
  float *pfVar2;
  bool bVar3;
  int iVar4;
  undefined3 extraout_var;
  undefined4 uVar5;
  float10 fVar6;
  
                    /* I76 semantic baseline note:
                       Vehicle object class pre-update callback. Active path: lifecycle +
                       control/drivetrain update. Inactive path: fixed-step wheel/contact physics.
                       Uses 0.05s vehicle fixed-step accumulator. */
  pfVar2 = param_1;
  fVar1 = param_1[0x1c];
  iVar4 = get_world_object_runtime_activity_state((int)param_1,25.0);
  if (((iVar4 == 2) || (((uint)param_1[4] & 0x20) != 0)) &&
     (bVar3 = is_gameplay_input_update_paused(), CONCAT31(extraout_var,bVar3) == 0)) {
    fVar6 = get_runtime_update_delta_seconds();
    update_vehicle_lifecycle_and_destruction_state((int)param_1,(float)fVar6);
    if (((uint)param_1[4] & 0x20) == 0) {
      update_vehicle_control_input_and_drivetrain_state((float)param_1,(float)fVar6);
    }
    initialize_fixedstep_accumulator_interval((float *)((int)fVar1 + 0x444),0.05);
  }
  else {
    if ((*(uint *)((int)fVar1 + 0x454) & 0x20000) != 0) {
      update_inactive_vehicle_ground_recovery_and_suspension_visuals((float)param_1);
    }
    iVar4 = (int)fVar1 + 0x444;
    reset_fixedstep_accumulator_timer(iVar4);
    fVar6 = get_fixedstep_accumulator_seconds(iVar4);
    if ((float10)_g_float_zero < fVar6) {
      do {
        param_1 = (float *)(float)fVar6;
        update_vehicle_lifecycle_and_destruction_state((int)pfVar2,(float)param_1);
        update_vehicle_wheel_contact_physics_and_terrain_response(pfVar2,(float)param_1);
        if (*(short *)(pfVar2 + 2) != 0) {
          return;
        }
        fVar6 = get_fixedstep_accumulator_seconds(iVar4);
      } while ((float10)_g_float_zero < fVar6);
    }
  }
  iVar4 = world_object_has_optional_runtime_flag((int)pfVar2);
  if (iVar4 == 0) goto LAB_00463931;
  iVar4 = find_nearest_effect_target_to_active_player();
  if (iVar4 == 0) {
    if (g_runtime_display_mode_last_vehicle_state == 9) {
      push_runtime_camera_state_stack();
      goto LAB_0046391f;
    }
  }
  else if (g_runtime_display_mode_last_vehicle_state != 9) {
    iVar4 = 0x1b;
    uVar5 = get_active_player_or_camera_world_object_entry();
    dispatch_runtime_camera_mode_activation_by_id(uVar5,iVar4);
LAB_0046391f:
    (*g_runtime_display_mode_change_callback)();
  }
  g_runtime_display_mode_last_vehicle_state = g_runtime_display_mode_state;
LAB_00463931:
  update_vehicle_skid_collision_damage_audio
            ((int)pfVar2,*(uint *)((int)fVar1 + 0x454),*(int *)((int)fVar1 + 0x45c));
  return;
}


