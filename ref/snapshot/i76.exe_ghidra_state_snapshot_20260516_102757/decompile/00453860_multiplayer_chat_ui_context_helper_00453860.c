/*
 * Program: i76.exe
 * Function: multiplayer_chat_ui_context_helper_00453860
 * Entry: 00453860
 * Signature: undefined __stdcall multiplayer_chat_ui_context_helper_00453860(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v18: was multiplayer_network_multiplayer_chat_ui_helper_00453860. Remove
   duplicated multiplayer wording from readability label. */

void multiplayer_chat_ui_context_helper_00453860(void)

{
  _DAT_004f5aa8 = 0xbf800000;
  g_damage_side_effects_suppressed = 0;
  g_directplay_message_processing_enabled = 0;
  multiplayer_network_scoreboard_table_helper_00451960();
  multiplayer_player_table_context_helper_00455470();
  delete_network_vehicle_files();
  multiplayer_chat_ui_context_helper_00453f10();
  team_score_table_context_helper_00452910();
  network_vehicle_message_context_helper_00455dd0();
  multiplayer_prompt_context_helper_00455810();
  return;
}


