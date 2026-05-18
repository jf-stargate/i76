/*
 * Program: i76.exe
 * Function: render_smacker_frame_to_buffer
 * Entry: 00499d60
 * Signature: undefined4 __cdecl render_smacker_frame_to_buffer(undefined4 param_1)
 */


/* i76 first-pass rename
   old_name: FUN_00499d60
   suggested_name: render_smacker_frame_to_buffer
   basis: Renders current Smacker frame using SmackDoFrame/SmackToBufferRect/SmackBufferBlit. */

undefined4 __cdecl render_smacker_frame_to_buffer(undefined4 param_1)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 uVar5;
  undefined4 uVar4;
  undefined2 uVar6;
  undefined2 extraout_var_02;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined8 uVar9;
  tagMSG tStack_31c;
  undefined4 local_300 [192];
  
  bVar1 = true;
  if (DAT_00504c1c == 0) {
    return 1;
  }
  if (*(int *)(g_active_smacker_cutscene_handle + 0x68) != 0) {
    puVar7 = (undefined4 *)(g_active_smacker_cutscene_handle + 0x6c);
    puVar8 = local_300;
    for (iVar3 = 0xc0; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    matrix_rotation_context_helper_004797f0((int)local_300,0,*(int *)(DAT_005a7d74 + 0x2c),0);
    _SmackBufferNewPalette_12(DAT_005a7d74,local_300,0);
    if (*(uint *)(DAT_005a7d74 + 0x30) < 0x100) {
      _SmackColorRemap_16(g_active_smacker_cutscene_handle,local_300,
                          *(undefined4 *)(DAT_005a7d74 + 0x2c),*(undefined4 *)(DAT_005a7d74 + 0x43c)
                         );
    }
  }
  _SmackDoFrame_4(g_active_smacker_cutscene_handle);
  uVar9 = _SmackToBufferRect_8(g_active_smacker_cutscene_handle,1);
  uVar4 = (undefined4)((ulonglong)uVar9 >> 0x20);
  uVar5 = (undefined2)((ulonglong)uVar9 >> 0x30);
  uVar6 = extraout_var;
  if ((int)uVar9 != 0) {
    bVar1 = false;
    do {
      uVar6 = (undefined2)((uint)uVar4 >> 0x10);
      sVar2 = _SmackBufferBlit_32(DAT_005a7d74,param_1,0,0,
                                  *(undefined2 *)(g_active_smacker_cutscene_handle + 0x380),
                                  CONCAT22(uVar6,*(undefined2 *)
                                                  (g_active_smacker_cutscene_handle + 900)),
                                  *(undefined2 *)(g_active_smacker_cutscene_handle + 0x388),
                                  CONCAT22(uVar6,*(undefined2 *)
                                                  (g_active_smacker_cutscene_handle + 0x38c)));
      uVar6 = extraout_var_00;
      uVar5 = extraout_var_02;
      if (sVar2 != 0) break;
      uVar9 = _SmackToBufferRect_8(g_active_smacker_cutscene_handle,1);
      uVar4 = (undefined4)((ulonglong)uVar9 >> 0x20);
      uVar5 = (undefined2)((ulonglong)uVar9 >> 0x30);
      uVar6 = extraout_var_01;
    } while ((int)uVar9 != 0);
  }
  if (bVar1) {
    _SmackBufferBlit_32(DAT_005a7d74,param_1,0,0,
                        CONCAT22(uVar5,*(undefined2 *)(g_active_smacker_cutscene_handle + 0x380)),
                        CONCAT22(uVar6,*(undefined2 *)(g_active_smacker_cutscene_handle + 900)),
                        CONCAT22(uVar5,*(undefined2 *)(g_active_smacker_cutscene_handle + 0x388)),
                        CONCAT22(uVar6,*(undefined2 *)(g_active_smacker_cutscene_handle + 0x38c)));
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
    iVar3 = (*DAT_005dd2cc)(&DAT_005dcec0,DAT_005a7d6c);
    if (iVar3 == 0) {
      report_chunk_parse_error();
    }
    (*DAT_005dd2c8)(&DAT_005dcec0,&DAT_005dcfa8);
    set_directsound_primary_buffer_rate(DAT_00524564,0x2b11);
    set_directsound_primary_buffer_rate(DAT_00524564,0x2b11);
    resume_cd_audio_after_cutscene_or_mode_change();
    force_feedback_runtime_helper_00445b40();
    iVar3 = PeekMessageA(&tStack_31c,(HWND)0x0,0x200,0x209,1);
    while (iVar3 != 0) {
      iVar3 = PeekMessageA(&tStack_31c,(HWND)0x0,0x200,0x209,1);
    }
    iVar3 = PeekMessageA(&tStack_31c,(HWND)0x0,0x100,0x108,1);
    while (iVar3 != 0) {
      iVar3 = PeekMessageA(&tStack_31c,(HWND)0x0,0x100,0x108,1);
    }
    return 0;
  }
  _SmackNextFrame_4(g_active_smacker_cutscene_handle);
  return 1;
}


