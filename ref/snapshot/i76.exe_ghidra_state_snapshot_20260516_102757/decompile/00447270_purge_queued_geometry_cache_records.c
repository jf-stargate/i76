/*
 * Program: i76.exe
 * Function: purge_queued_geometry_cache_records
 * Entry: 00447270
 * Signature: undefined __stdcall purge_queued_geometry_cache_records(void)
 */


/* cgpt rename v2: Unlinks and frees queued geometry cache records and releases geometry heap
   memory. */

void purge_queued_geometry_cache_records(void)

{
  uint *puVar1;
  LPCVOID lpMem;
  int iVar2;
  uint *puVar3;
  SIZE_T SVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  undefined8 uVar8;
  
  while (g_geometry_purge_list_head != (uint *)0x0) {
    uVar5 = (g_geometry_purge_list_head[3] * 0x6cd + 0xaab) % 0x7ed;
    puVar3 = &g_geometry_cache_by_handle + uVar5;
    for (puVar1 = (uint *)(&g_geometry_cache_by_handle)[uVar5]; puVar1 != g_geometry_purge_list_head
        ; puVar1 = (uint *)puVar1[4]) {
      puVar3 = puVar1 + 4;
    }
    *puVar3 = puVar1[4];
    uVar5 = *puVar1;
    uVar8 = __allshr(0x20,puVar1[1]);
    uVar5 = ((((uint)uVar8 ^ uVar5) & 0xdfdfdfdf) * 0x6cd + 0xaab) % 0x7ed;
    puVar3 = &g_geometry_cache_by_8char_name + uVar5;
    for (puVar1 = (uint *)(&g_geometry_cache_by_8char_name)[uVar5];
        puVar1 != g_geometry_purge_list_head; puVar1 = (uint *)puVar1[5]) {
      puVar3 = puVar1 + 5;
    }
    *puVar3 = puVar1[5];
    if (g_geometry_purge_list_head[6] == 0) {
      g_geometry_purge_list_tail = 0;
    }
    else {
      *(undefined4 *)(g_geometry_purge_list_head[6] + 0x1c) = 0;
    }
    g_geometry_purge_list_head = (uint *)g_geometry_purge_list_head[6];
    lpMem = (LPCVOID)puVar1[3];
    SVar4 = HeapSize(g_geometry_heap,0,lpMem);
    DAT_00608e5c = DAT_00608e5c + SVar4;
    HeapFree(g_geometry_heap,0,lpMem);
    HeapFree(g_geometry_cache_entry_heap,0,puVar1);
  }
  piVar6 = &g_geometry_cache_by_handle;
  iVar7 = 0;
  g_geometry_purge_list_head = (uint *)iVar7;
  do {
    for (iVar2 = *piVar6; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x10)) {
      SVar4 = HeapSize(g_geometry_heap,0,*(LPCVOID *)(iVar2 + 0xc));
      if (0 < (int)SVar4) {
        uVar5 = SVar4 + 0xfff >> 0xc;
        do {
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
      iVar7 = (int)g_geometry_purge_list_head;
    }
    piVar6 = piVar6 + 1;
  } while ((int)piVar6 < 0x52fb5c);
  for (; iVar7 != 0; iVar7 = *(int *)(iVar7 + 0x18)) {
    SVar4 = HeapSize(g_geometry_heap,0,*(LPCVOID *)(iVar7 + 0xc));
    if (0 < (int)SVar4) {
      uVar5 = SVar4 + 0xfff >> 0xc;
      do {
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
    }
  }
  return;
}


