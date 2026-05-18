/*
 * Program: i76.exe
 * Function: pop_free_astar_grid_node
 * Entry: 0040e9a0
 * Signature: undefined __stdcall pop_free_astar_grid_node(void)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Pops one node from the free A* node list and updates
   peak node allocation counters. */

void pop_free_astar_grid_node(void)

{
  DAT_005244bc = DAT_005244bc + 1;
  if (DAT_0051f650 < DAT_005244bc) {
    DAT_0051f650 = DAT_005244bc;
  }
  if (DAT_0051f65c == 0) {
    return;
  }
  DAT_0051f65c = *(undefined4 *)(DAT_0051f65c + 0x60);
  return;
}


