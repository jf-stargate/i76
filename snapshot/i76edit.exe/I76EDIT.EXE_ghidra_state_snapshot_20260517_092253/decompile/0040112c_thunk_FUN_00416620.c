/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00416620
 * Entry: 0040112c
 * Signature: undefined4 __cdecl thunk_FUN_00416620(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_00416620(HWND param_1,undefined4 param_2,uint param_3)

{
  WPARAM WVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar5;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint uVar6;
  int *piVar7;
  int unaff_EDI;
  undefined4 *puVar8;
  undefined8 uVar9;
  undefined1 *lParam;
  uint uStack_190;
  uint uStack_188;
  uint uStack_184;
  uint uStack_180;
  uint uStack_17c;
  undefined4 auStack_168 [3];
  undefined1 auStack_15c [16];
  LRESULT LStack_14c;
  char acStack_148 [8];
  undefined1 uStack_140;
  char acStack_13f [28];
  undefined1 auStack_123 [31];
  char acStack_104 [9];
  char acStack_fb [11];
  undefined4 auStack_f0 [7];
  undefined4 uStack_d4;
  char acStack_d0 [9];
  char acStack_c7 [55];
  undefined4 uStack_90;
  char acStack_8c [9];
  char acStack_83 [11];
  undefined4 auStack_78 [30];
  
  DAT_004363bc = 1;
  uVar9 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
  uVar2 = (uint)((ulonglong)uVar9 >> 0x20);
  uStack_190 = (uint)uVar9;
  if (DAT_004363ac == (int *)0x0) {
    if (DAT_004363c0 == (int *)0x0) {
      uVar5 = 0;
      uVar6 = uVar2;
    }
    else {
      SendDlgItemMessageA(DAT_01642394,0x3f2,0xd,0x28,(LPARAM)acStack_13f);
      SendDlgItemMessageA(DAT_01642394,0x3f3,0xd,9,(LPARAM)acStack_148);
      SendDlgItemMessageA(DAT_01642394,0x3f5,0xd,9,(LPARAM)acStack_fb);
      SendDlgItemMessageA(DAT_01642394,0x3f4,0xd,9,(LPARAM)acStack_104);
      WVar1 = SendDlgItemMessageA(DAT_01642394,0x3f7,0x147,0,0);
      LStack_14c = SendDlgItemMessageA(DAT_01642394,0x3f7,0x150,WVar1,0);
      thunk_FUN_0040f850((int)DAT_004363c0,LStack_14c,acStack_148);
      thunk_FUN_0040f890((int)DAT_004363c0,acStack_13f);
      thunk_FUN_0040f8c0((int)DAT_004363c0,acStack_fb,acStack_104);
      uVar5 = extraout_ECX_00;
      uVar6 = extraout_EDX_00;
    }
  }
  else {
    SendDlgItemMessageA(DAT_01642394,0x3f2,0xd,0x28,(LPARAM)acStack_13f);
    SendDlgItemMessageA(DAT_01642394,0x3f3,0xd,9,(LPARAM)acStack_148);
    SendDlgItemMessageA(DAT_01642394,0x3f5,0xd,9,(LPARAM)acStack_fb);
    SendDlgItemMessageA(DAT_01642394,0x3f4,0xd,9,(LPARAM)acStack_104);
    WVar1 = SendDlgItemMessageA(DAT_01642394,0x3f7,0x147,0,0);
    LStack_14c = SendDlgItemMessageA(DAT_01642394,0x3f7,0x150,WVar1,0);
    thunk_FUN_00409be0((int)DAT_004363ac,LStack_14c,acStack_148);
    thunk_FUN_00409c20((int)DAT_004363ac,acStack_13f);
    thunk_FUN_00409cb0((int)DAT_004363ac,acStack_fb,acStack_104);
    uVar5 = extraout_ECX;
    uVar6 = extraout_EDX;
  }
  switch(DAT_004363b4) {
  case 1:
    uStack_180 = uStack_190;
    uStack_188 = uStack_190;
    uStack_184 = uVar2;
    uStack_17c = uVar2;
    DAT_004363c0 = (int *)thunk_FUN_0040f180(0,(int *)&uStack_188,0);
    DAT_004363a8 = (int *)0x0;
    DAT_004363ac = (int *)0x0;
    DAT_004363c4 = 3;
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  case 2:
    uStack_180 = uStack_190;
    uStack_188 = uStack_190;
    uStack_184 = uVar2;
    uStack_17c = uVar2;
    DAT_004363c0 = (int *)thunk_FUN_0040f180(1,(int *)&uStack_188,0);
    DAT_004363a8 = (int *)0x0;
    DAT_004363ac = (int *)0x0;
    DAT_004363c4 = 3;
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  default:
    return 0;
  case 4:
    uVar9 = thunk_FUN_0040f250(uVar5,uVar6,uStack_190,uVar2,0x32,&DAT_004363c0);
    DAT_004363c4 = (undefined4)uVar9;
    DAT_004363a8 = (int *)0x0;
    DAT_004363ac = (int *)0x0;
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  case 5:
    uVar9 = thunk_FUN_0040f320(uVar5,uVar6,uStack_190,uVar2,0x32,&DAT_004363c0);
    DAT_004363c4 = (undefined4)uVar9;
    DAT_004363a8 = (int *)0x0;
    DAT_004363ac = (int *)0x0;
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  case 6:
    uVar9 = thunk_FUN_0040f250(uVar5,uVar6,uStack_190,uVar2,0x32,&DAT_004363c0);
    DAT_004363c4 = (undefined4)uVar9;
    if (DAT_004363c0 != (int *)0x0) {
      thunk_FUN_0040f4b0(auStack_78,(int)DAT_004363c0);
      iVar3 = MessageBoxA(param_1,s_Delete_these_objects__0043643c,s_Delete_Objects_00436458,1);
      if (iVar3 == 1) {
        thunk_FUN_0040f3f0(DAT_004363c0);
      }
      DAT_004363c4 = 0xffffffff;
      DAT_004363a8 = (int *)0x0;
      DAT_004363ac = (int *)0x0;
      DAT_004363c0 = (int *)0x0;
    }
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  case 7:
    if (DAT_004363ac != (int *)0x0) {
      DAT_004363b0 = DAT_004363ac;
      puVar4 = (undefined4 *)thunk_FUN_00409d20(auStack_78,(int)DAT_004363ac);
      puVar8 = auStack_f0;
      for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar8 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar8 = puVar8 + 1;
      }
    }
    DAT_004363c0 = (int *)0x0;
    DAT_004363ac = (int *)thunk_FUN_00409840(uStack_190,uVar2);
    uVar2 = thunk_FUN_0041f2b0(uStack_190,uVar2,0);
    thunk_FUN_00409b60((int)DAT_004363ac,uVar2);
    if (DAT_004363b0 != (int *)0x0) {
      thunk_FUN_00409be0((int)DAT_004363ac,uStack_d4,acStack_d0);
      thunk_FUN_00409c20((int)DAT_004363ac,acStack_c7);
      thunk_FUN_00409cb0((int)DAT_004363ac,acStack_83,acStack_8c);
      thunk_FUN_00409d00((int)DAT_004363ac,uStack_90);
    }
    break;
  case 8:
  case 9:
    DAT_004363a8 = thunk_FUN_00409930(uStack_190,uVar2,0x32,0);
    if (DAT_004363a8 != (int *)0x0) {
      DAT_004363ac = DAT_004363a8;
    }
    DAT_004363c0 = (int *)0x0;
    break;
  case 10:
    DAT_004363a8 = thunk_FUN_00409930(uStack_190,uVar2,0x32,0);
    if (DAT_004363a8 != (int *)0x0) {
      DAT_004363c0 = (int *)0x0;
      DAT_004363ac = DAT_004363a8;
      iVar3 = MessageBoxA(param_1,s_Delete_this_object__0043646c,s_Delete_Object_00436484,1);
      if (iVar3 == 1) {
        thunk_FUN_00409a60(DAT_004363a8);
        DAT_004363a8 = (int *)0x0;
        DAT_004363ac = (int *)0x0;
      }
      else {
        DAT_004363a8 = (int *)0x0;
      }
    }
  }
  if (DAT_004363ac == (int *)0x0) {
    if (DAT_004363c0 == (int *)0x0) {
      SendDlgItemMessageA(DAT_01642394,0x3f2,0xc,0,0x434334);
      SendDlgItemMessageA(DAT_01642394,0x3f3,0xc,0,0x434334);
      SendDlgItemMessageA(DAT_01642394,0x3f5,0xc,0,0x434334);
      lParam = &DAT_00434334;
    }
    else {
      puVar4 = (undefined4 *)thunk_FUN_0040f910(auStack_78,(int)DAT_004363c0);
      puVar8 = auStack_168;
      for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar8 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar8 = puVar8 + 1;
      }
      SendDlgItemMessageA(DAT_01642394,0x3f2,0xc,0,(LPARAM)acStack_13f);
      SendDlgItemMessageA(DAT_01642394,0x3f3,0xc,0,(LPARAM)auStack_15c);
      SendDlgItemMessageA(DAT_01642394,0x3f5,0xc,0,(LPARAM)auStack_123);
      lParam = &uStack_140;
    }
  }
  else {
    puVar4 = (undefined4 *)thunk_FUN_00409d20(auStack_78,(int)DAT_004363ac);
    puVar8 = auStack_168;
    for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar8 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar8 = puVar8 + 1;
    }
    SendDlgItemMessageA(DAT_01642394,0x3f2,0xc,0,(LPARAM)acStack_13f);
    SendDlgItemMessageA(DAT_01642394,0x3f3,0xc,0,(LPARAM)auStack_15c);
    SendDlgItemMessageA(DAT_01642394,0x3f5,0xc,0,(LPARAM)auStack_123);
    lParam = &uStack_140;
  }
  WVar1 = 0;
  SendDlgItemMessageA(DAT_01642394,0x3f4,0xc,0,(LPARAM)lParam);
  piVar7 = &DAT_004361c0;
  do {
    if (*piVar7 == unaff_EDI) {
      SendDlgItemMessageA(DAT_01642394,0x3f7,0x14e,WVar1,0);
    }
    piVar7 = piVar7 + 0xb;
    WVar1 = WVar1 + 1;
  } while (piVar7 < &DAT_004363fc);
  InvalidateRgn(param_1,(HRGN)0x0,0);
  return 1;
}


