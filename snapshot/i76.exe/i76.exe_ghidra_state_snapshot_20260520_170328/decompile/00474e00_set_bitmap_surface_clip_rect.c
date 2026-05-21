/*
 * Program: i76.exe
 * Function: set_bitmap_surface_clip_rect
 * Entry: 00474e00
 * Signature: undefined __cdecl set_bitmap_surface_clip_rect(int * param_1, int param_2, int param_3, int param_4, int param_5)
 */


/* cgpt rename v4: Normalizes and clips a rectangle to bitmap bounds and stores the resulting clip
   rectangle in the bitmap surface context. */

void __cdecl
set_bitmap_surface_clip_rect(int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10 [3];
  int local_4;
  
  local_18 = param_4;
  if (param_4 < param_2) {
    local_18 = param_2;
    param_2 = param_4;
  }
  local_14 = param_5;
  if (param_5 < param_3) {
    local_14 = param_3;
    param_3 = param_5;
  }
  local_10[2] = *param_1 + -1;
  local_4 = ((param_1[1] << 3) >> 3) + -1;
  local_10[0] = 0;
  local_10[1] = 0;
  local_20 = param_2;
  local_1c = param_3;
  iVar1 = clip_rect_to_rect_bounds(&local_20,local_10);
  if (-1 < iVar1) {
    param_1[7] = local_20;
    param_1[8] = local_1c;
    param_1[9] = local_18;
    param_1[10] = local_14;
  }
  return;
}


