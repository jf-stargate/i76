/*
 * Program: i76.exe
 * Function: compare_astar_open_node_greater
 * Entry: 0040edc0
 * Signature: bool __cdecl compare_astar_open_node_greater(int param_1, int param_2, int param_3)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Reverse A* priority comparator: orders nodes by
   accumulated score/cost in the opposite direction. */

bool __cdecl compare_astar_open_node_greater(int param_1,int param_2,int param_3)

{
  if (param_3 == 0) {
    return *(int *)(param_2 + 0xc) < *(int *)(param_1 + 0xc);
  }
  if (*(double *)(param_2 + 0x18) < *(double *)(param_1 + 0x18)) {
    return true;
  }
  if (*(double *)(param_1 + 0x18) == *(double *)(param_2 + 0x18)) {
    return *(int *)(param_2 + 0xc) < *(int *)(param_1 + 0xc);
  }
  return false;
}


