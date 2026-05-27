/*
 * Program: i76.exe
 * Function: set_audio_runtime_pause_when_zero_flag
 * Entry: 00423600
 * Signature: undefined __cdecl set_audio_runtime_pause_when_zero_flag(int param_1)
 */


/* cgpt readability rename v13 set A: Stores an inverted audio pause/mute style flag at
   DAT_00524580. */

void __cdecl set_audio_runtime_pause_when_zero_flag(int param_1)

{
  DAT_00524580 = (uint)(param_1 == 0);
  return;
}


