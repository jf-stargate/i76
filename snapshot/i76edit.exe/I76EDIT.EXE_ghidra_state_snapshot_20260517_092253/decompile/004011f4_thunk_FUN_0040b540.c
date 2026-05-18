/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040b540
 * Entry: 004011f4
 * Signature: undefined4 __cdecl thunk_FUN_0040b540(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_0040b540(HWND param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined8 uVar10;
  longlong lVar11;
  uint uStack_b8;
  int iStack_b4;
  undefined8 uStack_b0;
  undefined4 auStack_a8 [6];
  int aiStack_90 [15];
  undefined4 auStack_54 [21];
  
  iVar7 = -1;
  iVar8 = 0;
  iStack_b4 = -1;
  uStack_b8 = 0;
  if (DAT_00434780 != 0) {
    if ((0 < DAT_00434788) && (DAT_00434788 < 3)) {
      uStack_b0 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
      puVar4 = (undefined4 *)thunk_FUN_00408c30(auStack_54,DAT_00434780);
      puVar9 = auStack_a8;
      for (iVar6 = 0x15; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar9 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar9 = puVar9 + 1;
      }
      uVar3 = GetAsyncKeyState(0x11);
      iVar6 = uStack_b0._4_4_;
      if ((uVar3 & 0x8000) == 0) {
        if (aiStack_90[DAT_00434784] == 0) {
          uVar10 = thunk_FUN_004089e0(DAT_00434780,(int)uStack_b0,(int)uStack_b0,uStack_b0._4_4_,5,
                                      (undefined4 *)DAT_00434780,&uStack_b8);
          iVar7 = (int)uVar10;
          if (uStack_b8 != 0) {
            puVar4 = (undefined4 *)thunk_FUN_00408c30(auStack_54,uStack_b8);
            puVar9 = auStack_a8;
            for (iVar6 = 0x15; iVar6 != 0; iVar6 = iVar6 + -1) {
              *puVar9 = *puVar4;
              puVar4 = puVar4 + 1;
              puVar9 = puVar9 + 1;
            }
            lVar11 = __ftol();
            uStack_b0 = CONCAT44(uStack_b0._4_4_,(int)lVar11);
            lVar11 = __ftol();
            iVar6 = (int)lVar11;
          }
        }
        else {
          iStack_b4 = aiStack_90[DAT_00434784 + 2];
          iVar8 = aiStack_90[DAT_00434784];
        }
      }
      else {
        iVar1 = aiStack_90[DAT_00434784];
        if (iVar1 != 0) {
          iVar2 = aiStack_90[DAT_00434784 + 2];
          thunk_FUN_00408bc0(DAT_00434780,DAT_00434784,0,-1);
          iVar8 = 0;
          thunk_FUN_00408bc0(iVar1,iVar2,0,-1);
          iStack_b4 = -1;
        }
      }
      thunk_FUN_00408b80(DAT_00434780,DAT_00434784,(int)uStack_b0,iVar6);
      if (iVar8 != 0) {
        thunk_FUN_00408b80(iVar8,iStack_b4,(int)uStack_b0,iVar6);
      }
      if (uStack_b8 != 0) {
        uVar5 = thunk_FUN_004088c0(uStack_b8);
        if (uVar5 != 0) {
          FUN_0040bf40(DAT_00434780);
        }
        thunk_FUN_00408bc0(DAT_00434780,DAT_00434784,uStack_b8,iVar7);
        FUN_0040bed0(DAT_00434780);
        FUN_0040bed0(uStack_b8);
      }
      thunk_FUN_004087c0();
      InvalidateRgn(param_1,(HRGN)0x0,0);
    }
    DAT_00434780 = 0;
    DAT_00434784 = -1;
  }
  return 1;
}


