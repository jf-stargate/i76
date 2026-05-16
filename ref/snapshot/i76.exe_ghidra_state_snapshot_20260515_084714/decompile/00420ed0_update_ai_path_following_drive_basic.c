/*
 * Program: i76.exe
 * Function: update_ai_path_following_drive_basic
 * Entry: 00420ed0
 * Signature: undefined __cdecl update_ai_path_following_drive_basic(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: AI path-following drive update using
   validate_ai_path_destination_bounds, steering control, and throttle/brake helper. */

void __cdecl update_ai_path_following_drive_basic(float param_1)

{
  int *piVar1;
  int iVar2;
  float10 fVar3;
  
  piVar1 = *(int **)(*(int *)((int)param_1 + 0x70) + 0x108);
  update_ai_path_waypoint_progress_state(piVar1);
  fVar3 = (float10)validate_ai_path_destination_bounds((int)param_1,piVar1,0,11.0);
  update_ai_vehicle_steering_control((int)param_1,(float)fVar3);
  iVar2 = get_vehicle_runtime_context((int)param_1);
  *(undefined4 *)(iVar2 + 0xe8) = 0x3f800000;
  vehicle_specials_state_getter_helper_00467370((int)param_1,3);
  if ((*(int *)((int)param_1 + 0x6c) != 9) && ((float)_DAT_004bcc98 < ABS(*(float *)(iVar2 + 0xe0)))
     ) {
    fVar3 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
    set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)fVar3);
    return;
  }
  set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)piVar1[0x20]);
  return;
}


