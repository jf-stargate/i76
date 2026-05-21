/*
 * Program: i76.exe
 * Function: terrain_runtime_record_helper_00492270
 * Entry: 00492270
 * Signature: int * __cdecl terrain_runtime_record_helper_00492270(int * param_1, short * param_2)
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
   child_a then child_b; emits vertex_a for leaf edges into a vertex-index loop.
   [cgpt-i76-v36 high] Recursive forward edge flatten: child A/B, leaf emits vertex_a.
   
   I76 rename v43: terrain_runtime_record_helper_00492270
   Terrain runtime helper from adaptive path; semantics still partial. */

int * __cdecl terrain_runtime_record_helper_00492270(int *param_1,short *param_2)

{
  int *piVar1;
  
  if (*(short **)(param_2 + 2) != (short *)0x0) {
    piVar1 = terrain_runtime_record_helper_00492270(param_1,*(short **)(param_2 + 2));
    piVar1 = terrain_runtime_record_helper_00492270(piVar1,*(short **)(param_2 + 4));
    return piVar1;
  }
  *param_1 = (int)*param_2;
  return param_1 + 1;
}


