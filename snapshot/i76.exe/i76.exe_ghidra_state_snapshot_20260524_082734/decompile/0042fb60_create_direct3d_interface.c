/*
 * Program: i76.exe
 * Function: create_direct3d_interface
 * Entry: 0042fb60
 * Signature: undefined4 __stdcall create_direct3d_interface(void)
 */


/* cgpt whole-binary semantic rename v1: calls DirectDraw QueryInterface/Create IDirect3D and
   reports Creation of IDirect3D failed */

undefined4 create_direct3d_interface(void)

{
  DAT_005fdc0c = (**(code **)*DAT_006080b8)(DAT_006080b8,&DAT_004bcdf8,&DAT_005fde44);
  if (DAT_005fdc0c != 0) {
    directdraw_error_to_string(DAT_005fdc0c);
    set_directdraw_error_message(s_Creation_of_IDirect3D_failed___s_004ee01c);
    return 0;
  }
  return 1;
}


