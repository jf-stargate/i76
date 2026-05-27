/*
 * Program: i76.exe
 * Function: get_runtime_update_delta_seconds
 * Entry: 0049c7a0
 * Signature: float10 __stdcall get_runtime_update_delta_seconds(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium] Runtime frame/update delta
   accessor used by vehicle frame update before lifecycle and control update calls. */

float10 get_runtime_update_delta_seconds(void)

{
  return (float10)_DAT_004fe420;
}


