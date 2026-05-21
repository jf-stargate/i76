/*
 * Program: i76.exe
 * Function: compute_road_loop_distance_between_nodes
 * Entry: 0040d3f0
 * Signature: int __cdecl compute_road_loop_distance_between_nodes(int param_1, int param_2, int param_3, int param_4, int param_5)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Computes accumulated distance between two road-loop
   nodes in forward or reverse traversal direction. */

int __cdecl
compute_road_loop_distance_between_nodes
          (int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 1) {
    if (param_2 == param_4) {
      return param_3 - param_5;
    }
    iVar1 = *(int *)(param_2 + 8);
    if (iVar1 != 0) {
      for (; iVar1 != param_4; iVar1 = *(int *)(iVar1 + 8)) {
        param_3 = param_3 + *(int *)(iVar1 + 0x14);
      }
      param_3 = param_3 + (*(int *)(iVar1 + 0x14) - param_5);
    }
    return param_3;
  }
  if (param_2 == param_4) {
    return param_5 - param_3;
  }
  iVar2 = *(int *)(param_2 + 0x14) - param_3;
  for (iVar1 = *(int *)(param_2 + 4); iVar1 != param_4; iVar1 = *(int *)(iVar1 + 4)) {
    iVar2 = iVar2 + *(int *)(iVar1 + 0x14);
  }
  return iVar2 + param_5;
}


