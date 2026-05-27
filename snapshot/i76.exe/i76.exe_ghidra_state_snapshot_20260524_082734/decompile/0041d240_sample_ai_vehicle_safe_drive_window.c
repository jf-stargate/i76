/*
 * Program: i76.exe
 * Function: sample_ai_vehicle_safe_drive_window
 * Entry: 0041d240
 * Signature: int __cdecl sample_ai_vehicle_safe_drive_window(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Samples max safe drive/brake values into a rolling
   four-slot window and reports whether movement is blocked. */

int __cdecl sample_ai_vehicle_safe_drive_window(float param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  float10 fVar4;
  undefined4 local_18;
  undefined4 local_c;
  
  get_vehicle_runtime_context((int)param_1);
  iVar1 = get_ai_vehicle_behavior_state_block((int)param_1);
  fVar4 = solve_vehicle_max_drive_brake_delta(param_1,1.0);
  uVar2 = get_vehicle_damage_source_event_state();
  uVar3 = (int)uVar2 >> 0x1f;
  *(float *)(iVar1 + 0x9d58 + (((uVar2 ^ uVar3) - uVar3 & 3 ^ uVar3) - uVar3) * 4) = (float)fVar4;
  if ((((_DAT_004bcadc <= *(float *)(iVar1 + 0x9d58)) ||
       (_DAT_004bcadc <= *(float *)(iVar1 + 0x9d5c))) ||
      (_DAT_004bcadc <= *(float *)(iVar1 + 0x9d60))) ||
     (_DAT_004bcadc <= *(float *)(iVar1 + 0x9d64))) {
    local_18 = 0;
  }
  else {
    local_18 = 1;
  }
  local_c = local_18;
  if (local_18 != 0) {
    local_c = 2;
  }
  return local_c;
}


