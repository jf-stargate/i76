/*
 * Program: i76.exe
 * Function: geometry_binding_table_helper_00446900
 * Entry: 00446900
 * Signature: bool __stdcall geometry_binding_table_helper_00446900(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: geometry binding table helper based on
   prior focused closure context. */

bool geometry_binding_table_helper_00446900(void)

{
  int *piVar1;
  int iVar2;
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
  puVar4 = &g_geometry_cache_by_handle;
  for (iVar2 = 0x7ed; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = &g_geometry_cache_by_8char_name;
  for (iVar2 = 0x7ed; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  g_geometry_purge_list_head = 0;
  DAT_00608e5c = ((47999999 < local_20[2]) - 1 & 0xfff551a0) + 2000000;
  g_geometry_purge_list_tail = 0;
  g_geometry_heap = HeapCreate(0,0,DAT_00608e5c);
  if (g_geometry_heap == (HANDLE)0x0) {
    return false;
  }
  g_geometry_cache_entry_heap = HeapCreate(0,0,0);
  return g_geometry_cache_entry_heap == (HANDLE)0x0;
}


