/*
 * Program: i76.exe
 * Function: get_ai_vehicle_damage_state_speed_scalar
 * Entry: 0040f990
 * Signature: float10 __cdecl get_ai_vehicle_damage_state_speed_scalar(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v11 astar/ai/fsm-loader cluster: Returns the computed AI/vehicle damage-state speed
   scalar, or a fixed value for object class 9. */

float10 __cdecl get_ai_vehicle_damage_state_speed_scalar(int param_1)

{
  if (*(int *)(param_1 + 0x6c) == 9) {
    return (float10)_DAT_004bc73c;
  }
  return (float10)*(float *)(*(int *)(*(int *)(param_1 + 0x70) + 0x108) + 0xa994);
}


