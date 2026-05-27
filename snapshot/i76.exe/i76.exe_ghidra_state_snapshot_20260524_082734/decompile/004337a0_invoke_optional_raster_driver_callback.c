/*
 * Program: i76.exe
 * Function: invoke_optional_raster_driver_callback
 * Entry: 004337a0
 * Signature: undefined4 __cdecl invoke_optional_raster_driver_callback(undefined4 param_1, undefined4 param_2)
 */


/* cgpt label refinement v18: was invoke_optional_display_driver_callback. Clarify that this
   dispatch is in the optional raster/display backend callback path rather than a generic driver
   callback. */

undefined4 __cdecl invoke_optional_raster_driver_callback(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (DAT_005fcee8 != (code *)0x0) {
    DAT_005fcef0 = DAT_005fcef0 + 1;
    uVar1 = (*DAT_005fcee8)(param_1,param_2,&DAT_005fde4c,0);
    return uVar1;
  }
  return 1;
}


