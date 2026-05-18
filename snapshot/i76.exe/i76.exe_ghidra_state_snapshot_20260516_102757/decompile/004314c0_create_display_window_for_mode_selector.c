/*
 * Program: i76.exe
 * Function: create_display_window_for_mode_selector
 * Entry: 004314c0
 * Signature: undefined4 __cdecl create_display_window_for_mode_selector(int param_1, undefined4 * param_2)
 */


/* cgpt readability rename v13 set A: Dispatches display window creation to windowed or fullscreen
   mode based on a mode selector. */

undefined4 __cdecl create_display_window_for_mode_selector(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    uVar1 = create_display_window_mode_b(param_2);
    return uVar1;
  }
  if (param_1 != 1) {
    return 0;
  }
  uVar1 = create_raster_fullscreen_window_640x480(param_2);
  return uVar1;
}


