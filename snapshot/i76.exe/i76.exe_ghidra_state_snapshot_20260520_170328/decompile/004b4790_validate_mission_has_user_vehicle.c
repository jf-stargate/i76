/*
 * Program: i76.exe
 * Function: validate_mission_has_user_vehicle
 * Entry: 004b4790
 * Signature: undefined4 __stdcall validate_mission_has_user_vehicle(void)
 */


/* [cgpt i76.exe mission/runtime rename v14; confidence=high] Checks global/current world context
   for a user vehicle; reports 'No User vehicle in mission %s' on failure. */

undefined4 validate_mission_has_user_vehicle(void)

{
  int iVar1;
  
  iVar1 = mission_user_vehicle_allowed_by_damage_suppression();
  if (iVar1 == 0) {
    iVar1 = get_active_player_or_camera_world_object_entry();
    if (iVar1 == 0) {
      report_error();
    }
  }
  return 1;
}


