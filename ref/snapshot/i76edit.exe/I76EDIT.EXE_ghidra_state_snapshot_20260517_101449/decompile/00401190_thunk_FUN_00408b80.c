/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00408b80
 * Entry: 00401190
 * Signature: undefined4 __cdecl thunk_FUN_00408b80(int param_1, int param_2, int param_3, int param_4)
 */


undefined4 __cdecl thunk_FUN_00408b80(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 8);
  *(float *)(iVar1 + param_2 * 0xc) = (float)param_3;
  *(float *)(iVar1 + 4 + param_2 * 0xc) = (float)param_4;
  return 1;
}


