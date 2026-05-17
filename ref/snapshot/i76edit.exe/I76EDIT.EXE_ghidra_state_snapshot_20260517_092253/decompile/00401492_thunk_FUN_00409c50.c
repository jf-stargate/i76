/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409c50
 * Entry: 00401492
 * Signature: undefined4 __cdecl thunk_FUN_00409c50(int param_1, int param_2)
 */


undefined4 __cdecl thunk_FUN_00409c50(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_1 + 8);
  uVar2 = *(uint *)(iVar1 + 0x60);
  *(uint *)(iVar1 + 0x60) = uVar2 & 0xfffffeff;
  uVar2 = uVar2 & 0xfff8feff;
  *(uint *)(iVar1 + 0x60) = uVar2;
  *(uint *)(iVar1 + 0x60) = param_2 << 0x10 | uVar2;
  return 1;
}


