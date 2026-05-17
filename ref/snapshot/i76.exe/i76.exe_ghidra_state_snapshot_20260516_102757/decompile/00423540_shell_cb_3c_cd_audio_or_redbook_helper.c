/*
 * Program: i76.exe
 * Function: shell_cb_3c_cd_audio_or_redbook_helper
 * Entry: 00423540
 * Signature: undefined __cdecl shell_cb_3c_cd_audio_or_redbook_helper(uint param_1)
 */


/* [cgpt i76.exe shell callback rename v2; confidence=medium] ShellMain callback slot +0x3c.
   CD-audio subsystem shutdown callback exposed to the shell. */

void __cdecl shell_cb_3c_cd_audio_or_redbook_helper(uint param_1)

{
  int *piVar1;
  undefined4 local_2c [4];
  undefined4 local_1c;
  
  initialize_audio_distance_params_defaults(local_2c);
  local_1c = 0x12;
  piVar1 = find_audio_object_by_name_and_world_object(s_cammo_wav_004ed86c,0);
  release_audio_object_if_present(piVar1);
  set_audio_runtime_category_enable_mask(0xfffffffe,param_1,0xfffffffe);
  create_or_queue_positional_audio_object(s_cammo_wav_004ed86c,0,local_2c,(int *)0x0);
  return;
}


