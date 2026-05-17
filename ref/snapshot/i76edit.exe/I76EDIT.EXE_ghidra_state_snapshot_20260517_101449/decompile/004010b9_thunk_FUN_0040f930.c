/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040f930
 * Entry: 004010b9
 * Signature: undefined4 __cdecl thunk_FUN_0040f930(int param_1, int param_2, int param_3, int param_4)
 */


undefined4 __cdecl thunk_FUN_0040f930(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int *piVar5;
  
  iVar1 = *(int *)(param_1 + 8);
  piVar5 = (int *)(iVar1 + 0x78);
  fVar2 = *(float *)(iVar1 + 0x88 + param_2 * 0xc);
  fVar3 = (float)piVar5[param_2 * 3 + 5];
  piVar5[param_2 * 3 + 4] = (int)(float)param_3;
  piVar5[param_2 * 3 + 5] = (int)(float)param_4;
  if ((param_2 == 0) || (param_2 == 3)) {
    iVar4 = *piVar5;
    if (iVar4 == 1) {
      iVar4 = (uint)(param_2 == 0) * -3;
      piVar5[iVar4 + 10] =
           (int)((*(float *)(iVar1 + 0x88 + (iVar4 + 6) * 4) - fVar2) + (float)param_3);
      piVar5[iVar4 + 0xb] = (int)(((float)piVar5[iVar4 + 0xb] - fVar3) + (float)param_4);
    }
    else if ((iVar4 == 0) || (iVar4 == 2)) {
      thunk_FUN_00415fa0((int)piVar5);
    }
  }
  return 1;
}


