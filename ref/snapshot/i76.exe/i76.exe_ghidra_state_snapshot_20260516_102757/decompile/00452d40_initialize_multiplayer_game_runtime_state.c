/*
 * Program: i76.exe
 * Function: initialize_multiplayer_game_runtime_state
 * Entry: 00452d40
 * Signature: undefined __stdcall initialize_multiplayer_game_runtime_state(undefined4 param_1, undefined2 param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v4: Initializes multiplayer runtime state, disables damage side effects, registers
   network vehicle state, and initializes chat/join/vote/scoreboard UI. */

void initialize_multiplayer_game_runtime_state(undefined4 param_1,undefined2 param_2)

{
  g_damage_side_effects_suppressed = 1;
  g_directplay_message_processing_enabled = 0;
  _DAT_004f5aa8 = 0xbf800000;
  _DAT_00541014 = 0xbf800000;
  DAT_00609320 = 0;
  DAT_00541024 = param_1;
  DAT_00541028 = param_2;
  DAT_00541000 = 0;
  initialize_multiplayer_runtime_player_state();
  multiplayer_chat_message_queue_helper_00454090();
  network_vehicle_message_context_helper_004566a0();
  register_network_vehicle_file();
  initialize_multiplayer_chat_font();
  write_multiplayer_scoreboard_report();
  initialize_multiplayer_join_prompt_font();
  initialize_multiplayer_vote_prompt_font();
  return;
}


