/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049e0f0
 * Entry: 0049e0f0
 * Signature: undefined __cdecl mission_flow_map_context_helper_0049e0f0(double * param_1, float param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049e0f0.
   Remove duplicated mission-flow/map wording. */

void __cdecl mission_flow_map_context_helper_0049e0f0(double *param_1,float param_2,float param_3)

{
  double dVar1;
  float fVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  
  if (param_3 < _DAT_004bea10) {
    param_3 = 4.0;
  }
  fVar4 = (float10)_DAT_004bea14;
  iVar3 = 200;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)((int)param_1 + 0x14) = 0x3ff00000;
  *(undefined4 *)((int)param_1 + 0x1c) = 0;
  *(undefined4 *)((int)param_1 + 0x24) = 0;
  fVar4 = (float10)fcos(fVar4 / (float10)param_3);
  fVar4 = fVar4 * (float10)param_2 * (float10)_DAT_004bea18;
  param_1[1] = (double)((float10)param_2 * (float10)param_2);
  *param_1 = (double)fVar4;
  do {
    dVar1 = param_1[4];
    fVar5 = (float10)_DAT_004bea20;
    *(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_1 + 3);
    iVar3 = iVar3 + -1;
    fVar5 = (fVar5 - (float10)param_1[3] * fVar4) -
            (float10)dVar1 * (float10)param_2 * (float10)param_2;
    *(undefined4 *)((int)param_1 + 0x24) = *(undefined4 *)((int)param_1 + 0x1c);
    param_1[3] = (double)fVar5;
  } while (iVar3 != 0);
  fVar2 = _DAT_004bea28 / (float)fVar5;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)((int)param_1 + 0x1c) = 0;
  *(undefined4 *)((int)param_1 + 0x24) = 0;
  param_1[2] = (double)fVar2;
  return;
}


