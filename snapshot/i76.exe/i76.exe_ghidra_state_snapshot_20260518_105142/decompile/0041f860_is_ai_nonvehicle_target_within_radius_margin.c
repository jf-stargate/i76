/*
 * Program: i76.exe
 * Function: is_ai_nonvehicle_target_within_radius_margin
 * Entry: 0041f860
 * Signature: bool __cdecl is_ai_nonvehicle_target_within_radius_margin(uint param_1, uint param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Checks non-vehicle target distance against target
   radius plus margin. */

bool __cdecl is_ai_nonvehicle_target_within_radius_margin(uint param_1,uint param_2)

{
  float fVar1;
  bool bVar2;
  int iVar3;
  float10 fVar4;
  
  iVar3 = is_vehicle_or_actor_runtime_world_object(param_2);
  if (iVar3 == 0) {
    if ((param_2 != 0) && (*(int *)(param_2 + 0x5c) == 0)) {
      param_2 = *(uint *)(param_2 + 100);
    }
    if (param_2 == 0) {
      bVar2 = false;
    }
    else {
      fVar1 = *(float *)(param_2 + 0x90) + _DAT_004bcb2c;
      fVar4 = (float10)world_object_geometry_context_helper_004589f0(param_1,param_2);
      bVar2 = fVar4 < (float10)fVar1;
    }
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}


