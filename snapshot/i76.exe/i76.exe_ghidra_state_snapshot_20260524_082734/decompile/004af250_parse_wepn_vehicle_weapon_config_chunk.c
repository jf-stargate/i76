/*
 * Program: i76.exe
 * Function: parse_wepn_vehicle_weapon_config_chunk
 * Entry: 004af250
 * Signature: undefined4 __cdecl parse_wepn_vehicle_weapon_config_chunk(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] WEPN callback in
   VCFC table; parses vehicle weapon config subrecords. */

undefined4 __cdecl parse_wepn_vehicle_weapon_config_chunk(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  undefined3 extraout_var;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  char *pcVar9;
  char *pcVar10;
  int local_190 [4];
  int local_180;
  char local_17c [52];
  float local_148;
  
  iVar2 = *(int *)(param_2 + 4);
  iVar4 = 0;
  piVar8 = local_190;
  for (iVar5 = 100; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar8 = 0;
    piVar8 = piVar8 + 1;
  }
  local_190[0] = param_2;
  local_180 = *(int *)(param_1 + 8);
  iVar5 = -1;
  if (0 < *(int *)(iVar2 + 0xa5c)) {
    piVar8 = (int *)(iVar2 + 0x428);
    do {
      iVar5 = iVar4;
      if (*piVar8 == local_180) break;
      iVar4 = iVar4 + 1;
      piVar8 = piVar8 + 0x3f;
      iVar5 = -1;
    } while (iVar4 < *(int *)(iVar2 + 0xa5c));
  }
  if (iVar5 == -1) {
    return 0;
  }
  bVar3 = parse_bwd2_resource_with_descriptor_table
                    ((byte *)(param_1 + 0xc),&GDF_descriptor_table,6,(byte *)local_190);
  if (CONCAT31(extraout_var,bVar3) == 0) {
    return 0;
  }
  uVar6 = 0xffffffff;
  pcVar9 = local_17c;
  do {
    pcVar10 = pcVar9;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar10 = pcVar9 + 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar10;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar9 = pcVar10 + -uVar6;
  pcVar10 = (char *)(iVar2 + 0x3c8 + iVar5 * 0xfc);
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
    pcVar9 = pcVar9 + 4;
    pcVar10 = pcVar10 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar10 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    pcVar10 = pcVar10 + 1;
  }
  *(float *)(iVar2 + 0xaa0) = local_148 + *(float *)(iVar2 + 0xaa0);
  return 1;
}


