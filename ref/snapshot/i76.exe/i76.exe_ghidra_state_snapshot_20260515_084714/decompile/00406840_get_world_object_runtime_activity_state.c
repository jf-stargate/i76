/*
 * Program: i76.exe
 * Function: get_world_object_runtime_activity_state
 * Entry: 00406840
 * Signature: undefined4 __cdecl get_world_object_runtime_activity_state(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium] Object runtime/activity
   predicate used by the vehicle frame callback with threshold 25.0; result 2 enables direct update
   path. */

undefined4 __cdecl get_world_object_runtime_activity_state(int param_1,float param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = (float)*(double *)(param_1 + 0x40) - (float)_DAT_004c2890;
  fVar3 = (float)*(double *)(param_1 + 0x48) - (float)_DAT_004c2898;
  fVar2 = (float)*(double *)(param_1 + 0x50) - (float)_DAT_004c28a0;
  fVar1 = fVar2 * fVar2 + fVar3 * fVar3 + fVar1 * fVar1;
  if ((param_2 + DAT_004c2748) * (param_2 + DAT_004c2748) < fVar1) {
    return 2;
  }
  if ((param_2 + _DAT_004c2744) * (param_2 + _DAT_004c2744) < fVar1) {
    return 1;
  }
  return 0;
}


