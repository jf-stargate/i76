/*
 * Program: i76.exe
 * Function: allocate_terrain_leaf_primitive_node
 * Entry: 00491810
 * Signature: short * __cdecl allocate_terrain_leaf_primitive_node(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00491810. Remove
   duplicated terrain wording.
   
   [cgpt_i76exe_terrain_runtime_structs_v10] proposed=i76_runtime_alloc_terrain_primitive_node ::
   Allocates 0x1c-byte terrain primitive node: two short screen/range fields, int delta/range, two
   zero shorts, then four edge refs.
   
   [cgpt_i76exe_terrain_runtime_structs_v11] proposed=i76_runtime_alloc_terrain_primitive_node ::
   Allocates 0x1c-byte terrain primitive node: int16 start/end, int32 range_delta, next pointer,
   four edge refs.
   
   I76 rename v43: allocate_terrain_leaf_primitive_node
   Allocates/links emitted terrain primitive node. */

short * __cdecl
allocate_terrain_leaf_primitive_node
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  short *psVar1;
  short sVar2;
  int iVar3;
  
  psVar1 = g_runtime_terrain_arena_cursor;
  g_runtime_terrain_arena_cursor = g_runtime_terrain_arena_cursor + 0xe;
  sVar2 = ftol();
  *psVar1 = sVar2;
  sVar2 = ftol();
  psVar1[1] = sVar2;
  iVar3 = ftol();
  *(int *)(psVar1 + 2) = iVar3 - *psVar1;
  *(undefined4 *)(psVar1 + 6) = param_1;
  *(undefined4 *)(psVar1 + 8) = param_2;
  *(undefined4 *)(psVar1 + 10) = param_3;
  *(undefined4 *)(psVar1 + 0xc) = param_4;
  psVar1[4] = 0;
  psVar1[5] = 0;
  g_runtime_terrain_primitive_node_count = g_runtime_terrain_primitive_node_count + 1;
  return psVar1;
}


