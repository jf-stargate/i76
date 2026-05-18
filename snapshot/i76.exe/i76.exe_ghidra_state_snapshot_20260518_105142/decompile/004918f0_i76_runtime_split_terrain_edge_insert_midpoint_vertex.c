/*
 * Program: i76.exe
 * Function: i76_runtime_split_terrain_edge_insert_midpoint_vertex
 * Entry: 004918f0
 * Signature: undefined __cdecl i76_runtime_split_terrain_edge_insert_midpoint_vertex(undefined2 * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004918f0. Remove
   duplicated terrain wording.
   
   [cgpt_i76exe_terrain_runtime_structs_v10]
   proposed=i76_runtime_split_terrain_edge_insert_midpoint_vertex :: If an edge has no child split,
   inserts midpoint vertex in terrain vertex buffers, then creates two child edge records.
   
   [cgpt_i76exe_terrain_runtime_structs_v11]
   proposed=i76_runtime_split_terrain_edge_insert_midpoint_vertex :: Splits an unsplit edge by
   adding midpoint terrain vertex sampled via height lookup and allocating two child edges. */

void __cdecl i76_runtime_split_terrain_edge_insert_midpoint_vertex(undefined2 *param_1)

{
  undefined2 uVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined2 *puVar6;
  ushort uVar7;
  int iVar8;
  int iVar9;
  undefined2 extraout_var;
  int iVar10;
  
  if (*(int *)(param_1 + 2) == 0) {
    iVar8 = ftol();
    iVar9 = ftol();
    iVar4 = g_runtime_terrain_vertex_count;
    fVar2 = (float)(iVar9 >> 1);
    iVar10 = g_runtime_terrain_vertex_count * 0xc;
    g_runtime_terrain_vertex_count = g_runtime_terrain_vertex_count + 1;
    *(float *)(g_runtime_terrain_vertex_xyz_buffer + iVar10) = fVar2;
    fVar3 = (float)(iVar8 >> 1);
    *(float *)(g_runtime_terrain_vertex_xyz_buffer + 8 + iVar10) = fVar3;
    uVar7 = terrain_map_context_helper_00493160(iVar9 >> 1,iVar8 >> 1);
    *(float *)(g_runtime_terrain_vertex_xyz_buffer + 4 + iVar10) =
         (float)CONCAT22(extraout_var,uVar7);
    *(float *)(g_runtime_terrain_vertex_projected_or_scaled_buffer + iVar10) = fVar2 * _DAT_004be80c
    ;
    *(float *)(g_runtime_terrain_vertex_projected_or_scaled_buffer + 4 + iVar10) =
         fVar3 * _DAT_004be80c;
    puVar5 = g_runtime_terrain_arena_cursor;
    puVar6 = g_runtime_terrain_arena_cursor + 6;
    *g_runtime_terrain_arena_cursor = *param_1;
    g_runtime_terrain_arena_cursor = puVar6;
    puVar5[1] = (short)iVar4;
    *(undefined4 *)(puVar5 + 2) = 0;
    *(undefined4 *)(puVar5 + 4) = 0;
    g_runtime_terrain_edge_record_count = g_runtime_terrain_edge_record_count + 1;
    uVar1 = param_1[1];
    *(undefined2 **)(param_1 + 2) = puVar5;
    puVar5 = g_runtime_terrain_arena_cursor;
    puVar6 = g_runtime_terrain_arena_cursor + 6;
    *g_runtime_terrain_arena_cursor = (short)iVar4;
    g_runtime_terrain_arena_cursor = puVar6;
    puVar5[1] = uVar1;
    *(undefined4 *)(puVar5 + 2) = 0;
    *(undefined4 *)(puVar5 + 4) = 0;
    g_runtime_terrain_edge_record_count = g_runtime_terrain_edge_record_count + 1;
    *(undefined2 **)(param_1 + 4) = puVar5;
  }
  return;
}


