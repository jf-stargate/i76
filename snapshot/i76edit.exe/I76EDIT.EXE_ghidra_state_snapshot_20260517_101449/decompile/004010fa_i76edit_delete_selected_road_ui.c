/*
 * Program: I76EDIT.EXE
 * Function: i76edit_delete_selected_road_ui
 * Entry: 004010fa
 * Signature: undefined4 __cdecl i76edit_delete_selected_road_ui(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl i76edit_delete_selected_road_ui(HWND param_1,undefined4 param_2,uint param_3)

{
  ushort uVar1;
  uint *puVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  int iVar3;
  undefined4 uVar4;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int iVar5;
  uint *puVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  longlong lVar9;
  longlong lVar10;
  int iStack_cc;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  uint auStack_a8 [21];
  int aiStack_54 [21];
  
  iVar5 = -1;
  iStack_cc = 0;
  uVar7 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
  uVar4 = (undefined4)((ulonglong)uVar7 >> 0x20);
  iVar3 = (int)uVar7;
  aiStack_54[0] = iVar3;
  switch(DAT_00434348) {
  case 1:
    uVar1 = GetAsyncKeyState(0x11);
    if ((uVar1 & 0x8000) == 0) {
      uVar8 = thunk_FUN_00415640(extraout_ECX_00,extraout_EDX,iVar3,uVar4,5,(undefined4 *)0x0,
                                 &iStack_cc);
      iVar5 = (int)uVar8;
      if (iStack_cc != 0) {
        puVar2 = (uint *)thunk_FUN_00415a00(aiStack_54,iStack_cc);
        puVar6 = auStack_a8;
        for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar6 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar6 = puVar6 + 1;
        }
        lVar9 = __ftol();
        lVar10 = __ftol();
        uVar7 = CONCAT44((int)lVar10,(int)lVar9);
      }
    }
    uStack_c8 = uVar7;
    uStack_c0 = uVar7;
    DAT_0043433c = (int *)thunk_FUN_00415440(0,(int *)&uStack_c8,(short)DAT_00434350);
    DAT_00434344 = 3;
    if (iStack_cc != 0) {
      i76edit_link_road_edge_neighbors((int)DAT_0043433c,0,iStack_cc,iVar5);
    }
    break;
  case 2:
    uVar1 = GetAsyncKeyState(0x11);
    if ((uVar1 & 0x8000) == 0) {
      uVar8 = thunk_FUN_00415640(extraout_ECX_01,extraout_EDX_00,iVar3,uVar4,5,(undefined4 *)0x0,
                                 &iStack_cc);
      iVar5 = (int)uVar8;
      if (iStack_cc != 0) {
        puVar2 = (uint *)thunk_FUN_00415a00(aiStack_54,iStack_cc);
        puVar6 = auStack_a8;
        for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar6 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar6 = puVar6 + 1;
        }
        lVar9 = __ftol();
        lVar10 = __ftol();
        uVar7 = CONCAT44((int)lVar10,(int)lVar9);
      }
    }
    uStack_c8 = uVar7;
    uStack_c0 = uVar7;
    DAT_0043433c = (int *)thunk_FUN_00415440(1,(int *)&uStack_c8,(short)DAT_00434350);
    DAT_00434344 = 3;
    if (iStack_cc != 0) {
      i76edit_link_road_edge_neighbors((int)DAT_0043433c,0,iStack_cc,iVar5);
    }
    break;
  default:
    return 0;
  case 4:
    uVar7 = thunk_FUN_00415580(extraout_ECX,uVar4,iVar3,uVar4,10,&DAT_0043433c);
    DAT_00434344 = (int)uVar7;
    if (DAT_0043433c != (int *)0x0) {
      puVar2 = (uint *)thunk_FUN_00415a00(aiStack_54,(int)DAT_0043433c);
      puVar6 = auStack_a8;
      for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar6 = puVar6 + 1;
      }
      SendDlgItemMessageA(DAT_01642390,0x414,0x14e,auStack_a8[1] & 0xffff,0);
    }
    break;
  case 5:
    uVar7 = thunk_FUN_00415720(extraout_ECX,uVar4,iVar3,uVar4,10,&DAT_0043433c);
    DAT_00434344 = (int)uVar7;
    if (DAT_0043433c != (int *)0x0) {
      puVar2 = (uint *)thunk_FUN_00415a00(aiStack_54,(int)DAT_0043433c);
      puVar6 = auStack_a8;
      for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar6 = puVar6 + 1;
      }
      SendDlgItemMessageA(DAT_01642390,0x414,0x14e,auStack_a8[1] & 0xffff,0);
    }
    break;
  case 6:
    uVar7 = thunk_FUN_00415580(extraout_ECX,uVar4,iVar3,uVar4,10,&DAT_0043433c);
    DAT_00434344 = (int)uVar7;
    if (DAT_0043433c != (int *)0x0) {
      puVar2 = (uint *)thunk_FUN_00415a00(aiStack_54,(int)DAT_0043433c);
      puVar6 = auStack_a8;
      for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar6 = puVar6 + 1;
      }
      SendDlgItemMessageA(DAT_01642390,0x414,0x14e,auStack_a8[1] & 0xffff,0);
      if ((aiStack_54[DAT_00434344 / 3 + -5] == 0) &&
         (iVar3 = MessageBoxA(param_1,s_Delete_this_road__004343fc,s_Delete_Road_00434414,1),
         iVar3 == 1)) {
        i76edit_delete_road_node_and_cleanup_edges(DAT_0043433c);
      }
      if (DAT_00434340 == DAT_0043433c) {
        DAT_00434340 = (int *)0x0;
      }
      DAT_0043433c = (int *)0x0;
      DAT_00434344 = -1;
    }
  }
  InvalidateRgn(param_1,(HRGN)0x0,0);
  return 1;
}


