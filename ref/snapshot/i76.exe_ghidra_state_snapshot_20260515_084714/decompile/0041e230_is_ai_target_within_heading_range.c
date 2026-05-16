/*
 * Program: i76.exe
 * Function: is_ai_target_within_heading_range
 * Entry: 0041e230
 * Signature: bool __cdecl is_ai_target_within_heading_range(uint param_1, uint param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Returns whether target heading/range is within the
   allowed threshold for the object type. */

bool __cdecl is_ai_target_within_heading_range(uint param_1,uint param_2)

{
  bool bVar1;
  float10 fVar2;
  
  if (*(int *)(param_1 + 0x6c) == 9) {
    fVar2 = (float10)world_object_geometry_context_helper_00458a10(param_1,param_2);
    bVar1 = (float10)_DAT_004bcb38 < fVar2;
  }
  else {
    fVar2 = (float10)world_object_geometry_context_helper_00458a10(param_1,param_2);
    bVar1 = (float10)_DAT_004bcb48 < fVar2;
  }
  return !bVar1;
}


