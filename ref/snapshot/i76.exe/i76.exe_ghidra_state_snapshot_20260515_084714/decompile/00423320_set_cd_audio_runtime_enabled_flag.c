/*
 * Program: i76.exe
 * Function: set_cd_audio_runtime_enabled_flag
 * Entry: 00423320
 * Signature: undefined __cdecl set_cd_audio_runtime_enabled_flag(undefined4 param_1)
 */


/* cgpt readability rename v13 set A: Stores a CD/audio runtime enabled flag at DAT_004ed800. */

void __cdecl set_cd_audio_runtime_enabled_flag(undefined4 param_1)

{
  DAT_004ed800 = param_1;
  return;
}


