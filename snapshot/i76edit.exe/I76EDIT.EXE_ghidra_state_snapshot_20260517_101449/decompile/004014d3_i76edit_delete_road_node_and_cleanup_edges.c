/*
 * Program: I76EDIT.EXE
 * Function: i76edit_delete_road_node_and_cleanup_edges
 * Entry: 004014d3
 * Signature: undefined __cdecl i76edit_delete_road_node_and_cleanup_edges(int * param_1)
 */


void __cdecl i76edit_delete_road_node_and_cleanup_edges(int *param_1)

{
  void *_Memory;
  
  _Memory = (void *)param_1[2];
  thunk_FUN_0041c480(&DAT_0043c544,param_1);
  i76edit_link_road_edge_neighbors(*(int *)((int)_Memory + 0x40),*(int *)((int)_Memory + 0x48),0,-1)
  ;
  i76edit_link_road_edge_neighbors(*(int *)((int)_Memory + 0x44),*(int *)((int)_Memory + 0x4c),0,-1)
  ;
  _free(_Memory);
  return;
}


