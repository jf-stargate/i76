/*
 * Program: i76.exe
 * Function: select_display_mode_font_descriptor
 * Entry: 004998d0
 * Signature: undefined4 __cdecl select_display_mode_font_descriptor(int param_1, undefined4 param_2)
 */


/* [cgpt i76.exe mission/vehicle runtime rename v15; confidence=high] Returns font descriptor
   indexed by current display/options profile, falling back to caller default. */

undefined4 __cdecl select_display_mode_font_descriptor(int param_1,undefined4 param_2)

{
  if ((PTR_DAT_004fe194 != (undefined *)0x0) && (param_1 < 8)) {
    return *(undefined4 *)(*(int *)(PTR_DAT_004fe194 + 4) + param_1 * 4);
  }
  return param_2;
}


