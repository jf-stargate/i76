/*
 * Program: i76.exe
 * Function: append_wdf_weapon_part_record
 * Entry: 004b5310
 * Signature: undefined __cdecl append_wdf_weapon_part_record(int param_1, byte * param_2)
 */


/* [cgpt i76.exe vehicle/resource rename v4; confidence=high] Parses a .wdf resource and appends a
   shell vehicle-part record with category 5. Evidence includes WDF use and weapon diagnostics in
   adjacent loader. */

void __cdecl append_wdf_weapon_part_record(int param_1,byte *param_2)

{
  int iVar1;
  byte bVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  byte *pbVar9;
  char *pcVar10;
  byte local_40 [24];
  undefined1 local_28 [16];
  undefined4 local_18;
  char local_14 [16];
  undefined4 local_4;
  
  pbVar8 = local_40;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    pbVar8[0] = 0;
    pbVar8[1] = 0;
    pbVar8[2] = 0;
    pbVar8[3] = 0;
    pbVar8 = pbVar8 + 4;
  }
  parse_wdf_weapon_definition_resource(param_2,local_40);
  uVar6 = 0xffffffff;
  do {
    pbVar8 = param_2;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pbVar8 = param_2 + 1;
    bVar2 = *param_2;
    param_2 = pbVar8;
  } while (bVar2 != 0);
  uVar6 = ~uVar6;
  pbVar8 = pbVar8 + -uVar6;
  pbVar9 = (byte *)(param_1 + 0x3b + DAT_005db984 * 0x54);
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pbVar9 = *(undefined4 *)pbVar8;
    pbVar8 = pbVar8 + 4;
    pbVar9 = pbVar9 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pbVar9 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar9 = pbVar9 + 1;
  }
  pcVar4 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,local_28);
  uVar6 = 0xffffffff;
  do {
    pcVar10 = pcVar4;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar10 = pcVar4 + 1;
    cVar3 = *pcVar4;
    pcVar4 = pcVar10;
  } while (cVar3 != '\0');
  uVar6 = ~uVar6;
  pcVar4 = pcVar10 + -uVar6;
  pcVar10 = (char *)(param_1 + DAT_005db984 * 0x54);
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar10 = pcVar10 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar10 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar10 = pcVar10 + 1;
  }
  *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 5;
  iVar5 = 1;
  do {
    iVar1 = iVar5 + DAT_005db984 * 0x15;
    iVar5 = iVar5 + 1;
    *(undefined4 *)(param_1 + 0x1e + iVar1 * 4) = 0;
  } while (iVar5 < 4);
  uVar6 = 0xffffffff;
  pcVar4 = local_14;
  do {
    pcVar10 = pcVar4;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar10 = pcVar4 + 1;
    cVar3 = *pcVar4;
    pcVar4 = pcVar10;
  } while (cVar3 != '\0');
  uVar6 = ~uVar6;
  pcVar4 = pcVar10 + -uVar6;
  pcVar10 = (char *)(param_1 + 0x2e + DAT_005db984 * 0x54);
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar10 = pcVar10 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar10 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar10 = pcVar10 + 1;
  }
  *(undefined4 *)(param_1 + 0x4c + DAT_005db984 * 0x54) = local_18;
  *(undefined4 *)(param_1 + 0x50 + DAT_005db984 * 0x54) = local_4;
  DAT_005db984 = DAT_005db984 + 1;
  return;
}


