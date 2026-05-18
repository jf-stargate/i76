/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00408bc0
 * Entry: 004014d8
 * Signature: undefined4 __cdecl thunk_FUN_00408bc0(int param_1, int param_2, int param_3, int param_4)
 */


undefined4 __cdecl thunk_FUN_00408bc0(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if ((param_1 != 0) && (iVar1 = *(int *)(param_1 + 8), iVar1 != 0)) {
    *(int *)(iVar1 + 0x18 + param_2 * 4) = param_3;
    *(int *)(iVar1 + 0x20 + param_2 * 4) = param_4;
  }
  if ((param_3 != 0) && (iVar1 = *(int *)(param_3 + 8), iVar1 != 0)) {
    *(int *)(iVar1 + 0x18 + param_4 * 4) = param_1;
    *(int *)(iVar1 + 0x20 + param_4 * 4) = param_2;
  }
  return 1;
}


