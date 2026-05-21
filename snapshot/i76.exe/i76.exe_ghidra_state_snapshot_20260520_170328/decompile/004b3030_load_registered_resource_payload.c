/*
 * Program: i76.exe
 * Function: load_registered_resource_payload
 * Entry: 004b3030
 * Signature: uint * __cdecl load_registered_resource_payload(char * param_1, SIZE_T * param_2, uint * param_3, int param_4)
 */


/* [cgpt i76.exe ZFSF format renames v13; confidence=high] Retail resource-stack caller that opens
   ZFSF through open_zfsf_archive_file with create/update flag 0, confirming read-only rb path for
   normal payload loads.
   
   I76 rename v43: load_registered_resource_payload
   Loads registered resource payload via ZFS/loose/indexed path. */

uint * __cdecl
load_registered_resource_payload(char *param_1,SIZE_T *param_2,uint *param_3,int param_4)

{
  char cVar1;
  bool bVar2;
  char *pcVar3;
  char *pcVar4;
  undefined3 extraout_var;
  uint *puVar5;
  FILE *_File;
  SIZE_T dwBytes;
  size_t sVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  char local_22c [256];
  char local_12c [300];
  
  pcVar3 = lookup_registered_resource_record_by_key((undefined4 *)param_1);
  pcVar4 = (char *)0x0;
  if (pcVar3 != (char *)0x0) {
    if (*(int *)(pcVar3 + 0x100) == 0) {
      if (DAT_00669ee4 == 0) {
        sprintf(local_22c,s__s__s_004fffe0,
                &g_resource_directory_roots + *(int *)(pcVar3 + 0x104) * 0x300,pcVar3);
      }
      else {
        pcVar4 = pcVar3;
        cVar1 = get_active_cdrom_drive_letter();
        sprintf(local_22c,s__c___s_004faeb0,(int)cVar1,pcVar4);
      }
    }
    else {
      uVar7 = 0xffffffff;
      pcVar4 = pcVar3;
      do {
        pcVar9 = pcVar4;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar9 = pcVar4 + 1;
        cVar1 = *pcVar4;
        pcVar4 = pcVar9;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      pcVar4 = pcVar9 + -uVar7;
      pcVar9 = local_22c;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar9 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar9 = pcVar9 + 1;
      }
    }
    pcVar4 = local_22c;
  }
  if (pcVar4 == (char *)0x0) {
    return (uint *)0x0;
  }
  pcVar4 = strstr(local_22c,s__zfs_0050001c);
  if (pcVar4 == (char *)0x0) {
    sprintf(local_12c,s__s__s_004fffe0,local_22c,param_1);
    _File = fopen(local_12c,&DAT_004c2098);
    if (_File == (FILE *)0x0) {
      sprintf(&g_resource_key_registration_error_buffer,s_Couldn_t_open_file___s__004fffa8,local_12c
             );
      return (uint *)0x0;
    }
    setvbuf(_File,(char *)0x0,4,0);
    fseek(_File,0,2);
    dwBytes = ftell(_File);
    *param_2 = dwBytes;
    if (param_3 == (uint *)0x0) {
      puVar5 = HeapAlloc(g_resource_key_table_heap_handle,0,dwBytes);
      if (puVar5 == (uint *)0x0) {
        fatal_out_of_memory_message((LPCSTR)0x0);
      }
    }
    else {
      puVar5 = param_3;
      if (param_4 < (int)dwBytes) {
        fclose(_File);
        return (uint *)0x0;
      }
    }
    fseek(_File,0,0);
    sVar6 = fread(puVar5,*param_2,1,_File);
    if (sVar6 == 0) {
      sprintf(&g_resource_key_registration_error_buffer,s_Could_not_read_file___s__00500000,
              local_12c);
      if (param_3 == (uint *)0x0) {
        HeapFree(g_resource_key_table_heap_handle,0,puVar5);
      }
      fclose(_File);
      return (uint *)0x0;
    }
    fclose(_File);
    return puVar5;
  }
  if (*(int *)(pcVar3 + 0x108) == 0) {
    pcVar4 = open_zfsf_archive_file(local_22c,0);
    *(char **)(pcVar3 + 0x108) = pcVar4;
    if (pcVar4 == (char *)0x0) {
      return (uint *)0x0;
    }
  }
  if (param_3 != (uint *)0x0) {
    bVar2 = read_zfsf_record_to_buffer_bool
                      (*(undefined4 **)(pcVar3 + 0x108),param_1,param_2,param_3,param_4);
    return (uint *)(-(uint)(CONCAT31(extraout_var,bVar2) != 0) & (uint)param_3);
  }
  puVar5 = (uint *)read_zfsf_record_allocated_payload
                             (*(undefined4 **)(pcVar3 + 0x108),param_1,param_2);
  return puVar5;
}


