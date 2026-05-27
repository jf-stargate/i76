/*
 * Program: i76.exe
 * Function: accumulate_multiplayer_score_distance_from_active_vehicle
 * Entry: 00401280
 * Signature: undefined __stdcall accumulate_multiplayer_score_distance_from_active_vehicle(void)
 */


/* cgpt rename v3: Increments a multiplayer/scoreboard accumulator using the active player/camera
   object and refreshes the multiplayer scoreboard overlay. */

void accumulate_multiplayer_score_distance_from_active_vehicle(void)

{
  int iVar1;
  
  g_mp_score_1 = g_mp_score_1 + 1;
  iVar1 = get_active_player_or_camera_world_object_entry();
  if (iVar1 != 0) {
    iVar1 = ftol();
    g_mp_score_0 = g_mp_score_0 + iVar1;
    update_multiplayer_scoreboard_overlay();
    return;
  }
  return;
}


