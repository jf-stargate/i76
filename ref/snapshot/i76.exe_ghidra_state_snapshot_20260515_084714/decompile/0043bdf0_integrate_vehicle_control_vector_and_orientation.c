/*
 * Program: i76.exe
 * Function: integrate_vehicle_control_vector_and_orientation
 * Entry: 0043bdf0
 * Signature: undefined __cdecl integrate_vehicle_control_vector_and_orientation(float param_1, uint * param_2, float * param_3, float * param_4, undefined4 * param_5, float * param_6, float param_7)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=medium_high]
   Control-vector/orientation integrator used by drivetrain pre-pass; builds forward/speed vectors
   and candidate transform state. */

void __cdecl
integrate_vehicle_control_vector_and_orientation
          (float param_1,uint *param_2,float *param_3,float *param_4,undefined4 *param_5,
          float *param_6,float param_7)

{
  float fVar1;
  float *pfVar2;
  float *pfVar3;
  int iVar4;
  float *pfVar5;
  float local_dc;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  undefined4 local_a0 [2];
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80 [16];
  float local_40 [16];
  
  iVar4 = *(int *)((int)param_1 + 0x70);
  local_b4 = *(float *)(iVar4 + 0xe4);
  if ((*(int *)(iVar4 + 0xf0) != 0) || (*(int *)(iVar4 + 0x104) == 0)) {
    local_b4 = -1.0;
  }
  if ((local_b4 < _DAT_004bd148) && (*(int *)(iVar4 + 0xf4) != 0)) {
    local_b4 = local_b4 + local_b4;
  }
  *param_2 = *(uint *)(iVar4 + 0x454) & 0xfffffdf9;
  *param_5 = 0;
  param_5[1] = 0;
  param_5[2] = 0;
  local_dc = *(float *)(iVar4 + 0xac);
  if ((local_dc == _DAT_004bd148) && (local_b4 <= _DAT_004bd148)) {
    *param_3 = 0.0;
    param_3[1] = 0.0;
    param_3[2] = 0.0;
    *param_4 = 0.0;
    pfVar3 = (float *)((int)param_1 + 0x18);
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *param_6 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      param_6 = param_6 + 1;
    }
    return;
  }
  local_cc = *(float *)((int)param_1 + 0x30);
  local_c8 = *(float *)((int)param_1 + 0x34);
  local_c4 = *(float *)((int)param_1 + 0x38);
  if (*(float *)(iVar4 + 0xc4) * local_c4 +
      *(float *)(iVar4 + 0xc0) * local_c8 + local_cc * *(float *)(iVar4 + 0xbc) < _DAT_004bd148) {
    local_dc = -local_dc;
  }
  local_b0 = local_cc;
  local_ac = local_c8;
  local_a8 = local_c4;
  compute_vehicle_longitudinal_drive_brake_force
            (param_1,*(float *)(iVar4 + 0xe4),0,&local_b0,*param_2,&local_a4,local_a0);
  pfVar3 = (float *)(param_5 + 1);
  compute_vehicle_suspension_traction_limit((int)param_1,local_dc,pfVar3,local_a0,&local_84);
  local_cc = (float)*(double *)((int)param_1 + 0x40);
  local_c8 = (float)*(double *)((int)param_1 + 0x48);
  local_c4 = (float)*(double *)((int)param_1 + 0x50);
  local_c0 = local_b0 * local_dc;
  local_bc = local_ac * local_dc;
  local_98 = *(float *)((int)param_1 + 0x1c);
  local_b8 = local_a8 * local_dc;
  local_94 = *(float *)((int)param_1 + 0x20);
  fVar1 = -(local_dc * *pfVar3);
  local_90 = local_b0 * local_a4 + fVar1 * *(float *)((int)param_1 + 0x18);
  local_8c = local_ac * local_a4 + fVar1 * local_98;
  local_88 = local_a8 * local_a4 + fVar1 * local_94;
  effect_target_list_scan_context_helper_004383a0(&local_cc,&local_c0,&local_90,param_7);
  if ((_DAT_004bd148 <= local_b4) ||
     (_DAT_004bd148 <=
      *(float *)(iVar4 + 0xbc) * local_c0 +
      *(float *)(iVar4 + 0xc4) * local_b8 + *(float *)(iVar4 + 0xc0) * local_bc)) {
    local_dc = SQRT(local_b8 * local_b8 + local_bc * local_bc + local_c0 * local_c0);
    if ((_DAT_004bd148 < local_b4) || ((local_dc <= _DAT_004bd1a8 || (_DAT_004bd134 <= local_dc))))
    {
      if (local_b8 * local_a8 + local_bc * local_ac + local_c0 * local_b0 < _DAT_004bd148) {
        local_dc = -local_dc;
      }
    }
    else {
      local_dc = _DAT_004bd148;
      local_c0 = _DAT_004bd148;
      local_bc = _DAT_004bd148;
      local_b8 = _DAT_004bd148;
    }
  }
  else {
    local_dc = _DAT_004bd148;
    local_cc = (float)*(double *)((int)param_1 + 0x40);
    local_c8 = (float)*(double *)((int)param_1 + 0x48);
    local_c0 = _DAT_004bd148;
    local_c4 = (float)*(double *)((int)param_1 + 0x50);
    local_bc = _DAT_004bd148;
    local_b8 = _DAT_004bd148;
  }
  pfVar2 = (float *)zone_satellite_map_context_helper_00494710
                              ((float *)(iVar4 + 0x460),&local_b0,local_80);
  pfVar5 = param_6;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar5 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar5 = pfVar5 + 1;
  }
  pfVar3 = (float *)zone_satellite_map_context_helper_00493da0(local_80,-(param_7 * *pfVar3));
  pfVar2 = local_40;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar2 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar2 = pfVar2 + 1;
  }
  pfVar3 = compose_matrix_or_transform_a(local_80,local_40,param_6);
  pfVar2 = param_6;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar2 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar2 = pfVar2 + 1;
  }
  *(double *)(param_6 + 10) = (double)local_cc;
  *(double *)(param_6 + 0xc) = (double)local_c8;
  *(double *)(param_6 + 0xe) = (double)local_c4;
  *param_3 = local_c0;
  param_3[1] = local_bc;
  param_3[2] = local_b8;
  *param_4 = local_dc;
  return;
}


