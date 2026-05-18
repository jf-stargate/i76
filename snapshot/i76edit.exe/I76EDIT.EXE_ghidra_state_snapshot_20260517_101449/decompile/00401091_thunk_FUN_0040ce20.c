/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040ce20
 * Entry: 00401091
 * Signature: undefined4 __cdecl thunk_FUN_0040ce20(undefined4 param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_0040ce20(undefined4 param_1,undefined4 param_2,uint param_3)

{
  HWND pHVar1;
  
  pHVar1 = GetFocus();
  if (pHVar1 != DAT_01641fac) {
    thunk_FUN_0040d0f0(param_3 & 0xffff,param_3 >> 0x10);
    return 1;
  }
  return 0;
}


