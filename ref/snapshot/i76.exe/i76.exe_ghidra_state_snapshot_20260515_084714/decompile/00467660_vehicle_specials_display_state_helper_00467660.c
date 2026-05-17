/*
 * Program: i76.exe
 * Function: vehicle_specials_display_state_helper_00467660
 * Entry: 00467660
 * Signature: undefined __cdecl vehicle_specials_display_state_helper_00467660(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle specials display state helper
   based on adjacent named subsystem context. */

void __cdecl vehicle_specials_display_state_helper_00467660(int param_1)

{
  int iVar1;
  
  clear_world_object_geometry_binding_and_refresh_textures(param_1);
  for (iVar1 = *(int *)(param_1 + 100); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
    vehicle_specials_display_state_helper_00467660(iVar1);
  }
  return;
}


