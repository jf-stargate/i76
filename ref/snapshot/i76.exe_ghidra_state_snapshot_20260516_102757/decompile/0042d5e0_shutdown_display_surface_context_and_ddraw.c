/*
 * Program: i76.exe
 * Function: shutdown_display_surface_context_and_ddraw
 * Entry: 0042d5e0
 * Signature: undefined __cdecl shutdown_display_surface_context_and_ddraw(int param_1)
 */


/* cgpt rename v4: Releases a display surface context, restores/release DirectDraw interfaces, and
   clears related fullscreen/window state. */

void __cdecl shutdown_display_surface_context_and_ddraw(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x60) == 1) {
    release_bitmap_surface_context((int *)(param_1 + 0x34));
  }
  release_all_video_memory_texture_cache_records();
  if (((*(int *)(param_1 + 8) == 1) && (DAT_005fff34 == 1)) && (DAT_006080cc != (int *)0x0)) {
    iVar1 = (**(code **)(*DAT_006080cc + 8))(DAT_006080cc);
    if (iVar1 == 0) {
      DAT_006080cc = (int *)0x0;
    }
  }
  release_directdraw_direct3d_interfaces();
  return;
}


