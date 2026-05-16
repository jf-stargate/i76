/*
 * Program: i76.exe
 * Function: update_inactive_vehicle_ground_recovery_and_suspension_visuals
 * Entry: 0043d070
 * Signature: undefined __cdecl update_inactive_vehicle_ground_recovery_and_suspension_visuals(float param_1)
 */


/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=medium] Vehicle
   recovery/autopilot-like runtime update helper in the physics step path. */

void __cdecl update_inactive_vehicle_ground_recovery_and_suspension_visuals(float param_1)

{
  int iVar1;
  float fVar2;
  float10 fVar3;
  float local_18;
  float local_14;
  float local_10;
  float local_c [3];
  
  fVar2 = param_1;
                    /* I76 semantic baseline:
                       update_inactive_vehicle_ground_recovery_and_suspension_visuals
                       Inactive/special vehicle ground recovery and suspension visual update. */
  local_18 = (float)*(double *)((int)param_1 + 0x40);
  local_14 = (float)*(double *)((int)param_1 + 0x48);
  local_c[0] = 0.0;
  local_c[1] = 0.0;
  local_10 = (float)*(double *)((int)param_1 + 0x50);
  local_c[2] = 0.0;
  iVar1 = *(int *)((int)param_1 + 0x70);
  probe_effect_target_surface_height_at_position
            ((double)CONCAT44(local_14,local_18),local_10,&param_1,&local_18);
  *(double *)((int)fVar2 + 0x48) = (double)param_1;
  *(float *)(iVar1 + 0x460) = local_18;
  *(float *)(iVar1 + 0x464) = local_14;
  *(float *)(iVar1 + 0x468) = local_10;
  fVar3 = get_runtime_update_delta_seconds();
  update_tire_suspension_visual_compression_state((int)fVar2,local_c,0,1,(float)fVar3);
  *(uint *)(iVar1 + 0x454) = *(uint *)(iVar1 + 0x454) & 0xfffdffff;
  return;
}


