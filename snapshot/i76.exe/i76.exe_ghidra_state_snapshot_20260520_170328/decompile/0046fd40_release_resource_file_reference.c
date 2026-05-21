/*
 * Program: i76.exe
 * Function: release_resource_file_reference
 * Entry: 0046fd40
 * Signature: undefined __cdecl release_resource_file_reference(char * param_1)
 */


/* [cgpt i76.exe texture/resource-cache rename v10; confidence=high] Canonicalizes/lowercases a
   resource name and releases either indexed-resource payload or loaded-resource cache record
   reference.
   
   I76 rename v43: release_resource_file_reference
   Releases loaded-resource file reference after descriptor parse. */

void __cdecl release_resource_file_reference(char *param_1)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  char local_10;
  char local_f [15];
  
  strncpy(&local_10,param_1,0x10);
  _strlwr(&local_10);
  iVar2 = release_indexed_resource_record_payload(&local_10);
  if (iVar2 == 0) {
    if ((&stack0x00000000 == (undefined1 *)0x10) || (local_10 == '\0')) {
      pcVar4 = (char *)0x0;
    }
    else {
      pcVar4 = &local_10;
      uVar3 = 0;
      do {
        uVar3 = uVar3 * 2 ^ (int)local_10;
        local_10 = pcVar4[1];
        pcVar4 = pcVar4 + 1;
      } while (local_10 != '\0');
      if ((int)uVar3 < 0) {
        uVar3 = -uVar3;
      }
      pcVar4 = *(char **)(g_loaded_resource_cache_hash + ((int)uVar3 % 0x7d9) * 4);
      if (pcVar4 == (char *)0x0) {
        return;
      }
      do {
        iVar2 = _stricmp(pcVar4,&local_10);
        if (iVar2 == 0) break;
        pcVar4 = *(char **)(pcVar4 + 0x18);
      } while (pcVar4 != (char *)0x0);
    }
    if (((pcVar4 != (char *)0x0) && (*(short *)(pcVar4 + 0x14) != 0)) &&
       (sVar1 = *(short *)(pcVar4 + 0x14) + -1, *(short *)(pcVar4 + 0x14) = sVar1, sVar1 == 0)) {
      if (g_loaded_resource_purge_list_head != 0) {
        *(char **)(g_loaded_resource_purge_list_head + 0x1c) = pcVar4;
      }
      *(int *)(pcVar4 + 0x20) = g_loaded_resource_purge_list_head;
      g_loaded_resource_purge_list_head = (int)pcVar4;
      pcVar4[0x1c] = '\0';
      pcVar4[0x1d] = '\0';
      pcVar4[0x1e] = '\0';
      pcVar4[0x1f] = '\0';
      if (g_loaded_resource_purge_list_tail == 0) {
        g_loaded_resource_purge_list_tail = (int)pcVar4;
      }
    }
  }
  return;
}


