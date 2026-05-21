/*
 * Program: i76.exe
 * Function: solve_vehicle_max_drive_brake_delta
 * Entry: 0043c600
 * Signature: float10 __cdecl solve_vehicle_max_drive_brake_delta(float param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Binary-searches a safe longitudinal drive/brake delta by repeatedly testing
   drive/brake force response. */

float10 __cdecl solve_vehicle_max_drive_brake_delta(float param_1,float param_2)

{
  uint uVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  undefined3 extraout_var;
  int iVar5;
  int local_24;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  float local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  fVar3 = param_1;
  bVar4 = vehicle_damage_system_context_helper_00465350((int)param_1);
  if ((CONCAT31(extraout_var,bVar4) == 0) && (*(int *)((int)param_1 + 0x6c) != 9)) {
    local_18 = *(float *)((int)param_1 + 0x30);
    local_14 = *(undefined4 *)((int)param_1 + 0x34);
    local_10 = *(undefined4 *)((int)param_1 + 0x38);
    local_c = local_18;
    local_8 = local_14;
    local_4 = local_10;
    iVar5 = get_vehicle_runtime_context((int)param_1);
    param_1 = param_2 * _DAT_004bd138;
    uVar1 = *(uint *)(iVar5 + 0x454);
    local_20 = 0.0;
    iVar5 = 6;
    param_2 = param_1;
    do {
      param_1 = param_1 * _DAT_004bd138;
      local_24 = 0;
      compute_vehicle_longitudinal_drive_brake_force
                (fVar3,param_2,0,&local_c,uVar1,&local_1c,&local_24);
      if (local_24 == 0) {
        fVar2 = param_2 + param_1;
        local_20 = param_2;
      }
      else {
        fVar2 = param_2 - param_1;
      }
      iVar5 = iVar5 + -1;
      param_2 = fVar2;
    } while (iVar5 != 0);
    return (float10)local_20;
  }
  return (float10)param_2;
}


