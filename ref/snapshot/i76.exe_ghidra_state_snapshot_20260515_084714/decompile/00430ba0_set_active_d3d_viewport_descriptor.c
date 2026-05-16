/*
 * Program: i76.exe
 * Function: set_active_d3d_viewport_descriptor
 * Entry: 00430ba0
 * Signature: undefined4 __cdecl set_active_d3d_viewport_descriptor(undefined4 * param_1)
 */


/* cgpt readability rename v13 set A: Copies a D3D viewport/display descriptor into the active
   global block and validates backend error state. */

undefined4 __cdecl set_active_d3d_viewport_descriptor(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_1 == (undefined4 *)0x0) {
    param_1 = &DAT_005fcea0;
  }
  if (param_1 != &DAT_005fcea0) {
    puVar2 = &DAT_005fcea0;
    for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *param_1;
      param_1 = param_1 + 1;
      puVar2 = puVar2 + 1;
    }
  }
  if (DAT_0060844c != 0) {
    iVar1 = d3d_error_to_string();
    if (iVar1 == 0) {
      return 0;
    }
  }
  return 1;
}


