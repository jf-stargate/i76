/*
 * Program: i76.exe
 * Function: enumerate_cdrom_drives
 * Entry: 00471250
 * Signature: undefined4 __stdcall enumerate_cdrom_drives(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe mission/vehicle runtime rename v15; confidence=high] Enumerates CD-ROM drives,
   identifies I76 CD media, initializes loaded-resource/ZFS/PixPak callbacks, and loads the PIX/PAK
   resource index. */

undefined4 enumerate_cdrom_drives(void)

{
  char cVar1;
  bool bVar2;
  DWORD DVar3;
  UINT UVar4;
  BOOL BVar5;
  LPCSTR pCVar6;
  uint uVar7;
  char *_Str1;
  char cVar8;
  int iVar9;
  char *pcVar10;
  int local_50;
  DWORD local_4c;
  DWORD local_48;
  DWORD local_44;
  undefined *local_40 [8];
  CHAR local_20 [32];
  
  DAT_0058d934 = 1;
  local_40[0] = PTR_DAT_004f8bac;
  DVar3 = GetLogicalDrives();
  cVar8 = '\0';
  iVar9 = 0;
  do {
    if ((DVar3 & 1 << ((byte)iVar9 & 0x1f)) != 0) {
      local_40[0] = (undefined *)CONCAT31(local_40[0]._1_3_,cVar8 + 'A');
      UVar4 = GetDriveTypeA((LPCSTR)local_40);
      if (UVar4 == 5) {
        (&DAT_00609520)[iVar9] = 1;
      }
    }
    cVar8 = cVar8 + '\x01';
    iVar9 = iVar9 + 1;
  } while (cVar8 < '\x1a');
  bVar2 = false;
  DAT_0058d930 = 0;
  DAT_0058d92c = '\0';
  local_50 = 0;
  do {
    if (bVar2) break;
    if ((&DAT_00609520)[local_50] != '\0') {
      DAT_0058d930 = DAT_0058d930 + 1;
      cVar8 = (char)local_50 + 'A';
      local_40[0]._1_3_ = (undefined3)((uint)PTR_DAT_004f8bac >> 8);
      local_40[0] = (undefined *)CONCAT31(local_40[0]._1_3_,cVar8);
      BVar5 = GetVolumeInformationA
                        ((LPCSTR)local_40,&DAT_00609540,0x20,&local_44,&local_48,&local_4c,local_20,
                         0x20);
      _Str1 = (char *)(-(uint)(BVar5 != 0) & 0x609540);
      if (_Str1 != (char *)0x0) {
        uVar7 = 0xffffffff;
        pcVar10 = s_I76_CD_004f8c64;
        do {
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar10 + 1;
        } while (cVar1 != '\0');
        iVar9 = _strnicmp(_Str1,s_I76_CD_004f8c64,~uVar7 - 1);
        if (iVar9 == 0) {
          bVar2 = true;
          DAT_0058d92c = cVar8;
        }
      }
    }
    local_50 = local_50 + 1;
  } while (local_50 < 0x1a);
  initialize_loaded_resource_cache_heap();
  zfsf_payload_wrapper_context_helper_004b9dd0();
  DAT_00669ee4 = 1;
  DAT_00669ee0 = &LAB_00470d40;
  _DAT_00669ee8 = get_active_cdrom_drive_letter;
  DAT_006562d0 = &LAB_00470d90;
  iVar9 = init_resource_search_paths(s_i76_zix_004f8c5c);
  if (iVar9 != 0) {
    load_pix_pak_resource_index();
    return 1;
  }
  pCVar6 = (LPCSTR)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                 s_Sorry__unable_to_find_required_f_004f8bf4);
  fatal_out_of_memory_message(pCVar6);
  return 0;
}


