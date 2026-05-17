/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049c6d0
 * Entry: 0049c6d0
 * Signature: undefined __cdecl mission_flow_map_context_helper_0049c6d0(int param_1, float param_2, float param_3, float param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049c6d0.
   Remove duplicated mission-flow/map wording. */

void __cdecl
mission_flow_map_context_helper_0049c6d0(int param_1,float param_2,float param_3,float param_4)

{
  float fVar1;
  int iVar2;
  float fVar3;
  
  fVar1 = param_3;
  while( true ) {
    fVar3 = (float)((int)fVar1 + param_1 >> 1);
    iVar2 = rand();
    param_3 = (float)((int)fVar1 - param_1) * ((float)iVar2 * _DAT_004be974 - _DAT_004be978) *
              _DAT_004be98c - (param_4 + param_2) * _DAT_004be984;
    if (_DAT_004be978 < param_3) {
      param_3 = 1.0;
    }
    if (param_3 < _DAT_004be988) {
      param_3 = -1.0;
    }
    (&DAT_006543e0)[(int)fVar3] = param_3;
    if (fVar3 == (float)param_1) break;
    mission_flow_map_context_helper_0049c6d0(param_1,param_2,fVar3,param_3);
    param_2 = param_3;
    param_1 = (int)fVar3;
  }
  return;
}


