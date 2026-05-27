/*
 * Program: i76.exe
 * Function: update_optional_vehicle_runtime_visual_state
 * Entry: 00463950
 * Signature: undefined __cdecl update_optional_vehicle_runtime_visual_state(int param_1)
 */


/* [cgpt i76.exe vehicle class physics rename v29; confidence=medium] Class-id 1 callback gated by
   optional runtime flag; updates two visual/runtime helpers for the vehicle object. */

void __cdecl update_optional_vehicle_runtime_visual_state(int param_1)

{
  int iVar1;
  
  iVar1 = world_object_has_optional_runtime_flag(param_1);
  if (iVar1 != 0) {
    initialize_speed_tach_needles(param_1);
    force_feedback_runtime_helper_00445ba0(param_1);
  }
  return;
}


