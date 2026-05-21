/*
 * Program: i76shell.dll
 * Function: launch_single_player_trip_seed_session
 * Entry: 10016b50
 * Signature: undefined __stdcall launch_single_player_trip_seed_session(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void launch_single_player_trip_seed_session(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  char *pcVar6;
  undefined4 *puVar7;
  char *pcVar8;
  
  DAT_100c5ad8[0xe] = 0;
  DAT_100c5b18 = 0;
  DAT_100c5ae0._0_2_ = 0;
  DAT_100c5af8 = 1;
  DAT_100c5afc = 0;
  _DAT_100c5b00 = 2;
  write_player_definition_file(&DAT_100c5ae0);
  FUN_100177e0();
  (*(code *)DAT_10058198[5])(&DAT_100581a0,s_vppt01_vcf_100478c8,DAT_100c5b18);
  DAT_10047710 = (*(code *)*DAT_10058198)(&DAT_100c6288);
  build_vehicle_part_category_lists();
  export_current_vehicle_config_with_parts(s_addon_vehscn_vcf_100478d4,0);
  export_vehicle_scene_with_selected_parts(s_addon_vehscn_vsf_100478e8,0,0,0,0);
  destroy_vehicle_part_category_lists();
  *DAT_100d2180 = DAT_100c5af8;
  *DAT_100d2164 = 5;
  puVar5 = &DAT_100c5ae0;
  puVar7 = DAT_100c5ad8;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar7 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar7 = puVar7 + 1;
  }
  uVar3 = 0xffffffff;
  pcVar6 = &DAT_100478fc;
  do {
    pcVar8 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar6 = pcVar8 + -uVar3;
  pcVar8 = (char *)((int)DAT_100c5ad8 + 0x29);
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  if (DAT_100d21bc != 0) {
    PostMessageA(DAT_100f702c,0xc020,0,0);
    return;
  }
  PostMessageA(DAT_100f702c,0xc010,0,0);
  return;
}


