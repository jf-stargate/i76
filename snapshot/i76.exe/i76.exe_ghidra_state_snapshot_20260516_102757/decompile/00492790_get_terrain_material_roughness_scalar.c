/*
 * Program: i76.exe
 * Function: get_terrain_material_roughness_scalar
 * Entry: 00492790
 * Signature: float10 __cdecl get_terrain_material_roughness_scalar(int param_1)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Returns terrain/material
   roughness scalar from the terrain material table. */

float10 __cdecl get_terrain_material_roughness_scalar(int param_1)

{
  return (float10)*(float *)(&DAT_00644228 + param_1 * 0x14);
}


