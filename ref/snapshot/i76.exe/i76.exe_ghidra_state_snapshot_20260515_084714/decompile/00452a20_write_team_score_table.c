/*
 * Program: i76.exe
 * Function: write_team_score_table
 * Entry: 00452a20
 * Signature: undefined __stdcall write_team_score_table(void)
 */


/* cgpt whole-binary semantic rename v1: formats team/player score report */

void write_team_score_table(void)

{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  bool bVar4;
  short sVar5;
  short sVar6;
  int iVar7;
  undefined3 extraout_var;
  uint uVar8;
  uint uVar9;
  int iVar10;
  short *psVar11;
  size_t sVar12;
  undefined2 *puVar13;
  ushort *puVar14;
  char *pcVar15;
  short *psVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  char *pcVar19;
  size_t local_70;
  uint local_6c;
  undefined **local_68;
  uint local_60;
  size_t local_5c;
  int local_58;
  ushort local_54 [2];
  uchar local_50 [80];
  
  local_58 = get_multiplayer_player_count_or_limit();
  iVar10 = 0;
  local_70 = 0;
  iVar7 = multiplayer_chat_ui_context_helper_00452e10();
  if ((iVar7 == 0) || (DAT_00540da0 == 0)) {
    clear_multiplayer_scoreboard_dirty_flag();
    puVar13 = (undefined2 *)((int)&DAT_00540dc0 + 2);
    local_70 = 0;
    do {
      sVar5 = get_multiplayer_player_record_and_copy_name(iVar10,(uchar *)(puVar13 + -0xd));
      if (sVar5 != 0) {
        lookup_multiplayer_player_vehicle_config_id(sVar5,(undefined4 *)local_54);
        sVar6 = get_local_multiplayer_player_id();
        sVar12 = local_70;
        if (sVar5 != sVar6) {
          if ((local_54[0] & 1) != 0) goto LAB_00452be8;
          append_multiplayer_team_score_slot(sVar5);
          sVar12 = local_5c;
        }
        local_5c = sVar12;
        get_multiplayer_player_spawn_score_fields
                  (sVar5,(undefined4 *)(puVar13 + 1),puVar13 + -1,puVar13);
        local_70 = local_70 + 1;
        puVar13 = puVar13 + 0x12;
        if (local_58 <= (int)local_70) break;
      }
LAB_00452be8:
      iVar10 = iVar10 + 1;
    } while (iVar10 < 0x10);
  }
  else {
    local_6c = 0;
    local_68 = &PTR_s_Grey_Hounds_004c2130;
    psVar11 = (short *)&DAT_00540dc0;
    do {
      iVar10 = 0;
      iVar7 = 0;
      bVar4 = false;
      if (psVar11 != (short *)0x0) {
        *psVar11 = 0;
      }
      if (psVar11 + 1 != (short *)0x0) {
        psVar11[1] = 0;
      }
      do {
        sVar5 = get_multiplayer_player_record_and_copy_name(iVar10,(uchar *)0x0);
        if ((sVar5 != 0) &&
           (lookup_multiplayer_player_vehicle_config_id(sVar5,&local_60),
           (local_60 >> 0x10 & 7) == local_6c)) {
          get_multiplayer_player_spawn_score_fields
                    (sVar5,&local_5c,(undefined2 *)&local_58,local_54);
          iVar7 = iVar7 + local_5c;
          if (psVar11 != (short *)0x0) {
            *psVar11 = *psVar11 + (short)local_58;
          }
          psVar16 = psVar11 + 1;
          if (psVar16 != (short *)0x0) {
            *psVar16 = *psVar16 + local_54[0];
          }
          bVar4 = true;
        }
        iVar10 = iVar10 + 1;
      } while (iVar10 < 0x10);
      if (!bVar4) {
        iVar7 = -1;
      }
      if (iVar7 != -1) {
        uVar8 = 0xffffffff;
        pcVar19 = *local_68;
        do {
          pcVar15 = pcVar19;
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          pcVar15 = pcVar19 + 1;
          cVar1 = *pcVar19;
          pcVar19 = pcVar15;
        } while (cVar1 != '\0');
        uVar8 = ~uVar8;
        pcVar19 = pcVar15 + -uVar8;
        psVar16 = psVar11 + -0xc;
        for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined4 *)psVar16 = *(undefined4 *)pcVar19;
          pcVar19 = pcVar19 + 4;
          psVar16 = psVar16 + 2;
        }
        for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(char *)psVar16 = *pcVar19;
          pcVar19 = pcVar19 + 1;
          psVar16 = (short *)((int)psVar16 + 1);
        }
        *(int *)(psVar11 + 2) = iVar7;
        local_70 = local_70 + 1;
        psVar11 = psVar11 + 0x12;
      }
      local_68 = local_68 + 1;
      local_6c = local_6c + 1;
    } while ((int)local_68 < 0x4c2150);
    qsort(&DAT_00540da8,local_70,0x24,(_PtFuncCompare *)&LAB_004529f0);
  }
  iVar7 = multiplayer_chat_ui_context_helper_00452e10();
  if ((iVar7 == 0) || (DAT_00540da0 == 0)) {
    pcVar19 = s___Player_Name_Score_Kills_Deaths_004f5a08;
  }
  else {
    pcVar19 = s___Team_Name_Score_Kills_Deaths_004f5a30;
  }
  sprintf((char *)local_50,pcVar19);
  append_scrolling_text_widget_message(DAT_00609324,local_50);
  sVar12 = 0;
  local_68 = (undefined **)0x1;
  if (0 < (int)local_70) {
    puVar14 = (ushort *)&DAT_00540dc0;
    do {
      iVar7 = multiplayer_chat_ui_context_helper_00452e10();
      if ((iVar7 == 0) || (DAT_00540da0 == 0)) {
        bVar4 = is_local_multiplayer_sync_player_current();
        if ((CONCAT31(extraout_var,bVar4) == 0) || (sVar12 == local_5c)) {
          if (DAT_00540da0 != 0) goto LAB_00452ca9;
          uVar18 = *(undefined4 *)(puVar14 + 2);
          uVar2 = puVar14[1];
          uVar3 = *puVar14;
          uVar17 = 0x48;
          goto LAB_00452ced;
        }
        sprintf((char *)local_50,s__1d___15s__6d__5d__5d_004f59f0,local_68,puVar14 + -0xc,
                *(undefined4 *)(puVar14 + 2),(uint)*puVar14,(uint)puVar14[1]);
        local_68 = (undefined **)((int)local_68 + 1);
      }
      else {
LAB_00452ca9:
        uVar18 = *(undefined4 *)(puVar14 + 2);
        uVar2 = puVar14[1];
        uVar3 = *puVar14;
        uVar17 = 0x20;
LAB_00452ced:
        sprintf((char *)local_50,s__1c___15s__6d__5d__5d_004f59d8,uVar17,puVar14 + -0xc,uVar18,
                (uint)uVar3,(uint)uVar2);
      }
      append_scrolling_text_widget_message(DAT_00609324,local_50);
      sVar12 = sVar12 + 1;
      puVar14 = puVar14 + 0x12;
    } while ((int)sVar12 < (int)local_70);
  }
  return;
}


