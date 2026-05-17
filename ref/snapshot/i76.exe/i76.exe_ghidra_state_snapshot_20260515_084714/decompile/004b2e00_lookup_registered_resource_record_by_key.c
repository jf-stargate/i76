/*
 * Program: i76.exe
 * Function: lookup_registered_resource_record_by_key
 * Entry: 004b2e00
 * Signature: undefined * __cdecl lookup_registered_resource_record_by_key(undefined4 * param_1)
 */


/* [cgpt i76.exe resource/archive rename v11; confidence=high] Looks up the 0x30-byte registered
   resource record by 16-byte lowercase key. */

undefined * __cdecl lookup_registered_resource_record_by_key(undefined4 *param_1)

{
  uint uVar1;
  byte bVar2;
  undefined1 uVar3;
  void *pvVar4;
  int iVar5;
  int *piVar6;
  undefined *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined *puVar11;
  undefined4 *local_38;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_30 = *param_1;
  local_2c = param_1[1];
  local_28 = param_1[2];
  local_24 = param_1[3];
  pvVar4 = bsearch(&local_30,g_registered_resource_records,g_registered_resource_record_count,0x30,
                   (_PtFuncCompare *)&compare_resource_record_16byte_key);
  if (pvVar4 == (void *)0x0) {
    sprintf(&g_resource_error_message,s_Couldn_t_find_file___s__004fffe8,param_1);
    return (undefined *)0x0;
  }
  puVar8 = (undefined4 *)0xffffffff;
  puVar9 = (undefined4 *)0x0;
  param_1 = (undefined4 *)0xffffffff;
  local_38 = (undefined4 *)0xffffffff;
  piVar6 = &DAT_006593e0;
  do {
    if ((((int)piVar6 < 0x669fe1) &&
        (uVar1 = *(uint *)((int)pvVar4 +
                          ((int)((int)puVar9 + ((int)puVar9 >> 0x1f & 0x1fU)) >> 5) * 4 + 0x10),
        uVar1 != 0)) &&
       (bVar2 = (byte)((int)puVar9 >> 0x1f),
       (uVar1 & 1 << ((((byte)puVar9 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2 & 0x1f)) != 0)) {
      if (param_1 == (undefined4 *)0xffffffff) {
        param_1 = puVar9;
      }
      if (*piVar6 == 0) {
        if (puVar8 == (undefined4 *)0xffffffff) {
          puVar8 = puVar9;
        }
        if ((piVar6[1] == DAT_004fff18) && (local_38 == (undefined4 *)0xffffffff)) {
          local_38 = puVar9;
        }
      }
    }
    piVar6 = piVar6 + 0x43;
    puVar9 = (undefined4 *)((int)puVar9 + 1);
  } while ((int)piVar6 < 0x669fe0);
  if ((DAT_00669ee4 != 0) && (puVar8 != (undefined4 *)0xffffffff)) {
    if ((int)param_1 < (int)puVar8) {
      return &g_zix_search_path_records + (int)param_1 * 0x10c;
    }
    param_1 = local_38;
    if (local_38 == (undefined4 *)0xffffffff) {
      iVar10 = 0;
      iVar5 = (&DAT_006593e4)[(int)puVar8 * 0x43];
      puVar7 = &DAT_006562e0 + iVar5 * 0x300;
      if (0 < g_zix_search_path_count) {
        puVar9 = &DAT_006593e8;
        do {
          if ((undefined4 *)*puVar9 != (undefined4 *)0x0) {
            close_zfsf_archive((undefined4 *)*puVar9);
            *puVar9 = 0;
          }
          iVar10 = iVar10 + 1;
          puVar9 = puVar9 + 0x43;
        } while (iVar10 < g_zix_search_path_count);
      }
      puVar11 = &DAT_006563e0 + iVar5 * 0x300;
      uVar3 = get_active_cdrom_drive_letter();
      iVar5 = (*DAT_006562d0)(uVar3,puVar7,puVar11);
      if (iVar5 == 0) {
        return (undefined *)0x0;
      }
      DAT_004fff18 = (&DAT_006593e4)[(int)puVar8 * 0x43];
      return &g_zix_search_path_records + (int)puVar8 * 0x10c;
    }
  }
  return &g_zix_search_path_records + (int)param_1 * 0x10c;
}


