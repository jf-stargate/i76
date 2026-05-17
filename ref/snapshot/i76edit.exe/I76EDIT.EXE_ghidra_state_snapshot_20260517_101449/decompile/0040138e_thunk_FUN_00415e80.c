/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00415e80
 * Entry: 0040138e
 * Signature: float10 __cdecl thunk_FUN_00415e80(int param_1, int param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl thunk_FUN_00415e80(int param_1,int param_2,int param_3)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float10 fVar6;
  
  iVar1 = *(int *)(param_1 + 8);
  fVar2 = *(float *)(iVar1 + 0x34) - *(float *)(iVar1 + 0x10);
  fVar3 = *(float *)(iVar1 + 0x38) - *(float *)(iVar1 + 0x14);
  fVar4 = ((float)param_3 - *(float *)(iVar1 + 0x14)) * fVar3 +
          fVar2 * ((float)param_2 - *(float *)(iVar1 + 0x10));
  fVar5 = fVar2 * fVar2 + fVar3 * fVar3;
  if (fVar5 == (float)_DAT_00432170) {
    return (float10)_DAT_00432178;
  }
  fVar2 = (float)param_2 - ((fVar2 / fVar5) * fVar4 + *(float *)(iVar1 + 0x10));
  fVar6 = (float10)param_3 -
          (((float10)fVar3 / (float10)fVar5) * (float10)fVar4 + (float10)*(float *)(iVar1 + 0x14));
  return SQRT((float10)fVar2 * (float10)fVar2 + fVar6 * (float10)(float)fVar6);
}


