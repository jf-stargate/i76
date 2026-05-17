/*
 * Program: i76.exe
 * Function: world_transform_projection_context_helper_0048e110
 * Entry: 0048e110
 * Signature: undefined4 __cdecl world_transform_projection_context_helper_0048e110(DWORD * param_1)
 */


/* cgpt label refinement v19: was
   geometry_transform_highlight_world_transform_or_projection_helper_0048e110. Shorten readability
   label. */

undefined4 __cdecl world_transform_projection_context_helper_0048e110(DWORD *param_1)

{
  DWORD h;
  int iVar1;
  
  if (param_1[0x38] == 0) {
    return 0;
  }
  dib_surface_palette_context_helper_00476450((int *)param_1);
  h = (int)(param_1[1] << 3) >> 3;
  iVar1 = SetDIBitsToDevice(DAT_0059c1b0,0,0,*param_1,h,0,0,0,h,(void *)param_1[5],
                            (BITMAPINFO *)&DAT_0059bd88,1);
  if (iVar1 == 0) {
    param_1[0x39] = 4;
    return 0;
  }
  return 1;
}


