/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040d390
 * Entry: 00401226
 * Signature: undefined __cdecl thunk_FUN_0040d390(int param_1, int param_2)
 */


void __cdecl thunk_FUN_0040d390(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *lParam;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  char acStack_c [12];
  
  iVar7 = param_2;
  iVar3 = param_1;
  iVar4 = thunk_FUN_0041e8d0(&param_1,&param_2,0);
  iVar3 = iVar3 - param_1;
  iVar7 = iVar7 - param_2;
  iVar6 = 0;
  pbVar5 = &DAT_0163ce70 + iVar4 * 200;
  do {
    if (((int)(*pbVar5 - 10) < param_1) && (param_1 < (int)(*pbVar5 + 10))) {
      if (((int)(pbVar5[1] - 10) < param_2) && (param_2 < (int)(pbVar5[1] + 10))) {
        iVar1 = iVar6 + iVar4 * 0x32;
        iVar2 = iVar1 * 4;
        lParam = __itoa((uint)(ushort)(&DAT_0163ce72)[iVar1 * 2],acStack_c,10);
        SendMessageA(DAT_01641fac,0xc,0,(LPARAM)lParam);
        MoveWindow(DAT_01641fac,(uint)(byte)(&DAT_0163ce70)[iVar2] + iVar3 + 10,
                   (uint)(byte)(&DAT_0163ce71)[iVar2] + iVar7 + -0x17,0x2d,0x10,1);
        ShowWindow(DAT_01641fac,1);
        SetFocus(DAT_01641fac);
        SetCapture(DAT_01641fac);
        SendMessageA(DAT_01641fac,0xb1,0,-1);
        DAT_004347cc = iVar4;
        DAT_004347d0 = iVar6;
        return;
      }
    }
    pbVar5 = pbVar5 + 4;
    iVar6 = iVar6 + 1;
    if (0x31 < iVar6) {
      return;
    }
  } while( true );
}


