/*
 * Program: i76.exe
 * Function: get_active_player_or_camera_world_object_entry
 * Entry: 00457530
 * Signature: undefined4 __stdcall get_active_player_or_camera_world_object_entry(void)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=high] Returns active player/camera
   world-object entry global. */

undefined4 get_active_player_or_camera_world_object_entry(void)

{
  return g_active_player_or_camera_world_object_entry;
}


