/*
 * Program: i76.exe
 * Function: allocate_astar_grid_node
 * Entry: 0040e900
 * Signature: int * __cdecl allocate_astar_grid_node(int param_1, int param_2, undefined8 param_3, int param_4)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Allocates and initializes an A* grid node from grid
   X/Z coordinates, base cost, and parent pointer. */

int * __cdecl allocate_astar_grid_node(int param_1,int param_2,undefined8 param_3,int param_4)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  piVar1 = (int *)pop_free_astar_grid_node();
  if (piVar1 == (int *)0x0) {
    return (int *)0x0;
  }
  piVar1[1] = param_2;
  piVar1[0xe] = param_4;
  *(undefined8 *)(piVar1 + 8) = param_3;
  *piVar1 = param_1;
  *(undefined8 *)(piVar1 + 6) = param_3;
  piVar1[10] = 0;
  piVar1[0xc] = 0;
  piVar1[4] = 0;
  piVar1[3] = param_2 * 100000 + param_1;
  piVar1[0xb] = 0;
  piVar1[0xd] = 0;
  piVar1[2] = 0;
  piVar2 = piVar1 + 0xf;
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
  }
  piVar2 = piVar1 + 0x1c;
  piVar4 = piVar1 + 0x19;
  iVar3 = 2;
  do {
    *piVar4 = 2;
    piVar2[-1] = 0;
    *piVar2 = 0;
    piVar4 = piVar4 + 1;
    piVar2 = piVar2 + 2;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return piVar1;
}


