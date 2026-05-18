/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00415980
 * Entry: 00401410
 * Signature: undefined4 __cdecl thunk_FUN_00415980(int param_1, int param_2, int param_3, int param_4)
 */


undefined4 __cdecl thunk_FUN_00415980(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = (param_2 / 3) * 4 + *(int *)(param_1 + 8);
    *(int *)(iVar1 + 0x40) = param_3;
    *(int *)(iVar1 + 0x48) = param_4;
  }
  if (param_3 != 0) {
    iVar1 = *(int *)(param_3 + 8);
    *(int *)(iVar1 + 0x40 + (param_4 / 3) * 4) = param_1;
    *(int *)(iVar1 + 0x48 + (param_4 / 3) * 4) = param_2;
  }
  return 1;
}


