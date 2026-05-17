/*
 * Program: i76.exe
 * Function: is_ai_vehicle_close_and_slow_enough_for_behavior
 * Entry: 0041edb0
 * Signature: undefined4 __cdecl is_ai_vehicle_close_and_slow_enough_for_behavior(uint param_1, uint param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Checks vehicle speed and distance to target against
   close-range behavior thresholds. */

undefined4 __cdecl is_ai_vehicle_close_and_slow_enough_for_behavior(uint param_1,uint param_2)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  if ((*(float *)(iVar1 + 0xac) < _DAT_004bcb28) &&
     (fVar2 = (float10)world_object_geometry_context_helper_004589f0(param_1,param_2),
     fVar2 < (float10)_DAT_004bcb64)) {
    return 1;
  }
  return 0;
}


