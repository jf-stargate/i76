/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040cd60
 * Entry: 00401311
 * Signature: undefined4 __cdecl thunk_FUN_0040cd60(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_0040cd60(HWND param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  
  if (DAT_01641fb0 == '\0') {
    iVar1 = thunk_FUN_0040d0f0(param_3 & 0xffff,param_3 >> 0x10);
    if (iVar1 != 0) {
      thunk_FUN_0040d390(param_3 & 0xffff,param_3 >> 0x10);
    }
    return 1;
  }
  if (DAT_01641fb0 != '\x01') {
    if (DAT_01641fb0 != '\x02') {
      return 0;
    }
    return 1;
  }
  thunk_FUN_0040ced0(param_3 & 0xffff,param_3 >> 0x10);
  InvalidateRgn(param_1,(HRGN)0x0,0);
  return 1;
}


