/*
 * Program: i76.exe
 * Function: relax_astar_neighbor_cost_recursive
 * Entry: 0040f0a0
 * Signature: undefined __cdecl relax_astar_neighbor_cost_recursive(int * param_1, int * param_2, int * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v11 astar/ai/fsm-loader cluster: Relaxes an A* neighbor node cost through a parent
   node and recursively propagates cost changes to child nodes. */

void __cdecl relax_astar_neighbor_cost_recursive(int *param_1,int *param_2,int *param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  bool bVar4;
  int iVar5;
  int *piVar6;
  int local_14;
  undefined8 local_10;
  undefined8 local_8;
  
  piVar6 = (int *)param_1[0xe];
  local_14 = 0;
  bVar4 = false;
  if (piVar6 != (int *)0x0) {
    if (piVar6 != param_2) {
      dVar2 = *(double *)(param_2 + 8) + *(double *)(param_2 + 10);
      iVar5 = *param_1;
      dVar1 = *(double *)(param_1 + 10);
      if ((iVar5 == *piVar6) || (param_1[1] == piVar6[1])) {
        if ((iVar5 != *param_2) && (param_1[1] != param_2[1])) {
          dVar1 = dVar1 * _DAT_004bc6f0;
        }
      }
      else if ((iVar5 == *param_2) || (param_1[1] == param_2[1])) {
        dVar1 = dVar1 * _DAT_004bc708;
      }
      dVar3 = *(double *)(param_1 + 0xc) + dVar1 + dVar2;
      local_10 = dVar2;
      local_8 = dVar3;
      if (dVar3 < *(double *)(param_1 + 6)) {
        local_10._0_4_ = SUB84(dVar2,0);
        local_8._0_4_ = SUB84(dVar3,0);
        local_10._4_4_ = (int)((ulonglong)dVar2 >> 0x20);
        param_1[8] = (int)local_10;
        local_8._4_4_ = (int)((ulonglong)dVar3 >> 0x20);
        param_1[6] = (int)local_8;
        *(double *)(param_1 + 10) = dVar1;
        param_1[0xe] = (int)param_2;
        param_1[9] = local_10._4_4_;
        param_1[7] = local_8._4_4_;
        bVar4 = true;
      }
    }
    if ((int *)param_1[0xe] == param_2) {
      iVar5 = param_1[2];
      if (iVar5 == -1) {
        remove_astar_tree_node_recursive((int)param_1,&local_14,param_3,1);
      }
      if (!bVar4) {
        dVar1 = *(double *)(param_2 + 8);
        dVar2 = *(double *)(param_2 + 10);
        *(double *)(param_1 + 8) = dVar1 + dVar2;
        *(double *)(param_1 + 6) =
             *(double *)(param_1 + 10) + *(double *)(param_1 + 0xc) + dVar1 + dVar2;
      }
      if (iVar5 == -1) {
        insert_astar_tree_node_recursive((int)param_1,param_3,1);
        return;
      }
      if (0 < iVar5) {
        piVar6 = param_1 + 0xf;
        do {
          relax_astar_neighbor_cost_recursive((int *)*piVar6,param_1,param_3);
          piVar6 = piVar6 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
    }
  }
  return;
}


