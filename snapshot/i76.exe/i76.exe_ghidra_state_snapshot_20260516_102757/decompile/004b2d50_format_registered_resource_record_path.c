/*
 * Program: i76.exe
 * Function: format_registered_resource_record_path
 * Entry: 004b2d50
 * Signature: undefined4 * __cdecl format_registered_resource_record_path(undefined4 * param_1)
 */


/* [cgpt i76.exe resource/archive rename v11; confidence=medium-high] Formats/resolves the
   registered resource path for a 16-byte resource key. */

undefined4 * __cdecl format_registered_resource_record_path(undefined4 *param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  
  pcVar2 = lookup_registered_resource_record_by_key(param_1);
  if (pcVar2 == (char *)0x0) {
    return (undefined4 *)0x0;
  }
  if (*(int *)(pcVar2 + 0x100) == 0) {
    if (DAT_00669ee4 != 0) {
      cVar1 = get_active_cdrom_drive_letter();
      sprintf((char *)&DAT_005dabc8,s__c___s_004faeb0,(int)cVar1,pcVar2);
      return &DAT_005dabc8;
    }
    sprintf((char *)&DAT_005dabc8,s__s__s_004fffe0,
            &g_resource_directory_roots + *(int *)(pcVar2 + 0x104) * 0x300,pcVar2);
    return &DAT_005dabc8;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = pcVar2;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar2 = pcVar5 + -uVar3;
  pcVar5 = (char *)&DAT_005dabc8;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar5 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    pcVar5 = pcVar5 + 1;
  }
  return &DAT_005dabc8;
}


