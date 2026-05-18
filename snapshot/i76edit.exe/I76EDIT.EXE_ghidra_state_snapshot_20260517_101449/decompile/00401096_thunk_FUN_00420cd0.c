/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00420cd0
 * Entry: 00401096
 * Signature: undefined __cdecl thunk_FUN_00420cd0(int param_1, int param_2)
 */


void __cdecl thunk_FUN_00420cd0(int param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  uVar5 = param_2 - 4;
  if ((int)uVar5 < 0) {
    uVar5 = 0;
  }
  if (DAT_004376f8 < 10) {
    iVar7 = 0;
    iVar2 = DAT_004376f4;
    iVar3 = DAT_004376f8;
    do {
      iVar6 = 0;
      uVar4 = param_1 - 4;
      do {
        if (*(int *)(&DAT_00436a40 + ((iVar3 * 9 + iVar7) * 9 + iVar6) * 4) != 0) {
          uVar1 = 0x8000;
          if (iVar2 != 10) {
            uVar1 = (undefined2)
                    ((DAT_004376f0 * *(int *)(&DAT_00436a40 + ((iVar3 * 9 + iVar7) * 9 + iVar6) * 4)
                     ) / 10);
          }
          thunk_FUN_0041f3a0(uVar4,uVar5,uVar1,0);
          iVar2 = i76edit_get_or_create_zone_cell_backing(uVar4,uVar5,0);
          thunk_FUN_0041f7c0(iVar2,uVar4,uVar5);
          iVar2 = DAT_004376f4;
          iVar3 = DAT_004376f8;
        }
        uVar4 = uVar4 + 1;
        iVar6 = iVar6 + 1;
      } while (iVar6 < 9);
      uVar5 = uVar5 + 1;
      iVar7 = iVar7 + 1;
    } while (iVar7 < 9);
    InvalidateRgn(DAT_01641fb4,(HRGN)0x0,0);
  }
  return;
}


