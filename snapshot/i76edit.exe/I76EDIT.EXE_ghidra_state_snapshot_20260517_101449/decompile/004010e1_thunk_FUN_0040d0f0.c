/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040d0f0
 * Entry: 004010e1
 * Signature: int __cdecl thunk_FUN_0040d0f0(int param_1, int param_2)
 */


int __cdecl thunk_FUN_0040d0f0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *lParam;
  uint uVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  int iVar8;
  int iVar9;
  code *pcVar10;
  char acStack_c [12];
  
  iVar9 = param_2;
  iVar5 = param_1;
  iVar8 = 0;
  iVar3 = thunk_FUN_0041e8d0(&param_1,&param_2,0);
  iVar5 = iVar5 - param_1;
  iVar9 = iVar9 - param_2;
  if (iVar3 == -1) {
    DAT_004347cc = -1;
    DAT_004347d4 = -1;
    DAT_004347d8 = -1;
    ShowWindow(DAT_01641fac,0);
  }
  else {
    DAT_00439d68 = 0;
    pbVar7 = &DAT_0163ce70 + iVar3 * 200;
    do {
      uVar6 = (uint)*pbVar7;
      if (((((int)(uVar6 - 10) < param_1) && (param_1 < (int)(uVar6 + 10))) &&
          (uVar4 = (uint)pbVar7[1], (int)(uVar4 - 10) < param_2)) && (param_2 < (int)(uVar4 + 10)))
      {
        DAT_00439d68 = 1;
        if (((DAT_004347cc == -1) || (DAT_004347d4 == -1)) || (DAT_004347d8 == -1)) {
          iVar1 = iVar8 + iVar3 * 0x32;
          DAT_004347d4 = (&DAT_0163ce70)[iVar1 * 4];
          iVar2 = iVar1 * 4;
          DAT_004347d8 = (&DAT_0163ce71)[iVar2];
          DAT_004347cc = iVar3;
          lParam = __itoa((uint)(ushort)(&DAT_0163ce72)[iVar1 * 2],acStack_c,10);
          SendMessageA(DAT_01641fac,0xc,0,(LPARAM)lParam);
          MoveWindow(DAT_01641fac,(uint)(byte)(&DAT_0163ce70)[iVar2] + iVar5 + 10,
                     (uint)(byte)(&DAT_0163ce71)[iVar2] + iVar9 + -0x17,0x2d,0x11,1);
          pcVar10 = ShowWindow_exref;
          ShowWindow(DAT_01641fac,8);
          break;
        }
        if (((DAT_004347cc != iVar3) || ((int)DAT_004347d4 != uVar6)) ||
           ((int)DAT_004347d8 != uVar4)) {
          DAT_004347cc = -1;
          DAT_004347d4 = -1;
          DAT_004347d8 = -1;
        }
      }
      pbVar7 = pbVar7 + 4;
      iVar8 = iVar8 + 1;
      pcVar10 = ShowWindow_exref;
    } while (iVar8 < 0x32);
    if (DAT_00439d68 == 0) {
      DAT_004347cc = -1;
      DAT_004347d4 = -1;
      DAT_004347d8 = -1;
    }
    if ((iVar8 == 0x32) && (DAT_004347cc == -1)) {
      (*pcVar10)(DAT_01641fac,0);
    }
  }
  return DAT_00439d68;
}


