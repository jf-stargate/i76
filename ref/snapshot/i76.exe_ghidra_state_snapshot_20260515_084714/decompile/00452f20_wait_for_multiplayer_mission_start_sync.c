/*
 * Program: i76.exe
 * Function: wait_for_multiplayer_mission_start_sync
 * Entry: 00452f20
 * Signature: undefined4 __stdcall wait_for_multiplayer_mission_start_sync(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Pre-runtime DirectPlay
   synchronization loop waiting for mission/session start messages and local player readiness. */

undefined4 wait_for_multiplayer_mission_start_sync(void)

{
  short sVar1;
  ushort uVar2;
  undefined2 uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  float10 fVar7;
  undefined8 uVar8;
  undefined4 uVar9;
  uint local_214;
  uint local_210;
  uint local_20c;
  uint local_208;
  undefined1 local_202 [2];
  ushort local_200;
  char cStack_1fe;
  undefined1 uStack_1fd;
  short local_1fc;
  float local_1f8 [126];
  
  local_20c = 0x200;
joined_r0x00452f3a:
  do {
    if (DAT_00609320 != 0) {
LAB_0045318c:
      fVar7 = get_multiplayer_or_runtime_seconds();
      if (fVar7 - (float10)_DAT_00540ffc < (float10)_DAT_004bdf48) {
        fVar7 = get_multiplayer_or_runtime_seconds();
        if (((float10)_DAT_004bdf4c <= fVar7 - (float10)_DAT_00540ffc) &&
           (fVar7 = get_multiplayer_or_runtime_seconds(),
           (float10)_DAT_004bdf50 <= fVar7 - (float10)_DAT_00541004)) {
          network_vehicle_message_context_helper_004564e0();
          fVar7 = get_multiplayer_or_runtime_seconds();
          _DAT_00541004 = (float)fVar7;
        }
        return 0;
      }
      DAT_0054102c = DAT_00541028;
      broadcast_host_migration_notice(DAT_00541028);
      uVar9 = 0;
      uVar8 = get_selected_mission_resource_stem8();
      fsm_or_mission_logic_helper_a((int)uVar8,(int)((ulonglong)uVar8 >> 0x20),uVar9);
      goto LAB_004531d8;
    }
    iVar6 = 0;
    do {
      local_20c = 0x200;
      iVar4 = dpReceive(DAT_00541024,&local_210,local_202,0,&local_200,&local_20c);
      local_20c = 0x200;
      if (iVar4 != 2) break;
      iVar6 = iVar6 + 1;
    } while (iVar6 < 3);
    if (iVar4 != 0) goto LAB_0045318c;
    if ((short)local_210 == 0) {
      if (local_200 < 0x3265) {
        if (local_200 == 0x3264) {
          if (CONCAT11(uStack_1fd,cStack_1fe) == DAT_00541028) {
            DAT_00609320 = 1;
          }
          else {
            iVar6 = multiplayer_player_count_context_helper_00454620
                              (CONCAT11(uStack_1fd,cStack_1fe),(uchar *)0x0);
            if (iVar6 != 0) {
              notify_local_player_became_host(CONCAT11(uStack_1fd,cStack_1fe));
            }
          }
        }
        else if (local_200 == 0x3164) {
          multiplayer_chat_ui_context_helper_004541b0
                    (CONCAT22(local_1fc,CONCAT11(uStack_1fd,cStack_1fe)));
          lookup_multiplayer_player_vehicle_config_id(CONCAT11(uStack_1fd,cStack_1fe),&local_214);
          local_214 = local_214 | 1;
          multiplayer_player_record_lookup_helper_004546c0
                    (CONCAT11(uStack_1fd,cStack_1fe),local_214);
        }
      }
      else if (local_200 == 0x3364) {
        set_multiplayer_mission_sync_player_id(CONCAT11(uStack_1fd,cStack_1fe));
      }
      else if ((local_200 == 0x3564) &&
              (sVar1 = get_multiplayer_mission_sync_player_id(),
              CONCAT11(uStack_1fd,cStack_1fe) == sVar1)) {
        lookup_multiplayer_player_vehicle_config_id(local_1fc,&local_208);
        local_208 = local_208 & 0xfffffffe;
        multiplayer_player_record_lookup_helper_004546c0(local_1fc,local_208);
      }
      goto joined_r0x00452f3a;
    }
    multiplayer_host_migration_context_helper_00454840((short)local_210);
  } while (cStack_1fe == '\x02');
  if (local_200 < 0x5054) {
    if (local_200 == 0x5053) {
      handle_network_vehicle_spawn_or_update_record((ushort)local_210,(short *)local_1f8);
      if (local_1f8[0]._0_2_ == DAT_00541028) {
        uVar2 = (ushort)local_210;
        if ((DAT_0054102c != uVar2) && (uVar2 < DAT_00541028)) {
          DAT_0054102c = uVar2;
          broadcast_host_migration_notice(uVar2);
        }
LAB_004531d8:
        notify_remote_player_became_host(DAT_00541028,0.0);
        lookup_multiplayer_player_vehicle_config_id(DAT_00541028,&local_214);
        local_214 = local_214 & 0xfffffffe;
        multiplayer_player_record_lookup_helper_004546c0(DAT_00541028,local_214);
        uVar5 = (uint)DAT_00541028;
        uVar3 = get_multiplayer_mission_sync_player_id();
        dpAddPlayerToGroup(DAT_00541024,uVar3,uVar5);
        return 1;
      }
    }
    else if (local_200 == 0x4353) {
      fsm_or_mission_logic_helper_b((ushort)local_210,(uint *)local_1f8);
    }
    goto joined_r0x00452f3a;
  }
  if (local_200 == 0x5858) {
    network_vehicle_message_context_helper_004568b0(local_210);
    if ((cStack_1fe == '\x04') && (uVar2 = (ushort)local_210, DAT_0054102c != uVar2)) {
      DAT_0054102c = uVar2;
      broadcast_host_migration_notice(uVar2);
      uVar9 = 0;
      uVar8 = get_selected_mission_resource_stem8();
      fsm_or_mission_logic_helper_a((int)uVar8,(int)((ulonglong)uVar8 >> 0x20),uVar9);
      mission_flow_map_context_helper_0049c8d0(local_1f8[0],1);
    }
  }
  else if ((local_200 != 0xcc43) || (DAT_00541028 <= (ushort)local_210)) goto joined_r0x00452f3a;
  fVar7 = get_multiplayer_or_runtime_seconds();
  _DAT_00540ffc = (float)fVar7;
  goto joined_r0x00452f3a;
}


