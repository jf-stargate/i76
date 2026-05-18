/*
 * Program: i76.exe
 * Function: get_terrain_material_primary_scalar
 * Entry: 00492780
 * Signature: float10 __cdecl get_terrain_material_primary_scalar(int param_1)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium] Accessor for the first
   float in the 5-field terrain/material table entry. */

float10 __cdecl get_terrain_material_primary_scalar(int param_1)

{
  return (float10)(float)(&DAT_00644224)[param_1 * 5];
}


