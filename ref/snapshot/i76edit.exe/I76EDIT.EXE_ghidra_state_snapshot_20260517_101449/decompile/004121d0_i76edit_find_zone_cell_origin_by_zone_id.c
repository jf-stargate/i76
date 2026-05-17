/*
 * Program: I76EDIT.EXE
 * Function: i76edit_find_zone_cell_origin_by_zone_id
 * Entry: 004121d0
 * Signature: undefined8 __cdecl i76edit_find_zone_cell_origin_by_zone_id(int param_1, int param_2, int param_3)
 */


/* [cgpt_i76edit_level_renames_v4:medium] Searches the 80x80 byte zone map at DAT_00439ef0 for a
   zone id and returns x/y origins scaled by 0x80, or -1/-1 when not found. */

undefined8 __cdecl i76edit_find_zone_cell_origin_by_zone_id(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar1 = 0;
  iVar3 = 0;
  do {
    iVar2 = 0;
    do {
      if ((char)(&DAT_00439ef0)[iVar2 + iVar1] == param_1) {
        return CONCAT44(iVar3 * 0x80 + param_3,iVar2 * 0x80 + param_2);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x50);
    iVar1 = iVar1 + 0x50;
    iVar3 = iVar3 + 1;
  } while (iVar1 < 0x1900);
  if (iVar3 == 0x50) {
    local_8 = 0xffffffff;
    local_4 = 0xffffffff;
  }
  return CONCAT44(local_4,local_8);
}


