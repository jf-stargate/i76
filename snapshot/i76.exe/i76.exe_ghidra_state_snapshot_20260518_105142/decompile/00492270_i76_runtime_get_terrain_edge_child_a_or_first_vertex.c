/*
 * Program: i76.exe
 * Function: i76_runtime_get_terrain_edge_child_a_or_first_vertex
 * Entry: 00492270
 * Signature: int * __cdecl i76_runtime_get_terrain_edge_child_a_or_first_vertex(int * param_1, short * param_2)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00492270. Remove
   duplicated terrain wording.
   
   [cgpt_i76exe_terrain_runtime_structs_v10]
   proposed=i76_runtime_get_terrain_edge_child_a_or_first_vertex :: Small edge helper used by
   primitive walker to resolve edge endpoint/child data.
   
   [cgpt_i76exe_terrain_runtime_structs_v11]
   proposed=i76_runtime_emit_edge_first_side_vertex_sequence :: Flattens edge tree along
   child_edge_a then child_edge_b; emits vertex_a for leaf edges.
   
   [cgpt_i76exe_terrain_runtime_structs_v12]
   proposed=i76_runtime_flatten_edge_forward_emit_vertex_a_leaves :: Recursively flattens edge tree
   child_a then child_b; emits vertex_a for leaf edges into a vertex-index loop. */

int * __cdecl i76_runtime_get_terrain_edge_child_a_or_first_vertex(int *param_1,short *param_2)

{
  int *piVar1;
  
  if (*(short **)(param_2 + 2) != (short *)0x0) {
    piVar1 = i76_runtime_get_terrain_edge_child_a_or_first_vertex(param_1,*(short **)(param_2 + 2));
    piVar1 = i76_runtime_get_terrain_edge_child_a_or_first_vertex(piVar1,*(short **)(param_2 + 4));
    return piVar1;
  }
  *param_1 = (int)*param_2;
  return param_1 + 1;
}


