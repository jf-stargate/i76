/*
 * Program: i76.exe
 * Function: load_resource_stream_into_loaded_cache
 * Entry: 00470070
 * Signature: uint * __cdecl load_resource_stream_into_loaded_cache(char * param_1)
 */


/* [cgpt i76.exe texture/image/resource renames v21; confidence=high] Loads a resource stream into
   the loaded resource cache; used as the backing stream for .pak payload access.
   
   I76 rename v43: load_resource_stream_into_loaded_cache
   Loads resource payload into cache using registered-resource payload helpers. */

uint * __cdecl load_resource_stream_into_loaded_cache(char *param_1)

{
  char *pcVar1;
  char *pcVar2;
  char *_Str2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  char *_Dest;
  undefined3 extraout_var;
  char cVar6;
  char *pcVar7;
  
  _Str2 = param_1;
  if ((param_1 == (char *)0x0) || (cVar6 = *param_1, cVar6 == '\0')) {
    pcVar7 = (char *)0x0;
  }
  else {
    uVar4 = 0;
    pcVar7 = param_1;
    do {
      uVar4 = uVar4 * 2 ^ (int)cVar6;
      cVar6 = pcVar7[1];
      pcVar7 = pcVar7 + 1;
    } while (cVar6 != '\0');
    if ((int)uVar4 < 0) {
      uVar4 = -uVar4;
    }
    pcVar7 = *(char **)(g_loaded_resource_cache_hash + ((int)uVar4 % 0x7d9) * 4);
    if (pcVar7 == (char *)0x0) goto LAB_00470124;
    do {
      iVar5 = _stricmp(pcVar7,_Str2);
      if (iVar5 == 0) break;
      pcVar7 = *(char **)(pcVar7 + 0x18);
    } while (pcVar7 != (char *)0x0);
  }
  if (pcVar7 != (char *)0x0) {
    if (*(short *)(pcVar7 + 0x14) == 0) {
      if (*(int *)(pcVar7 + 0x1c) != 0) {
        *(undefined4 *)(*(int *)(pcVar7 + 0x1c) + 0x20) = *(undefined4 *)(pcVar7 + 0x20);
      }
      if (*(int *)(pcVar7 + 0x20) != 0) {
        *(undefined4 *)(*(int *)(pcVar7 + 0x20) + 0x1c) = *(undefined4 *)(pcVar7 + 0x1c);
      }
      if (pcVar7 == g_loaded_resource_purge_list_tail) {
        g_loaded_resource_purge_list_tail = *(char **)(pcVar7 + 0x1c);
      }
      if (pcVar7 == g_loaded_resource_purge_list_head) {
        g_loaded_resource_purge_list_head = *(char **)(pcVar7 + 0x20);
      }
      pcVar7[0x1c] = '\0';
      pcVar7[0x1d] = '\0';
      pcVar7[0x1e] = '\0';
      pcVar7[0x1f] = '\0';
      pcVar7[0x20] = '\0';
      pcVar7[0x21] = '\0';
      pcVar7[0x22] = '\0';
      pcVar7[0x23] = '\0';
    }
    *(short *)(pcVar7 + 0x14) = *(short *)(pcVar7 + 0x14) + 1;
    return (uint *)(pcVar7 + 0x24);
  }
LAB_00470124:
  if (g_loaded_resource_cache_low_watermark <= g_loaded_resource_cache_used_bytes) {
    if (g_loaded_resource_purge_list_tail == (char *)0x0) {
      report_error();
    }
    else {
      evict_loaded_resource_cache_record(g_loaded_resource_purge_list_tail);
    }
  }
  pcVar7 = (char *)get_registered_resource_payload_size(_Str2);
  if ((int)pcVar7 < 1) {
    return (uint *)0x0;
  }
  param_1 = pcVar7;
  strstr(_Str2,s__pak_004f8afc);
  pcVar7 = pcVar7 + 0x24;
  if ((char *)0x7fff7 < pcVar7) {
    report_error();
  }
  _Dest = HeapAlloc(g_loaded_resource_heap,0,(SIZE_T)pcVar7);
  pcVar2 = param_1;
  while (param_1 = pcVar2, _Dest == (char *)0x0) {
    if (g_loaded_resource_purge_list_tail == (char *)0x0) {
      report_error();
      return (uint *)0x0;
    }
    evict_loaded_resource_cache_record(g_loaded_resource_purge_list_tail);
    _Dest = HeapAlloc(g_loaded_resource_heap,0,(SIZE_T)pcVar7);
    pcVar2 = param_1;
  }
  bVar3 = load_registered_resource_payload_bool
                    (_Str2,(SIZE_T *)&param_1,(uint *)(_Dest + 0x24),(int)pcVar2);
  if (CONCAT31(extraout_var,bVar3) == 0) {
    HeapFree(g_loaded_resource_heap,0,_Dest);
    return (uint *)0x0;
  }
  if (g_resource_debug_log_file != 0) {
    debug_fprintf_wrapper('p');
    fprintf((FILE *)g_resource_debug_log_file,s__s__d_004f2588,_Str2,pcVar2);
  }
  uVar4 = 0;
  cVar6 = *_Str2;
  pcVar7 = _Str2;
  while (cVar6 != '\0') {
    uVar4 = uVar4 * 2 ^ (int)cVar6;
    pcVar1 = pcVar7 + 1;
    pcVar7 = pcVar7 + 1;
    cVar6 = *pcVar1;
  }
  if ((int)uVar4 < 0) {
    uVar4 = -uVar4;
  }
  iVar5 = ((int)uVar4 % 0x7d9) * 4;
  *(undefined4 *)(_Dest + 0x18) = *(undefined4 *)(g_loaded_resource_cache_hash + iVar5);
  *(char **)(g_loaded_resource_cache_hash + iVar5) = _Dest;
  _Dest[0x14] = '\x01';
  _Dest[0x15] = '\0';
  strncpy(_Dest,_Str2,0xf);
  *(char **)(_Dest + 0x10) = pcVar2;
  _Dest[0x1c] = '\0';
  _Dest[0x1d] = '\0';
  _Dest[0x1e] = '\0';
  _Dest[0x1f] = '\0';
  _Dest[0x20] = '\0';
  _Dest[0x21] = '\0';
  _Dest[0x22] = '\0';
  _Dest[0x23] = '\0';
  g_loaded_resource_cache_budget_bytes =
       g_loaded_resource_cache_budget_bytes + (-0x24 - (int)pcVar2);
  g_loaded_resource_cache_used_bytes = g_loaded_resource_cache_used_bytes + 1;
  return (uint *)(_Dest + 0x24);
}


