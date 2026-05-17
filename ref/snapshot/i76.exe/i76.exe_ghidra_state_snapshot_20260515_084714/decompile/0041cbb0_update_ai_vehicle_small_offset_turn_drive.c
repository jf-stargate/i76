/*
 * Program: i76.exe
 * Function: update_ai_vehicle_small_offset_turn_drive
 * Entry: 0041cbb0
 * Signature: undefined __cdecl update_ai_vehicle_small_offset_turn_drive(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Applies constant drive speed and steering offset
   relative to current heading. */

void __cdecl update_ai_vehicle_small_offset_turn_drive(float param_1)

{
  float10 fVar1;
  
  get_vehicle_runtime_context((int)param_1);
  set_ai_vehicle_throttle_brake_toward_speed(param_1,10.0);
  fVar1 = (float10)world_object_geometry_context_helper_00458920((int)param_1);
  update_ai_vehicle_steering_control((int)param_1,(float)(fVar1 + (float10)_DAT_004bcae4));
  return;
}


