/*
 * Program: i76.exe
 * Function: shell_cb_38_cd_audio_or_redbook_helper
 * Entry: 00423520
 * Signature: undefined __cdecl shell_cb_38_cd_audio_or_redbook_helper(uint param_1)
 */


/* [cgpt i76.exe shell callback rename v2; confidence=medium] ShellMain callback slot +0x38.
   CD-audio subsystem initialization/startup callback exposed to the shell. */

void __cdecl shell_cb_38_cd_audio_or_redbook_helper(uint param_1)

{
  set_audio_runtime_category_enable_mask(param_1,0xfffffffe,0xfffffffe);
  return;
}


