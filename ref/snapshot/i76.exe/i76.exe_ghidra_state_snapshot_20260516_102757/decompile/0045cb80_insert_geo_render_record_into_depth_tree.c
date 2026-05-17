/*
 * Program: i76.exe
 * Function: insert_geo_render_record_into_depth_tree
 * Entry: 0045cb80
 * Signature: undefined __cdecl insert_geo_render_record_into_depth_tree(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO lighting/render renames v33; confidence=high] Inserts a prepared GEO render
   record into the depth-sorted binary tree using render-record child links at +0x40/+0x44 and
   centroid/sort fields. */

void __cdecl insert_geo_render_record_into_depth_tree(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = g_geo_render_depth_tree_root;
  do {
    while (iVar2 = iVar1,
          *(float *)(iVar2 + 0x38) * *(float *)(param_1 + 0x2c) +
          *(float *)(iVar2 + 0x34) * *(float *)(param_1 + 0x28) +
          *(float *)(iVar2 + 0x30) * *(float *)(param_1 + 0x24) + *(float *)(iVar2 + 0x3c) <
          (float)_DAT_004be0e0) {
      iVar1 = *(int *)(iVar2 + 0x44);
      if (*(int *)(iVar2 + 0x44) == 0) {
        *(int *)(iVar2 + 0x44) = param_1;
        return;
      }
    }
    iVar1 = *(int *)(iVar2 + 0x40);
  } while (*(int *)(iVar2 + 0x40) != 0);
  *(int *)(iVar2 + 0x40) = param_1;
  return;
}


