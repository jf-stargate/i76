/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00420db0
 * Entry: 004014a1
 * Signature: undefined __cdecl thunk_FUN_00420db0(int param_1, int param_2)
 */


void __cdecl thunk_FUN_00420db0(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iStack_4;
  
  uVar5 = param_2 - 4;
  if ((int)uVar5 < 0) {
    uVar5 = 0;
  }
  if (DAT_004376f8 < 10) {
    iStack_4 = 0;
    iVar1 = DAT_004376f8;
    do {
      iVar4 = 0;
      uVar6 = param_1 - 4;
      do {
        if (*(int *)(&DAT_00436a40 + ((iVar1 * 9 + iStack_4) * 9 + iVar4) * 4) != 0) {
          iVar1 = DAT_004376ec * *(int *)(&DAT_00436a40 + ((iVar1 * 9 + iStack_4) * 9 + iVar4) * 4);
          uVar2 = i76edit_get_or_create_zone_surface_sample(uVar6,uVar5,0);
          uVar3 = i76edit_get_or_create_zone_surface_sample(uVar6,uVar5,0);
          iVar1 = uVar3 + (int)(uVar2 * (iVar1 / 10)) / 100;
          if (0xffe < iVar1) {
            iVar1 = 0xffe;
          }
          thunk_FUN_0041f3a0(uVar6,uVar5,(short)iVar1,0);
          iVar1 = i76edit_get_or_create_zone_cell_backing(uVar6,uVar5,0);
          thunk_FUN_0041f7c0(iVar1,uVar6,uVar5);
          iVar1 = DAT_004376f8;
        }
        uVar6 = uVar6 + 1;
        iVar4 = iVar4 + 1;
      } while (iVar4 < 9);
      uVar5 = uVar5 + 1;
      iStack_4 = iStack_4 + 1;
    } while (iStack_4 < 9);
    InvalidateRgn(DAT_01641fb4,(HRGN)0x0,0);
  }
  return;
}


