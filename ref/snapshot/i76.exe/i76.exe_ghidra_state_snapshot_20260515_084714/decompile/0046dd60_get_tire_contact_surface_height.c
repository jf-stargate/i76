/*
 * Program: i76.exe
 * Function: get_tire_contact_surface_height
 * Entry: 0046dd60
 * Signature: float10 __cdecl get_tire_contact_surface_height(int param_1)
 */


/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=high] Tire child accessor for
   cached contact surface height. */

float10 __cdecl get_tire_contact_surface_height(int param_1)

{
  return (float10)*(float *)(*(int *)(param_1 + 0x70) + 0x2c);
}


