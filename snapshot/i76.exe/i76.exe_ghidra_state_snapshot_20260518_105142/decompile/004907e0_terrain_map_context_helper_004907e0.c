/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_004907e0
 * Entry: 004907e0
 * Signature: undefined __cdecl terrain_map_context_helper_004907e0(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004907e0. Remove
   duplicated terrain wording. */

void __cdecl terrain_map_context_helper_004907e0(int param_1)

{
  _DAT_004fad24 = 0x3b2aaaab;
  _DAT_004fad20 = 0x41800000;
  if (param_1 == 0) {
    _DAT_004fad20 = 0x40cccccd;
    _DAT_004fad24 = 0x3b800000;
  }
  else if (param_1 == 2) {
    _DAT_004fad20 = 0x42200000;
    _DAT_004fad24 = 0x3ae353f8;
    return;
  }
  return;
}


