/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00408920
 * Entry: 00401023
 * Signature: undefined8 __fastcall thunk_FUN_00408920(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, int param_5, undefined4 * param_6)
 */


undefined8 __fastcall
thunk_FUN_00408920(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  int param_5,undefined4 *param_6)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  int iStack_c;
  undefined4 *puStack_8;
  int iStack_4;
  
  puStack_8 = (undefined4 *)0x0;
  iStack_4 = -1;
  iStack_c = 0x7fffffff;
  for (puVar1 = DAT_00439be4; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    iVar3 = 0;
    do {
      __ftol();
      __ftol();
      lVar4 = thunk_FUN_0041f560();
      param_2 = (undefined4)((ulonglong)lVar4 >> 0x20);
      iVar2 = (int)lVar4;
      if ((iVar2 < param_5) && (iVar2 < iStack_c)) {
        iStack_c = iVar2;
        puStack_8 = puVar1;
        iStack_4 = iVar3;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 2);
  }
  *param_6 = puStack_8;
  return CONCAT44(param_2,iStack_4);
}


