/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041e370
 * Entry: 0040137f
 * Signature: undefined __cdecl thunk_FUN_0041e370(byte param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl thunk_FUN_0041e370(byte param_1)

{
  thunk_FUN_0041e3e0();
  ShowWindow((HWND)(&DAT_01642380)[DAT_00433a34],0);
  DAT_00433a34 = param_1;
  thunk_FUN_0041e510();
  ShowWindow((HWND)(&DAT_01642380)[DAT_00433a34],5);
  _DAT_01641fb0 = (ushort)param_1 << 8;
  return;
}


