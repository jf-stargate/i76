/*
 * Program: i76.exe
 * Function: find_astar_tree_node_or_insert_parent
 * Entry: 00417b00
 * Signature: undefined4 __cdecl find_astar_tree_node_or_insert_parent(int param_1, int param_2, int param_3, int * param_4)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Searches an A*/path binary tree for a node and returns
   the matching/insertion-parent node through an output pointer. */

undefined4 __cdecl
find_astar_tree_node_or_insert_parent(int param_1,int param_2,int param_3,int *param_4)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  
  while( true ) {
    while( true ) {
      if (param_2 == 0) {
        *param_4 = 0;
        return 0;
      }
      bVar1 = compare_astar_open_node_less(param_1,param_2,param_3);
      if (CONCAT31(extraout_var,bVar1) == 0) break;
      param_2 = *(int *)(param_2 + 0x6c + param_3 * 8);
    }
    bVar1 = compare_astar_open_node_greater(param_1,param_2,param_3);
    if (CONCAT31(extraout_var_00,bVar1) == 0) break;
    param_2 = *(int *)(param_2 + 0x70 + param_3 * 8);
  }
  *param_4 = param_2;
  return 1;
}


