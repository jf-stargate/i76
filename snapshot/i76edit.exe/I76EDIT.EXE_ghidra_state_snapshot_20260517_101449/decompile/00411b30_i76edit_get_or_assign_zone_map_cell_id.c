/*
 * Program: I76EDIT.EXE
 * Function: i76edit_get_or_assign_zone_map_cell_id
 * Entry: 00411b30
 * Signature: int __cdecl i76edit_get_or_assign_zone_map_cell_id(int param_1, int param_2, int param_3)
 */


/* [cgpt_i76edit_level_renames_v4:medium] Bounds-checks an 80x80 zone map coordinate, reads byte
   zone id at DAT_00439ef0, and can assign a new id if the cell is -1 and assignment is requested.
    */

int __cdecl i76edit_get_or_assign_zone_map_cell_id(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  if ((param_1 < 0x50) && (param_2 < 0x50)) {
    iVar1 = (int)(char)(&DAT_00439ef0)[param_1 + param_2 * 0x50];
    if ((iVar1 == -1) && (param_3 != 0)) {
      iVar1 = i76edit_alloc_first_unused_base_terrain_row();
      (&DAT_00439ef0)[param_1 + param_2 * 0x50] = (char)iVar1;
      i76edit_export_height_txt_debug_view(iVar1);
    }
    return iVar1;
  }
  return -1;
}


