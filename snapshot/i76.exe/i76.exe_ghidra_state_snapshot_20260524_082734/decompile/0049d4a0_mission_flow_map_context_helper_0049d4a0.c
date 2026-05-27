/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049d4a0
 * Entry: 0049d4a0
 * Signature: undefined __cdecl mission_flow_map_context_helper_0049d4a0(int param_1, int * param_2, int * param_3, int * param_4, int * param_5, int * param_6, int * param_7)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049d4a0.
   Remove duplicated mission-flow/map wording. */

void __cdecl
mission_flow_map_context_helper_0049d4a0
          (int param_1,int *param_2,int *param_3,int *param_4,int *param_5,int *param_6,int *param_7
          )

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  float10 extraout_ST0;
  float local_80 [10];
  undefined4 local_58;
  undefined4 local_54;
  double local_50;
  undefined4 local_48;
  undefined4 local_44;
  float local_40 [16];
  
  pfVar1 = (float *)zone_satellite_map_context_helper_00493e60
                              (local_40,(float)(*param_5 % 36000) * _DAT_004be9c4,
                               (float)(*param_7 % 36000) * _DAT_004be9c4,
                               (float)(*param_6 % 36000) * _DAT_004be9c4,
                               (float)*param_2 * _DAT_004be9c0,(float)*param_3 * _DAT_004be9c0,
                               (float)*param_4 * _DAT_004be9c0);
  pfVar3 = local_80;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  pfVar1 = compose_matrix_or_transform_a(local_40,local_80,(float *)(param_1 + 0x18));
  pfVar3 = local_80;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  apply_world_object_transform_to_bounds_or_geometry
            ((double)CONCAT44(local_54,local_58),(double)CONCAT44(local_44,local_48));
  if ((float10)local_50 < extraout_ST0 - (float10)_DAT_004be9c8) {
    local_50 = (double)(extraout_ST0 - (float10)_DAT_004be9c8);
  }
  software_raster_queue_context_helper_00472990(0x4c2730,local_80);
  DAT_005a7ed8 = 0;
  DAT_005a7edc = 0;
  DAT_005a7ee0 = mission_flow_map_context_helper_0049d4a0;
  return;
}


