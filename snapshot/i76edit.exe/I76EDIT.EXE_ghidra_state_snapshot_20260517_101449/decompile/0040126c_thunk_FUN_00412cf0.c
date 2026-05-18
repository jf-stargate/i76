/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00412cf0
 * Entry: 0040126c
 * Signature: undefined8 __cdecl thunk_FUN_00412cf0(undefined4 param_1, undefined4 param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __cdecl thunk_FUN_00412cf0(undefined4 param_1,undefined4 param_2,int param_3)

{
  longlong lVar1;
  longlong lVar2;
  
  fcos(-((float10)param_3 * (float10)_DAT_00432150));
  fsin(-((float10)param_3 * (float10)_DAT_00432150));
  __ftol();
  __ftol();
  lVar1 = __ftol();
  lVar2 = __ftol();
  return CONCAT44((int)lVar2,(int)lVar1);
}


