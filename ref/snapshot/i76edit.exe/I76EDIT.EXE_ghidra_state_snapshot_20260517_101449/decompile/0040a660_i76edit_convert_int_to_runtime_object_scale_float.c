/*
 * Program: I76EDIT.EXE
 * Function: i76edit_convert_int_to_runtime_object_scale_float
 * Entry: 0040a660
 * Signature: float10 __cdecl i76edit_convert_int_to_runtime_object_scale_float(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt_i76edit_level_renames_v5:medium] Converts integer object field to float and multiplies by
   global scale constant 004320bc; used during runtime object export.
   
   [cgpt_i76edit_level_renames_v6:high] Converts integer object coordinate component to runtime
   float by multiplying by global scale constant at 004320bc. */

float10 __cdecl i76edit_convert_int_to_runtime_object_scale_float(int param_1)

{
  return (float10)param_1 * (float10)_DAT_004320bc;
}


