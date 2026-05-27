/*
 * Program: i76.exe
 * Function: parse_vcfc_vehicle_config_root
 * Entry: 004adb90
 * Signature: undefined4 __cdecl parse_vcfc_vehicle_config_root(int param_1, byte * param_2)
 */


/* [i76 level/static/material baseline v48]
   name: parse_vcfc_vehicle_config_root
   confidence: high
   module: vehicle_vcf
   Parses VCFC vehicle config root. Included for ODEF VCF-backed class chain completeness.
   note: Name already matches baseline. */

undefined4 __cdecl parse_vcfc_vehicle_config_root(int param_1,byte *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  bool bVar7;
  undefined3 extraout_var;
  int iVar8;
  undefined3 extraout_var_00;
  uint uVar9;
  uint uVar10;
  byte *pbVar11;
  char *pcVar12;
  byte *pbVar13;
  char *pcVar14;
  byte local_b0 [4];
  undefined4 local_ac;
  float local_98;
  char local_86 [18];
  undefined4 local_74;
  float local_60;
  char local_4e [18];
  undefined4 local_3c;
  float local_24;
  char local_12 [18];
  
  iVar6 = *(int *)(param_2 + 4);
  uVar9 = 0xffffffff;
  pcVar12 = (char *)(param_1 + 8);
  do {
    pcVar14 = pcVar12;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar14 = pcVar12 + 1;
    cVar4 = *pcVar12;
    pcVar12 = pcVar14;
  } while (cVar4 != '\0');
  uVar9 = ~uVar9;
  pcVar12 = pcVar14 + -uVar9;
  pcVar14 = (char *)(iVar6 + 0x50);
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar12;
    pcVar12 = pcVar12 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar14 = *pcVar12;
    pcVar12 = pcVar12 + 1;
    pcVar14 = pcVar14 + 1;
  }
  uVar9 = 0xffffffff;
  pbVar11 = (byte *)(param_1 + 0x18);
  do {
    pbVar13 = pbVar11;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pbVar13 = pbVar11 + 1;
    bVar5 = *pbVar11;
    pbVar11 = pbVar13;
  } while (bVar5 != 0);
  uVar9 = ~uVar9;
  pbVar11 = pbVar13 + -uVar9;
  pbVar13 = (byte *)(iVar6 + 0xf0);
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pbVar13 = *(undefined4 *)pbVar11;
    pbVar11 = pbVar11 + 4;
    pbVar13 = pbVar13 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pbVar13 = *pbVar11;
    pbVar11 = pbVar11 + 1;
    pbVar13 = pbVar13 + 1;
  }
  uVar9 = 0xffffffff;
  pcVar12 = (char *)(param_1 + 0x25);
  do {
    pcVar14 = pcVar12;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar14 = pcVar12 + 1;
    cVar4 = *pcVar12;
    pcVar12 = pcVar14;
  } while (cVar4 != '\0');
  uVar9 = ~uVar9;
  pcVar12 = pcVar14 + -uVar9;
  pcVar14 = (char *)(iVar6 + 0xfd);
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar12;
    pcVar12 = pcVar12 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar14 = *pcVar12;
    pcVar12 = pcVar12 + 1;
    pcVar14 = pcVar14 + 1;
  }
  *(undefined4 *)(iVar6 + 0xa7c) = *(undefined4 *)(param_1 + 0x65);
  *(undefined4 *)(iVar6 + 0xa80) = *(undefined4 *)(param_1 + 0x69);
  *(undefined4 *)(iVar6 + 0xa84) = *(undefined4 *)(param_1 + 0x6d);
  *(undefined4 *)(iVar6 + 0xa88) = *(undefined4 *)(param_1 + 0x71);
  *(undefined4 *)(iVar6 + 0xa8c) = *(undefined4 *)(param_1 + 0x75);
  *(undefined4 *)(iVar6 + 0xa90) = *(undefined4 *)(param_1 + 0x79);
  *(undefined4 *)(iVar6 + 0xa94) = *(undefined4 *)(param_1 + 0x7d);
  *(undefined4 *)(iVar6 + 0xa98) = *(undefined4 *)(param_1 + 0x81);
  *(undefined4 *)(iVar6 + 0xa9c) = *(undefined4 *)(param_1 + 0x85);
  bVar7 = parse_bwd2_resource_with_descriptor_table
                    ((byte *)(param_1 + 0x18),&vdfc_descriptor_table,0xd,param_2);
  if (CONCAT31(extraout_var,bVar7) == 0) {
    return 0;
  }
  iVar8 = parse_wdf_weapon_definition_into_vehicle_slot((byte *)(param_1 + 0x3e),(int)param_2,0);
  if (iVar8 == 0) {
    return 0;
  }
  iVar8 = parse_wdf_weapon_definition_into_vehicle_slot((byte *)(param_1 + 0x4b),(int)param_2,2);
  if (iVar8 == 0) {
    return 0;
  }
  iVar8 = parse_wdf_weapon_definition_into_vehicle_slot((byte *)(param_1 + 0x58),(int)param_2,4);
  if (iVar8 == 0) {
    return 0;
  }
  fVar1 = *(float *)(iVar6 + 0x2f4);
  fVar2 = *(float *)(iVar6 + 0x334);
  fVar3 = *(float *)(iVar6 + 0x374);
  pbVar11 = local_b0;
  for (iVar8 = 0x2c; iVar8 != 0; iVar8 = iVar8 + -1) {
    pbVar11[0] = 0;
    pbVar11[1] = 0;
    pbVar11[2] = 0;
    pbVar11[3] = 0;
    pbVar11 = pbVar11 + 4;
  }
  *(float *)(iVar6 + 0xaa0) = fVar1 + fVar2 + fVar3 + *(float *)(iVar6 + 0xaa0);
  local_ac = *(undefined4 *)(param_1 + 0x32);
  local_74 = *(undefined4 *)(param_1 + 0x3a);
  local_3c = *(undefined4 *)(param_1 + 0x36);
  iVar6 = *(int *)(param_2 + 4);
  bVar7 = parse_bwd2_resource_with_descriptor_table
                    ((byte *)s_compnent_cdf_004ffcd0,&component_cdf_descriptor_table,0xd,local_b0);
  if (CONCAT31(extraout_var_00,bVar7) == 0) {
    return 0;
  }
  uVar9 = 0xffffffff;
  pcVar12 = local_86;
  do {
    pcVar14 = pcVar12;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar14 = pcVar12 + 1;
    cVar4 = *pcVar12;
    pcVar12 = pcVar14;
  } while (cVar4 != '\0');
  uVar9 = ~uVar9;
  pcVar12 = pcVar14 + -uVar9;
  pcVar14 = (char *)(iVar6 + 0x137);
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar12;
    pcVar12 = pcVar12 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar14 = *pcVar12;
    pcVar12 = pcVar12 + 1;
    pcVar14 = pcVar14 + 1;
  }
  uVar9 = 0xffffffff;
  pcVar12 = local_12;
  do {
    pcVar14 = pcVar12;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar14 = pcVar12 + 1;
    cVar4 = *pcVar12;
    pcVar12 = pcVar14;
  } while (cVar4 != '\0');
  uVar9 = ~uVar9;
  pcVar12 = pcVar14 + -uVar9;
  pcVar14 = (char *)(iVar6 + 0x157);
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar12;
    pcVar12 = pcVar12 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar14 = *pcVar12;
    pcVar12 = pcVar12 + 1;
    pcVar14 = pcVar14 + 1;
  }
  uVar9 = 0xffffffff;
  pcVar12 = local_4e;
  do {
    pcVar14 = pcVar12;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar14 = pcVar12 + 1;
    cVar4 = *pcVar12;
    pcVar12 = pcVar14;
  } while (cVar4 != '\0');
  uVar9 = ~uVar9;
  pcVar12 = pcVar14 + -uVar9;
  pcVar14 = (char *)(iVar6 + 0x147);
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar12;
    pcVar12 = pcVar12 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar14 = *pcVar12;
    pcVar12 = pcVar12 + 1;
    pcVar14 = pcVar14 + 1;
  }
  local_98 = local_98 + *(float *)(iVar6 + 0xaa0);
  *(float *)(iVar6 + 0xaa0) = local_98;
  local_98 = local_98 + local_60;
  *(float *)(iVar6 + 0xaa0) = local_98;
  *(float *)(iVar6 + 0xaa0) = local_24 + local_98;
  return 1;
}


