/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00415e30
 * Entry: 00401276
 * Signature: int __cdecl thunk_FUN_00415e30(int param_1)
 */


int __cdecl thunk_FUN_00415e30(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  do {
    iVar1 = thunk_FUN_004022b0(param_1,DAT_0043c544);
  } while (iVar1 < 0);
  iVar2 = thunk_FUN_0041bcb0(param_1);
  iVar3 = thunk_FUN_0041bcb0(param_1);
  iVar4 = thunk_FUN_0041bcb0(param_1);
  return iVar4 + iVar1 + iVar2 + iVar3;
}


