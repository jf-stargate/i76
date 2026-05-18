/*
 * Program: i76.exe
 * Function: redraw_mission_loading_screen
 * Entry: 00496870
 * Signature: undefined __stdcall redraw_mission_loading_screen(void)
 */


/* [cgpt i76.exe mission/runtime rename v14; confidence=high] Redraws mission loading screen backing
   surface, paints selected entries, prints mission timer for nonzero mission family, flips/repaints
   through display callbacks. */

void redraw_mission_loading_screen(void)

{
  char cVar1;
  HGDIOBJ pvVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  code *pcVar6;
  uint *puVar7;
  char *pcVar8;
  int iVar9;
  char local_c [12];
  
  iVar3 = g_current_loading_screen_record;
  fill_bitmap_surface_context(&DAT_00654aa0,0xff);
  pvVar2 = GetStockObject(2);
  pcVar6 = SelectObject_exref;
  SelectObject(g_loading_screen_hdc,pvVar2);
  pvVar2 = SelectObject(g_loading_screen_hdc,DAT_00654a68);
  RealizePalette(g_loading_screen_hdc);
  SetTextColor(g_loading_screen_hdc,0x2101010);
  SetBkColor(g_loading_screen_hdc,0x2f0f0f0);
  SetBkMode(g_loading_screen_hdc,1);
  if (g_current_loading_screen_record != 0) {
    if (g_selected_mission_family != 0) {
      sprintf(local_c,s__05d__03d_004fd8c0,*(int *)(g_current_loading_screen_record + 0x24) / 1000,
              *(int *)(g_current_loading_screen_record + 0x24) % 1000);
      SelectObject(g_loading_screen_hdc,DAT_00654a50);
      if (g_display_mode_variant_index < 6) {
        uVar4 = 0xffffffff;
        pcVar8 = local_c;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar1 != '\0');
        TextOutA(g_loading_screen_hdc,0xe2,0x3c,local_c,~uVar4 - 1);
      }
    }
    puVar7 = *(uint **)(iVar3 + 0x18);
    iVar9 = 0;
    if (0 < *(int *)(iVar3 + 0x1c)) {
      do {
        puVar5 = (uint *)(g_loading_screen_layout_table + puVar7[3] * 0x20);
        puVar7[7] = *puVar5;
        puVar7[8] = puVar5[1];
        puVar7[9] = puVar5[2];
        puVar7[10] = puVar5[3];
        puVar5 = (uint *)(g_loading_screen_layout_table + 0x10 + puVar7[3] * 0x20);
        puVar7[0xb] = *puVar5;
        puVar7[0xc] = puVar5[1];
        puVar7[0xd] = puVar5[2];
        puVar7[0xe] = puVar5[3];
        draw_mission_loading_screen_entry
                  (puVar7,(uint)(iVar9 == *(int *)(g_current_loading_screen_record + 0x20)));
        iVar9 = iVar9 + 1;
        puVar7 = puVar7 + 0xf;
        pcVar6 = SelectObject_exref;
      } while (iVar9 < *(int *)(iVar3 + 0x1c));
    }
  }
  GdiFlush();
  if (DAT_005a6154 != 0) {
    DAT_005a6154 = 0;
    (*DAT_005dd2e8)(&DAT_005dcec0);
  }
  iVar3 = (*DAT_005dd2bc)(&DAT_005dcec0);
  if (iVar3 != 0) {
    blit_bitmap_surface_context_clipped_with_palette_blend
              (&DAT_005dcec0,&DAT_00654a6c,DAT_00654a3c,DAT_00654a40,(uint *)0x0);
    blit_bitmap_surface_context_clipped_with_palette_blend
              (&DAT_005dcec0,&DAT_00654aa0,DAT_00654a3c,DAT_00654a40,(uint *)0x1);
    (*DAT_005dd2c0)(&DAT_005dcec0);
  }
  (*pcVar6)(g_loading_screen_hdc,pvVar2);
  (*DAT_005dd2e0)(&DAT_005dcec0);
  return;
}


