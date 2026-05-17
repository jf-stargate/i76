/*
 * Program: I76EDIT.EXE
 * Function: i76edit_delete_selected_objects_ui
 * Entry: 00416620
 * Signature: undefined4 __cdecl i76edit_delete_selected_objects_ui(HWND param_1, undefined4 param_2, uint param_3)
 */


/* [cgpt_i76edit_level_renames_v2:medium] References 'Delete Object(s)' confirmation strings; UI
   command path for object deletion. */

undefined4 __cdecl i76edit_delete_selected_objects_ui(HWND param_1,undefined4 param_2,uint param_3)

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
  uint local_190;
  uint local_188;
  uint local_184;
  uint local_180;
  uint local_17c;
  undefined4 local_168 [3];
  undefined1 auStack_15c [16];
  LRESULT local_14c;
  char local_148 [8];
  undefined1 uStack_140;
  char local_13f [28];
  undefined1 auStack_123 [31];
  char local_104 [9];
  char local_fb [11];
  undefined4 local_f0 [7];
  undefined4 local_d4;
  char local_d0 [9];
  char local_c7 [55];
  undefined4 local_90;
  char local_8c [9];
  char local_83 [11];
  undefined4 local_78 [30];
  
  DAT_004363bc = 1;
  uVar9 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
  uVar2 = (uint)((ulonglong)uVar9 >> 0x20);
  local_190 = (uint)uVar9;
  if (DAT_004363ac == (int *)0x0) {
    if (DAT_004363c0 == (int *)0x0) {
      uVar5 = 0;
      uVar6 = uVar2;
    }
    else {
      SendDlgItemMessageA(DAT_01642394,0x3f2,0xd,0x28,(LPARAM)local_13f);
      SendDlgItemMessageA(DAT_01642394,0x3f3,0xd,9,(LPARAM)local_148);
      SendDlgItemMessageA(DAT_01642394,0x3f5,0xd,9,(LPARAM)local_fb);
      SendDlgItemMessageA(DAT_01642394,0x3f4,0xd,9,(LPARAM)local_104);
      WVar1 = SendDlgItemMessageA(DAT_01642394,0x3f7,0x147,0,0);
      local_14c = SendDlgItemMessageA(DAT_01642394,0x3f7,0x150,WVar1,0);
      thunk_FUN_0040f850((int)DAT_004363c0,local_14c,local_148);
      thunk_FUN_0040f890((int)DAT_004363c0,local_13f);
      thunk_FUN_0040f8c0((int)DAT_004363c0,local_fb,local_104);
      uVar5 = extraout_ECX_00;
      uVar6 = extraout_EDX_00;
    }
  }
  else {
    SendDlgItemMessageA(DAT_01642394,0x3f2,0xd,0x28,(LPARAM)local_13f);
    SendDlgItemMessageA(DAT_01642394,0x3f3,0xd,9,(LPARAM)local_148);
    SendDlgItemMessageA(DAT_01642394,0x3f5,0xd,9,(LPARAM)local_fb);
    SendDlgItemMessageA(DAT_01642394,0x3f4,0xd,9,(LPARAM)local_104);
    WVar1 = SendDlgItemMessageA(DAT_01642394,0x3f7,0x147,0,0);
    local_14c = SendDlgItemMessageA(DAT_01642394,0x3f7,0x150,WVar1,0);
    thunk_FUN_00409be0((int)DAT_004363ac,local_14c,local_148);
    thunk_FUN_00409c20((int)DAT_004363ac,local_13f);
    thunk_FUN_00409cb0((int)DAT_004363ac,local_fb,local_104);
    uVar5 = extraout_ECX;
    uVar6 = extraout_EDX;
  }
  switch(DAT_004363b4) {
  case 1:
    local_180 = local_190;
    local_188 = local_190;
    local_184 = uVar2;
    local_17c = uVar2;
    DAT_004363c0 = (int *)thunk_FUN_0040f180(0,(int *)&local_188,0);
    DAT_004363a8 = (int *)0x0;
    DAT_004363ac = (int *)0x0;
    DAT_004363c4 = 3;
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  case 2:
    local_180 = local_190;
    local_188 = local_190;
    local_184 = uVar2;
    local_17c = uVar2;
    DAT_004363c0 = (int *)thunk_FUN_0040f180(1,(int *)&local_188,0);
    DAT_004363a8 = (int *)0x0;
    DAT_004363ac = (int *)0x0;
    DAT_004363c4 = 3;
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  default:
    return 0;
  case 4:
    uVar9 = thunk_FUN_0040f250(uVar5,uVar6,local_190,uVar2,0x32,&DAT_004363c0);
    DAT_004363c4 = (undefined4)uVar9;
    DAT_004363a8 = (int *)0x0;
    DAT_004363ac = (int *)0x0;
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  case 5:
    uVar9 = thunk_FUN_0040f320(uVar5,uVar6,local_190,uVar2,0x32,&DAT_004363c0);
    DAT_004363c4 = (undefined4)uVar9;
    DAT_004363a8 = (int *)0x0;
    DAT_004363ac = (int *)0x0;
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  case 6:
    uVar9 = thunk_FUN_0040f250(uVar5,uVar6,local_190,uVar2,0x32,&DAT_004363c0);
    DAT_004363c4 = (undefined4)uVar9;
    if (DAT_004363c0 != (int *)0x0) {
      thunk_FUN_0040f4b0(local_78,(int)DAT_004363c0);
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
      puVar4 = (undefined4 *)thunk_FUN_00409d20(local_78,(int)DAT_004363ac);
      puVar8 = local_f0;
      for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar8 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar8 = puVar8 + 1;
      }
    }
    DAT_004363c0 = (int *)0x0;
    DAT_004363ac = (int *)thunk_FUN_00409840(local_190,uVar2);
    uVar2 = i76edit_get_or_create_zone_surface_sample(local_190,uVar2,0);
    thunk_FUN_00409b60((int)DAT_004363ac,uVar2);
    if (DAT_004363b0 != (int *)0x0) {
      thunk_FUN_00409be0((int)DAT_004363ac,local_d4,local_d0);
      thunk_FUN_00409c20((int)DAT_004363ac,local_c7);
      thunk_FUN_00409cb0((int)DAT_004363ac,local_83,local_8c);
      thunk_FUN_00409d00((int)DAT_004363ac,local_90);
    }
    break;
  case 8:
  case 9:
    DAT_004363a8 = thunk_FUN_00409930(local_190,uVar2,0x32,0);
    if (DAT_004363a8 != (int *)0x0) {
      DAT_004363ac = DAT_004363a8;
    }
    DAT_004363c0 = (int *)0x0;
    break;
  case 10:
    DAT_004363a8 = thunk_FUN_00409930(local_190,uVar2,0x32,0);
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
      puVar4 = (undefined4 *)thunk_FUN_0040f910(local_78,(int)DAT_004363c0);
      puVar8 = local_168;
      for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar8 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar8 = puVar8 + 1;
      }
      SendDlgItemMessageA(DAT_01642394,0x3f2,0xc,0,(LPARAM)local_13f);
      SendDlgItemMessageA(DAT_01642394,0x3f3,0xc,0,(LPARAM)auStack_15c);
      SendDlgItemMessageA(DAT_01642394,0x3f5,0xc,0,(LPARAM)auStack_123);
      lParam = &uStack_140;
    }
  }
  else {
    puVar4 = (undefined4 *)thunk_FUN_00409d20(local_78,(int)DAT_004363ac);
    puVar8 = local_168;
    for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar8 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar8 = puVar8 + 1;
    }
    SendDlgItemMessageA(DAT_01642394,0x3f2,0xc,0,(LPARAM)local_13f);
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


