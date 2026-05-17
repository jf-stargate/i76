/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409930
 * Entry: 00401406
 * Signature: undefined4 * __cdecl thunk_FUN_00409930(uint param_1, uint param_2, int param_3, int param_4)
 */


undefined4 * __cdecl thunk_FUN_00409930(uint param_1,uint param_2,int param_3,int param_4)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  int iStack_20;
  undefined4 *puStack_1c;
  int aiStack_c [3];
  
  puStack_1c = (undefined4 *)0x0;
  iStack_20 = 0x7fffffff;
  piVar2 = (int *)thunk_FUN_00412300(aiStack_c,param_1,param_2);
  if (*piVar2 != -1) {
    for (puVar1 = (undefined4 *)(&DAT_00439be8)[*piVar2]; puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      if (param_4 == 1) {
        iVar3 = thunk_FUN_0041f5a0(*(int *)(puVar1[2] + 0x1c));
        if (iVar3 != 0) {
          lVar4 = thunk_FUN_0041f560();
          iVar3 = (int)lVar4;
joined_r0x004099f6:
          if ((iVar3 < param_3) && (iVar3 < iStack_20)) {
            iStack_20 = iVar3;
            puStack_1c = puVar1;
          }
        }
      }
      else {
        iVar3 = thunk_FUN_0041f5a0(*(int *)(puVar1[2] + 0x1c));
        if (iVar3 == 0) {
          lVar4 = thunk_FUN_0041f560();
          iVar3 = (int)lVar4;
          goto joined_r0x004099f6;
        }
      }
    }
  }
  return puStack_1c;
}


