/*
 * Program: i76.exe
 * Function: set_game_flow_state
 * Entry: 00402620
 * Signature: undefined __cdecl set_game_flow_state(undefined4 param_1)
 */


/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Setter for g_game_flow_state. */

void __cdecl set_game_flow_state(undefined4 param_1)

{
  g_game_flow_state = param_1;
  return;
}


