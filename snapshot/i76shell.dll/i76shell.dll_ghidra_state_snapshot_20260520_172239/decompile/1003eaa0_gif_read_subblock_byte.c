/*
 * Program: i76shell.dll
 * Function: gif_read_subblock_byte
 * Entry: 1003eaa0
 * Signature: byte __stdcall gif_read_subblock_byte(void)
 */


byte gif_read_subblock_byte(void)

{
  byte bVar1;
  byte *unaff_ESI;
  byte *pbVar2;
  int unaff_EDI;
  
  pbVar2 = unaff_ESI;
  if (*(int *)(unaff_EDI + 0x10) == 0) {
    pbVar2 = unaff_ESI + 1;
    *(uint *)(unaff_EDI + 0x10) = (uint)*unaff_ESI;
  }
  bVar1 = *pbVar2;
  *(int *)(unaff_EDI + 0x10) = *(int *)(unaff_EDI + 0x10) + -1;
  return bVar1;
}


