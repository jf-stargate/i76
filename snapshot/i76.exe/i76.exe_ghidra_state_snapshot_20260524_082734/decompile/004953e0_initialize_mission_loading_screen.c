/*
 * Program: i76.exe
 * Function: initialize_mission_loading_screen
 * Entry: 004953e0
 * Signature: undefined4 __cdecl initialize_mission_loading_screen(undefined * param_1, undefined4 param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe mission/runtime rename v14; confidence=high] Creates compatible DC, fonts, loads
   x1.map, initializes mission loading/menu bitmap context, then calls
   load_selected_loading_screen_bitmap. */

undefined4 __cdecl initialize_mission_loading_screen(undefined *param_1,undefined4 param_2)

{
  int *piVar1;
  HDC hdc;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int aiStack_34 [13];
  
  release_and_show_mouse_cursor();
  if (g_loading_screen_tables_initialized == 0) {
    piVar1 = &DAT_004fb138;
    iVar3 = 0x66;
    do {
      *piVar1 = *piVar1 + piVar1[-2];
      piVar1[1] = piVar1[1] + piVar1[-1];
      piVar1 = piVar1 + 4;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    piVar1 = &DAT_004fb798;
    iVar3 = 0x66;
    do {
      *piVar1 = *piVar1 + piVar1[-2];
      piVar1[1] = piVar1[1] + piVar1[-1];
      piVar1 = piVar1 + 4;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    g_loading_screen_tables_initialized = 1;
  }
  if (g_loading_screen_cached_mission_number != g_selected_mission_number) {
    iVar3 = rand();
    g_loading_screen_cached_mission_number = g_selected_mission_number;
    _DAT_004fc0c4 = iVar3 % 0x3e0 + (g_selected_mission_number + 900) * 1000;
    _DAT_004fc1ac = _DAT_004fc0c4 + 1;
    _DAT_004fc464 = _DAT_004fc0c4 + 2;
    _DAT_004fc71c = _DAT_004fc0c4 + 3;
    _DAT_004fcb5c = _DAT_004fc0c4 + 4;
    _DAT_004fcd5c = _DAT_004fc0c4 + 5;
    _DAT_004fcee4 = _DAT_004fc0c4 + 6;
    _DAT_00654b0c = _DAT_004fc0c4 + 7;
  }
  hdc = (HDC)(*DAT_005dd2d0)(&DAT_005dcec0);
  g_loading_screen_hdc = CreateCompatibleDC(hdc);
  if ((g_loading_screen_hdc != (HDC)0x0) ||
     ((*DAT_005dd2c4)(&DAT_005dcec0,0,0x100,&DAT_005dcfa8,0), g_loading_screen_hdc != (HDC)0x0)) {
    puVar2 = (undefined4 *)select_display_mode_font_descriptor(0,&PTR_PTR_004fb018);
    g_loading_font_primary = create_gdi_font_from_i76_font_descriptor(puVar2);
    if (g_loading_font_primary != (HFONT)0x0) {
      puVar2 = (undefined4 *)select_display_mode_font_descriptor(1,&PTR_s_Arial_Bold_004fb040);
      g_loading_font_secondary = create_gdi_font_from_i76_font_descriptor(puVar2);
      if (g_loading_font_secondary != (HFONT)0x0) {
        puVar2 = (undefined4 *)select_display_mode_font_descriptor(2,&PTR_PTR_004fb068);
        g_loading_font_progress = create_gdi_font_from_i76_font_descriptor(puVar2);
        if (g_loading_font_progress != (HFONT)0x0) {
          puVar2 = (undefined4 *)select_display_mode_font_descriptor(3,&PTR_PTR_004fb090);
          g_loading_font_progress_alt = create_gdi_font_from_i76_font_descriptor(puVar2);
          if (g_loading_font_progress_alt != (HFONT)0x0) {
            puVar2 = (undefined4 *)select_display_mode_font_descriptor(4,&PTR_s_Arial_Bold_004fb0b8)
            ;
            g_loading_font_large = create_gdi_font_from_i76_font_descriptor(puVar2);
            if (g_loading_font_large != (HFONT)0x0) {
              puVar2 = (undefined4 *)select_display_mode_font_descriptor(5,&PTR_PTR_004fb0e0);
              g_loading_font_large_alt = create_gdi_font_from_i76_font_descriptor(puVar2);
              if (g_loading_font_large_alt != (HFONT)0x0) {
                puVar2 = (undefined4 *)
                         select_display_mode_font_descriptor(6,&PTR_s_Arial_Bold_004fb108);
                DAT_00654a50 = create_gdi_font_from_i76_font_descriptor(puVar2);
                if ((DAT_00654a50 != (HFONT)0x0) &&
                   (g_loading_x1_map_texture_handle =
                         (int *)load_localized_texture_resource_variant
                                          ((byte *)s_x1_map_004fd7e8,0,0),
                   g_loading_x1_map_texture_handle != (int *)0x0)) {
                  puVar2 = (undefined4 *)
                           construct_bitmap_surface_context
                                     (aiStack_34,*g_loading_x1_map_texture_handle,
                                      (g_loading_x1_map_texture_handle[1] << 3) >> 3,
                                      (int)(g_loading_x1_map_texture_handle + 2),0);
                  puVar4 = &DAT_00654ad4;
                  for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
                    *puVar4 = *puVar2;
                    puVar2 = puVar2 + 1;
                    puVar4 = puVar4 + 1;
                  }
                  if (DAT_00654ae8 != 0) {
                    g_loading_screen_layout_table = &DAT_004fb790;
                    if (g_display_mode_variant_index < 6) {
                      g_loading_screen_layout_table = &DAT_004fb130;
                    }
                    iVar3 = load_selected_loading_screen_bitmap(param_1);
                    if (iVar3 != 0) {
                      force_feedback_runtime_helper_00445b60();
                      DAT_00654b18 = param_2;
                      (*DAT_005dd2d4)(&DAT_005dcec0);
                      return 1;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  report_error();
  destroy_mission_loading_screen();
  (*DAT_005dd2d4)(&DAT_005dcec0);
  return 0;
}


