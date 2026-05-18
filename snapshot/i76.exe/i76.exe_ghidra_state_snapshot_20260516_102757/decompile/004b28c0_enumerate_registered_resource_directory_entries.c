/*
 * Program: i76.exe
 * Function: enumerate_registered_resource_directory_entries
 * Entry: 004b28c0
 * Signature: undefined4 __cdecl enumerate_registered_resource_directory_entries(int param_1, int * param_2, undefined4 * param_3)
 */


/* [cgpt i76.exe resource/archive rename v11; confidence=high] Enumerates configured ZIX/resource
   path directories with FindFirstFileA/FindNextFileA into 0x30-byte registered resource records. */

undefined4 __cdecl
enumerate_registered_resource_directory_entries(int param_1,int *param_2,undefined4 *param_3)

{
  char cVar1;
  int iVar2;
  HANDLE hFindFile;
  BOOL BVar3;
  char *_Str1;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int *local_248;
  int local_244;
  _WIN32_FIND_DATAA local_240;
  char local_100 [256];
  
  iVar5 = 0;
  local_244 = 0;
  if (param_2 != (int *)0x0) {
    *param_2 = 0;
  }
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = 0;
  }
  iVar4 = 0;
  if (0 < g_zix_search_path_count) {
    _Str1 = &g_zix_search_path_records;
    local_248 = &DAT_006593e0;
    do {
      iVar2 = _stricmp(_Str1,s_i76_zfs_004fffd8);
      if (iVar2 == 0) {
        iVar4 = iVar4 + 1;
        local_248 = local_248 + 0x43;
        _Str1 = _Str1 + 0x10c;
      }
      if (*local_248 == 1) {
        sprintf(local_100,s__s_____004fffd0,_Str1);
      }
      else if (*local_248 == 0) {
        pcVar6 = _Str1;
        cVar1 = get_active_cdrom_drive_letter();
        sprintf(local_100,s__c___s_____004fffc4,(int)cVar1,pcVar6);
      }
      hFindFile = FindFirstFileA(local_100,&local_240);
      if (hFindFile != (HANDLE)0xffffffff) {
        pcVar6 = (char *)(iVar5 * 0x30 + param_1);
        do {
          if ((local_240.cFileName[0] != '.') &&
             (_strlwr(local_240.cFileName), ((byte)local_240.dwFileAttributes & 0x10) == 0)) {
            if (param_1 != 0) {
              *(int *)(pcVar6 + 0x10) = iVar4;
              strncpy(pcVar6,local_240.cFileName,0x10);
              lowercase_resource_filename(pcVar6);
            }
            local_244 = local_244 + 1;
            pcVar6 = pcVar6 + 0x30;
          }
          BVar3 = FindNextFileA(hFindFile,&local_240);
        } while (BVar3 == 1);
        FindClose(hFindFile);
        iVar5 = local_244;
      }
      iVar4 = iVar4 + 1;
      local_248 = local_248 + 0x43;
      _Str1 = _Str1 + 0x10c;
    } while (iVar4 < g_zix_search_path_count);
  }
  if (param_2 != (int *)0x0) {
    *param_2 = iVar5;
  }
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = 0;
  }
  return 1;
}


