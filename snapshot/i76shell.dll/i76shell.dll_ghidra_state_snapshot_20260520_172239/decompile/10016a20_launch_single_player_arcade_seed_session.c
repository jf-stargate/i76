/*
 * Program: i76shell.dll
 * Function: launch_single_player_arcade_seed_session
 * Entry: 10016a20
 * Signature: undefined __stdcall launch_single_player_arcade_seed_session(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void launch_single_player_arcade_seed_session(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  char *pcVar6;
  undefined4 *puVar7;
  char *pcVar8;
  
  reset_shell_session_resource_globals();
  DAT_100c5ad8[0xe] = 0;
  DAT_100c5b18 = 0;
  DAT_100c5ae0._0_2_ = 0;
  DAT_100c5af8 = 1;
  DAT_100c5afc = 0;
  _DAT_100c5b00 = 0;
  write_player_definition_file(&DAT_100c5ae0);
  FUN_100177e0();
  (*(code *)DAT_10058198[5])(&DAT_100581a0,s_vppa01_vcf_10047880,DAT_100c5b18);
  DAT_10047710 = (*(code *)*DAT_10058198)(&DAT_100c6288);
  build_vehicle_part_category_lists();
  export_current_vehicle_config_with_parts(s_addon_vehscn_vcf_1004788c,0);
  export_vehicle_scene_with_selected_parts(s_addon_vehscn_vsf_100478a0,0,0,0,0);
  destroy_vehicle_part_category_lists();
  *DAT_100d2180 = DAT_100c5af8;
  *DAT_100d2164 = 5;
  uVar2 = 0xffffffff;
  pcVar6 = &DAT_100478b4;
  do {
    pcVar8 = pcVar6;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar8 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar8;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar6 = pcVar8 + -uVar2;
  pcVar8 = (char *)(DAT_100d2170 + 0x5d);
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  puVar5 = &DAT_100c5ae0;
  puVar7 = DAT_100c5ad8;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar7 = puVar7 + 1;
  }
  uVar2 = 0xffffffff;
  pcVar6 = &DAT_100478bc;
  do {
    pcVar8 = pcVar6;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar8 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar8;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar6 = pcVar8 + -uVar2;
  pcVar8 = (char *)((int)DAT_100c5ad8 + 0x29);
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  return;
}


