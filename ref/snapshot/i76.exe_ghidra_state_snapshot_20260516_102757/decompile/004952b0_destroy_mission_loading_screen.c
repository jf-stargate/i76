/*
 * Program: i76.exe
 * Function: destroy_mission_loading_screen
 * Entry: 004952b0
 * Signature: undefined __stdcall destroy_mission_loading_screen(void)
 */


/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Releases mission loading screen
   textures, bitmap contexts, GDI fonts, and display state. */

void destroy_mission_loading_screen(void)

{
  undefined4 uVar1;
  HGDIOBJ pvVar2;
  int iVar3;
  undefined4 *puVar4;
  
  uVar1 = g_loading_screen_previous_state;
  if (DAT_00654a34 != 0) {
    release_localized_texture_resource_variant((char *)&g_loading_screen_bitmap_resource_name,0,0);
    DAT_00654a34 = 0;
  }
  release_bitmap_surface_context(&DAT_00654a6c);
  if (DAT_00654a68 != (HGDIOBJ)0x0) {
    DeleteObject(DAT_00654a68);
    DAT_00654a68 = (HGDIOBJ)0x0;
  }
  release_bitmap_surface_context(&DAT_00654aa0);
  release_bitmap_surface_context(&DAT_00654ad4);
  force_feedback_runtime_helper_00445b40();
  if (g_loading_screen_hdc != (HDC)0x0) {
    pvVar2 = GetStockObject(0xd);
    SelectObject(g_loading_screen_hdc,pvVar2);
    pvVar2 = GetStockObject(5);
    SelectObject(g_loading_screen_hdc,pvVar2);
  }
  if (g_loading_x1_map_texture_handle != 0) {
    release_localized_texture_resource_variant(s_x1_map_004fd7e8,0,0);
  }
  if (g_loading_font_primary != (HGDIOBJ)0x0) {
    DeleteObject(g_loading_font_primary);
  }
  if (g_loading_font_secondary != (HGDIOBJ)0x0) {
    DeleteObject(g_loading_font_secondary);
  }
  if (g_loading_font_progress != (HGDIOBJ)0x0) {
    DeleteObject(g_loading_font_progress);
  }
  if (g_loading_font_progress_alt != (HGDIOBJ)0x0) {
    DeleteObject(g_loading_font_progress_alt);
  }
  if (g_loading_font_large != (HGDIOBJ)0x0) {
    DeleteObject(g_loading_font_large);
  }
  if (g_loading_font_large_alt != (HGDIOBJ)0x0) {
    DeleteObject(g_loading_font_large_alt);
  }
  puVar4 = &g_current_loading_screen_record;
  for (iVar3 = 0x41; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  g_loading_screen_previous_state = uVar1;
  capture_and_hide_mouse_cursor();
  return;
}


