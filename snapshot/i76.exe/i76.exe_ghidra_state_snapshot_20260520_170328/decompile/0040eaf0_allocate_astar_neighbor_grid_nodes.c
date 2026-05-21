/*
 * Program: i76.exe
 * Function: allocate_astar_neighbor_grid_nodes
 * Entry: 0040eaf0
 * Signature: undefined4 __cdecl allocate_astar_neighbor_grid_nodes(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v11 astar/ai/fsm-loader cluster: Allocates the eight neighboring A* grid nodes around
   a grid node and links them into neighbor slots. */

undefined4 __cdecl allocate_astar_neighbor_grid_nodes(int *param_1)

{
  int iVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  uint uVar9;
  double *pdVar10;
  
  floor((double)*param_1);
  iVar5 = ftol();
  floor((double)param_1[1]);
  iVar6 = ftol();
  dVar3 = *(double *)(param_1 + 10) + *(double *)(param_1 + 8);
  iVar1 = iVar5 + -10;
  iVar7 = iVar6 + -10;
  piVar8 = allocate_astar_grid_node(iVar1,iVar7,dVar3,(int)param_1);
  param_1[0xf] = (int)piVar8;
  if (piVar8 == (int *)0x0) {
    return 0;
  }
  piVar8 = allocate_astar_grid_node(iVar5,iVar7,dVar3,(int)param_1);
  param_1[0x10] = (int)piVar8;
  if (piVar8 == (int *)0x0) {
    return 0;
  }
  iVar2 = iVar5 + 10;
  piVar8 = allocate_astar_grid_node(iVar2,iVar7,dVar3,(int)param_1);
  param_1[0x11] = (int)piVar8;
  if (piVar8 == (int *)0x0) {
    return 0;
  }
  piVar8 = allocate_astar_grid_node(iVar1,iVar6,dVar3,(int)param_1);
  param_1[0x12] = (int)piVar8;
  if (piVar8 == (int *)0x0) {
    return 0;
  }
  piVar8 = allocate_astar_grid_node(iVar2,iVar6,dVar3,(int)param_1);
  param_1[0x13] = (int)piVar8;
  if (piVar8 == (int *)0x0) {
    return 0;
  }
  iVar7 = iVar6 + 10;
  piVar8 = allocate_astar_grid_node(iVar1,iVar7,dVar3,(int)param_1);
  param_1[0x14] = (int)piVar8;
  if (piVar8 == (int *)0x0) {
    return 0;
  }
  piVar8 = allocate_astar_grid_node(iVar5,iVar7,dVar3,(int)param_1);
  param_1[0x15] = (int)piVar8;
  if (piVar8 == (int *)0x0) {
    return 0;
  }
  piVar8 = allocate_astar_grid_node(iVar2,iVar7,dVar3,(int)param_1);
  param_1[0x16] = (int)piVar8;
  if (piVar8 == (int *)0x0) {
    return 0;
  }
  dVar4 = (double)iVar6 - (double)iVar5 * _DAT_004bc660;
  if (DAT_0051f654 == (double *)0x0) {
    uVar9 = 0;
  }
  else if (_DAT_004bc670 <= ABS(*DAT_0051f654 - dVar4)) {
    if (dVar4 <= *DAT_0051f654) {
      pdVar10 = *(double **)(DAT_0051f654 + 4);
    }
    else {
      pdVar10 = *(double **)((int)DAT_0051f654 + 0x1c);
    }
    uVar9 = find_bridge_validation_span_node_by_coordinate(pdVar10,dVar4);
  }
  else {
    uVar9 = ~-(uint)((*(uint *)(*(int *)(DAT_0051f654 + 3) + 0x10) & 0x200) != 0) &
            (uint)DAT_0051f654;
  }
  if (uVar9 != 0) {
    param_1[5] = 1;
    piVar8 = allocate_astar_grid_node
                       (*(int *)(uVar9 + 0x10),*(int *)(uVar9 + 0x14),dVar3,(int)param_1);
    param_1[0x17] = (int)piVar8;
    if (piVar8 == (int *)0x0) {
      return 0;
    }
    param_1[2] = 9;
    return 1;
  }
  param_1[5] = 0;
  param_1[2] = 8;
  return 1;
}


