/*
 * Program: i76.exe
 * Function: fsm_set_active_player_vehicle_control_context
 * Entry: 0040bf90
 * Signature: undefined __cdecl fsm_set_active_player_vehicle_control_context(int * param_1)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action: when the global context id changes,
   updates the active player/camera vehicle control context. */

void __cdecl fsm_set_active_player_vehicle_control_context(int *param_1)

{
  int *piVar1;
  
  if (DAT_004c2ab0 != *param_1) {
    piVar1 = (int *)get_active_player_or_camera_world_object_entry();
    if (piVar1 != (int *)0x0) {
      radar_render_context_helper_00460ea0(*piVar1);
      DAT_004c2ab0 = *param_1;
    }
  }
  return;
}


