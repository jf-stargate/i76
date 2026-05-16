/*
 * Program: i76.exe
 * Function: destroy_texture_binding_cache_heaps
 * Entry: 0044a630
 * Signature: undefined __stdcall destroy_texture_binding_cache_heaps(void)
 */


/* cgpt rename v2: Releases texture-set cache, texture-slot bindings, object binding lists, and
   associated heaps. */

void destroy_texture_binding_cache_heaps(void)

{
  LPVOID pvVar1;
  LPVOID pvVar2;
  undefined4 *puVar3;
  
  puVar3 = &g_texture_set_cache_hash;
  do {
    pvVar2 = (LPVOID)*puVar3;
    while (pvVar2 != (LPVOID)0x0) {
      HeapFree(g_texture_name_array_heap,0,*(LPVOID *)((int)pvVar2 + 0x2c));
      pvVar1 = *(LPVOID *)((int)pvVar2 + 0x30);
      HeapFree(g_texture_set_cache_heap,0,pvVar2);
      pvVar2 = pvVar1;
    }
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  } while ((int)puVar3 < 0x533dd4);
  puVar3 = &g_texture_slot_binding_hash;
  do {
    pvVar2 = (LPVOID)*puVar3;
    while (pvVar2 != (LPVOID)0x0) {
      if ((*(byte *)((int)pvVar2 + 0x3c) & 1) == 0) {
        release_vqm_texture_cache_reference_by_name((char *)((int)pvVar2 + 4));
      }
      else {
        xfree_global_heap(*(LPVOID *)((int)pvVar2 + 0x34));
      }
      release_m16_resource_handle((int *)((int)pvVar2 + 0x38),(char *)((int)pvVar2 + 4));
      pvVar1 = *(LPVOID *)((int)pvVar2 + 0x40);
      HeapFree(g_texture_slot_binding_heap,0,pvVar2);
      pvVar2 = pvVar1;
    }
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  } while ((int)puVar3 < 0x535f54);
  puVar3 = &g_texture_bindings_by_object_hash;
  do {
    pvVar2 = (LPVOID)*puVar3;
    while (pvVar2 != (LPVOID)0x0) {
      pvVar1 = *(LPVOID *)((int)pvVar2 + 8);
      HeapFree(g_texture_object_binding_list_heap,0,pvVar2);
      pvVar2 = pvVar1;
    }
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  } while ((int)puVar3 < 0x533f9c);
  HeapDestroy(g_texture_set_cache_heap);
  HeapDestroy(g_texture_slot_binding_heap);
  HeapDestroy(g_texture_name_array_heap);
  HeapDestroy(g_texture_object_binding_list_heap);
  return;
}


