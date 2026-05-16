/*
 * Program: i76.exe
 * Function: shutdown_radar_mask_texture
 * Entry: 0045f4d0
 * Signature: undefined __stdcall shutdown_radar_mask_texture(void)
 */


/* i76 second-pass rename
   old_name: FUN_0045f4d0
   suggested_name: shutdown_radar_mask_texture
   basis: Releases zradmask.map and destroys heap. */

void shutdown_radar_mask_texture(void)

{
  if (DAT_0054b200 == 1) {
    release_bitmap_surface_context(&DAT_0054b030);
    release_vqm_texture_cache_reference_by_name(s_zradmask_map_004f7684);
  }
  HeapDestroy(DAT_0054b1f0);
  HeapDestroy(DAT_0054b1f4);
  HeapDestroy(DAT_0054b1f8);
  return;
}


