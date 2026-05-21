/*
 * Program: i76shell.dll
 * Function: get_mw2_image_subresource_dimensions
 * Entry: 1003eeb9
 * Signature: undefined4 __cdecl get_mw2_image_subresource_dimensions(int param_1, int param_2)
 */


undefined4 __cdecl get_mw2_image_subresource_dimensions(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 8 + param_2 * 8) + param_1;
  return CONCAT22(((short)*(undefined4 *)(iVar1 + 0x10) - (short)*(undefined4 *)(iVar1 + 8)) + 1,
                  ((short)*(undefined4 *)(iVar1 + 0x14) - (short)*(undefined4 *)(iVar1 + 0xc)) + 1);
}


