/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_runtime_path_tree
 * Entry: 0040132f
 * Signature: undefined4 __cdecl i76edit_export_runtime_path_tree(int param_1, undefined4 * param_2)
 */


undefined4 __cdecl i76edit_export_runtime_path_tree(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  long _Offset;
  int iStack_c;
  int iStack_8;
  long lStack_4;
  
  iStack_c = 0;
  iStack_8 = 0;
  lStack_4 = __tell(param_1);
  __write(param_1,&iStack_c,4);
  for (puVar1 = i76edit_find_next_enabled_path_node(param_2); puVar1 != (undefined4 *)0x0;
      puVar1 = i76edit_find_next_enabled_path_node((undefined4 *)*puVar1)) {
    __write(param_1,(void *)(puVar1[2] + 0x28),0x28);
    lVar2 = __tell(param_1);
    __write(param_1,&iStack_8,4);
    iStack_8 = i76edit_export_runtime_path_tree_nodes_recursive(param_1,(int)puVar1);
    _Offset = __tell(param_1);
    __lseek(param_1,lVar2,0);
    __write(param_1,&iStack_8,4);
    __lseek(param_1,_Offset,0);
    iStack_c = iStack_c + 1;
  }
  lVar2 = __tell(param_1);
  __lseek(param_1,lStack_4,0);
  __write(param_1,&iStack_c,4);
  __lseek(param_1,lVar2,0);
  return 0;
}


