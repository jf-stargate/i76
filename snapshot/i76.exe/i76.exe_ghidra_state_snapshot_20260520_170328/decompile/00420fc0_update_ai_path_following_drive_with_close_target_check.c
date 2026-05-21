/*
 * Program: i76.exe
 * Function: update_ai_path_following_drive_with_close_target_check
 * Entry: 00420fc0
 * Signature: undefined __cdecl update_ai_path_following_drive_with_close_target_check(float param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Variant of AI path-following drive update with nearby-target
   gating and alternating avoidance state. */

void __cdecl update_ai_path_following_drive_with_close_target_check(float param_1,int param_2)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  bool bVar5;
  float fVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  float10 fVar10;
  float local_c;
  float local_8;
  float local_4;
  
  fVar6 = param_1;
  piVar1 = *(int **)(*(int *)((int)param_1 + 0x70) + 0x108);
  update_ai_path_waypoint_progress_state(piVar1);
  fVar10 = get_gameplay_runtime_seconds();
  if ((float)piVar1[0x273e] < (float)fVar10) {
    uVar7 = rand();
    uVar9 = (int)uVar7 >> 0x1f;
    piVar1[0x273f] = (uint)(piVar1[0x273f] == 0);
    piVar1[0x273e] =
         (int)(((float)(int)(((uVar7 ^ uVar9) - uVar9 & 3 ^ uVar9) - uVar9) + (float)fVar10) -
              _DAT_004bcc68);
  }
  local_c = (float)*(double *)((int)param_1 + 0x40);
  local_8 = (float)*(double *)((int)param_1 + 0x48);
  local_4 = (float)*(double *)((int)param_1 + 0x50);
  fVar2 = (float)*(double *)(param_2 + 0x40) - local_c;
  fVar4 = (float)*(double *)(param_2 + 0x48) - local_8;
  fVar3 = (float)*(double *)(param_2 + 0x50) - local_4;
  if (fVar3 * fVar3 + fVar4 * fVar4 + fVar2 * fVar2 < _DAT_004bcc6c) {
    iVar8 = fsm_query_primary_team_clear_of_position(&local_c);
    if (iVar8 != 0) {
      iVar8 = piVar1[0x273f];
      bVar5 = false;
      param_1 = 22.0;
      goto LAB_004210f3;
    }
  }
  iVar8 = 0;
  bVar5 = true;
  param_1 = 11.0;
LAB_004210f3:
  fVar10 = (float10)validate_ai_path_destination_bounds((int)fVar6,piVar1,iVar8,param_1);
  update_ai_vehicle_steering_control((int)fVar6,(float)fVar10);
  iVar8 = get_vehicle_runtime_context((int)fVar6);
  if (*(int *)((int)fVar6 + 0x6c) == 9) {
    param_1 = (float)piVar1[0x20];
  }
  else if (bVar5) {
    if (ABS(*(float *)(iVar8 + 0xe0)) <= (float)_DAT_004bcca0) {
      param_1 = (float)piVar1[0x20];
    }
    else {
      fVar10 = get_ai_vehicle_damage_state_speed_scalar((int)fVar6);
      param_1 = (float)fVar10;
    }
  }
  else if (ABS(*(float *)(iVar8 + 0xe0)) <= (float)_DAT_004bcc88) {
    param_1 = (float)piVar1[0x20];
  }
  else {
    fVar10 = get_ai_vehicle_damage_state_speed_scalar((int)fVar6);
    param_1 = (float)fVar10;
  }
  set_ai_vehicle_throttle_brake_toward_speed(fVar6,param_1);
  return;
}


