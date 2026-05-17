/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049da00
 * Entry: 0049da00
 * Signature: undefined __cdecl mission_flow_map_context_helper_0049da00(float param_1, int param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049da00.
   Remove duplicated mission-flow/map wording. */

void __cdecl mission_flow_map_context_helper_0049da00(float param_1,int param_2,int param_3)

{
  double dVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float10 fVar6;
  
  DAT_005a7ee4 = param_2;
  iVar2 = *(int *)(param_3 + 0x54);
  iVar5 = param_2 * 0xc;
  fVar3 = *(float *)(iVar2 + (param_2 + 1) * 0xc) - *(float *)(iVar5 + iVar2);
  fVar4 = *(float *)(iVar5 + 0x14 + iVar2) - *(float *)(iVar5 + 8 + iVar2);
  _DAT_005a7f18 = (double)fVar3;
  _DAT_005a7ee8 = (double)param_1;
  _DAT_005a7f20 = (double)fVar4;
  _DAT_005a7f08 = (double)(param_1 * fVar3 + *(float *)(*(int *)(param_3 + 0x54) + iVar5));
  _DAT_005a7f10 = (double)(param_1 * fVar4 + *(float *)(*(int *)(param_3 + 0x54) + 8 + iVar5));
  dVar1 = (double)(fVar4 * fVar4 + fVar3 * fVar3);
  fVar6 = zone_satellite_map_context_helper_00495000
                    (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  _DAT_005a7ef0 = (double)fVar6;
  return;
}


