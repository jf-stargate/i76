/*
 * Program: i76.exe
 * Function: process_directplay_runtime_messages
 * Entry: 004532c0
 * Signature: undefined __stdcall process_directplay_runtime_messages(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Runtime DirectPlay receive/update
   loop. Handles join/leave/chat/state/position/score/timing message families and periodic
   send/flush behavior. */

void process_directplay_runtime_messages(void)

{
  bool bVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  float fVar7;
  undefined2 extraout_var_00;
  undefined3 extraout_var;
  float10 fVar8;
  uint local_284;
  float local_280;
  uint local_27c;
  undefined4 local_278;
  float local_274;
  int local_270;
  undefined1 local_26a [2];
  uchar local_268 [24];
  uchar local_250 [80];
  ushort local_200;
  char cStack_1fe;
  undefined1 uStack_1fd;
  short local_1fc;
  undefined2 uStack_1fa;
  float local_1f8;
  uchar local_1f4 [500];
  
  local_278 = 0x200;
  local_270 = 0;
  iVar4 = g_directplay_message_processing_enabled;
  if (g_directplay_message_processing_enabled == 0) {
    fVar8 = get_multiplayer_or_runtime_seconds();
    if (_DAT_004f5aa8 == _DAT_004bdf44) {
      _DAT_004f5aa8 = (float)fVar8;
      _DAT_00541038 = (float)fVar8;
    }
    iVar4 = 1;
    if (fVar8 - (float10)_DAT_004f5aa8 <= (float10)_DAT_004bdf54) {
      iVar4 = multiplayer_sync_player_context_helper_00454e60();
    }
  }
  while (g_directplay_message_processing_enabled = iVar4, DAT_00609320 == 0) {
    iVar4 = 0;
    do {
      local_278 = 0x200;
      iVar5 = dpReceive(DAT_00541024,&local_284,local_26a,0,&local_200,&local_278);
      local_278 = 0x200;
      if (iVar5 != 2) break;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 3);
    if (iVar5 != 0) break;
    iVar4 = g_directplay_message_processing_enabled;
    if ((short)local_284 == 0) {
      if (local_200 == 0x3164) {
        multiplayer_chat_ui_context_helper_004541b0
                  (CONCAT22(local_1fc,CONCAT11(uStack_1fd,cStack_1fe)));
        lookup_multiplayer_player_vehicle_config_id(CONCAT11(uStack_1fd,cStack_1fe),&local_27c);
        local_27c = local_27c | 1;
        multiplayer_player_record_lookup_helper_004546c0(CONCAT11(uStack_1fd,cStack_1fe),local_27c);
        iVar4 = g_directplay_message_processing_enabled;
      }
      else if (local_200 == 0x3264) {
        if (CONCAT11(uStack_1fd,cStack_1fe) == DAT_00541028) {
          DAT_00609320 = 1;
        }
        else {
          iVar5 = multiplayer_player_count_context_helper_00454620
                            (CONCAT11(uStack_1fd,cStack_1fe),local_268);
          iVar4 = g_directplay_message_processing_enabled;
          if (iVar5 != 0) {
            lookup_multiplayer_player_vehicle_config_id(CONCAT11(uStack_1fd,cStack_1fe),&local_27c);
            if ((local_27c & 1) == 0) {
              pcVar6 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                             s______s_has_left_the_game_004f5aac,local_268);
              sprintf((char *)local_250,pcVar6);
              draw_multiplayer_chat_message(0,local_250);
            }
            notify_local_player_became_host(CONCAT11(uStack_1fd,cStack_1fe));
            iVar4 = g_directplay_message_processing_enabled;
          }
        }
      }
      else if ((local_200 == 0x3564) &&
              (sVar2 = get_multiplayer_mission_sync_player_id(),
              iVar4 = g_directplay_message_processing_enabled,
              CONCAT11(uStack_1fd,cStack_1fe) == sVar2)) {
        lookup_multiplayer_player_vehicle_config_id(local_1fc,&local_280);
        local_280 = (float)((uint)local_280 & 0xfffffffe);
        multiplayer_player_record_lookup_helper_004546c0(local_1fc,local_280);
        multiplayer_player_count_context_helper_00454620(local_1fc,local_268);
        pcVar6 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                       s______s_has_joined_the_game_004f5ac8,local_268);
        sprintf((char *)local_250,pcVar6);
        draw_multiplayer_chat_message(0,local_250);
        iVar4 = g_directplay_message_processing_enabled;
      }
    }
    else if (((local_200 & 0x8000) == 0) &&
            (multiplayer_host_migration_context_helper_00454840((short)local_284),
            iVar4 = g_directplay_message_processing_enabled, cStack_1fe != '\x02')) {
      is_local_multiplayer_sync_player_current();
      sVar2 = (short)local_284;
      iVar4 = g_directplay_message_processing_enabled;
      if (local_200 < 0x4553) {
        if (local_200 == 0x4552) {
          network_vehicle_message_context_helper_004568f0(local_284,(int *)&local_1f8);
          iVar4 = g_directplay_message_processing_enabled;
        }
        else if (local_200 == 0x4353) {
          fsm_or_mission_logic_helper_b(sVar2,(uint *)&local_1f8);
          iVar4 = g_directplay_message_processing_enabled;
        }
      }
      else if (local_200 < 0x4854) {
        if (local_200 == 0x4853) {
          multiplayer_network_network_vehicle_message_helper_00456d70(sVar2,(uint *)&local_1f8);
          iVar4 = g_directplay_message_processing_enabled;
        }
        else if (local_200 == 0x4843) {
          draw_multiplayer_chat_message(sVar2,local_1f4);
          iVar4 = g_directplay_message_processing_enabled;
        }
      }
      else if (local_200 < 0x5054) {
        if (local_200 == 0x5053) {
          handle_network_vehicle_spawn_or_update_record(sVar2,(short *)&local_1f8);
          iVar4 = g_directplay_message_processing_enabled;
        }
        else if (local_200 == 0x4f42) {
          kick_player_for_cheating(sVar2,(int *)&local_1f8);
          iVar4 = g_directplay_message_processing_enabled;
        }
      }
      else if (local_200 < 0x5454) {
        if (local_200 == 0x5453) {
          network_vehicle_spawn_update_context_helper_00456c10(local_284,&local_1f8);
          iVar4 = g_directplay_message_processing_enabled;
        }
        else if (local_200 == 0x5253) {
          report_no_valid_spawn_location(local_284,(uint *)&local_1f8);
          iVar4 = g_directplay_message_processing_enabled;
        }
      }
      else if (local_200 == 0x5858) {
        network_vehicle_message_context_helper_004568b0(local_284);
        sVar2 = get_multiplayer_message_source_player_id();
        if (sVar2 == (short)local_284) {
          mission_flow_map_context_helper_0049c8d0
                    (local_1f8,(uint)(DAT_0054102c != (short)local_284));
          DAT_0054102c = (short)local_284;
        }
        network_vehicle_message_context_helper_00456490(local_284,CONCAT22(uStack_1fa,local_1fc));
        iVar4 = g_directplay_message_processing_enabled;
      }
      else if (local_200 == 0x5959) {
        local_274 = (float)CONCAT22(uStack_1fa,local_1fc);
        fVar8 = get_multiplayer_or_runtime_seconds();
        notify_remote_player_became_host
                  ((ushort)local_284,(float)((fVar8 - (float10)local_274) * (float10)_DAT_004bdf58))
        ;
        iVar4 = g_directplay_message_processing_enabled;
      }
    }
  }
  if (g_directplay_message_processing_enabled != 0) {
    if (_DAT_00541014 == _DAT_004bdf44) {
      fVar8 = get_multiplayer_or_runtime_seconds();
      _DAT_00541014 = (float)fVar8;
    }
    fVar7 = (float)get_multiplayer_player_count_or_limit();
    iVar4 = 0;
    local_280 = 0.0;
    local_274 = fVar7;
    if (0 < (int)fVar7) {
      do {
        sVar2 = get_multiplayer_player_record_and_copy_name(iVar4,(uchar *)0x0);
        fVar8 = multiplayer_host_notice_context_helper_00454bc0(sVar2);
        iVar4 = iVar4 + 1;
        local_280 = (float)(fVar8 + (float10)local_280);
      } while (iVar4 < (int)fVar7);
    }
    local_280 = local_280 / ((float)(int)local_274 * _DAT_004bdf4c);
    if (local_280 < _DAT_004bdf50) {
      local_280 = 0.2;
    }
    if (_DAT_004bdf58 < local_280) {
      local_280 = 0.5;
    }
    fVar8 = get_multiplayer_or_runtime_seconds();
    iVar4 = local_270;
    if ((float10)local_280 <= fVar8 - (float10)_DAT_00541014) {
      network_vehicle_message_context_helper_00456320();
      _DAT_00541014 = local_280 + _DAT_00541014;
      iVar4 = 1;
    }
    iVar5 = network_vehicle_message_context_helper_004568a0();
    if ((iVar5 != 0) && (iVar4 == 0)) {
      uVar3 = get_multiplayer_mission_sync_player_id();
      network_vehicle_message_context_helper_00456760(CONCAT22(extraout_var_00,uVar3));
    }
    if ((g_player_weapon_status_bitmask & 0xfffffff) != 0) {
      network_vehicle_message_context_helper_004563a0
                (g_player_weapon_status_bitmask,(undefined4 *)&g_player_secondary_target_status_a,
                 g_player_primary_target_status);
    }
    multiplayer_player_table_context_helper_00455230();
    bVar1 = is_local_multiplayer_sync_player_current();
    if (((CONCAT31(extraout_var,bVar1) != 0) && (DAT_00541018 == 0)) &&
       (iVar4 = multiplayer_prompt_context_helper_00455800(), iVar4 == 0)) {
      prompt_allow_player_join_game();
    }
  }
  format_checkpoint_points_status();
  return;
}


