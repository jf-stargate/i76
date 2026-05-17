/*
 * Program: i76.exe
 * Function: update_vehicle_control_input_and_drivetrain_state
 * Entry: 0043a3c0
 * Signature: undefined __cdecl update_vehicle_control_input_and_drivetrain_state(float param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=medium_high] Per-frame vehicle
   control/drivetrain pre-pass feeding the physics integrator. */

void __cdecl update_vehicle_control_input_and_drivetrain_state(float param_1,float param_2)

{
  uint *puVar1;
  int iVar2;
  bool bVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  int iVar9;
  float local_10 [4];
  
  fVar7 = param_1;
  if ((*(byte *)((int)param_1 + 0x10) & 0x20) == 0) {
    iVar2 = *(int *)((int)param_1 + 0x70);
    iVar8 = get_vehicle_runtime_context((int)param_1);
    *(uint *)(iVar8 + 0x454) = *(uint *)(iVar8 + 0x454) & 0xfffffffd;
    update_tire_contact_skid_fx_state(*(int *)(iVar8 + 0x3bc),0);
    update_tire_contact_skid_fx_state(*(int *)(iVar8 + 0x3b8),0);
    puVar1 = (uint *)(iVar2 + 0x454);
    if ((*(uint *)(iVar2 + 0x454) & 0x20000) == 0) {
      local_10[1] = 0.0;
      local_10[2] = 1.0;
      local_10[3] = 0.0;
      *(undefined4 *)(iVar2 + 0x460) = 0;
      *(undefined4 *)(iVar2 + 0x46c) = 0x411ccccd;
      *(undefined4 *)(iVar2 + 0x464) = 0x3f800000;
      *(undefined4 *)(iVar2 + 0x468) = 0;
    }
    integrate_vehicle_control_vector_and_orientation
              (param_1,puVar1,(float *)(iVar2 + 0xbc),local_10,(undefined4 *)(iVar2 + 200),
               (float *)((int)param_1 + 0x18),param_2);
    fVar6 = _DAT_004bd150;
    fVar4 = ABS(local_10[0]);
    *(float *)(iVar2 + 0xac) = fVar4;
    fVar5 = _DAT_004bd188;
    if (fVar6 < fVar4) {
      fVar5 = _DAT_004bd134 / fVar4;
    }
    *(float *)(iVar2 + 0xb0) = fVar5;
    local_10[1] = 0.0;
    local_10[2] = 1.0;
    local_10[3] = 0.0;
    bVar3 = *(float *)(iVar2 + 0xe8) < _DAT_004bd148;
    *(undefined4 *)(iVar2 + 0x460) = 0;
    *(undefined4 *)(iVar2 + 0x45c) = 2;
    *(undefined4 *)(iVar2 + 0x464) = 0x3f800000;
    *(undefined4 *)(iVar2 + 0x468) = 0;
    *puVar1 = *puVar1 | 0x20000;
    param_1 = (float)(uint)bVar3;
    iVar8 = *(int *)(*(int *)(iVar2 + 0x3c4) + 0x70);
    iVar9 = get_vehicle_drivetrain_mode_state((int)fVar7);
    update_engine_gear_rpm_torque_state
              (iVar8,*(float *)(iVar2 + 0xe4),local_10[0],*puVar1,(int)param_1,iVar9);
  }
  return;
}


