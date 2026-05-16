/*
 * Program: i76.exe
 * Function: toggle_runtime_camera_debug_or_reverse_flag
 * Entry: 00405b30
 * Signature: undefined __stdcall toggle_runtime_camera_debug_or_reverse_flag(void)
 */


/* cgpt readability rename v13 set A: Toggles a runtime camera/display boolean flag at DAT_004c2718.
    */

void toggle_runtime_camera_debug_or_reverse_flag(void)

{
  DAT_004c2718 = (uint)(DAT_004c2718 == 0);
  return;
}


