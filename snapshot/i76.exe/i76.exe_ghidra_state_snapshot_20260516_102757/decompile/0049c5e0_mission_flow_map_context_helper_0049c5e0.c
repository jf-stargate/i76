/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049c5e0
 * Entry: 0049c5e0
 * Signature: undefined __stdcall mission_flow_map_context_helper_0049c5e0(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049c5e0.
   Remove duplicated mission-flow/map wording. */

void mission_flow_map_context_helper_0049c5e0(void)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  float local_8;
  
  iVar3 = rand();
  fVar2 = (float)iVar3 * _DAT_004be974 - _DAT_004be978;
  iVar3 = rand();
  local_8 = ((float)iVar3 * _DAT_004be974 - _DAT_004be978) * _DAT_004be97c -
            (fVar2 + fVar2) * _DAT_004be984;
  if (_DAT_004be978 < local_8) {
    local_8 = 1.0;
  }
  if (local_8 < _DAT_004be988) {
    local_8 = -1.0;
  }
  _DAT_006545e0 = local_8;
  mission_flow_map_context_helper_0049c6d0(0,fVar2,1.79366e-43,local_8);
  mission_flow_map_context_helper_0049c6d0(0x80,local_8,3.58732e-43,fVar2);
  pfVar4 = (float *)&DAT_006543e0;
  fVar2 = _DAT_006547dc;
  do {
    fVar1 = *pfVar4;
    pfVar5 = pfVar4 + 1;
    *pfVar4 = fVar1 - fVar2;
    pfVar4 = pfVar5;
    fVar2 = fVar1;
  } while ((int)pfVar5 < 0x6547e0);
  return;
}


