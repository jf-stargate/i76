/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004088c0
 * Entry: 00401159
 * Signature: uint __cdecl thunk_FUN_004088c0(uint param_1)
 */


uint __cdecl thunk_FUN_004088c0(uint param_1)

{
  uint uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  if ((*(int *)(*(int *)(param_1 + 8) + 0x18) != 0) && (*(int *)(*(int *)(param_1 + 8) + 0x1c) != 0)
     ) {
    param_1 = FUN_00409070(param_1);
  }
  if ((*(uint *)(*(int *)(param_1 + 8) + 0x50) & 1) == 0) {
    uVar1 = FUN_00409070(param_1);
    param_1 = (*(int *)(*(int *)(uVar1 + 8) + 0x50) << 0x1f) >> 0x1f & uVar1;
  }
  return param_1;
}


