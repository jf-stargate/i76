/*
 * Program: i76shell.dll
 * Function: get_shell_bitmap_dimensions_packed
 * Entry: 1003ea31
 * Signature: undefined4 __cdecl get_shell_bitmap_dimensions_packed(int param_1)
 */


undefined4 __cdecl get_shell_bitmap_dimensions_packed(int param_1)

{
  return CONCAT22((*(short *)(param_1 + 8) - *(short *)(param_1 + 4)) + 1,
                  (*(short *)(param_1 + 10) - *(short *)(param_1 + 6)) + 1);
}


