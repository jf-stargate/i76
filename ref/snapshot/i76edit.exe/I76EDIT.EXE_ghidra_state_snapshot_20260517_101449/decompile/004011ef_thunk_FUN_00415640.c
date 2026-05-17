/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00415640
 * Entry: 004011ef
 * Signature: undefined8 __fastcall thunk_FUN_00415640(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, int param_5, undefined4 * param_6, undefined4 * param_7)
 */


undefined8 __fastcall
thunk_FUN_00415640(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  int param_5,undefined4 *param_6,undefined4 *param_7)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  longlong lVar5;
  int iStack_c;
  undefined4 *puStack_8;
  int iStack_4;
  
  puStack_8 = (undefined4 *)0x0;
  iStack_4 = -1;
  iStack_c = 0x7fffffff;
  for (puVar1 = DAT_0043c544; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    if (puVar1 != param_6) {
      iVar4 = 0;
      piVar3 = (int *)(puVar1[2] + 0x40);
      do {
        if (*piVar3 == 0) {
          __ftol();
          __ftol();
          lVar5 = thunk_FUN_0041f560();
          param_2 = (undefined4)((ulonglong)lVar5 >> 0x20);
          iVar2 = (int)lVar5;
          if ((iVar2 < param_5) && (iVar2 < iStack_c)) {
            iStack_c = iVar2;
            puStack_8 = puVar1;
            iStack_4 = iVar4;
          }
        }
        iVar4 = iVar4 + 3;
        piVar3 = piVar3 + 1;
      } while (iVar4 < 6);
    }
  }
  *param_7 = puStack_8;
  return CONCAT44(param_2,iStack_4);
}


