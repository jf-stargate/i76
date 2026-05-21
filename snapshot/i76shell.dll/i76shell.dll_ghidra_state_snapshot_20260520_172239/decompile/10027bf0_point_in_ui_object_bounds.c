/*
 * Program: i76shell.dll
 * Function: point_in_ui_object_bounds
 * Entry: 10027bf0
 * Signature: undefined4 __cdecl point_in_ui_object_bounds(int param_1, int param_2, int param_3)
 */


undefined4 __cdecl point_in_ui_object_bounds(int param_1,int param_2,int param_3)

{
  if ((((*(int *)(param_3 + 4) < param_1) && (param_1 < *(int *)(param_3 + 8))) &&
      (*(int *)(param_3 + 0xc) < param_2)) && (param_2 < *(int *)(param_3 + 0x10))) {
    return 1;
  }
  return 0;
}


