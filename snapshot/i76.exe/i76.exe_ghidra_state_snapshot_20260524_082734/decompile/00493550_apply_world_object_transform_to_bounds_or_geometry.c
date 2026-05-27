/*
 * Program: i76.exe
 * Function: apply_world_object_transform_to_bounds_or_geometry
 * Entry: 00493550
 * Signature: uint __cdecl apply_world_object_transform_to_bounds_or_geometry(double param_1, double param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [i76 level/static/material baseline v48]
   name: apply_world_object_transform_to_bounds_or_geometry
   confidence: medium
   module: world_object_transform
   Applies world-object transform to geometry/bounds. Relevant to ODEF/LDEF object placement and
   static SDF/SGEO hierarchy validation.
   note: Name already matches baseline. */

uint __cdecl apply_world_object_transform_to_bounds_or_geometry(double param_1,double param_2)

{
  undefined2 in_FPUControlWord;
  uint local_20;
  uint local_18;
  
  local_18 = SUB84((double)(_DAT_006442c4 * (float)param_1 + (float)_DAT_004faf18),0);
  local_20 = SUB84((double)(_DAT_006442c4 * (float)param_2 + (float)_DAT_004faf18),0);
  if (((0x2800 - local_20 | 0x2800 - local_18 | local_20 | local_18) & 0x80000000) != 0) {
    return local_20;
  }
  return CONCAT22((short)((ulonglong)(longlong)ROUND(_DAT_006442c4 * (float)param_1) >> 0x10),
                  in_FPUControlWord) & 0xfffff3ff | 0x400;
}


