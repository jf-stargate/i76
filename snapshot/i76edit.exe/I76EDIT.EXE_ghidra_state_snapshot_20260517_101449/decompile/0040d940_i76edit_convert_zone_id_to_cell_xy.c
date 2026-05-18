/*
 * Program: I76EDIT.EXE
 * Function: i76edit_convert_zone_id_to_cell_xy
 * Entry: 0040d940
 * Signature: undefined __cdecl i76edit_convert_zone_id_to_cell_xy(int param_1, int * param_2, int * param_3)
 */


/* [cgpt_i76edit_level_renames_v4:medium] Finds zone id origin and converts returned fixed/world
   coordinates back to cell x/y by arithmetic shift by 7. */

void __cdecl i76edit_convert_zone_id_to_cell_xy(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  
  uVar3 = i76edit_find_zone_cell_origin_by_zone_id(param_1,0,0);
  iVar2 = (int)((ulonglong)uVar3 >> 0x20);
  iVar1 = (int)uVar3;
  if (iVar1 == -1) {
    *param_2 = -1;
    *param_3 = -1;
    return;
  }
  *param_2 = (int)(iVar1 + (iVar1 >> 0x1f & 0x7fU)) >> 7;
  *param_3 = (int)(iVar2 + (iVar2 >> 0x1f & 0x7fU)) >> 7;
  return;
}


