/*
 * Program: i76.exe
 * Function: reset_pix_pak_and_resource_cache
 * Entry: 004713f0
 * Signature: undefined __stdcall reset_pix_pak_and_resource_cache(void)
 */


/* [cgpt i76.exe mission/runtime rename v14; confidence=high] Frees PIX/PAK index, destroys
   loaded-resource cache heap, then calls ZFS/archive cleanup helper. */

void reset_pix_pak_and_resource_cache(void)

{
  free_pix_pak_resource_index();
  destroy_loaded_resource_cache_heap();
  zfsf_payload_wrapper_context_helper_004b9df0();
  return;
}


