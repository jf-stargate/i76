/*
 * Program: i76.exe
 * Function: compute_vehicle_tire_grip_control_scalar
 * Entry: 0043c6f0
 * Signature: float10 __cdecl compute_vehicle_tire_grip_control_scalar(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Computes a vehicle traction/control scalar from tire contact compression, terrain
   friction, speed, and suspension data. */

float10 __cdecl compute_vehicle_tire_grip_control_scalar(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  int iVar5;
  undefined3 extraout_var;
  int iVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  float10 fVar10;
  
  if ((((*(int *)(param_1 + 0x70) == 0) ||
       (iVar5 = is_vehicle_or_actor_runtime_world_object(param_1), iVar5 == 0)) ||
      (bVar4 = vehicle_damage_system_context_helper_00465350(param_1),
      CONCAT31(extraout_var,bVar4) != 0)) || (*(int *)(param_1 + 0x6c) == 9)) {
    return (float10)_DAT_004bd134;
  }
  iVar5 = *(int *)(param_1 + 0x70);
  iVar6 = get_vehicle_suspension_runtime_component(iVar5);
  iVar7 = get_vehicle_front_right_tire_runtime_component(iVar5);
  iVar8 = get_vehicle_front_left_tire_runtime_component(iVar5);
  fVar1 = *(float *)(iVar7 + 0xc);
  fVar2 = *(float *)(iVar8 + 0xc);
  iVar7 = get_vehicle_rear_right_tire_runtime_component(iVar5);
  fVar3 = *(float *)(iVar7 + 0xc);
  iVar7 = get_vehicle_rear_left_tire_runtime_component(iVar5);
  fVar1 = fVar1 + fVar2 + fVar3 + *(float *)(iVar7 + 0xc);
  fVar2 = fVar1 * _DAT_004bd1e0;
  fVar9 = get_terrain_material_friction_scalar(*(int *)(iVar5 + 0x45c));
  if (((float10)_DAT_004bd168 < fVar9) && ((*(uint *)(iVar5 + 0x454) & 0x400) != 0)) {
    fVar9 = (float10)_DAT_004bd148;
  }
  fVar10 = (float10)*(float *)(iVar5 + 0xac);
  fVar1 = (float)((float10)*(float *)(iVar5 + 0x46c) * (float10)*(float *)(iVar6 + 0x14) * fVar9 *
                  (float10)fVar1 * (float10)_DAT_004bd158);
  if ((float10)_DAT_004bd150 <= fVar10) {
    fVar10 = (float10)*(float *)(iVar5 + 0x110) * fVar10 * fVar10;
    if (fVar10 <= (float10)fVar2) {
      fVar10 = (float10)fVar1 / fVar10;
    }
    else {
      fVar10 = (float10)fVar1 / (float10)fVar2;
    }
  }
  else {
    fVar10 = (float10)_DAT_004bd134;
  }
  if (fVar10 <= (float10)_DAT_004bd134) {
    return fVar10;
  }
  return (float10)_DAT_004bd134;
}


