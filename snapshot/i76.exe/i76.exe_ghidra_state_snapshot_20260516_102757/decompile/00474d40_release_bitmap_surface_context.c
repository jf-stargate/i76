/*
 * Program: i76.exe
 * Function: release_bitmap_surface_context
 * Entry: 00474d40
 * Signature: undefined __cdecl release_bitmap_surface_context(int * param_1)
 */


/* [cgpt i76.exe image payload renames v28; confidence=medium-high] Releases heap/backing memory
   held by a bitmap/surface context. */

void __cdecl release_bitmap_surface_context(int *param_1)

{
  int iVar1;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10 [3];
  int local_4;
  
  if (param_1[0xb] == 1) {
    if ((param_1[0xc] != 1) && ((LPVOID)param_1[6] != (LPVOID)0x0)) {
      HeapFree(DAT_0058dac8,0,(LPVOID)param_1[6]);
    }
    local_10[2] = *param_1 + -1;
    local_4 = ((param_1[1] << 3) >> 3) + -1;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    local_14 = 0;
    local_10[0] = 0;
    local_10[1] = 0;
    iVar1 = clip_rect_to_rect_bounds(&local_20,local_10);
    if (-1 < iVar1) {
      param_1[7] = local_20;
      param_1[8] = local_1c;
      param_1[9] = local_18;
      param_1[10] = local_14;
    }
    param_1[6] = 0;
    param_1[5] = 0;
    *param_1 = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[0xc] = 1;
    param_1[1] = param_1[1] & 0xe0000000;
  }
  return;
}


