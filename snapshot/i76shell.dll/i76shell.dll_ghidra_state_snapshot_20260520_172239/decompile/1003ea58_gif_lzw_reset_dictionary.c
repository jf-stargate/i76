/*
 * Program: i76shell.dll
 * Function: gif_lzw_reset_dictionary
 * Entry: 1003ea58
 * Signature: undefined __fastcall gif_lzw_reset_dictionary(int param_1)
 */


void __fastcall gif_lzw_reset_dictionary(int param_1)

{
  int iVar1;
  int *unaff_EDI;
  
  *unaff_EDI = param_1 + 2;
  unaff_EDI[1] = param_1 << 1;
  for (iVar1 = 0; iVar1 < param_1; iVar1 = iVar1 + 1) {
    *(char *)(iVar1 + 0x102e + (int)unaff_EDI) = (char)iVar1;
    *(char *)(iVar1 + 0x202e + (int)unaff_EDI) = (char)iVar1;
    *(undefined2 *)((int)unaff_EDI + iVar1 * 2 + 0x302e) = 0xffff;
  }
  for (; iVar1 < 0x1000; iVar1 = iVar1 + 1) {
    *(undefined2 *)((int)unaff_EDI + iVar1 * 2 + 0x302e) = 0xfffe;
  }
  return;
}


