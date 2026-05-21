/*
 * Program: i76.exe
 * Function: read_zfsf_record_payload
 * Entry: 004b9bd0
 * Signature: uint * __cdecl read_zfsf_record_payload(undefined4 * param_1, char * param_2, SIZE_T * param_3, uint * param_4, int param_5)
 */


/* [cgpt i76.exe ZFSF format renames v13; confidence=high] Core ZFSF record read path: seeks to
   record file_offset, reads record stored_size bytes from disk, optionally LZO-decompresses based
   on flags byte, then applies archive XOR key dword-wise if nonzero.
   
   I76 rename v43: read_zfsf_record_payload
   Reads raw ZFSF record payload. */

uint * __cdecl
read_zfsf_record_payload
          (undefined4 *param_1,char *param_2,SIZE_T *param_3,uint *param_4,int param_5)

{
  void *this;
  uint uVar1;
  void *pvVar2;
  size_t sVar3;
  int iVar4;
  uint *puVar5;
  SIZE_T dwBytes;
  bool bVar6;
  uint *local_30;
  char local_24 [36];
  
                    /* I76 semantic baseline: read_zfsf_record_payload
                       Reads ZFSF record payload. */
  puVar5 = (uint *)0x0;
  strncpy(local_24,param_2,0x10);
  pvVar2 = bsearch(local_24,(void *)param_1[10],param_1[6],0x24,compare_zfsf_record_name_cstring);
  this = *(void **)((int)pvVar2 + 0x18);
  bVar6 = (*(uint *)((int)pvVar2 + 0x20) & 6) != 0;
  if ((bVar6) || (param_4 == (uint *)0x0)) {
    puVar5 = HeapAlloc(g_resource_key_table_heap_handle,0,(SIZE_T)this);
    local_30 = puVar5;
    if (puVar5 == (uint *)0x0) {
      fatal_out_of_memory_message((LPCSTR)0x0);
    }
  }
  else {
    if (param_5 < (int)this) {
      return (uint *)0x0;
    }
    local_30 = param_4;
  }
  fseek((FILE *)*param_1,*(long *)((int)pvVar2 + 0x10),0);
  sVar3 = fread(local_30,(size_t)this,1,(FILE *)*param_1);
  if (sVar3 == 0) {
    sprintf(&g_resource_key_registration_error_buffer,s_Could_not_read_record__s_from_fi_00500f2c,
            param_2,param_1 + 1);
    if (puVar5 == (uint *)0x0) {
      return (uint *)0x0;
    }
    HeapFree(g_resource_key_table_heap_handle,0,puVar5);
    return (uint *)0x0;
  }
  if (bVar6) {
    dwBytes = *(int *)((int)pvVar2 + 0x20) >> 8;
    if (param_4 == (uint *)0x0) {
      param_4 = HeapAlloc(g_resource_key_table_heap_handle,0,dwBytes);
      if (param_4 == (uint *)0x0) {
        fatal_out_of_memory_message((LPCSTR)0x0);
      }
    }
    else if (param_5 < (int)dwBytes) {
      HeapFree(g_resource_key_table_heap_handle,0,puVar5);
      return (uint *)0x0;
    }
    iVar4 = zfsf_decompress_record_payload_by_lzo_mode
                      (this,(byte *)local_30,(int)this,(byte)*(undefined4 *)((int)pvVar2 + 0x20),
                       param_4);
    HeapFree(g_resource_key_table_heap_handle,0,puVar5);
    if (iVar4 == 0) {
      return (uint *)0x0;
    }
    *param_3 = dwBytes;
    local_30 = param_4;
  }
  else {
    *param_3 = (SIZE_T)this;
  }
  uVar1 = param_1[7];
  if ((uVar1 != 0) && (iVar4 = (int)*param_3 >> 2, puVar5 = local_30, 0 < iVar4)) {
    do {
      iVar4 = iVar4 + -1;
      *puVar5 = *puVar5 ^ uVar1;
      puVar5 = puVar5 + 1;
    } while (iVar4 != 0);
  }
  return local_30;
}


