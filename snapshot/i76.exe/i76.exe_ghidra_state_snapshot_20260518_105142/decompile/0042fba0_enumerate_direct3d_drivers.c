/*
 * Program: i76.exe
 * Function: enumerate_direct3d_drivers
 * Entry: 0042fba0
 * Signature: undefined4 __stdcall enumerate_direct3d_drivers(void)
 */


/* cgpt whole-binary semantic rename v1: calls IDirect3D EnumDevices/driver enumeration; reports
   Enumeration of drivers failed */

undefined4 enumerate_direct3d_drivers(void)

{
  DAT_005fde50 = 0;
  DAT_005fdc0c = (**(code **)(*DAT_005fde44 + 0x10))(DAT_005fde44,&LAB_0042fc00,&stack0x00000004);
  if (DAT_005fdc0c != 0) {
    directdraw_error_to_string(DAT_005fdc0c);
    set_directdraw_error_message(s_Enumeration_of_drivers_failed____004ee040);
    return 0;
  }
  DAT_005fde54 = 0;
  return 1;
}


