/*
 * Program: i76.exe
 * Function: write_player_score_table
 * Entry: 00452360
 * Signature: undefined __cdecl write_player_score_table(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: formats Player Name Score Kills Deaths */

void __cdecl write_player_score_table(int param_1)

{
  int iVar1;
  uchar local_50 [80];
  
  iVar1 = is_damage_side_effects_suppressed();
  if ((iVar1 != 0) && (DAT_00540ff0 != param_1)) {
    if (param_1 != 0) {
      iVar1 = multiplayer_chat_ui_context_helper_00452e10();
      if (iVar1 != 0) {
        _DAT_00540fe8 = 1;
        DAT_00540da0 = 1;
        multiplayer_chat_ui_context_helper_00453ef0(0);
        set_text_widget_visible_flag(DAT_00609324,1);
        _DAT_00540fe8 = 1;
        clear_scrolling_text_widget_buffer(DAT_00609324);
        iVar1 = is_network_or_trip_runtime_mode();
        if (iVar1 != 0) {
          copy_multiplayer_scoreboard_name_string((char *)&DAT_00540da8);
          get_multiplayer_score_accumulators(&DAT_00540dc4,(undefined2 *)&DAT_00540dc0);
          DAT_00540dc0 = DAT_00540dc0 & 0xffff;
          sprintf((char *)local_50,s_Player_Name_Score_Kills_Deaths_004f5a6c);
          append_scrolling_text_widget_message(DAT_00609324,local_50);
          sprintf((char *)local_50,s___15s__6d__4d__4d_004f5a58,&DAT_00540da8,DAT_00540dc4,
                  DAT_00540dc0 & 0xffff,DAT_00540dc0 >> 0x10);
          append_scrolling_text_widget_message(DAT_00609324,local_50);
          DAT_00540ff0 = param_1;
          return;
        }
        write_team_score_table();
        DAT_00540ff0 = param_1;
        return;
      }
    }
    _DAT_00540fe8 = 0;
    DAT_00540da0 = 0;
    multiplayer_chat_ui_context_helper_00453ef0(1);
    set_text_widget_visible_flag(DAT_00609324,0);
    _DAT_00540fe8 = 0;
    DAT_00540ff0 = param_1;
  }
  return;
}


