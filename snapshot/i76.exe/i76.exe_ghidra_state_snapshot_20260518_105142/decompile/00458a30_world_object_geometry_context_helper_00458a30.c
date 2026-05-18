/*
 * Program: i76.exe
 * Function: world_object_geometry_context_helper_00458a30
 * Entry: 00458a30
 * Signature: undefined __stdcall world_object_geometry_context_helper_00458a30(float param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was world_object_geometry_world_object_geometry_helper_00458a30.
   Remove duplicated world_object_geometry wording. */

void world_object_geometry_context_helper_00458a30(float param_1,float param_2)

{
  float fVar1;
  float fVar2;
  
  fVar1 = param_2 - param_1;
  if (param_2 < param_1) {
    fVar1 = fVar1 - _DAT_004bdfc8;
  }
  fVar2 = _DAT_004bdfd0;
  if (_DAT_004bdfcc < fVar1) {
    fVar2 = _DAT_004bdfcc;
  }
  floor((double)((fVar1 - fVar2) * _DAT_004bdfd4));
  ftol();
  return;
}


