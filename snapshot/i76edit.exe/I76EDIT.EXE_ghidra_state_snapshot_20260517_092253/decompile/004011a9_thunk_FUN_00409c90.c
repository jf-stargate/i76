/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409c90
 * Entry: 004011a9
 * Signature: uint __cdecl thunk_FUN_00409c90(int param_1)
 */


uint __cdecl thunk_FUN_00409c90(int param_1)

{
  return (*(uint *)(*(int *)(param_1 + 8) + 0x60) & 0x70000) >> 0x10;
}


