/*
 * Program: i76.exe
 * Function: rotate_astar_tree_node_after_insert_delete
 * Entry: 00417510
 * Signature: undefined4 __cdecl rotate_astar_tree_node_after_insert_delete(int * param_1, int param_2, int param_3, int param_4)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Rebalances/rotates an A*/path tree node after
   insertion/deletion using side state fields. */

undefined4 __cdecl
rotate_astar_tree_node_after_insert_delete(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = param_2 * 2;
  iVar1 = (param_3 + iVar6) * 4 + 0x6c;
  iVar3 = *(int *)(*param_1 + iVar1);
  iVar2 = param_2 * 4 + 100;
  iVar4 = *(int *)(iVar3 + 100 + param_2 * 4);
  if ((iVar4 == param_3) || (iVar4 == 2)) {
    *(undefined4 *)(*param_1 + iVar1) = *(undefined4 *)(iVar3 + 0x6c + (param_4 + iVar6) * 4);
    *(int *)(iVar3 + 0x6c + (param_4 + iVar6) * 4) = *param_1;
    if (*(int *)(iVar3 + iVar2) == 2) {
      *(int *)(*param_1 + iVar2) = param_3;
      *(int *)(iVar3 + iVar2) = param_4;
      *param_1 = iVar3;
      return 0;
    }
    *(undefined4 *)(*param_1 + iVar2) = 2;
    *(undefined4 *)(iVar3 + iVar2) = 2;
    *param_1 = iVar3;
    return 1;
  }
  iVar5 = *(int *)(iVar3 + 0x6c + (param_4 + iVar6) * 4);
  iVar4 = (param_4 + iVar6) * 4 + 0x6c;
  *(undefined4 *)(iVar3 + iVar4) = *(undefined4 *)(iVar5 + iVar1);
  *(int *)(iVar5 + iVar1) = iVar3;
  *(undefined4 *)(*param_1 + iVar1) = *(undefined4 *)(iVar5 + iVar4);
  *(int *)(iVar5 + iVar4) = *param_1;
  if (*(int *)(iVar5 + iVar2) == param_3) {
    *(int *)(*param_1 + iVar2) = param_4;
  }
  else {
    *(undefined4 *)(*param_1 + iVar2) = 2;
  }
  if (*(int *)(iVar5 + iVar2) == param_4) {
    *(int *)(iVar3 + iVar2) = param_3;
    *param_1 = iVar5;
    *(undefined4 *)(iVar5 + iVar2) = 2;
    return 1;
  }
  *(undefined4 *)(iVar3 + iVar2) = 2;
  *param_1 = iVar5;
  *(undefined4 *)(iVar5 + iVar2) = 2;
  return 1;
}


