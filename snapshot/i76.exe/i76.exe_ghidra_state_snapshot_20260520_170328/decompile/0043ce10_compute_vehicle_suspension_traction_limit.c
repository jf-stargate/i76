/*
 * Program: i76.exe
 * Function: compute_vehicle_suspension_traction_limit
 * Entry: 0043ce10
 * Signature: undefined __cdecl compute_vehicle_suspension_traction_limit(int param_1, float param_2, float * param_3, undefined4 * param_4, float * param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Computes traction/grip
   limit from suspension component values, terrain friction/material, tire contact states, vehicle
   speed, and runtime flags. */

void __cdecl
compute_vehicle_suspension_traction_limit
          (int param_1,float param_2,float *param_3,undefined4 *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  float10 fVar11;
  float local_c;
  float local_8;
  
  iVar4 = *(int *)(param_1 + 0x70);
  iVar6 = get_vehicle_suspension_runtime_component(iVar4);
  fVar11 = get_vehicle_suspension_response_scalar(iVar4);
  local_c = (float)fVar11;
  iVar7 = get_vehicle_rear_right_tire_runtime_component(iVar4);
  iVar8 = get_vehicle_rear_left_tire_runtime_component(iVar4);
  fVar1 = *(float *)(iVar7 + 0xc);
  fVar2 = *(float *)(iVar8 + 0xc);
  iVar7 = get_vehicle_front_right_tire_runtime_component(iVar4);
  fVar3 = *(float *)(iVar7 + 0xc);
  iVar7 = get_vehicle_front_left_tire_runtime_component(iVar4);
  fVar1 = fVar1 + fVar2 + fVar3 + *(float *)(iVar7 + 0xc);
  fVar11 = get_terrain_material_friction_scalar(*(int *)(iVar4 + 0x45c));
  if (((float10)_DAT_004bd168 < fVar11) && ((*(uint *)(iVar4 + 0x454) & 0x400) != 0)) {
    fVar11 = (float10)_DAT_004bd148;
  }
  fVar2 = (float)((float10)*(float *)(iVar4 + 0x46c) * (float10)*(float *)(iVar6 + 0x14) * fVar11 *
                  (float10)fVar1 * (float10)_DAT_004bd158);
  local_8 = fVar2;
  if ((*(uint *)(iVar4 + 0x454) & 0x10000) == 0) {
    local_8 = fVar1 * _DAT_004bd1e0;
  }
  fVar1 = fVar2 + fVar2;
  iVar6 = world_object_has_optional_runtime_flag(param_1);
  fVar3 = local_c;
  if ((iVar6 == 0) || (iVar6 = get_pending_active_player_ai_control_change_flag(), iVar6 != 0))
  goto LAB_0043cfd3;
  iVar6 = *(int *)(param_1 + 0x70);
  iVar7 = is_tire_contact_active(*(int *)(iVar6 + 0x3ac));
  if ((iVar7 == 0) || (iVar7 = is_tire_contact_active(*(int *)(iVar6 + 0x3a8)), iVar7 == 0)) {
    iVar7 = is_tire_contact_active(*(int *)(iVar6 + 0x3ac));
    if (iVar7 != 0) {
      local_c = local_c - _DAT_004bd1e4;
    }
    iVar6 = is_tire_contact_active(*(int *)(iVar6 + 0x3a8));
    if (iVar6 != 0) goto LAB_0043cf9b;
  }
  else {
    uVar9 = rand();
    uVar10 = (int)uVar9 >> 0x1f;
    if (((uVar9 ^ uVar10) - uVar10 & 1 ^ uVar10) == uVar10) {
LAB_0043cf9b:
      local_c = local_c - _DAT_004bd1e8;
    }
    else {
      local_c = local_c - _DAT_004bd1e4;
    }
  }
  fVar3 = _DAT_004bd134;
  if ((local_c <= _DAT_004bd134) && (fVar3 = local_c, local_c < _DAT_004bd1a8)) {
    fVar3 = _DAT_004bd1a8;
  }
LAB_0043cfd3:
  if (param_2 * param_2 * *(float *)(iVar4 + 0x110) <= local_8) {
    fVar3 = fVar3 * param_2 * *(float *)(iVar4 + 0x110);
  }
  else {
    fVar3 = (fVar3 * local_8) / param_2;
  }
  fVar5 = ABS(fVar3 * param_2);
  if (fVar5 <= fVar1) {
    if (fVar2 < fVar5) {
      *param_5 = (fVar5 - fVar1) / (fVar2 - fVar1);
    }
    *param_3 = fVar3;
    return;
  }
  *param_4 = 1;
  *param_3 = fVar3;
  return;
}


