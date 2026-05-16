/*
 * Program: i76.exe
 * Function: double_rotate_astar_tree_nodes
 * Entry: 00417920
 * Signature: undefined __cdecl double_rotate_astar_tree_nodes(int * param_1, int param_2, int param_3, int param_4)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Performs a double rotation/relink operation on A*/path
   binary tree nodes. */

void __cdecl double_rotate_astar_tree_nodes(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = param_2 * 2;
  iVar1 = param_2 * 4 + 100;
  iVar2 = (param_3 + iVar3) * 4 + 0x6c;
  iVar4 = *(int *)(*param_1 + iVar2);
  if (*(int *)(iVar4 + iVar1) == param_3) {
    *(undefined4 *)(*param_1 + iVar2) = *(undefined4 *)(iVar4 + 0x6c + (param_4 + iVar3) * 4);
    *(int *)(iVar4 + 0x6c + (param_4 + iVar3) * 4) = *param_1;
    *(undefined4 *)(*param_1 + iVar1) = 2;
    *param_1 = iVar4;
    *(undefined4 *)(iVar4 + iVar1) = 2;
    return;
  }
  iVar5 = *(int *)(iVar4 + 0x6c + (param_4 + iVar3) * 4);
  iVar3 = (param_4 + iVar3) * 4 + 0x6c;
  *(undefined4 *)(iVar4 + iVar3) = *(undefined4 *)(iVar5 + iVar2);
  *(int *)(iVar5 + iVar2) = iVar4;
  *(undefined4 *)(*param_1 + iVar2) = *(undefined4 *)(iVar5 + iVar3);
  *(int *)(iVar5 + iVar3) = *param_1;
  if (*(int *)(iVar5 + iVar1) == param_3) {
    *(int *)(*param_1 + iVar1) = param_4;
  }
  else {
    *(undefined4 *)(*param_1 + iVar1) = 2;
  }
  if (*(int *)(iVar5 + iVar1) == param_4) {
    *(int *)(iVar4 + iVar1) = param_3;
    *param_1 = iVar5;
    *(undefined4 *)(iVar5 + iVar1) = 2;
    return;
  }
  *(undefined4 *)(iVar4 + iVar1) = 2;
  *param_1 = iVar5;
  *(undefined4 *)(iVar5 + iVar1) = 2;
  return;
}


