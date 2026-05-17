/*
 * Program: i76.exe
 * Function: stamp_multiplayer_respawn_or_score_time
 * Entry: 00451560
 * Signature: undefined __stdcall stamp_multiplayer_respawn_or_score_time(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Stores current multiplayer/runtime seconds into the respawn/score timing global.
    */

void stamp_multiplayer_respawn_or_score_time(void)

{
  float10 fVar1;
  
  fVar1 = get_network_or_session_runtime_seconds();
  _DAT_0053fd7c = (float)fVar1;
  return;
}


