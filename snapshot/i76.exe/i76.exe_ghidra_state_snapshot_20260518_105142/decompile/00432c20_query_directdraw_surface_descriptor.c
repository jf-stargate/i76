/*
 * Program: i76.exe
 * Function: query_directdraw_surface_descriptor
 * Entry: 00432c20
 * Signature: undefined __cdecl query_directdraw_surface_descriptor(undefined4 * param_1, int * param_2)
 */


/* cgpt rename v3: Zeros a DDSURFACEDESC-sized block, sets dwSize, and queries the DirectDraw
   surface description. */

void __cdecl query_directdraw_surface_descriptor(undefined4 *param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *param_1 = 0x6c;
  (**(code **)(*param_2 + 0x58))(param_2,param_1);
  return;
}


