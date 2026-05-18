/*
 * Program: i76.exe
 * Function: kick_player_for_cheating
 * Entry: 00456ea0
 * Signature: undefined __cdecl kick_player_for_cheating(short param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: kicked out for cheating */

void __cdecl kick_player_for_cheating(short param_1,int *param_2)

{
  short sVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  float local_5c;
  float local_58;
  float local_54;
  uchar local_50 [80];
  
  sVar1 = get_multiplayer_message_source_player_id();
  if (sVar1 == param_1) {
    multiplayer_chat_widget_context_helper_00453ee0();
    multiplayer_chat_ui_context_helper_00453ef0(1);
    if (*param_2 == 1) {
      pcVar2 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                     s_____You_have_been_kicked_out_for_004f5c78);
      sprintf((char *)local_50,pcVar2);
    }
    clear_pending_input_action_code();
    iVar3 = get_active_player_or_camera_world_object_entry();
    if (iVar3 == 0) {
      uVar4 = get_spawn_location_or_report_missing();
      if (uVar4 != 0xffffffff) {
        pcVar2 = load_or_create_player_vehicle_entity
                           (CONCAT22(extraout_var,DAT_00541028),uVar4,0,(void *)0x0,0);
        local_5c = (float)*(double *)(pcVar2 + 0x40);
        local_58 = (float)*(double *)(pcVar2 + 0x48);
        local_54 = (float)*(double *)(pcVar2 + 0x50);
        chunk_manager_lookup_or_remove_entry(&local_5c,20.0);
      }
    }
    iVar3 = 0xfefe;
    uVar5 = get_active_player_or_camera_world_object_entry();
    dispatch_runtime_camera_mode_activation_by_id(uVar5,iVar3);
    weapon_hud_display_context_helper_004621b0();
    _DAT_0053679c = 8;
    draw_multiplayer_chat_message(0,local_50);
    dpDestroyPlayer(DAT_00541024,CONCAT22(extraout_var_00,DAT_00541028));
  }
  return;
}


