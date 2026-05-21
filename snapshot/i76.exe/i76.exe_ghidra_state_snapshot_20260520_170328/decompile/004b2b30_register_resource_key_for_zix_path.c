/*
 * Program: i76.exe
 * Function: register_resource_key_for_zix_path
 * Entry: 004b2b30
 * Signature: undefined4 __cdecl register_resource_key_for_zix_path(char * param_1, char * param_2)
 */


/* [cgpt i76.exe resource/archive rename v11; confidence=high] Registers a 16-byte resource key
   against a ZIX/search-path index, maintaining the per-record path bitset and sorted table.
   
   I76 rename v43: register_resource_key_for_zix_path
   Registers resource key/path mapping, callback-table entry from shell contract. */

undefined4 __cdecl register_resource_key_for_zix_path(char *param_1,char *param_2)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  void *pvVar4;
  LPVOID pvVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  int iVar9;
  char *pcVar10;
  char *pcVar11;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  canonicalize_resource_key_16byte(param_1);
  iVar9 = 0;
  if (0 < g_resource_key_table_capacity_or_limit) {
    pcVar10 = &g_zix_search_path_records;
    do {
      iVar3 = _stricmp(pcVar10,param_2);
      if (iVar3 == 0) break;
      iVar9 = iVar9 + 1;
      pcVar10 = pcVar10 + 0x10c;
    } while (iVar9 < g_resource_key_table_capacity_or_limit);
  }
  if (0xff < iVar9) {
    sprintf(&g_resource_key_registration_error_buffer,s_More_than__d_zix_paths_specified_004fff1c,
            0x100);
    return 0;
  }
  if (iVar9 == g_resource_key_table_capacity_or_limit) {
    uVar6 = 0xffffffff;
    (&DAT_006593e0)[g_resource_key_table_capacity_or_limit * 0x43] = 1;
    do {
      pcVar10 = param_2;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar10 = param_2 + 1;
      cVar1 = *param_2;
      param_2 = pcVar10;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar10 = pcVar10 + -uVar6;
    pcVar8 = &g_zix_search_path_records + g_resource_key_table_capacity_or_limit * 0x10c;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar8 = pcVar8 + 4;
    }
    g_resource_key_table_capacity_or_limit = g_resource_key_table_capacity_or_limit + 1;
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar8 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar8 = pcVar8 + 1;
    }
  }
  local_30 = *(undefined4 *)param_1;
  local_2c = *(undefined4 *)(param_1 + 4);
  local_28 = *(undefined4 *)(param_1 + 8);
  local_24 = *(undefined4 *)(param_1 + 0xc);
  pvVar4 = bsearch(&local_30,g_resource_key_table_entries,g_resource_key_table_count,0x30,
                   (_PtFuncCompare *)&compare_resource_record_16byte_key);
  bVar2 = (byte)(iVar9 >> 0x1f);
  if (pvVar4 != (void *)0x0) {
    iVar3 = (int)(iVar9 + (iVar9 >> 0x1f & 0x1fU)) >> 5;
    *(uint *)((int)pvVar4 + iVar3 * 4 + 0x10) =
         *(uint *)((int)pvVar4 + iVar3 * 4 + 0x10) |
         1 << ((((byte)iVar9 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2 & 0x1f);
    return 1;
  }
  pvVar5 = HeapReAlloc(g_resource_key_table_heap_handle,0,g_resource_key_table_entries,
                       (g_resource_key_table_count + 1) * 0x30);
  if (pvVar5 == (LPVOID)0x0) {
    fatal_out_of_memory_message((LPCSTR)0x0);
  }
  pcVar8 = (char *)(g_resource_key_table_count * 0x30 + (int)pvVar5);
  g_resource_key_table_count = g_resource_key_table_count + 1;
  pcVar10 = pcVar8;
  g_resource_key_table_entries = pvVar5;
  for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
    pcVar10[0] = '\0';
    pcVar10[1] = '\0';
    pcVar10[2] = '\0';
    pcVar10[3] = '\0';
    pcVar10 = pcVar10 + 4;
  }
  uVar6 = 0xffffffff;
  do {
    pcVar10 = param_1;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar10 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar10;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar10 = pcVar10 + -uVar6;
  pcVar11 = pcVar8;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
    pcVar10 = pcVar10 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar11 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    pcVar11 = pcVar11 + 1;
  }
  iVar3 = (int)(iVar9 + (iVar9 >> 0x1f & 0x1fU)) >> 5;
  *(uint *)(pcVar8 + (iVar3 + 4) * 4) =
       *(uint *)(pcVar8 + (iVar3 + 4) * 4) |
       1 << ((((byte)iVar9 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2 & 0x1f);
  qsort(g_resource_key_table_entries,g_resource_key_table_count,0x30,
        (_PtFuncCompare *)&compare_resource_record_16byte_key);
  return 1;
}


