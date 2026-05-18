/*
 * Program: i76.exe
 * Function: compute_vehicle_longitudinal_drive_brake_force
 * Entry: 0043c310
 * Signature: undefined __cdecl compute_vehicle_longitudinal_drive_brake_force(float param_1, float param_2, int param_3, float * param_4, uint param_5, float * param_6, undefined4 * param_7)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Computes longitudinal
   drive/brake force from engine, brake, tire contact scalars, terrain friction, speed, gear/mode
   flags, and throttle/brake state. */

void __cdecl
compute_vehicle_longitudinal_drive_brake_force
          (float param_1,float param_2,int param_3,float *param_4,uint param_5,float *param_6,
          undefined4 *param_7)

{
  float fVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  bool bVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  float10 fVar13;
  float10 fVar14;
  
  iVar2 = *(int *)((int)param_1 + 0x70);
  if ((_DAT_004bd148 < param_2) && (((param_5 & 1) == 0 || (*(int *)(iVar2 + 0x104) == 2)))) {
    *param_6 = 0.0;
    return;
  }
  fVar3 = *(float *)(iVar2 + 0xe8);
  fVar4 = *(float *)(iVar2 + 0xac);
  iVar7 = get_vehicle_brake_runtime_component(iVar2);
  iVar8 = get_vehicle_front_left_tire_runtime_component(iVar2);
  iVar9 = get_vehicle_front_right_tire_runtime_component(iVar2);
  iVar10 = get_vehicle_rear_left_tire_runtime_component(iVar2);
  iVar11 = get_vehicle_rear_right_tire_runtime_component(iVar2);
  fVar1 = *(float *)(iVar2 + 0x46c) * _DAT_004bd158;
  fVar6 = *(float *)(iVar2 + 0xbc) * *param_4 +
          *(float *)(iVar2 + 0xc4) * param_4[2] + *(float *)(iVar2 + 0xc0) * param_4[1];
  bVar5 = fVar6 < _DAT_004bd148;
  fVar13 = get_terrain_material_friction_scalar(*(int *)(iVar2 + 0x45c));
  if (((float10)_DAT_004bd168 < fVar13) && ((*(uint *)(iVar2 + 0x454) & 0x400) != 0)) {
    fVar13 = (float10)_DAT_004bd148;
  }
  fVar14 = (float10)_DAT_004bd148;
  fVar1 = (float)(fVar13 * (float10)fVar1);
  if (param_3 == 0) {
    uVar12 = param_5 & 2;
  }
  else {
    param_2 = -1.0;
    uVar12 = 1;
  }
  if (_DAT_004bd1ac < param_2) {
    if (_DAT_004bd150 <= param_2) {
      fVar1 = (*(float *)(iVar11 + 0xc) + *(float *)(iVar10 + 0xc)) * fVar1;
      if (uVar12 == 0) {
        fVar13 = get_engine_component_drive_force_scalar(*(int *)(*(int *)(iVar2 + 0x3c4) + 0x70));
      }
      else {
        iVar7 = *(int *)(*(int *)(iVar2 + 0x3c4) + 0x70);
        fVar13 = (float10)*(float *)(iVar7 + 0x14) * (float10)*(float *)(iVar7 + 0x18);
      }
      fVar14 = fVar13 * (float10)*(float *)(iVar2 + 0xa8) * (float10)*(float *)(iVar2 + 0x128);
      if ((*(uint *)(iVar2 + 0x454) & 0x800) != 0) {
        fVar14 = fVar14 * (float10)_DAT_004bd1dc;
      }
      if (_DAT_004bd134 < fVar4) {
        fVar14 = fVar14 * (float10)*(float *)(iVar2 + 0xb0);
      }
      if (fVar14 < (float10)_DAT_004bd150) {
        fVar14 = (float10)_DAT_004bd150;
      }
      fVar14 = fVar14 * (float10)param_2;
      if ((float10)fVar1 < fVar14) {
        fVar14 = (float10)fVar1;
        *param_7 = 1;
      }
      fVar14 = fVar14 * (float10)fVar3;
    }
  }
  else {
    param_1 = -((*(float *)(iVar11 + 0xc) + *(float *)(iVar9 + 0xc) + *(float *)(iVar10 + 0xc) +
                *(float *)(iVar8 + 0xc)) * fVar1);
    if (_DAT_004bd134 < fVar4) {
      fVar14 = (float10)*(float *)(iVar7 + 0x10) * (float10)param_2 * (float10)_DAT_004bd1d8;
      if ((uVar12 != 0) && (param_1 = *(float *)(iVar2 + 0xb0) * fVar6 * param_1, bVar5)) {
        param_1 = -param_1;
      }
      if (*(int *)(iVar2 + 0xf0) != 0) {
        param_1 = param_1 * _DAT_004bd138;
      }
      if (param_3 == 0) {
        if (fVar14 < (float10)param_1) {
          fVar14 = (float10)param_1;
          *param_7 = 1;
        }
      }
      else {
        fVar14 = (float10)param_1 + (float10)param_1;
      }
      if (bVar5) {
        *param_6 = (float)-fVar14;
        return;
      }
    }
  }
  *param_6 = (float)fVar14;
  return;
}


