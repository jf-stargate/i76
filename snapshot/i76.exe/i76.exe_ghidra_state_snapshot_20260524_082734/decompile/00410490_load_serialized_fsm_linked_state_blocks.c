/*
 * Program: i76.exe
 * Function: load_serialized_fsm_linked_state_blocks
 * Entry: 00410490
 * Signature: undefined __cdecl load_serialized_fsm_linked_state_blocks(undefined4 * param_1, int * param_2, HANDLE param_3)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Loads serialized FSM/AI linked state blocks of size
   0x10bc and patches each block's internal pointer fields.
   
   I76 rename v43: fsm_load_linked_state_blocks
   FSM linked state-block loader. */

void __cdecl
load_serialized_fsm_linked_state_blocks(undefined4 *param_1,int *param_2,HANDLE param_3)

{
  int iVar1;
  LPVOID pvVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  LPVOID pvVar6;
  int iVar7;
  
  g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
  iVar7 = *(int *)(g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
  *param_2 = iVar7;
  if (iVar7 == 0) {
    *param_1 = 0;
    return;
  }
  pvVar2 = HeapAlloc(param_3,0,0x10bc);
  iVar7 = 1;
  *param_1 = pvVar2;
  pvVar6 = pvVar2;
  if (1 < *param_2) {
    do {
      pvVar2 = HeapAlloc(param_3,0,0x10bc);
      *(LPVOID *)((int)pvVar6 + 0x10b8) = pvVar2;
      iVar7 = iVar7 + 1;
      pvVar6 = pvVar2;
    } while (iVar7 < *param_2);
  }
  iVar7 = 0;
  *(undefined4 *)((int)pvVar2 + 0x10b8) = 0;
  puVar3 = (undefined4 *)*param_1;
  if (0 < *param_2) {
    do {
      g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
      puVar3[0x42a] =
           *(undefined4 *)
            (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
      g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
      iVar1 = *(int *)(g_fsm_serialized_stream_cursor + -4 +
                      g_fsm_serialized_stream_limit_or_base * 4);
      iVar5 = 0x28;
      puVar4 = puVar3;
      do {
        g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
        iVar5 = iVar5 + -1;
        *puVar4 = *(undefined4 *)
                   (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4)
        ;
        puVar4 = puVar4 + 1;
      } while (iVar5 != 0);
      puVar3[0x42c] = puVar3 + iVar1;
      puVar3 = (undefined4 *)puVar3[0x42e];
      iVar7 = iVar7 + 1;
    } while (iVar7 < *param_2);
  }
  return;
}


