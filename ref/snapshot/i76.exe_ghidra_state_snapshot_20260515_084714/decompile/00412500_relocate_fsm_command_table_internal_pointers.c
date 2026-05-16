/*
 * Program: i76.exe
 * Function: relocate_fsm_command_table_internal_pointers
 * Entry: 00412500
 * Signature: undefined __cdecl relocate_fsm_command_table_internal_pointers(int * param_1, int param_2, int param_3, int param_4)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Relocates internal command-table pointers after
   serialized FSM table load and initializes command-list sentinels. */

void __cdecl
relocate_fsm_command_table_internal_pointers(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  
  if (0 < param_2) {
    do {
      piVar2 = param_1;
      if ((int *)param_1[0x42c] != param_1) {
        do {
          *piVar2 = param_4 + *piVar2 * 4;
          piVar2 = piVar2 + 1;
        } while ((int *)param_1[0x42c] != piVar2);
      }
      param_1[0x428] = 0;
      param_1[0x429] = param_3;
      param_1[0x42a] = param_3 + param_1[0x42a] * 8;
      *(undefined4 *)param_1[0x42c] = 0;
      iVar1 = param_1[0x42c];
      param_1[0x42c] = iVar1 + 4;
      *(int *)(iVar1 + 4) = param_1[0x42a];
      param_1[0x42b] = param_1[0x42c];
      param_1[0x42c] = param_1[0x42c] + 4;
      param_1[0x42d] = (int)(param_1 + 0x400);
      param_1 = (int *)param_1[0x42e];
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return;
}


