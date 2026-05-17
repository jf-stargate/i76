/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040b2b0
 * Entry: 004014f1
 * Signature: undefined4 __cdecl thunk_FUN_0040b2b0(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_0040b2b0(HWND param_1,undefined4 param_2,uint param_3)

{
  ushort uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined8 uVar6;
  longlong lVar7;
  longlong lVar8;
  undefined8 uStack_160;
  int iStack_158;
  int iStack_154;
  undefined4 auStack_150 [6];
  int aiStack_138 [15];
  undefined4 auStack_fc [21];
  undefined4 auStack_a8 [21];
  undefined4 auStack_54 [21];
  
  iVar4 = 0;
  iStack_158 = 0;
  iStack_154 = -1;
  if (((DAT_00434780 != 0) && (0 < DAT_00434788)) && (DAT_00434788 < 3)) {
    uVar6 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
    puVar2 = (undefined4 *)thunk_FUN_00408c30(auStack_fc,DAT_00434780);
    puVar5 = auStack_150;
    for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    uVar1 = GetAsyncKeyState(0x11);
    iVar3 = iVar4;
    uStack_160 = uVar6;
    if ((uVar1 & 0x8000) == 0) {
      iVar3 = aiStack_138[DAT_00434784];
      if (iVar3 == 0) {
        uStack_160._4_4_ = (int)((ulonglong)uVar6 >> 0x20);
        uStack_160._0_4_ = (int)uVar6;
        thunk_FUN_004089e0(DAT_00434780,uStack_160._4_4_,(int)uStack_160,uStack_160._4_4_,5,
                           (undefined4 *)DAT_00434780,&iStack_158);
        iVar3 = iVar4;
        if (iStack_158 != 0) {
          puVar2 = (undefined4 *)thunk_FUN_00408c30(auStack_fc,iStack_158);
          puVar5 = auStack_54;
          for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar5 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar5 = puVar5 + 1;
          }
          lVar7 = __ftol();
          lVar8 = __ftol();
          uStack_160 = CONCAT44((int)lVar8,(int)lVar7);
          iVar3 = iVar4;
        }
      }
      else {
        iStack_154 = aiStack_138[DAT_00434784 + 2];
      }
    }
    thunk_FUN_00408b80(DAT_00434780,DAT_00434784,(int)uStack_160,uStack_160._4_4_);
    puVar2 = (undefined4 *)thunk_FUN_00408c30(auStack_fc,DAT_00434780);
    puVar5 = auStack_a8;
    for (iVar4 = 0x15; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    FUN_0040bb00(param_1,(int)auStack_150,(int)auStack_a8);
    if (iVar3 != 0) {
      puVar2 = (undefined4 *)thunk_FUN_00408c30(auStack_fc,iVar3);
      puVar5 = auStack_150;
      for (iVar4 = 0x15; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar5 = puVar5 + 1;
      }
      thunk_FUN_00408b80(iVar3,iStack_154,(int)uStack_160,uStack_160._4_4_);
      puVar2 = (undefined4 *)thunk_FUN_00408c30(auStack_fc,iVar3);
      puVar5 = auStack_a8;
      for (iVar4 = 0x15; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar5 = puVar5 + 1;
      }
      FUN_0040bb00(param_1,(int)auStack_150,(int)auStack_a8);
    }
  }
  return 1;
}


