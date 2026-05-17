/*
 * Program: i76.exe
 * Function: evict_loaded_resource_cache_record
 * Entry: 0046fbe0
 * Signature: undefined __cdecl evict_loaded_resource_cache_record(char * param_1)
 */


/* [cgpt i76.exe texture/resource-cache rename v10; confidence=high] Unlinks a loaded-resource cache
   record from purge/hash lists, frees it, and rebuilds purge list if needed. */

void __cdecl evict_loaded_resource_cache_record(char *param_1)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  
  if (param_1 != (char *)0x0) {
    if (*(short *)(param_1 + 0x14) != 0) {
      param_1[0x14] = '\0';
      param_1[0x15] = '\0';
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x20) = *(undefined4 *)(param_1 + 0x20);
    }
    if (*(int *)(param_1 + 0x20) != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x1c) = *(undefined4 *)(param_1 + 0x1c);
    }
    if (param_1 == g_loaded_resource_purge_list_tail) {
      g_loaded_resource_purge_list_tail = *(char **)(param_1 + 0x1c);
    }
    if (param_1 == g_loaded_resource_purge_list_head) {
      g_loaded_resource_purge_list_head = *(char **)(param_1 + 0x20);
    }
    param_1[0x1c] = '\0';
    param_1[0x1d] = '\0';
    param_1[0x1e] = '\0';
    param_1[0x1f] = '\0';
    param_1[0x20] = '\0';
    param_1[0x21] = '\0';
    param_1[0x22] = '\0';
    param_1[0x23] = '\0';
    uVar3 = 0;
    cVar2 = *param_1;
    pcVar4 = param_1;
    while (cVar2 != '\0') {
      uVar3 = uVar3 * 2 ^ (int)cVar2;
      pcVar1 = pcVar4 + 1;
      pcVar4 = pcVar4 + 1;
      cVar2 = *pcVar1;
    }
    if ((int)uVar3 < 0) {
      uVar3 = -uVar3;
    }
    pcVar4 = *(char **)(g_loaded_resource_cache_hash + ((int)uVar3 % 0x7d9) * 4);
    if (param_1 == pcVar4) {
      *(undefined4 *)(g_loaded_resource_cache_hash + ((int)uVar3 % 0x7d9) * 4) =
           *(undefined4 *)(param_1 + 0x18);
LAB_0046fc9e:
      g_loaded_resource_cache_budget_bytes =
           g_loaded_resource_cache_budget_bytes + 0x24 + *(int *)(param_1 + 0x10);
      HeapFree(g_loaded_resource_heap,0,param_1);
      g_loaded_resource_cache_used_bytes = g_loaded_resource_cache_used_bytes + -1;
      return;
    }
    if (pcVar4 != (char *)0x0) {
      do {
        pcVar1 = *(char **)(pcVar4 + 0x18);
        if ((pcVar1 == (char *)0x0) || (pcVar1 == param_1)) break;
        pcVar4 = pcVar1;
      } while (pcVar1 != (char *)0x0);
      if ((pcVar4 != (char *)0x0) && (*(int *)(pcVar4 + 0x18) != 0)) {
        *(undefined4 *)(pcVar4 + 0x18) = *(undefined4 *)(*(int *)(pcVar4 + 0x18) + 0x18);
        goto LAB_0046fc9e;
      }
    }
    if (param_1 == g_loaded_resource_purge_list_tail) {
      g_loaded_resource_purge_list_tail = (char *)0x0;
      g_loaded_resource_purge_list_head = (char *)0x0;
      iVar5 = 0;
      iVar6 = g_loaded_resource_cache_hash;
      do {
        pcVar4 = *(char **)(iVar6 + iVar5);
        for (; pcVar4 != (char *)0x0; pcVar4 = *(char **)(pcVar4 + 0x18)) {
          if (*(short *)(pcVar4 + 0x14) == 0) {
            pcVar4[0x14] = '\x01';
            pcVar4[0x15] = '\0';
            if (g_loaded_resource_purge_list_head != (char *)0x0) {
              *(char **)(g_loaded_resource_purge_list_head + 0x1c) = pcVar4;
            }
            *(char **)(pcVar4 + 0x20) = g_loaded_resource_purge_list_head;
            g_loaded_resource_purge_list_head = pcVar4;
            pcVar4[0x1c] = '\0';
            pcVar4[0x1d] = '\0';
            pcVar4[0x1e] = '\0';
            pcVar4[0x1f] = '\0';
            if (g_loaded_resource_purge_list_tail == (char *)0x0) {
              g_loaded_resource_purge_list_tail = pcVar4;
            }
          }
          iVar6 = g_loaded_resource_cache_hash;
        }
        iVar5 = iVar5 + 4;
      } while (iVar5 < 0x1f64);
    }
  }
  return;
}


