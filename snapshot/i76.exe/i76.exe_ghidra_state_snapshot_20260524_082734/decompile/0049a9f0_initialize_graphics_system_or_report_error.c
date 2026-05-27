/*
 * Program: i76.exe
 * Function: initialize_graphics_system_or_report_error
 * Entry: 0049a9f0
 * Signature: undefined __stdcall initialize_graphics_system_or_report_error(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence Init_Graphic_System */

void initialize_graphics_system_or_report_error(void)

{
  int iVar1;
  tagMSG tStack_1c;
  
  if (DAT_005a7d74 != 0) {
    _SmackBufferClose_4(DAT_005a7d74);
    DAT_005a7d74 = 0;
  }
  if (g_active_smacker_cutscene_handle != 0) {
    _SmackClose_4(g_active_smacker_cutscene_handle);
    g_active_smacker_cutscene_handle = 0;
  }
  mission_flow_map_context_helper_0049cdd0(1);
  if (g_cmdline_hardware_raster_requested == 0) {
    (*DAT_005dd2e4)(&DAT_005dcec0,DAT_005dd32c);
  }
  else {
    prepare_smacker_cutscene_display_surface(&DAT_005dcec0,DAT_005dd32c);
  }
  (*DAT_005dd2e0)(&DAT_005dcec0);
  DAT_005dd360 = DAT_005a7d6c;
  iVar1 = (*DAT_005dd2cc)(&DAT_005dcec0,DAT_005a7d6c);
  if (iVar1 == 0) {
    report_error();
  }
  (*DAT_005dd2c8)(&DAT_005dcec0,&DAT_005dcfa8);
  set_directsound_primary_buffer_rate(DAT_00524564,0x2b11);
  set_directsound_primary_buffer_rate(DAT_00524564,0x2b11);
  resume_cd_audio_after_cutscene_or_mode_change();
  force_feedback_runtime_helper_00445b40();
  iVar1 = PeekMessageA(&tStack_1c,(HWND)0x0,0x200,0x209,1);
  while (iVar1 != 0) {
    iVar1 = PeekMessageA(&tStack_1c,(HWND)0x0,0x200,0x209,1);
  }
  iVar1 = PeekMessageA(&tStack_1c,(HWND)0x0,0x100,0x108,1);
  while (iVar1 != 0) {
    iVar1 = PeekMessageA(&tStack_1c,(HWND)0x0,0x100,0x108,1);
  }
  return;
}


