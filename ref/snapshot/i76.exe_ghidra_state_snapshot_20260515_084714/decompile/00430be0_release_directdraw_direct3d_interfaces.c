/*
 * Program: i76.exe
 * Function: release_directdraw_direct3d_interfaces
 * Entry: 00430be0
 * Signature: undefined4 __stdcall release_directdraw_direct3d_interfaces(void)
 */


/* cgpt rename v2: Releases DirectDraw/Direct3D interfaces and restores display/cooperative state.
    */

undefined4 release_directdraw_direct3d_interfaces(void)

{
  int iVar1;
  
  DAT_0060844c = 0;
  DAT_005fde40 = 0;
  iVar1 = release_directdraw_surfaces_candidate();
  if (iVar1 == 0) {
    return 0;
  }
  if (DAT_005fde48 != (int *)0x0) {
    (**(code **)(*DAT_005fde48 + 8))(DAT_005fde48);
    DAT_005fde48 = (int *)0x0;
  }
  if (DAT_005fd0e0 != (int *)0x0) {
    (**(code **)(*DAT_005fd0e0 + 8))(DAT_005fd0e0);
    DAT_005fd0e0 = (int *)0x0;
  }
  if (DAT_005fd0e8 != (int *)0x0) {
    (**(code **)(*DAT_005fd0e8 + 8))(DAT_005fd0e8);
    DAT_005fd0e8 = (int *)0x0;
  }
  if (DAT_006080c4 != (int *)0x0) {
    (**(code **)(*DAT_006080c4 + 8))(DAT_006080c4);
    DAT_006080c4 = (int *)0x0;
  }
  if (DAT_006080c0 != (int *)0x0) {
    (**(code **)(*DAT_006080c0 + 8))(DAT_006080c0);
    DAT_006080c0 = (int *)0x0;
  }
  if (DAT_00608410 != 0) {
    restore_directdraw_display_mode();
    set_directdraw_cooperative_level_candidate(DAT_005fde40,0);
  }
  if (DAT_005fde44 != (int *)0x0) {
    (**(code **)(*DAT_005fde44 + 8))(DAT_005fde44);
    DAT_005fde44 = (int *)0x0;
  }
  if (DAT_006080b8 != (int *)0x0) {
    (**(code **)(*DAT_006080b8 + 8))(DAT_006080b8);
    DAT_006080b8 = (int *)0x0;
  }
  return 1;
}


