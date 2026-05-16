/*
 * Program: i76.exe
 * Function: remove_astar_tree_min_node_recursive
 * Entry: 00417640
 * Signature: undefined4 __cdecl remove_astar_tree_min_node_recursive(int * param_1, int * param_2, int * param_3, int param_4, int param_5)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Removes the minimum-side node from an A*/path binary
   tree and rebalances the tree. */

undefined4 __cdecl
remove_astar_tree_min_node_recursive(int *param_1,int *param_2,int *param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar4 = param_4 * 8 + 0x70;
  if (*(int *)(*param_1 + iVar4) == 0) {
    *param_3 = *param_2;
    *param_2 = *param_1;
    iVar1 = param_4 * 8;
    iVar2 = param_4 * 4 + 100;
    *param_1 = *(int *)(*param_1 + 0x6c + iVar1);
    *(undefined4 *)(*param_2 + iVar2) = *(undefined4 *)(*param_3 + iVar2);
    *(undefined4 *)(*param_2 + 0x6c + iVar1) = *(undefined4 *)(*param_3 + 0x6c + iVar1);
    *(undefined4 *)(*param_2 + iVar4) = *(undefined4 *)(*param_3 + iVar4);
    return 1;
  }
  iVar4 = remove_astar_tree_min_node_recursive((int *)(*param_1 + iVar4),param_2,param_3,param_4,0);
  if (iVar4 == 1) {
    if (param_5 == 0) {
      puVar3 = (undefined4 *)(*param_1 + 100 + param_4 * 4);
      iVar4 = *(int *)(*param_1 + 100 + param_4 * 4);
      if (iVar4 == 1) {
        *puVar3 = 2;
        return 1;
      }
      if (iVar4 == 2) {
        *puVar3 = 0;
        return 0;
      }
      if (iVar4 == 0) {
        uVar5 = rotate_astar_tree_node_after_insert_delete(param_1,param_4,0,1);
        return uVar5;
      }
    }
    else {
      iVar4 = *(int *)(*param_2 + 0x6c + param_4 * 8);
      iVar1 = *(int *)(iVar4 + 100 + param_4 * 4);
      puVar3 = (undefined4 *)(iVar4 + 100 + param_4 * 4);
      if (iVar1 == 1) {
        *puVar3 = 2;
        return 1;
      }
      if (iVar1 == 2) {
        *puVar3 = 0;
        return 0;
      }
      if (iVar1 == 0) {
        uVar5 = rotate_astar_tree_node_after_insert_delete
                          ((int *)(*param_2 + 0x6c + param_4 * 8),param_4,0,1);
        return uVar5;
      }
    }
  }
  return 0;
}


