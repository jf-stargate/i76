/*
 * Program: I76EDIT.EXE
 * Function: i76edit_get_terrain_plane_row_ptr
 * Entry: 004010b4
 * Signature: undefined4 * __cdecl i76edit_get_terrain_plane_row_ptr(int param_1, int param_2)
 */


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


