/*
 * Program: i76.exe
 * Function: insert_astar_tree_node_recursive
 * Entry: 00417a10
 * Signature: undefined4 __cdecl insert_astar_tree_node_recursive(int param_1, int * param_2, int param_3)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Inserts an A*/path node into a binary tree and updates
   balance/side state fields. */

undefined4 __cdecl insert_astar_tree_node_recursive(int param_1,int *param_2,int param_3)

{
  undefined4 *puVar1;
  bool bVar2;
  undefined3 extraout_var;
  int iVar3;
  
  if (*param_2 == 0) {
    *param_2 = param_1;
    return 1;
  }
  bVar2 = compare_astar_open_node_less(param_1,*param_2,param_3);
  if (CONCAT31(extraout_var,bVar2) == 0) {
    iVar3 = insert_astar_tree_node_recursive(param_1,(int *)(*param_2 + 0x70 + param_3 * 8),param_3)
    ;
    if (iVar3 != 0) {
      iVar3 = *(int *)(*param_2 + 100 + param_3 * 4);
      puVar1 = (undefined4 *)(*param_2 + 100 + param_3 * 4);
      if (iVar3 == 0) {
        *puVar1 = 2;
        return 0;
      }
      if (iVar3 == 2) {
        *puVar1 = 1;
        return 1;
      }
      if (iVar3 == 1) {
        double_rotate_astar_tree_nodes(param_2,param_3,1,0);
      }
    }
  }
  else {
    iVar3 = insert_astar_tree_node_recursive(param_1,(int *)(*param_2 + 0x6c + param_3 * 8),param_3)
    ;
    if (iVar3 != 0) {
      iVar3 = *(int *)(*param_2 + 100 + param_3 * 4);
      puVar1 = (undefined4 *)(*param_2 + 100 + param_3 * 4);
      if (iVar3 == 1) {
        *puVar1 = 2;
        return 0;
      }
      if (iVar3 == 2) {
        *puVar1 = 0;
        return 1;
      }
      if (iVar3 == 0) {
        double_rotate_astar_tree_nodes(param_2,param_3,0,1);
        return 0;
      }
    }
  }
  return 0;
}


