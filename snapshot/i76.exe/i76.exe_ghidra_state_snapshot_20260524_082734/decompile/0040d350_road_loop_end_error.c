/*
 * Program: i76.exe
 * Function: road_loop_end_error
 * Entry: 0040d350
 * Signature: undefined4 __cdecl road_loop_end_error(int param_1, int * param_2, int * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: road loop off the end of the road */

undefined4 __cdecl road_loop_end_error(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  *param_2 = param_1;
  while ((iVar1 = *(int *)(*param_2 + 8), iVar1 != 0 && (*(int *)(iVar1 + 0xc) != 1))) {
    *param_2 = iVar1;
  }
  *param_3 = param_1;
  while (*(int *)(*param_3 + 0xc) == 0) {
    if (*(int *)(*param_3 + 4) == 0) {
      report_error();
    }
    *param_3 = *(int *)(*param_3 + 4);
  }
  iVar4 = *(int *)(*param_3 + 0x14) + -1;
  iVar1 = *(int *)(*param_3 + 0x28);
  fVar2 = *(float *)(*(int *)(*param_2 + 0x28) + 0xc) - *(float *)(iVar1 + 0xc + iVar4 * 0x18);
  fVar3 = *(float *)(*(int *)(*param_2 + 0x28) + 0x14) - *(float *)(iVar1 + 0x14 + iVar4 * 0x18);
  if (fVar3 * fVar3 + fVar2 * fVar2 < _DAT_004bc6bc) {
    return 1;
  }
  return 0;
}


