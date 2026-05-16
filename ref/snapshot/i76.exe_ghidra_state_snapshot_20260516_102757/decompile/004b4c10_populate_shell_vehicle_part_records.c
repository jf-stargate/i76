/*
 * Program: i76.exe
 * Function: populate_shell_vehicle_part_records
 * Entry: 004b4c10
 * Signature: int __cdecl populate_shell_vehicle_part_records(int param_1)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=high] Populates frontend/shell vehicle
   part records and derives VTF names for vehicle paint/texture variants. */

int __cdecl populate_shell_vehicle_part_records(int param_1)

{
  int iVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  byte *pbVar5;
  char *pcVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  char *pcVar11;
  char local_20 [16];
  byte local_10;
  undefined4 local_f;
  undefined4 local_b;
  undefined4 local_7;
  undefined2 local_3;
  undefined1 local_1;
  
  iVar4 = param_1;
  DAT_005db984 = 0;
  append_empty_shell_vehicle_part_slots(param_1);
  sprintf(local_20,s___s_005008ec,&DAT_004ffec8);
  param_1 = 0;
  pbVar5 = (byte *)find_next_resource_file_record_by_pattern(local_20,&param_1);
  while (pbVar5 != (byte *)0x0) {
    append_wdf_weapon_part_record(iVar4,pbVar5);
    pbVar5 = (byte *)find_next_resource_file_record_by_pattern(local_20,&param_1);
  }
  sprintf(local_20,s___s_005008ec,s__gdf_004ffec0);
  param_1 = 0;
  pbVar5 = (byte *)find_next_resource_file_record_by_pattern(local_20,&param_1);
  while (pbVar5 != (byte *)0x0) {
    append_gdf_equipment_or_weapon_record(iVar4,pbVar5);
    pbVar5 = (byte *)find_next_resource_file_record_by_pattern(local_20,&param_1);
  }
  sprintf(local_20,s___s_005008ec,&DAT_00500630);
  param_1 = 0;
  pbVar5 = (byte *)find_next_resource_file_record_by_pattern(local_20,&param_1);
  do {
    if (pbVar5 == (byte *)0x0) {
      append_builtin_engine_part_records(iVar4,4);
      append_builtin_suspension_part_records(iVar4,4);
      append_builtin_brake_part_records(iVar4,4);
      append_builtin_special_equipment_records(iVar4);
      return DAT_005db984;
    }
    local_f = 0;
    local_b = 0;
    local_7 = 0;
    local_10 = 0;
    local_3 = 0;
    local_1 = 0;
    parse_vtfc_vehicle_display_key_resource(pbVar5,&local_10);
    uVar7 = 0xffffffff;
    do {
      pbVar10 = pbVar5;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pbVar10 = pbVar5 + 1;
      bVar2 = *pbVar5;
      pbVar5 = pbVar10;
    } while (bVar2 != 0);
    uVar7 = ~uVar7;
    pbVar5 = pbVar10 + -uVar7;
    pbVar10 = (byte *)(iVar4 + 0x3b + DAT_005db984 * 0x54);
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pbVar10 = *(undefined4 *)pbVar5;
      pbVar5 = pbVar5 + 4;
      pbVar10 = pbVar10 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pbVar10 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      pbVar10 = pbVar10 + 1;
    }
    pcVar6 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,&local_10);
    uVar7 = 0xffffffff;
    do {
      pcVar11 = pcVar6;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar11 = pcVar6 + 1;
      cVar3 = *pcVar6;
      pcVar6 = pcVar11;
    } while (cVar3 != '\0');
    uVar7 = ~uVar7;
    pcVar6 = pcVar11 + -uVar7;
    pcVar11 = (char *)(iVar4 + DAT_005db984 * 0x54);
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar11 = pcVar11 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar11 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar11 = pcVar11 + 1;
    }
    *(undefined4 *)(iVar4 + 0x1e + DAT_005db984 * 0x54) = 0xe;
    iVar9 = 1;
    do {
      iVar1 = iVar9 + DAT_005db984 * 0x15;
      iVar9 = iVar9 + 1;
      *(undefined4 *)(iVar4 + 0x1e + iVar1 * 4) = 0;
    } while (iVar9 < 4);
    DAT_005db984 = DAT_005db984 + 1;
    pbVar5 = (byte *)find_next_resource_file_record_by_pattern(local_20,&param_1);
  } while( true );
}


