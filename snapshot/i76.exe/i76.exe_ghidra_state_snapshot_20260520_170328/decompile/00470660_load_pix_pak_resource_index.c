/*
 * Program: i76.exe
 * Function: load_pix_pak_resource_index
 * Entry: 00470660
 * Signature: undefined __stdcall load_pix_pak_resource_index(void)
 */


/* [cgpt i76.exe texture/image/resource renames v21; confidence=high] Enumerates registered *.pix
   index files, maps each to a sibling .pak, parses resource offset/size rows, and builds the sorted
   0x1c-byte indexed-resource table.
   
   I76 rename v43: load_pix_pak_resource_index
   Scans *.pix, derives .pak, parses name/offset/size rows, sorts index. */

void load_pix_pak_resource_index(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  uint local_2c;
  int local_28;
  uint local_24;
  int local_20;
  uint local_1c;
  SIZE_T local_18;
  char *local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  g_pix_pak_file_table = (LPVOID)xcalloc_global_heap(0x40,0x18);
  if (g_pix_pak_file_table == (LPVOID)0x0) {
    fatal_out_of_memory_message((LPCSTR)0x0);
  }
  g_pix_pak_file_count = 0;
  local_20 = 0;
  puVar2 = (undefined4 *)find_next_resource_file_record_by_pattern(s___pix_004f8b8c,&local_20);
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)((int)g_pix_pak_file_table + g_pix_pak_file_count * 0x18);
    *puVar1 = *puVar2;
    puVar1[1] = puVar2[1];
    puVar1[2] = puVar2[2];
    puVar1[3] = puVar2[3];
    pcVar3 = strchr((char *)((int)g_pix_pak_file_table + g_pix_pak_file_count * 0x18),0x2e);
    *(undefined4 *)pcVar3 = s__pak_004f8afc._0_4_;
    pcVar3[4] = s__pak_004f8afc[4];
    *(undefined4 *)((int)g_pix_pak_file_table + g_pix_pak_file_count * 0x18 + 0x10) = 0;
    *(undefined4 *)((int)g_pix_pak_file_table + g_pix_pak_file_count * 0x18 + 0x14) = 0;
    uVar4 = g_pix_pak_file_count + 1;
    if (((uVar4 & 0x3f) == 0) &&
       (iVar5 = g_pix_pak_file_count + 0x41, g_pix_pak_file_count = uVar4,
       g_pix_pak_file_table = (LPVOID)xrealloc_global_heap(g_pix_pak_file_table,iVar5 * 0x18),
       uVar4 = g_pix_pak_file_count, g_pix_pak_file_table == (LPVOID)0x0)) {
      fatal_out_of_memory_message((LPCSTR)0x0);
      uVar4 = g_pix_pak_file_count;
    }
    g_pix_pak_file_count = uVar4;
    puVar2 = (undefined4 *)find_next_resource_file_record_by_pattern(s___pix_004f8b8c,&local_20);
  }
  g_pix_pak_file_table =
       (LPVOID)xrealloc_global_heap(g_pix_pak_file_table,g_pix_pak_file_count * 0x18);
  if (g_pix_pak_file_table == (LPVOID)0x0) {
    fatal_out_of_memory_message((LPCSTR)0x0);
  }
  g_indexed_resource_record_count = 0;
  local_2c = 0;
  if (g_pix_pak_file_count != 0) {
    iVar5 = 0;
    do {
      puVar2 = (undefined4 *)((int)g_pix_pak_file_table + iVar5);
      local_10 = *puVar2;
      local_c = puVar2[1];
      local_8 = puVar2[2];
      local_4 = puVar2[3];
      pcVar3 = strchr((char *)&local_10,0x2e);
      *(undefined4 *)pcVar3 = s__pix_004f8b84._0_4_;
      pcVar3[4] = s__pix_004f8b84[4];
      pcVar3 = (char *)registered_resource_payload_size_context_helper((char *)&local_10,&local_18);
      if ((pcVar3 == (char *)0x0) || (pcVar6 = strchr(pcVar3,10), pcVar6 == (char *)0x0)) {
LAB_0047085c:
        report_error();
      }
      else {
        *pcVar6 = '\0';
        iVar7 = sscanf(pcVar3,s__d_004f8b80,&local_24);
        if (iVar7 != 1) goto LAB_0047085c;
        g_indexed_resource_record_count = g_indexed_resource_record_count + local_24;
        registered_resource_lookup_context_helper(pcVar3);
      }
      local_2c = local_2c + 1;
      iVar5 = iVar5 + 0x18;
    } while (local_2c < g_pix_pak_file_count);
  }
  g_indexed_resource_records = xcalloc_global_heap(g_indexed_resource_record_count,0x1c);
  if (g_indexed_resource_records == 0) {
    fatal_out_of_memory_message((LPCSTR)0x0);
  }
  g_indexed_resource_record_count = 0;
  local_2c = 0;
  if (g_pix_pak_file_count != 0) {
    local_28 = 0;
    do {
      puVar2 = (undefined4 *)((int)g_pix_pak_file_table + local_28);
      local_10 = *puVar2;
      local_c = puVar2[1];
      local_8 = puVar2[2];
      local_4 = puVar2[3];
      pcVar3 = strchr((char *)&local_10,0x2e);
      *(undefined4 *)pcVar3 = s__pix_004f8b84._0_4_;
      pcVar3[4] = s__pix_004f8b84[4];
      pcVar3 = (char *)registered_resource_payload_size_context_helper((char *)&local_10,&local_18);
      local_14 = pcVar3;
      if (pcVar3 != (char *)0x0) {
        pcVar6 = strchr(pcVar3,10);
        if (pcVar6 != (char *)0x0) {
          *pcVar6 = '\0';
          iVar5 = sscanf(pcVar3,s__d_004f8b80,&local_24);
          if (iVar5 == 1) {
            local_1c = 0;
            if (local_24 != 0) {
              do {
                pcVar3 = pcVar6 + 1;
                pcVar6 = strchr(pcVar3,10);
                if (pcVar6 == (char *)0x0) {
LAB_00470a1a:
                  report_error();
                }
                else {
                  *pcVar6 = '\0';
                  puVar2 = (undefined4 *)
                           (g_indexed_resource_records + g_indexed_resource_record_count * 0x1c);
                  for (iVar5 = 7; iVar5 != 0; iVar5 = iVar5 + -1) {
                    *puVar2 = 0;
                    puVar2 = puVar2 + 1;
                  }
                  iVar5 = g_indexed_resource_records + g_indexed_resource_record_count * 0x1c;
                  iVar5 = sscanf(pcVar3,s__s__d__d_004f8b4c,iVar5,iVar5 + 0x14,iVar5 + 0x18);
                  if (iVar5 != 3) goto LAB_00470a1a;
                  _strlwr((char *)(g_indexed_resource_records +
                                  g_indexed_resource_record_count * 0x1c));
                  *(uint *)(g_indexed_resource_records + 0x10 +
                           g_indexed_resource_record_count * 0x1c) = local_2c;
                  g_indexed_resource_record_count = g_indexed_resource_record_count + 1;
                }
                local_1c = local_1c + 1;
                pcVar3 = local_14;
              } while (local_1c < local_24);
            }
            registered_resource_lookup_context_helper(pcVar3);
            goto LAB_00470a73;
          }
        }
        report_error();
      }
LAB_00470a73:
      local_2c = local_2c + 1;
      local_28 = local_28 + 0x18;
    } while (local_2c < g_pix_pak_file_count);
  }
  qsort((void *)g_indexed_resource_records,g_indexed_resource_record_count,0x1c,
        (_PtFuncCompare *)&compare_resource_record_16byte_key);
  return;
}


