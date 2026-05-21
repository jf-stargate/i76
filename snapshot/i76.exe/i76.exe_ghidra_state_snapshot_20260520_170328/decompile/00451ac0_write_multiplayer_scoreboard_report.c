/*
 * Program: i76.exe
 * Function: write_multiplayer_scoreboard_report
 * Entry: 00451ac0
 * Signature: undefined __stdcall write_multiplayer_scoreboard_report(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: formats player/team score kills deaths */

void write_multiplayer_scoreboard_report(void)

{
  short *psVar1;
  char cVar2;
  ushort uVar3;
  ushort uVar4;
  bool bVar5;
  short sVar6;
  short sVar7;
  int iVar8;
  undefined3 extraout_var;
  uint uVar9;
  uint uVar10;
  uint *puVar11;
  size_t sVar12;
  uint *puVar13;
  undefined2 *puVar14;
  uint uVar15;
  char *pcVar16;
  uint *puVar17;
  undefined4 uVar18;
  char *pcVar19;
  undefined **local_b4;
  size_t local_b0;
  ushort local_ac [2];
  int local_a8;
  uint local_a4;
  size_t local_a0;
  int local_9c;
  uint local_98;
  uchar local_94 [80];
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  char local_34 [4];
  char local_30 [36];
  undefined4 local_c;
  undefined4 local_4;
  
  local_44 = 0x32;
  local_40 = 0x96;
  local_3c = 0x50;
  local_38 = 9;
  local_c = 0xff;
  local_34 = (char  [4])s_courier_004f5a94._0_4_;
  local_30._0_4_ = s_courier_004f5a94._4_4_;
  local_4 = 8;
  DAT_00609324 = create_scroll_region_bitmap(&local_44);
  set_text_widget_integer_values(DAT_00609324,4,(undefined4 *)&DAT_004f59c8);
  DAT_00540da0 = 1;
  _DAT_00540fe8 = 0;
  clear_scrolling_text_widget_buffer(DAT_00609324);
  iVar8 = is_network_or_trip_runtime_mode();
  if (iVar8 != 0) {
    copy_multiplayer_scoreboard_name_string((char *)&DAT_00540da8);
    get_multiplayer_score_accumulators(&DAT_00540dc4,(undefined2 *)&DAT_00540dc0);
    DAT_00540dc0 = DAT_00540dc0 & 0xffff;
    sprintf((char *)local_94,s_Player_Name_Score_Kills_Deaths_004f5a6c);
    append_scrolling_text_widget_message(DAT_00609324,local_94);
    sprintf((char *)local_94,s___15s__6d__4d__4d_004f5a58,&DAT_00540da8,DAT_00540dc4,
            DAT_00540dc0 & 0xffff,DAT_00540dc0 >> 0x10);
    append_scrolling_text_widget_message(DAT_00609324,local_94);
    return;
  }
  local_a8 = get_multiplayer_player_count_or_limit();
  local_b0 = 0;
  iVar8 = multiplayer_chat_ui_context_helper_00452e10();
  if ((iVar8 == 0) || (DAT_00540da0 == 0)) {
    clear_multiplayer_scoreboard_dirty_flag();
    iVar8 = 0;
    puVar14 = (undefined2 *)((int)&DAT_00540dc0 + 2);
    local_b0 = 0;
    do {
      sVar6 = get_multiplayer_player_record_and_copy_name(iVar8,(uchar *)(puVar14 + -0xd));
      if (sVar6 != 0) {
        lookup_multiplayer_player_vehicle_config_id(sVar6,(undefined4 *)local_ac);
        sVar7 = get_local_multiplayer_player_id();
        sVar12 = local_b0;
        if (sVar6 != sVar7) {
          if ((local_ac[0] & 1) != 0) goto LAB_00451dd0;
          append_multiplayer_team_score_slot(sVar6);
          sVar12 = local_a0;
        }
        local_a0 = sVar12;
        get_multiplayer_player_spawn_score_fields
                  (sVar6,(undefined4 *)(puVar14 + 1),puVar14 + -1,puVar14);
        local_b0 = local_b0 + 1;
        puVar14 = puVar14 + 0x12;
        if (local_a8 <= (int)local_b0) break;
      }
LAB_00451dd0:
      iVar8 = iVar8 + 1;
    } while (iVar8 < 0x10);
  }
  else {
    local_a4 = 0;
    local_b4 = &PTR_s_Grey_Hounds_004c2130;
    puVar11 = &DAT_00540dc0;
    do {
      iVar8 = 0;
      uVar15 = 0;
      local_9c = 0;
      if (puVar11 != (uint *)0x0) {
        *(short *)puVar11 = 0;
      }
      if ((short *)((int)puVar11 + 2) != (short *)0x0) {
        *(short *)((int)puVar11 + 2) = 0;
      }
      do {
        sVar6 = get_multiplayer_player_record_and_copy_name(iVar8,(uchar *)0x0);
        if ((sVar6 != 0) &&
           (lookup_multiplayer_player_vehicle_config_id(sVar6,&local_98),
           (local_98 >> 0x10 & 7) == local_a4)) {
          get_multiplayer_player_spawn_score_fields
                    (sVar6,&local_a0,(undefined2 *)&local_a8,local_ac);
          uVar15 = uVar15 + local_a0;
          if (puVar11 != (uint *)0x0) {
            *(short *)puVar11 = (short)*puVar11 + (short)local_a8;
          }
          psVar1 = (short *)((int)puVar11 + 2);
          if (psVar1 != (short *)0x0) {
            *psVar1 = *psVar1 + local_ac[0];
          }
          local_9c = 1;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < 0x10);
      if (local_9c == 0) {
        uVar15 = 0xffffffff;
      }
      if (uVar15 != 0xffffffff) {
        uVar9 = 0xffffffff;
        pcVar19 = *local_b4;
        do {
          pcVar16 = pcVar19;
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          pcVar16 = pcVar19 + 1;
          cVar2 = *pcVar19;
          pcVar19 = pcVar16;
        } while (cVar2 != '\0');
        uVar9 = ~uVar9;
        puVar13 = (uint *)(pcVar16 + -uVar9);
        puVar17 = puVar11 + -6;
        for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *puVar17 = *puVar13;
          puVar13 = puVar13 + 1;
          puVar17 = puVar17 + 1;
        }
        for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(char *)puVar17 = (char)*puVar13;
          puVar13 = (uint *)((int)puVar13 + 1);
          puVar17 = (uint *)((int)puVar17 + 1);
        }
        puVar11[1] = uVar15;
        local_b0 = local_b0 + 1;
        puVar11 = puVar11 + 9;
      }
      local_b4 = local_b4 + 1;
      local_a4 = local_a4 + 1;
    } while ((int)local_b4 < 0x4c2150);
    qsort(&DAT_00540da8,local_b0,0x24,(_PtFuncCompare *)&LAB_004529f0);
  }
  iVar8 = multiplayer_chat_ui_context_helper_00452e10();
  if ((iVar8 == 0) || (DAT_00540da0 == 0)) {
    pcVar19 = s___Player_Name_Score_Kills_Deaths_004f5a08;
  }
  else {
    pcVar19 = s___Team_Name_Score_Kills_Deaths_004f5a30;
  }
  sprintf((char *)local_94,pcVar19);
  append_scrolling_text_widget_message(DAT_00609324,local_94);
  sVar12 = 0;
  local_b4 = (undefined **)0x1;
  if (0 < (int)local_b0) {
    puVar11 = &DAT_00540dc0;
    do {
      iVar8 = multiplayer_chat_ui_context_helper_00452e10();
      if ((iVar8 == 0) || (DAT_00540da0 == 0)) {
        bVar5 = is_local_multiplayer_sync_player_current();
        if ((CONCAT31(extraout_var,bVar5) == 0) || (sVar12 == local_a0)) {
          if (DAT_00540da0 != 0) goto LAB_00451e91;
          uVar15 = puVar11[1];
          uVar3 = *(ushort *)((int)puVar11 + 2);
          uVar4 = (ushort)*puVar11;
          uVar18 = 0x48;
          goto LAB_00451ed5;
        }
        sprintf((char *)local_94,s__1d___15s__6d__5d__5d_004f59f0,local_b4,puVar11 + -6,puVar11[1],
                (uint)(ushort)*puVar11,(uint)*(ushort *)((int)puVar11 + 2));
        local_b4 = (undefined **)((int)local_b4 + 1);
      }
      else {
LAB_00451e91:
        uVar15 = puVar11[1];
        uVar3 = *(ushort *)((int)puVar11 + 2);
        uVar4 = (ushort)*puVar11;
        uVar18 = 0x20;
LAB_00451ed5:
        sprintf((char *)local_94,s__1c___15s__6d__5d__5d_004f59d8,uVar18,puVar11 + -6,uVar15,
                (uint)uVar4,(uint)uVar3);
      }
      append_scrolling_text_widget_message(DAT_00609324,local_94);
      sVar12 = sVar12 + 1;
      puVar11 = puVar11 + 9;
    } while ((int)sVar12 < (int)local_b0);
  }
  return;
}


