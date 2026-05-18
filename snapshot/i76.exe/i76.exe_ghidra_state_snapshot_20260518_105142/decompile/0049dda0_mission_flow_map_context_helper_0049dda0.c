/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049dda0
 * Entry: 0049dda0
 * Signature: undefined __cdecl mission_flow_map_context_helper_0049dda0(int param_1, int param_2, int * param_3, int * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049dda0.
   Remove duplicated mission-flow/map wording. */

void __cdecl
mission_flow_map_context_helper_0049dda0(int param_1,int param_2,int *param_3,int *param_4)

{
  float fVar1;
  double dVar2;
  float *pfVar3;
  int iVar4;
  float *pfVar5;
  float10 fVar6;
  float10 extraout_ST0;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0 [10];
  double local_98;
  double local_90;
  double local_88;
  float local_80 [10];
  undefined8 local_58;
  double local_50;
  undefined8 local_48;
  float local_40 [16];
  
  local_cc = (float)*(double *)(param_1 + 0x40);
  local_d4 = (float)*(double *)(param_1 + 0x48);
  local_c4 = (float)*(double *)(param_1 + 0x50);
  local_d8 = (float)*param_3 * _DAT_004be9c0;
  local_d0 = (float)*param_4 * _DAT_004be9c0;
  local_e4 = (float)*(double *)(param_2 + 0x40) - local_cc;
  local_e0 = (float)*(double *)(param_2 + 0x48) -
             ((float)*(double *)(param_1 + 0x48) - _DAT_004be9fc);
  local_dc = (float)*(double *)(param_2 + 0x50) - local_c4;
  local_c8 = local_d0 + local_d4;
  dVar2 = (double)(local_dc * local_dc + local_e0 * local_e0 + local_e4 * local_e4);
  fVar6 = zone_satellite_map_context_helper_00495000
                    (SUB84(dVar2,0),(uint)((ulonglong)dVar2 >> 0x20));
  fVar1 = (float)fVar6;
  local_e4 = local_e4 * fVar1;
  local_e0 = local_e0 * fVar1;
  local_dc = local_dc * fVar1;
  local_cc = local_cc - local_e4 * local_d8;
  local_c8 = local_c8 - local_e0 * local_d8;
  local_c4 = local_c4 - local_dc * local_d8;
  pfVar3 = (float *)zone_satellite_map_context_helper_00494880(&local_cc,&local_e4,local_40);
  pfVar5 = local_c0;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar5 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar5 = pfVar5 + 1;
  }
  if (_DAT_004bea00 < fVar1) {
    local_e8 = (fVar1 - _DAT_004bea00) * _DAT_004bea04;
    if (_DAT_004bea08 <= local_e8) {
      local_e8 = 0.5235988;
    }
    dVar2 = (double)(local_dc * local_dc + local_e4 * local_e4);
    fVar6 = zone_satellite_map_context_helper_00495000
                      (SUB84(dVar2,0),(uint)((ulonglong)dVar2 >> 0x20));
    local_d4 = (float)fVar6;
    pfVar3 = (float *)zone_satellite_map_context_helper_00494460
                                (local_40,-local_e8,local_dc * local_d4,0.0,-(local_e4 * local_d4));
    dVar2 = *(double *)(param_1 + 0x48);
    local_58 = *(undefined8 *)(param_1 + 0x40);
    local_48 = *(undefined8 *)(param_1 + 0x50);
    pfVar5 = local_80;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar5 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      pfVar5 = pfVar5 + 1;
    }
    local_98 = (double)-(local_e4 * local_d8);
    local_90 = (double)-(local_e0 * local_d8);
    local_88 = (double)-(local_dc * local_d8);
    local_50 = (double)(local_d0 + (float)dVar2);
    pfVar3 = compose_matrix_or_transform_a(local_40,local_c0,local_80);
    pfVar5 = local_c0;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar5 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      pfVar5 = pfVar5 + 1;
    }
  }
  apply_world_object_transform_to_bounds_or_geometry(local_98,local_88);
  if ((float10)local_90 < extraout_ST0 - (float10)_DAT_004be9c8) {
    local_90 = (double)(extraout_ST0 - (float10)_DAT_004be9c8);
  }
  software_raster_queue_context_helper_00472990(0x4c2730,local_c0);
  DAT_005a7ed8 = 0;
  DAT_005a7edc = 0;
  DAT_005a7ee0 = mission_flow_map_context_helper_0049dda0;
  return;
}


