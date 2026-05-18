/*
 * Program: i76.exe
 * Function: vqm_texture_cache_context_helper_00447f70
 * Entry: 00447f70
 * Signature: undefined __stdcall vqm_texture_cache_context_helper_00447f70(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: vqm texture cache context helper based
   on prior focused closure context. */

void vqm_texture_cache_context_helper_00447f70(void)

{
  int iVar1;
  
  for (iVar1 = g_vqm_texture_lru_tail; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x1c)) {
    *(ushort *)(iVar1 + 0x16) = *(ushort *)(iVar1 + 0x16) & 0xfffd;
  }
  return;
}


