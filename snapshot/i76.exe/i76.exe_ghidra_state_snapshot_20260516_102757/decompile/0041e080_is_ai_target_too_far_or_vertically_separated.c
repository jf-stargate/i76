/*
 * Program: i76.exe
 * Function: is_ai_target_too_far_or_vertically_separated
 * Entry: 0041e080
 * Signature: bool __cdecl is_ai_target_too_far_or_vertically_separated(uint param_1, uint param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Distance/vertical separation predicate for rejecting
   far or unsuitable targets. */

bool __cdecl is_ai_target_too_far_or_vertically_separated(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  float10 fVar3;
  
  if (*(int *)(param_1 + 0x6c) == 9) {
    fVar3 = (float10)world_object_geometry_context_helper_004589f0(param_1,param_2);
    bVar2 = (float10)_DAT_004bcb38 < fVar3;
  }
  else {
    iVar1 = is_vehicle_or_actor_runtime_world_object(param_2);
    if (iVar1 == 0) {
      fVar3 = (float10)world_object_geometry_context_helper_004589f0(param_1,param_2);
      bVar2 = (float10)_DAT_004bcb3c < fVar3;
    }
    else if (ABS(*(double *)(param_1 + 0x48) - *(double *)(param_2 + 0x48)) <= _DAT_004bcb40) {
      fVar3 = (float10)world_object_geometry_context_helper_00458a10(param_1,param_2);
      bVar2 = (float10)_DAT_004bcb48 < fVar3;
    }
    else {
      bVar2 = true;
    }
  }
  return bVar2;
}


