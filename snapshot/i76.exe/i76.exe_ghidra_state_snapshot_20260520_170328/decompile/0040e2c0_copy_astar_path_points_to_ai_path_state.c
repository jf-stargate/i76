/*
 * Program: i76.exe
 * Function: copy_astar_path_points_to_ai_path_state
 * Entry: 0040e2c0
 * Signature: undefined __cdecl copy_astar_path_points_to_ai_path_state(int param_1, int param_2, int param_3)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Copies path point coordinates and turn/flag fields
   into an AI path-state output block. */

void __cdecl copy_astar_path_points_to_ai_path_state(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  
  if (0 < param_3) {
    puVar2 = (undefined4 *)(param_1 + 0xb8);
    piVar3 = (int *)(param_2 + 8);
    iVar4 = param_3;
    do {
      puVar2[-2] = piVar3[-2];
      puVar2[-1] = piVar3[-1];
      if (*piVar3 == 0x3f800000) {
        *puVar2 = 1;
LAB_0040e310:
        puVar2[1] = 0;
      }
      else {
        iVar1 = *piVar3;
        *puVar2 = 0;
        if (iVar1 != 0x40000000) goto LAB_0040e310;
        puVar2[1] = 1;
      }
      piVar3 = piVar3 + 3;
      puVar2 = puVar2 + 5;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  *(undefined4 *)(param_1 + 0xa8) = 0;
  *(int *)(param_1 + 0xac) = param_3;
  return;
}


