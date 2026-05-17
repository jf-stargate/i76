/*
 * Program: i76.exe
 * Function: remove_astar_tree_leftmost_node_recursive
 * Entry: 00417b60
 * Signature: undefined4 __cdecl remove_astar_tree_leftmost_node_recursive(int * param_1, int * param_2, int param_3)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Removes a leftmost child node from an A*/path binary
   tree and rebalances on unwind. */

undefined4 __cdecl remove_astar_tree_leftmost_node_recursive(int *param_1,int *param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = *param_2;
  if (*(int *)(iVar2 + 0x6c + param_3 * 8) == 0) {
    *param_1 = iVar2;
    *param_2 = *(int *)(*param_2 + 0x70 + param_3 * 8);
    return 1;
  }
  iVar2 = remove_astar_tree_leftmost_node_recursive
                    (param_1,(int *)(iVar2 + 0x6c + param_3 * 8),param_3);
  if (iVar2 != 0) {
    iVar2 = *(int *)(*param_2 + 100 + param_3 * 4);
    puVar1 = (undefined4 *)(*param_2 + 100 + param_3 * 4);
    if (iVar2 == 0) {
      *puVar1 = 2;
      return 1;
    }
    if (iVar2 == 2) {
      *puVar1 = 1;
      return 0;
    }
    if (iVar2 == 1) {
      uVar3 = rotate_astar_tree_node_after_insert_delete(param_2,param_3,1,0);
      return uVar3;
    }
  }
  return 0;
}


