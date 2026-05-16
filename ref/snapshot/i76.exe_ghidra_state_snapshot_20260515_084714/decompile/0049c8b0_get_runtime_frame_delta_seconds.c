/*
 * Program: i76.exe
 * Function: get_runtime_frame_delta_seconds
 * Entry: 0049c8b0
 * Signature: float10 __stdcall get_runtime_frame_delta_seconds(void)
 */


/* [cgpt i76.exe weapon/projectile v27; confidence=high] Returns current frame delta scalar used by
   targeting, cooldowns, projectile spread, and mount updates. */

float10 get_runtime_frame_delta_seconds(void)

{
  return (float10)DAT_004fe428;
}


