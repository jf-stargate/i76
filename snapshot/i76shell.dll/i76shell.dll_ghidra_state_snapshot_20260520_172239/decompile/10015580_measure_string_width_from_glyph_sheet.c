/*
 * Program: i76shell.dll
 * Function: measure_string_width_from_glyph_sheet
 * Entry: 10015580
 * Signature: int __thiscall measure_string_width_from_glyph_sheet(void * this, byte * param_1)
 */


/* i76shell forced text/glyph rename
   old_name: FUN_10015580
   forced_name: measure_string_width_from_glyph_sheet
   basis: Walks string, gets each glyph width, and accumulates text width.
   
   i76shell locale/rich-text rename
   old_name: measure_string_width_from_glyph_sheet
   forced_name: measure_string_width_from_glyph_sheet
   basis: Uses DAT_1004efa0 stride and sums glyph widths. */

int __thiscall measure_string_width_from_glyph_sheet(void *this,byte *param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  
  if (param_1 != (byte *)0x0) {
    iVar3 = 0;
    bVar1 = *param_1;
    while (bVar1 != 0) {
      iVar2 = get_glyph_width(*(int *)this,(uint)bVar1);
      iVar3 = iVar3 + iVar2;
      param_1 = param_1 + DAT_1004efa0;
      bVar1 = *param_1;
    }
    return iVar3;
  }
  return 0;
}


