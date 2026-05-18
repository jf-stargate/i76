/*
 * Program: i76.exe
 * Function: publish_local_player_vehicle_config_to_directplay
 * Entry: 00452e30
 * Signature: undefined4 __stdcall publish_local_player_vehicle_config_to_directplay(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe runtime loop refinement v23; confidence=MEDIUM_HIGH] Loads selected local player
   .vcf and publishes it as DirectPlay player data. */

undefined4 publish_local_player_vehicle_config_to_directplay(void)

{
  undefined4 in_EAX;
  undefined4 uVar1;
  int iVar2;
  uint *puVar3;
  undefined2 extraout_var;
  float10 fVar4;
  undefined8 uVar5;
  char *pcVar6;
  uint local_4;
  
  uVar1 = multiplayer_chat_ui_context_helper_004541b0
                    (CONCAT22((short)((uint)in_EAX >> 0x10),DAT_00541028));
  lookup_multiplayer_player_vehicle_config_id(DAT_00541028,&local_4);
  local_4 = local_4 | 1;
  multiplayer_player_record_lookup_helper_004546c0(DAT_00541028,local_4);
  pcVar6 = &s_dot_vcf;
  uVar5 = get_selected_mission_resource_stem8();
  pcVar6 = format_8char_resource_basename_with_suffix
                     ((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),pcVar6);
  iVar2 = get_loaded_resource_file_size(pcVar6);
  pcVar6 = &s_dot_vcf;
  uVar5 = get_selected_mission_resource_stem8();
  pcVar6 = format_8char_resource_basename_with_suffix
                     ((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),pcVar6);
  puVar3 = open_resource_file_into_memory(pcVar6);
  dpSetPlayerData(DAT_00541024,CONCAT22(extraout_var,DAT_00541028),0,puVar3,iVar2,0);
  pcVar6 = &s_dot_vcf;
  uVar5 = get_selected_mission_resource_stem8();
  pcVar6 = format_8char_resource_basename_with_suffix
                     ((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),pcVar6);
  release_resource_file_reference(pcVar6);
  update_runtime_clock_from_gettickcount();
  fVar4 = get_network_or_session_runtime_seconds();
  _DAT_00540ffc = (float)fVar4;
  fVar4 = get_network_or_session_runtime_seconds();
  _DAT_00541004 = (float)fVar4;
  DAT_0054102c = 0;
  return uVar1;
}


