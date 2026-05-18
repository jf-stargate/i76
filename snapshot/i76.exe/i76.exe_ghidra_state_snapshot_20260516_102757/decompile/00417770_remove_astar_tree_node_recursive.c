/*
 * Program: i76.exe
 * Function: remove_astar_tree_node_recursive
 * Entry: 00417770
 * Signature: undefined4 __cdecl remove_astar_tree_node_recursive(int param_1, int * param_2, int * param_3, int param_4)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Removes a matching node from an A*/path binary tree
   using the path-node comparators and rebalancing helpers. */

undefined4 __cdecl
remove_astar_tree_node_recursive(int param_1,int *param_2,int *param_3,int param_4)

{
  undefined4 *puVar1;
  int iVar2;
  bool bVar3;
  undefined3 extraout_var;
  int iVar4;
  undefined4 uVar5;
  undefined3 extraout_var_00;
  
  if (*param_3 != 0) {
    bVar3 = compare_astar_open_node_less(param_1,*param_3,param_4);
    if (CONCAT31(extraout_var,bVar3) == 0) {
      bVar3 = compare_astar_open_node_greater(param_1,*param_3,param_4);
      if (CONCAT31(extraout_var_00,bVar3) == 0) {
        iVar2 = *param_3;
        iVar4 = param_4 * 8 + 0x70;
        if (*(int *)(iVar4 + iVar2) == 0) {
          *param_2 = iVar2;
          *param_3 = *(int *)(*param_3 + 0x6c + param_4 * 8);
          return 1;
        }
        if (*(int *)(iVar2 + 0x6c + param_4 * 8) == 0) {
          *param_2 = iVar2;
          *param_3 = *(int *)(*param_3 + iVar4);
          return 1;
        }
        iVar4 = remove_astar_tree_min_node_recursive
                          ((int *)(iVar2 + 0x6c + param_4 * 8),param_3,param_2,param_4,1);
        if (iVar4 == 1) {
          iVar4 = *(int *)(*param_3 + 100 + param_4 * 4);
          puVar1 = (undefined4 *)(*param_3 + 100 + param_4 * 4);
          if (iVar4 == 0) {
            *puVar1 = 2;
            return 1;
          }
          if (iVar4 == 2) {
            *puVar1 = 1;
            return 0;
          }
          if (iVar4 == 1) {
            uVar5 = rotate_astar_tree_node_after_insert_delete(param_3,param_4,1,0);
            return uVar5;
          }
        }
      }
      else {
        iVar4 = remove_astar_tree_node_recursive
                          (param_1,param_2,(int *)(*param_3 + 0x70 + param_4 * 8),param_4);
        if (iVar4 != 0) {
          iVar4 = *(int *)(*param_3 + 100 + param_4 * 4);
          puVar1 = (undefined4 *)(*param_3 + 100 + param_4 * 4);
          if (iVar4 == 1) {
            *puVar1 = 2;
            return 1;
          }
          if (iVar4 == 2) {
            *puVar1 = 0;
            return 0;
          }
          if (iVar4 == 0) {
            uVar5 = rotate_astar_tree_node_after_insert_delete(param_3,param_4,0,1);
            return uVar5;
          }
        }
      }
    }
    else {
      iVar4 = remove_astar_tree_node_recursive
                        (param_1,param_2,(int *)(*param_3 + 0x6c + param_4 * 8),param_4);
      if (iVar4 != 0) {
        iVar4 = *(int *)(*param_3 + 100 + param_4 * 4);
        puVar1 = (undefined4 *)(*param_3 + 100 + param_4 * 4);
        if (iVar4 == 0) {
          *puVar1 = 2;
          return 1;
        }
        if (iVar4 == 2) {
          *puVar1 = 1;
          return 0;
        }
        if (iVar4 == 1) {
          uVar5 = rotate_astar_tree_node_after_insert_delete(param_3,param_4,1,0);
          return uVar5;
        }
      }
    }
  }
  return 0;
}


