/*
 * Program: i76.exe
 * Function: get_loaded_resource_file_size
 * Entry: 0046fee0
 * Signature: int __cdecl get_loaded_resource_file_size(char * param_1)
 */


/* [cgpt i76.exe vehicle/resource rename v4; confidence=high] Returns loaded resource file size for
   the resource/cache helper object. */

int __cdecl get_loaded_resource_file_size(char *param_1)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  char local_10;
  char local_f [15];
  
  strncpy(&local_10,param_1,0x10);
  _strlwr(&local_10);
  if ((&stack0x00000000 == (undefined1 *)0x10) || (local_10 == '\0')) {
    return 0;
  }
  iVar1 = get_indexed_resource_record_size(&local_10);
  if (iVar1 != -1) {
    return iVar1;
  }
  if (local_10 == '\0') {
    pcVar3 = (char *)0x0;
  }
  else {
    uVar2 = 0;
    pcVar3 = &local_10;
    do {
      uVar2 = uVar2 * 2 ^ (int)local_10;
      local_10 = pcVar3[1];
      pcVar3 = pcVar3 + 1;
    } while (local_10 != '\0');
    if ((int)uVar2 < 0) {
      uVar2 = -uVar2;
    }
    pcVar3 = *(char **)(g_loaded_resource_cache_hash + ((int)uVar2 % 0x7d9) * 4);
    if (pcVar3 == (char *)0x0) goto LAB_0046ff96;
    do {
      iVar1 = _stricmp(pcVar3,&local_10);
      if (iVar1 == 0) break;
      pcVar3 = *(char **)(pcVar3 + 0x18);
    } while (pcVar3 != (char *)0x0);
  }
  if (pcVar3 != (char *)0x0) {
    return *(int *)(pcVar3 + 0x10);
  }
LAB_0046ff96:
  iVar1 = get_registered_resource_payload_size(&local_10);
  return iVar1;
}


