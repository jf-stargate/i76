/*
 * Program: i76.exe
 * Function: update_ai_path_following_drive_with_target_avoidance
 * Entry: 00420b30
 * Signature: undefined __cdecl update_ai_path_following_drive_with_target_avoidance(float param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: AI path-following drive update with waypoint progress, target
   proximity avoidance, steering, and throttle/brake control. */

void __cdecl update_ai_path_following_drive_with_target_avoidance(float param_1,int param_2)

{
  float fVar1;
  int *piVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  bool bVar6;
  float fVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  float10 fVar11;
  float local_c;
  float local_8;
  float local_4;
  
  fVar7 = param_1;
  piVar2 = *(int **)(*(int *)((int)param_1 + 0x70) + 0x108);
  update_ai_path_waypoint_progress_state(piVar2);
  fVar11 = get_runtime_time_seconds();
  fVar1 = (float)fVar11;
  if ((float)piVar2[0x273e] < fVar1) {
    uVar8 = rand();
    uVar10 = (int)uVar8 >> 0x1f;
    piVar2[0x273f] = (uint)(piVar2[0x273f] == 0);
    piVar2[0x273e] =
         (int)(((float)(int)(((uVar8 ^ uVar10) - uVar10 & 3 ^ uVar10) - uVar10) + fVar1) -
              _DAT_004bcc68);
  }
  local_c = (float)*(double *)((int)param_1 + 0x40);
  local_8 = (float)*(double *)((int)param_1 + 0x48);
  local_4 = (float)*(double *)((int)param_1 + 0x50);
  fVar3 = (float)*(double *)(param_2 + 0x40) - local_c;
  fVar5 = (float)*(double *)(param_2 + 0x48) - local_8;
  fVar4 = (float)*(double *)(param_2 + 0x50) - local_4;
  if (fVar4 * fVar4 + fVar5 * fVar5 + fVar3 * fVar3 < _DAT_004bcc6c) {
    iVar9 = fsm_query_primary_team_clear_of_position(&local_c);
    if ((iVar9 != 0) && (fVar1 < (float)piVar2[0x29bc] - _DAT_004bcc70)) {
      iVar9 = piVar2[0x273f];
      bVar6 = false;
      param_1 = 22.0;
      goto LAB_00420c7c;
    }
  }
  iVar9 = 0;
  bVar6 = true;
  param_1 = 11.0;
LAB_00420c7c:
  fVar11 = (float10)validate_ai_path_destination_bounds((int)fVar7,piVar2,iVar9,param_1);
  update_ai_vehicle_steering_control((int)fVar7,(float)fVar11);
  iVar9 = get_vehicle_runtime_context((int)fVar7);
  if (*(int *)((int)fVar7 + 0x6c) == 9) {
    param_1 = (float)piVar2[0x20];
  }
  else if (bVar6) {
    if (ABS(*(float *)(iVar9 + 0xe0)) <= (float)_DAT_004bcc80) {
      param_1 = (float)piVar2[0x20];
    }
    else {
      fVar11 = get_ai_vehicle_damage_state_speed_scalar((int)fVar7);
      param_1 = (float)fVar11;
    }
  }
  else if (ABS(*(float *)(iVar9 + 0xe0)) <= (float)_DAT_004bcc88) {
    param_1 = (float)piVar2[0x20];
  }
  else {
    fVar11 = get_ai_vehicle_damage_state_speed_scalar((int)fVar7);
    param_1 = (float)fVar11;
  }
  set_ai_vehicle_throttle_brake_toward_speed(fVar7,param_1);
  return;
}


