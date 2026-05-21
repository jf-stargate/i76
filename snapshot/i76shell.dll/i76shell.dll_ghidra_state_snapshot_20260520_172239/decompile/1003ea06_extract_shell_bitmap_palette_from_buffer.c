/*
 * Program: i76shell.dll
 * Function: extract_shell_bitmap_palette_from_buffer
 * Entry: 1003ea06
 * Signature: undefined __cdecl extract_shell_bitmap_palette_from_buffer(int param_1, int param_2, byte * param_3)
 */


void __cdecl extract_shell_bitmap_palette_from_buffer(int param_1,int param_2,byte *param_3)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = 0x300;
  pbVar2 = (byte *)(param_1 + param_2 + -0x300);
  do {
    *param_3 = *pbVar2 >> 2;
    iVar1 = iVar1 + -1;
    pbVar2 = pbVar2 + 1;
    param_3 = param_3 + 1;
  } while (iVar1 != 0);
  return;
}


