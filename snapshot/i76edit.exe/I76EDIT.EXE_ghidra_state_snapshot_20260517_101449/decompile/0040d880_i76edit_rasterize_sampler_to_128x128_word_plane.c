/*
 * Program: I76EDIT.EXE
 * Function: i76edit_rasterize_sampler_to_128x128_word_plane
 * Entry: 0040d880
 * Signature: undefined __cdecl i76edit_rasterize_sampler_to_128x128_word_plane(int * param_1, int param_2, int param_3, int param_4)
 */


/* [cgpt_i76edit_level_renames_v4:low] Builds/updates a word terrain/zone plane by sampling a
   floating helper over width/height loops. Provisional until helper 0040d5f0 is traced.
   
   [cgpt_i76edit_level_renames_v5:medium] Rasterizes a sampler into a 128x128 word plane by calling
   i76edit_sample_weighted_height_field over grid coordinates. */

void __cdecl
i76edit_rasterize_sampler_to_128x128_word_plane(int *param_1,int param_2,int param_3,int param_4)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  undefined4 local_c;
  
  iVar4 = 0;
  i76edit_build_distance_weighted_sample_table(param_1);
  puVar1 = i76edit_get_terrain_plane_row_ptr(param_4,0);
  local_c = 0;
  if (0 < param_3) {
    do {
      if (0 < param_2) {
        iVar2 = 0;
        do {
          iVar3 = iVar2 + 1;
          i76edit_sample_weighted_height_field(param_1,(float)iVar2,(float)local_c);
          lVar5 = __ftol();
          *(short *)((int)puVar1 + (iVar2 + iVar4) * 2) = (short)lVar5;
          iVar2 = iVar3;
        } while (iVar3 < param_2);
      }
      iVar4 = iVar4 + 0x80;
      local_c = local_c + 1;
    } while (local_c < param_3);
  }
  return;
}


