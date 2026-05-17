/*
 * Program: i76.exe
 * Function: map_display_bit_depth_to_ddraw_caps_mask
 * Entry: 004335e0
 * Signature: undefined4 __cdecl map_display_bit_depth_to_ddraw_caps_mask(undefined4 param_1)
 */


/* cgpt rename v2: Maps display bit-depth selector values to DirectDraw capability masks. */

undefined4 __cdecl map_display_bit_depth_to_ddraw_caps_mask(undefined4 param_1)

{
  switch(param_1) {
  case 1:
    return 0x4000;
  case 2:
    return 0x2000;
  default:
    return 0xffffff9c;
  case 4:
    return 0x1000;
  case 8:
    return 0x800;
  case 0x10:
    return 0x400;
  case 0x18:
    return 0x200;
  case 0x20:
    return 0x100;
  }
}


