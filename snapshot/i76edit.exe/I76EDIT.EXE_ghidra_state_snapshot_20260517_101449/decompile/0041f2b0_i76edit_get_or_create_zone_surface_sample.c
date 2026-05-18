/*
 * Program: I76EDIT.EXE
 * Function: i76edit_get_or_create_zone_surface_sample
 * Entry: 0041f2b0
 * Signature: uint __cdecl i76edit_get_or_create_zone_surface_sample(uint param_1, uint param_2, int param_3)
 */


/* [cgpt_i76edit_level_renames_v5:medium] Given world/cell X/Y and surface selector, normalizes
   special surface ids 0x63/0x64, ensures zone/cell backing data exists, then returns a
   terrain-plane sample.
   
   [cgpt_i76edit_level_renames_v6:high] Maps world/local coordinates to a zone cell and
   returns/creates a terrain surface/height sample used while building 128x128 runtime zone rasters.
    */

uint __cdecl i76edit_get_or_create_zone_surface_sample(uint param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int local_c [3];
  
  if ((-1 < (int)param_1) && (-1 < (int)param_2)) {
    if (param_3 < 99) {
      i76edit_get_or_create_zone_cell_backing(param_1,param_2,1);
    }
    else {
      iVar2 = i76edit_get_or_create_zone_cell_backing(param_1,param_2,0);
      if (iVar2 < 0) {
        return 0xffffffff;
      }
      if (param_3 == 99) {
        param_3 = 0;
      }
      if (param_3 == 100) {
        param_3 = 1;
      }
    }
    piVar3 = (int *)i76edit_world_xy_to_zone_local_triplet(local_c,param_1,param_2);
    iVar2 = piVar3[1];
    iVar1 = piVar3[2];
    puVar4 = i76edit_get_terrain_plane_row_ptr(*piVar3,param_3);
    return (uint)*(ushort *)((int)puVar4 + (iVar1 * 0x80 + iVar2) * 2);
  }
  return 0xffffffff;
}


