/*
 * Program: i76.exe
 * Function: initialize_notepad_objective_display
 * Entry: 0045e2b0
 * Signature: undefined __stdcall initialize_notepad_objective_display(void)
 */


/* cgpt whole-binary semantic rename v1: loads notepad textures/DC/font and objective state */

void initialize_notepad_objective_display(void)

{
  int *piVar1;
  HGDIOBJ pvVar2;
  undefined4 uVar3;
  HDC hdc;
  undefined4 *puVar4;
  int iVar5;
  code *pcVar6;
  undefined4 *puVar7;
  uint uStack_6c;
  int aiStack_68 [13];
  int aiStack_34 [13];
  
  if (g_runtime_display_input_mode == 8) {
    piVar1 = find_audio_object_by_name_and_world_object(s_cnote_wav_004f749c,0);
    release_audio_object_if_present(piVar1);
    release_bitmap_surface_context(&DAT_00609478);
    release_bitmap_surface_context(&DAT_00609444);
    if (DAT_006094dc != (HDC)0x0) {
      pvVar2 = GetStockObject(0xd);
      SelectObject(DAT_006094dc,pvVar2);
      pvVar2 = GetStockObject(5);
      SelectObject(DAT_006094dc,pvVar2);
      DeleteDC(DAT_006094dc);
    }
    if (DAT_006094ac != (uint *)0x0) {
      xfree_global_heap(DAT_006094ac);
    }
    if (DAT_006094c0 != (HGDIOBJ)0x0) {
      DeleteObject(DAT_006094c0);
    }
    if (DAT_006094e0 != (HFONT)0x0) {
      DeleteObject(DAT_006094e0);
    }
    puVar4 = &DAT_00609440;
    for (iVar5 = 0x29; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    start_pending_audio_objects();
    mission_flow_map_context_helper_0049cdd0(1);
    force_feedback_runtime_helper_00445b40();
    return;
  }
  if (DAT_006093c0 < 1) {
    report_chunk_parse_error();
  }
  puVar4 = &DAT_00609440;
  for (iVar5 = 0x29; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  uVar3 = mission_flow_map_context_helper_0049ccc0();
  sprintf(&DAT_006094b0,s_ZNPD_1d01_map_004f72c0,uVar3);
  hdc = (HDC)(*DAT_005dd2d0)(&DAT_005dcec0);
  DAT_006094dc = CreateCompatibleDC(hdc);
  if ((DAT_006094dc == (HDC)0x0) ||
     (DAT_006094e0 = create_gdi_font_from_i76_font_descriptor(&PTR_PTR_004f7298),
     DAT_006094e0 == (HFONT)0x0)) {
    report_chunk_parse_error();
    release_bitmap_surface_context(&DAT_00609478);
    release_bitmap_surface_context(&DAT_00609444);
    if (DAT_006094dc == (HDC)0x0) goto LAB_0045e5a8;
    pvVar2 = GetStockObject(0xd);
    SelectObject(DAT_006094dc,pvVar2);
    pvVar2 = GetStockObject(5);
    SelectObject(DAT_006094dc,pvVar2);
    DeleteDC(DAT_006094dc);
    if (DAT_006094ac == (uint *)0x0) goto LAB_0045e5ba;
    xfree_global_heap(DAT_006094ac);
    pcVar6 = DeleteObject_exref;
    if (DAT_006094c0 != (HGDIOBJ)0x0) {
      DeleteObject(DAT_006094c0);
      if (DAT_006094e0 != (HFONT)0x0) {
        DeleteObject(DAT_006094e0);
        puVar4 = &DAT_00609440;
        for (iVar5 = 0x29; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar4 = 0;
          puVar4 = puVar4 + 1;
        }
        (*DAT_005dd2d4)(&DAT_005dcec0);
        return;
      }
      goto LAB_0045e5d8;
    }
  }
  else {
    DAT_006094c8 = 0;
    DAT_006094c4 = 0;
    if (g_display_mode_variant_index < 6) {
      iVar5 = 0x1c0;
      DAT_006094d0 = 0x13d;
      DAT_006094cc = 0x1c0;
    }
    else {
      iVar5 = 0xe4;
      DAT_006094d0 = 199;
      DAT_006094cc = 0xe4;
    }
    puVar4 = (undefined4 *)
             create_dibsection_8bpp_surface_context_with_game_palette
                       (aiStack_68,DAT_006094dc,iVar5,DAT_006094d0,&DAT_006094c0);
    puVar7 = &DAT_00609478;
    for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar7 = puVar7 + 1;
    }
    if (DAT_006094c0 != (HGDIOBJ)0x0) {
      uStack_6c = 0;
      load_localized_texture_or_vqm_to_buffer(&DAT_006094b0,0,4,(uint *)0x0,&uStack_6c);
      DAT_006094ac = (uint *)xalloc_global_heap(uStack_6c);
      if (DAT_006094ac == (uint *)0x0) {
        report_chunk_parse_error();
      }
      else {
        iVar5 = load_localized_texture_or_vqm_to_buffer(&DAT_006094b0,0,4,DAT_006094ac,&uStack_6c);
        if (iVar5 == 0) {
          report_chunk_parse_error();
        }
        else {
          puVar4 = (undefined4 *)
                   construct_bitmap_surface_context
                             (aiStack_34,*DAT_006094ac,(int)(DAT_006094ac[1] << 3) >> 3,
                              (int)(DAT_006094ac + 2),0);
          puVar7 = &DAT_00609444;
          for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar7 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar7 = puVar7 + 1;
          }
          if (DAT_00609458 != 0) {
            if (g_display_mode_variant_index < 6) {
              DAT_006094d8 = (uint *)0x66;
              DAT_006094d4 = 0x52;
            }
            else {
              DAT_006094d8 = (uint *)0x29;
              DAT_006094d4 = 0x28;
            }
            redraw_notepad_objective_display_surface();
            blit_bitmap_surface_context_clipped_with_palette_blend
                      (&DAT_00609444,&DAT_00609478,DAT_006094d4,DAT_006094d8,(uint *)0x1);
            iVar5 = mission_objective_notepad_context_helper_0045e190(&DAT_00609444);
            if (iVar5 != 0) {
              (*DAT_005dd2d4)(&DAT_005dcec0);
              update_audio_object_lists_and_release_finished();
              mission_flow_map_context_helper_0049cdd0(8);
              force_feedback_runtime_helper_00445b60();
              return;
            }
          }
          report_chunk_parse_error();
        }
      }
      release_notepad_objective_display_resources();
      (*DAT_005dd2d4)(&DAT_005dcec0);
      return;
    }
    report_chunk_parse_error();
    release_bitmap_surface_context(&DAT_00609478);
    release_bitmap_surface_context(&DAT_00609444);
    if (DAT_006094dc != (HDC)0x0) {
      pvVar2 = GetStockObject(0xd);
      SelectObject(DAT_006094dc,pvVar2);
      pvVar2 = GetStockObject(5);
      SelectObject(DAT_006094dc,pvVar2);
      DeleteDC(DAT_006094dc);
    }
LAB_0045e5a8:
    if (DAT_006094ac != (uint *)0x0) {
      xfree_global_heap(DAT_006094ac);
    }
LAB_0045e5ba:
    pcVar6 = DeleteObject_exref;
    if (DAT_006094c0 != (HGDIOBJ)0x0) {
      DeleteObject(DAT_006094c0);
    }
  }
  if (DAT_006094e0 != (HFONT)0x0) {
    (*pcVar6)(DAT_006094e0);
  }
LAB_0045e5d8:
  puVar4 = &DAT_00609440;
  for (iVar5 = 0x29; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  (*DAT_005dd2d4)(&DAT_005dcec0);
  return;
}


