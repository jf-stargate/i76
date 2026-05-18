/*
 * Program: i76.exe
 * Function: reset_display_clip_rects_to_current_mode
 * Entry: 00433ca0
 * Signature: undefined __stdcall reset_display_clip_rects_to_current_mode(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Sets display dirty/fullscreen flags and resets multiple render/client rectangles
   to the current mode dimensions. */

void reset_display_clip_rects_to_current_mode(void)

{
  _DAT_005fd0e4 = 1;
  _DAT_005fdc14 = 1;
  _DAT_005fdc20 = 1;
  SetRect((LPRECT)&DAT_005fdc40,0,0,DAT_00608424,DAT_00608428);
  SetRect((LPRECT)&DAT_005fd920,0,0,DAT_00608424,DAT_00608428);
  SetRect((LPRECT)&DAT_005fcf00,0,0,DAT_00608424,DAT_00608428);
  return;
}


