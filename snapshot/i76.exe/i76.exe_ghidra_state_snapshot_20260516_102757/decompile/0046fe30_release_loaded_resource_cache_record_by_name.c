/*
 * Program: i76.exe
 * Function: release_loaded_resource_cache_record_by_name
 * Entry: 0046fe30
 * Signature: undefined __cdecl release_loaded_resource_cache_record_by_name(char * param_1)
 */


/* [cgpt i76.exe texture/resource-cache rename v10; confidence=high] Looks up a loaded-resource
   cache record by name, decrements refcount, and moves it to the purge list when refcount reaches
   zero. */

void __cdecl release_loaded_resource_cache_record_by_name(char *param_1)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  char cVar4;
  char *pcVar5;
  
  if ((param_1 == (char *)0x0) || (cVar4 = *param_1, cVar4 == '\0')) {
    pcVar5 = (char *)0x0;
  }
  else {
    uVar2 = 0;
    pcVar5 = param_1;
    do {
      uVar2 = uVar2 * 2 ^ (int)cVar4;
      cVar4 = pcVar5[1];
      pcVar5 = pcVar5 + 1;
    } while (cVar4 != '\0');
    if ((int)uVar2 < 0) {
      uVar2 = -uVar2;
    }
    pcVar5 = *(char **)(g_loaded_resource_cache_hash + ((int)uVar2 % 0x7d9) * 4);
    if (pcVar5 == (char *)0x0) {
      return;
    }
    do {
      iVar3 = _stricmp(pcVar5,param_1);
      if (iVar3 == 0) break;
      pcVar5 = *(char **)(pcVar5 + 0x18);
    } while (pcVar5 != (char *)0x0);
  }
  if (((pcVar5 != (char *)0x0) && (*(short *)(pcVar5 + 0x14) != 0)) &&
     (sVar1 = *(short *)(pcVar5 + 0x14) + -1, *(short *)(pcVar5 + 0x14) = sVar1, sVar1 == 0)) {
    if (g_loaded_resource_purge_list_head != 0) {
      *(char **)(g_loaded_resource_purge_list_head + 0x1c) = pcVar5;
    }
    *(int *)(pcVar5 + 0x20) = g_loaded_resource_purge_list_head;
    g_loaded_resource_purge_list_head = (int)pcVar5;
    pcVar5[0x1c] = '\0';
    pcVar5[0x1d] = '\0';
    pcVar5[0x1e] = '\0';
    pcVar5[0x1f] = '\0';
    if (g_loaded_resource_purge_list_tail == 0) {
      g_loaded_resource_purge_list_tail = (int)pcVar5;
    }
  }
  return;
}


