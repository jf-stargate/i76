/*
 * Program: i76.exe
 * Function: is_ai_target_close_while_vehicle_slow
 * Entry: 00416ed0
 * Signature: undefined4 __cdecl is_ai_target_close_while_vehicle_slow(uint param_1, uint param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Returns true when target vehicle speed is low and
   object distance is under 30. */

undefined4 __cdecl is_ai_target_close_while_vehicle_slow(uint param_1,uint param_2)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = get_vehicle_runtime_context(param_2);
  if (*(float *)(iVar1 + 0xac) < _DAT_004bc884) {
    fVar2 = (float10)world_object_geometry_context_helper_004589f0(param_1,param_2);
    if (fVar2 < (float10)_DAT_004bc8b0) {
      return 1;
    }
  }
  return 0;
}


