/*
 * Program: i76.exe
 * Function: init_resource_search_paths
 * Entry: 004b23e0
 * Signature: undefined4 __cdecl init_resource_search_paths(char * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 first-pass rename
   old_name: FUN_004b23e0
   suggested_name: init_resource_search_paths
   basis: Resource/search-path setup candidate; clustered with archive/resource discovery routines.
    */

undefined4 __cdecl init_resource_search_paths(char *param_1)

{
  byte bVar1;
  bool bVar2;
  undefined1 uVar3;
  FILE *_File;
  int iVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int *_Source;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  int iVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  char *_Str2;
  undefined4 *puVar10;
  char *pcVar11;
  size_t local_18;
  int local_14;
  int local_10;
  int local_c;
  int *local_8;
  FILE *local_4;
  
  local_18 = 0;
  _File = fopen(param_1,s_rt_004fffc0);
  local_4 = _File;
  if (_File == (FILE *)0x0) {
    pcVar11 = s_Couldn_t_open_file___s__004fffa8;
LAB_004b2899:
    sprintf(&g_resource_error_message,pcVar11,param_1);
    return 0;
  }
  iVar4 = fscanf(_File,s__d_004fffa4,&local_18);
  if (iVar4 != 1) {
    pcVar11 = s_Could_not_read_number_of_files_f_004f8b58;
    goto LAB_004b2899;
  }
  g_zix_search_path_records = s_addon_004c2350[0];
  g_zix_search_path_records_1._0_1_ = s_addon_004c2350[1];
  g_zix_search_path_records_1._1_1_ = s_addon_004c2350[2];
  g_zix_search_path_records_1._2_1_ = s_addon_004c2350[3];
  DAT_006592e4 = s_addon_004c2350[4];
  DAT_006592e5 = s_addon_004c2350[5];
  DAT_006593e0 = 1;
  DAT_006593e4 = 0;
  g_zix_search_path_count = 2;
  bVar2 = get_global_heap_handle();
  if (CONCAT31(extraout_var,bVar2) == 0) {
    bVar2 = init_registry_install_settings();
    if (CONCAT31(extraout_var_01,bVar2) == 0) {
      DAT_006593ec = (char)DAT_004fff58;
      DAT_006593ec_1._0_1_ = DAT_004fff58._1_1_;
      DAT_006593ec_1._1_1_ = DAT_004fff58._2_1_;
      DAT_006593ec_1._2_1_ = DAT_004fff58._3_1_;
      DAT_006593f0 = (char)DAT_004fff5c;
      DAT_006593f0_1 = DAT_004fff5c._1_1_;
      goto LAB_004b24ea;
    }
    DAT_006593ec = (char)DAT_004fff58;
    DAT_006593ec_1._0_1_ = DAT_004fff58._1_1_;
    DAT_006593ec_1._1_1_ = DAT_004fff58._2_1_;
    DAT_006593ec_1._2_1_ = DAT_004fff58._3_1_;
    DAT_006593f0 = (char)DAT_004fff5c;
    DAT_006593f0_1 = DAT_004fff5c._1_1_;
    bVar2 = true;
  }
  else {
    bVar2 = init_registry_install_settings();
    DAT_006593f0 = s_miss16_004fff7c[4];
    DAT_006593f0_1 = s_miss16_004fff7c[5];
    DAT_006593ec = s_miss16_004fff7c[0];
    DAT_006593ec_1._0_1_ = s_miss16_004fff7c[1];
    DAT_006593ec_1._1_1_ = s_miss16_004fff7c[2];
    DAT_006593ec_1._2_1_ = s_miss16_004fff7c[3];
    DAT_006593f2 = s_miss16_004fff7c[6];
    if (CONCAT31(extraout_var_00,bVar2) == 0) {
LAB_004b24ea:
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
  }
  _DAT_006594ec = (uint)!bVar2;
  _DAT_006594f0 = 0;
  enumerate_registered_resource_directory_entries(0,&local_14,&local_10);
  local_18 = local_18 + local_14;
  iVar4 = parse_zix_path_line(_File,local_10);
  if (iVar4 == 0) {
    return 0;
  }
  _Source = HeapAlloc(g_process_heap,0,local_18 * 0x30);
  local_8 = _Source;
  if (_Source == (int *)0x0) {
    fatal_out_of_memory_message((LPCSTR)0x0);
  }
  DAT_006592e4 = s_addon_004c2350[4];
  DAT_006592e5 = s_addon_004c2350[5];
  g_zix_search_path_records = s_addon_004c2350[0];
  g_zix_search_path_records_1._0_1_ = s_addon_004c2350[1];
  g_zix_search_path_records_1._1_1_ = s_addon_004c2350[2];
  g_zix_search_path_records_1._2_1_ = s_addon_004c2350[3];
  DAT_006593e0 = 1;
  DAT_006593e4 = 0;
  iVar4 = g_zix_search_path_count * 0x10c;
  pcVar11 = &g_zix_search_path_records + iVar4;
  bVar2 = get_global_heap_handle();
  if (CONCAT31(extraout_var_02,bVar2) == 0) {
    bVar2 = init_registry_install_settings();
    if (CONCAT31(extraout_var_04,bVar2) != 0) {
      *(undefined4 *)pcVar11 = DAT_004fff58;
      *(undefined2 *)(&DAT_006592e4 + iVar4) = DAT_004fff5c;
      bVar2 = true;
      goto LAB_004b260e;
    }
    *(undefined4 *)pcVar11 = DAT_004fff58;
    *(undefined2 *)(&DAT_006592e4 + iVar4) = DAT_004fff5c;
  }
  else {
    bVar2 = init_registry_install_settings();
    *(undefined4 *)pcVar11 = s_miss16_004fff7c._0_4_;
    *(undefined2 *)(&DAT_006592e4 + iVar4) = s_miss16_004fff7c._4_2_;
    *(char *)(iVar4 + 0x6592e6) = s_miss16_004fff7c[6];
    if (CONCAT31(extraout_var_03,bVar2) != 0) {
      bVar2 = true;
      goto LAB_004b260e;
    }
  }
  bVar2 = false;
LAB_004b260e:
  if (bVar2) {
    (&DAT_006593e0)[g_zix_search_path_count * 0x43] = 0;
  }
  else {
    (&DAT_006593e0)[g_zix_search_path_count * 0x43] = 1;
  }
  (&DAT_006593e4)[g_zix_search_path_count * 0x43] = 0;
  g_zix_search_path_count = g_zix_search_path_count + 1;
  enumerate_registered_resource_directory_entries((int)_Source,(int *)0x0,(undefined4 *)0x0);
  if (local_14 < (int)local_18) {
    piVar6 = _Source + local_14 * 0xc;
    iVar4 = local_14;
    do {
      iVar5 = fscanf(_File,s__d__s_004fff9c,&local_c,piVar6);
      if (iVar5 != 2) {
        pcVar11 = s_Invalid_file_line_in__s_004fff84;
        goto LAB_004b2899;
      }
      piVar6[4] = local_c + local_10;
      lowercase_resource_filename((char *)piVar6);
      iVar4 = iVar4 + 1;
      piVar6 = piVar6 + 0xc;
    } while (iVar4 < (int)local_18);
  }
  qsort(_Source,local_18,0x30,registered_resource_directory_context_helper_004b2a70);
  g_registered_resource_records = HeapAlloc(g_process_heap,0,local_18 * 0x30);
  puVar10 = g_registered_resource_records;
  for (uVar7 = local_18 * 0x30 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined1 *)puVar10 = 0;
    puVar10 = (undefined4 *)((int)puVar10 + 1);
  }
  if (g_registered_resource_records == (undefined4 *)0x0) {
    fatal_out_of_memory_message((LPCSTR)0x0);
  }
  iVar4 = -1;
  piVar9 = (int *)&DAT_00504c28;
  g_registered_resource_record_count = -1;
  param_1 = (char *)0x0;
  piVar6 = _Source;
  if (0 < (int)local_18) {
    do {
      iVar5 = 0;
      piVar6 = piVar9;
      do {
        iVar8 = *piVar6 - *(int *)((int)piVar6 + ((int)_Source - (int)piVar9));
        if (iVar8 != 0) goto LAB_004b274c;
        piVar6 = piVar6 + 1;
        iVar5 = iVar5 + 1;
      } while (iVar5 < 4);
      iVar8 = 0;
LAB_004b274c:
      if (iVar8 != 0) {
        g_registered_resource_record_count = iVar4 + 1;
        strncpy((char *)(g_registered_resource_records + g_registered_resource_record_count * 0xc),
                (char *)_Source,0x10);
        iVar4 = g_registered_resource_record_count;
        piVar9 = _Source;
      }
      iVar5 = _Source[4];
      if (iVar5 < 0x101) {
        bVar1 = (byte)(iVar5 >> 0x1f);
        iVar8 = (int)(iVar5 + (iVar5 >> 0x1f & 0x1fU)) >> 5;
        g_registered_resource_records[iVar4 * 0xc + iVar8 + 4] =
             g_registered_resource_records[iVar4 * 0xc + iVar8 + 4] |
             1 << ((((byte)iVar5 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1 & 0x1f);
        iVar4 = g_registered_resource_record_count;
      }
      param_1 = param_1 + 1;
      _Source = _Source + 0xc;
      piVar6 = local_8;
    } while ((int)param_1 < (int)local_18);
  }
  g_registered_resource_record_count = iVar4 + 1;
  g_registered_resource_records =
       HeapReAlloc(g_process_heap,0,g_registered_resource_records,
                   g_registered_resource_record_count * 0x30);
  HeapFree(g_process_heap,0,piVar6);
  fclose(local_4);
  uVar3 = get_active_cdrom_drive_letter();
  pcVar11 = (char *)(*DAT_00669ee0)(uVar3);
  iVar4 = DAT_004fff18;
  if ((pcVar11 != (char *)0x0) && (iVar5 = 0, 0 < DAT_006562cc)) {
    _Str2 = &DAT_006562e0;
    while (iVar8 = _stricmp(pcVar11,_Str2), iVar4 = iVar5, iVar8 != 0) {
      iVar5 = iVar5 + 1;
      _Str2 = _Str2 + 0x300;
      if (DAT_006562cc <= iVar5) {
        return 1;
      }
    }
  }
  DAT_004fff18 = iVar4;
  return 1;
}


