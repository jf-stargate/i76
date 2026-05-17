/*
 * Program: i76.exe
 * Function: create_selected_direct3d_device
 * Entry: 00430110
 * Signature: undefined4 __cdecl create_selected_direct3d_device(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: creates selected D3D device and enumerates texture formats
    */

undefined4 __cdecl create_selected_direct3d_device(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if (DAT_005fde48 != (int *)0x0) {
    (**(code **)(*DAT_005fde48 + 8))(DAT_005fde48);
    DAT_005fde48 = (int *)0x0;
  }
  iVar2 = param_1 * 0x13c;
  if (((&DAT_005fdf84)[param_1 * 0x4f] == 0) || (DAT_006080d0 != 0)) {
    DAT_005fde54 = param_1;
    puVar3 = (undefined4 *)(&DAT_005fde58 + iVar2);
    puVar4 = &DAT_005fe484;
    for (iVar1 = 0x4f; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    DAT_005fdc0c = (**(code **)*DAT_006080c4)(DAT_006080c4,&DAT_005fdf74 + iVar2,&DAT_005fde48);
    if (DAT_005fdc0c == 0) {
      DAT_005fde54 = param_1;
      DAT_005fe5c0 = 0;
      if (*(int *)(&DAT_005fdf88 + iVar2) != 0) {
        DAT_005fe5c0 = 0;
        DAT_005fdc0c = (**(code **)(*DAT_005fde48 + 0x38))
                                 (DAT_005fde48,register_d3d_device_driver_descriptor,0);
        if (DAT_005fdc0c == 0) {
          qsort(&DAT_005fe5c8,DAT_005fe5c0,0x80,(_PtFuncCompare *)&LAB_0042fff0);
          puVar3 = &DAT_005fe5c8;
          puVar4 = &DAT_005fff48;
          for (iVar2 = 0x20; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          _DAT_005fe5c4 = 0;
          qsort(&DAT_005fe5c8,DAT_005fe5c0,0x80,(_PtFuncCompare *)&LAB_0042fef0);
          puVar3 = &DAT_005fe5c8;
          puVar4 = &DAT_005ffec8;
          for (iVar2 = 0x20; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          return 1;
        }
        directdraw_error_to_string(DAT_005fdc0c);
        set_directdraw_error_message(s_Enumeration_of_texture_formats_f_004ee064);
      }
    }
    else {
      directdraw_error_to_string(DAT_005fdc0c);
      set_directdraw_error_message(s_Create_D3D_device_failed___s_004ee090);
    }
  }
  else {
    set_directdraw_error_message(s_Could_not_fit_the_rendering_surf_004ee0b0);
  }
  if (DAT_005fde48 != (int *)0x0) {
    (**(code **)(*DAT_005fde48 + 8))(DAT_005fde48);
    DAT_005fde48 = (int *)0x0;
  }
  return 0;
}


