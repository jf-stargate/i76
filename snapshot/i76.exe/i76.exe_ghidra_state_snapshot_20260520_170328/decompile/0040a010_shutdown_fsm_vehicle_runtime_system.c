/*
 * Program: i76.exe
 * Function: shutdown_fsm_vehicle_runtime_system
 * Entry: 0040a010
 * Signature: undefined __stdcall shutdown_fsm_vehicle_runtime_system(void)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: Shuts down or resets FSM/vehicle runtime state after
   mission/user-vehicle checks and bridge/path cleanup. */

void shutdown_fsm_vehicle_runtime_system(void)

{
  int iVar1;
  
  initialize_bridge_and_road_validation_records();
  iVar1 = mission_user_vehicle_allowed_by_damage_suppression();
  if (iVar1 == 0) {
    initialize_active_player_ai_control_change_state();
    return;
  }
  return;
}


