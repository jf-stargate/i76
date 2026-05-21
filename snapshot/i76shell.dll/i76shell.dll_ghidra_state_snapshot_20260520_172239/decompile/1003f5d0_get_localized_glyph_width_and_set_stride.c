/*
 * Program: i76shell.dll
 * Function: get_localized_glyph_width_and_set_stride
 * Entry: 1003f5d0
 * Signature: undefined4 __cdecl get_localized_glyph_width_and_set_stride(int param_1, uint param_2)
 */


/* i76shell locale/rich-text rename
   old_name: FUN_1003f5d0
   forced_name: set_single_byte_text_mode_candidate
   basis: Writes DAT_1004efa0; likely character stride/text mode initialization path.
   
   i76shell localized glyph rename
   old_name: set_single_byte_text_mode_candidate
   forced_name: get_localized_glyph_width_and_set_stride
   basis: Maps a byte/DBCS character through DAT_1004ef9c, sets DAT_1004efa0 to 1 or 2, and returns
   localized glyph width. */

undefined4 __cdecl get_localized_glyph_width_and_set_stride(int param_1,uint param_2)

{
  short sVar1;
  int iVar2;
  undefined2 uVar3;
  
  iVar2 = (param_2 & 0xffff00ff) * 2;
  DAT_1004efa0 = 2;
  sVar1 = *(short *)(DAT_1004ef9c + iVar2);
  uVar3 = (undefined2)((uint)iVar2 >> 0x10);
  if (sVar1 == 0) {
    iVar2 = CONCAT31((int3)(CONCAT22(uVar3,sVar1) >> 8),(char)param_2);
    DAT_1004efa0 = 1;
  }
  else {
    iVar2 = CONCAT22(uVar3,sVar1 + ((ushort)param_2 >> 8));
  }
  return *(undefined4 *)(*(int *)(iVar2 * 4 + param_1 + 0x10) + param_1);
}


