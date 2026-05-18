/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00420090
 * Entry: 004010f5
 * Signature: undefined4 __cdecl thunk_FUN_00420090(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_00420090(HWND param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined8 uVar4;
  char acStack_64 [16];
  undefined8 uStack_54;
  
  acStack_64[0] = '\0';
  acStack_64[1] = '\0';
  acStack_64[2] = '\0';
  acStack_64[3] = '\0';
  acStack_64[4] = '\0';
  acStack_64[5] = '\0';
  acStack_64[6] = '\0';
  acStack_64[7] = '\0';
  acStack_64[8] = '\0';
  acStack_64[9] = '\0';
  acStack_64[10] = '\0';
  acStack_64[0xb] = '\0';
  acStack_64[0xc] = '\0';
  acStack_64[0xd] = '\0';
  acStack_64[0xe] = '\0';
  acStack_64[0xf] = '\0';
  DAT_004376fc = 0;
  uVar4 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
  uStack_54._4_4_ = (uint)((ulonglong)uVar4 >> 0x20);
  uVar2 = uStack_54._4_4_;
  uStack_54._0_4_ = (uint)uVar4;
  uVar1 = (uint)uStack_54;
  uStack_54 = uVar4;
  uVar3 = i76edit_get_or_create_zone_surface_sample(uVar1,uVar2,99);
  __itoa(uVar3 & 0xffff,acStack_64,10);
  SendDlgItemMessageA(DAT_01642384,0x415,0xc,0,(LPARAM)acStack_64);
  if (DAT_00437700 == 0) {
    return 1;
  }
  switch(DAT_004376f4) {
  case 1:
  case 2:
  case 4:
    thunk_FUN_00415a00((undefined4 *)&uStack_54,DAT_00437700);
    break;
  default:
    goto switchD_0042012b_caseD_3;
  case 5:
  }
  thunk_FUN_004158b0(DAT_00437700,DAT_00437704,uVar1,uVar2);
switchD_0042012b_caseD_3:
  InvalidateRgn(param_1,(HRGN)0x0,0);
  DAT_00437704 = 0xffffffff;
  DAT_00437700 = 0;
  return 1;
}


