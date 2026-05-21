/*
 * Program: i76shell.dll
 * Function: gif_lzw_add_dictionary_entry
 * Entry: 1003eaff
 * Signature: undefined __fastcall gif_lzw_add_dictionary_entry(int param_1)
 */


void __fastcall gif_lzw_add_dictionary_entry(int param_1)

{
  int unaff_EBX;
  int *unaff_EDI;
  
  *(short *)((int)unaff_EDI + *unaff_EDI * 2 + 0x302e) = (short)param_1;
  *(undefined1 *)(*unaff_EDI + 0x202e + (int)unaff_EDI) =
       *(undefined1 *)(unaff_EBX + 0x102e + (int)unaff_EDI);
  *(undefined1 *)(*unaff_EDI + 0x102e + (int)unaff_EDI) =
       *(undefined1 *)(param_1 + 0x102e + (int)unaff_EDI);
  *unaff_EDI = *unaff_EDI + 1;
  if ((*unaff_EDI == unaff_EDI[1]) && (unaff_EDI[7] < 0xc)) {
    unaff_EDI[7] = unaff_EDI[7] + 1;
    unaff_EDI[1] = unaff_EDI[1] << 1;
  }
  return;
}


