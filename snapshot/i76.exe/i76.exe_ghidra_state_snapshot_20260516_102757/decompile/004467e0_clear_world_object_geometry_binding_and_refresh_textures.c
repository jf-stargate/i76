/*
 * Program: i76.exe
 * Function: clear_world_object_geometry_binding_and_refresh_textures
 * Entry: 004467e0
 * Signature: uint __cdecl clear_world_object_geometry_binding_and_refresh_textures(int param_1)
 */


/* cgpt rename v2: Clears a world object's geometry cache binding and refreshes object texture
   bindings after the change. */

uint __cdecl clear_world_object_geometry_binding_and_refresh_textures(int param_1)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  
  uVar1 = param_1 * 0x6cd + 0xaab;
  uVar2 = uVar1 / 0x7ed;
  for (piVar3 = (int *)(&g_geometry_binding_hash)[uVar1 % 0x7ed]; piVar3 != (int *)0x0;
      piVar3 = (int *)piVar3[0xe]) {
    if (*piVar3 == param_1) goto LAB_00446819;
  }
  piVar3 = (int *)0x0;
LAB_00446819:
  if (piVar3 != (int *)0x0) {
    if (piVar3[1] != 0) {
      release_geometry_cache_reference(piVar3[1]);
      piVar3[1] = 0;
    }
    piVar3[3] = -1;
    piVar3[4] = -1;
    piVar3[9] = 0;
    piVar3[10] = 0;
    piVar3[0xb] = 0;
    piVar3[0xc] = 0;
    piVar3[5] = 0;
    piVar3[6] = 0;
    piVar3[7] = 0;
    piVar3[8] = 0;
    *(undefined4 *)(param_1 + 0x5c) = 0;
    uVar2 = refresh_object_texture_bindings_after_geometry_change(param_1);
  }
  return uVar2;
}


