/*
 * Program: I76EDIT.EXE
 * Function: i76edit_link_road_edge_neighbors
 * Entry: 00415980
 * Signature: undefined4 __cdecl i76edit_link_road_edge_neighbors(int param_1, int param_2, int param_3, int param_4)
 */


/* [cgpt_i76edit_level_renames_v5:medium] Updates road node neighbor/edge pointers at payload
   offsets +0x40/+0x48 and reciprocal links. */

undefined4 __cdecl i76edit_link_road_edge_neighbors(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = (param_2 / 3) * 4 + *(int *)(param_1 + 8);
    *(int *)(iVar1 + 0x40) = param_3;
    *(int *)(iVar1 + 0x48) = param_4;
  }
  if (param_3 != 0) {
    iVar1 = *(int *)(param_3 + 8);
    *(int *)(iVar1 + 0x40 + (param_4 / 3) * 4) = param_1;
    *(int *)(iVar1 + 0x48 + (param_4 / 3) * 4) = param_2;
  }
  return 1;
}


