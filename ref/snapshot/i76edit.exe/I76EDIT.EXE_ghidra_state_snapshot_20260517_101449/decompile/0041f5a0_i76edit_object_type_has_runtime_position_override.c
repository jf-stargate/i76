/*
 * Program: I76EDIT.EXE
 * Function: i76edit_object_type_has_runtime_position_override
 * Entry: 0041f5a0
 * Signature: undefined4 __cdecl i76edit_object_type_has_runtime_position_override(int param_1)
 */


/* [cgpt_i76edit_level_renames_v4:medium] Returns true for object type ids 1, 8, and 9; used by
   runtime object export to choose alternate coordinate handling. */

undefined4 __cdecl i76edit_object_type_has_runtime_position_override(int param_1)

{
  if (((param_1 != 1) && (param_1 != 9)) && (param_1 != 8)) {
    return 0;
  }
  return 1;
}


