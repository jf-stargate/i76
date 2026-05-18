/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00404bd0
 * Entry: 004014ba
 * Signature: undefined4 __cdecl thunk_FUN_00404bd0(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_00404bd0(HWND param_1,undefined4 param_2,uint param_3)

{
  ushort uVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int *piVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 uVar10;
  undefined8 uStack_160;
  int iStack_158;
  int iStack_154;
  int aiStack_150 [16];
  int aiStack_110 [5];
  int aiStack_fc [21];
  int aiStack_a8 [21];
  undefined4 auStack_54 [21];
  
  iStack_154 = -1;
  iVar5 = 0;
  iStack_158 = 0;
  if (DAT_0043433c != 0) {
    switch(DAT_00434348) {
    case 1:
    case 2:
    case 4:
      uVar10 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
      piVar3 = (int *)thunk_FUN_00415a00(aiStack_110 + 5,DAT_0043433c);
      piVar7 = aiStack_150;
      for (iVar4 = 0x15; iVar4 != 0; iVar4 = iVar4 + -1) {
        *piVar7 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar7 = piVar7 + 1;
      }
      uVar1 = GetAsyncKeyState(0x11);
      iVar4 = iVar5;
      uStack_160 = uVar10;
      if ((uVar1 & 0x8000) == 0) {
        iVar4 = aiStack_110[DAT_00434344 / 3];
        if (iVar4 == 0) {
          uStack_160._4_4_ = (int)((ulonglong)uVar10 >> 0x20);
          uStack_160._0_4_ = (int)uVar10;
          thunk_FUN_00415640(DAT_0043433c,uStack_160._4_4_,(int)uStack_160,uStack_160._4_4_,5,
                             (undefined4 *)DAT_0043433c,&iStack_158);
          iVar4 = iVar5;
          if (iStack_158 != 0) {
            puVar2 = (undefined4 *)thunk_FUN_00415a00(aiStack_110 + 5,iStack_158);
            puVar6 = auStack_54;
            for (iVar4 = 0x15; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar6 = *puVar2;
              puVar2 = puVar2 + 1;
              puVar6 = puVar6 + 1;
            }
            lVar8 = __ftol();
            lVar9 = __ftol();
            uStack_160 = CONCAT44((int)lVar9,(int)lVar8);
            iVar4 = iVar5;
          }
        }
        else {
          iStack_154 = aiStack_110[DAT_00434344 / 3 + 2];
        }
      }
      thunk_FUN_004158b0(DAT_0043433c,DAT_00434344,(int)uStack_160,uStack_160._4_4_);
      piVar3 = (int *)thunk_FUN_00415a00(aiStack_110 + 5,DAT_0043433c);
      piVar7 = aiStack_a8;
      for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
        *piVar7 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar7 = piVar7 + 1;
      }
      thunk_FUN_004058a0(param_1,aiStack_150,aiStack_a8);
      if (iVar4 == 0) {
        return 1;
      }
      piVar3 = (int *)thunk_FUN_00415a00(aiStack_110 + 5,iVar4);
      piVar7 = aiStack_150;
      for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
        *piVar7 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar7 = piVar7 + 1;
      }
      thunk_FUN_004158b0(iVar4,iStack_154,(int)uStack_160,uStack_160._4_4_);
      piVar3 = (int *)thunk_FUN_00415a00(aiStack_110 + 5,iVar4);
      piVar7 = aiStack_a8;
      for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
        *piVar7 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar7 = piVar7 + 1;
      }
      break;
    default:
      goto switchD_00404c03_caseD_3;
    case 5:
      uVar10 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
      piVar3 = (int *)thunk_FUN_00415a00(aiStack_110 + 5,DAT_0043433c);
      piVar7 = aiStack_150;
      for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
        *piVar7 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar7 = piVar7 + 1;
      }
      uStack_160._4_4_ = (int)((ulonglong)uVar10 >> 0x20);
      uStack_160._0_4_ = (int)uVar10;
      thunk_FUN_004158b0(DAT_0043433c,DAT_00434344,(int)uStack_160,uStack_160._4_4_);
      piVar3 = (int *)thunk_FUN_00415a00(aiStack_110 + 5,DAT_0043433c);
      piVar7 = aiStack_a8;
      for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
        *piVar7 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar7 = piVar7 + 1;
      }
    }
    thunk_FUN_004058a0(param_1,aiStack_150,aiStack_a8);
  }
switchD_00404c03_caseD_3:
  return 1;
}


