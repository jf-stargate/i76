/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049dac0
 * Entry: 0049dac0
 * Signature: undefined __cdecl mission_flow_map_context_helper_0049dac0(float param_1, int * param_2, int * param_3, int * param_4, int * param_5, int * param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049dac0.
   Remove duplicated mission-flow/map wording. */

void __cdecl
mission_flow_map_context_helper_0049dac0
          (float param_1,int *param_2,int *param_3,int *param_4,int *param_5,int *param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  int iVar5;
  float *pfVar6;
  float10 fVar7;
  float10 extraout_ST0;
  float local_94 [16];
  float local_54 [16];
  float local_14;
  float local_10;
  double local_c;
  
  fVar3 = param_1;
  if ((DAT_005a7ee0 != mission_flow_map_context_helper_0049dac0) || (DAT_005a7edc != param_1)) {
    mission_flow_map_context_helper_0049da00(0.0,0,(int)param_1);
    _DAT_005a7ef8 = _DAT_005a7f08;
    _DAT_005a7f00 = _DAT_005a7f10;
  }
  local_10 = (float)*param_2 * _DAT_004be9c0;
  fVar1 = (float)(*param_5 % 36000) * _DAT_004be9c4;
  local_14 = (float)(*param_4 % 36000) * _DAT_004be9c4;
  param_1 = 0.0;
  fVar2 = (float)(*param_6 % 36000) * _DAT_004be9c4;
  if (param_3 != (int *)0x0) {
    param_1 = (float)*param_3 * _DAT_004be9c0;
  }
  fVar7 = get_runtime_frame_delta_seconds();
  local_c = (double)(fVar7 * (float10)param_1 * (float10)_DAT_005a7ef0);
  if (_DAT_004be9d8 < _DAT_005a7ee8) {
    if (*(int *)((int)fVar3 + 0x50) <= DAT_005a7ee4 + 2) {
      DAT_005a7edc = 0.0;
      DAT_005a7ee0 = (code *)0x0;
      DAT_005a7ed8 = 1;
      return;
    }
    param_2 = (int *)((float)_DAT_005a7ee8 - ((float)_DAT_005a7ee8 / 1.0) * 1.0);
    if ((float)param_2 < _DAT_004be9e4) {
      param_2 = (int *)((float)param_2 - _DAT_004be9e8);
    }
    mission_flow_map_context_helper_0049da00((float)param_2,DAT_005a7ee4 + 1,(int)fVar3);
  }
  DAT_005a7ee0 = mission_flow_map_context_helper_0049dac0;
  DAT_005a7edc = fVar3;
  DAT_005a7ed8 = 0;
  apply_world_object_transform_to_bounds_or_geometry(_DAT_005a7ef8,_DAT_005a7f00);
  param_1 = (float)(extraout_ST0 + (float10)local_10);
  if ((float10)param_1 < extraout_ST0 - (float10)_DAT_004be9c8) {
    param_1 = (float)(extraout_ST0 - (float10)_DAT_004be9c8);
  }
  pfVar4 = (float *)zone_satellite_map_context_helper_00493e60
                              (local_94,local_14,fVar2,fVar1,(float)_DAT_005a7ef8,param_1,
                               (float)_DAT_005a7f00);
  pfVar6 = local_54;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar6 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar6 = pfVar6 + 1;
  }
  software_raster_queue_context_helper_00472990(0x4c2730,local_54);
  fVar1 = (float)_DAT_005a7f08;
  fVar3 = fVar1 - (float)_DAT_005a7ef8;
  if ((float)_DAT_004be9f0 <= ABS(fVar3)) {
    fVar1 = (float)_DAT_005a7ef8 - fVar3 * _DAT_004be9f8;
  }
  _DAT_005a7ef8 = (double)fVar1;
  fVar1 = (float)_DAT_005a7f10;
  fVar3 = fVar1 - (float)_DAT_005a7f00;
  if ((float)_DAT_004be9f0 <= ABS(fVar3)) {
    fVar1 = (float)_DAT_005a7f00 - fVar3 * _DAT_004be9f8;
  }
  _DAT_005a7f00 = (double)fVar1;
  _DAT_005a7ee8 = local_c + _DAT_005a7ee8;
  _DAT_005a7f08 = local_c * _DAT_005a7f18 + _DAT_005a7f08;
  _DAT_005a7f10 = local_c * _DAT_005a7f20 + _DAT_005a7f10;
  return;
}


