/*
 * Program: I76EDIT.EXE
 * Function: i76edit_refresh_object_zone_membership_from_zone_map
 * Entry: 0040ac20
 * Signature: undefined __stdcall i76edit_refresh_object_zone_membership_from_zone_map(void)
 */


/* [cgpt_i76edit_level_renames_v4:medium] Iterates object lists across 0x50 buckets and updates
   object +0x0c from the zone map based on object cell coordinates. */

void i76edit_refresh_object_zone_membership_from_zone_map(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  uVar4 = 0;
  do {
    for (puVar1 = (undefined4 *)(&DAT_00439be8)[uVar4]; puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      puVar3 = i76edit_get_terrain_plane_row_ptr(uVar4,0);
      iVar2 = puVar1[2];
      *(uint *)(iVar2 + 0xc) =
           (uint)*(ushort *)((int)puVar3 + (*(int *)(iVar2 + 8) * 0x80 + *(int *)(iVar2 + 4)) * 2);
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x50);
  return;
}


