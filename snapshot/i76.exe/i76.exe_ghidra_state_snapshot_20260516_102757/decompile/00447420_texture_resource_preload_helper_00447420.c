/*
 * Program: i76.exe
 * Function: texture_resource_preload_helper_00447420
 * Entry: 00447420
 * Signature: undefined __stdcall texture_resource_preload_helper_00447420(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: texture resource preload helper based
   on prior focused closure context. */

void texture_resource_preload_helper_00447420(void)

{
  int *piVar1;
  int iVar2;
  SIZE_T dwMaximumSize;
  int *piVar3;
  undefined4 *puVar4;
  int local_20 [8];
  
  piVar1 = (int *)system_cutscene_memory_context_helper_00499ae0(local_20);
  piVar3 = local_20;
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar3 = *piVar1;
    piVar1 = piVar1 + 1;
    piVar3 = piVar3 + 1;
  }
  DAT_00531cf4 = HeapCreate(0,0,0);
  if (local_20[2] < 32000000) {
    dwMaximumSize = 0x36b000;
  }
  else {
    dwMaximumSize = ((63999999 < local_20[2]) - 1 & 0xfff00000) + 0x600000;
  }
  g_vqm_texture_heap_handle = HeapCreate(0,0,dwMaximumSize);
  puVar4 = &g_vqm_texture_cache_hash;
  for (iVar2 = 0x6d; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  g_vqm_texture_cache_bytes_remaining = dwMaximumSize;
  g_vqm_texture_lru_head = 0;
  g_vqm_texture_lru_tail = 0;
  return;
}


