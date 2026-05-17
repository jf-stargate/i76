/*
 * Program: i76.exe
 * Function: texture_cache_record_touch_helper_00447db0
 * Entry: 00447db0
 * Signature: undefined __stdcall texture_cache_record_touch_helper_00447db0(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: texture cache record touch helper
   based on prior focused closure context. */

void texture_cache_record_touch_helper_00447db0(void)

{
  int iVar1;
  
  iVar1 = evict_lru_vqm_texture_cache_record();
  while (iVar1 != 0) {
    iVar1 = evict_lru_vqm_texture_cache_record();
  }
  texture_cache_record_lookup_helper_00447d20();
  return;
}


