/*
 * Program: i76.exe
 * Function: compute_world_object_bounds_and_link_global
 * Entry: 004925f0
 * Signature: undefined __cdecl compute_world_object_bounds_and_link_global(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Computes bounds for a world
   object and links it into global runtime structures after geometry/object creation. */

void __cdecl compute_world_object_bounds_and_link_global(int param_1)

{
  float10 fVar1;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if ((*(int *)(param_1 + 0x6c) != 0x51) && (*(int *)(param_1 + 0x6c) != 5)) {
    compute_world_object_transformed_bounds(param_1,&local_18,&local_c);
    local_18 = (local_c + local_18) * _DAT_004be85c;
    *(float *)(param_1 + 0x84) = local_18;
    local_14 = (local_8 + local_14) * _DAT_004be85c;
    *(float *)(param_1 + 0x88) = local_14;
    local_10 = (local_4 + local_10) * _DAT_004be85c;
    *(float *)(param_1 + 0x8c) = local_10;
    fVar1 = compute_world_object_bounding_radius_from_point(param_1,local_18,local_14,local_10);
    *(float *)(param_1 + 0x90) = (float)fVar1;
  }
  if (DAT_00644200 == 0) {
    DAT_00644200 = param_1;
    return;
  }
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(DAT_00644200 + 0x60);
  *(int *)(DAT_00644200 + 0x60) = param_1;
  return;
}


