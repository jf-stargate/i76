/*
 * Program: i76.exe
 * Function: close_smacker_cutscene_and_restore_display
 * Entry: 0049a920
 * Signature: undefined __stdcall close_smacker_cutscene_and_restore_display(void)
 */


/* i76 first-pass rename
   old_name: FUN_0049a920
   suggested_name: close_smacker_cutscene_and_restore_display
   basis: Cleanup path for Smacker playback and display restoration. */

void close_smacker_cutscene_and_restore_display(void)

{
  int iVar1;
  
  if (DAT_005a7d74 != 0) {
    _SmackBufferClose_4(DAT_005a7d74);
    DAT_005a7d74 = 0;
  }
  if (g_active_smacker_cutscene_handle != 0) {
    _SmackClose_4(g_active_smacker_cutscene_handle);
    g_active_smacker_cutscene_handle = 0;
  }
  mission_flow_map_context_helper_0049cdd0(1);
  if (DAT_00504be8 == 0) {
    (*DAT_005dd2e4)(&DAT_005dcec0,DAT_005dd32c);
  }
  else {
    prepare_smacker_cutscene_display_surface(&DAT_005dcec0,DAT_005dd32c);
  }
  (*DAT_005dd2e0)(&DAT_005dcec0);
  DAT_005dd360 = DAT_005a7d6c;
  iVar1 = (*DAT_005dd2cc)(&DAT_005dcec0,DAT_005a7d6c);
  if (iVar1 == 0) {
    report_chunk_parse_error();
  }
  (*DAT_005dd2c8)(&DAT_005dcec0,&DAT_005dcfa8);
  set_directsound_primary_buffer_rate(DAT_00524564,0x2b11);
  return;
}


