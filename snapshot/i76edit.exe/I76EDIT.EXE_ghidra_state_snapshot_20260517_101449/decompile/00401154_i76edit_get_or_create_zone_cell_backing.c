/*
 * Program: I76EDIT.EXE
 * Function: i76edit_get_or_create_zone_cell_backing
 * Entry: 00401154
 * Signature: undefined __cdecl i76edit_get_or_create_zone_cell_backing(int param_1, int param_2, int param_3)
 */


void __cdecl i76edit_get_or_create_zone_cell_backing(int param_1,int param_2,int param_3)

{
  i76edit_get_or_assign_zone_map_cell_id
            ((int)(param_1 + (param_1 >> 0x1f & 0x7fU)) >> 7,
             (int)(param_2 + (param_2 >> 0x1f & 0x7fU)) >> 7,param_3);
  return;
}


