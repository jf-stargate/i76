/*
 * Program: i76.exe
 * Function: advance_smacker_cutscene_frame
 * Entry: 0049a670
 * Signature: undefined4 __stdcall advance_smacker_cutscene_frame(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 first-pass rename
   old_name: FUN_0049a670
   suggested_name: advance_smacker_cutscene_frame
   basis: Waits, renders, advances Smacker frame, closes playback on final frame. */

undefined4 advance_smacker_cutscene_frame(void)

{
  HWND pHVar1;
  int iVar2;
  HWND pHVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  tagMSG tStack_31c;
  undefined4 local_300 [192];
  
  if (g_active_smacker_cutscene_handle == 0) {
    return 0;
  }
  iVar2 = _SmackWait_4(g_active_smacker_cutscene_handle);
  pHVar1 = DAT_005dcf7c;
  if (iVar2 != 0) {
    return 1;
  }
  if (DAT_004f9f20 == 0) {
    uVar4 = (*DAT_005dd2d0)(&DAT_005dcec0);
    uVar4 = render_smacker_frame_to_buffer(uVar4);
    return uVar4;
  }
  pHVar3 = GetFocus();
  if (pHVar3 == pHVar1) {
    if (*(int *)(g_active_smacker_cutscene_handle + 0x68) != 0) {
      puVar5 = (undefined4 *)(g_active_smacker_cutscene_handle + 0x6c);
      puVar6 = local_300;
      for (iVar2 = 0xc0; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      matrix_rotation_context_helper_004797f0((int)local_300,0,*(int *)(DAT_005a7d74 + 0x2c),0);
      (*DAT_005dd2c8)(&DAT_005dcec0,local_300);
    }
    _DAT_005a7d7c = 0;
    (*DAT_005dd2bc)(&DAT_005dcec0);
    _SmackToBuffer_28(g_active_smacker_cutscene_handle,0,0,*(undefined4 *)(DAT_005a7d74 + 0x18),
                      *(undefined4 *)(DAT_005a7d74 + 0x14),DAT_005dced4,0);
    _SmackDoFrame_4(g_active_smacker_cutscene_handle);
    (*DAT_005dd2c0)(&DAT_005dcec0);
    (*DAT_005dd2e0)(&DAT_005dcec0);
  }
  if (*(int *)(g_active_smacker_cutscene_handle + 0x374) ==
      *(int *)(g_active_smacker_cutscene_handle + 0xc) + -1) {
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
    iVar2 = (*DAT_005dd2cc)(&DAT_005dcec0,DAT_005a7d6c);
    if (iVar2 == 0) {
      report_chunk_parse_error();
    }
    (*DAT_005dd2c8)(&DAT_005dcec0,&DAT_005dcfa8);
    set_directsound_primary_buffer_rate(DAT_00524564,0x2b11);
    set_directsound_primary_buffer_rate(DAT_00524564,0x2b11);
    resume_cd_audio_after_cutscene_or_mode_change();
    force_feedback_runtime_helper_00445b40();
    iVar2 = PeekMessageA(&tStack_31c,(HWND)0x0,0x200,0x209,1);
    while (iVar2 != 0) {
      iVar2 = PeekMessageA(&tStack_31c,(HWND)0x0,0x200,0x209,1);
    }
    iVar2 = PeekMessageA(&tStack_31c,(HWND)0x0,0x100,0x108,1);
    while (iVar2 != 0) {
      iVar2 = PeekMessageA(&tStack_31c,(HWND)0x0,0x100,0x108,1);
    }
    return 0;
  }
  _SmackNextFrame_4(g_active_smacker_cutscene_handle);
  return 1;
}


