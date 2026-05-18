/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040d530
 * Entry: 00401041
 * Signature: undefined __cdecl thunk_FUN_0040d530(undefined2 param_1)
 */


void __cdecl thunk_FUN_0040d530(undefined2 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_004347d0;
  iVar1 = DAT_004347cc;
  if ((DAT_004347cc != -1) && (DAT_004347d0 != -1)) {
    DAT_004347d0 = -1;
    DAT_004347cc = -1;
    (&DAT_0163ce72)[(iVar2 + iVar1 * 0x32) * 2] = param_1;
  }
  return;
}


