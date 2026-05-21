/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049d740
 * Entry: 0049d740
 * Signature: undefined __cdecl mission_flow_map_context_helper_0049d740(int param_1, int * param_2, int * param_3, int param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049d740.
   Remove duplicated mission-flow/map wording. */

void __cdecl
mission_flow_map_context_helper_0049d740(int param_1,int *param_2,int *param_3,int param_4)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  int iVar4;
  float *pfVar5;
  float10 fVar6;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float local_a4 [16];
  float local_64 [10];
  undefined4 local_3c;
  undefined4 local_38;
  double local_34;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  undefined8 local_20;
  float local_18;
  float local_14;
  float local_10;
  double local_c;
  
  if ((DAT_005a7ee0 != mission_flow_map_context_helper_0049d740) || (DAT_005a7edc != param_1)) {
    mission_flow_map_context_helper_0049da00(0.0,0,param_1);
    _DAT_005a7ef8 = _DAT_005a7f08;
    _DAT_005a7f00 = _DAT_005a7f10;
  }
  local_c = 0.0;
  if (param_3 != (int *)0x0) {
    local_c = (double)((float)*param_3 * _DAT_004be9c0);
  }
  local_20 = (double)((float)*param_2 * _DAT_004be9c0);
  fVar6 = get_runtime_frame_delta_seconds();
  local_c = (double)(fVar6 * (float10)local_c * (float10)_DAT_005a7ef0);
  if (_DAT_004be9d8 < _DAT_005a7ee8) {
    if (*(int *)(param_1 + 0x50) <= DAT_005a7ee4 + 2) {
      DAT_005a7edc = 0;
      DAT_005a7ee0 = (code *)0x0;
      DAT_005a7ed8 = 1;
      return;
    }
    param_3 = (int *)((float)_DAT_005a7ee8 - ((float)_DAT_005a7ee8 / 1.0) * 1.0);
    if ((float)param_3 < _DAT_004be9e4) {
      param_3 = (int *)((float)param_3 - _DAT_004be9e8);
    }
    mission_flow_map_context_helper_0049da00((float)param_3,DAT_005a7ee4 + 1,param_1);
  }
  local_18 = (float)_DAT_005a7ef8;
  local_10 = (float)_DAT_005a7f00;
  DAT_005a7ee0 = mission_flow_map_context_helper_0049d740;
  DAT_005a7edc = param_1;
  DAT_005a7ed8 = 0;
  apply_world_object_transform_to_bounds_or_geometry(_DAT_005a7ef8,_DAT_005a7f00);
  local_14 = (float)((float10)local_20 + extraout_ST0);
  local_24 = (float)*(double *)(param_4 + 0x40) - local_18;
  local_20 = (double)CONCAT44((float)*(double *)(param_4 + 0x50) - local_10,
                              (float)*(double *)(param_4 + 0x48) - local_14);
  pfVar3 = (float *)zone_satellite_map_context_helper_00494880(&local_18,&local_24,local_a4);
  pfVar5 = local_64;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar5 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar5 = pfVar5 + 1;
  }
  apply_world_object_transform_to_bounds_or_geometry
            ((double)CONCAT44(local_38,local_3c),(double)CONCAT44(local_28,local_2c));
  if ((float10)local_34 < extraout_ST0_00 - (float10)_DAT_004be9c8) {
    local_34 = (double)(extraout_ST0_00 - (float10)_DAT_004be9c8);
  }
  software_raster_queue_context_helper_00472990(0x4c2730,local_64);
  fVar2 = (float)_DAT_005a7f08;
  fVar1 = fVar2 - (float)_DAT_005a7ef8;
  if ((float)_DAT_004be9f0 <= ABS(fVar1)) {
    fVar2 = (float)_DAT_005a7ef8 - fVar1 * _DAT_004be9f8;
  }
  _DAT_005a7ef8 = (double)fVar2;
  fVar2 = (float)_DAT_005a7f10;
  fVar1 = fVar2 - (float)_DAT_005a7f00;
  if ((float)_DAT_004be9f0 <= ABS(fVar1)) {
    fVar2 = (float)_DAT_005a7f00 - fVar1 * _DAT_004be9f8;
  }
  _DAT_005a7f00 = (double)fVar2;
  _DAT_005a7ee8 = local_c + _DAT_005a7ee8;
  _DAT_005a7f08 = local_c * _DAT_005a7f18 + _DAT_005a7f08;
  _DAT_005a7f10 = local_c * _DAT_005a7f20 + _DAT_005a7f10;
  return;
}


