/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041fad0
 * Entry: 0040129e
 * Signature: undefined4 __cdecl thunk_FUN_0041fad0(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_0041fad0(HWND param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  undefined4 extraout_ECX;
  int iVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  undefined8 uStack_84;
  undefined8 uStack_7c;
  undefined8 auStack_64 [10];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_10 = 0;
  uStack_c = 0;
  uStack_8 = 0;
  uStack_4 = 0;
  puVar3 = &DAT_0043bf90;
  for (iVar1 = 0x50; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = 0xffffffff;
    puVar3 = puVar3 + 1;
  }
  auStack_64[0] = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
  iVar2 = (int)((ulonglong)auStack_64[0] >> 0x20);
  iVar1 = (int)auStack_64[0];
  DAT_004376fc = 1;
  uStack_84 = auStack_64[0];
  uStack_7c = auStack_64[0];
  switch(DAT_004376f4) {
  case 1:
    DAT_00437700 = (int *)thunk_FUN_0040c750(0,(int *)&uStack_84,0);
    DAT_00437704 = 3;
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  case 2:
    DAT_00437700 = (int *)thunk_FUN_0040c750(1,(int *)&uStack_84,0);
    DAT_00437704 = 3;
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  default:
    return 0;
  case 4:
    uVar4 = thunk_FUN_0040c800(extraout_ECX,iVar2,iVar1,iVar2,5,&DAT_00437700);
    DAT_00437704 = (undefined4)uVar4;
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  case 5:
    uVar4 = thunk_FUN_0040c8c0(extraout_ECX,iVar2,iVar1,iVar2,5,&DAT_00437700);
    DAT_00437704 = (undefined4)uVar4;
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  case 6:
    uVar4 = thunk_FUN_0040c800(extraout_ECX,iVar2,iVar1,iVar2,5,&DAT_00437700);
    DAT_00437704 = (undefined4)uVar4;
    if (DAT_00437700 != (int *)0x0) {
      thunk_FUN_00415a00((undefined4 *)auStack_64,(int)DAT_00437700);
      iVar1 = MessageBoxA(param_1,s_Delete_this_grade__0043799c,s_Delete_Grade_004379b4,1);
      if (iVar1 == 1) {
        thunk_FUN_0040c990(DAT_00437700);
      }
      DAT_00437700 = (int *)0x0;
      DAT_00437704 = 0xffffffff;
    }
    InvalidateRgn(param_1,(HRGN)0x0,0);
    break;
  case 7:
    thunk_FUN_00420db0(iVar1,iVar2);
    break;
  case 8:
    thunk_FUN_00420ba0(iVar1,iVar2);
    break;
  case 9:
  case 10:
    thunk_FUN_00420cd0(iVar1,iVar2);
  }
  return 1;
}


