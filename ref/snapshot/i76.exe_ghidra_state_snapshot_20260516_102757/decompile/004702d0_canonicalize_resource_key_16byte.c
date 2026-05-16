/*
 * Program: i76.exe
 * Function: canonicalize_resource_key_16byte
 * Entry: 004702d0
 * Signature: undefined __cdecl canonicalize_resource_key_16byte(char * param_1)
 */


/* [cgpt i76.exe resource/archive rename v11; confidence=medium-high] Canonicalizes a resource key
   before it is inserted into or queried from the registered resource table. */

void __cdecl canonicalize_resource_key_16byte(char *param_1)

{
  uint uVar1;
  int iVar2;
  char cVar3;
  char *pcVar4;
  
  if ((param_1 == (char *)0x0) || (cVar3 = *param_1, cVar3 == '\0')) {
    pcVar4 = (char *)0x0;
  }
  else {
    uVar1 = 0;
    pcVar4 = param_1;
    do {
      uVar1 = uVar1 * 2 ^ (int)cVar3;
      cVar3 = pcVar4[1];
      pcVar4 = pcVar4 + 1;
    } while (cVar3 != '\0');
    if ((int)uVar1 < 0) {
      uVar1 = -uVar1;
    }
    pcVar4 = *(char **)(g_loaded_resource_cache_hash + ((int)uVar1 % 0x7d9) * 4);
    if (pcVar4 == (char *)0x0) {
      return;
    }
    do {
      iVar2 = _stricmp(pcVar4,param_1);
      if (iVar2 == 0) break;
      pcVar4 = *(char **)(pcVar4 + 0x18);
    } while (pcVar4 != (char *)0x0);
  }
  if (pcVar4 != (char *)0x0) {
    evict_loaded_resource_cache_record(pcVar4);
  }
  return;
}


