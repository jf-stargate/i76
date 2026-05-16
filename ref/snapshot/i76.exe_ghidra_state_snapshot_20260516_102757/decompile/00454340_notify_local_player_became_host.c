/*
 * Program: i76.exe
 * Function: notify_local_player_became_host
 * Entry: 00454340
 * Signature: undefined4 __cdecl notify_local_player_became_host(ushort param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: You are now the host */

undefined4 __cdecl notify_local_player_became_host(ushort param_1)

{
  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined4 uVar7;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 extraout_var_03;
  ushort uVar8;
  bool bVar9;
  uchar local_250 [24];
  char local_238 [80];
  uchar local_1e8 [80];
  undefined4 local_198 [102];
  
  puVar3 = &DAT_00541070;
  uVar8 = 0;
  iVar5 = 0;
  do {
    if (*puVar3 == param_1) break;
    puVar3 = puVar3 + 0x24;
    iVar5 = iVar5 + 1;
  } while ((int)puVar3 < 0x5414f0);
  if (iVar5 == 0x10) {
    iVar5 = -1;
  }
  if (iVar5 == -1) {
    return 0;
  }
  if (DAT_005dd330 != 0) {
    DAT_005dd330 = 0;
    write_multiplayer_score_results_file();
  }
  uVar2 = DAT_00541064;
  bVar9 = DAT_00541064 == param_1;
  (&DAT_00541070)[iVar5 * 0x24] = 0;
  if (bVar9) {
    puVar3 = &DAT_00541070;
    do {
      uVar1 = *puVar3;
      if (((uVar1 != 0) && (*(int *)(puVar3 + 0x18) != -0x40800000)) &&
         ((uVar8 == 0 || (uVar1 < uVar8)))) {
        uVar8 = uVar1;
      }
      puVar3 = puVar3 + 0x24;
    } while ((int)puVar3 < 0x5414f0);
    uVar7 = CONCAT22(0xbf80,DAT_00541028);
    if (uVar2 == DAT_00541028) {
      pcVar4 = local_238;
      for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
        pcVar4[0] = '\0';
        pcVar4[1] = '\0';
        pcVar4[2] = '\0';
        pcVar4[3] = '\0';
        pcVar4 = pcVar4 + 4;
      }
      dpGetPlayerName(DAT_00541024,uVar7,local_238,0x50);
      dpSetPlayerData(DAT_00541024,CONCAT22(extraout_var_01,DAT_00541028),2,0,0,0);
      dpSetPlayerData(DAT_00541024,CONCAT22(extraout_var,DAT_00541028),3,0,0,0);
      uVar7 = CONCAT22(extraout_var_02,DAT_00541028);
    }
    DAT_00541064 = uVar8;
    if (uVar8 == (ushort)uVar7) {
      pcVar4 = local_238;
      for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
        pcVar4[0] = '\0';
        pcVar4[1] = '\0';
        pcVar4[2] = '\0';
        pcVar4[3] = '\0';
        pcVar4 = pcVar4 + 4;
      }
      dpGetPlayerName(DAT_00541024,uVar7,local_238,0x50);
      copy_shell_session_text_block(local_238);
      dpSetPlayerData(DAT_00541024,CONCAT22(extraout_var_00,DAT_00541028),2,local_238,0x1e,0);
      copy_shell_session_descriptor_block(local_198);
      dpSetPlayerData(DAT_00541024,CONCAT22(extraout_var_03,DAT_00541028),3,local_198,0x198,0);
    }
    multiplayer_scoreboard_accumulator_helper_00451900();
    if (uVar8 == DAT_00541028) {
      pcVar4 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                     s_____You_are_now_the_host__004f5b38);
      sprintf((char *)local_1e8,pcVar4);
    }
    else {
      iVar6 = 0;
      puVar3 = &DAT_00541070;
      do {
        if (*puVar3 == uVar8) break;
        puVar3 = puVar3 + 0x24;
        iVar6 = iVar6 + 1;
      } while ((int)puVar3 < 0x5414f0);
      if (iVar6 == 0x10) {
        iVar6 = -1;
      }
      if ((iVar6 != -1) && (&stack0x00000000 != (undefined1 *)0x250)) {
        _mbsnbcpy(local_250,&DAT_00541072 + iVar6 * 0x48,0x18);
      }
      pcVar4 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                     s______s_is_now_the_host__004f5b20,local_250);
      sprintf((char *)local_1e8,pcVar4);
    }
    draw_multiplayer_chat_message(0,local_1e8);
  }
  if (*(int *)(iVar5 * 0x48 + 0x541090) != 0 || *(int *)(iVar5 * 0x48 + 0x541094) != 0) {
    parse_network_vehicle_slot_name();
  }
  iVar5 = (&DAT_00541098)[iVar5 * 0x12];
  if ((iVar5 != 0) && ((*(byte *)(*(int *)(iVar5 + 0x70) + 0x454) & 0x20) == 0)) {
    trigger_vehicle_forced_damage_or_actor_cleanup(iVar5);
  }
  DAT_00541068 = DAT_00541068 + -1;
  return 1;
}


