/*
 * Program: i76.exe
 * Function: get_runtime_time_seconds
 * Entry: 0049c7c0
 * Signature: float10 __stdcall get_runtime_time_seconds(void)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=high] Returns runtime time seconds global
   used by damage/effect timestamps. */

float10 get_runtime_time_seconds(void)

{
  return (float10)g_runtime_time_seconds;
}


