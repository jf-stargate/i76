/*
 * Program: i76.exe
 * Function: i76_runtime_alloc_terrain_edge_record
 * Entry: 004918b0
 * Signature: undefined __cdecl i76_runtime_alloc_terrain_edge_record(undefined2 param_1, undefined2 param_2)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004918b0. Remove
   duplicated terrain wording.
   
   [cgpt_i76exe_terrain_runtime_structs_v10] proposed=i76_runtime_alloc_terrain_edge_record ::
   Allocates 0x0c-byte terrain edge record: short v0, short v1, edge* child_a, edge* child_b.
   
   [cgpt_i76exe_terrain_runtime_structs_v11] proposed=i76_runtime_alloc_terrain_edge_record ::
   Allocates 0x0c-byte terrain edge record: int16 vertex_a, int16 vertex_b, child edge A pointer,
   child edge B pointer. */

void __cdecl i76_runtime_alloc_terrain_edge_record(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  
  puVar2 = g_runtime_terrain_arena_cursor;
  puVar1 = g_runtime_terrain_arena_cursor + 1;
  g_runtime_terrain_arena_cursor = g_runtime_terrain_arena_cursor + 6;
  *puVar1 = param_2;
  *puVar2 = param_1;
  *(undefined4 *)(puVar2 + 2) = 0;
  *(undefined4 *)(puVar2 + 4) = 0;
  g_runtime_terrain_edge_record_count = g_runtime_terrain_edge_record_count + 1;
  return;
}


