/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_runtime_all_linked_object_chunks
 * Entry: 0040fa00
 * Signature: undefined __cdecl i76edit_export_runtime_all_linked_object_chunks(int param_1)
 */


/* [cgpt_i76edit_level_renames_v4:high] Runtime LDEF payload wrapper. Iterates linked-object/export
   helper at 00417ef0 over global list/root DAT_0163ce60 until non-negative completion. */

void __cdecl i76edit_export_runtime_all_linked_object_chunks(int param_1)

{
  int iVar1;
  
  do {
    iVar1 = i76edit_export_runtime_linked_object_obj_records(param_1,DAT_0163ce60);
  } while (iVar1 < 0);
  return;
}


