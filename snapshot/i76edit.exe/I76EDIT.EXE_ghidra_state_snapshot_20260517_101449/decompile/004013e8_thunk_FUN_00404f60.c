/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00404f60
 * Entry: 004013e8
 * Signature: undefined4 __cdecl thunk_FUN_00404f60(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_00404f60(HWND param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined8 uVar9;
  longlong lVar10;
  ulonglong uVar11;
  int iStack_b8;
  undefined8 uStack_b4;
  int iStack_ac;
  undefined4 auStack_a8 [16];
  int aiStack_68 [5];
  int aiStack_54 [21];
  
  iVar6 = 0;
  iVar7 = -1;
  iStack_b8 = 0;
  iStack_ac = -1;
  if (DAT_0043433c == 0) {
    return 1;
  }
  switch(DAT_00434348) {
  case 1:
  case 2:
  case 4:
    uVar11 = CONCAT44(param_3 >> 0x10,param_3) & 0xffffffff0000ffff;
    uStack_b4 = thunk_FUN_0040c580((int)uVar11,(int)(uVar11 >> 0x20));
    puVar4 = (undefined4 *)thunk_FUN_00415a00(aiStack_68 + 5,DAT_0043433c);
    puVar8 = auStack_a8;
    for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar8 = puVar8 + 1;
    }
    uVar3 = GetAsyncKeyState(0x11);
    iVar5 = uStack_b4._4_4_;
    if ((uVar3 & 0x8000) == 0) {
      if (aiStack_68[DAT_00434344 / 3] == 0) {
        uVar9 = thunk_FUN_00415640(DAT_0043433c,(int)uStack_b4,(int)uStack_b4,uStack_b4._4_4_,5,
                                   (undefined4 *)DAT_0043433c,&iStack_b8);
        iVar7 = (int)uVar9;
        if (iStack_b8 != 0) {
          puVar4 = (undefined4 *)thunk_FUN_00415a00(aiStack_68 + 5,iStack_b8);
          puVar8 = auStack_a8;
          for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar8 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar8 = puVar8 + 1;
          }
          lVar10 = __ftol();
          uStack_b4 = CONCAT44(uStack_b4._4_4_,(int)lVar10);
          lVar10 = __ftol();
          iVar5 = (int)lVar10;
        }
      }
      else {
        iStack_ac = aiStack_68[DAT_00434344 / 3 + 2];
        iVar6 = aiStack_68[DAT_00434344 / 3];
      }
    }
    else {
      iVar1 = aiStack_68[DAT_00434344 / 3];
      if (iVar1 != 0) {
        iVar2 = aiStack_68[DAT_00434344 / 3 + 2];
        i76edit_link_road_edge_neighbors(DAT_0043433c,DAT_00434344,0,-1);
        iVar6 = 0;
        i76edit_link_road_edge_neighbors(iVar1,iVar2,0,-1);
        iStack_ac = -1;
      }
    }
    thunk_FUN_004158b0(DAT_0043433c,DAT_00434344,(int)uStack_b4,iVar5);
    if (iVar6 != 0) {
      thunk_FUN_004158b0(iVar6,iStack_ac,(int)uStack_b4,iVar5);
    }
    if (iStack_b8 != 0) {
      i76edit_link_road_edge_neighbors(DAT_0043433c,DAT_00434344,iStack_b8,iVar7);
    }
    break;
  default:
    goto switchD_00404f96_caseD_3;
  case 5:
    uVar11 = CONCAT44(param_3 >> 0x10,param_3) & 0xffffffff0000ffff;
    uStack_b4 = thunk_FUN_0040c580((int)uVar11,(int)(uVar11 >> 0x20));
    thunk_FUN_004158b0(DAT_0043433c,DAT_00434344,(int)uStack_b4,(int)((ulonglong)uStack_b4 >> 0x20))
    ;
  }
  InvalidateRgn(param_1,(HRGN)0x0,0);
switchD_00404f96_caseD_3:
  DAT_00434344 = 0xffffffff;
  DAT_00434340 = DAT_0043433c;
  DAT_0043433c = 0;
  return 1;
}


