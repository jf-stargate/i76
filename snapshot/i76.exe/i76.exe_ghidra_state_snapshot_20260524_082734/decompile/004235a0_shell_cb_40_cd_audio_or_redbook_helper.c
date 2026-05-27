/*
 * Program: i76.exe
 * Function: shell_cb_40_cd_audio_or_redbook_helper
 * Entry: 004235a0
 * Signature: undefined __cdecl shell_cb_40_cd_audio_or_redbook_helper(uint param_1)
 */


/* [cgpt i76.exe shell callback rename v2; confidence=medium] ShellMain callback slot +0x40.
   CD-audio availability/status callback exposed to the shell. */

void __cdecl shell_cb_40_cd_audio_or_redbook_helper(uint param_1)

{
  int *piVar1;
  undefined4 local_2c [4];
  undefined4 local_1c;
  
  initialize_audio_distance_params_defaults(local_2c);
  local_1c = 0x14;
  piVar1 = find_audio_object_by_name_and_world_object(s_croger_wav_004ed878,0);
  release_audio_object_if_present(piVar1);
  set_audio_runtime_category_enable_mask(0xfffffffe,0xfffffffe,param_1);
  create_or_queue_positional_audio_object(s_croger_wav_004ed878,0,local_2c,(int *)0x0);
  return;
}


