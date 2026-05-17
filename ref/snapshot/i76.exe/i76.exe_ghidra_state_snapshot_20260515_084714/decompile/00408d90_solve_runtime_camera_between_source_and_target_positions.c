/*
 * Program: i76.exe
 * Function: solve_runtime_camera_between_source_and_target_positions
 * Entry: 00408d90
 * Signature: undefined __cdecl solve_runtime_camera_between_source_and_target_positions(double * param_1, double * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v5 runtime camera cluster: Builds a camera transform between source and target
   positions with distance/tilt limiting, then writes the active camera matrix. */

void __cdecl
solve_runtime_camera_between_source_and_target_positions(double *param_1,double *param_2)

{
  double dVar1;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  float10 fVar5;
  float10 extraout_ST0;
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
  double local_58;
  double local_50;
  double local_48;
  float local_40 [16];
  
  fVar5 = (float10)param_2[1] - ((float10)param_1[1] - (float10)_DAT_004bc5c0);
  local_e0 = (float)((float10)*param_2 - (float10)*param_1);
  local_dc = (float)fVar5;
  local_d8 = (float)((float10)param_2[2] - (float10)param_1[2]);
  local_cc = (float)param_1[1] - _DAT_004bc5b8;
  local_d0 = (float)*param_1;
  local_c8 = (float)param_1[2];
  dVar1 = (double)(((float10)param_2[2] - (float10)param_1[2]) * (float10)local_d8 +
                  fVar5 * (float10)local_dc +
                  ((float10)*param_2 - (float10)*param_1) * (float10)local_e0);
  fVar5 = zone_satellite_map_context_helper_00495000
                    (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  local_d4 = (float)fVar5;
  local_e0 = local_e0 * local_d4;
  local_dc = local_dc * local_d4;
  local_d8 = local_d8 * local_d4;
  local_d0 = local_d0 - local_e0 * _DAT_004bc5c8;
  local_cc = local_cc - local_dc * _DAT_004bc5c8;
  local_c8 = local_c8 - local_d8 * _DAT_004bc5c8;
  pfVar2 = (float *)zone_satellite_map_context_helper_00494880(&local_d0,&local_e0,local_40);
  pfVar4 = local_c0;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar4 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar4 = pfVar4 + 1;
  }
  if (_DAT_004bc5cc < local_d4) {
    local_d4 = (local_d4 - _DAT_004bc5cc) * _DAT_004bc5c8;
    if (_DAT_004bc51c <= local_d4) {
      local_d4 = 0.5235988;
    }
    dVar1 = (double)(local_d8 * local_d8 + local_e0 * local_e0);
    fVar5 = zone_satellite_map_context_helper_00495000
                      (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
    local_c4 = (float)fVar5;
    pfVar2 = (float *)zone_satellite_map_context_helper_00494460
                                (local_40,-local_d4,local_d8 * local_c4,0.0,-(local_e0 * local_c4));
    local_50 = param_1[1] - _DAT_004bc5d8;
    local_58 = *param_1;
    local_48 = param_1[2];
    pfVar4 = local_80;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar2;
      pfVar2 = pfVar2 + 1;
      pfVar4 = pfVar4 + 1;
    }
    local_98 = (double)(local_e0 * _DAT_004bc5d0);
    local_90 = (double)(local_dc * _DAT_004bc5d0);
    local_88 = (double)(local_d8 * _DAT_004bc5d0);
    pfVar2 = compose_matrix_or_transform_a(local_40,local_c0,local_80);
    pfVar4 = local_c0;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar2;
      pfVar2 = pfVar2 + 1;
      pfVar4 = pfVar4 + 1;
    }
  }
  apply_world_object_transform_to_bounds_or_geometry(local_98,local_88);
  if ((float10)local_90 - (float10)_DAT_004bc560 < extraout_ST0 - (float10)_DAT_004bc558) {
    local_90 = (double)((extraout_ST0 - (float10)_DAT_004bc558) - (float10)_DAT_004bc568);
  }
  software_raster_queue_context_helper_00472990(0x4c2730,local_c0);
  return;
}


