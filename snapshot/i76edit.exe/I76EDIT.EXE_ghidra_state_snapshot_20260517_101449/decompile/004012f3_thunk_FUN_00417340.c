/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00417340
 * Entry: 004012f3
 * Signature: undefined4 __cdecl thunk_FUN_00417340(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_00417340(HWND param_1,undefined4 param_2,uint param_3)

{
  ulonglong uVar1;
  int iVar2;
  code *pcVar3;
  undefined8 auStack_54 [10];
  
  DAT_004363a8 = 0;
  auStack_54[0] = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
  uVar1 = (ulonglong)auStack_54[0] >> 0x20;
  iVar2 = (int)auStack_54[0];
  DAT_004363bc = 0;
  pcVar3 = InvalidateRgn_exref;
  if (DAT_004363c0 == 0) goto LAB_004173f7;
  switch(DAT_004363b4) {
  case 1:
  case 2:
  case 4:
    thunk_FUN_0040f4b0((undefined4 *)auStack_54,DAT_004363c0);
    break;
  default:
    goto switchD_00417396_caseD_3;
  case 5:
  }
  thunk_FUN_0040f930(DAT_004363c0,DAT_004363c4,iVar2,(int)uVar1);
switchD_00417396_caseD_3:
  pcVar3 = InvalidateRgn_exref;
  InvalidateRgn(param_1,(HRGN)0x0,0);
LAB_004173f7:
  (*pcVar3)(param_1,0,0);
  return 1;
}


