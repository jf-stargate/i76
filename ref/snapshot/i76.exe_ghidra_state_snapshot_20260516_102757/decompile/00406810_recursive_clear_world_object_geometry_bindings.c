/*
 * Program: i76.exe
 * Function: recursive_clear_world_object_geometry_bindings
 * Entry: 00406810
 * Signature: undefined __cdecl recursive_clear_world_object_geometry_bindings(int param_1)
 */


/* cgpt rename v3: Recursively clears geometry bindings and refreshes texture bindings over a
   world-object subtree. */

void __cdecl recursive_clear_world_object_geometry_bindings(int param_1)

{
  int iVar1;
  
  if (param_1 != 0) {
    clear_world_object_geometry_binding_and_refresh_textures(param_1);
    for (iVar1 = *(int *)(param_1 + 100); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
      recursive_clear_world_object_geometry_bindings(iVar1);
    }
  }
  return;
}


