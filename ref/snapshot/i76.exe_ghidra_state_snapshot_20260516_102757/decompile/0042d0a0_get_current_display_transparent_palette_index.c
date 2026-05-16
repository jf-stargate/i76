/*
 * Program: i76.exe
 * Function: get_current_display_transparent_palette_index
 * Entry: 0042d0a0
 * Signature: undefined2 __stdcall get_current_display_transparent_palette_index(void)
 */


/* cgpt rename v8 display/d3d cluster: Returns the active transparent palette index, using 0xff in
   one display mode and DAT_0060865e otherwise. */

undefined2 get_current_display_transparent_palette_index(void)

{
  if (DAT_005fff34 == 1) {
    return 0xff;
  }
  return DAT_0060865e;
}


