/*
 * Program: i76.exe
 * Function: get_terrain_material_integer_scalar
 * Entry: 004927a0
 * Signature: float10 __cdecl get_terrain_material_integer_scalar(int param_1)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium] Accessor returning the
   integer field from a terrain/material table entry as a floating-point value. */

float10 __cdecl get_terrain_material_integer_scalar(int param_1)

{
  return (float10)*(int *)(&DAT_00644230 + param_1 * 0x14);
}


