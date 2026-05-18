/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004089e0
 * Entry: 00401537
 * Signature: undefined8 __fastcall thunk_FUN_004089e0(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, int param_5, undefined4 * param_6, undefined4 * param_7)
 */


undefined8 __fastcall
thunk_FUN_004089e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  int param_5,undefined4 *param_6,undefined4 *param_7)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  longlong lVar5;
  int iStack_c;
  undefined4 *puStack_8;
  int iStack_4;
  
  puStack_8 = (undefined4 *)0x0;
  iStack_4 = -1;
  iStack_c = 0x7fffffff;
  for (puVar1 = DAT_00439be4; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    if (puVar1 != param_6) {
      iVar3 = 0;
      piVar4 = (int *)(puVar1[2] + 0x18);
      do {
        if (*piVar4 == 0) {
          __ftol();
          __ftol();
          lVar5 = thunk_FUN_0041f560();
          param_2 = (undefined4)((ulonglong)lVar5 >> 0x20);
          iVar2 = (int)lVar5;
          if ((iVar2 < param_5) && (iVar2 < iStack_c)) {
            iStack_c = iVar2;
            puStack_8 = puVar1;
            iStack_4 = iVar3;
          }
        }
        piVar4 = piVar4 + 1;
        iVar3 = iVar3 + 1;
      } while (iVar3 < 2);
    }
  }
  *param_7 = puStack_8;
  return CONCAT44(param_2,iStack_4);
}


