/*
 * Program: i76.exe
 * Function: load_geometry_resource_into_cache
 * Entry: 004469a0
 * Signature: uint __cdecl load_geometry_resource_into_cache(uint * param_1)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=high] Loads a .geo resource through the
   resource stack, calls construct_geometry_from_geo_buffer, and installs the runtime geometry
   record into the geometry cache. */

uint __cdecl load_geometry_resource_into_cache(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  bool bVar8;
  undefined8 uVar9;
  uint local_8;
  uint local_4;
  
  local_8 = *param_1;
  local_4 = param_1[1];
  uVar7 = 0;
  do {
    iVar3 = toupper((int)*(char *)((int)&local_8 + uVar7));
    *(char *)((int)&local_8 + uVar7) = (char)iVar3;
    uVar2 = local_4;
    uVar1 = local_8;
    uVar7 = uVar7 + 1;
  } while (uVar7 < 8);
  uVar9 = __allshr(0x20,local_4);
  uVar7 = ((((uint)uVar9 ^ uVar1) & 0xdfdfdfdf) * 0x6cd + 0xaab) % 0x7ed;
  puVar4 = (uint *)(&g_geometry_cache_by_8char_name)[uVar7];
  while( true ) {
    if (puVar4 == (uint *)0x0) {
      g_resource_nested_load_depth = g_resource_nested_load_depth + 1;
      puVar4 = open_resource_file_into_memory((char *)param_1);
      if (puVar4 == (uint *)0x0) {
        g_resource_nested_load_depth = g_resource_nested_load_depth + -1;
        return 0;
      }
      iVar3 = get_loaded_resource_file_size((char *)param_1);
      puVar5 = HeapAlloc(g_geometry_cache_entry_heap,0,0x20);
      *puVar5 = uVar1;
      puVar5[1] = local_4;
      puVar5[2] = 1;
      puVar5[5] = 0;
      puVar5[4] = 0;
      puVar6 = construct_geometry_from_geo_buffer((int *)puVar4);
      puVar5[3] = (uint)puVar6;
      release_resource_file_reference((char *)param_1);
      puVar5[5] = (&g_geometry_cache_by_8char_name)[uVar7];
      (&g_geometry_cache_by_8char_name)[uVar7] = puVar5;
      uVar7 = (puVar5[3] * 0x6cd + 0xaab) % 0x7ed;
      puVar5[4] = (&g_geometry_cache_by_handle)[uVar7];
      g_resource_nested_load_depth = g_resource_nested_load_depth + -1;
      bVar8 = g_resource_debug_log_file != 0;
      (&g_geometry_cache_by_handle)[uVar7] = puVar5;
      if (bVar8) {
        debug_fprintf_wrapper('g');
        fprintf((FILE *)g_resource_debug_log_file,s__s__d_004f2588,param_1,iVar3);
      }
      return puVar5[3];
    }
    if ((*puVar4 == uVar1) && (puVar4[1] == uVar2)) break;
    puVar4 = (uint *)puVar4[5];
  }
  uVar7 = puVar4[2];
  puVar4[2] = uVar7 + 1;
  if (uVar7 == 0) {
    if (puVar4 == g_geometry_purge_list_head) {
      if (g_geometry_purge_list_head[6] == 0) {
        g_geometry_purge_list_tail = 0;
        g_geometry_purge_list_head = (uint *)g_geometry_purge_list_head[6];
        return puVar4[3];
      }
      *(undefined4 *)(g_geometry_purge_list_head[6] + 0x1c) = 0;
      g_geometry_purge_list_head = (uint *)g_geometry_purge_list_head[6];
      return puVar4[3];
    }
    *(uint *)(puVar4[7] + 0x18) = puVar4[6];
    if (puVar4[6] != 0) {
      *(uint *)(puVar4[6] + 0x1c) = puVar4[7];
      return puVar4[3];
    }
    g_geometry_purge_list_tail = puVar4[7];
  }
  return puVar4[3];
}


