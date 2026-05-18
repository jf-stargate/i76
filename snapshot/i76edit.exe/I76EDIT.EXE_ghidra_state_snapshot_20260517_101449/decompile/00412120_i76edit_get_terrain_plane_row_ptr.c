/*
 * Program: I76EDIT.EXE
 * Function: i76edit_get_terrain_plane_row_ptr
 * Entry: 00412120
 * Signature: undefined4 * __cdecl i76edit_get_terrain_plane_row_ptr(int param_1, int param_2)
 */


/* [cgpt_i76edit_level_renames_v5:high] Returns row pointers into one of six terrain planes. Row
   stride is 0x8004 bytes = 0x2001 dwords; selector 0 uses 009bc824, 1 uses 0043c554, 2 uses
   00ebcaa4, 3 uses 0113cbe4, 4 uses 00c3c964, 5 uses 013bcd24.
   
   [cgpt_i76edit_level_renames_v6:high] Returns row pointers into one of six terrain planes. Row
   stride is 0x8004 bytes = 0x2001 dwords; selector 0 uses 009bc824, 1 uses 0043c554, 2 uses
   00ebcaa4, 3 uses 0113cbe4, 4 uses 00c3c964, 5 uses 013bcd24. */

undefined4 * __cdecl i76edit_get_terrain_plane_row_ptr(int param_1,int param_2)

{
  if (param_2 == 1) {
    return (undefined4 *)(&DAT_0043c554 + param_1 * 0x4002);
  }
  if (param_2 == 2) {
    return (undefined4 *)(&DAT_00ebcaa4 + param_1 * 0x8004);
  }
  if (param_2 == 3) {
    return (undefined4 *)(&DAT_0113cbe4 + param_1 * 0x4002);
  }
  if (param_2 == 4) {
    return (undefined4 *)(&DAT_00c3c964 + param_1 * 0x8004);
  }
  if (param_2 == 5) {
    return &DAT_013bcd24 + param_1 * 0x2001;
  }
  return (undefined4 *)(&DAT_009bc824 + param_1 * 0x4002);
}


