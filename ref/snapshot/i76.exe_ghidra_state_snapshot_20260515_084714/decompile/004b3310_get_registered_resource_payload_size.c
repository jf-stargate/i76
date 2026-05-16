/*
 * Program: i76.exe
 * Function: get_registered_resource_payload_size
 * Entry: 004b3310
 * Signature: int __cdecl get_registered_resource_payload_size(char * param_1)
 */


/* [cgpt i76.exe ZFSF format renames v13; confidence=high] Retail resource-stack size caller that
   opens ZFSF through open_zfsf_archive_file with create/update flag 0, confirming read-only rb path
   for normal size lookups. */

int __cdecl get_registered_resource_payload_size(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  FILE *_File;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char local_22c [256];
  char local_12c [300];
  
  pcVar2 = lookup_registered_resource_record_by_key((undefined4 *)param_1);
  pcVar3 = (char *)0x0;
  if (pcVar2 != (char *)0x0) {
    if (*(int *)(pcVar2 + 0x100) == 0) {
      if (DAT_00669ee4 == 0) {
        sprintf(local_22c,s__s__s_004fffe0,
                &g_resource_directory_roots + *(int *)(pcVar2 + 0x104) * 0x300,pcVar2);
      }
      else {
        pcVar3 = pcVar2;
        cVar1 = get_active_cdrom_drive_letter();
        sprintf(local_22c,s__c___s_004faeb0,(int)cVar1,pcVar3);
      }
    }
    else {
      uVar5 = 0xffffffff;
      pcVar3 = pcVar2;
      do {
        pcVar7 = pcVar3;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar7 = pcVar3 + 1;
        cVar1 = *pcVar3;
        pcVar3 = pcVar7;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      pcVar3 = pcVar7 + -uVar5;
      pcVar7 = local_22c;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
        pcVar3 = pcVar3 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar7 = *pcVar3;
        pcVar3 = pcVar3 + 1;
        pcVar7 = pcVar7 + 1;
      }
    }
    pcVar3 = local_22c;
  }
  if (pcVar3 == (char *)0x0) {
    return 0;
  }
  pcVar3 = strstr(local_22c,s__zfs_0050001c);
  if (pcVar3 == (char *)0x0) {
    sprintf(local_12c,s__s__s_004fffe0,local_22c,param_1);
    _File = fopen(local_12c,&DAT_004c2098);
    if (_File == (FILE *)0x0) {
      sprintf(&g_resource_error_message,s_Couldn_t_open_file___s__004fffa8,local_12c);
      return 0;
    }
    setvbuf(_File,(char *)0x0,4,0);
    fseek(_File,0,2);
    iVar4 = ftell(_File);
    fclose(_File);
  }
  else {
    if (*(int *)(pcVar2 + 0x108) == 0) {
      pcVar3 = open_zfsf_archive_file(local_22c,0);
      *(char **)(pcVar2 + 0x108) = pcVar3;
      if (pcVar3 == (char *)0x0) {
        return 0;
      }
    }
    iVar4 = lookup_zfsf_record_logical_size(*(int *)(pcVar2 + 0x108),param_1);
    if (iVar4 == -1) {
      sprintf(&g_resource_error_message,s_Could_not_find_record___s__in_fi_00500024,param_1,
              *(int *)(pcVar2 + 0x108) + 4);
      return 0;
    }
  }
  return iVar4;
}


