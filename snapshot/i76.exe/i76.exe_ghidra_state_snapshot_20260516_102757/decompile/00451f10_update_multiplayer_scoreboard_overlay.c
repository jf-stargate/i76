/*
 * Program: i76.exe
 * Function: update_multiplayer_scoreboard_overlay
 * Entry: 00451f10
 * Signature: undefined __stdcall update_multiplayer_scoreboard_overlay(void)
 */


/* [cgpt i76.exe runtime loop refinement v23; confidence=MEDIUM_HIGH] Aggregates player
   score/kills/deaths and updates or draws multiplayer scoreboard overlay rows. */

void update_multiplayer_scoreboard_overlay(void)

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
  int iVar11;
  uint *puVar12;
  size_t sVar13;
  uint *puVar14;
  undefined2 *puVar15;
  uint uVar16;
  char *pcVar17;
  uint *puVar18;
  undefined4 uVar19;
  char *pcVar20;
  size_t local_70;
  uint local_6c;
  undefined **local_68;
  uint local_60;
  size_t local_5c;
  int local_58;
  ushort local_54 [2];
  uchar local_50 [80];
  
  clear_scrolling_text_widget_buffer(DAT_00609324);
  iVar8 = is_network_or_trip_runtime_mode();
  if (iVar8 != 0) {
    copy_multiplayer_scoreboard_name_string((char *)&DAT_00540da8);
    get_multiplayer_score_accumulators(&DAT_00540dc4,(undefined2 *)&DAT_00540dc0);
    DAT_00540dc0 = DAT_00540dc0 & 0xffff;
    sprintf((char *)local_50,s_Player_Name_Score_Kills_Deaths_004f5a6c);
    append_scrolling_text_widget_message(DAT_00609324,local_50);
    sprintf((char *)local_50,s___15s__6d__4d__4d_004f5a58,&DAT_00540da8,DAT_00540dc4,
            DAT_00540dc0 & 0xffff,DAT_00540dc0 >> 0x10);
    append_scrolling_text_widget_message(DAT_00609324,local_50);
    return;
  }
  local_58 = get_multiplayer_player_count_or_limit();
  iVar11 = 0;
  local_70 = 0;
  iVar8 = multiplayer_chat_ui_context_helper_00452e10();
  if ((iVar8 == 0) || (DAT_00540da0 == 0)) {
    clear_multiplayer_scoreboard_dirty_flag();
    puVar15 = (undefined2 *)((int)&DAT_00540dc0 + 2);
    local_70 = 0;
    do {
      sVar6 = get_multiplayer_player_record_and_copy_name(iVar11,(uchar *)(puVar15 + -0xd));
      if (sVar6 != 0) {
        lookup_multiplayer_player_vehicle_config_id(sVar6,(undefined4 *)local_54);
        sVar7 = get_local_multiplayer_player_id();
        sVar13 = local_70;
        if (sVar6 != sVar7) {
          if ((local_54[0] & 1) != 0) goto LAB_0045218f;
          append_multiplayer_team_score_slot(sVar6);
          sVar13 = local_5c;
        }
        local_5c = sVar13;
        get_multiplayer_player_spawn_score_fields
                  (sVar6,(undefined4 *)(puVar15 + 1),puVar15 + -1,puVar15);
        local_70 = local_70 + 1;
        puVar15 = puVar15 + 0x12;
        if (local_58 <= (int)local_70) break;
      }
LAB_0045218f:
      iVar11 = iVar11 + 1;
    } while (iVar11 < 0x10);
  }
  else {
    local_6c = 0;
    local_68 = &PTR_s_Grey_Hounds_004c2130;
    puVar12 = &DAT_00540dc0;
    do {
      iVar8 = 0;
      uVar16 = 0;
      bVar5 = false;
      if (puVar12 != (uint *)0x0) {
        *(short *)puVar12 = 0;
      }
      if ((short *)((int)puVar12 + 2) != (short *)0x0) {
        *(short *)((int)puVar12 + 2) = 0;
      }
      do {
        sVar6 = get_multiplayer_player_record_and_copy_name(iVar8,(uchar *)0x0);
        if ((sVar6 != 0) &&
           (lookup_multiplayer_player_vehicle_config_id(sVar6,&local_60),
           (local_60 >> 0x10 & 7) == local_6c)) {
          get_multiplayer_player_spawn_score_fields
                    (sVar6,&local_5c,(undefined2 *)&local_58,local_54);
          uVar16 = uVar16 + local_5c;
          if (puVar12 != (uint *)0x0) {
            *(short *)puVar12 = (short)*puVar12 + (short)local_58;
          }
          psVar1 = (short *)((int)puVar12 + 2);
          if (psVar1 != (short *)0x0) {
            *psVar1 = *psVar1 + local_54[0];
          }
          bVar5 = true;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < 0x10);
      if (!bVar5) {
        uVar16 = 0xffffffff;
      }
      if (uVar16 != 0xffffffff) {
        uVar9 = 0xffffffff;
        pcVar20 = *local_68;
        do {
          pcVar17 = pcVar20;
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          pcVar17 = pcVar20 + 1;
          cVar2 = *pcVar20;
          pcVar20 = pcVar17;
        } while (cVar2 != '\0');
        uVar9 = ~uVar9;
        puVar14 = (uint *)(pcVar17 + -uVar9);
        puVar18 = puVar12 + -6;
        for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *puVar18 = *puVar14;
          puVar14 = puVar14 + 1;
          puVar18 = puVar18 + 1;
        }
        for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(char *)puVar18 = (char)*puVar14;
          puVar14 = (uint *)((int)puVar14 + 1);
          puVar18 = (uint *)((int)puVar18 + 1);
        }
        puVar12[1] = uVar16;
        local_70 = local_70 + 1;
        puVar12 = puVar12 + 9;
      }
      local_68 = local_68 + 1;
      local_6c = local_6c + 1;
    } while ((int)local_68 < 0x4c2150);
    qsort(&DAT_00540da8,local_70,0x24,(_PtFuncCompare *)&LAB_004529f0);
  }
  iVar8 = multiplayer_chat_ui_context_helper_00452e10();
  if ((iVar8 == 0) || (DAT_00540da0 == 0)) {
    pcVar20 = s___Player_Name_Score_Kills_Deaths_004f5a08;
  }
  else {
    pcVar20 = s___Team_Name_Score_Kills_Deaths_004f5a30;
  }
  sprintf((char *)local_50,pcVar20);
  append_scrolling_text_widget_message(DAT_00609324,local_50);
  sVar13 = 0;
  local_68 = (undefined **)0x1;
  if (0 < (int)local_70) {
    puVar12 = &DAT_00540dc0;
    do {
      iVar8 = multiplayer_chat_ui_context_helper_00452e10();
      if ((iVar8 == 0) || (DAT_00540da0 == 0)) {
        bVar5 = is_local_multiplayer_sync_player_current();
        if ((CONCAT31(extraout_var,bVar5) == 0) || (sVar13 == local_5c)) {
          if (DAT_00540da0 != 0) goto LAB_00452250;
          uVar16 = puVar12[1];
          uVar3 = *(ushort *)((int)puVar12 + 2);
          uVar4 = (ushort)*puVar12;
          uVar19 = 0x48;
          goto LAB_00452294;
        }
        sprintf((char *)local_50,s__1d___15s__6d__5d__5d_004f59f0,local_68,puVar12 + -6,puVar12[1],
                (uint)(ushort)*puVar12,(uint)*(ushort *)((int)puVar12 + 2));
        local_68 = (undefined **)((int)local_68 + 1);
      }
      else {
LAB_00452250:
        uVar16 = puVar12[1];
        uVar3 = *(ushort *)((int)puVar12 + 2);
        uVar4 = (ushort)*puVar12;
        uVar19 = 0x20;
LAB_00452294:
        sprintf((char *)local_50,s__1c___15s__6d__5d__5d_004f59d8,uVar19,puVar12 + -6,uVar16,
                (uint)uVar4,(uint)uVar3);
      }
      append_scrolling_text_widget_message(DAT_00609324,local_50);
      sVar13 = sVar13 + 1;
      puVar12 = puVar12 + 9;
    } while ((int)sVar13 < (int)local_70);
  }
  return;
}


