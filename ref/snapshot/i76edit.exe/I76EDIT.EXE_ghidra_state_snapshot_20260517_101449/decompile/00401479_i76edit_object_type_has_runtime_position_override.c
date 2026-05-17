/*
 * Program: I76EDIT.EXE
 * Function: i76edit_object_type_has_runtime_position_override
 * Entry: 00401479
 * Signature: undefined4 __cdecl i76edit_object_type_has_runtime_position_override(int param_1)
 */


undefined4 __cdecl i76edit_object_type_has_runtime_position_override(int param_1)

{
  if (((param_1 != 1) && (param_1 != 9)) && (param_1 != 8)) {
    return 0;
  }
  return 1;
}


