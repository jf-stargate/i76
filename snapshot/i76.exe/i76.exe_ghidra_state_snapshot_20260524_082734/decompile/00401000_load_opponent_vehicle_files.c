/*
 * Program: i76.exe
 * Function: load_opponent_vehicle_files
 * Entry: 00401000
 * Signature: undefined __stdcall load_opponent_vehicle_files(void)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=medium-high] Loads network/opponent
   vehicle VCF files from NVCL/VCL naming patterns. */

void load_opponent_vehicle_files(void)

{
  int iVar1;
  FILE *_File;
  char *pcVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 local_154;
  undefined4 local_150;
  FILE *local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  char local_13c [80];
  int local_ec;
  undefined1 local_e8 [102];
  undefined1 local_82 [130];
  
  write_multiplayer_scoreboard_report();
  DAT_00501780 = 1;
  g_is_network_mode = 1;
  DAT_00501810 = 3;
  DAT_00501814 = 8;
  g_mp_score_1 = 0;
  g_mp_score_0 = 0;
  register_world_object_tree_callback(&LAB_00401340);
  iVar1 = _access(&DAT_004c20a8,0);
  if (iVar1 == 0) {
    _unlink(s_NVCL___vcf_004c209c);
  }
  else {
    _mkdir(&DAT_004c20a8);
  }
  _File = fopen(s_MULTICAR_def_004c2088,&DAT_004c2098);
  local_14c = _File;
  if (_File != (FILE *)0x0) {
    fread(&DAT_0050177c,4,1,_File);
    uVar5 = 0;
    DAT_00501778 = DAT_0050177c;
    if (DAT_0050177c != 0) {
      puVar6 = &DAT_00501790;
      do {
        local_13c[0] = '\0';
        local_13c[1] = '\0';
        local_13c[2] = '\0';
        local_13c[3] = '\0';
        local_13c[4] = '\0';
        local_13c[5] = '\0';
        local_13c[6] = '\0';
        local_13c[7] = '\0';
        local_13c[8] = '\0';
        local_13c[9] = '\0';
        local_13c[10] = '\0';
        local_13c[0xb] = '\0';
        local_13c[0xc] = '\0';
        local_13c[0xd] = '\0';
        local_13c[0xe] = '\0';
        local_13c[0xf] = '\0';
        sprintf(local_13c,s_nvcl_1x_vcf_004c2038,uVar5);
        register_resource_key_for_zix_path(local_13c,&DAT_004c20a8);
        fread(&local_ec,0xeb,1,local_14c);
        sprintf(local_13c,s__s_nvcl_1x_vcf_004c2028,&DAT_004c20a8,uVar5);
        local_140 = 0;
        local_144 = 0;
        local_148 = 0;
        read_vehicle_config_weapon_chunks(local_13c,local_82,(int)local_e8,local_ec,&local_148);
        local_154 = 0;
        local_150 = 0;
        _splitpath(local_13c,(char *)0x0,(char *)0x0,(char *)&local_154,(char *)0x0);
        pcVar2 = format_8char_resource_basename_with_suffix(local_154,local_150,&s_dot_vcf);
        canonicalize_resource_key_16byte(pcVar2);
        uVar3 = DAT_00501778;
        *puVar6 = local_154;
        puVar6[1] = local_150;
        uVar5 = uVar5 + 1;
        puVar6 = puVar6 + 2;
        _File = local_14c;
      } while (uVar5 < uVar3);
    }
    fclose(_File);
    if (DAT_0050177c != 0) {
      puVar6 = &DAT_00501790;
      uVar5 = DAT_0050177c;
      do {
        uVar8 = puVar6[1];
        uVar7 = *puVar6;
        iVar9 = 0;
        iVar1 = 0;
        uVar3 = get_spawn_location_or_report_missing();
        load_vehicle_entity(uVar3,iVar1,uVar7,uVar8,iVar9);
        puVar6 = puVar6 + 2;
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
    }
    piVar4 = (int *)get_active_player_or_camera_world_object_entry();
    if (piVar4 != (int *)0x0) {
      fsm_set_ai_behavior_state_field_a948(*piVar4,&DAT_00501814);
      fsm_set_all_aggression(DAT_00501810);
    }
    return;
  }
  report_error();
  DAT_00501778 = 0;
  DAT_0050177c = 0;
  return;
}


