/*
 * Program: i76.exe
 * Function: append_gdf_equipment_or_weapon_record
 * Entry: 004b5470
 * Signature: undefined __cdecl append_gdf_equipment_or_weapon_record(int param_1, byte * param_2)
 */


/* [cgpt i76.exe vehicle/resource rename v4; confidence=medium-high] Parses a .gdf resource and
   appends a shell vehicle-part record. It classifies parsed local_16c values into shell categories
   7/8/9 and reports ERROR weapon has no class. */

void __cdecl append_gdf_equipment_or_weapon_record(int param_1,byte *param_2)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  char *pcVar9;
  byte *pbVar10;
  byte local_190 [20];
  undefined1 local_17c [16];
  int local_16c;
  int local_168;
  undefined4 local_14c;
  undefined4 local_148;
  char local_144 [324];
  
  pbVar8 = local_190;
  for (iVar4 = 100; iVar4 != 0; iVar4 = iVar4 + -1) {
    pbVar8[0] = 0;
    pbVar8[1] = 0;
    pbVar8[2] = 0;
    pbVar8[3] = 0;
    pbVar8 = pbVar8 + 4;
  }
  parse_gdf_equipment_definition_resource(param_2,local_190);
  uVar7 = (local_168 < 100) - 1 & 0xb;
  pcVar3 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,local_17c);
  uVar5 = 0xffffffff;
  do {
    pcVar9 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar9 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar9;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar9 + -uVar5;
  pcVar9 = (char *)(param_1 + DAT_005db984 * 0x54);
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar9 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar3 = local_144;
  do {
    pcVar9 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar9 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar9;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar9 + -uVar5;
  pcVar9 = (char *)(param_1 + 0x2e + DAT_005db984 * 0x54);
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar9 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar5 = 0xffffffff;
  do {
    pbVar8 = param_2;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pbVar8 = param_2 + 1;
    bVar2 = *param_2;
    param_2 = pbVar8;
  } while (bVar2 != 0);
  uVar5 = ~uVar5;
  pbVar8 = pbVar8 + -uVar5;
  pbVar10 = (byte *)(param_1 + 0x3b + DAT_005db984 * 0x54);
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pbVar10 = *(undefined4 *)pbVar8;
    pbVar8 = pbVar8 + 4;
    pbVar10 = pbVar10 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar10 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar10 = pbVar10 + 1;
  }
  *(undefined4 *)(param_1 + 0x4c + DAT_005db984 * 0x54) = local_14c;
  if (local_16c == 1) {
    *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 9;
    *(undefined4 *)(param_1 + 0x22 + DAT_005db984 * 0x54) = 10;
    goto LAB_004b5698;
  }
  if (local_16c != 2) {
    if (local_16c == 3) {
      *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 7;
      *(uint *)(param_1 + 0x22 + DAT_005db984 * 0x54) = uVar7;
      goto LAB_004b5698;
    }
    if (local_16c == 4) {
      *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 7;
      *(uint *)(param_1 + 0x22 + DAT_005db984 * 0x54) = uVar7;
      goto LAB_004b5698;
    }
    if (local_16c != 5) {
      if (local_16c != 6) {
        report_chunk_parse_error();
                    /* WARNING: Subroutine does not return */
        exit(0);
      }
      *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 8;
      goto LAB_004b5698;
    }
  }
  *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 7;
  *(uint *)(param_1 + 0x22 + DAT_005db984 * 0x54) = uVar7;
LAB_004b5698:
  *(undefined4 *)(param_1 + 0x50 + DAT_005db984 * 0x54) = local_148;
  DAT_005db984 = DAT_005db984 + 1;
  return;
}


