/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_runtime_path_tree
 * Entry: 004113c0
 * Signature: undefined4 __cdecl i76edit_export_runtime_path_tree(int param_1, undefined4 * param_2)
 */


/* [cgpt_i76edit_level_renames_v3] Runtime export helper that writes count placeholder, serializes
   path tree nodes, then backpatches count.
   
   [cgpt_i76edit_level_renames_v6:high] Runtime path-tree writer. Writes a count placeholder,
   serializes enabled path roots, backpatches per-root node counts, then backpatches total root
   count. */

undefined4 __cdecl i76edit_export_runtime_path_tree(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  long _Offset;
  int local_c;
  int local_8;
  long local_4;
  
  local_c = 0;
  local_8 = 0;
  local_4 = __tell(param_1);
  __write(param_1,&local_c,4);
  for (puVar1 = i76edit_find_next_enabled_path_node(param_2); puVar1 != (undefined4 *)0x0;
      puVar1 = i76edit_find_next_enabled_path_node((undefined4 *)*puVar1)) {
    __write(param_1,(void *)(puVar1[2] + 0x28),0x28);
    lVar2 = __tell(param_1);
    __write(param_1,&local_8,4);
    local_8 = i76edit_export_runtime_path_tree_nodes_recursive(param_1,(int)puVar1);
    _Offset = __tell(param_1);
    __lseek(param_1,lVar2,0);
    __write(param_1,&local_8,4);
    __lseek(param_1,_Offset,0);
    local_c = local_c + 1;
  }
  lVar2 = __tell(param_1);
  __lseek(param_1,local_4,0);
  __write(param_1,&local_c,4);
  __lseek(param_1,lVar2,0);
  return 0;
}


