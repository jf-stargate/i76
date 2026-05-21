/*
 * Program: i76shell.dll
 * Function: dispatch_selected_mission_or_vehicle_config_transition
 * Entry: 10002750
 * Signature: undefined __stdcall dispatch_selected_mission_or_vehicle_config_transition(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76shell first-pass rename
   old_name: FUN_10002750
   suggested_name: shell_menu_transition_or_dispatch
   basis: Shell UI/menu transition candidate referenced from ShellWindowProc/ShellMain neighborhood.
    */

void dispatch_selected_mission_or_vehicle_config_transition(void)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  char acStack_50 [40];
  char acStack_28 [40];
  
  if ((*DAT_100d2164 == 8) && (*DAT_100d2180 != 0x11)) {
    delete_user_repair_profile_file();
    destroy_repair_profile_pointer_list();
    reset_shell_session_resource_globals();
    iVar3 = read_spc_or_cmp_mission_vehicle_config(s_reconfig_spc_100431d0);
    if (iVar3 == 0) {
      PostMessageA(DAT_100f702c,0xc00e,0xc01e,0);
      return;
    }
  }
  else {
    iVar3 = *DAT_100d2180;
    if (*DAT_100d2164 == 1) {
      iVar3 = iVar3 + 1;
    }
    DAT_100cc500 = (int *)0x0;
    _DAT_100cc504 = 0;
    _DAT_100cc508 = 0;
    DAT_10047710 = (*(code *)*DAT_10058198)(&DAT_100c6288);
    puVar4 = &DAT_100581d8;
    do {
      *puVar4 = 0;
      puVar4 = puVar4 + 0x231;
    } while ((int)puVar4 < 0x100c5af8);
    uVar6 = 0xffffffff;
    pcVar8 = &DAT_100431e0;
    do {
      pcVar9 = pcVar8;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar9 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar9;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar8 = pcVar9 + -uVar6;
    pcVar9 = acStack_50;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar9 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    }
    uVar6 = 0xffffffff;
    pcVar8 = &DAT_100431ec;
    do {
      pcVar9 = pcVar8;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar9 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar9;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar8 = pcVar9 + -uVar6;
    pcVar9 = acStack_28;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar9 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    }
    if (iVar3 == 0x11) {
      (*(code *)DAT_10058198[5])(&DAT_100581a0,acStack_50,*(undefined4 *)(DAT_100c5ad8 + 0x38));
      populate_current_mission_vehicle_selection_list();
      PostMessageA(DAT_100f702c,0xc00d,0xc01e,0);
      return;
    }
    if ((DAT_100cc858 & 2) != 0) {
      (*(code *)DAT_10058198[5])(&DAT_100581a0,acStack_50,*(undefined4 *)(DAT_100c5ad8 + 0x38));
      populate_current_mission_vehicle_selection_list();
      bVar2 = false;
      piVar5 = DAT_100cc500;
      while (((piVar5 != (int *)0x0 && (piVar5 != DAT_100cc500)) || (!bVar2))) {
        piVar5[3] = *(int *)(*piVar5 + 0x4c);
        piVar5 = (int *)piVar5[1];
        bVar2 = true;
      }
      PostMessageA(DAT_100f702c,0xc015,0xc01e,0);
      return;
    }
    if (iVar3 == 0xd) {
      (*(code *)DAT_10058198[5])(&DAT_100581a0,acStack_50,*(undefined4 *)(DAT_100c5ad8 + 0x38));
      populate_current_mission_vehicle_selection_list();
      PostMessageA(DAT_100f702c,0xc015,0xc01e,0);
      return;
    }
    (*(code *)DAT_10058198[5])(&DAT_100581a0,acStack_50,*(undefined4 *)(DAT_100c5ad8 + 0x38));
    (*(code *)DAT_10058198[6])(&DAT_100c5b20,acStack_28,&LAB_10001800);
    DAT_100cc4fc = *(undefined4 *)(DAT_100c5ad8 + 0x38);
    populate_current_mission_vehicle_selection_list();
    apply_loaded_mission_vehicle_slot_defaults();
  }
  PostMessageA(DAT_100f702c,0xc017,0xc01e,0);
  return;
}


