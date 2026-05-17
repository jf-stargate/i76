/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004158b0
 * Entry: 0040109b
 * Signature: undefined4 __cdecl thunk_FUN_004158b0(int param_1, int param_2, int param_3, int param_4)
 */


undefined4 __cdecl thunk_FUN_004158b0(int param_1,int param_2,int param_3,int param_4)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  piVar1 = *(int **)(param_1 + 8);
  fVar2 = (float)piVar1[param_2 * 3 + 4];
  fVar3 = (float)piVar1[param_2 * 3 + 5];
  piVar1[param_2 * 3 + 4] = (int)(float)param_3;
  piVar1[param_2 * 3 + 5] = (int)(float)param_4;
  if ((param_2 == 0) || (param_2 == 3)) {
    iVar4 = *piVar1;
    if (iVar4 == 1) {
      iVar4 = (uint)(param_2 == 0) * -3;
      piVar1[iVar4 + 10] = (int)(((float)piVar1[iVar4 + 10] - fVar2) + (float)param_3);
      piVar1[iVar4 + 0xb] = (int)(((float)piVar1[iVar4 + 0xb] - fVar3) + (float)param_4);
    }
    else if ((iVar4 == 0) || (iVar4 == 2)) {
      thunk_FUN_00415fa0((int)piVar1);
    }
  }
  return 1;
}


