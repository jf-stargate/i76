/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004035d0
 * Entry: 004010d2
 * Signature: undefined4 __cdecl thunk_FUN_004035d0(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_004035d0(HWND param_1,undefined4 param_2,uint param_3)

{
  LRESULT LVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined8 uVar8;
  WPARAM wParam;
  uint uStack_170;
  uint uStack_16c;
  int aiStack_168 [7];
  int iStack_14c;
  char acStack_148 [9];
  char acStack_13f [55];
  uint uStack_108;
  undefined4 auStack_f0 [7];
  undefined4 uStack_d4;
  char acStack_d0 [9];
  char acStack_c7 [55];
  undefined4 uStack_90;
  undefined4 auStack_78 [30];
  
  uVar8 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
  uStack_170 = (uint)uVar8;
  if (DAT_004340a4 != (int *)0x0) {
    SendDlgItemMessageA(DAT_01642398,0x3f2,0xd,0x28,(LPARAM)acStack_13f);
    SendDlgItemMessageA(DAT_01642398,0x3f3,0xd,9,(LPARAM)acStack_148);
    LVar1 = SendDlgItemMessageA(DAT_01642398,0x40b,0x147,0,0);
    thunk_FUN_00409be0((int)DAT_004340a4,(&DAT_00434240)[LVar1 * 0xb],acStack_148);
    thunk_FUN_00409c20((int)DAT_004340a4,acStack_13f);
  }
  uStack_16c = (uint)((ulonglong)uVar8 >> 0x20);
  switch(DAT_004340ac) {
  case 1:
    if (DAT_004340a4 != (int *)0x0) {
      DAT_004340a8 = DAT_004340a4;
      puVar2 = (undefined4 *)thunk_FUN_00409d20(auStack_78,(int)DAT_004340a4);
      puVar6 = auStack_f0;
      for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar6 = puVar6 + 1;
      }
    }
    DAT_004340a4 = (int *)thunk_FUN_00409840(uStack_170,uStack_16c);
    uVar5 = i76edit_get_or_create_zone_surface_sample(uStack_170,uStack_16c,0);
    thunk_FUN_00409b60((int)DAT_004340a4,uVar5);
    LVar1 = SendDlgItemMessageA(DAT_01642398,0x40b,0x147,0,0);
    thunk_FUN_00409be0((int)DAT_004340a4,(&DAT_00434240)[LVar1 * 0xb],&DAT_00434334);
    if (DAT_004340a8 != (int *)0x0) {
      thunk_FUN_00409be0((int)DAT_004340a4,uStack_d4,acStack_d0);
      thunk_FUN_00409c20((int)DAT_004340a4,acStack_c7);
      thunk_FUN_00409d00((int)DAT_004340a4,uStack_90);
    }
    break;
  case 2:
  case 3:
    DAT_004340a0 = thunk_FUN_00409930(uStack_170,uStack_16c,10,1);
    if (DAT_004340a0 != (int *)0x0) {
      DAT_004340a4 = DAT_004340a0;
    }
    break;
  case 4:
    DAT_004340a0 = thunk_FUN_00409930(uStack_170,uStack_16c,10,1);
    if (DAT_004340a0 != (int *)0x0) {
      DAT_004340a4 = DAT_004340a0;
      iVar3 = MessageBoxA(param_1,s_Delete_this_vehicle__00434304,s_Delete_Vehicle_00434320,1);
      if (iVar3 == 1) {
        thunk_FUN_00409a60(DAT_004340a0);
        DAT_004340a0 = (int *)0x0;
        DAT_004340a4 = (int *)0x0;
      }
      else {
        DAT_004340a0 = (int *)0x0;
      }
    }
    break;
  default:
    return 0;
  }
  InvalidateRgn(param_1,(HRGN)0x0,0);
  if (DAT_004340a4 == (int *)0x0) {
    SendDlgItemMessageA(DAT_01642398,0x3f2,0xc,0,0x434334);
    SendDlgItemMessageA(DAT_01642398,0x3f3,0xc,0,0x434334);
    SendDlgItemMessageA(DAT_01642398,0x3f7,0xf1,0,0);
    SendDlgItemMessageA(DAT_01642398,0x3f6,0xf1,0,0);
    SendDlgItemMessageA(DAT_01642398,0x40a,0x14e,2,0);
    SendDlgItemMessageA(DAT_01642398,0x40b,0x14e,0,0);
  }
  else {
    piVar4 = (int *)thunk_FUN_00409d20(auStack_78,(int)DAT_004340a4);
    piVar7 = aiStack_168;
    for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar7 = *piVar4;
      piVar4 = piVar4 + 1;
      piVar7 = piVar7 + 1;
    }
    SendDlgItemMessageA(DAT_01642398,0x3f2,0xc,0,(LPARAM)acStack_13f);
    SendDlgItemMessageA(DAT_01642398,0x3f3,0xc,0,(LPARAM)acStack_148);
    SendDlgItemMessageA(DAT_01642398,0x3f7,0xf1,(uStack_108 & 0x10) >> 4,0);
    SendDlgItemMessageA(DAT_01642398,0x3f6,0xf1,(uint)((uStack_108 & 0x10) == 0),0);
    if (iStack_14c == 9) {
      wParam = 1;
    }
    else if (iStack_14c == 8) {
      wParam = 2;
    }
    else {
      wParam = 0;
    }
    SendDlgItemMessageA(DAT_01642398,0x40b,0x14e,wParam,0);
    uVar5 = thunk_FUN_00409c90((int)DAT_004340a4);
    SendDlgItemMessageA(DAT_01642398,0x40a,0x14e,uVar5,0);
    FUN_004043d0(param_1,aiStack_168,aiStack_168);
  }
  InvalidateRgn(param_1,(HRGN)0x0,0);
  return 1;
}


