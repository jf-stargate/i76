/*
 * Program: I76EDIT.EXE
 * Function: i76edit_rasterize_sampler_to_128x128_word_plane
 * Entry: 0040119f
 * Signature: undefined __cdecl i76edit_rasterize_sampler_to_128x128_word_plane(int * param_1, int param_2, int param_3, int param_4)
 */


void __cdecl
i76edit_rasterize_sampler_to_128x128_word_plane(int *param_1,int param_2,int param_3,int param_4)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  undefined4 uStack_c;
  
  iVar4 = 0;
  i76edit_build_distance_weighted_sample_table(param_1);
  puVar1 = i76edit_get_terrain_plane_row_ptr(param_4,0);
  uStack_c = 0;
  if (0 < param_3) {
    do {
      if (0 < param_2) {
        iVar2 = 0;
        do {
          iVar3 = iVar2 + 1;
          i76edit_sample_weighted_height_field(param_1,(float)iVar2,(float)uStack_c);
          lVar5 = __ftol();
          *(short *)((int)puVar1 + (iVar2 + iVar4) * 2) = (short)lVar5;
          iVar2 = iVar3;
        } while (iVar3 < param_2);
      }
      iVar4 = iVar4 + 0x80;
      uStack_c = uStack_c + 1;
    } while (uStack_c < param_3);
  }
  return;
}


