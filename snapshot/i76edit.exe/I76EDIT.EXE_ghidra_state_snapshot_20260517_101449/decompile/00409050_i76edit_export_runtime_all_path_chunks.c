/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_runtime_all_path_chunks
 * Entry: 00409050
 * Signature: undefined __cdecl i76edit_export_runtime_all_path_chunks(int param_1)
 */


/* [cgpt_i76edit_level_renames_v4:high] Runtime path export wrapper. Calls path-tree
   initialization/helper and then i76edit_export_runtime_path_tree using global path root
   DAT_00439be4. */

void __cdecl i76edit_export_runtime_all_path_chunks(int param_1)

{
  thunk_FUN_004087c0();
  i76edit_export_runtime_path_tree(param_1,DAT_00439be4);
  return;
}


