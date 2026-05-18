/*
 * Program: i76.exe
 * Function: i76_runtime_get_terrain_edge_child_b_or_second_vertex
 * Entry: 004922b0
 * Signature: int * __cdecl i76_runtime_get_terrain_edge_child_b_or_second_vertex(int * param_1, int param_2)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004922b0. Remove
   duplicated terrain wording.
   
   [cgpt_i76exe_terrain_runtime_structs_v10]
   proposed=i76_runtime_get_terrain_edge_child_b_or_second_vertex :: Small edge helper used by
   primitive walker to resolve edge endpoint/child data.
   
   [cgpt_i76exe_terrain_runtime_structs_v11]
   proposed=i76_runtime_emit_edge_second_side_vertex_sequence :: Flattens edge tree along
   child_edge_b then child_edge_a; emits vertex_b for leaf edges.
   
   [cgpt_i76exe_terrain_runtime_structs_v12]
   proposed=i76_runtime_flatten_edge_reverse_emit_vertex_b_leaves :: Recursively flattens edge tree
   child_b then child_a; emits vertex_b for leaf edges into a vertex-index loop. */

int * __cdecl i76_runtime_get_terrain_edge_child_b_or_second_vertex(int *param_1,int param_2)

{
  int *piVar1;
  
  if (*(int *)(param_2 + 4) != 0) {
    piVar1 = i76_runtime_get_terrain_edge_child_b_or_second_vertex(param_1,*(int *)(param_2 + 8));
    piVar1 = i76_runtime_get_terrain_edge_child_b_or_second_vertex(piVar1,*(int *)(param_2 + 4));
    return piVar1;
  }
  *param_1 = (int)*(short *)(param_2 + 2);
  return param_1 + 1;
}


