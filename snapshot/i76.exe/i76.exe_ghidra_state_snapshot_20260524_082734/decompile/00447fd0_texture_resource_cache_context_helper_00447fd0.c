/*
 * Program: i76.exe
 * Function: texture_resource_cache_context_helper_00447fd0
 * Entry: 00447fd0
 * Signature: undefined __stdcall texture_resource_cache_context_helper_00447fd0(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: texture resource cache context helper
   based on prior focused closure context. */

void texture_resource_cache_context_helper_00447fd0(void)

{
  if (DAT_00531d04 != (HANDLE)0x0) {
    HeapDestroy(DAT_00531d04);
  }
  DAT_00531d04 = (HANDLE)0x0;
  DAT_00531d08 = 0;
  DAT_00531d0c = 0;
  DAT_00531d14 = 0;
  DAT_00531d10 = 0;
  DAT_00531e1c = 0;
  return;
}


