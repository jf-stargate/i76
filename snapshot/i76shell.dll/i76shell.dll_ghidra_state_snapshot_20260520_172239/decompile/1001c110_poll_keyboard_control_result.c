/*
 * Program: i76shell.dll
 * Function: poll_keyboard_control_result
 * Entry: 1001c110
 * Signature: int __fastcall poll_keyboard_control_result(UINT * param_1)
 */


int __fastcall poll_keyboard_control_result(UINT *param_1)

{
  uint uVar1;
  short sVar2;
  int iVar3;
  BYTE *pBVar4;
  uint local_104;
  BYTE local_100 [16];
  undefined1 local_f0;
  
  sVar2 = FUN_1001d630();
  *param_1 = (int)sVar2;
  if ((int)sVar2 != 0) {
    uVar1 = (uint)sVar2;
    param_1[0x43] = 1;
    *param_1 = uVar1 & 0xfffffeff;
    pBVar4 = local_100;
    for (iVar3 = 0x40; iVar3 != 0; iVar3 = iVar3 + -1) {
      pBVar4[0] = '\0';
      pBVar4[1] = '\0';
      pBVar4[2] = '\0';
      pBVar4[3] = '\0';
      pBVar4 = pBVar4 + 4;
    }
    if ((uVar1 & 0x200) != 0) {
      local_f0 = 0x80;
      *param_1 = uVar1 & 0xfffffcff;
    }
    iVar3 = ToAscii(*param_1,0,local_100,(LPWORD)&local_104,0);
    if (iVar3 == 1) {
      *param_1 = local_104 & 0xffff;
    }
    return (-(uint)(*param_1 != 0x1b) & 0xfffffffe) + 3;
  }
  param_1[0x43] = 0;
  return 0;
}


