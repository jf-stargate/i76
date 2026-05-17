/*
 * Program: i76.exe
 * Function: load_vehicle_config_for_world_object
 * Entry: 004ad6f0
 * Signature: undefined4 __cdecl load_vehicle_config_for_world_object(undefined4 param_1, byte * param_2, char * param_3)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=high] Loads a vehicle object's VCF/VCST
   resources, appends .vcf/.vsf suffixes, and enters the BWD2 descriptor parser. */

undefined4 __cdecl
load_vehicle_config_for_world_object(undefined4 param_1,byte *param_2,char *param_3)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  char *pcVar8;
  char *pcVar9;
  byte *pbVar10;
  byte local_cbc [16];
  char local_cac [4];
  char local_ca8 [256];
  char local_ba8 [256];
  byte local_aa8 [2728];
  
  pbVar7 = local_aa8;
  for (iVar4 = 0x2aa; iVar4 != 0; iVar4 = iVar4 + -1) {
    pbVar7[0] = 0;
    pbVar7[1] = 0;
    pbVar7[2] = 0;
    pbVar7[3] = 0;
    pbVar7 = pbVar7 + 4;
  }
  *(byte **)(param_2 + 4) = local_aa8;
  iVar4 = world_object_has_optional_runtime_flag(*(int *)param_2);
  if ((iVar4 == 0) || (g_force_explicit_vehicle_config_path != 0)) {
    uVar5 = 0xffffffff;
    do {
      pcVar8 = param_3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar8 = param_3 + 1;
      cVar1 = *param_3;
      param_3 = pcVar8;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pbVar7 = (byte *)(pcVar8 + -uVar5);
    pbVar10 = local_cbc;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pbVar10 = *(undefined4 *)pbVar7;
      pbVar7 = pbVar7 + 4;
      pbVar10 = pbVar10 + 4;
    }
  }
  else {
    _splitpath((char *)&g_selected_mission_resource_path,local_cac,local_ba8,(char *)local_cbc,
               local_ca8);
    strncpy(*(char **)param_2,(char *)local_cbc,8);
    uVar5 = 0xffffffff;
    pcVar8 = &s_dot_vcf;
    do {
      pcVar9 = pcVar8;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar9 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar9;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    iVar4 = -1;
    pbVar7 = local_cbc;
    do {
      pbVar10 = pbVar7;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pbVar10 = pbVar7 + 1;
      bVar2 = *pbVar7;
      pbVar7 = pbVar10;
    } while (bVar2 != 0);
    pbVar7 = (byte *)(pcVar9 + -uVar5);
    pbVar10 = pbVar10 + -1;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pbVar10 = *(undefined4 *)pbVar7;
      pbVar7 = pbVar7 + 4;
      pbVar10 = pbVar10 + 4;
    }
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar10 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    pbVar10 = pbVar10 + 1;
  }
  bVar3 = parse_bwd2_resource_with_descriptor_table
                    (local_cbc,&g_vcfc_vehicle_config_descriptor_table,4,param_2);
  if (CONCAT31(extraout_var,bVar3) == 0) {
    return 0;
  }
  if (g_selected_mission_family == 2) {
    _splitpath((char *)local_cbc,local_cac,local_ba8,(char *)local_cbc,local_ca8);
    uVar5 = 0xffffffff;
    pcVar8 = &s_dot_vsf;
    do {
      pcVar9 = pcVar8;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar9 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar9;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    iVar4 = -1;
    pbVar7 = local_cbc;
    do {
      pbVar10 = pbVar7;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pbVar10 = pbVar7 + 1;
      bVar2 = *pbVar7;
      pbVar7 = pbVar10;
    } while (bVar2 != 0);
    pbVar7 = (byte *)(pcVar9 + -uVar5);
    pbVar10 = pbVar10 + -1;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pbVar10 = *(undefined4 *)pbVar7;
      pbVar7 = pbVar7 + 4;
      pbVar10 = pbVar10 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pbVar10 = *pbVar7;
      pbVar7 = pbVar7 + 1;
      pbVar10 = pbVar10 + 1;
    }
    uVar5 = 0xffffffff;
    pbVar7 = local_cbc;
    do {
      pbVar10 = pbVar7;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pbVar10 = pbVar7 + 1;
      bVar2 = *pbVar7;
      pbVar7 = pbVar10;
    } while (bVar2 != 0);
    uVar5 = ~uVar5;
    pbVar7 = pbVar10 + -uVar5;
    pbVar10 = local_aa8;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pbVar10 = *(undefined4 *)pbVar7;
      pbVar7 = pbVar7 + 4;
      pbVar10 = pbVar10 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pbVar10 = *pbVar7;
      pbVar7 = pbVar7 + 1;
      pbVar10 = pbVar10 + 1;
    }
    bVar3 = resource_exists_in_cache_or_search_paths((char *)local_cbc);
    if (CONCAT31(extraout_var_00,bVar3) != 0) {
      parse_bwd2_resource_with_descriptor_table
                (local_cbc,&g_vcst_vehicle_state_descriptor_table,5,param_2);
      return 1;
    }
  }
  return 1;
}


