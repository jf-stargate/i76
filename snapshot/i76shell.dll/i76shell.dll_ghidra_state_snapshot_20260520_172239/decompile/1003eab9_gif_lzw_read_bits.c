/*
 * Program: i76shell.dll
 * Function: gif_lzw_read_bits
 * Entry: 1003eab9
 * Signature: uint __fastcall gif_lzw_read_bits(undefined4 param_1, int param_2)
 */


uint __fastcall gif_lzw_read_bits(undefined4 param_1,int param_2)

{
  uint uVar1;
  byte bVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int extraout_EDX;
  int extraout_EDX_00;
  int unaff_EDI;
  
  if (*(int *)(unaff_EDI + 0x18) == 0) {
    bVar2 = gif_read_subblock_byte();
    *(uint *)(unaff_EDI + 0x14) = CONCAT31(extraout_var,bVar2);
    *(undefined4 *)(unaff_EDI + 0x18) = 8;
    param_2 = extraout_EDX;
  }
  if (*(int *)(unaff_EDI + 0x18) < param_2) {
    bVar2 = gif_read_subblock_byte();
    *(uint *)(unaff_EDI + 0x14) =
         *(uint *)(unaff_EDI + 0x14) |
         CONCAT31(extraout_var_00,bVar2) << ((byte)*(undefined4 *)(unaff_EDI + 0x18) & 0x1f);
    *(int *)(unaff_EDI + 0x18) = *(int *)(unaff_EDI + 0x18) + 8;
    param_2 = extraout_EDX_00;
  }
  bVar2 = (&DAT_1004ee25)[param_2];
  uVar1 = *(uint *)(unaff_EDI + 0x14);
  *(int *)(unaff_EDI + 0x18) = *(int *)(unaff_EDI + 0x18) - param_2;
  *(uint *)(unaff_EDI + 0x14) = *(uint *)(unaff_EDI + 0x14) >> ((byte)param_2 & 0x1f);
  return uVar1 & bVar2;
}


