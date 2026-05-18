/*
 * Program: I76EDIT.EXE
 * Function: i76edit_world_xy_to_zone_local_triplet
 * Entry: 00412300
 * Signature: undefined __cdecl i76edit_world_xy_to_zone_local_triplet(int * param_1, uint param_2, uint param_3)
 */


/* [cgpt_i76edit_level_renames_v5:high] Converts world X/Y into zone/local coordinates: zone id from
   80x80 byte map at 00439ef0 using x>>7,y>>7; local x/y are signed modulo 128.
   
   [cgpt_i76edit_level_renames_v6:high] Converts world X/Y into zone id and signed local 0..127-ish
   coordinates using the 80x80 zone map at 00439ef0 with x>>7,y>>7 cell selection. */

void __cdecl i76edit_world_xy_to_zone_local_triplet(int *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (int)param_3 >> 0x1f;
  uVar2 = (int)param_2 >> 0x1f;
  *param_1 = (int)(char)(&DAT_00439ef0)
                        [((int)(param_2 + (uVar2 & 0x7f)) >> 7) +
                         ((int)(param_3 + (uVar1 & 0x7f)) >> 7) * 0x50];
  param_1[1] = ((param_2 ^ uVar2) - uVar2 & 0x7f ^ uVar2) - uVar2;
  param_1[2] = ((param_3 ^ uVar1) - uVar1 & 0x7f ^ uVar1) - uVar1;
  return;
}


