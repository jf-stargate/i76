/*
 * Program: i76.exe
 * Function: get_game_flow_state
 * Entry: 00402610
 * Signature: undefined4 __stdcall get_game_flow_state(void)
 */


/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Accessor returning g_game_flow_state.
    */

undefined4 get_game_flow_state(void)

{
  return g_game_flow_state;
}


