/*
 * Program: i76.exe
 * Function: get_gameplay_runtime_seconds
 * Entry: 0049c7c0
 * Signature: float10 __stdcall get_gameplay_runtime_seconds(void)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=high] Returns runtime time seconds global
   used by damage/effect timestamps. */

float10 get_gameplay_runtime_seconds(void)

{
                    /* I76 semantic baseline: get_gameplay_runtime_seconds
                       Returns gameplay/runtime seconds used by damage/effect/FSM timestamps. */
  return (float10)g_runtime_time_seconds;
}


