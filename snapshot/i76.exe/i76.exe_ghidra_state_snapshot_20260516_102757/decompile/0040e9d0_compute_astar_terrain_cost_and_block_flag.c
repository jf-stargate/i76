/*
 * Program: i76.exe
 * Function: compute_astar_terrain_cost_and_block_flag
 * Entry: 0040e9d0
 * Signature: float10 __cdecl compute_astar_terrain_cost_and_block_flag(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v11 astar/ai/fsm-loader cluster: Computes A* terrain traversal cost from terrain
   material and blocked-road flags, also setting a blocked flag in the node. */

float10 __cdecl
compute_astar_terrain_cost_and_block_flag
          (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  ushort uVar1;
  undefined2 extraout_var;
  uint uVar2;
  float10 fVar3;
  float local_8;
  
  uVar1 = lookup_terrain_material_index_at_world_xz((double)param_3,(double)param_4);
  switch(CONCAT22(extraout_var,uVar1)) {
  case 2:
  case 3:
  case 4:
    local_8 = 0.5;
    fVar3 = (float10)0.0;
    *(undefined4 *)(param_2 + 0x10) = 1;
    break;
  default:
    local_8 = 15.0;
    *(undefined4 *)(param_2 + 0x10) = 0;
    if ((*(int *)(param_1 + 0x9d14) == 0) ||
       (uVar2 = terrain_map_context_helper_004926f0((double)param_3,(double)param_4), uVar2 == 0)) {
      fVar3 = (float10)_DAT_004bc6b4;
    }
    else {
      fVar3 = (float10)_DAT_004bc6dc;
    }
    break;
  case 6:
  case 7:
    local_8 = 0.5;
    fVar3 = (float10)0.0;
    *(undefined4 *)(param_2 + 0x10) = 0;
  }
  if ((param_3 != param_5) && (param_4 != param_6)) {
    return (fVar3 + (float10)local_8) * (float10)_DAT_004bc6f0;
  }
  return (fVar3 + (float10)local_8) * (float10)_DAT_004bc670;
}


