/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00405d80
 * Entry: 0040136b
 * Signature: undefined4 __cdecl thunk_FUN_00405d80(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_00405d80(HWND param_1,undefined4 param_2,uint param_3)

{
  longlong lVar1;
  int iVar2;
  longlong lVar3;
  
  lVar3 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
  iVar2 = (int)((ulonglong)lVar3 >> 0x20);
  lVar1 = CONCAT44(DAT_00439b9c,DAT_00439b98);
  if ((DAT_00434438 != 0) && (lVar1 = lVar3, lVar3 != CONCAT44(DAT_00439b9c,DAT_00439b98))) {
    if (DAT_00434434 == 5) {
      FUN_00405e50(param_1,DAT_00439b98,DAT_00439b9c,(int)lVar3,iVar2);
    }
    else {
      thunk_FUN_00406950((int)lVar3,iVar2);
    }
  }
  DAT_00439b9c = (int)((ulonglong)lVar1 >> 0x20);
  DAT_00439b98 = (int)lVar1;
  return 1;
}


