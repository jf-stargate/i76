/*
 * Program: i76.exe
 * Function: get_vehicle_effective_terrain_friction_scalar
 * Entry: 0043d240
 * Signature: float10 __cdecl get_vehicle_effective_terrain_friction_scalar(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Returns terrain material
   friction for vehicle runtime field +0x45c, with wet/slippery flag clamp when vehicle runtime flag
   0x400 is set. */

float10 __cdecl get_vehicle_effective_terrain_friction_scalar(int param_1)

{
  float10 fVar1;
  
  fVar1 = get_terrain_material_friction_scalar(*(int *)(param_1 + 0x45c));
  if (((float10)_DAT_004bd168 < fVar1) && ((*(uint *)(param_1 + 0x454) & 0x400) != 0)) {
    fVar1 = (float10)_DAT_004bd148;
  }
  return fVar1;
}


